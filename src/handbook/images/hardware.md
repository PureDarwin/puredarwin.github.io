# Running on Real Hardware

QEMU hides things. Real machines are where the driver bugs live, and where most of the
project's harder problems have been found.

## Writing an Image

Build an image, copy it out of the Nix store and write it to a disk. Check the device name
twice. `dd` to the wrong device destroys the host.

```
nix build .#image-gpu
cp result/*.img /tmp/pd.img
sudo dd if=/tmp/pd.img of=/dev/sdX bs=4M status=progress conv=fsync
sync
```

Wait for `sync` to return before you unplug the drive. A stick pulled early can still
hold parts of the previous image. To check what you wrote, mount the first partition and
compare the sha256 of `EFI/BOOT/kernel` with the one in the image.

`image-gpu` is the desktop image with every GPU driver. `image-minimal` is the small
image for boot testing. See [Image Flavours](flavours.md).

## What Is Known to Work

This is a record of what has been tried. It makes no compatibility promise. A machine
missing from these tables has usually not been tested.

### Virtualisation

| | Status |
| --- | --- |
| KVM | Works on most machines |
| QEMU TCG | Works on some CPU models and fails on others. IvyBridge is confirmed |
| QEMU named CPU models | Work. Use `host` passthrough when you can, because some named models omit CPUID details the kernel reads |

That TCG caveat is why `nix run .#vm` passes `-cpu IvyBridge`. It is a known good model.
If you change it and the guest stops booting, suspect the CPU model before your change.

### Drivers

| Driver | Status |
| --- | --- |
| AHCI | Works on all hardware tried |
| NVMe | Works |
| xHCI | Works on nearly all hardware |
| EHCI | Works on most hardware |
| UHCI | Device only |
| OHCI | Unknown |
| AMD GPUs (amdgpu) | RX 7800 XT and RX 7900 XTX reach the desktop with OpenGL |
| NVIDIA GPUs (nouveau) | Quadro 410, Quadro K620, GeForce 9500 GT and GeForce 7900 GS reach the desktop with OpenGL |
| Intel GPUs (i915) | Gen9 and Gemini Lake work |
| PS/2 | Works |
| `PDACPIPlatform` | Works on most Intel and AMD hardware |

### Intel

| Platform | Status |
| --- | --- |
| Gemini Lake | Works, confirmed on two J5005 boards |
| Skylake desktop | Boots to the desktop |
| Haswell | Confirmed on one board |
| Ivy Bridge, Sandy Bridge | Works on some boards, reaches kernel handoff on all |
| Kaby Lake and newer | Works |
| Meteor Lake | Confirmed on one board |

### AMD

| Platform | Status |
| --- | --- |
| AM4, Zen to Zen 2 | Boots |
| AM5, Zen 4 | Boots to the desktop, confirmed with a Ryzen 5 7600X and an RX 7900 XTX |
| Mendocino (Ryzen 5 7520U) | Boots to the desktop on all cores |
| AM3 | Unknown |

## Firmware Settings

* UEFI boot. The `-legacy` images also boot on BIOS machines.
* Secure Boot either off, or on with an `-sb` image. See [Secure Boot](secure-boot.md)
  for the one-time setup.
* AHCI for SATA. RAID and Intel RST modes are not supported.

## Known Machine-Specific Issues

**AMD Ryzen PFM64 window.** Boot-time PCI reallocation used to shrink the window that
holds the EFI framebuffer, and the display disappeared. Old notes may mention
`pci=0x4000000` as a workaround. It is fixed now, and the boot argument is no longer
needed.

**Devices behind a closed PCI bridge window.** If firmware leaves a bridge window closed,
a device behind it reads back all `0xff` over MMIO. This is what made an RTL8168 look
like a dead card.

**PS/2 controllers that are not there.** On laptops with no 8042 controller, an early
version of the PS/2 driver spun forever and held up IOKit for six minutes. This is fixed.
If a machine with no 8042 hangs partway through IOKit, that is the shape of the bug.

**SATA disks stuck with TFD 0x80.** FRE has to stay enabled across COMRESET, or the first
D2H FIS is dropped. QEMU tolerates it, real controllers do not.

## What a Healthy Boot Looks Like

The images boot verbose, so every stage prints to the screen. In order:

1. **The loader.** Lines about kernel segments, `KASLR`, the TSC frequency, the device
   tree and `MCFG`. Then the screen clears and the kernel takes over.
2. **The kernel and ACPI.** `PDACPIPlatform` lists the ACPI tables, then
   `MADT reports N enabled processors`, one line for each CPU the firmware describes.
3. **The other CPUs.** `[processor_init] processor N belongs to processor set 0` for each
   CPU, then `Started cpu N` for each one.
4. **Devices.** USB, NVMe, SATA and network drivers attach. Expect a lot of lines here.
5. **The root disk.** `Ext4FileSystemDriver: publishing boot-uuid-media 'Darwin ext4 Root'`.
   The kernel has found the PureDarwin partition and mounts it.
6. **Userland.** launchd starts the system daemons. On the desktop images the display
   switches mode and the Argon desktop appears, with the menu bar and the Dock. The
   minimal images stop at a `#` prompt instead.

In QEMU this takes well under a minute. Real machines vary, and the first boot of a
desktop image takes longer while GPU firmware loads.

### Where It Stops Tells You What Broke

| Last thing on screen | Likely cause | What to try |
| --- | --- | --- |
| The loader's `MCFG` line, nothing after | The kernel stopped before its console came up, often an unsupported CPU model | Report the CPU model |
| `watching for ext4 boot volume` and no more | The root disk was not found | Try another USB port, or SATA in AHCI mode |
| The display goes black or grey after the mode switch | A GPU driver | `pdamdgpu=0`, `pdi915=0` or `pdnouveau=0` |
| A `panic(` line | A kernel panic | Photograph the whole screen |

Boot arguments go in `EFI/BOOT/boot-args.txt` on the EFI partition, all on one line. When
you edit it with mtools, write it under its long name. Writing the short `BOOT-A~1.TXT`
name drops the long name, and the loader quietly falls back to its defaults.

After a hang or a power cut, the kernel log of the last boot is on the root partition in
`/var/log/dmesg-boot.0.txt` and `/var/log/dmesg-boot.1.txt`.

## Getting Output

Serial is the best console when you have it. `serial=` is a bitmask: 1 read, 2 write, 3
both. Use `serial=3` unless you have a reason not to. Verbose logging over a slow serial
line can push back hard enough to look exactly like a hang.

For machines with no serial port, the kernel can paint progress bars on the framebuffer.
On a laptop or a modern desktop board that is often the only signal, and it is enough to
tell how far boot got.

The kernel log is also saved to `/var/log/dmesg-boot.0.txt` and `dmesg-boot.1.txt`
while the system runs. After a hang, mount the root partition from another machine and
read them. `pdlogsave=0` or an empty `/etc/no-dmesg-save` turns this off.

If you get no display at all on x86, check the console setup before the driver. A loader
that hands over a graphics-mode `v_display` disables the framebuffer text console.

## Reporting a Hardware Bug

Include the machine, the firmware mode, the boot arguments and as much of the serial or
photographed console output as you have. A boot that stops with a panic message is much
easier to work with than one that stops with no output, so get a console working first.
