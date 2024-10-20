This page describes how to produce a CD-ROM (or DVD, for that matter) which can boot Darwin on both EFI- and BIOS-based systems.

### What we want to do 

Master a CD from which both EFI- (Intel Mac) and BIOS-based (PC) systems can boot.

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/bothboots.jpg)

An Intel-based Macintosh will actually be able to boot the volume either through EFI (right-hand side) or through its Compatibility Support Module ("Boot Camp") BIOS emulation (left-hand side, misleadingly labeled "Windows").

### How hybrid images work

The key is to use a HFS+ filesystem for the image (thus, making a ".dmg" rather than a ".iso") and "injecting" parts of an El Torito ISO into it, This is called a "hybrid image". 

### How to create a hybrid image using pd_makedmg 

To create a hybrid image, you can use the [pd_makedmg](https://github.com/PureDarwin/PureDarwin/blob/master/scripts/pd_makedmg) script. It is based on [darwinmaster.sh](https://darwinbuild.macosforge.org/trac/browser/trunk/darwinbuild/darwinmaster.sh), and has been extended to support EFI booting in addition to BIOS booting. Its syntax is as follows:

```
pd_makedmg /Volumes/PureDarwinDisk /tmp/puredarwin.dmg PureDarwin
```

This would take the files located at `/Volumes/PureDarwinDisk` (which should contain a working Darwin installation) and turn them into a disk image located at `/tmp/puredarwin.dmg` with the name of "PureDarwin", which could be burned to a CD e.g., using Disk Utility.

Note that `pd_makedmg` currently needs a Mac to run, since it makes use of commands like `hdiutil` which are not part of Darwin.

### How pd_makedmg works

Here is what it essentially does:
-   Creates `Extensions.mkext` from the kexts in the source tree
-   Makes a temporary ISO that contains the boot-132 files and that has cdboot as its El Torito boot image 
    (this allows BIOS-based machines to boot)
-   Creates, initializes and mounts a HFS+ disk image (dmg)
-   "Injects" parts of the temporary El Torito ISO into the dmg using
    `dd if="$ELTORITOISO" of=$rdev skip=64 seek=64 bs=512`
    (Do not actually execute this command. It is ran automatically by the script.)
-   Copies the contents of the source tree to the dmg
-   Blesses `boot.efi` (this allows EFI-based machines to boot)

### kexts needed for booting from CD-ROM

Following the instructions from above should produce a CD that boots at least to the point `Still waiting for root device...`. For the kernel to be able to access the CD, the necessary kexts need to be installed of course. These are, in addition to the [minimal set of kexts](https://github.com/PureDarwin/PureDarwin/wiki/kexts):

-   IOATAPIProtocolTransport.kext
-   IOCDStorageFamily.kext
-   IODVDStorageFamily.kext
-   <span>IOBDStorageFamily.kext (Blu-ray Disc driver; available for Darwin as binary only)

### To do

-   Remove any tools that are not part of Darwin
-   replace `hdiutil create` with a simple `dd if=/dev/zero` and `hdid -nomount` with `losetup` ... and it would appear to work on Linux then (dfe)