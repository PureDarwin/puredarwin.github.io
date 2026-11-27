# Getting Started

This page takes you from a Linux machine to PureDarwin running in a virtual machine.

## What You Need

* **A Linux computer with Nix.** Nix is the package manager PureDarwin's build is
  written in. PureDarwin is developed on NixOS, but any Linux distribution with Nix
  works. Turn on flakes by setting
  `experimental-features = nix-command flakes` in your Nix configuration.
* **Disk space.** A full image build pulls in a cross compiler, LLVM, Mesa and a
  desktop. Plan for 60 GB or more.

You won't need any files from Apple. The build makes its own SDK, the set
of headers programs are compiled against, from open source headers. See
[The SDK](building/apple-sdk.md).

A Mac can build some parts, such as the kernel and libSystem, but not disk images. Only
Linux builds a whole system today.

## Build an Image

Get the code and build the minimal image. It's the quickest way to a prompt, and it's
the image used for most boot testing.

```
git clone https://github.com/PureDarwin/PureDarwin
cd PureDarwin
nix build .#image-minimal
```

The result is a raw disk image under `result/`. The other images, such as the desktop,
are listed in [Image Flavours](images/flavours.md).

One thing to know before your first build. Nix reads the repository through git, so
**a file you haven't added to git doesn't exist for the build**. If a change seems to
have no effect, run `git status` first.

## Boot It

```
nix run .#vm
```

This starts QEMU, a machine emulator, with UEFI firmware, 4 GB of memory and the serial
console in your terminal. If your computer has KVM, `nix run .#kvm` is much faster, and it also forwards port 2222 on your computer to the guest's SSH port.

A good boot prints kernel messages, starts every CPU, mounts the root filesystem, starts
launchd and leaves you at a `#` prompt. [What a Healthy Boot Looks
Like](images/hardware.md#what-a-healthy-boot-looks-like) lists each step and what it
means if a boot stops there. Once you've a prompt, try:

```
uname -a
sw_vers
ioreg -l | head
fastfetch
```

If it doesn't get that far, [Debugging](debugging.md) explains how to read the boot.

## Building One Part

You don't need to build a whole image to work on one part of the system. Disk images are the flake's packages, and everything else is grouped by kind:

```
nix build .#kernel.kernel          # the x86_64 kernel
nix build .#kernel.kexts           # its kernel extensions
nix build .#kc.default             # the kernel and extensions linked together
nix build .#pd.x86_64.libSystem    # one library
nix build .#pd.x86_64.zsh          # one ported program
nix build .#pd.arm64.zsh           # the same program for arm64
```

`nix flake show` lists everything. [The Nix Flake](building/flake.md) explains the
names.
