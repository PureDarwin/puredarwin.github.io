# Targets

A target is a kind of machine PureDarwin is built for. PureDarwin builds for x86_64,
arm64, armv6 and riscv64. x86_64 is the main target. The others are at different stages
of bringup, which means getting a system to start on a new machine for the first time.

| Target | Boots to a shell | Display | Page |
| --- | --- | --- | --- |
| x86_64 PCs and laptops | Yes | The Argon desktop, with AMD, Intel and NVIDIA GPU drivers | [x86_64](targets/x86_64.md) |
| arm64, QEMU virt | Yes | A simple framebuffer, and a Wayland image | [arm64 virt](targets/arm64-virt.md) |
| armv6, Raspberry Pi Zero | Not yet, it reaches `dyld` | - | [Pi Zero](targets/armv6-bcm2835.md) |

## arm64 Hardware

These don't have a page of their own yet.

| Machine | State |
| --- | --- |
| NVIDIA Jetson TX1 | Has booted to the desktop. GPU work is still in progress |
| Lenovo ThinkPad X13s (Snapdragon 8cx Gen 3) | In bringup. Board support and the kernel build, and the USB driver starts on it |
| Orange Pi Zero 3 (Allwinner H618) | Board support is in, but it hasn't been tested on hardware yet. No Wi-Fi, and no GPU because its Mali driver is GPL |
| Orange Pi Zero 4 (Allwinner A733) | Board support is in, but it hasn't been tested on hardware yet. No Wi-Fi |
| Google Pixel 3a (Snapdragon 670) | In bringup. Board support, a serial console and an Android boot image build |
| Snapdragon 410 (MSM8916) USB stick | In bringup. Its storage works, and its GPU and Wi-Fi drivers are being written |
| Apple A9 (iPhone 6s) | Runs under the Inferno emulator |
| Apple M1 | Bringup in progress |
| riscv64, QEMU virt | Builds, bringup in progress |

## Earlier Targets

The Raspberry Pi 3 and the iPad 6 booted to a shell on PureDarwin's older Darwin 20.5
tree. Their pages, [Pi 3](targets/arm64-bcm2837.md) and [iPad 6](targets/arm64-t8010.md),
describe that work. Support for the iPad 6 is being brought over to the current tree.

## How the Boards Boot

The arm64 boards start xnu-loader as if it were a Linux kernel, from the board's own
bootloader. The loader reads the device tree, the description of the hardware the board
passes in. Board-specific code is only needed where the device tree can't describe the
hardware.

## What All Targets Share

Every target uses the same launchd and userland. All of them except armv6 boot through a
kernel collection, a single file that holds the kernel and its drivers. armv6 uses the
older prelinked kernel format. What differs is the platform driver, the list of kexts
and how the kernel is loaded.

Most of the kernel and kext code is shared between architectures. ARM work can break
x86_64 without anyone noticing until an image fails to boot. **After you touch shared
kernel or kext code, build and boot an x86_64 image.** This is the most common way a
working tree stops working.
