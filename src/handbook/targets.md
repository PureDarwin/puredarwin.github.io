# Targets

PureDarwin builds for x86_64, arm64, armv6 and riscv64. x86_64 is the primary target.
The others are at different stages of bringup.

| Target | Prefix | Boots to a shell | Display | Page |
| --- | --- | --- | --- | --- |
| x86_64 | none | Yes | The Argon desktop, with AMD, Intel and NVIDIA GPU drivers | [x86_64](targets/x86_64.md) |
| arm64 QEMU virt | `-arm64`, `-arm64-virt` | Yes | ramfb console, Wayland image available | [arm64 virt](targets/arm64-virt.md) |
| armv6 Pi Zero | `-arm32-bcm2835` | Not yet, reaches `dyld` | - | [Pi Zero](targets/armv6-bcm2835.md) |

## Boards in Bringup

These boot on real hardware but do not have a page of their own yet.

| Board | State |
| --- | --- |
| Orange Pi Zero 3 (Allwinner H618) | Boots, with Ethernet |
| Orange Pi Zero 4 (Allwinner A733) | Boots to a shell, from SD card or a USB stick |
| Luckfox Pico (Rockchip RV1103, Cortex-A7) | Boots to a shell over USB |
| NVIDIA Jetson TX1 | Boots, the nouveau GPU driver loads its firmware, GPU bringup in progress |
| riscv64 QEMU virt | Builds, bringup in progress |

## Earlier Targets

The Raspberry Pi 3 and the iPad 6 (T8010, through checkm8 and PongoOS) booted to a shell on
the 20.5-era tree. They have not been brought up on the current `upstream-xnu-12377` tree.
Their pages, [Pi 3](targets/arm64-bcm2837.md) and [T8010](targets/arm64-t8010.md),
describe that earlier work.

## How the Boards Boot

The arm64 boards boot xnu-loader as a Linux kernel image and read the device tree the
board's own bootloader passes in. Board-specific code is only needed where the device
tree cannot describe the hardware.

## Shared Rules

Every target uses the same launchd and userland. All of them except armv6 boot through a
kernel collection. armv6 uses a prelinked kernel. The differences are the platform
expert, the kext list and how the kernel gets loaded.

Most of the kernel and kext tree is shared between architectures, so ARM work can break
x86 without anyone noticing until an image fails to boot. **Build and boot an x86_64
image after touching shared XNU or kext code.** This is the most common way a working
tree stops working.
