# Source Tree

A map of the repository. The short version: `src/` is Darwin, `nix/` is everything
around it, `tools/` is what the host needs to build Darwin at all.

## src/Kernel

`src/Kernel/xnu` is the kernel. Alongside it, `libkmod` and `libfirehose_kernel`, and
`src/Kernel/Extensions`, which holds the kexts. They fall into groups:

* **Platform**: `PDACPIPlatform` (built on uACPI), `AppleI386GenericPlatform`,
  `AppleAPIC`, `AppleI386PCI`, `IOACPIFamily`, `IOPCIFamily`, and the ARM equivalents
  `PDArmPlatformExpert`, `PDArmPCI`.
* **Storage**: `IOStorageFamily`, `IOATAFamily` and `IOATABlockStorage`, `IONVMEFamily`,
  `RavynAHCIPort`, `PDBcm2835SD`, plus the optical families.
* **Filesystems**: `ext4` and `Ext4FileSystemDriver` (the root filesystem on every
  target), `hfs` with `HFSEncodings`, `msdosfs`, `apfs`, `AppleFileSystemDriver`.
* **Graphics**: `IOGraphicsFamily`, `IOGOPFramebuffer`, `IOIntelFramebuffer`,
  `IOVirtIOGPU`, `IONDRVSupport`.
* **Input, USB, network, audio**: `IOHIDFamily`, `ApplePS2Controller`, `IOUSBFamily`
  with its EHCI/OHCI/UHCI plugins, `RavynXHCIPort`, `IONetworkingFamily`, `PDE1000`,
  `PDRealtek8111`, `IOVirtIONet`, `RavynHDAudio`.
* **Support**: `corecrypto`, `pthread`, `GTrace`, `GMetric`.

Note the licence on `corecrypto`: it and the CommonCrypto code above it are GPL, and
unlike the other GPL software the project uses, they are part of the default build. It
descends from rafirafi's 2016 pdcrypto because no alternative existed. Replacing it is
on the [roadmap](roadmap.md#replace-corecrypto---blocked-on-an-alternative) and matters
if you are redistributing PureDarwin.

The ext4 driver is worth calling out. Darwin has no ext4, and PureDarwin uses it as the
root filesystem, so it is entirely project code and has been the source of a long list
of subtle bugs (see [Debugging](debugging.md)).

## src/Libraries

The userland foundation. Apple publishes some of this; the rest is written here.

* **The core**: `libSystem` (and its many sub-libraries), `dyld`, `libcxx`, `libcxxabi`,
  `libunwind`, `llvm-libc`, `libdarwin`, `architecture`, `AvailabilityVersions`.
* **Objective-C and frameworks**: `objc4`, `CoreFoundation`, `Foundation`,
  `CoreServices`, `IOKit`, `DiskArbitration`, `Security` with `libDER`,
  `SystemConfiguration` and `libSystemConfiguration`, `ProtocolBuffer`,
  `SymptomReporter`, `WirelessDiagnostics`, `CommonCrypto`, `CrashReporterClient`.
* **Services**: `XPC` (which includes launchd, launchctl and notifyd), `syslog`,
  `libsystem_trace`, `mDNSResponder`, `libresolv`, `bootp`, `eap8021x`, `ppp`.
* **Graphics support**: `OpenGL`, `libdrm`, `libgbm`, and the project's own `PDGOP`,
  `PDSurface` and `PDVirglShim`.

## src/Frameworks

`CoreGraphics` and `Onyx2D`. Early, and on the [roadmap](roadmap.md) for real work.

## src/Userspace

The commands that make the system usable: `shell_cmds`, `text_cmds`, `system_cmds`,
`diskdev_cmds`, `ps`, `ping`, `ioreg`, `sw_vers`, `startx`, `netsetup`, `mdnsd`, the
`ext4tool` and `ext4util` maintenance utilities, `iomediacheck`, `mousemon`, `pcmplay`,
`tcc`, `fbdoom`, and the two Xorg drivers `xf86-video-puredarwingop` and
`xf86-input-puredarwin`.

## src/ThirdParty

Upstream projects vendored because they needed real porting work: `wayland`,
`wayland-protocols`, `wlroots`, `sway`.

## projects/

`libapfsrw`. The README there also lists a planned `libhfsrw` that does not exist yet.

## nix/

| Path | Contents |
| --- | --- |
| `nix/sources.nix` | Source tree pinning for in-tree components |
| `nix/image-contents.nix` | What goes in each image; the QEMU runners |
| `nix/arm64.nix` | arm64 and armv6 kernels, kexts, userland |
| `nix/xfce.nix` | The Xfce desktop package set |
| `nix/lib/` | `kc-kexts.nix`, `target-info.nix` |
| `nix/pkgs/` | Ported third-party packages |
| `nix/patches/` | Patches applied to host-side tooling |

The ports under `nix/pkgs/` are grouped by what they are:

| Group | Contents |
| --- | --- |
| `base` | Build tools and core libraries: autotools, cmake, meson, ninja, perl, python, ncurses, openssl, curl, zsh, git |
| `apple` | Apple frameworks and the test programs that exercise them: CoreFoundation, Foundation, IOKit, Security, libobjc, launchd, Onyx2D |
| `x11` | The X server, its libraries and clients |
| `apps` | End-user software: browsers, terminals, Wine |
| `gtk`, `xfce`, `wayland`, `mesa` | The desktop stacks and the graphics layer under them |
| `toolchain` | Host and cross machinery rather than ports: clang, LLVM, `native-ld`, the KC builders, the pinned SDK |

`ls nix/pkgs/<group>` is the current answer for any of them.

## tools/

Host-side build tools: `cctools`, `mig`, `unifdef`, `dtrace_ctf`, `xar`, `iig-selfhost`.
See [Host tools and toolchains](building/toolchains.md).

## cmake/

The CMake helper modules. See [The CMake tree](building/cmake.md).
