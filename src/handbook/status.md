# Status

What works today, per target. This page changes often; the [Roadmap](roadmap.md) is
about intent, this is about facts.

Legend: **yes** works, **partial** works with limits or known bugs, **no** not there
yet, **-** not applicable to this target.

## Core system

| | x86_64 | arm64 virt | Pi 3 | T8010 | Pi Zero |
| --- | --- | --- | --- | --- | --- |
| Kernel builds | yes | yes | yes | yes | yes |
| Boots to a shell | yes | yes | yes | yes | not yet, reaches `dyld` |
| ext4 root | yes | yes | yes | yes (ramdisk) | yes |
| launchd and XPC | yes | yes | yes | yes | not yet, `dyld` fails on pthreads |
| Runs on real hardware | yes | - | yes | yes | partial |

## Filesystems

| | Status |
| --- | --- |
| ext4 | yes, with journalling and UBC coherence. Project code, and historically the source of subtle bugs |
| HFS+ | yes. `image-hfs` uses it for bisection, and so that macOS users can mount the image |
| msdosfs | yes |
| APFS | partial, read-oriented; the test partition exists for driver work |

## Networking

| | Status |
| --- | --- |
| DHCP | yes, end to end through IPConfiguration |
| DNS and TCP clients | yes, unicast DNS and curl in the guest |
| e1000, Realtek 8111, virtio-net | yes |
| LAN78xx (Pi 3) | partial |
| Wireless | no |
| sshd | yes |

## Graphics and desktop (x86_64)

| | Status |
| --- | --- |
| Framebuffer console | yes |
| Xorg | yes, on `IOGOPFramebuffer` via the project's own driver |
| Mesa llvmpipe | yes, GL 4.6 through GLX |
| Vulkan | yes, lavapipe (Mesa's software rasteriser). `vkcube` renders |
| virgl | yes, and the default renderer when available |
| Intel gen9 modesetting | partial, Skylake, Kaby Lake and Gemini Lake |
| Wayland (sway, wlroots) | yes, with Xwayland |
| Xfce | yes, on Xorg directly or as X11 clients under Xwayland on sway |
| GTK3 | yes |
| WebKitGTK | no, in progress |

On arm64 virt, Xorg can be started, but GL is currently broken on the reference machine.

## Applications and toolchains (x86_64)

| | Status |
| --- | --- |
| zsh, toybox, core userland | yes |
| Wine, GUI applications | yes on X11 |
| In-guest clang, cmake, ninja, meson | yes |
| In-guest rustc | yes |
| Audio (Intel HDA) | yes |
| Input (PS/2, USB) | yes |

## Frameworks

| | Status |
| --- | --- |
| CoreFoundation | yes, a real cross-built CF |
| objc4 and libobjc | yes |
| libc++ / libc++abi / libunwind | yes, LLVM 21 |
| Foundation | partial |
| Security | yes, apart from `trustd` |
| SystemConfiguration | yes, configd runs and drives DHCP |
| DiskArbitration | yes |
| IOKit | yes |
| CoreGraphics, Onyx2D | early |
| AppKit | no |
| Swift | no |

Per-machine detail, including which Intel and AMD platforms have actually been tried, is
in [Running on real hardware](images/hardware.md).

## Known issues worth knowing about

* `corecrypto` and CommonCrypto are GPL, and they are in the default build. See the
  [roadmap](roadmap.md#replace-corecrypto---blocked-on-an-alternative).
* Security is missing `trustd`, so certificate trust evaluation through the framework is
  not available. TLS in ported software goes through GnuTLS and is unaffected.
* `libm`'s `pow()` is inaccurate for fractional exponents.
* Building still requires Apple's proprietary SDK.
* macOS hosts cannot build images, kernel collections or runners.
