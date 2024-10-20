VirtualBox
==========

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/oraclevirtualbox.png)

Status
------
2011 Jan 14 news:

- PureDarwin Nano + Xmas run in 
    - VirtualBox 4 on ubuntu

- PureDarwin Nano runs with 
    - VirtualBox 4 on Windows
    - VirtualBox 3.2 on Snow Leopard

older news:

- PureDarwin Nano runs in VirtualBox 3
    - on Mac OS X
    - on Windows XP 32 bits

PureDarwin Nano
---------------
VirtualBox 4 is able to run [PureDarwin Nano](https://github.com/PureDarwin/PureDarwin/wiki/PureDarwin-Nano)

- on Linux
    - details of the linux test system:
        - host: ubuntu 10.10 2.6.35-24-generic #42-Ubuntu SMP Thu Dec 2 02:41:37 UTC 2010 x86_64 GNU/Linux
        - VirtualBox 4.0.0 r69151
        - PureDarwin Nano: with PureDarwin.local 9.5.0 Darwin Kernel Version 9.5.0: Sat Dec 6 19:39:54 IST 2008; Voodoo; Release 1.0 :xnu-1228.7.58/BUILD/obj/RELEASE_I386 i386
    - please use following settings in VirtualBox
        - Systems > Motherboard
            - Chipset ICH9
            - enable IO APIC
            - enable EFI
        - Systems > Processor: enable PAE/NX
        - Systems > Acceleration
            - enable VT-x/AMD-V
            - enable nested paging
- on Windows
    - VirtualBox 4.0.0 under Windows 7 x86-64, when using the "Red Hat Linux", VT-X, Nested paging and IO APIC

VirtualBox 3
- MacOS
    - VirtualBox 3.0.2 on Mac OS X
    - VirtualBox 3.2.12 r68302 on Snow Leopard 10.6.6, x86_64 kernel
- Windows
    - VirtualBox 3.0.6 on Windows XP 32 bits

PureDarwin Xmas
---------------

VirtualBox 4 is able to run [PureDarwin Xmas](https://github.com/PureDarwin/PureDarwin/wiki/Xmas)
- on Linux
    - details of the linux test system:
        - host: ubuntu 10.10 2.6.35-24-generic #42-Ubuntu SMP Thu Dec 2 02:41:37 UTC 2010 x86_64 GNU/Linux
        - VirtualBox 4.0.0 r69151
        - PureDarwin Nano: with PureDarwin.local 9.5.0 Darwin Kernel Version 9.5.0: Sat Dec 6 19:39:54 IST 2008; Voodoo; Release 1.0 :xnu-1228.7.58/BUILD/obj/RELEASE_I386 i386
    - please use following settings in VirtualBox</span>
        - Systems > Motherboard
            - Chipset ICH9
            - enable IO APIC
        - Systems > Processor: enable PAE/NX
        - Systems > Acceleration
            - enable VT-x/AMD-V
            - enable nested paging
    - add PureDarwin Nano as CDrom + select after F8 the Xmas HD and start with Graphics mode = 1024x768x16

Screenshots of PureDarwin Xmas
------------------------------
Ubuntu + VirtualBox 4

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/PD_Xmas_2_VBox4_ubuntu_2011Jan14.png)

Screenshots of PureDarwin nano
------------------------------
Ubuntu + VirtualBox 4

[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/Nano_VBox_ubuntu_2011Jan_14.png)](virtualbox/Nano_VBox_ubuntu_2011Jan_14.png%3Fattredirects=0)


### Using boot.efi in VirtualBox
EFI emulation in VirtualBox 4 is capable of loading and executing boot.efi as the bootloader. Hence boot-132 or its derivatives are no longer needed in VirtualBox. We were able to boot PureDarwinNano.iso this way.


[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/boot.efi.png)](booting/efiboot/boot.efi.png%3Fattredirects=0)

The code responsible for loading boot.efi can be seen [here](http://www.virtualbox.org/svn/vbox/trunk/src/VBox/Devices/EFI/Firmware2/VBoxPkg/Library/VBoxGenericBdsLib/BdsBoot.c). Apparently VirtualBox includes an EFI implementation based on TianoCore EDK2, with [special patches](http://www.virtualbox.org/svn/vbox/trunk/src/VBox/Devices/EFI/Firmware2/VBoxPkg/edk2.patch-apple) to boot Mac OS X Server (and hence, Darwin).

Screenshots of VirtualBox 4 settings
------------------------------------

PureDarwin: Ubuntu + VirtualBox 4

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/VBox4_ubuntu_2011Jan14_v2.png)


PureDarwin: Windows + VirtualBox 4

[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/VBox4_windows_2011Jan14.png)](virtualbox/VBox4_windows_2011Jan14.png%3Fattredirects=0)




See also
--------

-   "[VirtualBox 3.2 supports Mac OS X guests out-of-the-box](http://forums.virtualbox.org/viewtopic.php?t=2076)"
-   [http://www.puredarwin.org/virtualbox-archive](../virtualbox-archive.html)



