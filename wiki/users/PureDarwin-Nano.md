# PureDarwin Nano

This page describes the minimal components needed for a minimal PureDarwin system (also known as "PureDarwin Nano"). 

This system is a **proof-of-concept** of a minimal bootable Darwin 9 system that can be built from the components that Apple provides through the [DarwinBuild](http://darwinbuild.macosforge.org/) project.

[![](https://sites.google.com/a/puredarwin.org/puredarwin/downloads/puredarwin-nano/puredarwin.jpg?attredirects=0)](https://sites.google.com/a/puredarwin.org/puredarwin/downloads/puredarwin-nano/puredarwin.jpg?attredirects=0)

-----

<a name="Download"></a>Download
--------

A ready-made VMware virtual machine containing a minimal Darwin 9 system (PureDarwin nano (based on 9C31)) can be downloaded [here](https://sites.google.com/a/puredarwin.org/puredarwin/downloads).  

    MD5  (puredarwinnano0df46.tbz2) = f6853449e263dd83bba0ac9662f29143
    SHA1 (puredarwinnano0df46.tbz2) = 7a32331fcb443538f0737c172160f3cef6067ec9

The virtual machine contains an ISO that could be used on real hardware as well.

<a name="Components"></a>Components
----------
Here is what such a minimal system needs to consist of:


![](/img/downloads/puredarwin-nano/Bild%202.png)

Notes: [VoodooPS2*](https://github.com/PureDarwin/PureDarwin/wiki/PS2_Controller) or (exclusively) [ACPIPS2Nub.kext](http://code.google.com/p/puredarwin/source/browse/Roots/pd/ACPIPS2Nub.root.tar.gz) and [ApplePS2Controller.kext](http://code.google.com/p/puredarwin/source/browse/Roots/pd/ApplePS2Controller.root.tar.gz) ([sources](http://tgwbd.org/darwin/extensions.html)) are only required if you want to use a PS/2 keyboard and/or mouse.
The number of files can be further brought down by using a [prelinked mach_kernel](https://github.com/PureDarwin/PureDarwin/wiki/XNU,_the_kernel). This removes the need for the System directory.
Using _kextcache_, the boot process can be faster, the image bigger.

### <a name="C-Bootloader"></a>Bootloader

Of course, the system needs to be made bootable by [boot](https://github.com/PureDarwin/PureDarwin/wiki/boot) and/or [efiboot](https://github.com/PureDarwin/PureDarwin/wiki/efiboot). 
Chameleon is reported to work.

### <a name="C-Installer"></a>Installer

An installer is currently being prepared.

### <a name="C-Interactive-mode"></a>Interactive mode

An interactive shell is run by default. In fact, `/sbin/launchd` is replaced by a shell script that runs `/bin/bash`.

![](/img/downloads/puredarwin-nano/bash%20interactive%20mode%20in%20nano.png)

The Z shell (zsh) is also usable as an interactive UNIX command interpreter (shell).

![](/img/downloads/puredarwin-nano/VMware%20running%20PureDarwin%20nano%20with%20interactive%20commands.png)

<a name="Virtual-machine"></a>Virtual machine
---------------
"PureDarwin nano" reported to work with VMware products (Fusion and Player), QEMU and VirtualBox
See [VMware](https://github.com/PureDarwin/PureDarwin/wiki/vmware) page, [QEMU](https://github.com/PureDarwin/PureDarwin/wiki/qemu) page and [VirtualBox](https://github.com/PureDarwin/PureDarwin/wiki/virtualbox) page for more information.

### <a name="VM-VMWarwe"></a>VMware

![](/img/downloads/puredarwin-nano/nanovmwarelittlegray.png)

### <a name="VM-QEMU"></a>QEMU

![](/img/downloads/puredarwin-nano/qemu1.png)