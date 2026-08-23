# Building

PureDarwin is built with Nix. Every artifact the project produces, from a single library
to a bootable disk image, is a flake output: components, kernel collections, disk
images, and the QEMU runners that boot them. The short version, on a Linux host:

```
nix-store --add-fixed sha256 /path/to/MacOSX11.3.sdk.tar.xz
nix build .#image-minimal
nix run .#vm
```

Under the Nix layer, the Darwin sources themselves are compiled by CMake. That CMake
tree exists because Apple's Xcode projects had to be ported to it, and it is driven by
Nix rather than used on its own; configuring it by hand is not a supported path. Both
layers rely on a cross toolchain the project builds for itself, and there is one
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

Two things are worth learning before any of that. **Untracked files are invisible**: the
flake is evaluated from a `git+file://` source, so a new file that has not been `git
add`ed does not exist as far as the build is concerned, and the failure mode is a build
that quietly uses the old state. And **do not guess at the CMake layer**: it is driven
by Nix, so if you want to iterate on a component quickly, use the dev shell and read
[The CMake tree](building/cmake.md) first to know what that shell can and cannot give
you.
