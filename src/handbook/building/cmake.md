# The CMake tree

## Support statement, first

**Nix is the build system. CMake is a tool Nix drives, not an independent source target.
Building the tree by invoking `cmake` yourself is largely unsupported, and it is going
to stay that way.**

The reason is worth stating plainly, because from the outside a CMake tree looks like
something you should be able to configure and build.

Apple ships these components as Xcode projects. Getting them to build anywhere else
meant porting those projects to CMake. An Xcode project encodes a great deal that CMake
has no direct equivalent for, so the port forces choices inside CMake that are
undesirable on their own terms, and it leaves gaps that are filled with extra glue on
the Nix side. The result works, and it works reliably when Nix drives it, but the
dependency graph is fragile: order, toolchain wiring, generated headers and install
components all depend on the surrounding derivation setting things up correctly.

So: build with `nix build`. Bug reports against a hand-rolled `cmake` configure will not
be actioned. The dev shell exists so you can iterate on one component while you are
working on it, not so you can produce a system.

Note that `CODING_STYLE.md` requires "the CMake build system only" for in-tree code.
That rule means no second build system in the tree. It does not mean a bare CMake build
is a supported product.

The rest of this page documents the layer, because you will need to read and modify it.

## Top-level rules

`CMakeLists.txt` at the root enforces a few things up front:

* Clang only. GCC is rejected, and so is the Xcode generator.
* `CMAKE_MACOSX_MIN_VERSION` is 11.0.
* Objective-C is enabled project-wide, because libdispatch's `object.m` needs the
  frontend.

It then builds several symlink farms under `generated-headers/`, for `objc`,
`Foundation`, `mach-o`, `dlfcn` and `CoreFoundation`. These exist so that in-tree
sources can use the flat `<CoreFoundation/CFAvailability.h>` style include that Apple
frameworks expect, without every consumer needing bespoke include paths.

## Configuration switches

| Variable | Meaning |
| --- | --- |
| `PUREDARWIN_ARCH` | `x86_64`, `arm64` or `armv6`. Falls back to `CMAKE_OSX_ARCHITECTURES` |
| `PUREDARWIN_ARM64_MACHINE_CONFIG` | `VIRT`, `T8010` or `BCM2837` |
| `PUREDARWIN_ARM32_MACHINE_CONFIG` | `BCM2835` |
| `PUREDARWIN_ENABLE_KERNEL` | Build `src/Kernel` |
| `PUREDARWIN_ENABLE_LIBRARIES` | Build `src/Libraries` |
| `PUREDARWIN_ENABLE_USERSPACE` | Build `src/Userspace` |
| `PUREDARWIN_PREBUILT_LIBSYSTEM_ROOT` | Use an already-built libSystem instead of building one |
| `PUREDARWIN_ENABLE_SELFHOST_CCTOOLS` | Also build the self-hosting cctools variants |

## build.nix

`build.nix` is the single derivation that wraps this tree. Every in-tree component
package is the same derivation with different arguments:

| Argument | Effect |
| --- | --- |
| `buildTargets` | Which Ninja targets to build |
| `enableKernel`, `enableLibraries`, `enableUserspace`, `enableTools`, `enableProjects` | Which subtrees to configure |
| `installKernel`, `installKexts`, `installKextNames`, `installLibSystem`, `installBaseSystem`, `installXnuHeaders`, `installUserland`, `installUserlandTargetsOnly` | What ends up in `$out` |
| `xnuKernelConfig` | `RELEASE` or `DEVELOPMENT` |
| `puredarwinArch` | Selects the cross toolchain and target triple |
| `prebuiltLibSystem` | Reuse a libSystem build rather than rebuilding it |
| `extraCmakeFlags` | Per-target flags, such as the machine config |

This is also where the guest's `/etc`-adjacent bits of a component land: the libSystem
install rule stages `dyld`, `launchd_real`, `notifyd` and its LaunchDaemon plist, and
the guest C headers under `pd-guest-headers/`, which `image.nix` later moves to
`/usr/include`.

## The cmake/ helper modules

| Module | What it does |
| --- | --- |
| `kext.cmake` | Builds a kext bundle: Info.plist, the Mach-O kmod, the bundle layout |
| `mig.cmake` | Runs MIG to generate Mach IPC stubs |
| `iig.cmake` | Runs `iig` for IOKit interface definitions |
| `crosscompile.cmake` | Cross-compilation plumbing |
| `nix-toolchain.cmake` | The toolchain file the Nix derivations and dev shell point at |
| `prebuilt_libsystem.cmake` | Wires an external libSystem in place of building one |
| `circular.cmake` | Handles the circular dependencies between libSystem components |
| `install_helpers.cmake`, `bundle_resources.cmake`, `asm.cmake`, `suppress_warnings.cmake` | Supporting utilities |
