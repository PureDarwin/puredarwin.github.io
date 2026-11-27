# Image Flavours

Every image is built by the same `image.nix`, with different contents and sizes.
`nix/image-contents.nix` defines each one, so read it for the exact contents and boot
arguments, which change often.

## x86_64

| Package | What it is |
| --- | --- |
| `image-minimal` | A small image that boots to a shell. Used for most boot testing |
| `image-wayland` | The Argon desktop with the GPU and Wi-Fi drivers and the built-in apps. Also built as `image-argon`. This is the "Desktop" download |
| `image-nvidia` | The same desktop with NVIDIA's 580 driver, for Maxwell, Pascal and Volta cards |
| `image` | The full image: every GPU and Wi-Fi driver, and both 64-bit and 32-bit UEFI and BIOS boot on one disk |
| `image-sb` | The full image signed for Secure Boot. See [Secure Boot](secure-boot.md) |
| `image-wayland-minimal` | The desktop session on a small base |
| `image-debug` | Built against the debug kernel |
| `image-amdgpu-debug` | The desktop with extra GPU driver logging, to find out why a driver gives up |
| `image-hfs` | An HFS+ root instead of ext4 |
| `image-apfs` | An APFS root |
| `image-installer`, `iso-installer` | An install and rescue drive, with the disk tools and the installer |
| `image-virtio-drm` | For virtual machines with a virtio GPU |

`image-hfs` has two uses.

The first is narrowing down bugs. When something looks like filesystem damage, boot the
same system on Apple's own HFS+ driver. If the problem goes away, the ext4 driver is the
cause. This test has settled the question more than once.

The second is for Mac users who want to open the image and change something. macOS
can't read ext4 without our driver, but it reads HFS+ without any help.

## arm64 and Others

| Package | What it is |
| --- | --- |
| `image-arm64-virt` | A disk image for QEMU's virt machine |
| `image-arm64-virt-minimal` | The virt machine with its root in a RAM disk. This is the arm64 download |
| `image-arm64-virt-wayland` | The virt machine with a Wayland desktop |
| `netboot-arm64-virt-minimal` | Files for network booting, with no disk image |
| `image-arm64-bcm2837` | Raspberry Pi 3 |
| `image-arm64-t8103` | Apple M1 machines. Work in progress |
| `ramdisk-arm64-*` | RAM disk images for boards that load the system into memory, such as the Allwinner, Tegra and Snapdragon boards |
| `bootimg-arm64-*` | Android boot images, for phones |
| `image-riscv64-virt-minimal` | QEMU's riscv64 virt machine |

## Settings for a New Flavour

These are the `image.nix` settings you meet when you add a flavour:

| Setting | Meaning |
| --- | --- |
| `espMB` | Size of the EFI system partition, the small FAT partition the firmware reads |
| `rootMB` | Size of the root partition |
| `rootFsType` | `ext4` or `hfs` |
| `efiBinary` | `BOOTX64.EFI`, or `BOOTAA64.EFI` on arm64 |
| `useRamdisk`, `ramdiskMB` | Put the root filesystem in a RAM disk, and its size |
| `ramdiskPrune` | Paths to leave out of the RAM disk |
| `netbootOnly` | Make network boot files and no disk image |
| `bootArgs` | Boot arguments, written to `\EFI\BOOT\boot-args.txt` |

`ramdiskPrune` matters more than it looks. A RAM disk has to fit in memory twice while
it's loaded, so anything the running system doesn't need should go.

## Boot Arguments

Each image writes its boot arguments to `\EFI\BOOT\boot-args.txt` on the EFI partition.
You can edit that file without rebuilding the image. The loader uses its own defaults
if it can't read the file. [Debugging](../debugging.md) explains what each argument
does.
