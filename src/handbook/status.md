# Status

What works today. This page changes often. The [Roadmap](roadmap.md) covers intent, and
this page covers facts.

Legend: **yes** works, **partial** works with limits or known bugs, **no** not there
yet, **-** does not apply to this target.

## Core System

| | x86_64 | arm64 virt | Pi Zero |
| --- | --- | --- | --- |
| Kernel builds | yes | yes | yes |
| Boots to a shell | yes | yes | not yet, reaches `dyld` |
| ext4 root | yes | yes | yes |
| launchd and XPC | yes | yes | not yet |
| Runs on real hardware | yes | - | partial |

On real arm64 hardware, the Jetson TX1, the Orange Pi Zero 3, the Orange Pi Zero 4 and
other boards are in bringup. See [Targets](targets.md). The Raspberry Pi 3 and the iPad 6
(T8010) booted on the 20.5-era tree only.

## Booting

| | Status |
| --- | --- |
| UEFI, 64-bit | yes, through xnu-loader |
| UEFI, 32-bit (IA32 firmware) | partial, reaches the root mount in QEMU. The GPU images carry `BOOTIA32.EFI` next to `BOOTX64.EFI` |
| Legacy BIOS | yes, with the `-legacy` images |
| Secure Boot | yes, with the `-sb` images. They boot through a Microsoft-signed shim and a loader signed with the PureDarwin key, which you enroll once |
| Multiboot2 and Linux boot protocol | yes, the loader also boots from GRUB and from QEMU's `-kernel` |

## Filesystems

| | Status |
| --- | --- |
| ext4 | yes, with journalling. Project code, and historically the source of subtle bugs |
| HFS+ | yes. `image-hfs` uses it for bisection, and so macOS users can mount the image |
| APFS | yes, `image-apfs-minimal` boots with an APFS root |
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
| LAN78xx (Pi 3, 20.5-era tree) | partial |

The FreeBSD drivers run on `fbsdkpi`, a FreeBSD compatibility layer built on Haiku's.
Wi-Fi is managed with `wifiutil` and from the menu bar.

## Graphics and Desktop (x86_64)

| | Status |
| --- | --- |
| Argon desktop | yes. The `neuswc` Wayland compositor with the menu bar, Dock, Files, Terminal, Settings and other built-in apps |
| AMD GPUs (amdgpu through drm-kmod) | yes on the RX 7800 XT and RX 7900 XTX, with `radeonsi` OpenGL |
| Intel GPUs (i915 through drm-kmod) | partial. Gen9 and Gemini Lake work, newer generations vary |
| NVIDIA GPUs (nouveau through drm-kmod) | yes on the Quadro 410, Quadro K620, GeForce 9500 GT and GeForce 7900 GS, with OpenGL |
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
| CoreFoundation | yes, a real cross-built CF |
| objc4 and libobjc | yes |
| libc++, libc++abi, libunwind | yes, LLVM 21 |
| Foundation | partial |
| AppKit | partial, the built-in apps are AppKit apps |
| Unmodified macOS apps | partial, a select few run, including Firefox |
| Security | yes, apart from `trustd` |
| SystemConfiguration | yes, configd runs and drives DHCP |
| DiskArbitration | yes |
| IOKit | yes, the real IOKit.framework built from IOKitUser |
| CoreGraphics, Onyx2D, CoreText | partial |
| Swift | no |

Per-machine detail, including which Intel and AMD platforms have been tried, is in
[Running on Real Hardware](images/hardware.md).

## Known Issues

* Some Intel laptops from the Kaby Lake generation onward freeze when the kernel starts
  the second CPU. Booting with `cpus=1` works around it. This is being investigated.
* The boot kernel collection is close to the 64 MiB limit the loader allows. New drivers
  that are not needed to mount root go into the auxiliary kernel collection.
* `corecrypto` and CommonCrypto are GPL, and they are in the default build. See the
  [Roadmap](roadmap.md#replace-corecrypto-blocked-on-an-alternative).
* Security is missing `trustd`, so certificate trust evaluation through the framework is
  not available. TLS in ported software goes through GnuTLS and works.
* macOS hosts cannot build images, kernel collections or runners.
