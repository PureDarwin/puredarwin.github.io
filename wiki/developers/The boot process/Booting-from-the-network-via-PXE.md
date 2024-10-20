Booting from the network via PXE
================================

There are now at least 2 known working ways to get forked versions of boot-132 running via PXE. This page describes the two approaches and provides scripts for you to try it out yourself.

Note that right now this page ends where boot-132 is loaded; the rest can be read on [DFE's blog](http://tgwbd.org/blog/2009/10/17/be-free-little-pxes-be-free/).

### Booting PureDarwin with a PXE-enabled boot-132

Apparently DFE has written the missing Darwin/x86 first-stage network boot program (NBP), a first-stage loader for boot-132.

Basically, booting PureDarwin over the network involves the following steps:

1.  Client network card firmware asks DHCP server
2.  DHCP server asks dnsmasq on the server
3.  dnsmasq sends TFTP information
4.  Client network card firmware downloads boot1pxe.0 file specified by dnsmasq from dnsmasq
5.  boot1pxe.0 loads boot (boot-132) (known to work up to this point)
6.  boot-132 loads mach_kernel and Extensions.mkext from the server (still to be implemented)
7.  mach_kernel loads network kext and uses it to load the root volume from the network (still to be implemented)
8.  Root volume image detects that it is booted via the network and sets up ramdisks etc. as needed (like on Mac OS X network boot)
You can try this variant by:
1.  Run Ubuntu 9.10 Live CD (we are using this as the server for now; later we could use PureDarwin as the server)
2.  `wget "http://sites.google.com/a/puredarwin.org/puredarwin/developers/booting/boot/pxe/boot-boot1pxe.bash?attredirects=0&d=1" -O ./boot-boot1pxe.bash ; sudo bash ./boot-boot1pxe.bash`

### Booting PureDarwin via Chameleon via mboot.c32 via pxelinux via PXE

Another route is [pxelinux](http://syslinux.zytor.com/wiki/index.php/PXELINUX) which can boot multiboot kernels via PXE. Since mach_kernel itself is not a multiboot-compliant kernel, we need to use a multiboot-compliant fork of boot-132 (such as Chameleon), and load it with the [mboot.c32](http://syslinux.zytor.com/wiki/index.php/Mboot.c32) pxelinux plug-in.

Basically, booting PureDarwin over the network involves the following steps:

1.  Client network card firmware asks DHCP server
2.  DHCP server asks dnsmasq on the server
3.  dnsmasq sends TFTP information
4.  Client network card firmware downloads pxelinux.0 file specified by dnsmasq from dnsmasq
5.  pxelinux downloads its configuration
6.  pxelinux loads mboot.c32 which is a multiboot loader
7.  mboot.c32 loads boot which is a multiboot-compliant version of boot-132 such as Chameleon (known to work up to this point)
8.  boot-132 loads mach_kernel and Extensions.mkext from a supplied ramdisk (still to be implemented)
9.  mach_kernel loads network kext and uses it to load the root volume from the network (still to be implemented)
10. Root volume image detects that it is booted via the network and sets up ramdisks etc. as needed (like on Mac OS X network boot)
You can try this variant by:
1.  Run Ubuntu 9.10 Live CD (we are using this as the server; later we could use PureDarwin as the server)
2.  `wget "http://sites.google.com/a/puredarwin.org/puredarwin/developers/booting/boot/pxe/boot-chameleon-over-pxelinux.bash?attredirects=0&d=1" -O ./boot-chameleon-over-pxelinux.bash ; sudo bash ./boot-chameleon-over-pxelinux.bash`

### Information from dfe's blog

The following is mirrored from dfe's [Be free little PXEs, be free!](https://tgwbd.org/blog/2009/10/17/be-free-little-pxes-be-free/) blog entry at https://tgwbd.org/blog/2009/10/17/be-free-little-pxes-be-free/

Posted Saturday, October 17, 2009 09:15:19 PM by dfe

Those of you looking over at the bootloader page have probably been rather disappointed to see no new postings for over a year. In reality I've made several nice changes and I need to do several posts so people are aware of them. For now we're going to start with PXE.

For those unaware, PXE is a specification for booting PCs over the network. The proper name is Preboot eXecution Environment but it's generally referred to by the pronunciation of its acronym: pixie.

In its most basic form, PXE operates as follows:

* Computer is turned on
* PXE boot is selected, usually by pressing F12 (standard key). On some BIOS, F12 selects PXE boot. On most newer BIOS, F12 brings up a menu and one of the choices will be something like "PXE" or "Network Boot Agent" or whatever.
* PXE BIOS code stored in ROM initializes the network hardware and brings up link
* A DHCP request is issued
* A DHCP response is received including the address from which to download a boot file and the TFTP path to that file
* PXE ROM code downloads the file in to RAM at 0:7C00h.
* PXE ROM code jumps to 0:7C00h.

A few notes: 0:7C00h is linear 0x7C00 which is the 31k mark in the first segment and the standard boot address. According to the spec, the ROM should be able to load linearly all the way up to the top of "real mode" RAM (640k mark). In practice many ROMs balk at anything that would exceed the end of the first 64k segment. That is 33k and the spec recommends limiting boot file size to 32k for other reasons. Also, because it is a jump to 0:7C00 you cannot execute a return. What you can do is invoke software INT 18h which sort of serves like an abort() call.

The Darwin implementation follows the specification pretty well. The boot1pxe binary (an NBP, Network Boot Program) is downloaded and loaded by the PXE ROM. Similar to the boot1u program for UFS filesystem booting, the boot1pxe program is a 32-bit program using portions of the same support libraries that boot2, the real booter, uses. The NBP uses the boot server discover reply packet to retrieve its own filename. From there it knocks off the last path component (i.e. the thing after the last "/") and replaces it with "boot". That is the name of the real boot program and is the same exact "boot" binary used as the HFS+ startup file and in other places. The boot1pxe NBP loads it to 2000:0200h, cleans itself up, and jumps to the booter.

Once the real booter has started it is able to detect that it was loaded via PXE. The boot process is virtually identical to the process on a hard drive from a UI standpoint. That is, there will be an entry in the device list representing the PXE server and a prompt where you can add all the usual options. In addition, all of the ordinary UI applies so if you want to you can at this point opt to instead directly boot an OS X volume on the hard drive or even chain to another OS partition. This is particularly useful if you've hosed the boot code on your hard disk and simply want to boot to it.

That said there are some special considerations for PXE boot. Because TFTP does not provide any facility for enumerating directory contents, the booter must know in advance which files to load. Those files are com.apple.lre.Boot.plist or com.apple.Boot.plist, mach.macosx, and mach.macosx.mkext. The booter uses the same trick that boot1pxe used to find it. That is, it uses the pathname from the boot server's discover reply packet as the base for all filenames.

On the TFTP server you will want to create a directory containing all of the boot files. One very simple option is to simply use Mac OS X Server and the network boot tools from the Server Administration Tools package to set up the boot. In general it likes to set things up in a directory like {unique-name}.nbi/i386/. So for example, 10a432.nbi/i386/mach.macosx will be the kernel (normally named mach_kernel).

The list of files you need is as follows:

boot1pxe: The NBP that will be loaded by the PXE ROM
boot: The normal booter program loaded by boot1pxe
com.apple.lre.Boot.plist: Booter configuration file
mach.macosx: The xnu kernel.
mach.macosx.mkext: An Extensions.mkext archive for this kernel
booter: Not needed, but if you use the "System Image Utility" you will find that this is just boot.efi
On the DHCP server you simply need to set next-server to the correct TFTP server (strongly recommended this be the same as the DHCP server) and set the boot filename to /path/to/whatever.nbi/i386/boot1pxe. You may also want to set root-path option in DHCP although you can instead specify it using rp= on the command-line (including in the boot plist of course).

As an alternative to setting these DHCP options on your real DHCP server you can instead set up a separate boot server. One such boot server is Microsoft's Windows Deployment Services (WDS) or the older Remote Installation Services (RIS). I have not figured out a way to add non-Windows choices to the WDS native menu but you can add non-Windows choices in WDS Legacy which is just Microsoft's new name for RIS. Setting up a choice in RIS will have to be the subject of another blog entry.

When the booter boots from PXE it sets rd=en in the kernel boot args. This tells the kernel that the root device is ethernet. The kernel then looks for the root path in either the DHCP options or from the rp= option. Assuming you have the IOHDIXController.kext you can use an HTTP server so you would have e.g. rp=http://192.0.2.1/path/to/whatever.dmg on the command line in the boot plist or the http URL in the root-path DHCP option. If you don't have IOHDIXController then it may be possible to specify an NFS path to a disk image. A glance at the kernel source seems to indicate that it has some facility for mounting flat disk images (using BSD vndevice) as the root.

There is one little gotcha about the root-path option and this is actually true of booting a Macintosh using Apple's special Boot Service Discovery Protocol. That is that the firmware does not request the root path option. So it is incumbent upon the DHCP server to send the value even though the client did not request it. ISC DHCP has a way of telling it to send additional unrequested options. It is, however, probably easier to just set rp= in the boot plist.

The last piece of the puzzle is building mach.macosx.mkext. You cannot just use one copied from your hard drive as it is unlikely to contain the network drivers. Interestingly though, the copy on the Snow Leopard DVD does. So if you don't need any additional extensions then you can use it outright. In practice the only machines that don't need extra extensions are genuine Macs. So if you were using something like a gPXE CD to boot a real Mac over the network you could do this. But of course you're then booting OS X via the BootCamp legacy BIOS layer which breaks a few things.

To build the mach.macosx.mkext you just use the ordinary kextcache tool. The general form is as follows: kextcache -m mach.macosx.kext [-n] [-l] /path/to/System/Library/Extensions ... /path/to/SomeAdditional.kext .... You do not need to and should not run kextcache as root because we're using it in a mode where it outputs an mkext file instead of updating the running system's mkext. The options break down as follows:

* -m {output-file}: Specifies that an mkext is to be output to the specified output file
* -n: Specifies that only extensions required to mount the root filesystem over the network are to be included
* -l: Specifies that only extensions required to mount the root filesystem from a local disk are to be included.
* /path/to/Extensions: One or more directories containing .kext bundles can be specified. If provided, the -n and -l filters apply to the kexts found.
* /path/to/SomeAdditional.kext: One or more additional extensions can be included in the archive. The -n and -l options do not apply and these extensions will always be included

With neither -n or -l no filtering takes place so all extensions are included resulting in a rather hefty mkext. With -n and -l you will get almost all the kexts you need. If -n and -l are failing to include some kext you know you need then you can specify it directly on the command-line to override this. These options look at the OSBundleRequired key in the Info.plist of each kernel extension. If its value is Root then either one will include it. If it's Local-Root then -l will include it and if it's Network-Root then -n will include it.

Once the booter has loaded the kernel and mkext archive it jumps to the kernel as per usual. At this point it's all about having enough driver support to bring up the network and mount the root disk image. The disk image itself is simply an ordinary OS X image. It is quite possible to use the normal DVD image as the root image. If you have a paid ADC account, the dmg files provided for download by Apple work out of the box.

Of course you aren't limited to installer images. The System Image Utility can be used to create a directly bootable image or you can even build one by hand. You are, however, limited to a read-only root FS similar to booting from a CD or DVD. Of course you can always mount some ramdisks for temporary files and NFS or AFP or SMB shares for permanent files.

The great thing about network booting is that it is extremely fast. With a basic fileserver it's on par with hard drive boot. If you have a fast server with fast disks, RAID, and a decent disk cache it can actually be quite a bit faster. In all cases, installing OS X off the network is certainly faster than off of a DVD. Generally you should see the GUI in about a minute as opposed to say five minutes when booting off a DVD.

There are of course a myriad of uses for network boot support. The most obvious one is to quickly install OS X. Beyond that, the network boot support has made developing the booter far easier. Prior to this testing the code involved building a vmdk or iso image, shutting down the VM, and rebooting with the new disk or CD image. With the network boot support I can set the VM to boot off the network, copy new binaries to the boot server, and simply reboot the VM. A similar situation applies for kernel or kernel extension development. With a quick little shell script I can have the code built and deployed to the boot server and I can quickly reset the target machine and start the new code running immediately.

There are other useful tricks too. Say I want to test El Torito support on some machine. The only way to have the El Torito stack correctly installed is to have booted from a CD. So I go to ROM-o-matic.net download a gPXE ISO and burn that to a CD. Now I can change the bootloader code simply by dropping a new binary on the network but because boot occurred from CD one of the BIOS devices will be the CD.

In short, if you can take a minute or two to set up a boot server you can make your life a lot easier when bringing up Darwin or OS X on a new machine.