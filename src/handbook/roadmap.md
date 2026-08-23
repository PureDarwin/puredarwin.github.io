# Roadmap

Where PureDarwin is going. The near-term goal is a release; everything after that is
grouped by theme rather than scheduled.

## PureDarwin 20.5.0

The current release target. 20.5.0 is about making what already exists shippable rather
than adding new capability: ironing out bugs, closing the gaps that make the system
awkward to use, and getting the supported targets to a state that can be handed to
someone who is not a developer.

Where the targets stand today:

* x86_64 boots to a shell, runs X11 and Wayland desktops, and is the release target.
* arm64 virt, arm64 bcm2837 (Pi 3) and arm64 t8010 (iPad 6) all boot to a shell.
* armv6 (Pi Zero) is not part of this release.

See [Status](status.md) for the detail.

Mechanically, a release is a freeze: development runs on `next`, and when the tree is
ready the branch is merged to `main` and frozen there. Cleanup work for 20.5.0 goes to
`next` like everything else.

## After 20.5.0

Each item is marked with where it currently stands.

### Wayland for Wine - planned

Wine currently uses the X11 driver on PureDarwin. `winewayland.drv` runs under sway, but
the X11 path is what the images are built around. Done means Wine is a first-class
Wayland client and X11 is the compatibility path rather than the default.

### A modern browser - in progress

WebKitGTK is being brought up. Most of the tree compiles against the project's libc++ 21
and the current blocker is gettext. Done means a browser on the image that can load the
modern web, not a demonstration that WebKit links.

### Xorg fixes and better alternatives - in progress

The X server works, with a project-written GOP video driver and input driver, but there
are outstanding bugs. Part of this is fixing them; part is moving to better options
where they exist, rather than carrying workarounds forever.

### More drivers and better hardware support - in progress

Broader hardware coverage: further NetBSD drivers ported across, wireless support, and
continued work on the storage, USB and graphics families. Real machines remain where the
interesting bugs are.

### Frameworks: Foundation, CoreGraphics, AppKit, Swift, Onyx2D - planned

The layers above CoreFoundation are the thinnest part of the system. Foundation needs
filling out, CoreGraphics and Onyx2D need real work, AppKit barely exists, and Swift is
not there yet. This is the difference between a Unix that boots and a Darwin that can
run Darwin software.

### Later Darwin components - planned

Move to newer versions of Apple's open source components where doing so is possible
without the closed-source SDK. This follows 20.5.0 deliberately: shipping a coherent
release first, then advancing the base.

### pdpkgs and declarative system configuration - planned

The long-term answer to "how is a PureDarwin system described" is a NixOS-style
`configuration.nix`, backed by a package repository called **pdpkgs**.

The reasoning is worth spelling out, because it looks like a detour. The alternative to
building on Nix is inventing a build system, and inventing one means rebuilding
cross-compilation from scratch. Cross-compilation is the single thing this project
cannot afford to break: it is how the whole system is produced. So the project banked on
Nix instead, following the path from Nix to nix-darwin and, in principle, on to Nix
running natively on PureDarwin.

That last step does not work. It has been tried. Nix on PureDarwin is not currently
possible, and the roadmap does not depend on it becoming possible.

pdpkgs is what to do instead. It is a nixpkgs-compliant package set that falls through
to nixpkgs wherever it does not need to differ, evaluated on the build host and
producing a PureDarwin system, in the same way a NixOS image is built today. Much of
what currently lives in `nix/` moves into it over time, and `nix/image-contents.nix` is
effectively a hand-rolled draft of the idea already.

This lands after 20.5.0, and not by a small margin. It is months of work, and doing it
before a release would mean rebuilding the build while trying to stabilise the thing
being built.

### Application packaging with DMGs - planned

pdpkgs answers how the system is assembled. It does not answer how somebody ships an
application to a user who is not building from source, and the Darwin-native answer to
that is a disk image. The project already builds DMGs on the host side for the HFS+
image target, so parts of the machinery exist.

### Replace corecrypto - blocked on an alternative

The `corecrypto` kext and the CommonCrypto pieces that sit on it are GPL. That is not a
choice anybody made on the merits; it is what was available. Apple's own corecrypto is
not usable here, and the current code descends from rafirafi's 2016 pdcrypto with
tiny-AES128-C adapted into it, which is what existed at the time and what has kept the
system booting since.

The obvious question is why Apple's own CommonCrypto is not used, given that it is
published. The answer is a licensing gap rather than a technical one. Only some of the
files carry a per-file licence header, and there is no repository-wide `LICENSE` file to
cover the rest, so the unheaded files come with no grant at all. Under the project's own
[provenance rules](contributing.md#provenance) that makes them unusable, and it is the
same reason the project cannot simply lift them: code with no licence is code we cannot
touch, and Apple publishing it does not change that. libDER arrived with the same
problem.

corecrypto is the exception to how the project handles this
elsewhere: an independently licensed substantial component folded
into the default distribution, where such things are normally kept
[external](building/apple-sdk.md#the-same-pattern-for-external-sources). It is in the
tree because nothing else does the job, and it is not optional at boot.

[NeoDarwinOS/corecrypto](https://github.com/NeoDarwinOS/corecrypto) is the intended
replacement, so this item is waiting on that work rather than on anything in this tree.

If you are packaging or redistributing PureDarwin, this is the licence you need to be
aware of.

### Remove the proprietary SDK dependency - planned

Building currently requires `MacOSX11.3.sdk.tar.xz`, which cannot be redistributed. Done
means a clean machine can build PureDarwin with nothing but the repository and Nix. See
[The Apple SDK requirement](building/apple-sdk.md).

### Finish the Nix-on-Darwin host path - planned

macOS hosts can build the kernel and libSystem, but images, kernel collections and the
runners are Linux-only. Done means a macOS host is a first-class build machine.
