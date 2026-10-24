# Building

PureDarwin is built with Nix. Everything the project produces, from a single library to
a bootable disk image, is a flake output: components, kernel collections, disk images and
the QEMU runners that boot them. The short version, on a Linux host:

```
nix build .#image-minimal
nix run .#vm
```

Under the Nix layer, the Darwin sources are compiled with CMake. That CMake tree exists
because Apple's Xcode projects had to be ported to something, and Nix drives it.
Configuring it by hand is not supported. Both layers use cross toolchains the project
builds for itself, and an SDK the project assembles from open source headers. Those
topics get a page each:

* [The Nix Flake](building/flake.md) covers the outputs, how they are organised and the
  dev shell.
* [The CMake Tree](building/cmake.md) covers what CMake does here, and why it is not a
  supported entry point on its own.
* [Host Tools and Toolchains](building/toolchains.md) covers the cross compilers, the
  real `ld64` and the bootstrap sequence that produces them.
* [The SDK](building/apple-sdk.md) covers how the build gets its headers without
  Apple's proprietary SDK.

## Two Traps

**Untracked files are invisible.** The flake is read as a `git+file://` source, so a file
you have not added with `git add` does not exist as far as the build is concerned. The
build does not fail. It quietly uses the old state, and your change seems to do nothing.
Stage before you build.

**CMake is not an entry point.** Nix drives it. The dev shell is for working on a single
component. It does not produce a system. Read [The CMake Tree](building/cmake.md) before
reaching for it.
