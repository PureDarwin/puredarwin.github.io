# Getting Started

This page takes you from a clean Linux machine to a PureDarwin shell prompt in a VM.

## What you need

* **A Linux host with Nix and flakes enabled.** NixOS is what the project is developed
  on. Any Linux distribution with the Nix package manager works, as long as
  `experimental-features = nix-command flakes` is set.
* **Disk space.** A full image build pulls in a cross toolchain, LLVM, Mesa and a
  desktop stack. Budget 60 GB or more of Nix store.
* **A copy of `MacOSX11.3.sdk.tar.xz`.** This is Apple's SDK. It is proprietary and
  cannot be fetched or redistributed, so you have to supply it yourself. See
  [The Apple SDK requirement](building/apple-sdk.md) for why it is still needed and what
  the plan is for removing it.

macOS hosts are partially supported: the kernel and libSystem build, but the image,
kernel collection and runner outputs are Linux-only. Finishing that path is
[roadmap work](roadmap.md).

There is no supported way to build the tree with CMake directly. Nix is the interface.

## Register the SDK

Nix will refuse to build until the SDK tarball is in the store under its expected hash:

```
nix-store --add-fixed sha256 /path/to/MacOSX11.3.sdk.tar.xz
```

If you skip this, the first build fails with a message telling you to run exactly that
command.

## Build an image

Clone the repository and build the minimal image. It is the fastest way to get to a
prompt, and it is the image used for most boot testing:

```
git clone -b next https://github.com/PureDarwin/PureDarwin
cd PureDarwin
nix build .#image-minimal
```

`next` is where development happens; `main` holds the last frozen release. See
[Contributing](contributing.md) for the branch model.

The result is a raw disk image under `result/`. Other flavours (a full desktop image, a
Wayland-only image, debug images, arm64 images) are listed in
[Image flavours](images/flavours.md).

One thing to know before your first build: the flake is consumed as a `git+file://`
source, so **files you have not staged in git are invisible to the build**. If a change
of yours appears to have no effect, check `git status` first.

## Boot it

```
nix run .#vm
```

That starts QEMU with OVMF firmware, a q35 machine, 4 GB of RAM and the serial console
on your terminal. If you have KVM, `nix run .#kvm` is considerably faster and forwards
port 2222 to the guest's SSH.

A healthy boot prints kernel log lines, brings up the ext4 root, starts launchd, and
leaves you at a `#` prompt on the console. From there:

```
uname -a
sw_vers
ioreg -l | head
fastfetch
```

If it does not get that far, [Debugging](debugging.md) covers reading the boot, the
useful boot-args, and what the common failure signatures mean.

## Building single components

You do not have to build a whole image to work on one part of the system:

```
nix build .#kernel          # xnu for x86_64
nix build .#kexts           # the kext bundles
nix build .#libSystem
nix build .#userland
nix build .#zsh             # a cross-built guest package
```

`nix flake show` lists everything. The naming scheme is explained in
[The Nix flake](building/flake.md).
