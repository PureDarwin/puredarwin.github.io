# The CMake Tree

## Read This First

**Nix is the build system, and CMake is a tool that Nix drives. Running `cmake` on the
tree yourself isn't supported, and we don't plan to change that.**

From the outside a CMake tree looks like something you should be able to configure and
build, so here's why you can't.

Apple ships these components as Xcode projects, and getting them to build anywhere else
meant porting those projects to CMake. An Xcode project encodes a lot that CMake has no
direct equivalent for. The port forces some choices inside CMake that we wouldn't make
otherwise, and it leaves gaps that extra glue on the Nix side fills. The result works,
and it works reliably when Nix drives it, but the order, the toolchain wiring, the
generated headers and the install components all depend on the surrounding derivation
setting things up correctly.

So build with `nix build`. We won't act on bug reports against a hand-rolled `cmake`
configure. The dev shell lets you work on one component at a time, but it doesn't
produce a system.

`CODING_STYLE.md` asks for "the CMake build system only" in in-tree code. That means we
don't want a second build system in the tree. It doesn't make a bare CMake build a
supported product.

You'll still need to read and change this layer, so the rest of this page describes it.

## Top-Level Rules

`CMakeLists.txt` at the root sets a few rules up front:

* Only Clang is allowed. GCC is rejected, and so is the Xcode generator.
* `CMAKE_MACOSX_MIN_VERSION` is 26.5.
* Objective-C is turned on for the whole project, because libdispatch's `object.m`
  needs the frontend.

It then builds several symlink farms under `generated-headers/`, for `objc`,
`Foundation`, `mach-o`, `dlfcn` and `CoreFoundation`. They let in-tree sources use the
flat `<CoreFoundation/CFAvailability.h>` style of include that Apple frameworks expect,
without every consumer needing its own include paths.

## Configuration Switches

| Variable | Meaning |
| --- | --- |
| `PUREDARWIN_ARCH` | `x86_64`, `arm64`, `armv6` or `riscv64`. Falls back to `CMAKE_OSX_ARCHITECTURES` |
| `PUREDARWIN_ARM64_MACHINE_CONFIG` | The arm64 machine, for example `VIRT`, `T8010` or `BCM2837` |
| `PUREDARWIN_ARM32_MACHINE_CONFIG` | `BCM2835` |
| `PUREDARWIN_ENABLE_KERNEL` | Build `src/Kernel` |
| `PUREDARWIN_ENABLE_LIBRARIES` | Build `src/Libraries` |
| `PUREDARWIN_ENABLE_USERSPACE` | Build `src/Userspace` |
| `PUREDARWIN_PREBUILT_LIBSYSTEM_ROOT` | Use an already-built libSystem |
| `PUREDARWIN_ENABLE_SELFHOST_CCTOOLS` | Also build the self-hosting cctools variants |

## build.nix

`build.nix` is the one derivation that wraps this tree. Every in-tree component package
is that same derivation with different arguments:

| Argument | Effect |
| --- | --- |
| `buildTargets` | Which Ninja targets to build |
| `enableKernel`, `enableLibraries`, `enableUserspace`, `enableTools`, `enableProjects` | Which subtrees to configure |
| `installKernel`, `installKexts`, `installKextNames`, `installLibSystem`, `installBaseSystem`, `installXnuHeaders`, `installUserland`, `installUserlandTargetsOnly` | What ends up in `$out` |
| `xnuKernelConfig` | `RELEASE` or `DEVELOPMENT` |
| `puredarwinArch` | Selects the cross toolchain and target triple |
| `prebuiltLibSystem` | Reuse an existing libSystem build |
| `extraCmakeFlags` | Per-target flags, such as the machine config |

Some of a component's system files are put in place here too. The libSystem install
rule stages `dyld`, `launchd_real`, `notifyd` and its LaunchDaemon plist, along with the
guest C headers under `pd-guest-headers/`, which `image.nix` later moves to
`/usr/include`.

## The cmake/ Helper Modules

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
