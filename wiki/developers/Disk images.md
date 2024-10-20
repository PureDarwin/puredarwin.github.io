# Disk images

This page describes various formats for disk images used in Darwin, Mac OS X, and Linux.
 This is a work in progress. Please add to the table.

Note that this page might mention tools that are only available in Mac OS X, but not in PureDarwin.

## Hard disk images

### .dmg (disk image)
.dmg files can contain either an image of one volume (partition) or of an entire disk (device; including the MBR).

These files are used on the Mac. They can be created by Disk Utility, for example.
 file reports "VAX COFF executable - version 8122" for compressed images.
To mount these on a PureDarwin system, they need to be uncompressed first using the [dmg2img](http://vu1tur.eu.org/tools/) utility. Here is an example:

```shell
URL="http://macfuse.googlecode.com/files/MacFUSE-2.0.3%2C2.dmg"
DMG="MacFUSE-2.0.3,2.dmg"
MOUNTPOINT=/Volumes/test/
VN=/dev/vn0
set +v # be verbose
set +e # exit on errors
wget -c "${URL}" # download compressed DMG
IMG=$(echo "${DMG}" | sed -e "s|.dmg$|.img|g" ) # get name of IMG
dmg2img "${DMG}" -o "/tmp/${IMG}" -v # uncompress to IMG, http://trac.macports.org/ticket/23489 
vndevice attach /dev/vn0 "/tmp/${IMG}" # attach IMG to device
mkdir "${MOUNTPOINT}" # create mount point
mount -t hfs "${VN}" "${MOUNTPOINT}" # mount
find "${MOUNTPOINT}" -iname Archive.pax.gz # do something
# install (to be written)...
umount "${MOUNTPOINT}" && rm -r "${MOUNTPOINT}" # unmount
vndevice detach "${VN}" # detach device
rm "/tmp/${IMG}" # delete IMG
```

The dmg2img utility can be compiled on a PureDarwin system using MacPorts (see [#23489](http://trac.macports.org/ticket/23489)).

### .dd/.cdr (raw image)
These files are raw dumps, as the dd program uses them.
You can convert .dmg files to these on the Mac, using the following command:

```shell
hdiutil convert some.dmg -format UDTO -o some.dd
```

hdiutil uses the suffix ".cdr" for these files, but in fact the result is a raw dump that can be used with standard, cross-platform tools such as dd. This is why we prefer the ".dd" suffix. 

To write a raw dump to a physical disk:

**CAUTION**: the following commands are dangerous. You might accidentially wipe your hard disk.
Do not use this if you do not know what you are doing.

-   On the Mac, it can be written with
    
```shell
   dd if=some.dd of=/dev/rdiskX bs=2048
```
-   On Linux, it can be written with
    
```shell
    dd if=some.dd of=/dev/sdaX bs=2048
```

### .vmdk (Virtual Machine Disk Format)

In this case we use qemu-img.

```shell
qemu-img convert -O vmdk PureDarwin.iso PureDarwin.vmdk
```

### CD/DVD images

These are **.iso**s (ISO 9660 CD-ROM filesystem data)

First, you need to populate a temporary directory that contains the boot-132 files and that has cdboot as its El Torito boot image (this allows BIOS-based machines to boot).

```shell
ELTORITOISO=/tmp/eltorito.iso
cp cdboot ... /tmp/i386/
cd /tmp/i386
```

From the temporary directory, run *mkisofs*:

   ```shell
mkisofs -quiet -V "PureDarwin" -no-emul-boot -boot-load-size 4 -c boot.cat -b cdboot -o "$ELTORITOISO"
```

In order to retreive the sector count:

```shell
sectors=$(du "$ELTORITOISO" | tail -1 | awk '{print $1}')
size_mb=$(du -h "$ELTORITOISO" | tail -1 | awk '{print $1}')
```

Then create, initialize and mount a HFS+ disk image (dmg)

```shell
hdiutil create -fs HFS+J -o "$CDDMG" -size 256M -layout NONE -type UDIF -nospotlight
```

#### Partitioning with pdisk + newfs_hfs
(please add text)

The tricky way is to "injects" parts of the temporary El Torito ISO into the dmg using

```shell
dd if="$ELTORITOISO" of=$rdev skip=64 seek=64 bs=512
```

#### Dump a CD/DVD to an iso image

(please add text)

```shell
hdiutil create -srcdevice /dev/disk1s0 -format UDTO some.iso # create the image
mv some.iso.cdr some.iso # manually remove the forced .cdr extension
```

### Hybrid media
Up to four file systems supported: HFS+, ISO-9660, Joliet and/or UDF.

   -hfs Generate an HFS+ filesystem
   -iso Generate an ISO9660 filesystem
   -joliet Generate Joliet extensions to ISO9660
   -udf Generate a UDF filesystem

(Please write some text)

```shell
hdiutil makehybrid -o ... ...
```

## Bootable CDs
For bootable CDs, see [here](https://github.com/PureDarwin/PureDarwin/wiki/Booting-from-CD-ROM).

### Mounting DMGs on PureDarwin
It looks like compressed DMGs (UDIF) cannot readily be mounted on PureDarwin since Darwin lacks the neccessary frameworks (e.g., DiskImages.framework) and/or kernel extensions (e.g., IOHDIXController.kext and its plug-ins) that Mac OS X uses for this purpose.

IOHDIXController.kext used to be [distributed](https://github.com/PureDarwin/PureDarwin/wiki/BinaryDrivers) with Darwin under the Apple Binary License. Perhaps that's what we need to do for PureDarwin as well.

### vndevice
Using the raw BSD vndevice would mean that we cannot seemingly use compressed DMGs (UDIF).
Since we want to use a compressed filesystem, it appears that the raw vndevice approach is not an option for PureDarwin.

### hdik
Mac OS X comes with a little tool called hdik. Its description reads like it could exactly do what we need in PureDarwin:

>   hdik is a lightweight tool that can be used to attach disk images in-kernel (i.e. not using a user-land process to providing the backing store).
>   Only a subset of disk images can be mounted in this manner including
     read/write disk images, UDIF disk images that use zlib compression, shadowed disk images, and sparse disk images.

>  hdik is intended for use in situations where linking against the DiskIm-
>   ages framework is problematic or an extremely lightweight mechanism for
>   attaching a disk image is needed.

And it looks like it has no "impure" dependencies. However, it apparently calls /usr/libexec/load_hdi which, according to its man page, "is used to load the disk image driver.  load_hdi is invoked by the DiskImages framework when it needs to attach images and the user client in IOHDIXController.kext is not available".

Besides, it looks like the source for hdik is not available. Apparently, hdik is part of the closed-source project DiskImages-195.
So it appears that it is not an option for PureDarwin either.

### Source code as starting point for own developments
For compressed DMGs (UDIF) see [here](http://catacombae.svn.sourceforge.net/viewvc/catacombae/DMGExtractor/src/org/catacombae/udif/) (sample code in Java) and here ([C](http://vu1tur.eu.org/tools/))
Also have a look at this:
<https://svn.greensocs.com/public/packages/qemu_systemc/qemu-0.9.1/block-dmg.c>

### Conversion of disk images using LibDMG's HFS+ implementation

**This log should be cleaned up, when I (Tyson) get around to it:**

>   (11:04:38 AM) errordeveloper: hi

>   (11:05:56 AM) errordeveloper: I just had a bit of experience with getting a dmg image converted into a raw disk image with 1 partion

>   (11:06:12 AM) errordeveloper: so poweriso and dmg2img didn't work for me

>   (11:06:30 AM) errordeveloper: both produced a wrong kind of image

>   (11:06:46 AM) errordeveloper: which I couldn't validate with fdisk/parted

>   (11:06:59 AM) errordeveloper: then I found this:

>   (11:07:02 AM) errordeveloper: https://github.com/planetbeing/libdmg-hfsplus/>

>   (11:07:13 AM) errordeveloper: commit d4a253cae40fb4b38377273eb1f89f21c4cb224a

>   (11:08:13 AM) errordeveloper: ^ current state of the master branch is a bit broken, but all I had to do was just to add one variable which was not defined for some reason

>   (11:08:53 AM) errordeveloper: after it compiled, I got the 'dmg' util to convert the image

>   (11:09:19 AM) errordeveloper: and the result turned out to be valid in parted

>   (11:09:29 AM) errordeveloper: now

>  (11:09:53 AM) errordeveloper: the problem is that [http://www.puredarwin.org/developers/diskimages](diskimages.html) is not a wiki page

>   (11:10:10 AM) errordeveloper: and I cannot simpy add this info there, so other might find it usefull
