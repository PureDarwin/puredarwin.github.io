# Handbook

![The PureDarwin logo](/img/handbook/pd-logo-bg000.jpg)

This handbook is for people who want to build PureDarwin, boot it and work on it. It
describes the system as it's today.

## What PureDarwin Is

Darwin is the open source core of Apple's operating systems. Apple used to release bootable Darwin, but it stopped in the mid 2000s (see
[Darwin's History](history.md)). Today it publishes its kernel, XNU, and a big part of
its Unix userland as source code only, and that isn't enough to boot a computer. There's no bootloader, there are few
drivers for ordinary PC hardware, and none of the graphical frameworks are there. Each
release leaves out a little more.

PureDarwin turns those releases into a system you can boot. We combine Apple's
releases with other open source projects, extend both where they fall short, and write
our own code where nothing suitable exists. The [Credits](credits.md) page says which is
which.

The result today:

* PureDarwin's kernel, based on Apple's current XNU release. The system reports itself as
  Darwin 26.5, so programs built for that version find what they expect.
* On x86_64 PCs, a desktop called Argon, with drivers for AMD, Intel and NVIDIA
  graphics cards.
* On arm64, a shell in QEMU and a desktop on the NVIDIA Jetson TX1, with more boards in
  bring-up.
* A set of ported software, such as Wayland, Mesa, GTK, Wine and a compiler toolchain.

PureDarwin is a community project, often called the informal successor to OpenDarwin. There's no formal link, but PureDarwin would not exist without the work
OpenDarwin left behind.

## Goals

Our goal hasn't changed since the project began. Make Darwin usable on its own, so
anyone can get it, understand it, change it, build it and share it. Document the parts Apple doesn't. We do it to learn, and because it's fun.

## What "Pure" Means

[Pure as in beer](https://en.wikipedia.org/wiki/Reinheitsgebot). PureDarwin is built
from components Apple has released as open source and from other open source software.
Nothing is taken from Apple's closed products. PureDarwin changes and extends the open
source code where the licences allow, and much of this handbook describes those changes.

## Hexley

The platypus you see around the site is [Hexley](../archive/about/Hexley.md), Darwin's
unofficial mascot. Jon Hooper drew him in 2000. He was the face of Darwin projects long
before PureDarwin existed, and he is staying.

## Getting the Code

Everything is in the [PureDarwin repository](https://github.com/PureDarwin/PureDarwin)
on GitHub. Work happens on the `main` branch.

## Where to Start

* [Getting Started](getting-started.md) takes you from a Linux machine to PureDarwin
  running in a virtual machine.
* [Building](building.md) explains how the build works.
* [Source Tree](source-tree.md) is a map of the repository.
* [Images and Boot](images.md) explains how a disk image is put together and how it
  boots.
* [Targets](targets.md) lists the machines PureDarwin runs on and how far each gets.
* [Porting Guide](porting.md) is for adding software.
* [Debugging](debugging.md) is for when it doesn't boot.
* [Credits](credits.md) says where each part of the system came from.
* [Licensing](licensing.md) and [Contributing](contributing.md) explain the rules for
  using and adding code.
* [Roadmap](roadmap.md) and [Status](status.md) cover where the project is going and
  what works today.

## Notice

PureDarwin and its website are independent and aren't affiliated with, endorsed by
or sponsored by Apple Inc. Apple, Macintosh, macOS and related trademarks and logos are
the property of Apple Inc., registered in the U.S. and other countries. Darwin is
licensed under the
[Apple Public Source License (APSL)](https://opensource.apple.com/apsl/). All other
trademarks are the property of their respective owners.
