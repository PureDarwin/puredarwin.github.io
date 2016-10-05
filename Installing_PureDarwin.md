Installing PureDarwin
=====================

Don't get too excited: we haven't put together a full "How to" yet. This page will provide a selection of pointers.

### Installing PureDarwin using GRUB and CHAMELEON

The process for installing PureDarwin to boot using the GRUB and CHAMELEON bootloaders (perhaps as part of a multi-boot system) is described below. Thanks to poppyer for the information.

The basic booting procedure is:
GRUB(MBR) -&gt; CHAMELEON boot1h -&gt; CHAMELEON boot2 -&gt; darwin kernel

First of all, preparing a primary partition as hfs partition 
NOTES: I only try these on a primary partition, so I am not sure whether it works for logical extended partition

1) make an hfs partition and mount it
   * FOR LINUX: using mkfs.hfs
   * FOR OSX: using the Disk Utils.app

2) loop mount the puredarwin image (iso or vmdk)
   * loop mount a vmdk might be tricky under linux.

3) copy everything from the puredarwin image to your hfs partition
   * FOR LINUX: using sudo cp -a
   * FOR OSX: using sudo cp -pR
   in order to preverse file wnerships etc.

So far, the hfs partition is ready, now going to install the boot loader

4) Download an extract the Chameleon Boot Loader to any folder. Copy the "boot" file (often called boot2) to the root of your hfs partition.

5) Unmount your HFS partition (VERY IMPORTANT)
   dd the "boot1h" file (1024 bytes) from chamelaeon to the bootsector of you hfs partition.

By here, the hfs partition is self bootable, now add it to your first level boot loader (GRUB)

6) add and item to the menu.lst of your GRUB (MBR), usually:
     rootnotify (hd?,?)
     makeactive
     chainloader +1

Last, if your CPU is SSE2 only, you MUST use the voodoo kernel
BEFORE your reboot, edit the 
/Library/Preferences/SystemConfiguration/com.apple.Boot.plist,
add ".voodoo" to "mach_kernel", so it becomes "mach_kernel.voodoo"
     * mach_kernel.voodoo is already shipped with puredarwin.Xmas
<span style="white-space:pre"> </span> * but mach_kernel.voodoo uses its own System.kext

Troubleshooting:
Q: if your first reboot freeze at: "MAC Framework successfully initialized using ...."
A: you might need a patched version of AppleACPIPlatform.kext and AppleAPIC.kext from boot132 generic.iso to replace those ones under /Systerm/Library/Extensions/

### Preparing a Disk Using Darwin Tools
(Sorry, these are just quick notes while I still remember.)

You will need:
-   The Chameleon boot loader, installed into /usr/standalone/i386/ 
-   <span style="font-family:courier new,monospace">fdisk</span> (a version comes with Chameleon, so use that one)
-   <span style="font-family:courier new,monospace">dd</span><span><span style="font-family:arial,sans-serif">, </span></span><span style="font-family:courier new,monospace">newfs_hfs</span> and <span style="font-family:courier new,monospace">mount</span>
Then, assuming that you're working with the first disk (0):
1.  Create a partition and install the primary bootloader: <span style="font-family:courier new,monospace">fdisk -i -a hfs /dev/rdisk0</span>
2.  <span style="font-family:arial,sans-serif">Create an HFS+ file system on the disk: </span><span style="font-family:courier new,monospace">newfs_hfs -s -J -v /dev/rdisk0</span>
3.  Install the secondary bootloader: <span style="font-family:courier new,monospace">dd if=/usr/standalone/i386/boot1h of=/dev/rdisk0s1</span>
4.  Mount the partition: <span style="font-family:courier new,monospace">mount -t hfs /dev/rdisk0s1 /tmp</span>
5.  Install the tertiary bootloader: <span style="font-family:courier new,monospace">cp /usr/standalone/i386/boot /tmp/</span>
6.  Install the kernel and everything else onto the system
Simples, eh? A version of the PureDarwin Nano CD image with these tools installed will be available soon.

