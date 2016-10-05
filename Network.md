Network
=======

This page primarily details how to get networking working in PureDarwinXmas, but these steps should be applicable to any Darwin installation.
Next releases should/could include some part present here.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:333px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Network support](network.html#TOC-Network-support)
    1.  [**1.1** Install Network Drivers](network.html#TOC-Install-Network-Drivers)
    2.  [**1.2** VMWare settings](network.html#TOC-VMWare-settings)
    3.  [**1.3** QEMU settings](network.html#TOC-QEMU-settings)
    4.  [**1.4** Install PureFoundation](network.html#TOC-Install-PureFoundation)
    5.  [**1.5** Activate DirectoryServices](network.html#TOC-Activate-DirectoryServices)
    6.  [**1.6** Install IPConfiguration](network.html#TOC-Install-IPConfiguration)
2.  [**2** Credits](network.html#TOC-Credits)
3.  [**3** Availability and investigation](network.html#TOC-Availability-and-investigation)
    1.  [**3.1** Available](network.html#TOC-Available)
    2.  [**3.2** Investigate](network.html#TOC-Investigate)
    3.  [**3.3** Blocked](network.html#TOC-Blocked)

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

<span><span style="font-family:courier new,monospace"><span style="font-size:small">ethernet0.present = "TRUE"</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">ethernet0.virtualDev = "e1000"</span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span></span>
<span style="font-family:courier new">
</span>
<span style="font-family:arial,sans-serif">Optionally, you can also add with <span style="font-family:courier new;font-size:12px">TRUE</span> or <span style="font-family:courier new;font-size:12px">FALSE<span style="font-family:arial;font-size:13px"> depending your needs</span></span></span>


<span style="font-family:courier new,monospace"><span style="font-size:small">ethernet0.wakeOnPcktRcv = "FALSE"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">ethernet0.linkStatePropagation.enable = "FALSE"</span></span>

<span style="font-family:courier new">
</span>
<span style="font-family:arial,sans-serif">Next you will have to install a driver for your network card. For the <span style="font-style:italic">Intel </span><span style="font-style:italic">e1000</span> device, the only current compatible Darwin driver is Apple's closed-source *AppleIntel8245XEthernet.kext*, which live in </span><span><span style="font-family:courier new,monospace"><span style="font-size:small">/System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/</span></span></span><span style="font-family:arial,sans-serif">.</span>

<span style="font-family:arial,sans-serif">But since this isn't available ([blocker](../blockers.html)) for general distribution you're pretty much stuck.</span>

**<span style="text-decoration:underline">Blocker:</span> no kext available which will match the e1000 device in VMware**
### QEMU settings
Through the *QEMU user mode network stack*, it is possible to have a weird but functional network (rtl8139 tested).
For more information, refer to the [QEMU](qemu.html) page.
A quick overview:
-   <span style="font-family:arial,sans-serif">DHCP client (KernelEventMonitor) and server (QEMU virtual DHCP server) functionality.</span>
-   <span style="font-family:arial,sans-serif">Guest IP address starts from 10.0.2.15.</span>
-   <span style="font-family:arial,sans-serif">DHCP server and gateway on 10.0.2.2.</span>
-   <span style="font-family:arial,sans-serif">A virtual DNS server is also (10.0.2.3) present and autoset.</span>
-   <span style="font-family:arial,sans-serif">A virtual SAMBA or NFS can be used on 10.0.2.4 (**not tested**) in order to access files on the host via file sharing.</span>
-   A workaround is involved in order to avoid the connection to stall.
### Install PureFoundation
The <span style="font-size:small">PureFoundation.root.tar.gz</span> available from [the PureDarwin svn](http://puredarwin.googlecode.com/svn/Roots/pd/) or [the PureDarwin hg](http://puredarwin.googlecode.com/hg/Roots/pd/) repository contains two system frameworks which are required by a number of different networking components. Also available from the same location is the ddistonoted.root.tar.gz. Install both of these.
<span style="font-size:18px;font-weight:bold">Install SystemConfiguration.framework and Components</span>
<span style="font-style:italic">SystemConfiguration.framework</span>, which is part of the configd project, provides the components needed to configure network interfaces.
Unfortunately, it does not currently build correctly and the available binary roots (spread across <span style="font-style:italic">configd.root</span> and <span style="font-style:italic">configd_executables.root</span>) are incomplete.
You've probably already guessed that the missing components are the ones we need.
However, by loading configd into XCode it is possible to build some of the individual components needed.

The file <span style="font-style:italic">configd.root.tar.gz</span> below contains as many of the missing components as we could get to build and a template *preferences.plist*.
Install it in the usual manner (using ditto) and you will have all the components needed to get networking up and running.

Install and fix these files with:

<span><span style="font-family:courier new,monospace"><span style="font-size:small">sudo ditto ~/Downloads/configd.root/ /Volumes/PureDarwinXmas/</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">sudo chown root:wheel /Volumes/PureDarwinXmas/System/Library/LaunchDaemons/com.apple.configd.plist</span></span></span>
### Activate DirectoryServices
You must copy the <span style="font-family:courier new,monospace"><span style="font-size:small">com.apple.DirectoryService* plists</span></span> into <span style="font-family:courier new,monospace"><span style="font-size:small">/System/Library/LaunchDaemons</span></span> and set their ownership to <span style="font-family:courier new,monospace"><span style="font-size:small">root:wheel</span></span>.
### <span style="font-size:22px"><span style="font-size:18px">I</span><span style="font-size:18px">nstall IPConfiguration</span></span>
<span style="font-size:13px;font-weight:normal">This is all very well, but how do we get networking to configure itself automatically?</span>
<span style="font-size:13px;font-weight:normal">Most of the bundles to be found under <span style="font-family:courier new,monospace"><span style="font-size:small">/System/Library/SystemConfiguration/</span></span> have some part to play, but chief among them are IPConfiguration and IPMonitor.</span>
-   <span style="font-size:13px">The IPMonitor bundle contains no compiled code and is responsible for allowing the DirectoryService daemon to perform DNS lookups.</span>
-   <span style="font-size:13px">The IPConfiguration bundles is available as part of the "bootp" package and is responsible for performing configuration via DHCP.
    It also has dependencies on the closed-source <span style="font-style:italic">Apple80211.framework</span>, as well as private CF symbols missing in CFLite.</span>
<span style="font-size:13px">Getting a version of this bundle which will work in PureDarwin will now be one of our highest priorities.</span>
So we're currently waiting for a non-linked version of bootp.
Credits
-------
Thanks to Dr. Rolf "RolfHeinrich" Jansen for providing the missing components and the knowledge to use them.
Availability and investigation
------------------------------
Watch carefully from many points of view (e.g., legal, technical, etc..).
### Available
<span style="border-collapse:separate;white-space:pre"><http://src.macosforge.org/Roots/9A581/AppleIntel8255x.root.tar.gz> (available in DarwinBuild consequently)</span>
<span style="border-collapse:separate;white-space:pre">(reported to work in QEMU)</span>
<span style="border-collapse:separate;white-space:pre">
</span>
<span style="border-collapse:separate;white-space:pre"><span style="border-collapse:collapse;white-space:normal">Realtek's [AppleRTL8169Ethernet](http://www.realtek.com/downloads/downloadsView.aspx?Langid=1&PNid=13&PFid=4&Level=5&Conn=4&DownTypeID=3&GetDown=false&Downloads=true#97)</span></span>
<span style="border-collapse:separate;white-space:pre"><span style="border-collapse:collapse;white-space:normal">Intel d945gclf2 Atom board (e.g., reported to work)</span></span>

<span style="font-weight:bold">AppleRTL8139Ethernet.kext</span> is available in Darwinbuild.
Realtek RTL8139 Ethernet card" (e.g., reported to work in QEMU)
### Investigate
<span style="font-weight:bold">RealtekR1000</span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-style:italic">It's an opensource driver for network controllers RTL8168, RTL8111, RTL8169, RTL8101 and some others modification for Mac OSX. It is based on Realtek' driver for Linux and doesn't supported by Realtek.</span></span></span>
<http://sourceforge.net/projects/realtekr1000/> 
<span style="font-weight:bold">82566mm</span>
<span style="font-weight:bold"><span style="font-weight:normal">svn checkout http://82566mm-osx-driver.googlecode.com/svn/trunk/ 82566mm-osx-driver-read-only</span></span>
<http://techresearchinfo.blogspot.com/> 

**intel-e1000e-kext**
**<span style="font-family:arial,sans-serif;font-weight:normal">Open source kernel extension for Intel E1000e series of network cards (supporting many models)</span>**
[http://code.google.com/p/intel-e1000e-kext/](http://code.google.com/p/intel-e1000e-kext/source/browse/#svn/trunk)

<span style="font-weight:bold">iwidarwin</span>
<span style="font-style:italic">Intel® PROSet/Wireless 2200-2915/2100/3945/4965 driver for Mac OS X</span>
<http://code.google.com/p/iwidarwin> 

<span style="border-collapse:separate;font-family:arial;font-style:italic"><span style="border-collapse:collapse;font-family:Arial;font-style:normal"><span style="font-weight:bold">osxbge</span></span></span>
<span style="border-collapse:separate;font-family:arial;font-style:italic">[A port of the BSD bge driver to Apple's OS X operating system.](http://code.google.com/p/osxbge/)</span>
<span style="border-collapse:separate;font-family:arial">Broadcom 57xx and 59xx network chipsets</span>
[http://code.google.com/p/osxbge/](http://code.google.com/p/osxbge)

<span style="font-weight:bold">wirelessdriver</span>
<span style="font-weight:bold"><span style="font-weight:normal;border-collapse:collapse;font-style:italic">A Prism/Prism2 driver for use with MacOS X and/or the Darwin operating system from Apple. <span style="font-style:normal">(seems old..)</span></span></span>
<span style="border-collapse:collapse"></span>
<http://sourceforge.net/projects/wirelessdriver/>
### Blocked
<span style="font-weight:bold">AppleIntel8254XEthernet.kext</span> is not redistributable.
Intel e1000 network card (e.g., the one supported in VMware Fusion)

