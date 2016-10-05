VirtualBox
==========

![](../_/rsrc/1295181212811/developers/virtualbox/oraclevirtualbox.png)
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:444px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Status](virtualbox.html#TOC-Status)
2.  [**2** PureDarwin Nano](virtualbox.html#TOC-PureDarwin-Nano)
3.  [**3** PureDarwin Xmas](virtualbox.html#TOC-PureDarwin-Xmas)
4.  [**4** Screenshots of PureDarwin Xmas](virtualbox.html#TOC-Screenshots-of-PureDarwin-Xmas)
5.  [**5** Ubuntu + Virtual Box 4](virtualbox.html#TOC-Ubuntu-Virtual-Box-4)
6.  [**6** Screenshots of PureDarwin nano](virtualbox.html#TOC-Screenshots-of-PureDarwin-nano)
    1.  [**6.1** Using boot.efi in VirtualBox](virtualbox.html#TOC-Using-boot.efi-in-VirtualBox)
7.  [**7** Screenshots of VirtualBox 4 settings](virtualbox.html#TOC-Screenshots-of-VirtualBox-4-settings)
8.  [**8** See also](virtualbox.html#TOC-See-also)

Status
------
2011 Jan 14 news: 
PureDarwin Nano + Xmas run in 
-   VirtualBox 4 on ubuntu
PureDarwin Nano runs with 
-   VirtualBox 4 on Windows
-   VirtualBox 3.2 on Snow Leopard
<span style="font-family:sans-serif;line-height:20px">older news:</span>
<span style="font-family:sans-serif;line-height:20px"><span style="font-family:Arial,Verdana,sans-serif;line-height:normal"></span></span>
PureDarwin Nano runs in VirtualBox 3 
-   on Mac OS X
<!-- -->
-   on Windows XP 32 bits
<span style="font-family:sans-serif;line-height:20px"><span style="font-family:Arial,Verdana,sans-serif;line-height:normal"></span></span>
PureDarwin Nano
---------------
<span style="font-family:sans-serif;line-height:20px">Virtual Box 4 is able to run [PureDarwin Nano](../downloads/puredarwin-nano.html)</span>
on Linux
details of the linux test system:
-   host: ubuntu 10.10 2.6.35-24-generic #42-Ubuntu SMP Thu Dec 2 02:41:37 UTC 2010 x86_64 GNU/Linux
-   <span style="line-height:19px">Virtual Box 4.0.0 r69151</span>
-   <span style="line-height:19px">PureDarwin Nano: with PureDarwin.local 9.5.0 Darwin Kernel Version 9.5.0: Sat Dec 6 19:39:54 IST 2008; Voodoo; Release 1.0 :xnu-1228.7.58/BUILD/obj/RELEASE_I386 i386</span>
<span style="line-height:19px">please use following settings in VirtualBox</span>
<span style="line-height:19px">Systems &gt; </span><span style="font-family:sans-serif;line-height:19px">Motherboard</span>
-   <span style="font-family:sans-serif;line-height:19px">Chipset ICH9</span>
-   <span style="font-family:sans-serif;line-height:19px">enable IO APIC</span>
-   <span style="line-height:19px">enable EFI</span>
<span style="line-height:19px">Systems &gt; Processor: enable PAE/NX</span>
<span style="line-height:19px">Systems &gt; Acceleration</span>
-   <span style="line-height:19px">enable VT-x/AMD-V</span>
-   <span style="line-height:19px">enable nested paging</span>
<span style="line-height:19px">on Windows</span>
-   <span style="line-height:19px"> VirtualBox 4.0.0 under Windows 7 x86-64, when using the "Red Hat Linux", VT-X, Nested paging and IO APIC</span>

<span style="font-family:sans-serif;line-height:20px">Virtual Box 3 </span>
MacOS
-   VirtualBox 3.0.2 on Mac OS X
-   VirtualBox 3.2.12 r68302 on Snow Leopard 10.6.6, x86_64 kernel
Windows
-   VirtualBox 3.0.6 on Windows XP 32 bits
PureDarwin Xmas
---------------

<span style="font-family:sans-serif;line-height:20px">Virtual Box 4 is able to run [PureDarwin Xmas](../downloads/xmas.html)</span>
on Linux
details of the linux test system:
-   host: ubuntu 10.10 2.6.35-24-generic #42-Ubuntu SMP Thu Dec 2 02:41:37 UTC 2010 x86_64 GNU/Linux
-   <span style="line-height:19px">Virtual Box 4.0.0 r69151</span>
-   <span style="line-height:19px">PureDarwin Nano: with PureDarwin.local 9.5.0 Darwin Kernel Version 9.5.0: Sat Dec 6 19:39:54 IST 2008; Voodoo; Release 1.0 :xnu-1228.7.58/BUILD/obj/RELEASE_I386 i386</span>
<span style="line-height:19px">please use following settings in VirtualBox</span>
<span style="line-height:19px">Systems &gt; </span><span style="font-family:sans-serif;line-height:19px">Motherboard</span>
-   <span style="font-family:sans-serif;line-height:19px">Chipset ICH9</span>
-   <span style="font-family:sans-serif;line-height:19px">enable IO APIC</span>
<span style="line-height:19px">Systems &gt; Processor: enable PAE/NX</span>
<span style="line-height:19px">Systems &gt; Acceleration</span>
-   <span style="line-height:19px">enable VT-x/AMD-V</span>
-   <span style="line-height:19px">enable nested paging</span>
<span style="line-height:19px">add PureDarwin Nano as CDrom + select after F8 the Xmas HD and start with Graphics mode = 1024x768x16</span>

Screenshots of PureDarwin Xmas
------------------------------
<span style="font-weight:normal"><span style="font-family:sans-serif;font-size:13px;line-height:20px">Ubuntu + Virtual Box 4</span></span>
------------------------------------------------------------------------------------------------------------------------------------------
<span style="font-weight:normal;font-size:medium"></span>
[![](../_/rsrc/1295046673709/developers/virtualbox/PD_Xmas_2_VBox4_ubuntu_2011Jan14.png)](virtualbox/PD_Xmas_2_VBox4_ubuntu_2011Jan14.png%3Fattredirects=0)

<span style="font-weight:normal;font-size:medium">
</span>
Screenshots of PureDarwin nano
------------------------------
<span style="font-size:medium">Ubuntu + VirtualBox4</span>
<span style="font-size:medium">
</span>
<span style="font-size:medium"></span>
[![](../_/rsrc/1295039743303/developers/virtualbox/Nano_VBox_ubuntu_2011Jan_14.png%3Fheight=241&width=320)](virtualbox/Nano_VBox_ubuntu_2011Jan_14.png%3Fattredirects=0)


### Using boot.efi in VirtualBox
EFI emulation in VirtualBox 4 is capable of loading and executing boot.efi as the bootloader. Hence boot-132 or its derivatives are no longer needed in VirtualBox. We were able to boot PureDarwinNano.iso this way.


[![](../_/rsrc/1295181011428/developers/booting/efiboot/boot.efi.png)](booting/efiboot/boot.efi.png%3Fattredirects=0)


The code responsible for loading boot.efi can be seen [here](http://www.virtualbox.org/svn/vbox/trunk/src/VBox/Devices/EFI/Firmware2/VBoxPkg/Library/VBoxGenericBdsLib/BdsBoot.c). Apparently VirtualBox includes an EFI implementation based on TianoCore EDK2, with [special patches](http://www.virtualbox.org/svn/vbox/trunk/src/VBox/Devices/EFI/Firmware2/VBoxPkg/edk2.patch-apple) to boot Mac OS X Server (and hence, Darwin).
Screenshots of VirtualBox 4 settings
------------------------------------

PureDarwin: Ubuntu + VirtualBox4

[![](../_/rsrc/1295039174419/developers/virtualbox/VBox4_ubuntu_2011Jan14_v2.png)](virtualbox/VBox4_ubuntu_2011Jan14_v2.png%3Fattredirects=0)


PureDarwin: Windows + VirtualBox4

[![](../_/rsrc/1295039199181/developers/virtualbox/VBox4_windows_2011Jan14.png)](virtualbox/VBox4_windows_2011Jan14.png%3Fattredirects=0)




See also
--------

-   "[VirtualBox 3.2 supports Mac OS X guests out-of-the-box](http://forums.virtualbox.org/viewtopic.php?t=2076)"
-   [http://www.puredarwin.org/virtualbox-archive](../virtualbox-archive.html)



