# Host tools and toolchains

Cross-building Darwin from Linux needs tools that only exist in Apple's world. The
project builds them itself, from Apple's own sources where they exist.

## What tools/ builds

| Tool | Why it is needed |
| --- | --- |
| `cctools` | The real Mach-O binutils: `ld64`, `ar`, `as`, `otool`, `libmacho`, `libstuff`. LLD cannot produce everything Darwin needs |
| `mig` | The Mach Interface Generator, for Mach IPC stubs |
| `unifdef` | Used by the xnu header install rules |
| `dtrace_ctf` | The CTF tools the kernel build uses for type information |
| `xar` | Archive format used by parts of the build |
| `iig-selfhost` | Optional self-hosting `iig`, behind `PUREDARWIN_ENABLE_SELFHOST_CCTOOLS` |

`otool` deserves a note: the in-tree copy was extended to understand `MH_FILESET` and
`LC_FILESET_ENTRY`, so it can read a kernel collection. That is how you inspect a KC
without a Mac.

## The bootstrap sequence

There is a chicken-and-egg problem: the real linker is a Mach-O program that has to be
built and linked. It is resolved in three steps.

1. **`bootstrapCrossToolchain`** - clang with LLD. Good enough to link the linker.
2. **`native-ld`** - the real cctools `ld64`, built with the bootstrap toolchain.
3. **`darwinCrossToolchain`**, **`arm64CrossToolchain`**, **`armv6CrossToolchain`** -
   the toolchains everything else uses, wired to that real `ld64`.

Alongside them, `nativeMigcom` and `nativeUnifdef` are built once and cached, and are
what the dev shell exports as `NIX_MIGCOM_PATH` and `NIX_UNIFDEF_PATH`.

Target triples are `x86_64-apple-darwin20.4`, `arm64-apple-darwin20.4` and
`armv6-apple-darwin20.4`.

## Target settings

`nix/lib/target-info.nix` turns a triple into the settings a build system needs: the
architecture, meson's `cpu_family` (arm64 becomes `aarch64`), `cpu`, endianness, and the
clang target `<arch>-apple-macosx11.0`.

It carries a warning that is easy to trip over and expensive to debug: **an explicit
`-target` in a package's own flags overrides the wrapper's and silently produces objects
for the wrong architecture.** They link, they install, and they fail at runtime in ways
that look like something else entirely.

## Two architecture-specific notes

* Build arm64 with `-mcpu=apple-a10`. The default `macosx11.0` CPU emits LSE atomics,
  which fault on an A10.
* Compiler builtins come from a real cross-built LLVM compiler-rt, for both
  architectures. Watch out for hidden visibility when adding to it.
