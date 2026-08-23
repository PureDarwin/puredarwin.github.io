# Running on real hardware

QEMU hides things. Real machines are where the driver bugs live, and where most of the
project's harder problems have been found.

## Writing an image

Build an image, copy it out of the Nix store, and write it to a disk. Check the device
name twice; `dd` to the wrong one destroys the host.

```
nix build .#image-minimal
cp result/puredarwin-minimal.img /tmp/pd.img
sudo dd if=/tmp/pd.img of=/dev/sdX bs=4M status=progress conv=fsync
```

Comparing sha256 of the source and the written device is a cheap way to catch a bad
cable or a truncated write.

## What is known to work

This is a record of what has actually been tried, not a compatibility promise. Absence
from these tables usually means nobody has tested it, not that it fails.

### Virtualisation

| | Status |
| --- | --- |
| KVM | Works on most machines, tested on several without issue |
| QEMU TCG | Works flawlessly on some CPU models and dies on others. IvyBridge is confirmed |

That TCG caveat is why `nix run .#vm` passes `-cpu IvyBridge`. It is a known-good model
rather than an arbitrary one, so if you change it and the guest stops booting, suspect
the CPU model before you suspect your change.

### Drivers

| Driver | Status |
| --- | --- |
| AHCI | Works on all hardware tried |
| xHCI | Works on nearly all hardware |
| EHCI | Works on most hardware |
| UHCI | Device only |
| OHCI | Unknown |
| `IOIntelFramebuffer` | Confirmed on Gen9 (Gemini Lake). The code comes from `lil` and carries support for Gen7 and other older targets, but those are untested |
| PS/2 | Partially working. Keycodes are known to be unreliable |
| `PDACPIPlatform` | Works on most Intel hardware. Not reliable on some AMD boards |

### Intel

| Platform | Status |
| --- | --- |
| Gemini Lake | Confirmed on two boards, both J5005. Modesetting works |
| Haswell | Confirmed on one board |
| Meteor Lake | Confirmed on one board |
| Ivy Bridge | Works on some boards, reaches kernel handoff on all. Varies |
| Sandy Bridge | As Ivy Bridge. Varies |
| Alder Lake | Early kernel panic, does not boot |

### AMD

| Platform | Status |
| --- | --- |
| AM4, Zen | Boots to a shell |
| AM4, Zen+ | Boots to a shell |
| AM4, Zen 2 | Boots to a shell |
| AM5 | Dies at handoff. Confirmed on the 9000 desktop series (9900X) |
| AM3 | Unknown |

AM5 is hard to diagnose precisely because modern boards ship without a serial port, so
there is no console to read the failure from. If you have an AM5 machine, the
framebuffer progress bars described below are currently the best available signal.

## Firmware settings

* UEFI boot, not CSM or legacy.
* Secure Boot off. Nothing here is signed.
* AHCI rather than RAID or Intel RST for SATA.

## Known machine-specific issues

**AMD Ryzen PFM64 window.** Boot-time PCI reallocation used to shrink the PFM64 window
that holds the EFI framebuffer, and the display would disappear. This was worked around
with `pci=0x4000000` in the boot-args; it is now fixed properly in the underlying
support, so the boot-arg is no longer needed. If you find it in an old thread or an old
set of notes, that is why.

**Machines behind a firmware-closed PCI bridge window.** IOPCIFamily does not assign P2P
bridge apertures, so a device behind a window the firmware left closed reads back all
0xff over MMIO. This is what made an RTL8168 look like a dead card.

**PS/2 controllers that are not there.** `ApplePS2Controller::start()` used to spin
forever when the status port floated at 0xff, holding its nub busy and blocking the
IOKit quiesce for six minutes. Fixed, but if a laptop with no 8042 hangs partway through
IOKit, that is the shape of the bug.

**SATA disks stuck with TFD 0x80.** FRE has to stay enabled across COMRESET or the
initial D2H FIS is dropped. QEMU tolerated it; real controllers do not.

## Getting output

Serial is the best console when you have it. `serial=` is a bitmask rather than a port
number: 1 read, 2 write, 3 both. Use `serial=3` unless you have a reason not to, and
note that verbose logging over a slow serial line can apply enough back-pressure to look
exactly like a hang. A machine that appears to stop partway through boot with verbose
logging on may just be waiting on the UART.

For machines with no serial port and no POST card, the kernel can paint progress bars
directly on the framebuffer. That is often the only signal available on a laptop or a
modern desktop board, and it is enough to tell how far boot got. This is the situation
on AM5, where the absence of serial is the main reason the handoff failure there is
still uncharacterised.

If you get no display at all on x86, check the console selection first rather than the
driver: a loader that hands over a graphics-mode `v_display` disables the framebuffer
text console outright.

## Reporting a hardware bug

Include the machine, the firmware mode, the boot-args used, and as much of the serial or
photographed console output as you have. A boot that stops with no output is much harder
to work with than one that stops with a panic string, so try to get a console working
before filing.
