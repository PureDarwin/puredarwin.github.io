# Kernel Collections

Modern Darwin does not load kexts from disk at boot. The kernel and its boot-time kexts
are linked ahead of time into a single Mach-O of type `MH_FILESET`, the kernel
collection, and the loader loads that. PureDarwin does the same, using `kc-builder` from
the `kc-tools` repository.

Build one with `nix build .#kc`, or `.#kc-arm64`, `.#kc-arm64-t8010` and
`.#kc-arm64-bcm2837`. The 32-bit ARM target uses the older prelinked-kernel format
through `prelink-builder`, as `.#prelinked-arm32-bcm2835`.

## The Kext List

`nix/lib/kexts.nix` lists every kext the build produces. Each entry says which
architectures build it and which architectures' boot kernel collections include it. The
x86_64 entries that go into the boot collection come first, in link order. The image
build and the guest's own `pd-rebuild-kc` both read this list, so they cannot drift
apart. Read that file for the current list.

Each kext also builds as its own Nix derivation, so changing one kext rebuilds only that
kext and the collections that contain it.

## The Boot and Auxiliary Collections

The loader limits how large the boot collection can be, and the x86_64 collection is
close to that limit. So the desktop images split their kexts in two:

* **The boot collection** holds what the system needs to reach root: the platform, PCI,
  storage, filesystems, USB, input and the firmware framebuffer.
* **The auxiliary collection** holds the large drivers that can wait: the DRM GPU
  drivers and the USB Wi-Fi drivers. It is installed as
  `/Library/KernelCollections/AuxiliaryKernelExtensions.kc` and loaded once root is
  mounted.

The auxiliary collection lives on the ext4 root, so loading it needs
`csr-active-config=0x3` in the boot arguments. The desktop images set it. If the GPU or
Wi-Fi drivers never load, check that the boot arguments reached the kernel with
`sysctl kern.bootargs`.

## Per-Target Lists

The other targets keep their lists in their builders, and they are much shorter, because a
board only needs what it has.

| Target | Builder | Highlights |
| --- | --- | --- |
| arm64 virt | `kc-arm64.nix` | `PDArmPlatformExpert`, `PDArmPCI`, the virtio family, USB, graphics, `PDFBSDem` |
| arm64 bcm2837 | `kc-arm64-bcm2837.nix` | `PDArmPlatformExpert`, `PDBcm2835SD`, ext4, `IOGOPFramebuffer` |
| arm64 t8010 | `kc-arm64-t8010.nix` | `corecrypto`, `pthread`, `PDArmPlatformExpert`, the ext4 pair |
| armv6 bcm2835 | `prelinked-arm32-bcm2835.nix` | As bcm2837, without graphics |

Every builder also appends each `System.kext/PlugIns/*.kext` from the kernel output as a
codeless entry. That is how the pseudo-kexts that declare kernel symbol sets get into the
collection.

## Ordering and Other Traps

* The x86_64 list is in **link order**. Changing the order changes what links.
* `corecrypto` is required even on the smallest target. Without it `read_random()`
  dereferences NULL early in boot.
* On arm64, segment order in a fileset matters. `__LINKINFO` and `__KLD` in the wrong
  place double-faulted corecrypto until the segments were relinked in order.
* `kc-tools` truncates a `<dict>` after an XML comment in a kext's `Info.plist`. The kext
  then loses properties such as `IOProviderClass` and silently never matches. If a kext
  is in the collection but does nothing, search the raw image for the property before
  you suspect the driver.
* A kext in the auxiliary collection can only call kernel functions that are exported to
  it. Inline functions from a family's headers can end up bound to a panic stub. Call
  virtual methods or read registry properties instead.

## Inspecting a Collection

The in-tree `otool` understands `MH_FILESET` and `LC_FILESET_ENTRY`, so you can list the
entries of a collection without a Mac:

```
otool -l result/kernel | less
```
