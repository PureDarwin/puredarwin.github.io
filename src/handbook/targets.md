# Targets

PureDarwin builds for five machine targets. x86_64 is the primary one; the rest are at
varying stages of bringup, and all but the Pi Zero reach a shell.

| Target | Prefix | Boots to a shell | Display | Page |
| --- | --- | --- | --- | --- |
| x86_64 | none | Yes | Xorg and Wayland, llvmpipe and virgl | [x86_64](targets/x86_64.md) |
| arm64 QEMU virt | `-arm64`, `-arm64-virt` | Yes | ramfb console; Xorg starts, GL currently broken | [arm64 virt](targets/arm64-virt.md) |
| arm64 Raspberry Pi 3 | `-arm64-bcm2837` | Yes | Framebuffer console | [Pi 3](targets/arm64-bcm2837.md) |
| arm64 T8010 (iPad 6) | `-arm64-t8010` | Yes | On-screen console, framebuffer inherited from iBoot | [T8010](targets/arm64-t8010.md) |
| armv6 Pi Zero | `-arm32-bcm2835` | Not yet, reaches `dyld` | - | [Pi Zero](targets/armv6-bcm2835.md) |

All of them use ext4 as the root filesystem, boot through a kernel collection (except
armv6, which uses a prelinked kernel), and run the same launchd and userland. The
differences are the platform expert, the kext list, and how the kernel gets loaded.

Most of the kernel and kext tree is architecture-independent, which means ARM work
regularly breaks x86 without anybody noticing until an image fails to boot. **Run an
x86_64 regression build after touching shared XNU or kext code.** This is the single
most common way a working tree stops working.
