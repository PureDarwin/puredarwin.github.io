For users
=========
This page contains information for users.

## 1. General information for users

### 1.1 Installation ISOs ###

* **Darwin 10**
For versions up to Darwin10 (e.g.: the one included in Snow Leopard), the PureDarwin project is working on building it.

* **Darwin 9**
For versions from Darwin 9 (the version that matches Leopard) onwards, the PureDarwin project is providing ISOs and a way to code, build and use it. Currently, there is a minimal Darwin 9 ISO ("[PureDarwin Nano](PureDarwin-Nano)", can boot into bash) and a Developer Preview with X11 ("[PureDarwin Xmas](Xmas)", can boot into a X11 desktop). 

    If you are a [developer](https://github.com/PureDarwin/PureDarwin/wiki/For-developers), you can create your own full PureDarwin 9 ISOs and virtual machines with our scripts and tools as described [here](PureDarwin_repository).

* **Darwin 8**
For versions up to Darwin 8, Apple and the OpenDarwin project provided [installation ISOs](http://opensource.apple.com/static/iso/).
These are probably mainly of historical value today since the i386 version is binary incompatible to both newer versions of Darwin and Mac OS X, and hardware support is limited to older systems.

Please watch this space for changes, and have a look at the [prerequisites](#2-prerequisites).

### 1.2 Other
[Historic Apple Darwin ISOs](http://opensource.apple.com/static/iso/)

[Historic OpenDarwin 6 ISOs at http://www.mit.edu/~darwin/downloads/](http://www.mit.edu/~darwin/downloads/) 

### 1.3 Documentation

This wiki is a place for users and developers alike to document and discuss Darwin.

## 2. Prerequisites

This list does not consider the PowerPC platform since no PowerPC hardware is available in the marketplace any more to our knowledge, other than used vintage Macs (which already come with Mac OS X).

### 2.1 Darwin 8

Note that the PureDarwin project is **not** about running Darwin 8 and earlier and we will not support it in any way.

### 2.2 Darwin 9

  - **For PureDarwin Xmas: VMware Fusion 2 running on a Macintosh**
  - A "family 6" Intel processor, which includes (but is not limited to)
    - Core Solo and Core Duo ("Yonah")
    - Core 2 Duo and Core 2 Quad ("Merom", "Penryn", "Conroe", "Allendale", "Wolfdale", "Kentsfield", "Yorkfield")
    - Celeron S 4x0 ("Conroe-L")
    - Celeron E1x00 ("Conroe-L")
    - Pentium Dual-Core T2xx0, E2xx0 ("Yonah-1024", "Merom-1024", "Allendale-1024")
    - Atom 2x0 ("Diamondville")

For best compatibility, use an Intel chipset (ICHx). These requirements might be lifted by the use of the xnu-dev kernel.

## 3 Tested Compatible Hardware

### 3.1 Virtual

Pseudo-legend:

> *Host*
>
> *Soft version x.y.z (+ info(s))
> -   *cpu + info(s)*

**Apple Mac OS X (Snow) Leopard**
[QEMU](QEMU) > v0.9.0
-   Intel Core 2 Duo (T7400)
[VMware Fusion](VMware)
-   Intel Core 2 Duo (T7400)
MS Windows
QEMU v0.10.0 (XP 32 bits SP3)
-   AMD Sempron 2800+ (specific version from "Patrick", see [QEMU](QEMU) page)
VMware Server 2.0 nc (AMD 64bits)
VMware Player 2.5.1 (XP 32 bits SP3)
VMware Player 2.5.2 (WIN7 64bits RC)
-   Intel Core 2 Quad (Q9400)
GNU/Linux

**kvm (Ubuntu 8.10)**
-   AMD Phenom(tm) II X4 940 Processor
VMware Player 2.5 (Ubuntu, Fedora 8, OpenSuse 64 bits)
VMware Server 2.0.0 (SMP x86_64) via VMware Infrastructure Web Access
-   Dual Core AMD Opteron(tm) Processor 180 (Sun Fire(TM) X2100)


### 3.2 Physical

-   Apple MacBook2,1 (Intel Core 2 Duo 2.16Ghz)
-   Apple MacBookPro3,1
-   ? ich7m, T7200, 945pm
-   IBM T42
-   Lenovo S10 (no Ethernet yet)
-   Netbook nc10
-   Acer Aspire 5610Z (Intel T2060 1.6Ghz)
-   MSI Wind U100 (no XFree86 yet)

## 4. Installing PureDarwin

Don't get too excited: we haven't put together a full "How to" yet. This page will provide a selection of pointers.

### 4.1 Installing PureDarwin using `GRUB` and `CHAMELEON`

The process for installing PureDarwin to boot using the `GRUB` and `CHAMELEON` bootloaders (perhaps as part of a multi-boot system) is described below. Thanks to poppyer for the information.

The basic booting procedure is:
`GRUB(MBR)` -> `CHAMELEON boot1h` -> `CHAMELEON boot2` -> `darwin kernel`

First of all, preparing a primary partition as hfs partition 
NOTE: I only tried these on a primary partition, so I am not sure whether it works for logical extended partitions

1) make an hfs partition and mount it
   - FOR LINUX: using `mkfs.hfs`
   - FOR OSX: using the `Disk Utils.app`

2) loop mount the puredarwin image (iso or vmdk)
   - loop mount a vmdk might be tricky under linux.

3) copy everything from the puredarwin image to your hfs partition in order to preverse file ownerships etc.
   - FOR LINUX: using `sudo cp -a`
   - FOR OSX: using `sudo cp -pR`

So far, the hfs partition is ready, now going to install the boot loader

1) Download an extract the Chameleon Boot Loader to any folder. Copy the `boot` file (often called `boot2`) to the root of your hfs partition.

2) Unmount your HFS partition (VERY IMPORTANT)
   `dd` the `boot1h` file (1024 bytes) from chameleon to the bootsector of your hfs partition.

By here, the hfs partition is self bootable, now add it to your first level boot loader (GRUB)

6) add and item to the menu.lst of your GRUB (MBR), usually:

        rootnotify (hd?,?)
        makeactive
        chainloader +1

Last, if your CPU is SSE2 only, you **MUST** use the voodoo kernel
BEFORE your reboot, edit the 
`/Library/Preferences/SystemConfiguration/com.apple.Boot.plist`,
add `".voodoo"` to `"mach_kernel"`, so it becomes `"mach_kernel.voodoo"`

- `mach_kernel.voodoo` is already shipped with puredarwin.Xmas
but `mach_kernel.voodoo` uses its own `System.kext`,

**Troubleshooting**

**Q:** if your first reboot freeze at: `"MAC Framework successfully initialized using ...."`

**A:** you might need a patched version of `AppleACPIPlatform.kext` and `AppleAPIC.kext` from `boot132 generic.iso` to replace those ones under `/Systerm/Library/Extensions/`

### 4.2 Preparing a Disk Using Darwin Tools
You will need:
-   The Chameleon boot loader, installed into /usr/standalone/i386/ 
-   `fdisk` (a version comes with Chameleon, so use that one)
-   `dd`, `newfs_hfs` and `mount`.


Then, assuming that you're working with the first disk (0),
1.  Create a partition and install the primary bootloader: `fdisk -i -a hfs /dev/rdisk0`
2.  Create an HFS+ file system on the disk: `newfs_hfs -s -J -v /dev/rdisk0`
3.  Install the secondary bootloader: `dd if=/usr/standalone/i386/boot1h of=/dev/rdisk0s1`
4.  Mount the partition: `mount -t hfs /dev/rdisk0s1 /tmp`
5.  Install the tertiary bootloader: `cp /usr/standalone/i386/boot /tmp/`
6.  Install the kernel and everything else onto the system
   
Simple, eh? A version of the PureDarwin Nano CD image with these tools installed will be available soon.

