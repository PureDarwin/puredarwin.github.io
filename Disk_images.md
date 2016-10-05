Disk images
===========
This page describes various formats for disk images used in Darwin, Mac OS X, and Linux.
 This is a work in progress. Please add to the table.

Note that this page might mention tools that are only available in Mac OS X, but not in PureDarwin.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Hard disk images](diskimages.html#TOC-Hard-disk-images)
    1.  [**1.1** .dmg (disk image)](diskimages.html#TOC-.dmg-disk-image-)
    2.  [**1.2** .dd/.cdr (raw image)](diskimages.html#TOC-.dd-.cdr-raw-image-)
    3.  [**1.3** .vmdk (Virtual Machine Disk Format)](diskimages.html#TOC-.vmdk-Virtual-Machine-Disk-Format-)
    4.  [**1.4** Dump a CD/DVD to an iso image](diskimages.html#TOC-Dump-a-CD-DVD-to-an-iso-image)
    5.  [**1.5** Hybrid media](diskimages.html#TOC-Hybrid-media)
2.  [**2** Bootable CDs](diskimages.html#TOC-Bootable-CDs)
3.  [**3** Mounting DMGs on PureDarwin](diskimages.html#TOC-Mounting-DMGs-on-PureDarwin)
    1.  [**3.1** vndevice](diskimages.html#TOC-vndevice)
    2.  [**3.2** hdik](diskimages.html#TOC-hdik)
    3.  [**3.3** Source code as starting point for own developments](diskimages.html#TOC-Source-code-as-starting-point-for-own-developments)
    4.  [**3.4** Conversion of disk images using LibDMG's HFS+ implementation](diskimages.html#TOC-Conversion-of-disk-images-using-LibDMG-s-HFS-implementation)

### Hard disk images
#### <span style="font-weight:normal">.</span>dmg (disk image)
.dmg files can contain either an image of one volume (partition) or of an entire disk (device; including the MBR).

These files are used on the Mac. They can be created by Disk Utility, for example.
 file reports "VAX COFF executable - version 8122" for compressed images.
To mount these on a PureDarwin system, they need to be uncompressed first using the [dmg2img](http://vu1tur.eu.org/tools/) utility. Here is an example:
<span style="font-family:courier new,monospace">URL="http://macfuse.googlecode.com/files/MacFUSE-2.0.3%2C2.dmg"</span>
<span style="font-family:courier new,monospace">DMG="MacFUSE-2.0.3,2.dmg"</span>
<span style="font-family:courier new,monospace">MOUNTPOINT=/Volumes/test/</span>
<span style="font-family:courier new,monospace">VN=/dev/vn0</span>
<span style="font-family:courier new,monospace">set +v # be verbose</span>
<span style="font-family:courier new,monospace">set +e # exit on errors</span>
<span style="font-family:courier new,monospace">wget -c "${URL}" # download compressed DMG</span>
<span style="font-family:courier new,monospace">IMG=$(echo "${DMG}" | sed -e "s|.dmg$|.img|g" ) # get name of IMG</span>
<span style="font-family:courier new,monospace">dmg2img "${DMG}" -o "/tmp/${IMG}" -v # uncompress to IMG, http://trac.macports.org/ticket/23489 </span>
<span style="font-family:courier new,monospace">vndevice attach /dev/vn0 "/tmp/${IMG}" # attach IMG to device</span>
<span style="font-family:courier new,monospace">mkdir "${MOUNTPOINT}" # create mount point</span>
<span style="font-family:courier new,monospace">mount -t hfs "${VN}" "${MOUNTPOINT}" # mount</span>
<span style="font-family:courier new,monospace">find "${MOUNTPOINT}" -iname Archive.pax.gz # do something</span>
<span style="font-family:courier new,monospace"># install (to be written)...</span>
<span style="font-family:courier new,monospace">umount "${MOUNTPOINT}" && rm -r "${MOUNTPOINT}" # unmount</span>
<span style="font-family:courier new,monospace">vndevice detach "${VN}" # detach device</span>
<span style="font-family:courier new,monospace">rm "/tmp/${IMG}" # delete IMG</span>
The dmg2img utility can be compiled on a PureDarwin system using MacPorts (see [#23489](http://trac.macports.org/ticket/23489)).
#### .dd/.cdr (raw image)
These files are raw dumps, as the dd program uses them.
You can convert .dmg files to these on the Mac, using the following command:
    hdiutil convert some.dmg -format UDTO -o some.dd
hdiutil uses the suffix ".cdr" for these files, but in fact the result is a raw dump that can be used with standard, cross-platform tools such as dd. This is why we prefer the ".dd" suffix. 

To write a raw dump to a physical disk:
<span style="font-weight:bold">CAUTION: </span>the following commands are dangerous. You might accidentially wipe your hard disk.
Do not use this if you do not know what you are doing.
-   On the Mac, it can be written with
        dd if=some.dd of=/dev/rdiskX bs=2048
-   On Linux, it can be written with
> <span style="font-family:courier new;font-size:12px;white-space:pre">dd if=some.dd of=/dev/sdaX bs=2048</span>
    .vmdk (Virtual Machine Disk Format)In this case we use qemu-img.
    qemu-img convert -O vmdk PureDarwin.iso PureDarwin.vmdk
    CD/DVD images
<span style="font-size:14px;font-weight:bold">.iso (ISO 9660 CD-ROM filesystem data)</span>

First, you need to populate a temporary directory that contains the boot-132 files and that has cdboot as its El Torito boot image (this allows BIOS-based machines to boot).

<span style="font-family:courier new,monospace"><span style="font-size:small">ELTORITOISO=/tmp/eltorito.iso</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">cp cdboot ... /tmp/i386/</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">cd /tmp/i386</span></span>

From the temporary directory, run <span style="font-style:italic">mkisofs</span>:

<span style="font-family:courier new,monospace"><span style="font-size:small">mkisofs -quiet -V "PureDarwin" -no-emul-boot -boot-load-size 4 -c boot.cat -b cdboot -o "$</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">ELTORITOISO"</span></span>

In order to retreive the sector count:


<span style="font-family:courier new,monospace"><span style="font-size:small">sectors=$(du "$ELTORITOISO" | tail -1 | awk '{print $1}')</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">size_mb=$(du -h "$ELTORITOISO" | tail -1 | awk '{print $1}')</span></span>

Then create, initialize and mount a HFS+ disk image (dmg)


<span style="font-family:courier new,monospace"><span style="font-size:small">hdiutil create -fs HFS+J -o "$CDDMG" -size 256M -layout NONE -type UDIF -nospotlight</span></span>


Partitioning with pdisk + newfs_hfs.
(please add text)


The tricky way is to "injects" parts of the temporary El Torito ISO into the dmg using

<span style="font-family:courier new,monospace"><span style="font-size:small">dd if="$ELTORITOISO" of=$rdev skip=64 seek=64 bs=512</span></span>
<span style="font-family:courier new;font-size:12px">
</span>
(please add text)
#### Dump a CD/DVD to an iso image
<span style="font-family:courier new,monospace"><span style="font-size:small">hdiutil create -srcdevice /dev/disk1s0 -format UDTO some.iso
mv some.iso.cdr some.iso</span></span>
#### Hybrid media
Up to four file systems supported: HFS+, ISO-9660, Joliet and/or UDF.
<span>       </span><span style="font-family:courier new,monospace"><span style="font-size:small">-hfs Generate an HFS+ filesystem
<span>    </span>-iso Generate an ISO9660 filesystem
<span>    </span>-joliet Generate Joliet extensions to ISO9660
<span>    </span>-udf Generate a UDF filesystem
</span></span>
(Please write some text)
<span style="font-family:courier new,monospace"><span style="font-size:small">hdiutil makehybrid -o ... ...</span></span>
### Bootable CDs
For bootable CDs, see [here](booting/booting-from-cd-rom.html).
### Mounting DMGs on PureDarwin
It looks like compressed DMGs (UDIF) cannot readily be mounted on PureDarwin since Darwin lacks the neccessary frameworks (e.g., DiskImages.framework) and/or kernel extensions (e.g., IOHDIXController.kext and its plug-ins) that Mac OS X uses for this purpose.

<span style="color:rgb(255,0,0)">IOHDIXController.kext used to be </span>[<span style="color:rgb(255,0,0)">distributed</span>](../legal/binarydrivers.html)<span style="color:rgb(255,0,0)"> with Darwin under the Apple Binary License. Perhaps that's what we need to do for PureDarwin as well.</span>
#### vndevice
Using the raw BSD vndevice would mean that we cannot seemingly use compressed DMGs (UDIF).
Since we want to use a compressed filesystem, it appears that the raw vndevice approach is not an option for PureDarwin.
#### hdik
Mac OS X comes with a little tool called hdik. Its description reads like it could exactly do what we need in PureDarwin:


     hdik is a lightweight tool that can be used to attach disk images in-ker-
     nel (i.e. not using a user-land process to providing the backing store).
     Only a subset of disk images can be mounted in this manner including
     read/write disk images, UDIF disk images that use zlib compression, shad-
     owed disk images, and sparse disk images.

     hdik is intended for use in situations where linking against the DiskIm-
     ages framework is problematic or an extremely lightweight mechanism for
     attaching a disk image is needed.

And it looks like it has no "impure" dependencies. However, it apparently calls /usr/libexec/load_hdi which, according to its man page, "is used to load the disk image driver.  load_hdi is invoked by the DiskImages framework when it needs to attach images and the user client in IOHDIXController.kext is not available".

Besides, it looks like the source for hdik is not available. Apparently, hdik is part of the closed-source project DiskImages-195.
So it appears that it is not an option for PureDarwin either.
#### Source code as starting point for own developments
For compressed DMGs (UDIF) see [here](http://catacombae.svn.sourceforge.net/viewvc/catacombae/DMGExtractor/src/org/catacombae/udif/) (sample code in Java) and here ([C](http://vu1tur.eu.org/tools/))
Also have a look at this:
<https://svn.greensocs.com/public/packages/qemu_systemc/qemu-0.9.1/block-dmg.c>

#### **Conversion of disk images using LibDMG's HFS+ implementation**
**
**
This log should be cleaned up, when I (Tyson) get around to it:

<span>(11:04:38 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>hi
<span>(11:05:56 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>I just had a bit of experience with getting a dmg image converted into a raw disk image with 1 partion
<span>(11:06:12 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>so poweriso and dmg2img didn't work for me
<span>(11:06:30 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>both produced a wrong kind of image
<span>(11:06:46 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>which I couldn't validate with fdisk/parted
<span>(11:06:59 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>then I found this:
<span>(11:07:02 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span><https://github.com/planetbeing/libdmg-hfsplus/>
<span>(11:07:13 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>commit d4a253cae40fb4b38377273eb1f89f21c4cb224a
<span>(11:08:13 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>^ current state of the master branch is a bit broken, but all I had to do was just to add one variable which was not defined for some reason
<span>(11:08:53 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>after it compiled, I got the 'dmg' util to convert the image
<span>(11:09:19 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>and the result turned out to be valid in parted
<span>(11:09:29 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>now
<span>(11:09:53 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>the problem is that [http://www.puredarwin.org/developers/diskimages](diskimages.html) is not a wiki page
<span>(11:10:10 AM) </span><span style="color:rgb(118,69,31)">errordeveloper: </span>and I cannot simpy add this info there, so other might find it usefull



