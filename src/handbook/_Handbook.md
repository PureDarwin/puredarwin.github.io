# Handbook

![The PureDarwin logo](/img/handbook/pd-logo-bg000.jpg)

This is the developer documentation for PureDarwin as it exists today. It is written for
people who want to build it, boot it and work on it.

## What PureDarwin Is

Darwin is the open source operating system Apple releases as the foundation of macOS. It
has never been a complete, bootable system on its own. Apple publishes the kernel and a
large amount of userland. The pieces that turn that into something you can boot have
always been missing, and more of them go missing with each release.

PureDarwin fills those gaps. Where Apple ships source, we build it. Where Apple ships
nothing, or stopped shipping years ago, we write our own: the bootloader, the ext4
filesystem driver, most of the drivers, a launchd and XPC current enough for the Darwin
version we target, and a long list of frameworks that otherwise exist only as headers.
On top of that sits a set of ported software (Wayland, Mesa, GTK, Wine, a compiler
toolchain and more), so the result is a system you can use day to day.

The kernel is XNU 12377, and the system identifies itself as version 26.5, build 25F74.
On x86_64 it boots to Argon, the PureDarwin desktop, with GPU drivers for AMD, Intel and
NVIDIA cards. It also boots on several arm64 machines, from QEMU to single board
computers such as the Jetson TX1 and the Orange Pi Zero 3 and Zero 4.

The project is a community effort, often described as the informal successor to
OpenDarwin. There is no formal relationship, but PureDarwin would not exist without the
work that project left behind.

## Goals

The goal has not changed since the project started. Make Darwin usable on its own, so
anyone can retrieve, understand, modify, build and distribute it, and document the parts
Apple does not. Why spend time on this? For learning, and for fun.

## What the "Pure" Means

[Pure as in beer](https://en.wikipedia.org/wiki/Reinheitsgebot). PureDarwin builds from
components Apple has released for use with Darwin, together with other open source
software. Nothing is lifted from macOS. The upstream code is not left untouched. We
modify and extend it wherever the licenses allow, and most of this handbook describes
those changes.

## Hexley

The platypus you will see around the site is [Hexley](../archive/about/Hexley.md),
Darwin's unofficial mascot, created by Jon Hooper in 2000. He has been the face of
Darwin projects far longer than PureDarwin has existed, and he is staying.

## Getting the Code

Everything lives in the
[PureDarwin repository](https://github.com/PureDarwin/PureDarwin) on GitHub. Development
happens on the `upstream-xnu-12377` branch. `main` is frozen. See
[Contributing](contributing.md) for the branch model.

## Where to Start

* [Getting Started](getting-started.md) takes you from a Linux machine to a booting VM.
* [Building](building.md) explains the flake, the CMake layer under it and the host
  toolchains.
* [Source Tree](source-tree.md) is the map of what lives where.
* [Images and Boot](images.md) covers how a disk image is assembled and what happens
  between firmware and the desktop.
* [Targets](targets.md) lists every machine PureDarwin builds for and how far each gets.
* [Porting Guide](porting.md) is for adding software, and for the traps that keep
  costing people days.
* [Debugging](debugging.md) is for when it does not boot.
* [Roadmap](roadmap.md) and [Status](status.md) cover where the project is going and
  what works today.

## Credits

There are too many people to thank, but some highlights:

* [Apple](https://github.com/apple), Inc. for releasing
  [Darwin](https://github.com/apple-oss-distributions) as open source
* David Elliott and the Chameleon team for their work on boot-132
* The xnu-dev team for their work on the XNU kernel
* Rafirafi for his work on Generic Platform kexts
* Mac OS Forge, the DarwinBuild project and the MacPorts project
* The OpenDarwin project, whose contributions PureDarwin still benefits from
* The FreeBSD and Haiku projects, whose drivers and compatibility layers run many of our
  devices
* [Probono](https://github.com/probonopd) for founding PureDarwin
* [csekel](https://github.com/csekel) for believing in PureDarwin and keeping it going
  when nobody else would. Rest in peace
* [vali0004](https://github.com/Vali0004) for pushing PureDarwin into a modern era
* Everyone else contributing to Darwin

## Notice

PureDarwin and the PureDarwin website are independent resources and are not affiliated
with, endorsed by or sponsored by Apple Inc. Apple, Macintosh, macOS and related
trademarks and logos are the property of Apple Inc., registered in the U.S. and other
countries. Darwin is licensed under the
[Apple Public Source License (APSL)](https://opensource.apple.com/apsl/). All other
trademarks are the property of their respective owners.
