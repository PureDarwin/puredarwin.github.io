boot
====
The boot project contains the bootloader that is used to boot the system on generic hardware through BIOS. 

### What is boot
boot is a series of files that collectively act as bootloader for BIOS-based hardware.

-   **boot** (sometimes referred to as "boot2") [HFS+ startup file](http://developer.apple.com/technotes/tn/tn1150.html#StartupFile), lives in the HFS+ file system structure (not a regular file). (Could also be used as a regular file; using a special version of boot1h that would no longer need it to be HFS+ the startup file.)
-   **[Master Boot Record](http://en.wikipedia.org/wiki/Master_boot_record)** (MBR), lives in the first 440 bytes of the disk (not identical to the MBR from other OSes)
-   **boot1h** stage 1 booter (bootsector) for HFS+ partitions, lives in the first 512 bytes of the partition
-   **boot1u** (not used by PureDarwin)
-   **boot1u0** (not used by PureDarwin)
-   **cdboot** booter for CD-ROMs (only works with valid Extensions.mkext due to a bug)
-   **chain0** (tbd; probably not used by PureDarwin)

Since Intel-based Macintosh computers use EFI instead of BIOS, they need to use a different bootloader, [efiboot](https://github.com/PureDarwin/PureDarwin/wiki/efiboot).
Another alternative to the above two bootloaders, is the new XNU loading support in [grub2](http://www.gnu.org/software/grub/grub-2.en.html), which works on both platforms (EFI and BIOS based) . For more information, check out [this](http://grub.enbug.org/XNUSupport) page.

### Requirements

To use boot, you need:

-   A MBR-formatted HFS+ volume containing a Darwin system
-   startupfiletool ([source](http://www.opensource.apple.com/darwinsource/projects/other/DarwinTools-1/))
-   boot-132 ([patched](http://tgwbd.org/darwin/boot.html) to include the EFI tables the Darwin system expects to be present)

### Installation

The disk needs to contain a HFS+ volume, and it must not be mounted.

```
launchctl unload /System/Library/LaunchDaemons/com.apple.diskarbitrationd.plist
[startupfiletool](../../downloads.html) ${RDEVICE}s1 boot
sleep 3
dd if=boot1h of=${RDEVICE}s1 bs=512 count=1
sleep 3
dd if=boot0 of=${DEVICE} bs=440 count=1
sync
launchctl load /System/Library/LaunchDaemons/com.apple.diskarbitrationd.plist
````

The chameleon boot loader (a fork of boot-132) has a greatly simplified installation procedure, since it does NOT need the disk to be unmounted, and it does NOT need startupfiletool:

```
fdisk -f boot0 -u -y /dev/rdiskX    # Install boot0 to the MBR
dd if=boot1h of=/dev/rdiskXsY       # Install boot1h to the partition's bootsector
cp boot /Volumes/XXX                # Install boot to the volume's root directory
```

### Troubleshooting

#### Non-System Disk

**Problem:** You get the error
```
Boot0: MBR
Boot0: Done
Non-System Disk
```
**Solution:** You need to set the partition bootable ("boot flag", "set partition active"), e.g., using fdisk:

```
sh-3.2# fdisk -e /dev/rdisk1
Enter 'help' for information
fdisk: 1> f 1
Partition 1 marked active.
fdisk:*1> w
Device could not be accessed exclusively.
A reboot will be needed for changes to take effect. OK? [n] y
Writing MBR at offset 0.
fdisk: 1> q
sh-3.2# 
```

#### Wrong system booted by default

**Problem:** On a system with multiple OSes, boot wants to boot the wrong (non-PureDarwin) one by default. This happens when a non-HFS+ partition (e.g., FAT32 or NTFS) has the bootable ("active") flag and comes before the HFS+ partition that contains PureDarwin.

**Solution:** Modify boot so that it uses the first HFS+ partition instead of the first partition with the bootable ("active") flag:

In `boot-132/i386/lib/libsaio/sys.c`, comment the following line:

```
    for ( bvr = chain; bvr; bvr = bvr-&gt;next ) 
    { 
        if ( bvr-&gt;flags & kBVFlagNativeBoot ) bvr1 = bvr; 
        <span style="font-weight:bold">// if ( bvr-&gt;flags & kBVFlagPrimary )    bvr2 = bvr; 
    }
```

To be continued...