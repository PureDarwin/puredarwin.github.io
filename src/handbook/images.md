# Images and Boot

A PureDarwin image is a raw disk file with partitions. It holds a small FAT partition
that the firmware reads, called the EFI system partition, and a root filesystem with the
system on it. Some images have more.

`image.nix` builds the image, and `nix/image-contents.nix` decides what goes into each kind
of image.

* [Image Flavours](images/flavours.md) lists every image and what it's for.
* [Boot Chain](images/boot-chain.md) follows a boot from the firmware to a prompt.
* [Kernel Collections](images/kernel-collections.md) explains how the kernel and its
  drivers are linked together.
* [Running in QEMU](images/running.md) covers the scripts that start a virtual machine.
* [Running on Real Hardware](images/hardware.md) covers what changes on a real computer.
* [Secure Boot](images/secure-boot.md) covers booting with Secure Boot turned on.

A typical x86_64 image looks like this:

```
GPT
+-- p1  EFI system partition (FAT)
|     \EFI\BOOT\BOOTX64.EFI      xnu-loader, the bootloader
|     \EFI\BOOT\boot-args.txt    boot arguments, read by the loader
|     the kernel collection
+-- p2  root filesystem (ext4, or HFS+ or APFS on some images)
      the base system, plus the extra software the flavour includes
```

On arm64 the loader is `BOOTAA64.EFI`. Some arm64 images have no root partition and load
the whole system into a RAM disk instead.

`image.nix` writes almost all of `/etc` when it builds the image. That includes
`passwd`, `master.passwd`, `group`, `hosts`, `fstab`, `resolv.conf`, `ttys` and the
shell start-up files. If an edit to one of those files in a running system doesn't
survive a rebuild, this is why. Change `image.nix` instead, and rebuild the image.
