# Roadmap

Where PureDarwin is going. The near goal is a release, and everything after that's
grouped by theme with no dates.

## The Next Release

The next release is about making what exists ready to hand to someone who isn't a
developer. That means fixing bugs, closing the gaps that make the system awkward to use,
and getting the main targets into a dependable state.

Where the targets stand today:

* x86_64 boots to the Argon desktop on real hardware, with AMD, Intel and NVIDIA GPU
  drivers. It's the release target.
* arm64 boots to a shell in QEMU. The Jetson TX1 has booted to the desktop, the Orange Pi Zero 3
  and Zero 4 have board support but haven't been tested on hardware yet, and more boards
  are being brought up.
* armv6 (the Raspberry Pi Zero) isn't part of the release.

See [Status](status.md) for the detail.

Work for the release happens on `main`, like everything else.

## After the Release

Each item says where it stands.

### Wi-Fi Through FreeBSD Drivers: In Progress

USB and PCIe Wi-Fi run on FreeBSD's drivers through PureDarwin's driver compatibility
layer. The Realtek RTL8192EU, RTL8852B and RTL8852C join WPA2 networks. Next are the
Ralink RT3572 on FreeBSD's driver, the RTL8811AU, and MediaTek's MT7921 and MT7922. The
aim is one Wi-Fi stack for every adapter, so the older OpenBSD-based one can go.

### FreeBSD Drivers on Every Architecture: In Progress

The FreeBSD network drivers build for arm64, and the Intel e1000 driver gets a network
address on the arm64 virtual machine. The aim is the same drivers on the arm64 boards,
then on riscv64.

### Multiple Displays: In Progress

A desktop stretched across several screens works in virtual machines, and the aim is the
same on real GPUs.

### A Bigger Boot Kernel Collection: Planned

The kernel collection the loader starts with is close to the 64 MiB the loader allows.
Drivers not needed to mount the root disk already go into a second collection, loaded
later. The aim is a loader that takes a larger collection, so this stops being a limit.

### Wine on Wayland: Planned

Wine uses its X11 driver on PureDarwin. Its Wayland driver runs, but the images are
built around X11. The aim is Wine as a full Wayland program, with X11 kept for
compatibility.

### Frameworks and Swift: In Progress

The built-in apps are AppKit apps, and the frameworks under them keep filling out. Swift
support has started and works in part. These frameworks are
what separate a Unix that boots from a Darwin that runs Darwin software.

### Newer Darwin Components: Planned

Move to newer versions of Apple's open source components where they work with the
project's own SDK.

### pdpkgs and Declarative Configuration: Planned

The long-term plan is to describe a PureDarwin system in one configuration file, the way
NixOS does, backed by a package collection called **pdpkgs**.

This can look like a detour. The other choice would be to invent a build system, which
means rebuilding cross-compilation from scratch. Cross-compilation is how the whole
system is produced, and we can't afford to break it. So we build on
Nix.

pdpkgs would be a package set that works like nixpkgs and falls back to nixpkgs wherever
it doesn't need to differ. Much of `nix/` would move into it over time.
`nix/image-contents.nix` is already a hand-made first draft of the idea.

This comes well after the release. It's months of work, and doing it first would mean
rebuilding the build while trying to stabilise the system it builds.

### Application Packaging with Disk Images: Planned

pdpkgs covers how the system is put together. Shipping an application to a user who
doesn't build from source is a separate question, and on Darwin the usual answer is a
disk image file, a DMG. The build already makes DMGs for the HFS+ image, so some of the
pieces exist.

### Building on a Mac: Planned

A Mac can build the kernel and libSystem, but not images, kernel collections or the
QEMU scripts. The aim is a Mac that can build the whole system.
