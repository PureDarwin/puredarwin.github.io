# Release: PureDarwin 17.4 Test Build for Developers

July 1, 2018 - _Clifford Sekel_

![Test Build 17.4 Based on Darwin 17](/img/news/2024/news-cover-17-4-test.jpg)

### Download 

* This Test Build can be downloaded from here [PD-Devs](https://www.pd-devs.org/Beta/pd_17_4.vmdk.xz) (vmdk).

### VMDK

* To run this, first extract the image with `xz` (`xz -d pd_17_4.vmdk.xz`).

* Then, start the VMDK with QEMU: `qemu-system-x86_64 -m 8192 -cpu Penryn -smp 2  -netdev user,id=network0 -device rtl8139,netdev=network0 -serial stdio -drive format=vmdk,file=pd_17_4.vmdk`

### ISO 

* To run this, first extract the image with `xz` (`xz -d pd_17_4.vmdk.xz`).

* Then convert to VDMK to ISO `qemu-img convert -f vmdk pd_17_4.vmdk -O raw pd_17_4.iso`.

* Then, start the ISO with QEMU: `qemu-system-x86_64 -m 8192 -cpu Penryn -smp 2  -netdev user,id=network0 -device rtl8139,netdev=network0 -serial stdio -drive format=raw,file=pd_17_4.iso`

## Notes

* This is not a full OS like PureDarwin Xmas was, as Apple have closed down a lot of core components, we the community have to pick up the slack. 

* There is still a lot of work to be done but it can be completed if we band together. If you would like to view what's on this VM please use Paragon VMDK mounter for macOS users, all other please see what you need to do to mount and read an hfs filesystem on your OS. You may also use this `qemu-img convert -f vmdk pd_17_4.vmdk -O raw pd_17_4.iso`

* Please do not ask us questions on how to run macOS applications and non-open source software on PureDarwin. If you want something to hack on, then this is it.

* We have not finished all the system/network_cmds. We built as much as we could without pulling headers from Apple's Xcode SDK's.

## Projects 

[Libxpc/Launchd](https://github.com/PureDarwin/launchd-and-libxpc)

[PureFoundation](https://github.com/PureDarwin/PureFoundation)

[CoreFoundation](https://github.com/PureDarwin/CoreFoundation)

[ddisnoted](https://github.com/PureDarwin/ddistnoted)

[DarwinBuild](https://github.com/PureDarwin/DarwinBuild)

[Enoch Bootloader](http://forge.voodooprojects.org/p/chameleon/source/tree/HEAD/branches/ErmaC/Enoch)

## To Do

* Finish out Family Driver Support(USB/SATA/NVME/AHCI/PD-APCIPlatform)
* Finish out System Commands(Reboot/Shutdown)
* Finish out the Networking
* Finish out the Multi-User

## Credits
We would like to thank:

* Apple, Inc. for releasing Darwin as Open Source 
* David Elliott for his work on boot-132
* The Chameleon team for their work on boot-132
* The xnu-dev team for their work on the XNU kernel
* Stuart Crook for his work on PureFoundation, ddisnoted and libxpc/launchd work
* Ethan Sheriff for his work on the libsystem-plaform and libxpc/launchd work
* William Kent for his work on the DarwinBuild upgrade 
* Rafirafi for his work on Generic Platform and PDCrypto kexts
* Mac OS Forge for The DarwinBuild project 

## Contact Us!

[![PureDarwin Discord](https://dcbadge.limes.pink/api/server/https://discord.gg/9kz8XXRRcT?style=flat)](https://discord.gg/9kz8XXRRcT)

### Admins

* Ferdinand Klinzer - bart@pd-devs.org
* Clifford Sekel - insanedarwin@pd-devs.org

### Core Dev’s

* Avi Saven - avisaven@pd-devs.org
* Ethan Sherriff - libsystem_ethan@pd-devs.org
* Stuart Cook - sjc@pd-devs.org
* William Kent - wjk@pd-devs.org
