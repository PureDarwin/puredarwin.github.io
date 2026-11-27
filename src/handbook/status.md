# Status

What works today. This page changes often, and it covers facts while the
[Roadmap](roadmap.md) covers plans.

In the tables, **yes** means it works and **partial** means it works with limits or known
bugs. **no** means it's not there yet, and **-** means it doesn't apply to this target.

## Core System

| | x86_64 | arm64 virt | Pi Zero |
| --- | --- | --- | --- |
| Kernel builds | yes | yes | yes |
| Boots to a shell | yes | yes | not yet, reaches `dyld` |
| ext4 root | yes | yes | yes |
| launchd and XPC | yes | yes | not yet |
| Runs on real hardware | yes | - | partial |

On real arm64 hardware, the Jetson TX1 has booted to the desktop. The Orange Pi Zero 3
and Zero 4 have board support but haven't been tested on hardware yet, and other boards
are being brought up. See [Targets](targets.md). The Raspberry Pi 3 and the
iPad 6 booted on PureDarwin's older Darwin 20.5 tree only.

## Booting

| | Status |
| --- | --- |
| UEFI, 64-bit | yes, through xnu-loader |
| UEFI, 32-bit | partial, reaches the root mount in QEMU. The full image carries `BOOTIA32.EFI` next to `BOOTX64.EFI` |
| BIOS | yes, with the full `image` |
| Secure Boot | yes, with `image-sb`, built locally until the build server has a signing service, which has no date yet. It boots through a shim signed by Microsoft and a loader signed with the PureDarwin key, which you enroll once |
| Started by another bootloader | yes, the loader also starts from GRUB and from QEMU's `-kernel` |

## Filesystems

| | Status |
| --- | --- |
| ext4 | yes, with a journal. PureDarwin's own code, and in the past the source of subtle bugs |
| HFS+ | yes. `image-hfs` uses it to narrow down filesystem bugs, and so Mac users can open the image |
| APFS | yes, `image-apfs` boots with an APFS root |
| msdosfs | yes |

## Networking

| | Status |
| --- | --- |
| DHCP, DNS, TCP clients | yes, end to end through configd and IPConfiguration |
| sshd | yes |
| virtio-net | yes |
| Intel e1000 family (FreeBSD `em`) | yes, also on arm64 virt |
| Intel I225 and I226 (FreeBSD `igc`) | builds, not yet tested on hardware |
| Realtek RTL8111/8168 | yes |
| Realtek RTL8125 and RTL8126 (FreeBSD `rge`) | builds, not yet tested on hardware |
| Wi-Fi, Realtek RTL8852B and RTL8852C (FreeBSD `rtw89`) | yes |
| Wi-Fi, Realtek RTL8192EU USB (FreeBSD `rtwn`) | yes, joins WPA2 networks with DHCP |
| Wi-Fi, Ralink RT3572 USB | yes with the OpenBSD `run` driver. The FreeBSD `run` driver attaches and scans, joining is in progress |
| LAN78xx (Pi 3, older Darwin 20.5 tree) | partial |

The FreeBSD drivers run on `fbsdkpi`, PureDarwin's driver compatibility layer, which is
built on Haiku's FreeBSD compatibility code.
Wi-Fi is managed with `wifiutil` and from the menu bar.

## Graphics and Desktop (x86_64)

| | Status |
| --- | --- |
| Argon desktop | yes. The `neuswc` Wayland compositor with the menu bar, Dock, Files, Terminal, Settings and other built-in apps |
| AMD GPUs (amdgpu through drm-kmod) | yes on the RX 7800 XT and RX 7900 XTX, with `radeonsi` OpenGL |
| Intel GPUs (i915 through drm-kmod) | partial. Gen9 and Gemini Lake work, newer generations vary |
| NVIDIA GPUs (nouveau through drm-kmod) | yes on the Quadro 410, Quadro K620, GeForce 9500 GT and GeForce 7900 GS, with OpenGL |
| NVIDIA GPUs (NVIDIA's 580 driver) | yes on Maxwell, Pascal and Volta cards, with `image-nvidia` |
| Firmware framebuffer | yes, the fallback on every machine |
| virgl and Venus in VMs | yes |
| Mesa llvmpipe | yes |
| Multiple displays | partial, extended desktop in VMs, real GPUs in progress |
| Xorg | yes |
| GTK3 | yes |
| WebKitGTK | yes |

## Applications and Toolchains (x86_64)

| | Status |
| --- | --- |
| zsh, toybox, core userland | yes |
| Wine, GUI applications | yes |
| In-guest clang, cmake, ninja, meson | yes |
| In-guest rustc | yes |
| Nix inside PureDarwin | partial, a port builds derivations in the guest |
| Audio (Intel HDA) | yes |
| Input (PS/2, USB) | yes |

## Frameworks

| | Status |
| --- | --- |
| CoreFoundation | yes, Apple's portable CoreFoundation from its Swift releases |
| objc4 and libobjc | yes |
| libc++, libc++abi, libunwind | yes, LLVM 21 |
| Foundation | partial, grown from NeoDarwin's small first Foundation |
| AppKit | partial, started from Cocotron. The built-in apps are AppKit apps |
| Unmodified macOS apps | partial, a select few run, including Firefox |
| Security | yes, including `trustd` |
| SystemConfiguration | yes, configd runs and drives DHCP |
| DiskArbitration | yes |
| IOKit | yes, the real IOKit.framework built from IOKitUser |
| CoreGraphics, Onyx2D, CoreText | partial, started from Cocotron |
| Swift | partial |

Per-machine detail, including which Intel and AMD platforms have been tried, is in
[Running on Real Hardware](images/hardware.md).

## Known Issues

* The boot kernel collection is close to the 64 MiB limit the loader allows. New drivers
  that aren't needed to mount root go into the auxiliary kernel collection.
* A Mac can't build images, kernel collections or the QEMU scripts.
