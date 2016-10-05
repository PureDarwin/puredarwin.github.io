PureDarwinBoot
==============
PureDarwin Boot is a minimal Darwin distribution, based on Nano, with a few extra packages added and many unnecessary files removed. It takes up approximately 64Mb, and can be compressed down to 28Mb. By default it runs an installation script (based on the one from Darwin 8, which will partition and format a disk, install bootloaders, and copy across a number of root archives), but you can also drop into a shell where many useful diagnostic and repair tools are available to you.

A binary root of PureDarwin Boot is available below.

### Creating a Bootable Image
To create a bootable CD image of PureDarwin Boot you will need the archive below and a copy of the <span style="font-family:courier new,monospace">pd_makedmg</span> script from the svn/hg. Assuming you've unpacked the archive in your Downloads directory, and as root:

<span>    <span style="font-family:courier new,monospace"># pd_makedmg ~/Downloads/PureDarwinBoot.root/ /tmp/pdboot.iso PureDarwinBoot</span></span>

The image will have been created as /tmp/pdboot.iso.dmg, so rename it to pdboot.iso and burn it to a CD.

### The Installer
The installer will take you thorough creating a partition for Darwin and will then copy then binary roots found under /System/Installation/Packages/ and named *.root.tar.gz and *.root.tar.bz2. There are no binary roots included in the archive below. A PureDarwin Install CD with images will be produced soon. This information is for if you want to create your own custom install CD.

The files from /System/Installation/Extras/ on the CD will be copied to /System/Installation/Packages/ on the destination partition.

The installer offers you a choice of EFI (for Macs and VMWare Fusion) or Chameleon BIOS bootloader. It also allows you to specify default boot arguments to be passed to the kernel.

A step-by-step guide to installing using it will be written soon. Maybe even by me.

### Know Issues
-   <span style="font-family:courier new">shutdown</span> does not work. This is because Apple's shutdown (which this is) attempts to communicate with the kextd before stopping the system. If it cannot contact the kextd (which it can't because Boot doesn't run the kextd) it will not allow shutdown.
-   <span style="font-family:courier new,monospace">bless</span> does not work, because it requires the ApplicationServices.framework, which isn't even in the full PureDarwin release. Still, VMWare at least still boots without having its disk blessed.
There are also many more problems, I'm sure.

Please leave comments below as you find them.

So far this has been tested on VMWare Fusion and nowhere else.

And, yes, I know they released a Release Candidate of the new Chameleon bootloader today. I'll get round to looking at it as soon as I can.

### Download
Apparently I'm not allowed to upload anything over 11Mb, so you can find the root [here](http://www.hereapi.com/PureDarwinBoot.root.tar.gz).

