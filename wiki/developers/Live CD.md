Live CD
=======
Live CDs are a very popular way to distribute operating systems.

### How Live CDs work
In order to make a PureDarwin Live CD, we essentially need to do two things:

1.  **Hardware detection**. Linux Live CDs configure themselves to use the correct drivers. While this is a major breaktrough for Linux distributions, Darwin has been working like this all the time. What this means for PureDarwin is that we essentially have to ensure that we ship a broad range of kexts, and the system does the rest "for free".
2.  **Compressed main filesystem**. Linux Live CDs contain, besides the kernel, an initrd (a small filesystem) which loads the necessary drivers (roughly comparable to Extensions.mkext), mounts a 700 MB compressed filesystem (roughly comparable to a .dmg) that contains around 2GB of compressed software, switches over ("chroot") to that filesystem, and continues to boot from there. For PureDarwin, we can probably achieve this by using *NetBoot disk images* locally. 
3.  **Union filesystem**. Because the main compressed filesystem is read-only, write accesses must be redirected to an overlay/union filesystem. Most Linux Live CDs use unionfs/aufs for this purpose. Darwin can use *shadow volumes* for the same purpose. A PureDarwin Live CD would *attach a shadow volume* that is stored in a local ramdisk to the root disk image. Mac OS X does this using the [nbdst](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man8/nbdst.8.html) tool.

If anyone knows more about how to use NetBoot images locally, please join work on the Live CD.

### How Mac OS X Installation DVDs work
Mac OS X Installation DVDs are capable of running Mac OS X from a read-only medium. Maybe we can learn from that, hence we are looking at the procedure in this paragraph.

As of Snow Leopard, Mac OS X Installation DVDs contain the launchd LaunchDaemon plist file /System/Library/LaunchDaemons/com.apple.install.cd.plist with the following content:

```XML
<?xml version="1.0" encoding="UTF-8">
<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
 <key>Label</key>
 <string>com.apple.install.cd</string>
 <key>OnDemand</key>
 <false/>
 <key>ProgramArguments</key>
 <array>
   <string>/bin/sh</string>
   <string>/etc/rc.install</string>
 </array>
</dict>
</plist>
```

Hence, when the system is booted, the script ```/etc/rc.install``` is executed. This script mainly launches the Installer. However, there is also a script ```/etc/rc.cdrom``` which does the main magic of mounting ramdisks to.

```sh
#!/bin/sh
# (...)

#
# Disable prebinding-on-the-fly while we're CD booted
#
export DYLD_NO_FIX_PREBINDING=1

#
# mount root_device to update vnode information
#
mount -u -o ro /

# (...)

#
# Create a RAM disk with same perms as mountpoint
#
RAMDisk()
{
  mntpt=$1
  rdsize=$2
  echo "Creating RAM Disk for $mntpt"
  dev=`hdik -drivekey system-image=yes -nomount ram://$rdsize`
  if [ $? -eq 0 ] ; then
    newfs_hfs $dev
    # save & restore fs permissions covered by the mount
    eval `/usr/bin/stat -s $mntpt`
    mount -t hfs -o union -o nobrowse $dev $mntpt
    chown $st_uid:$st_gid $mntpt
    chmod $st_mode $mntpt
  fi
}


**RAMDisk /Volumes 1024**
**RAMDisk /var/tmp 1024**
**RAMDisk /var/run 1024**
**
**
**RAMDisk /var/db 1024**
mkdir -m 1777 /var/db/mds


# language prefs, colorsync need to be able to write some preferences (5424449)
**RAMDisk** **** **/Library/Preferences 1024**
**RAMDisk /Library/ColorSync/Profiles/Displays 2048**


# use or create the boot cache playlist, and allow B&I to force 32-bit playlist generation
FORCETHIRTYTWO="false"
if nvram boot-args | grep "no64exec" ; then
 FORCETHIRTYTWO="true"
fi


SIXTYFOURBIT=`sysctl -n hw.cpu64bit_capable`


if [ $SIXTYFOURBIT = "0" -o $FORCETHIRTYTWO = "true" ] ; then
 echo "using 32-bit bootcache playlist"
 BootCacheControl -f /var/db/BootCache.playlist32 start
elif [ $SIXTYFOURBIT = "1" ] ; then
 echo "using 64-bit bootcache playlist"
 BootCacheControl -f /var/db/BootCache.playlist start
fi


# tell launchd to commence with loading the system.
# for the OS Install environment only, /etc/rc.install is included in this process.
launchctl load -D system


# this script sleeps forever; the installer or startup disk will always reboot the system. 
sleep 9999999
````
How does this script get called? **How can hdik be replaced with what is in Darwin? **Please let us know. Perhaps we could use a [MacFUSE](macfuse.html) based ramdisk from http://thebends.googlecode.com/svn/trunk/ramdisk/

So far, when replacing the above RAMDisk function with one based on MacFUSE's mount_ramdisk, we get
launchctl error: launch_msg(): Socket is not connected
Please let us know if you know how to solve this.
### How a PureDarwin Live CD might work
#### Alternative 1: Uncompressed from disc 
Run the system uncompressed from the CD medium (like PureDarwin nano or like the Mac OS X Install DVD). 

This is not a workable option for two reasons: It's slow (since more data needs to be read from the slow optical disc) and it's too small (700 MB is not much space).
#### Alternative 2: Using imageboot
The XNU kernel contains some references to "imageboot", e.g., here:
<http://fxr.watson.org/fxr/source/bsd/kern/imageboot.c?v=xnu-1228> 

Apparently, one should be able to boot using a boot argument like -v rp=file:///some.dmg
then the system would mount /some.dmg as the root device and continue booting from there.

How this works is largely undocumented. Below is a proof-of-concept for imagebooting PureDarwin nano on a Mac host.

What follows are proof-of-concept instructions that show how to boot into puredarwin.iso (from the PureDarwin nano image on the download page) that is located at / on a *Mac* running Mac OS X 10.5.4. **Please do not try this on a production machine. Only try this if you have a spare Mac.**
Download PureDarwin nano, it contains puredarwin.iso which we will use as the imageboot image
On the Mac running Mac OS X (tested with 10.5.4), copy puredarwin.iso to /
Change IOHDIXController.kext and its plug-ins so that they are loaded at boot time
(normally, this is only the case for NetBoot):
```sh
cd /System/Library/Extensions/IOHDIXController.kext/
find . -type f | xargs perl -i -p -e 'print STDERR "changed $val values on line $. of $ARGVn" if($val = s@Network-Root@Root@g)'
touch /System/Library/Extensions
```
Edit /Library/Preferences/SystemConfiguration/com.apple.Boot.plist so that it contains:
```XML
<key>Kernel Flags</key>
<string>-v r p=file:///puredarwin.iso</string>
```
Reboot the Mac. It should now boot into PureDarwin, running from puredarwin.iso

You have now performed an ImageBoot of PureDarwin nano on a Mac OS X host. 

To undo, remove the extra Kernel Flags from your Boot.plist.

There are (unverified) news reports that cite "ImageBoot" as an official feature in the not-yet-released Snow Leopard:
<http://www.macnn.com/articles/08/10/20/more.snow.leopard.changes> 


However, all attempts to make this work on a Darwin host so far resulted in 

According to Singh, the kernel can be forced to use the BSD vndevice instead of hdix by specifying vndevice=1 as a boot argument. In this case, the function netboot_setup() from netboot.c is supposed to mount the file system contained in the vndevice node. But we can't get it to work yet (and it would only work for uncompressed images).
![](/img/developers/live-cd/imageboot%20failed%20ro.png)

Please let us know if you know if you are aware of a working solution that does not involve IOHDIXController.kext, or where  a recent version of IOHDIXController.kext can be downloaded under a suitable license. (It used to be available under the Apple Binary License, but it made its last appearance in Darwin 6...)


As a totally desperate worst-case fallback scenario: The source code for mounting filesystem images is available, and there is source code for uncompressing compressed DMGs available. Maybe it would be feasible to write a minimal IOHDIXController.kext replacement that is able to mount compressed DMGs. Volunteers?


A set of NetBoot files created by System Image Utility looks like this:
<span style="font-family:courier new,monospace">
```
./i386
./i386/booter
./i386/mach.macosx
./i386/mach.macosx.mkext
./NBImageInfo.plist
./NetBoot.dmg
./ppc
./ppc/booter
./ppc/mach.macosx
./ppc/mach.macosx.mkext

$ file NetBoot.dmg
NetBoot.dmg: Apple Partition data block size: 2048, first type: Apple_partition_map, name: Apple, number of blocks: 63, second type: Apple_Driver43, name: Macintosh, number of blocks: 56, third type: Apple_Free, name: , number of blocks: 0, fourth type: Apple_Driver_ATAPI, name: Macintosh, number of blocks: 56

$ file i386/booter
i386/booter: Universal EFI binary with 2 architectures, i386, x86_64
```


(to be continued)
#### Alternative 3: Using a ZFS file
Maybe using a compressed ZFS file and manual trickery...

### Shadow files
This is a work in progress.


```sh
#!/bin/bash -e -x

mount -uw
touch /shadowfile

/usr/libexec/vndevice attach /dev/vn0 /uncompressed.dmg
/usr/libexec/vndevice shadow /dev/vn0 /shadowfile

mount -t hfs /dev/vn0 /live/
# /usr/libexec/vndevice detach /dev/vn0
```
### References
-   System Image Utility.app (part of [Server Admin Tools](http://www.apple.com/downloads/macosx/apple/macosx_updates/serveradmintools105.html) for Mac OS X) can create NetBoot images; probably the same can be achieved with lower-level command line tools
-   [/etc/rc.netboot](http://www.opensource.apple.com/darwinsource/10.5/launchd-257/launchd/src/rc.netboot) ([mailing list entry](http://lists.apple.com/archives/Macos-x-server/2007/Dec/msg00150.html))
-   [BootMania](http://www2.tba.t-com.ne.jp/beanz/BootManiaDoc/index_e.html), a software that supposedly can boot Darwin (8) with NetBoot
-   [Server Admin Tools 10.5](http://www.apple.com/support/downloads/serveradmintools105.html), contains *System Image Utility* which is used in Mac OS X to make NetBoot images

