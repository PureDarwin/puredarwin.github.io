# Building

PureDarwin is built with Nix. Every artifact the project produces, from a single library
to a bootable disk image, is a flake output. The short version, on a Linux host:

```
nix-store --add-fixed sha256 /path/to/MacOSX11.3.sdk.tar.xz
nix build .#image-minimal
nix run .#vm
```

Under the Nix layer, the Darwin sources themselves are compiled by CMake, and both
layers rely on a cross toolchain the project builds for itself. There is also one
proprietary prerequisite that has not yet been designed out. Those four topics get a
page each:

* [The Nix flake](building/flake.md) - the outputs, how they are organised, and the dev
  shell.
* [The CMake tree](building/cmake.md) - what CMake does here, and why it is not a
  supported entry point on its own.
* [Host tools and toolchains](building/toolchains.md) - the cross compilers, the real
  `ld64`, and the bootstrap sequence that produces them.
* [The Apple SDK requirement](building/apple-sdk.md) - the one file you have to supply
  yourself.

## Two traps

**Untracked files are invisible.** The flake is evaluated from a `git+file://`
source, so a file you have not `git add`ed does not exist as far as the build is
concerned. The failure mode is not an error: the build quietly uses the old state, and
your change appears to do nothing. Stage before you build.

**CMake is not an entry point.** It is driven by Nix. The dev shell is for iterating on
a single component, not for producing a system, so read
[The CMake tree](building/cmake.md) before reaching for it.
