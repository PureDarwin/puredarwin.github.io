New PureDarwin 1.3 beta release
===============================

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Download](newpuredarwin9l30betarelease.html#TOC-Download)
    1.  [**1.1** Running](newpuredarwin9l30betarelease.html#TOC-Running)
    2.  [**1.2** Release notes](newpuredarwin9l30betarelease.html#TOC-Release-notes)
2.  [**2** Running with VirtualBox](newpuredarwin9l30betarelease.html#TOC-Running-with-VirtualBox)


Hi everyone.  Due completely to the work of rafirafi, there is a new beta release of PureDarwin which is available for testing.  This has yet to be completely verified or replicated (rebuilt from source code, and free licenses verified) by anyone else, but it does boot in qemu and in other virtual machines.

Rafirafi has rewritten the remaining binary roots of Darwin 9, including a completely new platform expert called GenericPlatform.  He says that there is complete network support including DNS, via his ported E1000 and pcnet32 drivers.  It has the latest MacPorts and OpenDirectory.  The user's password is 'darwin' and 'sudo' is activated.  The documentation for this build is located in the default home directory, which you'll see upon booting.  The image is in the form of a qemu qcow2 image, which can be used or converted by various virtual machines.
### Download
Here it is for download:

http://www.secrettoeverybody.com/

Just kidding.  Here is a fast download from Google at 1139081216 bytes:

https://docs.google.com/open?id=0B27s590NKd-YVmxBdWZyOGtoN1E

Here's the same file which I recompressed at 1036042200 bytes for those who need fewer bytes, but which should also be fast:

http://smuckola.org/projects/puredarwin/puredarwin_1.3.0.qcow2.xz

**Edit:** fast mirrors at <http://sourceforge.net/projects/puredarwin/files/2012/Puredarwin-darwin_9.8-version_9L30.qcow2.xz/download>
### Running
I am using the following command for qemu 1.2.0, installed via MacPorts, on a Mac OS 10.8.0 host.

qemu-system-i386 -m 1024 -cpu core2duo -vga std -net user -net nic -hda puredarwin_1.3.0.qcow2

You'll arrive at an X11 display with a terminal window.  The user's password is 'darwin', which you'll need for enabling DHCP networking.

sudo ipconfig set en1 BOOTP
<span style="font-family:arial,helvetica,sans-serif">
</span>
<span style="font-family:arial,helvetica,sans-serif">See the default user's home directory for the source code patches.  Use 'port sync' instead of 'port selfupdate', because MacPorts has to be patched in order to function, but you can still install the latest packages anyway.  Some MacPorts packages (such as python27) require further patches, which are documented on trac.macports.org.</span>

Please come to IRC (#puredarwin at irc.freenode.net, where I'm 'dtm') to discuss your findings and to give rafirafi your thanks!

### Release notes
Date : 25/09/2012
Author : rafirafi

<span style="white-space:pre"> </span>About this build :

platform : leopard 9L30
only i386 architecture

<span style="white-space:pre"> </span>How to use:
<span style="white-space:pre"> </span>
There is an user created "puredarwin" with passworg "darwin", "root" have password "rootroot"
Network is tested as working in virtualbox and linux with kvm modules patch available on puredarwin.org site, from here you can connect with ssh.

Example of a complete command line :
kvm -m 512 -cpu host,family=6,model=15 -device VGA,bus=pci.0,addr=0x02 -device rtl8139,mac=54:52:03:04:05:02,vlan=0,bus=pci.0,addr=0x04 -net users,vlan=0 -machine pc,accel=kvm  -name ***PD-XMAS-9L30pd1*** -hda /opt/PD-Xmas-9L30pd1.qcow2

**Edit:** See below for running in VirtualBox.

<span style="white-space:pre"> </span>What it is :

This is an attempt to have a puredarwin without binaries.

 made with the information publicly available about the puredarwin project with the maximum of features and developer tools I have been abble to include.
What news / puredarwin Xmas :
<span style="white-space:pre"> </span>- based on 10.5.8 source
<span style="white-space:pre"> </span>- use the last opensource platform expert, only i386


<span style="white-space:pre"> </span>Shipped but not built :

openjdk and antlr : here in case someone want to built openjdk

<span style="white-space:pre"> </span>Packages not coming from 9L30 apple source with puredarwin patches:

From rafirafi :
<span style="white-space:pre"> </span>ClockRTC.kext : Read the date from rtc and provide it to the platform expert
<span style="white-space:pre"> </span>VMQemuVGA.kext : a framebuffer for the qemu default vga, should be compatible with any card supporting the VBE standard.
<span style="white-space:pre"> </span>PCNet : an experimental driver for the pcnet32 network card, only version Am79C970A supported. 
From darwin 8:
<span style="white-space:pre"> </span>IOATABlockStorage.kext
<span style="white-space:pre"> </span>IOSCSIArchitectureModelFamily.kext
<span style="white-space:pre"> </span>AppleAPIC.kext with 8259 support : made standalone in Apple8259PIC.kext
<span style="white-space:pre"> </span>AppleI386GenericPlatform.kext : hook to ClockRTC added. Add the kernel boot option "platform=PCx86" for compatibility or Apple ACPI platform will be loaded.
<span style="white-space:pre"> </span>AppleI386PCI.kext
<span style="white-space:pre"> </span>DarwinTools : provide sw_vers and SystemVersion.plist
<span style="white-space:pre"> </span>CFNetwork : not so much tested
From BSD:
<span style="white-space:pre"> </span>logger
From Zenith432 / VMware:
<span style="white-space:pre"> </span>VMMouse.kext
From Stuart Crook:
<span style="white-space:pre"> </span>purefoundation
<span style="white-space:pre"> </span>pam_sessioncreate.so : Cf http://marc.info/?l=launchd-dev&m=123732227520735
From opencflite:
<span style="white-space:pre"> </span>CF : missing function, essentially Stuart Crook code.
From voodooprojects :
<span style="white-space:pre"> </span>chameleon : last version building with darwin 9, svn version 2045, need 400M of memory min. to boot.
From macports :
<span style="white-space:pre"> </span>a macports fresh install of the last version is here (compiled zithout objc and foundation support)
<span style="white-space:pre"> </span>a keep a Xorg installed for convenience, if you dont zant it erase /usr/X* directory and modify .profile file.
From cauldrondevelopement:
<span style="white-space:pre"> </span>osxbom : for now just lsbom, a reimplementation of the utility of the same name. Here for using with macport binary package.
From hnak:
<span style="white-space:pre"> </span>AppleIntelE1000.kext : driver for the e1000 netwok family cards (http://osx86drivers.sourceforge.net ), slightly corrected to work with puredarwin.

Others:
<span style="white-space:pre"> </span>subversion-1.3.2 is in /Users/puredarwin.
<span style="white-space:pre"> </span>A part of jre from openjdk is here with antlr 2.7.3.
<span style="white-space:pre"> </span>

<span style="white-space:pre"> </span>Components not working / lacking :

PureFoundation : there are (...) features not implemented, tested. 

Security framework : there is no free CSP, so a lot of features are not ok.
<span style="white-space:pre"> </span>www.opensource.apple.com/source/Security/Security-55163.44/doc/AppleCSP.doc

CFNetwork : not really tested, perhaps it's ok.

CF: the patches are mainly stubs, but it should be possible to implement the features without too much difficulties.

ddistnoted: not here. you can get the binary from puredarwin site or ask the author for the source.

Kerberos : depends on plutil. A python module for plist exist so somebody can make a plutil substitute.


<span style="white-space:pre"> </span>Features with less problems:

Login throught pam:
this is achieve by creating/recreating the pam_sessioncreate.so module foolowing the Stuart mail from:
http://lists.macosforge.org/pipermail/launchd-dev/2009-March.txt

Multi-users : you can use the script from puredarwin site

DTrace:
The dtrace patch interfers which dyld buily, so I patched ld64 but dtrace functionnalities were not tested after this patch.

<span style="white-space:pre"> </span>Features with less problem:

Network:
You can see a message at boot:
 "InterfaceNamer: no network interfaces"
=&gt; it just means the interface is not built-in, so not used to generqte uuid platform.

Graphics :
Only a framebuffer for qemu/virtualbox is here, it's based on VBE features only iirc, so nothing hardware specific.

There is a driver made by zenith432 VMWare Svga II which should provide support for vmware.

<span style="white-space:pre"> </span>What's been done :

A lot of patches.
But there is a lot of patch to build only i386.

<span style="white-space:pre"> </span>What I think could be solve :

CF - purefoundation : 
The patch available for CF pf6 is not ok, and some feature were backported from CF-550 or opencflite.
There is no reconstructed headers/headers based on the doc, so they couldn't be included. But compilation against purefoundation in puredarwin is fine and show you immediatly what symbols are lacking...

The purefoundation r30 needs minor corrections to built in darwinbuild and have all the symbol defined (link to libffi...), notably the Foundation headers can be self-contained easily.

Python and Tcl needs additionnal patches to build completly in darwinbuild.

X : re-enable XDarwin feature.


<span style="white-space:pre"> </span>What will be very difficult to solve :

Security :
there is no opensource CSP, perhaps it's possible to use openssl...

XCode dependency :
It means porting every project to use a Makefile...

Running with VirtualBox
-----------------------
To run this on a Ubuntu i386 (32-bit) box with VirtualBox, do


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

# ... use it ...

rm /Library/Preferences/SystemConfiguration/NetworkInterfaces.plist 
rm /Library/Preferences/SystemConfiguration/com.apple.network.identification.plist
reboot
# Should give me a new NetworkInterfaces.plist 
# and should get an IP address via DHCP from VirtualBox
sudo /usr/sbin/sshd

sudo ipconfig set en0 BOOTP
sudo ipconfig set en0 DHCP
# Crashes if ich9 is set instead of piix3

VBoxManage controlvm PD poweroff


