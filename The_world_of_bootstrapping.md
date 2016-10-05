The world of bootstrapping
==========================
This page gives an overview over some basic concepts about booting operating systems.
It is based on a conversation with dfe in #puredarwin.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Linux](bootstrapping.html#TOC-Linux)
2.  [**2** Windows NTLDR](bootstrapping.html#TOC-Windows-NTLDR)
3.  [**3** EFI](bootstrapping.html#TOC-EFI)
4.  [**4** Multiboot](bootstrapping.html#TOC-Multiboot)
    1.  [**4.1** Modified boot-132 to run as multiboot kernel](bootstrapping.html#TOC-Modified-boot-132-to-run-as-multiboot-kernel)
5.  [**5** Network booting](bootstrapping.html#TOC-Network-booting)
    1.  [**5.1** PXE](bootstrapping.html#TOC-PXE)
    2.  [**5.2** BootX (PPC)](bootstrapping.html#TOC-BootX-PPC-)
    3.  [**5.3** Netboot (PPC)](bootstrapping.html#TOC-Netboot-PPC-)
    4.  [**5.4** Windows](bootstrapping.html#TOC-Windows)
    5.  [**5.5** General](bootstrapping.html#TOC-General)

### Linux
Linux needs two files to boot.  A kernel, and an initrd
any time you upgrade your kernel you've got to build a new initrd to go with it
which pulls needed drivers off the filesystem as is and puts them into the initrd
now in Linux's case you're typically not going to be adding a driver needed at boot time to the filesystem after the fact
but in the case of Windows or OS X you'll have a lot of third-party drivers which the user might want to install at any time
therefore the bootloader must be able to read all of those drivers
which means the bootloader must be able to read the root filesystem
which the bootloader will do using BIOS calls to read sectors and its own code to read the filesystem
### Windows NTLDR
NTLDR does basically the same thing
the boot sector knows barely enough to get NTLDR loaded, just like boot1 knows barely enough to get boot (a.k.a. boot2) loaded
once there, the second-stage bootloader (be it NTLDR or boot) has enough code to read the filesystem and locate the kernel and drivers
in NTLDR's case it even has enough code to read a registry hive which tells it which drivers to load rather than simply loading any drivers that might be needed for boot
which is also why windows won't boot if you move the hard drive to a different system.  The system registry hive only says to load say the 440bx HD controller driver, not the ICH-7 driver or the VIA driver or whatever
that's part of the reason why EFI is such a big deal. 
### EFI
With EFI you've got a decent 32-bit callable interface to read sectors from the hard drive
plus you're guaranteed to be able to read FAT32
plus you can supply drivers for other filesystems
so it enables you to write bootloaders that can read quite a bit, certainly enough to get all the individual drivers loaded
Now take something like GRUB for instance.  GRUB is actually advanced enough that it code theoretically load a vmlinuz and a  number of .ko files to get the system loaded.  But which .ko files would it load?
if you look on a macbook you'll note that everything you need to boot is in ROM
there's hardly anything in the EFI partition
well there never was anything on the service partition because Apple has enough in the firmware that it doesn't need the service partition
but that's because Apple wants to explicitly support booting of OS X which is an addition to the EFI spec
and to boot from CD apple may have used the EFI El Torito spec to load enough to get the HFS+ driver and boot.efi loaded
then boot.efi could take over as per usual
yeah, take the linux case for instance
assume you had everything to do from scratch and there was no legacy of initrds
what you would probably do is write an ext2/3 driver for EFI
and you might then have a bootloader which looked for a config file to tell it which kernel and set of drivers to load
yeah, if OS X was made to run on generic PCs then the CD might have a custom loader that was just good enough to load an HFS+ driver and the real second-stage booter (boot.efi)
notice how nothing really changes from x86 boot here.  You still have the situation of a first stage loader good enough to load the second stage loader which is good enough to load the OS
welcome to the world of bootstrapping
### Multiboot
multiboot is an open specification designed to allow you to boot a kernel straight into protected mode
for it to have any chance of working you've either got to have enough in the kernel itself to be able to root or you've got to supply modules to the kernel
the multiboot spec can supply modules to the kernel though
but again you wind up in a similar situation.  Now part of your bootstrapping code is sort of in the kernel
at least it has to have enough code to know how to link in the additional modules because let's face it, at some point you need to root a filesystem
there's no getting around that
typically multiboot is used primarily for toy operating systems
yes, multiboot doesn't really give you a whole lot
basically all it does is say that your kernel and some number of additional files will have been loaded by the bootloader
basically all it does is say that your kernel and some number of additional files will have been loaded by the bootloader
and then the bootloader will jump into your code which will start in protected mode
#### Modified boot-132 to run as multiboot kernel
kernel being boot-132 in our special case
well the reason for multiboot in boot-132 is to avoid having to replace the startup file to develop it
and boot-132 uses multiboot in a rather queer way
basically there's an alternative entrypoint coming from the multiboot bootloader
that entrypoint sets up enough to get a stack and whatnot and from there runs the bootloader as per usual
i.e. it still thunks into real-mode to make BIOS calls
Q: So in a nutshell, it's BIOS/EFI -&gt; (GRUB) and/or boot1 (our "kernel" for argument's sake) -&gt; boot2 -&gt; xnu (our "real" kernel)?
when using multiboot there is no boot1
GRUB boots boot(2) directly
that is the point of it
the reason being that 512 bytes for boot1h is barely enough to find the HFS+ startupfile and load it
now it's really the case that you're guaranteed to have 1024 bytes available which as we've seen is actually enough to read some of the HFS+ directory structure and find a file in the root
but even then the 1024-byte is really not enough to do it right
### Network booting
Q: from a server's perspective the i386 network boot mechanisms are all the same?

yeah, just provide an IP via DHCP and files via TFTP
#### PXE
PXE is an x86 thing
it does use TFTP like basically everything else out there to grab the kernel and modules (extensions) though
actually bootstrapping over the network is interesting
regardless of platform this is basically how it is supposed to go down
DHCP or BootP so the firmware can get itself an IP address
TFTP to actually grab the bootloader
which depending on system might be a first-stage loader (PXE tends to require this) or might be THE loader
PXE tends to require it primarily because PXE spec says to only force the firmware to load 32k
so 32k is usually only enough to get your own code in place that can load the larger real booter
either way you'll eventually get the real (second-stage) booter loaded
#### BootX (PPC)
for PPC that'd be BootX
so BootX itself would be loaded by OpenFirmware
from there BootX will make open firmware calls to load more files from tftp, including the kernel and hopefully the Extensions.mkext package
#### Netboot (PPC)
although PPC Macs have the whole netboot spec too
which is some more stuff on top of TFTP/DHCP

there is a command to do a netboot in openfirmware
typically just hold down N
#### Windows
ditto for Windows NT, it has a special server program
there's actually a server program that tells the client which drivers it needs
the Windows PXE client enumerates PCI devices and sends that info to this special server
the special server responds back and tells it which drivers it needs to download via TFTP
#### General
the thing is that this kinda goes back to what I was talking about earlier on having to know which drivers to load
there's different ways to accomplish it
Windows actually has a client/server thing to do this and the client side tells the server about the hardware and the server then does the hard work of sifting through the INF files to determine which SYS files to load
a typical Linux setup uses an initrd
for something like Fedora the initrd intended for PXE boot will basically contain any driver (.ko) that might possibly be needed to root locally or over the network
for OS X it's similar except that instead of an initrd you have an Extensions.mkext

