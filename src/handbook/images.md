# Images and Boot

A PureDarwin image is a partitioned raw disk file: a FAT EFI system partition holding
the bootloader, a root filesystem, and on the full x86_64 images an APFS partition kept
around for driver testing.

`image.nix` builds it. `nix/image-contents.nix` decides what goes in it, and defines the
several flavours the project ships.

* [Image flavours](images/flavours.md) - every image package, its geometry and its baked
  boot-args.
* [Boot chain](images/boot-chain.md) - firmware to shell prompt, step by step.
* [Kernel collections](images/kernel-collections.md) - how the kernel and its kexts are
  linked together.
* [Running in QEMU](images/running.md) - the runner apps and their knobs.
* [Running on real hardware](images/hardware.md) - what changes off QEMU.

The shape of an image:

```
GPT
+-- p1  EFI system partition (FAT)
|     \EFI\BOOT\BOOTX64.EFI      xnu-loader
|     \EFI\BOOT\boot-args.txt    boot arguments, read by the loader
|     the kernel collection
+-- p2  root filesystem (ext4, or HFS+ on image-hfs)
|     the base system, plus whatever extra packages the flavour includes
+-- p3  APFS test partition (full images only)
```

On arm64 the EFI binary is `BOOTAA64.EFI`. Some arm64 targets boot a RAM disk instead of
a root partition; see [Image flavours](images/flavours.md).

Nearly all of `/etc` is written by `image.nix` at image build time: `passwd`,
`master.passwd`, `group`, `hosts`, `fstab`, `services`, `protocols`, `resolv.conf`,
`shells`, `ttys`, `profile`, `zshenv`, `zprofile` and `zshrc`, plus the fontconfig and
XDG environment defaults.

If you are wondering why an edit to a config file in the guest does not survive a
rebuild, this is why: change `image.nix`, not the image.
