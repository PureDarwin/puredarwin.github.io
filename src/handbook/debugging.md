# Debugging

Most PureDarwin debugging is done from the boot log, because when something is wrong
there is often no userland left to debug from.

## Getting a Console

**Serial is the primary console.** `serial=` in the boot arguments is a bitmask: 1 is
read, 2 is write and 3 is both. `serial=3` is almost always what you want. An
output-only console cannot take input, and an input-only one shows you nothing. Under QEMU, `.#vm` puts it on your terminal with `-serial mon:stdio`.

**The framebuffer console** is what you get without serial. `gopconsole=1` enables it,
and `serial_video_mirror=1` sends the same output to both.

On x86 with no serial port, watch out for the interaction described in
[Boot Chain](images/boot-chain.md). If the loader hands over a graphics-mode
`v_display`, the kernel's framebuffer text console is disabled and you see nothing.

For very early boot, or when the console is dead, the kernel can paint progress bars
directly on the framebuffer, and there is a shared-memory tracer that writes into a DRAM
ring. The tracer keeps working after the identity mapping is torn down, which is past
the point where early UART and `printf` are useful.

Logging early can mislead you in both directions. In early userspace, launchd and the
first daemons, the logging helpers buffer. A trace that never appears may have run
perfectly well. Writing straight to the console file descriptor with `write(2)` avoids
the buffer. In kernel code the equivalent question is `IOLog` against `kprintf`, which
do not reach the same places at the same times.

## Boot Arguments Worth Knowing

| Argument | Effect |
| --- | --- |
| `-v` | Verbose boot |
| `debug=0x218` | The usual debug flag set for development |
| `debug=0x8` | Needed for `disable_serial_output` to take effect |
| `keepsyms=1` | Keep symbols so panics are symbolicated |
| `serial=N` | Serial console bitmask: 1 read, 2 write, 3 both |
| `gopconsole=1` | Framebuffer console |
| `serial_video_mirror=1` | Mirror console output to both |
| `-nogzalloc_mode` | Disable the guard allocator |
| `-noprogress` | No boot progress meter |
| `rd=md0` | Root from the RAM disk |
| `no_interrupt_masked_debug=1` | Needed on ARM targets |
| `pdtrace=1` | Project tracing |
| `cpus=1` | Start only the boot CPU. Rules out problems bringing up the other CPUs |
| `pdapdbg=1` | Print each step of CPU startup straight to the screen |
| `pdi915=0`, `pdamdgpu=0`, `pdnouveau=0` | Keep a DRM GPU driver from attaching, so the firmware framebuffer stays |
| `pdfb_pattern=1` | Draw colour bars when amdgpu lights a display |
| `csr-active-config=0x3` | Lets the auxiliary kernel collection load from the ext4 root |
| `pdlogsave=0` | Turn off the saved kernel log in `/var/log` |
| `pci=0x4000000` | Historical PFM64 window workaround for some AMD machines. No longer needed |
| `kext=0xffff io=0xffff` | Very verbose kext and IOKit matching logs |
| `gen9_debug=1`, `ahci_debug=1`, `vgpu_debug=1` | Per-subsystem logging |

Edit them in `\EFI\BOOT\boot-args.txt` on the ESP. There is no need to rebuild the
image. If you edit it with `mtools`, keep the long file name, or the loader falls back
to its defaults.

Note that verbose logging over a slow serial line applies real back-pressure. A boot
that appears to hang with everything enabled may just be waiting on the UART. That
mistake has been made here more than once.

After a hang on real hardware, the saved kernel log in `/var/log/dmesg-boot.0.txt` and
`dmesg-boot.1.txt` often has what the screen lost. Mount the root partition from
another machine to read it.

## Driving a VM

Boot a qcow2 overlay on top of the image so the original stays pristine and a reset is
just deleting the overlay. When the guest console is output-only, `sendkey` through the
QEMU monitor gets input in. A LaunchDaemon with `StandardOutPath` set to `/dev/console`
is a reliable way to get a service's output onto the console.

## Working Inside the Guest

The guest has more than you might expect. `curl` and `clang` are both there, which means
you can probe a guest-local service from inside the guest and compile a test case in
place. Some tools are missing, including `netstat`, `od` and `timeout`.

Two guest-specific gotchas:

* `hw.pagesize` reports the task's 16K granule, so pairing it with `vm_statistics64`
  gives numbers four times too large. `/usr/bin/vmprobe` exists for this.
* `ioreg` is the first thing to reach for when a device is not working. A kext present
  in the collection but absent from the IOKit registry usually means matching failed.
  The driver itself may be fine.

## Reading a Kernel Collection

The in-tree `otool` understands `MH_FILESET`, so `otool -l` on a KC lists its entries.
If a kext seems to be in the collection but does nothing, check its Info.plist
properties in the raw image. `kc-tools` truncates a `<dict>` after an XML comment, and
the kext loses `IOProviderClass` without any error.

## Panic Signatures

| What you see | Usual cause |
| --- | --- |
| Corrupt or garbled panic string | Something stripped from the exports at RELEASE, `__cxa_atexit` being the known case |
| `bad extent magic 0x0` from ext4 | Stale vnode reuse handing back a freed node |
| Panic in `vm_compressor_init` | Early arm64 memory configuration |
| `sleh_irq` NULL handler | Interrupts not quiesced by the bootloader before the jump |
| SIGILL in an arm64 binary | LSE atomics. Build with `-mcpu=apple-a10` |
| SIGSEGV on the first `__thread` access | The TLV runtime was never initialised |
| Everything stops during IOKit matching | A driver spinning in `start()`, blocking the quiesce |
| `Unsupported CPU` before the console comes up | A CPU model missing from the kernel's table. Read the panic from memory with the QEMU monitor |
| `element modified after free` in a `kalloc` zone | Memory written after it was freed. A clock running far too fast in a VM made one such race easy to hit |

## When It Is the Filesystem

ext4 is project code and has been the root cause of a long list of bugs that presented
as something else: launchd races, files reverting after a reboot, applications looping
on restart, and apparent memory corruption. If a failure looks like corruption and you
cannot pin it down, boot `image-hfs`. Same system, Apple's own HFS driver, and if the
problem disappears you have your answer.
