# Handbook

This is the developer documentation for PureDarwin as it exists today, written for
people who want to build it, boot it, and work on it.

## What PureDarwin is

Darwin is the open source operating system Apple releases as the foundation of macOS. It
has never been a complete, buildable system on its own: Apple publishes the kernel and a
large amount of userland, but the pieces that turn that into something you can boot have
always been missing, and more of them go missing with each release.

PureDarwin fills those gaps. Where Apple ships source, we build it. Where Apple ships
nothing, or stopped shipping years ago, we write a replacement: the bootloader, the ext4
filesystem driver, most of the drivers, a launchd and XPC current enough for the Darwin
version we target, and a long list of frameworks that exist as headers and nothing else.
On top of that sits a set of ported third-party software (X11, Wayland, Mesa, GTK, Xfce,
Wine, a compiler toolchain) so the result is a system you can actually use rather than a
kernel that reaches a prompt.

Today PureDarwin boots to a shell on four targets, with a fifth reaching userspace, runs
both an X11 and a Wayland desktop on x86_64, and cross-builds several hundred packages.

## How the build is layered

**Nix is the build system.** Everything is expressed as a flake output: components,
kernel collections, disk images, and the QEMU runners that boot them. `nix build
.#image-minimal` and `nix run .#vm` are the interface.

Underneath, the Darwin sources are built by CMake. That CMake exists because Apple's
Xcode projects had to be ported to it, and it is driven by Nix rather than used on its
own. Configuring the tree with `cmake` by hand is not a supported path; see
[The CMake tree](building/cmake.md) for what that means in practice.

## Where to start

* [Getting Started](getting-started.md) puts a booting VM in front of you.
* [Building](building.md) explains the flake, the CMake layer under it, the host
  toolchains, and the one proprietary prerequisite that is still required.
* [Source Tree](source-tree.md) is the map of what lives where.
* [Images and Boot](images.md) covers how a disk image is assembled and what happens
  between firmware and your shell prompt.
* [Targets](targets.md) is the per-machine status and how to build for each.
* [Porting Guide](porting.md) is for adding software, and the traps that keep costing
  people days.
* [Debugging](debugging.md) is for when it does not boot.
* [Roadmap](roadmap.md) and [Status](status.md) are where the project is going and what
  currently works.
