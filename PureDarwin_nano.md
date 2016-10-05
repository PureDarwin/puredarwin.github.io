PureDarwin nano
===============

This page describes the minimal components needed for a minimal PureDarwin system (also known as "PureDarwin nano"). 

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:300px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Download](puredarwin-nano.html#TOC-Download)
2.  [**2** Components](puredarwin-nano.html#TOC-Components)
    1.  [**2.1** Bootloader](puredarwin-nano.html#TOC-Bootloader)
    2.  [**2.2** Installer](puredarwin-nano.html#TOC-Installer)
    3.  [**2.3** Interactive mode](puredarwin-nano.html#TOC-Interactive-mode)
3.  [**3** Virtual machine](puredarwin-nano.html#TOC-Virtual-machine)
    1.  [**3.1** VMware](puredarwin-nano.html#TOC-VMware)
    2.  [**3.2** QEMU](puredarwin-nano.html#TOC-QEMU)

This system is a <span style="font-weight:bold">proof-of-concept</span> of a minimal bootable Darwin 9 system that can be built from the components that Apple provides through the [DarwinBuild](http://darwinbuild.macosforge.org/) project.

[![](../_/rsrc/1234090957898/downloads/puredarwin-nano/puredarwin.jpg)](puredarwin-nano/puredarwin.jpg%3Fattredirects=0)
Download
--------
A ready-made VMware virtual machine containing a minimal Darwin 9 system (PureDarwin nano (based on 9C31)) can be downloaded [here](../downloads.html).
<span style="font-family:courier new,monospace;font-size:small">MD5 (puredarwinnano0df46.tbz2) = f6853449e263dd83bba0ac9662f29143</span>
<span style="font-size:small">SHA1 (puredarwinnano0df46.tbz2) = 7a32331fcb443538f0737c172160f3cef6067ec9</span>
<span style="font-size:small">
</span>
<span style="font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:13px"></span></span>
The virtual machine contains an ISO that could be used on real hardware as well.
Components
----------
Here is what such a minimal system needs to consist of:


[![](../_/rsrc/1234090957898/downloads/puredarwin-nano/Bild%202.png)](puredarwin-nano/Bild%202.png%3Fattredirects=0)


<span style="text-decoration:underline">Notes:</span> [VoodooPS2*](../developers/xnu/ps2-controller.html) or (exclusively) [ACPIPS2Nub.kext](http://code.google.com/p/puredarwin/source/browse/Roots/pd/ACPIPS2Nub.root.tar.gz) and [ApplePS2Controller.kext](http://code.google.com/p/puredarwin/source/browse/Roots/pd/ApplePS2Controller.root.tar.gz) ([sources](http://tgwbd.org/darwin/extensions.html)) are only required if you want to use a PS/2 keyboard and/or mouse.
The number of files can be further brought down by using a [prelinked mach_kernel](../developers/xnu.1.html). This removes the need for the System directory.
Using <span style="font-style:italic">kextcache</span>, the boot process can be faster, the image bigger.
### Bootloader
Of course, the system needs to be made bootable by [boot](../developers/booting/boot.html) and/or [efiboot](../developers/booting/efiboot.html). 
Chameleon is reported to work.
### Installer
An installer is currently being prepared.
### Interactive mode
An interactive shell is run by default. In fact, <span style="font-family:courier new,monospace"><span style="font-size:small">/sbin/launchd</span></span> is replaced by a shell script that runs <span style="font-family:courier new,monospace"><span style="font-size:small">/bin/bash</span></span>


[![](../_/rsrc/1234090957898/downloads/puredarwin-nano/bash%20interactive%20mode%20in%20nano.png)](puredarwin-nano/bash%20interactive%20mode%20in%20nano.png%3Fattredirects=0)

The Z shell (zsh) is also usable as an interactive UNIX command interpreter (shell).


[![](../_/rsrc/1234090957898/downloads/puredarwin-nano/VMware%20running%20PureDarwin%20nano%20with%20interactive%20commands.png)](puredarwin-nano/VMware%20running%20PureDarwin%20nano%20with%20interactive%20commands.png%3Fattredirects=0)

Virtual machine
---------------
"PureDarwin nano" reported to work with VMware products (Fusion and Player), QEMU and VirtualBox
See [VMware](../developers/vmware.html) page, [QEMU](../developers/qemu.html) page and [VirtualBox](../developers/virtualbox.html) page for more information.
### VMware
<span style="color:rgb(0,102,204)">[![](../_/rsrc/1234090957898/downloads/puredarwin-nano/nanovmwarelittlegray.png)](puredarwin-nano/nanovmwarelittlegray.png%3Fattredirects=0)</span>
### QEMU

[](puredarwin-nano/qemu%20running%20nano.png%3Fattredirects=0)
[![](../_/rsrc/1254082132956/downloads/puredarwin-nano/qemu1.png%3Fheight=321&width=420)](puredarwin-nano/qemu1.png%3Fattredirects=0)


