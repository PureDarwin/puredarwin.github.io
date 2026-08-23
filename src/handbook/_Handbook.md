# Handbook

![The PureDarwin logo](/img/handbook/pd-logo-bg000.jpg)

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

The project is a community effort, often described as the informal successor to
OpenDarwin. There is no formal relationship, but PureDarwin would not exist without the
work that project left behind.

## Goals

The goal has not changed since the project started: make Darwin usable on its own, by
enabling anyone to retrieve, understand, modify, build, and distribute it, and by
documenting the parts Apple does not. Why spend time on this? For learning and for fun.

## What the "Pure" means

[Pure as in beer](https://en.wikipedia.org/wiki/Reinheitsgebot). PureDarwin builds only
from components Apple has released for use with Darwin, together with other open source
software - collectively, upstream code. Nothing is lifted from macOS. That does not mean
the upstream code is left untouched: we modify and extend it wherever the licenses
allow, and most of this handbook describes exactly those modifications.

## Hexley

The platypus you will see around the site is [Hexley](../archive/about/Hexley.md),
Darwin's unofficial mascot, created by Jon Hooper in 2000. He has been the face of
Darwin projects far longer than PureDarwin has existed, and he is not going anywhere.

## Getting the code

Everything lives in the
[PureDarwin repository](https://github.com/PureDarwin/PureDarwin) on GitHub. Development
happens on the `next` branch; `main` holds the last frozen release. See
[Contributing](contributing.md) for the branch model.

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

## Credits

There are too many to thank, but some highlights:

* [Apple](https://github.com/apple), Inc. for releasing
  [Darwin](https://github.com/apple-oss-distributions) as open source
* David Elliott and the Chameleon team for their work on boot-132
* The xnu-dev team for their work on the XNU kernel
* Rafirafi for his work on Generic Platform kexts
* Mac OS Forge, the DarwinBuild project, and the MacPorts project
* The OpenDarwin project, whose contributions PureDarwin still benefits from
* [Probono](https://github.com/probonopd) for founding PureDarwin
* [csekel](https://github.com/csekel) for believing and keeping PureDarwin going when nobody would. Rest in Peace
* [vali0004](https://github.com/Vali0004) for pushing PureDarwin into a modern era
* Everyone else contributing to Darwin

## Notice

PureDarwin and the PureDarwin website are independent resources and are not affiliated
with, endorsed by, or sponsored by Apple Inc. Apple, Macintosh, macOS, and related
trademarks and logos are the property of Apple Inc., registered in the U.S. and other
countries. Darwin is licensed under the
[Apple Public Source License (APSL)](https://opensource.apple.com/apsl/). All other
trademarks are the property of their respective owners.
