# Debugging

Most debugging in PureDarwin starts from the boot log. When something goes wrong early,
there's often no userland left to debug from.

## Getting a Console

A console is where the kernel prints its messages, so get one working before anything
else.

**Serial is the best console.** `serial=` in the boot arguments is a bitmask. 1 is read,
2 is write and 3 is both. `serial=3` is almost always what you want. In QEMU, `nix run
.#vm` puts the serial console in your terminal.

**The framebuffer console** is what you get without serial. `gopconsole=1` turns it on,
and `serial_video_mirror=1` sends the same output to both.

On x86_64 without a serial port, watch for one problem described in
[Boot Chain](images/boot-chain.md). If the loader hands the kernel a screen in graphics
mode, the kernel's text console turns itself off and you see nothing.

For very early boot, or when the console is dead, the kernel can draw progress bars
straight onto the screen. There's also a tracer that writes into a ring buffer in memory, and it keeps working later in boot than the early serial output does.

Early logging can mislead you both ways. In early userspace, meaning launchd and the
first daemons, the logging helpers hold output in a buffer. A message that never appears may have come from code that ran fine, and writing straight to the console with
`write(2)` avoids the buffer. In kernel code, `IOLog` and `kprintf` don't reach the same
places at the same times.

## Useful Boot Arguments

| Argument | Effect |
| --- | --- |
| `-v` | Verbose boot |
| `debug=0x218` | The usual set of debug flags for development |
| `debug=0x8` | Needed for `disable_serial_output` to take effect |
| `keepsyms=1` | Keep symbols, so panics show function names |
| `serial=N` | Serial console bitmask. 1 read, 2 write, 3 both |
| `gopconsole=1` | Framebuffer console |
| `serial_video_mirror=1` | Send console output to both |
| `-nogzalloc_mode` | Turn off the guard allocator |
| `-noprogress` | No boot progress bar |
| `rd=md0` | Use the RAM disk as root |
| `no_interrupt_masked_debug=1` | Needed on ARM targets |
| `pdtrace=1` | PureDarwin's own tracing |
| `cpus=1` | Start only the first CPU. Rules out problems starting the others |
| `pdapdbg=1` | Print each step of CPU start-up to the screen |
| `pdi915=0`, `pdamdgpu=0`, `pdnouveau=0` | Keep a GPU driver from attaching, so the firmware framebuffer stays |
| `pdfb_pattern=1` | Draw colour bars when the AMD driver turns on a display |
| `csr-active-config=0x3` | Lets the auxiliary kernel collection load from the root disk |
| `pdlogsave=0` | Don't save the kernel log to `/var/log` |
| `kext=0xffff io=0xffff` | Very detailed logs of kext loading and driver matching |
| `drm_debug=0x6 fbsdkpi_debug=1` | GPU driver and driver-layer logging |
| `gen9_debug=1`, `ahci_debug=1`, `vgpu_debug=1` | Logging for one subsystem |

Boot arguments live in `\EFI\BOOT\boot-args.txt` on the EFI partition, and you can change them without rebuilding the image. If you edit the file with `mtools`, keep its long
file name, or the loader falls back to its defaults.

Verbose logging over a slow serial line slows the whole system down. A boot that seems
to hang with every log turned on may just be waiting for the serial port.

After a hang on real hardware, the kernel log saved in `/var/log/dmesg-boot.0.txt` and
`dmesg-boot.1.txt` often has what the screen lost. Mount the root partition on another
computer to read it.

## Driving a Virtual Machine

Boot from a qcow2 overlay on top of the image. The original stays untouched, and
deleting the overlay gives you a clean start. When the guest console only shows output,
`sendkey` in the QEMU monitor can type into it. A LaunchDaemon with `StandardOutPath`
set to `/dev/console` is a reliable way to get a service's output onto the console.

## Working Inside the Guest

The guest has more tools than you might expect. `curl` and `clang` are both there, so
you can test a service from inside the guest and compile a test program in place.

`ioreg` is the first thing to try when a device doesn't work. If a kext is in the
kernel collection but missing from the IOKit registry, matching usually failed. The
driver itself may be fine.

## Reading a Kernel Collection

The `otool` in the tree understands kernel collections, so `otool -l` lists what's in
one. If a kext is in the collection but does nothing, check its Info.plist in the
collection. `kc-tools` cuts a `<dict>` short after an XML comment, and the kext loses
`IOProviderClass` without any error.

## Common Panics

| What you see | Usual cause |
| --- | --- |
| A garbled panic message | Something stripped from the kernel's exports in the release build |
| `bad extent magic 0x0` from ext4 | A file's in-memory record reused after it was freed |
| A panic in `vm_compressor_init` | Early arm64 memory setup |
| `sleh_irq` with a NULL handler | The bootloader didn't turn off interrupts before starting the kernel |
| SIGILL in an arm64 program | Atomic instructions the CPU lacks. Build with `-mcpu=apple-a10` |
| SIGSEGV on the first thread-local variable | Thread-local storage was never set up |
| Everything stops while drivers are matching | A driver stuck in its `start()` function |
| `Unsupported CPU` before the console comes up | A CPU model missing from the kernel's table. Read the panic from memory with the QEMU monitor |
| `element modified after free` | Memory written after it was freed |

## When It Is the Filesystem

ext4 is our own code, and it has caused a long list of bugs that looked like
something else: launchd races, files going back to an old version after a reboot, and
what looked like memory damage. If a failure looks like damage and you can't pin it
down, boot `image-hfs`. It's the same system on Apple's HFS+ driver, so if the problem goes away, you've your
answer.
