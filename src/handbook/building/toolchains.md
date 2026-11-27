# Host Tools and Toolchains

Cross-building Darwin from Linux needs tools that normally only exist on a Mac. We build
them ourselves, from Apple's own sources where those exist.

## What tools/ Builds

| Tool | Why we need it |
| --- | --- |
| `cctools` | The real Mach-O binutils: `ld64`, `ar`, `as`, `otool`, `libmacho`, `libstuff`. LLD can't produce everything Darwin needs |
| `mig` | The Mach Interface Generator, for Mach IPC stubs |
| `unifdef` | Used by the xnu header install rules |
| `dtrace_ctf` | The CTF tools the kernel build uses for type information |
| `xar` | Archive format used by parts of the build |
| `iig-selfhost` | Optional self-hosting `iig`, behind `PUREDARWIN_ENABLE_SELFHOST_CCTOOLS` |

We extended the in-tree `otool` to understand `MH_FILESET` and `LC_FILESET_ENTRY`, so it
can read a kernel collection. That's how you look inside one without a Mac.

## The Bootstrap Sequence

The real linker is itself a Mach-O program that has to be built and linked, so there's a
chicken-and-egg problem. We get around it in three steps.

1. **`bootstrapCrossToolchain`** is clang with LLD, which is good enough to link the
   linker.
2. **`native-ld`** is the real cctools `ld64`, built with the bootstrap toolchain.
3. **`darwinCrossToolchain`**, **`arm64CrossToolchain`** and **`armv6CrossToolchain`**
   are the toolchains everything else uses, wired to that real `ld64`.

`nativeMigcom` and `nativeUnifdef` are built once beside them and cached. The dev shell
exports them as `NIX_MIGCOM_PATH` and `NIX_UNIFDEF_PATH`.

The toolchain triples are `x86_64-apple-darwin20.4`, `arm64-apple-darwin20.4`,
`armv6-apple-darwin20.4` and `riscv64-apple-darwin20.4`, and the deployment target comes
from the clang target below.

## Target Settings

`nix/lib/target-info.nix` turns a triple into the settings a build system needs: the
architecture, meson's `cpu_family` (arm64 becomes `aarch64`), `cpu`, endianness, and the
clang target `<arch>-apple-macosx26.5`.

It carries a warning that's easy to trip over and expensive to debug. **An explicit
`-target` in a package's own flags overrides the wrapper's and quietly produces objects
for the wrong architecture.** They link and install fine, and then fail at runtime in
ways that look like something else entirely.

## Two Architecture Notes

* Build arm64 with `-mcpu=apple-a10`, because the default arm64 CPU emits LSE atomics,
  which fault on an A10.
* Compiler builtins come from a real cross-built LLVM compiler-rt on both architectures.
  Watch out for hidden visibility when you add to it.
