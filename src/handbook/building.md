# Building

PureDarwin is built with Nix. Everything we make, from one library to a
bootable disk image, is an output of the Nix flake in the repository. The short version,
on a Linux computer:

```
nix build .#image-minimal
nix run .#vm
```

There are two layers. Nix decides what to build, with which compiler, and how the pieces
fit into an image. Under it, the Darwin sources are compiled with CMake. Apple ships
these sources as Xcode projects, which only build on a Mac, so they had to be moved to
some other build system, and CMake is the one chosen. Nix drives CMake, and running CMake by hand isn't supported.

Both layers use cross compilers we build ourselves, and an SDK we put together
from open source headers. Each of these has its own page:

* [The Nix Flake](building/flake.md) explains the outputs and how they are named.
* [The CMake Tree](building/cmake.md) explains what CMake does here, and why it's not
  an entry point of its own.
* [Host Tools and Toolchains](building/toolchains.md) explains the cross compilers, the
  Mach-O linker and the order they are built in.
* [The SDK](building/apple-sdk.md) explains how the build gets its headers without
  Apple's SDK.

## Two Things That Catch People Out

**Files you haven't added to git are invisible.** Nix reads the repository through git.
The build quietly uses the last state git knows about, so a change in a file you've
not added with `git add` seems to do nothing. Add your files before you build.

**Run CMake only through Nix.** The development shell from `nix develop` is for working
on one component at a time. Read
[The CMake Tree](building/cmake.md) before you reach for it.
