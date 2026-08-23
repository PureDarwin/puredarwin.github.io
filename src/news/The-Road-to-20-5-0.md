# The Road to 20.5.0

August 23, 2026 - [Vali](https://github.com/Vali0004)

![PureDarwin running Xfce under Xwayland on sway, with the LunarG Vulkan cube on Mesa, Wine, and fastfetch reporting Darwin 20.5.0](/img/news/2026/news-cover-road-to-20-5-0-wide.jpg)

PureDarwin is preparing its first release in eight years, and the first one with a
graphical desktop since PureDarwin Xmas in 2007. This post covers where the system
actually is, what 20.5.0 needs before it ships, and two things that landed this week:
developer documentation, and a written contribution policy.

### Who is writing this

I am Vali. You may know me from the Discord.

I have worked on PureDarwin for three years, and I was one of
the first people to get it running properly on Linux. I wrote
[xnu-loader](https://github.com/PureDarwin/xnu-loader) and
[iig-tools](https://github.com/PureDarwin/iig-tools), along with a lot of the
surrounding code that turns a pile of Apple source into something that boots. Outside
this project I work on the [Xenon Emulator](https://github.com/xenon-emu/xenon).

I also contribute to [ravynOS](https://ravynos.com), and my time splits between porting
work over to them and reusing theirs. That exchange is not one-directional: we ship
kexts that came from ravynOS, and ravynOS ships kexts that came from us. Two small
projects working on the same difficult problem get further by sharing than by competing,
and I would rather spend the effort once.

One thing I am not, at least these days, is a designer. I am a full stack developer,
and design is a skill I have let go rusty. That has a visible consequence: the nice
artwork that a project like this deserves is mostly not going to be there, and what you
see is going to look like something built by someone optimising for whether it works.
The wireframes in the 2024 [A New Direction](/news/A-New-Direction.md) post are the kind
of thing I cannot produce on my own.

### How we got here

PureDarwin lost its leader last year. Cliff Sekel, InsaneDarwin, kept this project alive
when letting it quietly disappear would have been the easier choice, and
[we wrote about that in January](/news/Remembering-Cliff-Sekel.md). Everything below is
built on work he refused to abandon.

PureDarwin has existed since 2006, and carrying it forward meant dealing with a
repository that had accumulated twenty years of history, much of it referring to
approaches the project no longer takes. I hated doing it, but before modernising
anything I made a complete archive of the previous repository state at
[PureDarwin-archive](https://github.com/PureDarwin/PureDarwin-archive). Tyson Key
([vmlemon](https://github.com/vmlemon)) and Ferdinand Klinzer
([hideout](https://github.com/hideout)) were aware of the changes.

That archive was made from a full, non-shallow clone. I ran `git fsck` to recover
objects that were otherwise unreferenced, then pushed every ref with `--mirror`,
including pull request refs. The old history, branches and tags are all preserved, as
are the now-archived wiki and the surrounding repositories. Nothing was deleted or
purged; it was archived instead. Stale pull requests and issues in the main repository
were closed as part of the same cleanup.

We owe that much to everyone who has worked on PureDarwin over the years. The history is
preserved, and the project gets to move.

Active development happens on the `next` branch, and updates go out in the development
channel on Discord as they happen.

### Where the system is

PureDarwin boots to a shell on four targets:

- **x86_64**, on QEMU and on real hardware. This is the release target.
- **arm64 under QEMU virt**.
- **arm64 Raspberry Pi 3**.
- **arm64 T8010**, the iPad 6, reached through checkm8 and a modified PongoOS.

A fifth target, the ARMv6 Raspberry Pi Zero, is not there yet, but it is closer than it
sounds: the 32-bit kernel boots, mounts root and gets into userspace, where `dyld`
currently complains about pthreads.

On x86_64 that shell is the least interesting part. The system mounts an ext4 root
written from scratch for this project, gets a DHCP lease end to end, and runs a real
Xorg server on its own GOP framebuffer driver, with Mesa providing llvmpipe for OpenGL,
lavapipe for Vulkan, and virgl as the default renderer where the host offers it. There
is a Wayland stack as well: sway on wlroots, with Xwayland for X clients, and a
Wayland-only image that drops the X client stack entirely. Xfce runs. GTK3 runs. Wine
runs GUI applications.

Perhaps the best measure of how far this has come: clang, cmake, ninja, meson and rustc
all run inside PureDarwin itself. You can develop on it.

The last time PureDarwin had a graphical desktop was Xmas, back in 2007, and that one
leaned on binary blobs lifted from Mac OS X to fill in what Apple had not released. This
one does not. Every binary in the image is built from source. We still need Apple's SDK
to do the building, which is a real problem and one we intend to solve, but nothing
borrowed is shipped in the result.

A good deal of this is Apple's code. XNU is Apple's, and so is a large amount of the
userland. The work is in the gaps, and the gaps are wide. Apple has never released
`boot.efi`, so the bootloader is ours. Most of the drivers are ours. So is the ext4
driver the system boots from, since Darwin has no ext4 at all.

launchd is the instructive case. Apple did release it, and the last drop was perfectly
usable for its vintage, but that vintage is 10.9 Mavericks. We target Darwin 20, Big
Sur, and are preparing to move to Tahoe. A thirteen-year-old launchd does not bridge
that gap, so ours is a reimplementation. The same story repeats across the system: the
problem is rarely that Apple released nothing, it is that what was released stopped
where it stopped.

### The road to 20.5.0

20.5.0 is not about adding capability. It is about taking what exists and making it
something you can hand to somebody who is not a developer: ironing out bugs, closing the
gaps that make the system awkward, and getting the supported targets to a state worth
putting a version number on.

After that, the work is grouped rather than scheduled:

- Move Wine from the X11 driver to a proper Wayland driver.
- Update WebKitGTK to land a modern browser. Most of the tree compiles; gettext is the
  current blocker.
- Fix outstanding Xorg bugs, and move to better alternatives where they exist.
- More drivers and better hardware support: further NetBSD drivers ported across, and
  wireless.
- Improve Foundation, CoreGraphics, AppKit, Swift and Onyx2D. These layers are the
  thinnest part of the system, and they are the difference between a Unix that boots and
  a Darwin that can run Darwin software.
- Move to later Darwin components where that is possible without the closed-source SDK.
  Big Sur is what we target now; Tahoe is where we are heading.
- Describe a PureDarwin system with a NixOS-style `configuration.nix`, backed by a
  nixpkgs-compliant package set called pdpkgs that falls through to nixpkgs where it
  does not need to differ. The alternative is inventing a build system, and that means
  rebuilding cross-compilation, which is the one thing we cannot afford to break. Note
  that Nix running natively on PureDarwin is not on the list: I tried, it does not work,
  and none of this depends on it. This is months of work and it comes after 20.5.0.
- Ship applications as DMGs, so software can reach people who are not building from
  source.
- Remove the proprietary SDK requirement entirely.
- Finish the Nix-on-Darwin host path, so a Mac is a first-class build machine.

That last pair deserves honesty. Building PureDarwin today still requires a copy of
Apple's macOS 11.3 SDK, which we cannot redistribute and you have to supply yourself.
That is a real barrier to contribution and we intend to remove it. It is not a blocker
for 20.5.0, but it is on the list.

### Documentation

There is now a [Handbook](/handbook/_Handbook.html): how the build works, what lives
where in the source tree, how an image is assembled, what happens between firmware and
your shell prompt, per-target status, a porting guide, and a debugging guide.

Two pages are worth reading even if you never build anything. The
[Status](/handbook/status.html) page is an honest matrix of what works and what does
not, per target. The [Roadmap](/handbook/roadmap.html) page marks every item as planned,
in progress or done, so it stays a work queue rather than a wish list.

The porting guide contains a section called "Recurring traps", which is a list of the
mistakes that have each cost this project days. If you are going to work on PureDarwin,
read that one first.

### Contributing

There is now a written contribution policy, in `CONTRIBUTING.md`. The short version:

Development happens on `next`; each release is frozen onto `main`. New contributors
should work on Nix packages, and changes to existing kernel or system-library
implementations from first-time contributors are closed without review. That restriction
is about blast radius rather than gatekeeping: these components all depend on each
other, and a one-line change in libSystem can produce eight bugs in eight places that
look unrelated to what you touched. Additive libSystem integration work is exempt.

On AI-assisted code, the policy is neither a ban nor a shrug. Use whatever tools you
like. You are responsible for what you submit, there is no distinction at review between
code you wrote unaided and code a model produced, and you will be asked questions about
your patch. If you cannot answer them, it is closed. The same standard applies to a
patch copied from a forum post.

Provenance is the one place we are inflexible. Code whose licensing is unknown cannot be
accepted, and cannot be looked at. Clean-room work from datasheets, published standards
and hardware observation is not only permitted but is how a good deal of this project
got written.

### Getting involved

Grab an image and boot it. `nix build .#image-minimal` and `nix run .#vm` on a Linux
host with Nix, and the Handbook has the full version. If it does not boot on your
hardware, that is worth a bug report; real machines are where the interesting problems
still live.

If your skills are not in kernels, that is fine and possibly better. Packaging is the
most useful thing a new contributor can do, and it is where the restrictions in
`CONTRIBUTING.md` deliberately point people. Documentation, testing on hardware nobody
here owns, and design work are all wide open, that last one especially.

Come and say hello on [Discord](https://discord.gg/9kz8XXRRcT).
