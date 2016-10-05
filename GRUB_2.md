GRUB 2
======
GRUB, the GRand Unified Bootloader, is a boot loader from the GNU project. GRUB 2 is a complete rewrite. In early 2009, Vladimir Serbinenko has added support for booting Darwin to GRUB 2, making it suitable as an alternative to boot-132 (the original Apple Darwin boot loader).
However the "COPYING" file stipulates a GPLv3 license.
This page discusses how to install and use GRUB 2.
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** For BIOS-based machines](grub2.html#TOC-For-BIOS-based-machines)
    1.  [**1.1** Getting GRUB 2](grub2.html#TOC-Getting-GRUB-2)
        1.  [**1.1.1** Compiling from SVN using Ubuntu](grub2.html#TOC-Compiling-from-SVN-using-Ubuntu)
    2.  [**1.2** Installing GRUB 2](grub2.html#TOC-Installing-GRUB-2)
    3.  [**1.3** Booting Darwin with GRUB 2](grub2.html#TOC-Booting-Darwin-with-GRUB-2)
2.  [**2** For EFI-based machines](grub2.html#TOC-For-EFI-based-machines)
3.  [**3** References](grub2.html#TOC-References)

For BIOS-based machines
-----------------------
### Getting GRUB 2
Since GRUB 2 is still under heavy development, and since the XNU-related functionality is still very new at the time of this writing (June 2009), your best option for getting the most recent version of GRUB 2 is to compile it from source.
#### Compiling from SVN using Ubuntu
At the time of this writing, there are some issues with compiling GRUB 2 on Mac OS X and Darwin. Hence, the follwoing instructions assume that you use a Ubuntu 8.10 Live CD (more recent versions should work as well). <span style="color:rgb(255,0,0)">(This page needs to be updated to explain the procedure using Mac OS X or Darwin as well.)</span>
 <span style="font-family:courier new,monospace">sudo apt-get update</span>
 <span style="font-family:courier new,monospace">sudo apt-get install build-essential subversion autoconf ruby bison</span>
 <span style="font-family:courier new,monospace">svn co svn://svn.sv.gnu.org/grub/trunk/grub2</span>
 <span style="font-family:courier new,monospace">cd grub2/</span>
 <span style="font-family:courier new,monospace">./autogen.sh</span>
 <span style="font-family:courier new,monospace">./configure --enable-efiemu</span>
 <span style="font-family:courier new,monospace">make</span>
 <span style="font-family:courier new,monospace">sudo make install</span>
 This should install GRUB 2 to /usr/local/bin, from where you can call it to install the boot loader to a disk.
### Installing GRUB 2
Once you have installed GRUB 2 to /usr/local/bin as described above, you need to install it to the disk you want to make bootable.
 <span style="font-family:courier new,monospace">sudo grub-install --root-directory=/media/XXX/ /dev/sdX </span>
 This should give a message like
 <span style="font-family:courier new,monospace">Installation finished. No error reported.</span>
 <span style="font-family:courier new,monospace">This is the contents of the device map /media/disk//boot/grub/device.map.</span>
 <span style="font-family:courier new,monospace">Check if this is correct or not. If any of the lines is incorrect,</span>
 <span style="font-family:courier new,monospace">fix it and re-run the script `grub-install'.</span>
 This has been tested with a FAT32-formatted USB stick. You need to replace <span style="font-family:courier new,monospace">/media/XXX/ </span>with the mountpoint the partition is mounted to, and <span style="font-family:courier new,monospace">/dev/sdX </span>with the device of the USB stick (not the partition). It might be necessary that you flag the partition bootable using cfdisk. <span style="color:rgb(255,0,0)">To be investigated:</span> Can we install this to a HFS+ volume from Ubuntu?
### Booting Darwin with GRUB 2
GRUB 2 lets you control the kernel and extensions to be loaded in a very fine-grained manner. Please refer to the [XNUSupport page of the GRUB wiki](http://grub.enbug.org/XNUSupport) for more detailed information. The following searches all disks for /mach_kernel, and boots it using Extensions.mkext:
 <span style="font-family:courier new,monospace">insmod vbe</span>
 <span style="font-family:courier new,monospace">insmod gfxterm</span>
 <span style="font-family:courier new,monospace">search --set </span><span style="font-family:courier new,monospace">/mach_kernel</span>
 <span style="font-family:courier new,monospace">xnu_kernel /mach_kernel</span>
 <span style="font-family:courier new,monospace">xnu_mkext /System/Library/Extensions.mkext</span>
 <span style="font-family:courier new,monospace">terminal_output gfxterm
 boot</span>
For EFI-based machines
----------------------
GRUB 2 can also be used on EFI-based machines, such as Intel-based Macs.
 The procedure is different from the one described above. Basically, you have to compile GRUB 2 as an EFI module, and place it in
 <span style="font-family:courier new,monospace">/EFI/BOOT/BOOTX64.EFI</span>
 <span style="font-family:courier new,monospace">/EFI/BOOT/BOOTIA32.EFI</span>
 on your disk. When you press the Alt key during boot, your Intel Mac should show the disk as "EFI Boot". See [this thread on the Ubuntu Forums](http://ubuntuforums.org/showpost.php?p=7275427&postcount=762) for more information.
References
----------
-   <http://en.wikipedia.org/wiki/GNU_GRUB>
-   <http://www.gnu.org/software/grub/grub-2.en.html>
-   <http://grub.enbug.org/XNUSupport>
-   <http://ubuntuforums.org/showpost.php?p=7275427&postcount=762>
