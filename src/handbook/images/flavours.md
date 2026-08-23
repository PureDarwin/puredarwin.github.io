# Image flavours

Every image is the same `image.nix` derivation with different contents and geometry.
Sizes are megabytes.

## x86_64

| Package | File | ESP | Root | Notes |
| --- | --- | --- | --- | --- |
| `image` | `puredarwin.img` | 64 | 6144 | The full system: X11, Wayland, Xfce, Wine, toolchains |
| `image-debug` | `puredarwin.img` | 64 | 6144 | Same, built against the debug kernel |
| `image-stripped` | `puredarwin-stripped.img` | 64 | 6144 | Base system plus a small library and test set |
| `image-wayland` | `puredarwin-wayland.img` | 64 | 6144 | Wayland only: no X11 clients, no Xfce, sway and GTK built without X |
| `image-minimal` | `puredarwin-minimal.img` | 60 | 200 | The usual boot-test image |
| `image-minimal-debug` | `puredarwin-minimal-debug.img` | 64 | 384 | Minimal, debug kernel, tracing on |
| `image-hfs` | `puredarwin.img` | 64 | 6144 | HFS+ root instead of ext4 |

`image-hfs` has two uses.

The first is bisection. When something looks like filesystem corruption, booting the
same system on Apple's own `hfs.kext` tells you whether the ext4 driver is the culprit.
It has been the deciding test more than once.

The second is for macOS users who want to open the image and change something. Every
other image has an ext4 root, and macOS cannot mount ext4 without our own kext, which is
not much help when the thing you are trying to modify is the image that contains it. An
HFS+ root mounts on a Mac without ceremony. This is the mildly absurd consequence of
supporting a filesystem Apple does not: the Linux-native option is the one a Mac cannot
read.

## arm64

| Package | ESP | Root | Notes |
| --- | --- | --- | --- |
| `image-arm64-virt` | 64 | 6144 | QEMU virt, `BOOTAA64.EFI` |
| `image-arm64-virt-minimal` | 768 | 512 | RAM disk root (`rd=md0`), 512 MB ramdisk |
| `image-arm64-virt-minimal-release` | 64 | 512 | Release kernel, AHCI and kext logging |
| `image-arm64-virt-full` | 64 | 3072 | Larger set, virtio-gpu debugging enabled |
| `netboot-arm64-virt-minimal` | - | - | Netboot only, 512 MB ramdisk |
| `ramdisk-arm64-t8010` | - | - | iPad 6, 160 MB ext4 ramdisk, loaded by PongoOS |
| `image-arm64-bcm2837` | 64 | 1024 | Raspberry Pi 3, `puredarwin-rpi3.img` |

## Geometry and ramdisk knobs

`image.nix` parameters you will meet when adding a flavour:

| Parameter | Default | Meaning |
| --- | --- | --- |
| `espMB` | 64 | EFI system partition size |
| `rootMB` | 6144 | Root partition size |
| `apfsMB` | 128 | APFS test partition size |
| `rootFsType` | `ext4` | `ext4` or `hfs` |
| `efiBinary` | `BOOTX64.EFI` | `BOOTAA64.EFI` on arm64 |
| `netbootOnly` | false | Produce netboot artifacts instead of a disk image |
| `useRamdisk` | false | Root from a RAM disk |
| `ramdiskMB` | 128 | RAM disk size |
| `ramdiskPrune` | empty | Paths to drop from the RAM disk only |
| `bootArgs` | see below | Written to `\EFI\BOOT\boot-args.txt` |

`ramdiskPrune` matters more than it looks. A RAM disk has to fit in memory twice over on
the way in, so anything not needed to run the system is worth removing. The T8010 image
prunes the kernels directory, every `include` tree, the pkgconfig directories and the
guest header staging.

## Baked boot-args

The default, used by the full x86_64 images:

```
debug=0x218 -nogzalloc_mode keepsyms=1 serial=3 gopconsole=1 -noprogress
gen9_debug=1 serial_video_mirror=1
```

Per-flavour overrides:

| Flavour | boot-args |
| --- | --- |
| `image-minimal` | `-v debug=0x218 -nogzalloc_mode keepsyms=1 serial=3 gopconsole=1 gen9_debug=1` |
| `image-minimal-debug` | as above plus `serial_video_mirror=1 pdtrace=1` |
| `image-arm64-virt-minimal`, `netboot-arm64-virt-minimal` | `-v debug=0x218 -nogzalloc_mode keepsyms=1 serial=3 gopconsole=1 pdtrace=1 serial_video_mirror=1 no_interrupt_masked_debug=1 rd=md0` |
| `ramdisk-arm64-t8010` | `-v debug=0x218 -nogzalloc_mode keepsyms=1 serial=3 serial_video_mirror=1 no_interrupt_masked_debug=1 rd=md0` |
| `image-arm64-bcm2837` | `-v debug=0x218 -nogzalloc_mode keepsyms=1 serial=1 no_interrupt_masked_debug=1` |
| `image-arm64-virt-full` | default plus `vgpu_debug=1` |
| `image-arm64-virt-minimal-release` | `-v serial=3 ahci_debug=1 kext=0xffff io=0xffff` |

The loader falls back to a built-in default if it cannot read `boot-args.txt`, but the
file is there so you can edit arguments without rebuilding an image. What each argument
does is in [Debugging](../debugging.md).

One row reads oddly on its own: `ramdisk-arm64-t8010` sets `serial=3` on a device with
no serial port. `serial_video_mirror=1` is the part that matters there, because the
console the user actually sees is the iPad's display. See
[arm64 T8010](../targets/arm64-t8010.md).
