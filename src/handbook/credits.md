# Credits

Most of PureDarwin is other people's work, and we want to be clear about whose. This page
says where each big part of the system came from and what we've added to it. It's based
on the `NOTICE` file in the repository and the copyright notices in the source files,
and if the two ever disagree, the notice in the file wins.

We ask forks to say what they inherited and what they wrote, and this page is our own
record of that.

## How to Read This Page

Most parts of PureDarwin fall into one of three groups.

* Some parts were **taken from another project and changed**. The original authors keep their copyright
  and licence, and we make our changes in place, in the same files.
* Some **started from another project and have since grown**. The original code is still there,
  with a lot of new code beside it, and we name both below.
* Some were **written for PureDarwin**, and their files carry "The PureDarwin Project" in their
  copyright line.

A component can be in more than one group. AppKit is the clearest example.

## Apple's Darwin Releases

Darwin is the open source core of Apple's operating systems. Apple publishes it as
source code, one repository per component, at
[apple-oss-distributions](https://github.com/apple-oss-distributions). Most of it uses
the Apple Public Source License 2.0, and some of it carries code from NeXT Computer and
BSD.

We copy these sources into our tree, so that one tree builds the whole system, and make
our changes in place. These are the Apple components.

* **XNU**, Apple's kernel, brings together the Mach microkernel, a BSD layer and the
  IOKit driver framework. Apple releases it under the APSL 2.0, and the Mach and BSD files
  still carry their Carnegie Mellon and University of California notices. Our kernel is
  built from Apple's current XNU release. We first brought it in from an older release in
  2021 and have kept it up to date since, and most of its files are still exactly
  Apple's. What we've added are the ports and platform code under
  [What PureDarwin Wrote](#what-puredarwin-wrote).
* We use Apple's **core libraries**: Libc, libmalloc, libplatform, libpthread, libdispatch, the
  system call wrappers, objc4, dyld (see NeoDarwin below), CommonCrypto, Security with
  its trust daemon trustd, SystemConfiguration (configd), DiskArbitration, IOKitUser,
  libresolv, Libinfo, Libnotify, syslog and bootp.
* We use **the IOKit families** for storage, ATA, PCI, SCSI, networking, graphics, audio, HID,
  serial, ACPI and optical discs, along with drivers such as AppleIntelPIIXATA.
* Our **filesystems** include Apple's HFS+ and msdosfs, and cd9660, which we ported from an older XNU
  release that still had it.
* We use Apple's **commands and tools** such as DTrace, network_cmds (netstat and ping), system_cmds
  and msdos_cmds, and cctools and ld64 for building.
* **mDNSResponder** is Apple's service discovery daemon, which Apple releases under the
  Apache 2.0 licence.

`NOTICE` lists every Apple directory in the tree, the Apple release it came from and how
many of its files still match that release. That's the exact record, so we don't repeat
it here.

**launchd** is Apple's launchd from Mac OS X 10.9 (Mavericks), the last version Apple
released as open source. We've done a lot of work to bring it up to date with the rest
of the system, which is why only some of its files still match Apple's release.

Some Apple components were never open source. For those we either write our own or start
from another open source project, as the sections below describe.

## Cocotron

[Cocotron](https://github.com/cjwl/cocotron) is an open source implementation of
Apple's Cocoa frameworks, started by Christopher J. W. Lloyd and MIT-licensed. Many
people contributed to it over the years, including Dan Knapp and Johannes Fortmann,
whose names appear in the files we carry.

Several of our graphical frameworks started from Cocotron. They came to us in September
2026 through the copies [ravynOS](https://github.com/ravynsoft/ravynos) carries, so some
files carry ravynOS's notices too. The Cocotron notices are all still in place.

The counts below are the source files in each framework that still carry a Cocotron
copyright notice, out of its source files today. They show where the code came from, not how much work went into it, because a file keeps its original notice however much it has changed since:

| Framework | What it does | Cocotron files |
| --- | --- | --- |
| AppKit | Windows, menus, controls and the rest of the application toolkit | 402 of 615 |
| Onyx2D | Cocotron's 2D drawing engine, which CoreGraphics draws with | 101 of 196 |
| CoreGraphics | The 2D drawing interface applications call | 39 of 67 |
| CoreData | The object storage framework | 21 of 49 |
| CoreText | Text layout | 6 of 30 |
| Cocoa, ApplicationServices | Umbrella frameworks that include the others | small headers |

We got CoreData from ravynOS, which got it from Cocotron. In Cocotron it was mostly Dan
Knapp's work. His MIT notice is on 20 of its files and Christopher J. W. Lloyd's on one,
and its bundle information still names Cocotron.

### What We Added

Cocotron was written to run Cocoa programs on other operating systems, mostly Windows,
and was never meant to be the system framework of a Darwin system. Most of our work on
these frameworks has been about that change.

* We run them on our [Foundation](#foundation) and on Apple's portable
  [CoreFoundation](#corefoundation), in place of Cocotron's own.
* They draw through our display stack, which runs on [Wayland and neuswc](#wayland).
* We've filled in classes and methods Cocotron never had, so unmodified programs built for
  macOS can load and run. Firefox, in October 2026, was the first large one.
* We've added new files. About 77 AppKit files and 22 CoreText files carry our notice, and some of
  those sit beside Cocotron code in the same file.

Much of what these frameworks do today is still Cocotron's code.

## NeoDarwin

[NeoDarwin](https://github.com/NeoDarwinOS) is another project that builds on Darwin.
We use three things from it.

* <a id="foundation"></a>Our **Foundation** started from
  [NeoDarwin's Foundation](https://github.com/NeoDarwinOS/Foundation), which Samuel
  Zormeister wrote under the MPL 2.0. That first version was small, 14 source files and
  about 12 KB in all, with only 3 of them holding code. It had the start-up hook that
  sets up CoreFoundation, a basic NSObject and NSZone, and short headers for strings,
  ranges, values and errors. Nearly all of today's Foundation was written for
  PureDarwin on top of that start. It now has about 250 source files and 46,000 lines
  covering collections, strings, dates, run loops, threads, archiving, key-value coding,
  predicates, file handling and more. Cocotron's AppKit runs on it, and Samuel
  Zormeister's notice is still on the files that came from his version.
* Our **dyld** comes through NeoDarwin's dyld4linux, whose Apple base is close to an
  older Apple dyld release.
* We carry NeoDarwin's **corecrypto** as an MPL 2.0 fork in `external/corecrypto`.

## ravynOS

[ravynOS](https://github.com/ravynsoft/ravynos), led by Zoe Knox, is an operating system
that also carries Cocotron's frameworks and several Darwin drivers. This is what we use from ravynOS.

* We took the Cocotron frameworks listed above.
* We took **QuartzCore**, the layer and animation framework, and we've extended it so
  that many of its files now carry our notice.
* We took **RavynAHCIPort**, the SATA driver Zoe Knox wrote for ravynOS, and our changes
  to it went back to ravynOS.
* We use ravynOS's copies of Apple's IOUSBFamily, ApplePS2Controller, AppleAPIC and
  AppleI386PCI.

**RavynXHCIPort** went the other way. We wrote it for PureDarwin as a USB driver, using
the structure of RavynAHCIPort as a starting point, and then contributed it to ravynOS.
Its files keep ravynOS's notice for the code it was derived from.

**RavynHDAudio**, our Intel HD Audio driver, was written for PureDarwin from Intel's
public HD Audio specification and is shared with other projects.

## Darling

[Darling](https://www.darlinghq.org) runs macOS programs on Linux. We use two of its
projects for Metal, Apple's graphics programming interface.

* <a id="darling-metal"></a>**[Darling Metal](https://github.com/darlinghq/darling-metal)**
  is our Metal frontend, the Metal.framework that programs call. Its files are
  MPL-2.0, with a per-file SPDX line naming the Darling developers. The build fetches it
  at a pinned commit and applies our patch, `nix/pkgs/gpu/darling-metal-pd.patch`, which
  changes 40 of its headers and source files so it runs over our GPU path. Darling's
  notices stay in the files.
* We also use **[Indium](https://github.com/darlinghq/indium)**, which Ella Stanforth
  and the Darling developers released under 0BSD. We take its C++ interface headers and
  its tests, and our `indium-pd` puts that interface over airjitd (see below) in place
  of Indium's own Vulkan backend.

Our MetalKit, which gives Metal programs a window to draw into, is our own code.

## Compilers and Build Tools

Apple builds its own systems with these same tools, so they're easy to take for
granted. This is how we use them.

* <a id="llvm"></a>Clang, from **[LLVM](https://llvm.org)**, compiles the whole
  system. We also use LLVM's libc++, libc++abi and libunwind in `src/Libraries`,
  compiler-rt for the compiler's runtime helpers and parts of LLVM's libc in
  `src/Libraries/llvm-libc`. It all comes from LLVM 21's source in nixpkgs, under
  Apache 2.0 with the LLVM exception.
* <a id="cctools"></a>Our Mach-O linker, assembler, `ar`, `otool` and their libraries
  in `tools/cctools` are **Apple's cctools and ld64**, from Apple's open source releases
  under the APSL 2.0. We taught `otool` to read kernel collections.
* <a id="mig"></a>The Mach interface generator in `tools/mig` is **Apple's MIG**, also
  under the APSL 2.0.
* <a id="tapi"></a>ld64 reads `.tbd` text stubs with **libtapi**, Apple's library for
  them. We fetch it from Thomas Poechtrager's
  [apple-libtapi](https://github.com/tpoechtrager/apple-libtapi), which packages Apple's
  release for other systems under the University of Illinois/NCSA licence, and we've
  added RISC-V to its architecture table.
* <a id="swift"></a>We build Swift code with swift.org's prebuilt
  **[Swift](https://www.swift.org)** toolchain, run only on the build computer. The
  runtime and standard library that ship in PureDarwin are built from Apple's open
  source `swiftlang/swift` repository, under Apache 2.0 with the Runtime Library
  Exception. The Swift layers over our frameworks, in `src/Libraries/Swift*`, are our code.
* <a id="unifdef"></a>Two small BSD-licensed tools in `tools/` come from other authors:
  **unifdef** by Tony Finch and **xar** by Rob Braun.

## Other Projects

* <a id="freebsd"></a>Our driver compatibility layer uses **FreeBSD**'s LinuxKPI and
  other kernel code, and we use FreeBSD's libnv, all under BSD licences. Many network and
  Wi-Fi drivers run on that layer as FreeBSD drivers.
* <a id="haiku"></a>The same layer is built on **Haiku**'s MIT-licensed FreeBSD network
  compatibility code.
* <a id="drm-kmod"></a>Our AMD, Intel and NVIDIA (nouveau) drivers come from
  **drm-kmod**, FreeBSD's port of the Linux GPU drivers. They're GPL, and the build
  fetches them instead of keeping them in the tree.
* <a id="uacpi"></a>Our ACPI platform driver is built on **uACPI** by Daniil Tatianin,
  which is MIT-licensed.
* <a id="nextbsd"></a>Our XPC is built on libxpc from **NextBSD**, by iXsystems, which
  is BSD-2-Clause.
* <a id="corefoundation"></a>Our CoreFoundation is **Swift's CoreFoundation**, the portable one Apple publishes
  with Swift under the Apache 2.0 licence.
* <a id="openssl"></a>Security.framework uses **OpenSSL** for TLS and certificates. The
  Nix build builds it, and it isn't stored in the tree.
* <a id="wayland"></a>The display stack under the desktop is **Wayland,
  wayland-protocols, wlroots, sway, neuswc and neuwld**, each under its own licence.
* <a id="mesa"></a>OpenGL and Vulkan come from **Mesa**, which the build fetches.
* On NVIDIA cards that use it, we load **NVIDIA's 580 driver**, NVIDIA's own closed
  driver, unchanged, and we never redistribute it in changed form.
* <a id="nix"></a>Our build system is **Nix**, and most of the third-party software we
  port reuses the versions and sources in **nixpkgs**.
* **Wine, GTK, WebKitGTK** and the rest of the ported software each keep their own
  licence.

## What PureDarwin Wrote

Everything in this list was written for PureDarwin, and its files carry our notice.

* We wrote our own bootloader, **xnu-loader**, because Apple's isn't open source.
* We wrote **the kernel ports and platform code**: the arm64 board support, the
  platform drivers whose names start with PD (our ACPI one is built on
  [uACPI](#uacpi)), and the display and IOSurface drivers. Our GPU driver kexts host the
  [drm-kmod](#drm-kmod) drivers rather than replacing them.
* **fbsdkpi** is our layer for running FreeBSD and Linux drivers on XNU. It's built on
  [FreeBSD's LinuxKPI](#freebsd) and [Haiku's network compatibility code](#haiku).
* **The ext4 filesystem driver** is all ours, because Darwin has no ext4.
* **libDER** is ours. Apple's libDER sources carry copyright notices but no applicable
  redistribution licence, so we wrote our own implementation.
* **libsandbox, CoreServices** and many smaller libraries and frameworks are ours too.
* **The desktop** is ours, meaning the Argon session and its applications, including
  the menu bar, Dock, Files, Terminal and Settings. It runs on the
  [neuswc compositor and Wayland](#wayland).
* **elftrans**, which runs Linux programs on XNU, is ours.
* **airjitd** is our shader daemon. It compiles the GPU code Metal programs ship in
  Apple's shader format, AIR, so it runs on the GPU through Vulkan. We wrote it by
  clean-room engineering, from the observed behaviour of Apple's software. Its files
  carry our notice, and one includes Yann Collet's xxHash under its own BSD licence.
* **The Nix build** is ours, along with every image it produces. So is the way the
  build assembles its SDK, though the headers in it come from Apple's open source
  releases and the other projects on this page.
* Our work in the frameworks above is described in each of their sections.

## People

There are too many people to name everyone. Some of them:

* Apple, for releasing Darwin as open source.
* Christopher J. W. Lloyd and the Cocotron contributors.
* Zoe Knox and the ravynOS contributors.
* The NeoDarwin developers.
* The Darling developers.
* David Elliott and the Chameleon team, for their work on boot-132.
* The xnu-dev team, for their work on the XNU kernel.
* Rafirafi, for the generic platform kexts.
* Mac OS Forge, the DarwinBuild project and the MacPorts project.
* The OpenDarwin project, whose work we still benefit from.
* The FreeBSD and Haiku projects.
* [Probono](https://github.com/probonopd), who founded PureDarwin.
* [csekel](https://github.com/csekel), who kept PureDarwin going when nobody else would.
  Rest in peace.
* [Vali0004](https://github.com/Vali0004), who brought PureDarwin to current Darwin.
* Jon Hooper, who drew Hexley.
* Everyone else who has contributed to Darwin.

The git history of the [PureDarwin repository](https://github.com/PureDarwin/PureDarwin)
is the full record of who did what.
