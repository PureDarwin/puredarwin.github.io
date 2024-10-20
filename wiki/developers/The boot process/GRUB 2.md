GRUB 2
======
GRUB, the GRand Unified Bootloader, is a boot loader from the GNU project. GRUB 2 is a complete rewrite. In early 2009, Vladimir Serbinenko has added support for booting Darwin to GRUB 2, making it suitable as an alternative to boot-132 (the original Apple Darwin boot loader).
However the "COPYING" file stipulates a GPLv3 license.
This page discusses how to install and use GRUB 2.

For BIOS-based machines
-----------------------
### Getting GRUB 2
Since GRUB 2 is still under heavy development, and since the XNU-related functionality is still very new at the time of this writing (June 2009), your best option for getting the most recent version of GRUB 2 is to compile it from source.
#### Compiling from SVN using Ubuntu
At the time of this writing, there are some issues with compiling GRUB 2 on Mac OS X and Darwin. Hence, the follwoing instructions assume that you use a Ubuntu 8.10 Live CD (more recent versions should work as well). (This page needs to be updated to explain the procedure using Mac OS X or Darwin as well.)
 `sudo apt-get update`
 `sudo apt-get install build-essential subversion autoconf ruby bison`
 `svn co svn://svn.sv.gnu.org/grub/trunk/grub2`
 `cd grub2/`
 `./autogen.sh`
 `./configure --enable-efiemu`
 `make`
 `sudo make install`
 This should install GRUB 2 to /usr/local/bin, from where you can call it to install the boot loader to a disk.
### Installing GRUB 2
Once you have installed GRUB 2 to /usr/local/bin as described above, you need to install it to the disk you want to make bootable.
 `sudo grub-install --root-directory=/media/XXX/ /dev/sdX `
 This should give a message like
 `Installation finished. No error reported.`
 `This is the contents of the device map /media/disk//boot/grub/device.map.`
 `Check if this is correct or not. If any of the lines is incorrect,`
 `fix it and re-run the script `grub-install'.`
 This has been tested with a FAT32-formatted USB stick. You need to replace `/media/XXX/ `with the mountpoint the partition is mounted to, and `/dev/sdX `with the device of the USB stick (not the partition). It might be necessary that you flag the partition bootable using cfdisk. To be investigated: Can we install this to a HFS+ volume from Ubuntu?
### Booting Darwin with GRUB 2
GRUB 2 lets you control the kernel and extensions to be loaded in a very fine-grained manner. Please refer to the [XNUSupport page of the GRUB wiki](http://grub.enbug.org/XNUSupport) for more detailed information. The following searches all disks for /mach_kernel, and boots it using Extensions.mkext:
 `insmod vbe`
 `insmod gfxterm`
 `search --set ``/mach_kernel`
 `xnu_kernel /mach_kernel`
 `xnu_mkext /System/Library/Extensions.mkext`
 `terminal_output gfxterm
 boot`
For EFI-based machines
----------------------
GRUB 2 can also be used on EFI-based machines, such as Intel-based Macs.
 The procedure is different from the one described above. Basically, you have to compile GRUB 2 as an EFI module, and place it in
 `/EFI/BOOT/BOOTX64.EFI`
 `/EFI/BOOT/BOOTIA32.EFI`
 on your disk. When you press the Alt key during boot, your Intel Mac should show the disk as "EFI Boot". See [this thread on the Ubuntu Forums](http://ubuntuforums.org/showpost.php?p=7275427&postcount=762) for more information.
References
----------
-   <http://en.wikipedia.org/wiki/GNU_GRUB>
-   <http://www.gnu.org/software/grub/grub-2.en.html>
-   <http://grub.enbug.org/XNUSupport>
-   <http://ubuntuforums.org/showpost.php?p=7275427&postcount=762>
