# Source Tree

A map of the repository. The short version: `src/` is Darwin, `nix/` is everything
around it, and `tools/` is what the host needs to build Darwin at all.

## src/Kernel

`src/Kernel/xnu` is the kernel. Next to it are `libkmod`, `libfirehose_kernel`,
`fbsdkpi` and `src/Kernel/Extensions`, which holds the kexts. They fall into groups:

* **Platform**: `PDACPIPlatform` (built on uACPI), `AppleI386GenericPlatform`,
  `AppleAPIC`, `AppleI386PCI`, `IOACPIFamily`, `IOPCIFamily`, `PDEcamPCI`, and for ARM
  and RISC-V `PDArmPlatformExpert`, `PDArmPCI` and `PDRiscvPlatformExpert`.
* **Storage**: `IOStorageFamily`, `IOATAFamily` and `IOATABlockStorage`, `IONVMEFamily`,
  `RavynAHCIPort`, `IOVirtIOBlock`, the SD card drivers for the boards, and the optical
  families.
* **Filesystems**: `ext4` and `Ext4FileSystemDriver`, `hfs` with `HFSEncodings`, `apfs`
  and `ApfsFileSystemDriver`, `msdosfs`, `cd9660` and `AppleFileSystemDriver`.
* **Graphics**: `IOGraphicsFamily`, `IOGOPFramebuffer`, `IOVirtIOGPU`, `IONDRVSupport`,
  `PDIOSurface`, and the DRM drivers `PDDRMamdgpu`, `PDDRMi915` and `PDDRMnouveau` with
  `PDDRMDri`, which provides `/dev/dri`.
* **Network**: `IONetworkingFamily`, `IO80211Family`, `IOVirtIONet`, `PDE1000`,
  `PDRealtek8111`, `PDRalinkUSB`, and the FreeBSD drivers `PDFBSDem`, `PDFBSDigc`,
  `PDFBSDrge`, `PDFBSDrtw89`, `PDFBSDrtwn` and `PDFBSDrun`.
* **Input, USB and audio**: `IOHIDFamily`, `ApplePS2Controller`, `IOUSBFamily`,
  `RavynXHCIPort`, `IOAudioFamily` and `RavynHDAudio`.
* **Support**: `corecrypto`, `pthread`, `Sandbox`, `amfi`, `GTrace` and `GMetric`.

`fbsdkpi` is the FreeBSD compatibility layer. It builds on Haiku's FreeBSD network and
iflib compatibility code, adds FreeBSD's `net80211` and the LinuxKPI from FreeBSD, and
lets the `PDFBSD*` and `PDDRM*` kexts run FreeBSD and drm-kmod drivers unmodified.

The `corecrypto` kext builds from the MPL-2.0 fork in `external/corecrypto`. The old GPL
corecrypto in `src/Libraries/libSystem/corecrypto` is only compiled into Security.framework.
See [Licensing](licensing.md#corecrypto) if you redistribute PureDarwin.

The ext4 driver is worth calling out. Darwin has no ext4, and PureDarwin uses it as the
root filesystem, so it is entirely project code. It has been the source of a long list
of subtle bugs (see [Debugging](debugging.md)).

## src/Libraries

The userland foundation. Apple publishes some of it, and the rest is written here.

* **The core**: `libSystem` and its sub-libraries, `dyld`, `libcxx`, `libcxxabi`,
  `libunwind`, `llvm-libc`, `libdarwin`, `architecture`, `AvailabilityVersions`.
* **Objective-C and system libraries**: `objc4`, `CoreServices`, `IOKit`,
  `DiskArbitration`, `Security` with `libDER`, `SystemConfiguration` and
  `libSystemConfiguration`, `CommonCrypto`, `libsandbox`.
* **Services**: `XPC` (which includes launchd, launchctl and notifyd), `syslog`,
  `libsystem_trace`, `mDNSResponder`, `libresolv`, `bootp`, `eap8021x`, `ppp`.
* **Graphics support**: `libdrm`, `libgbm`, and the project's own `PDGOP`, `PDSurface`
  and `PDVirglShim`.

## src/Frameworks

The frameworks above the core: `CoreFoundation`, `Foundation`, `AppKit`, `Cocoa`,
`CoreGraphics` and `Onyx2D`, `CoreText`, `QuartzCore`, `CoreVideo`, `OpenGL`,
`IOSurface`, `WindowServer`, `ApplicationServices` and a growing list of others.

## src/Userspace

The commands and apps that make the system usable.

* **Commands**: `shell_cmds`, `text_cmds`, `system_cmds`, `diskdev_cmds`, `ps`, `ping`,
  `ioreg`, `sw_vers`, `netsetup`, `mdnsd`, `wifiutil`, `pdinstall`, `pdkext`,
  `pdpowerd`, the `ext4tool` and `ext4util` maintenance tools, and `tcc`.
* **The desktop**: `argon-session`, `MenuBar`, `Dock`, `Finder` (shown as Files),
  `Terminal`, `Settings`, `Calculator`, `SystemInformation`, `Installer` and
  `loginwindow`.
* **X11 support**: `startx` and the two Xorg drivers `xf86-video-puredarwingop` and
  `xf86-input-puredarwin`.

## src/ThirdParty

Upstream projects vendored because they needed real porting work: `neuswc` and `neuwld`
(the compositor and drawing library under Argon), `wayland`, `wayland-protocols`,
`wlroots` and `sway`.

## projects/

`libapfsrw`, the APFS read and write library the `apfs` kext shares.

## nix/

| Path | Contents |
| --- | --- |
| `nix/sources.nix` | Source tree pinning for in-tree components |
| `nix/image-contents.nix` | What goes in each image, and the QEMU runners |
| `nix/arm64.nix` | arm64 and armv6 kernels, kexts and userland |
| `nix/riscv64.nix` | riscv64 kernels, kexts and userland |
| `nix/lib/` | `kexts.nix` (every kext and which kernel collection lists it), `kc-kexts.nix`, `target-info.nix`, `secureboot.nix` |
| `nix/pkgs/` | Ported third-party packages |
| `nix/secureboot/` | The SBAT data and the keyless placeholder for Secure Boot images |

The ports under `nix/pkgs/` are grouped by what they are:

| Group | Contents |
| --- | --- |
| `base` | Build tools and core libraries: autotools, cmake, meson, ninja, perl, python, ncurses, openssl, curl, zsh, git |
| `apple` | Apple components and the test programs that exercise them |
| `x11` | The X server, its libraries and clients |
| `apps` | End-user software, the built-in apps, terminals and Wine |
| `gpu`, `mesa`, `wayland`, `gtk` | The graphics stack and the desktop libraries |
| `boot` | The shim for Secure Boot images |
| `toolchain` | Host and cross machinery: clang, LLVM, `native-ld`, the kernel collection builders, the SDK |

`ls nix/pkgs/<group>` is the current answer for any of them.

## tools/

Host-side build tools: `cctools`, `mig`, `unifdef`, `dtrace_ctf`, `xar`, `iig-selfhost`.
See [Host Tools and Toolchains](building/toolchains.md).

## cmake/

The CMake helper modules. See [The CMake Tree](building/cmake.md).
