# Getting Started

This page takes you from a Linux machine to PureDarwin running in a VM.

## What You Need

* **A Linux host with Nix and flakes enabled.** PureDarwin is developed on NixOS. Any
  Linux distribution with the Nix package manager works, as long as
  `experimental-features = nix-command flakes` is set.
* **Disk space.** A full image build pulls in a cross toolchain, LLVM, Mesa and a
  desktop stack. Budget 60 GB or more of Nix store.

That is all. Earlier versions needed a copy of Apple's proprietary macOS SDK. The build
now assembles its own SDK from open source headers, so a clean machine needs nothing but
the repository and Nix. See [The SDK](building/apple-sdk.md).

macOS hosts are partially supported. The kernel and libSystem build there, but images,
kernel collections and the QEMU runners are Linux only. Finishing that path is
[roadmap work](roadmap.md).

Nix is the interface. There is no supported way to build the tree with CMake directly.

## Build an Image

Clone the repository and build the minimal image. It is the fastest way to a prompt,
and it is the image used for most boot testing:

```
git clone -b upstream-xnu-12377 https://github.com/PureDarwin/PureDarwin
cd PureDarwin
nix build .#image-minimal
```

Development happens on `upstream-xnu-12377`. `main` is frozen. See
[Contributing](contributing.md) for the branch model.

The result is a raw disk image under `result/`. Other images, such as the GPU desktop
image, the Wayland image, debug images and the arm64 images, are listed in
[Image Flavours](images/flavours.md).

One thing to know before your first build. The flake is read as a `git+file://` source,
so **files you have not added to git are invisible to the build**. If a change seems to
have no effect, check `git status` first.

## Boot It

```
nix run .#vm
```

That starts QEMU with OVMF firmware, a q35 machine, 4 GB of RAM and the serial console
on your terminal. With KVM, `nix run .#kvm` is much faster and forwards port 2222 to the
guest's SSH.

A healthy boot prints kernel log lines, starts every CPU, mounts the ext4 root, starts
launchd and leaves you at a `#` prompt on the console. [What a Healthy Boot Looks
Like](images/hardware.md#what-a-healthy-boot-looks-like) lists each stage and what it means
when a boot stops at one. From there:

```
uname -a
sw_vers
ioreg -l | head
fastfetch
```

If it does not get that far, [Debugging](debugging.md) covers reading the boot, the
useful boot arguments and what the common failures look like.

## Building Single Components

You do not have to build a whole image to work on one part of the system:

```
nix build .#kernel          # xnu for x86_64
nix build .#kexts           # the kext bundles
nix build .#libSystem
nix build .#userland
nix build .#zsh             # a cross-built guest package
```

`nix flake show` lists everything. The naming scheme is explained in
[The Nix Flake](building/flake.md).
