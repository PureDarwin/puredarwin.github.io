Network
=======

This page primarily details how to get networking working in PureDarwinXmas, but these steps should be applicable to any Darwin installation.
Next releases should/could include some part present here.

Network support
---------------
A must.
### Install Network Drivers
Network drivers are provided in the form of [Kernel Extensions (KEXTs)](kexts.html).
While Apple has made a few available in either source or binary form, these are nowhere near as many as are provided with OS X.
In particular, although the *AppleIntel8254XEthernet.kext* which is needed for VMWare exists, it is not available for redistribution in any form.

For the Intel d945gclf2 Atom board, Realtek's [AppleRTL8169Ethernet](http://www.realtek.com/downloads/downloadsView.aspx?Langid=1&PNid=13&PFid=4&Level=5&Conn=4&DownTypeID=3&GetDown=false&Downloads=true#97) is reported to work. Realtek have a good selection of drivers available on their website.
### VMWare settings
The first thing you will need to do is edit the virtual machines configuration file. This is the .vmx file inside the virtual machine's bundle.
Ensure that the following options are present.

ethernet0.present = "TRUE"`
`
ethernet0.virtualDev = "e1000"`
`





`ethernet0.wakeOnPcktRcv = "FALSE"`
`ethernet0.linkStatePropagation.enable = "FALSE"`



/System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/.

But since this isn't available ([blocker](../blockers.html)) for general distribution you're pretty much stuck.

**__Blocker:__ no kext available which will match the e1000 device in VMware**
### QEMU settings
Through the *QEMU user mode network stack*, it is possible to have a weird but functional network (rtl8139 tested).
For more information, refer to the [QEMU](https://github.com/PureDarwin/PureDarwin/wiki/QEMU) page.
A quick overview:
-   DHCP client (KernelEventMonitor) and server (QEMU virtual DHCP server) functionality.
-   Guest IP address starts from 10.0.2.15.
-   DHCP server and gateway on 10.0.2.2.
-   A virtual DNS server is also (10.0.2.3) present and autoset.
-   A virtual SAMBA or NFS can be used on 10.0.2.4 (**not tested**) in order to access files on the host via file sharing.
-   A workaround is involved in order to avoid the connection to stall.
### Install PureFoundation
The PureFoundation.root.tar.gz available from [the PureDarwin svn](http://puredarwin.googlecode.com/svn/Roots/pd/) or [the PureDarwin hg](http://puredarwin.googlecode.com/hg/Roots/pd/) repository contains two system frameworks which are required by a number of different networking components. Also available from the same location is the ddistonoted.root.tar.gz. Install both of these.
**Install SystemConfiguration.framework and Components**
*SystemConfiguration.framework*, which is part of the configd project, provides the components needed to configure network interfaces.
Unfortunately, it does not currently build correctly and the available binary roots (spread across *configd.root* and *configd_executables.root*) are incomplete.
You've probably already guessed that the missing components are the ones we need.
However, by loading configd into XCode it is possible to build some of the individual components needed.

The file *configd.root.tar.gz* below contains as many of the missing components as we could get to build and a template *preferences.plist*.
Install it in the usual manner (using ditto) and you will have all the components needed to get networking up and running.

Install and fix these files with:

sudo ditto ~/Downloads/configd.root/ /Volumes/PureDarwinXmas/`
`
sudo chown root:wheel /Volumes/PureDarwinXmas/System/Library/LaunchDaemons/com.apple.configd.plist
### Activate DirectoryServices
You must copy the `com.apple.DirectoryService* plists` into `/System/Library/LaunchDaemons` and set their ownership to `root:wheel`.
### 
This is all very well, but how do we get networking to configure itself automatically?

-   The IPMonitor bundle contains no compiled code and is responsible for allowing the DirectoryService daemon to perform DNS lookups.
-   
Getting a version of this bundle which will work in PureDarwin will now be one of our highest priorities.
So we're currently waiting for a non-linked version of bootp.
Credits
-------
Thanks to Dr. Rolf "RolfHeinrich" Jansen for providing the missing components and the knowledge to use them.
Availability and investigation
------------------------------
Watch carefully from many points of view (e.g., legal, technical, etc..).
### Available
<span style="border-collapse:separate;white-space:pre"><http://src.macosforge.org/Roots/9A581/AppleIntel8255x.root.tar.gz> (available in DarwinBuild consequently)</span>
(reported to work in QEMU)


<span style="border-collapse:separate;white-space:pre"><span style="border-collapse:collapse;white-space:normal">Realtek's [AppleRTL8169Ethernet](http://www.realtek.com/downloads/downloadsView.aspx?Langid=1&PNid=13&PFid=4&Level=5&Conn=4&DownTypeID=3&GetDown=false&Downloads=true#97)</span></span>
Intel d945gclf2 Atom board (e.g., reported to work)

**AppleRTL8139Ethernet.kext** is available in Darwinbuild.
Realtek RTL8139 Ethernet card" (e.g., reported to work in QEMU)
### Investigate
**RealtekR1000**
**It's an opensource driver for network controllers RTL8168, RTL8111, RTL8169, RTL8101 and some others modification for Mac OSX. It is based on Realtek' driver for Linux and doesn't supported by Realtek.**
<http://sourceforge.net/projects/realtekr1000/> 
**82566mm**
**svn checkout http://82566mm-osx-driver.googlecode.com/svn/trunk/ 82566mm-osx-driver-read-only**
<http://techresearchinfo.blogspot.com/> 

**intel-e1000e-kext**
**Open source kernel extension for Intel E1000e series of network cards (supporting many models)**
[http://code.google.com/p/intel-e1000e-kext/](http://code.google.com/p/intel-e1000e-kext/source/browse/#svn/trunk)

**iwidarwin**
*Intel® PROSet/Wireless 2200-2915/2100/3945/4965 driver for Mac OS X*
<http://code.google.com/p/iwidarwin> 

*osxbge*
*[A port of the BSD bge driver to Apple's OS X operating system.](http://code.google.com/p/osxbge/)*
Broadcom 57xx and 59xx network chipsets
[http://code.google.com/p/osxbge/](http://code.google.com/p/osxbge)

**wirelessdriver**
****

<http://sourceforge.net/projects/wirelessdriver/>
### Blocked
**AppleIntel8254XEthernet.kext** is not redistributable.
Intel e1000 network card (e.g., the one supported in VMware Fusion)

