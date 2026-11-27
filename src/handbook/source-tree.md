# Source Tree

A map of the repository. `src/` holds the system itself, `nix/` holds the
build around it, and `tools/` holds what the build computer needs to build Darwin at
all.

Many directories hold code that came from Apple or from other projects. The
[Credits](credits.md) page says where each came from, and `NOTICE` in the repository
lists the exact Apple release for each Apple directory.

## src/Kernel

`src/Kernel/xnu` is the kernel, PureDarwin's version of Apple's XNU. Beside it are
`libkmod`, `libfirehose_kernel`, `fbsdkpi` and `src/Kernel/Extensions`, which holds the
kernel extensions, or kexts. Kexts are Darwin's drivers and kernel modules, and they fall into groups:

* **Platform.** The code that describes the machine to the kernel. `PDACPIPlatform`
  (built on uACPI), `AppleI386GenericPlatform`, `AppleAPIC`, `AppleI386PCI`,
  `IOACPIFamily`, `IOPCIFamily`, `PDEcamPCI`, and for ARM and RISC-V
  `PDArmPlatformExpert`, `PDArmPCI` and `PDRiscvPlatformExpert`.
* **Storage.** `IOStorageFamily`, `IOATAFamily`, `IOATABlockStorage`, `IONVMEFamily`,
  `RavynAHCIPort`, `IOVirtIOBlock`, the SD card drivers for the boards, and the optical
  disc families.
* **Filesystems.** `ext4` and `Ext4FileSystemDriver`, `hfs` with `HFSEncodings`, `apfs`
  and `ApfsFileSystemDriver`, `msdosfs`, `cd9660` and `AppleFileSystemDriver`.
* **Graphics.** `IOGraphicsFamily`, `IOGOPFramebuffer`, `IOVirtIOGPU`, `IONDRVSupport`,
  `PDIOSurface`, and the GPU drivers `PDDRMamdgpu`, `PDDRMi915` and `PDDRMnouveau`
  with `PDDRMDri`, which provides `/dev/dri`. NVIDIA's own driver is loaded by
  `PDNVLoader`.
* **Network.** `IONetworkingFamily`, `IO80211Family`, `IOVirtIONet`, `PDE1000`,
  `PDRealtek8111`, `PDRalinkUSB`, and the FreeBSD drivers whose names start with
  `PDFBSD`.
* **Input, USB and audio.** `IOHIDFamily`, `ApplePS2Controller`, `IOUSBFamily`,
  `RavynXHCIPort`, `IOAudioFamily` and `RavynHDAudio`.
* **Support.** `corecrypto`, `pthread`, `Sandbox`, `amfi` and others.

`fbsdkpi` lets FreeBSD drivers, and the Linux GPU drivers FreeBSD carries, run on XNU
without changes. It's built on Haiku's FreeBSD compatibility code and adds FreeBSD's
Wi-Fi stack and its Linux compatibility layer. The kexts whose names start with
`PDFBSD` and `PDDRM` run on it.

The `corecrypto` kext is built from the MPL 2.0 fork in `external/corecrypto`, which
started from NeoDarwin's corecrypto.

The ext4 driver deserves a mention. Darwin has no ext4, and we use it as our root filesystem, so it's all our own code. It has caused a long list of subtle
bugs over time (see [Debugging](debugging.md)).

## src/Libraries

The base of the userland. Apple publishes some of it, and the rest is written here or
comes from other projects.

* **The core.** `libSystem` and its parts, `dyld` and `dyld4`, `libcxx`, `libcxxabi`,
  `libunwind`, `llvm-libc`, `libdarwin`, `architecture` and `AvailabilityVersions`.
* **Objective-C and system libraries.** `objc4`, `CoreServices`, `IOKit`,
  `DiskArbitration`, `Security` with `libDER`, `SystemConfiguration` and
  `libSystemConfiguration`, `CommonCrypto` and `libsandbox`.
* **Services.** `XPC` (which holds launchd, launchctl and notifyd), `syslog`,
  `libsystem_trace`, `mDNSResponder`, `libresolv`, `bootp`, `eap8021x` and `ppp`.
* **Graphics support.** `libdrm`, `libgbm`, and our own `PDGOP`, `PDSurface`
  and `PDVirglShim`.
* **Swift support.** `SwiftFoundation`, `SwiftFrameworks`, `SwiftOverlays` and
  `SwiftSupplemental`, PureDarwin's Swift layers over its frameworks.

## src/Frameworks

The frameworks that graphical programs use: `CoreFoundation`, `Foundation`, `AppKit`,
`Cocoa`, `CoreGraphics` and `Onyx2D`, `CoreText`, `CoreData`, `QuartzCore`,
`CoreVideo`, `OpenGL`, `IOSurface`, `WindowServer`, `ApplicationServices` and many
smaller ones. Several of them started from Cocotron or NeoDarwin, as [Credits](credits.md) explains.

## src/Userspace

The commands and applications.

* **Commands.** `shell_cmds`, `text_cmds`, `system_cmds`, `diskdev_cmds`, `ps`, `ping`,
  `netstat`, `ioreg`, `sw_vers`, `dtrace`, `netsetup`, `mdnsd`, `wifiutil`, `pdinstall`,
  `pdkext`, `pdpowerd`, the `ext4tool` and `ext4util` maintenance tools, and `tcc`.
* **The desktop.** `argon-session`, `MenuBar`, `Dock`, `Finder` (shown as Files),
  `Terminal`, `Settings`, `Calculator`, `SystemInformation`, `TextEditor`,
  `ImageViewer`, `Installer`, `loginwindow` and others.
* **X11 support.** `startx` and the two Xorg drivers `xf86-video-puredarwingop` and
  `xf86-input-puredarwin`.

## src/ThirdParty

Other projects kept in the tree because they needed real porting work: `neuswc` and
`neuwld` (the compositor and drawing library under the desktop), `wayland`,
`wayland-protocols`, `wlroots` and `sway`.

## projects/

`libapfsrw`, the APFS read and write library the `apfs` kext uses.

## external/

`corecrypto`, the MPL 2.0 fork described above.

## nix/

The build. [The Nix Flake](building/flake.md) describes the files. The ported software
is in `nix/pkgs/`, grouped by kind:

| Group | Contents |
| --- | --- |
| `base` | Build tools and core libraries, such as autotools, cmake, meson, perl, python, openssl, curl, zsh and git |
| `apple` | Apple components and the test programs for them |
| `x11` | The X server, its libraries and clients |
| `apps` | Applications, terminals and Wine |
| `gpu`, `mesa`, `wayland`, `gtk` | The graphics stack and desktop libraries |
| `boot` | The shim for Secure Boot images |
| `toolchain` | Compilers, LLVM, the linker, the kernel collection tools and the SDK |

`ls nix/pkgs/<group>` shows what's there today.

## tools/

Tools for the build computer: `cctools`, `mig`, `unifdef`, `dtrace_ctf`, `xar` and
`iig-selfhost`. See [Host Tools and Toolchains](building/toolchains.md).

## cmake/

The CMake helper modules. See [The CMake Tree](building/cmake.md).
