# New PureDarwin 1.3 beta release

Hi everyone. Thanks to the work of rafirafi, there is a new beta release of PureDarwin which is available for testing. This has yet to be completely verified or replicated (rebuilt from source code, and free licenses verified) by anyone else, but it does boot in QEMU and other virtual machines.

Rafirafi has rewritten the remaining binary roots of Darwin 9, including a completely new platform expert called GenericPlatform. He says that there is complete network support including DNS, via his ported E1000 and pcnet32 drivers. It has the latest MacPorts and OpenDirectory. The user's password is 'darwin' and 'sudo' is activated. The documentation for this build is located in the default home directory, which you'll see upon booting. The image is in the form of a qemu qcow2 image, which can be used or converted by various virtual machines.

### Download

Google Drive at 1139081216 bytes: https://docs.google.com/open?id=0B27s590NKd-YVmxBdWZyOGtoN1E

Recompressed at 1036042200 bytes: http://smuckola.org/projects/puredarwin/puredarwin_1.3.0.qcow2.xz

SourceForge: https://sourceforge.net/projects/puredarwin/files/2012/Puredarwin-darwin_9.8-version_9L30.qcow2.xz/download

### Running

I am using the following command for QEMU 1.2.0, installed via MacPorts, on a Mac OS 10.8.0 host.

`qemu-system-i386 -m 1024 -cpu core2duo -vga std -net user -net nic -hda puredarwin_1.3.0.qcow2`

You'll arrive at an X11 display with a terminal window. The user's password is 'darwin', which you'll need for enabling DHCP networking.

`sudo ipconfig set en1 BOOTP`

See the default user's home directory for the source code patches. Use `port sync` instead of `port selfupdate`, because MacPorts has to be patched in order to function, but you can still install the latest packages anyway. Some MacPorts packages (such as python27) require further patches, which are documented on trac.macports.org.

Please come to IRC (#puredarwin at irc.freenode.net, where I'm 'dtm') to discuss your findings and to give rafirafi your thanks!

## Release notes

Date: 25/09/2012

Author: rafirafi

### About this build:

Platform: leopard 9L30

Only i386 architecture

### How to use:

There is an user created with username "puredarwin" and password "darwin", and "root" has the password "rootroot".

Network is tested as working in VirtualBox under Linux with KVM modules patch available on puredarwin.org site, from here you can connect with ssh.

Example of a complete command line:
`kvm -m 512 -cpu host,family=6,model=15 -device VGA,bus=pci.0,addr=0x02 -device rtl8139,mac=54:52:03:04:05:02,vlan=0,bus=pci.0,addr=0x04 -net users,vlan=0 -machine pc,accel=kvm -name PD-XMAS-9L30pd1 -hda /opt/PD-Xmas-9L30pd1.qcow2`

**Edit:** See below for running in VirtualBox.

### What it is:

This is an attempt to have PureDarwin fully compiled from source.

Made with the information publicly available about the PureDarwin project with the maximum of features and developer tools I have been able to include.

- based on 10.5.8 source
- use the last opensource platform expert, only i386

### Packages not coming from 9L30 Apple source with PureDarwin patches:

From rafirafi:
- ClockRTC.kext: Read the date from rtc and provide it to the platform expert
- VMQemuVGA.kext: a framebuffer for the qemu default vga, should be compatible with any card supporting the VBE standard.
- PCNet: an experimental driver for the pcnet32 network card, only version Am79C970A supported. 

From Darwin 8:
- IOATABlockStorage.kext
- IOSCSIArchitectureModelFamily.kext
- AppleAPIC.kext with 8259 support: made standalone in Apple8259PIC.kext
- AppleI386GenericPlatform.kext: hook to ClockRTC added. Add the kernel boot option "platform=PCx86" for compatibility or Apple ACPI platform will be loaded.
- AppleI386PCI.kext
- DarwinTools: provide sw_vers and SystemVersion.plist
- CFNetwork: not so much tested

From BSD:
- logger

From Zenith432 / VMware:
- VMMouse.kext

From Stuart Crook:
- purefoundation
- pam_sessioncreate.so: Cf http://marc.info/?l=launchd-dev&m=123732227520735

From opencflite:
- CF: missing function, essentially Stuart Crook code.

From voodooprojects:
- chameleon: last version building with darwin 9, svn version 2045, need 400M of memory min. to boot.

From macports:
- a macports fresh install of the last version is here (compiled zithout objc and foundation support)
- Xorg is installed for convenience, if you don't want it erase /usr/X* directory and modify .profile file.

From cauldrondevelopment:
- osxbom: for now just lsbom, a reimplementation of the utility of the same name. Here for using with macport binary package.

From hnak:
- AppleIntelE1000.kext : driver for the e1000 netwok family cards (http://osx86drivers.sourceforge.net ), slightly corrected to work with puredarwin.

Others:
- subversion-1.3.2 is in /Users/puredarwin.
- A part of jre from OpenJDK is here with ANTLR 2.7.3.

### Components not working / lacking:

PureFoundation: there are (...) features not implemented, tested. 

Security framework: there is no free CSP, so a lot of features are not ok.
https://opensource.apple.com/source/Security/Security-55163.44/doc/AppleCSP.doc

CFNetwork: not really tested, perhaps it's ok.

CF: the patches are mainly stubs, but it should be possible to implement the features without too much difficulties.

ddistnoted: not here. You can get the binary from the PureDarwin site or ask the author for the source.

Kerberos: depends on plutil. A python module for plist exist so somebody can make a plutil substitute.

### Features with less problems:

Login through pam: this is achieved by creating/recreating the pam_sessioncreate.so module following the Stuart mail from http://lists.macosforge.org/pipermail/launchd-dev/2009-March.txt

Multi-users: you can use the script from PureDarwin site

DTrace: the dtrace patch interfers with dyld build, so I patched ld64 but dtrace functionalities were not tested after this patch.

You can see a message at boot: "InterfaceNamer: no network interfaces" => it just means the interface is not built-in, so not used to generate uuid platform.

Only a framebuffer for QEMU/VirtualBox is here, it's based on VBE features only iirc, so nothing hardware specific.

There is a driver made by zenith432 VMWare Svga II which should provide support for VMWare.

### What's been done:

A lot of patches.
But there is a lot of patch to build only i386.

### What I think could be solved:

The patch available for CF pf6 is not OK, and some feature were backported from CF-550 or opencflite.
There is no reconstructed headers/headers based on the doc, so they couldn't be included. But compilation against PureFoundation in PureDarwin is fine and shows you immediately what symbols are lacking.

The PureFoundation r30 needs minor corrections to be built in darwinbuild and have all the symbol defined (link to libffi...), notably the Foundation headers can be self-contained easily.

Python and Tcl needs additional patches to build completely in darwinbuild.

X: re-enable XDarwin feature.

### What will be very difficult to solve:

There is no open source CSP, perhaps it's possible to use OpenSSL...

Xcode dependency: it means porting every project to use a Makefile...

### Running with VirtualBox

To run this on a Ubuntu i386 (32-bit) box with VirtualBox, do

```
sudo apt-get -y install qemu-utils
xz -v -d -k Puredarwin-darwin_9.8-version_9L30.qcow2.xz
qemu-img convert -O vdi /Puredarwin-darwin_9.8-version_9L30.qcow2 Puredarwin-darwin_9.8-version_9L30.vdi

VBoxManage createvm -name PD -ostype MacOS -basefolder . -register
VBoxManage modifyvm PD --cpus 1
VBoxManage modifyvm PD --pae on
VBoxManage modifyvm PD --acpi on --ioapic on
VBoxManage modifyvm PD --memory 512
VBoxManage modifyvm PD --usb off
VBoxManage modifyvm PD --chipset piix3 # ich9 is only for their UEFI implementation
VBoxManage modifyvm PD --firmware bios
VBoxManage storagectl PD --name "IDE Controller" --add ide --controller ICH6  --bootable on
VBoxManage storageattach PD --storagectl "IDE Controller" --port 0  --type hdd --device 0 --medium Puredarwin-darwin_9.8-version_9L30.vdi 
VBoxManage modifyvm PD --natpf1 "guestssh,tcp,,2222,,22" # ssh 127.0.0.1:2222
VBoxManage startvm PD
```

### Use it

```
rm /Library/Preferences/SystemConfiguration/NetworkInterfaces.plist 
rm /Library/Preferences/SystemConfiguration/com.apple.network.identification.plist
reboot
```

Should give a new NetworkInterfaces.plist and should get an IP address via DHCP from VirtualBox

```
sudo /usr/sbin/sshd

sudo ipconfig set en0 BOOTP
sudo ipconfig set en0 DHCP
```

Crashes if ich9 is set instead of piix3
