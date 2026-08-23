# Kernel collections

Modern Darwin does not load kexts from disk at boot. The kernel and its boot-time kexts
are linked ahead of time into a single Mach-O of type `MH_FILESET`, the kernel
collection, and the loader loads that. PureDarwin does the same, using `kc-builder` from
the `kc-tools` repository.

Build one with `nix build .#kc`, or `.#kc-arm64`, `.#kc-arm64-t8010`,
`.#kc-arm64-bcm2837`. The 32-bit ARM target does not use a fileset; it uses the older
prelinked-kernel format via `prelink-builder`, as `.#prelinked-arm32-bcm2835`.

## The x86_64 list

`nix/lib/kc-kexts.nix` holds the x86_64 kext list, in link order. It is a shared file on
purpose: the image build and the guest's own `pd-rebuild-kc` both read it, so the two
cannot drift. Read that file for the current list; the summary below is a guide to its
shape, not a substitute for it.

In order: `corecrypto`, `pthread`, `IOACPIFamily`, `PDACPIPlatform`, `IOPCIFamily`,
`AppleAPIC`, `AppleI386PCI`, `IOStorageFamily`, `IONVMEFamily`, `IOATAFamily` with its
nested `AppleIntelPIIXATA` plugin, `IOATABlockStorage`, `ext4`, `msdosfs`, `apfs`,
`HFSEncodings`, `hfs`, `AppleFileSystemDriver`, `Ext4FileSystemDriver`, `IOHIDFamily`,
`ApplePS2Controller`, `IOUSBFamily` with its composite, merge-nub, HID, EHCI, OHCI and
UHCI plugins, `RavynAHCIPort`, `RavynXHCIPort`, `IOGraphicsFamily`, `IOGOPFramebuffer`,
`IONetworkingFamily`, `IOVirtIOFamily`, `IOVirtIOGPU`, `IOVirtIONet`, `IOVirtIOBlock`,
`IOIntelFramebuffer`, `PDE1000`, `PDRealtek8111`, `RavynHDAudio`.

## Per-target lists

The other targets keep their lists inline in their builder, and they are much shorter,
because a board only needs what it has.

| Target | Builder | Highlights |
| --- | --- | --- |
| arm64 virt | `kc-arm64.nix` | `PDArmPlatformExpert`, `PDArmPCI`, the virtio family, USB, graphics |
| arm64 bcm2837 | `kc-arm64-bcm2837.nix` | `PDArmPlatformExpert`, `PDBcm2835SD`, ext4, `IOGOPFramebuffer` |
| arm64 t8010 | `kc-arm64-t8010.nix` | `corecrypto`, `pthread`, `PDArmPlatformExpert`, the ext4 pair |
| armv6 bcm2835 | `prelinked-arm32-bcm2835.nix` | As bcm2837 minus graphics |

Every builder also appends each `System.kext/PlugIns/*.kext` from the kernel output as a
codeless entry, which is how the pseudo-kexts that declare kernel symbol sets get into
the collection.

## Ordering and other traps

* The x86_64 list is in **link order**, not alphabetical. Changing the order changes
  what links.
* `corecrypto` is mandatory even on the smallest target. Without it `read_random()`
  dereferences NULL early in boot.
* On arm64, segment order in a fileset is load-bearing: `__LINKINFO` and `__KLD`
  squatting in the wrong place double-faulted corecrypto until the segments were
  relinked in the right order.
* `kc-tools` truncates a `<dict>` after an XML comment when parsing a kext's Info.plist.
  The kext then loses properties such as `IOProviderClass` and silently never matches.
  If a kext is in the collection but does nothing, grep the raw image for the property
  before suspecting the driver.

## Inspecting a collection

The in-tree `otool` understands `MH_FILESET` and `LC_FILESET_ENTRY`, so you can list the
entries of a KC without a Mac:

```
otool -l result/kernel | less
```
