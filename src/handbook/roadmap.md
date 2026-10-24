# Roadmap

Where PureDarwin is going. The near-term goal is a release. Everything after that is
grouped by theme and not scheduled.

## The Next Release

The next release is about making what already exists shippable: fixing bugs, closing
the gaps that make the system awkward to use, and getting the supported targets to a
state that can be handed to someone who is not a developer.

Where the targets stand today:

* x86_64 boots to the Argon desktop on real hardware, with AMD, Intel and NVIDIA GPU
  drivers. It is the release target.
* arm64 virt boots to a shell. The Jetson TX1, the Orange Pi Zero 3 and the Orange Pi
  Zero 4 boot on real hardware, and more arm64 boards are in bringup. The Raspberry Pi 3
  and the iPad 6 (T8010) booted on the 20.5-era tree only.
* armv6 (Pi Zero) is not part of the release.

See [Status](status.md) for the detail.

A release is a freeze. `main` is frozen, and development runs on `upstream-xnu-12377`. Release
cleanup goes there like everything else.

## After the Release

Each item is marked with where it stands.

### CPU Startup on Recent Intel Laptops: In Progress

Some Intel laptops from the Kaby Lake generation onward freeze when the kernel starts
the second CPU, so they only boot with `cpus=1`. Done means every CPU comes up on these
machines without a boot argument.

### Wi-Fi Through FreeBSD Drivers: In Progress

USB and PCIe Wi-Fi now run on FreeBSD's drivers through `fbsdkpi`. The Realtek
RTL8192EU and the RTL8852B and RTL8852C join WPA2 networks. Next are the Ralink
RT3572 on FreeBSD's `run` driver, the RTL8811AU, and MediaTek's MT7921 and MT7922. Done
means one Wi-Fi stack for every adapter, so the older OpenBSD-based stack can go.

### FreeBSD Drivers on Every Architecture: In Progress

The FreeBSD network drivers build for arm64 and the e1000 driver gets a DHCP lease on
arm64 virt. Done means the same drivers on the arm64 boards, then on riscv64.

### Multiple Displays: In Progress

An extended desktop works across several screens in VMs. Done means the same on real
GPUs.

### A Bigger Boot Kernel Collection: Planned

The boot kernel collection is close to the 64 MiB the loader allows. Drivers that are not
needed to mount root already go into the auxiliary collection. Done means the loader
takes a larger collection, so this stops being a constraint.

### Wayland for Wine: Planned

Wine uses the X11 driver on PureDarwin. `winewayland.drv` runs, but the images are built
around the X11 path. Done means Wine is a full Wayland client and X11 is the
compatibility path.

### Frameworks: Foundation, AppKit, CoreGraphics, Swift: In Progress

The built-in apps are AppKit apps, and the frameworks under them are filling out. Swift
is not there yet. This is the difference between a Unix that boots and a Darwin that can
run Darwin software.

### Later Darwin Components: Planned

Move to newer versions of Apple's open source components where that works with the
project's own SDK.

### pdpkgs and Declarative System Configuration: Planned

The long-term answer to how a PureDarwin system is described is a NixOS-style
`configuration.nix`, backed by a package repository called **pdpkgs**.

The reasoning is worth spelling out, because it looks like a detour. The alternative to
building on Nix is inventing a build system, and that means rebuilding cross-compilation
from scratch. Cross-compilation is the one thing this project cannot afford to break,
because it is how the whole system is produced. So the project builds on Nix.

pdpkgs is a nixpkgs-compatible package set that falls through to nixpkgs wherever it does
not need to differ. It is evaluated on the build host and produces a PureDarwin system,
the same way a NixOS image is built today. Much of what lives in `nix/` moves into it
over time, and `nix/image-contents.nix` is already a hand-rolled draft of the idea.

This lands after the release, and not by a small margin. It is months of work, and doing
it before a release would mean rebuilding the build while trying to stabilise the system
it builds.

### Application Packaging with DMGs: Planned

pdpkgs answers how the system is assembled. It does not answer how someone ships an
application to a user who is not building from source. The Darwin answer to that is a
disk image. The project already builds DMGs on the host side for the HFS+ image, so
parts of the machinery exist.

### Replace corecrypto: Blocked on an Alternative

The `corecrypto` kext and the CommonCrypto pieces on top of it are GPL. Nobody chose
that on the merits. It is what was available. Apple's own corecrypto cannot be used
here, and the current code descends from rafirafi's 2016 pdcrypto with tiny-AES128-C
adapted into it. That is what existed at the time, and it has kept the system booting
since.

The obvious question is why Apple's published CommonCrypto is not used. The answer is a
licensing gap. Only some of its files carry a license header, and there is no
repository-wide `LICENSE` file to cover the rest, so those files come with no grant at
all. Under the project's [provenance rules](contributing.md#provenance) that makes them
unusable. Code with no license is code we cannot touch, and Apple publishing it does not
change that. libDER has the same problem.

corecrypto is the exception to how the project handles GPL code elsewhere. It is a
separately licensed component in the default build, where such things are normally
[kept outside the tree](licensing.md#code-kept-outside-the-tree). It is in the tree
because nothing else does the job, and the system needs it to boot.

[NeoDarwinOS/corecrypto](https://github.com/NeoDarwinOS/corecrypto) is the intended
replacement, so this item waits on that work.

If you package or redistribute PureDarwin, this is the license you need to know about.

### Finish the Nix-on-Darwin Host Path: Planned

macOS hosts can build the kernel and libSystem, but images, kernel collections and the
runners are Linux only. Done means a macOS host is a full build machine.
