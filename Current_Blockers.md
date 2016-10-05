Current Blockers
================
This page lists the current issues we are having that prevent us from making a Darwin 9 ISO. The contents of this page are subject to change.
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:432px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents

1.  [Problems to be solved](Current_Blockers#problems-to-be-solved)
    1. [CFOpenDirectory missing in CFOpenDirectory binary root](Current_Blockers#cfopendirectory-missing-incfopendirectory-binary-root)
    2. [IOHDIXController.kext needed (image boot support)](Current_Blockers#iohdixcontrollerkext-needed-image-boot-support)
    3. [OSvKernDSPLib.kext needed (audio support)](Current_Blockers#osvkerndsplibkext-needed-audio-support)
    4. [Shortage of network drivers](Current_Blockers#shortage-of-network-drivers)
    5. [SystemConfiguration.framework is incomplete](Current_Blockers#systemconfigurationframework-is-incomplete)
    6. [gdb does not compile](Current_Blockers#gdb-does-not-compile)
    7. [DirectoryService daemon depends on missing CFLite functions](Current_Blockers#directoryservice-daemon-depends-on-missing-cflite-functions)
2.  [Problems with partial workarounds](Current_Blockers#problems-with-partial-workarounds)
    1. [OpenDirectory depends on Foundation](Current_Blockers#opendirectory-depends-on-foundation)
    2. [launchd does not build](Current_Blockers#launchd-does-not-build)
    3. [IOKitUser does not build](Current_Blockers#iokituser-does-not-build)
3.  [Problems that are problems no more](Current_Blockers#problems-that-are-problems-no-more)
    1. [diskarbitrationd fails with "_SCSerialize() failure" errors](Current_Blockers#diskarbitrationd-fails-with-_scserialize-failure-errors)
    2. [CF missing symbols](Current_Blockers#cf-missing-symbols)
    3. [libauto.dylib missing](Current_Blockers#libautodylib-missing)

### Problems to be solved
#### CFOpenDirectory missing in CFOpenDirectory binary root
OpenDirectory framework depends on CFOpenDirectory framework, for which there is both a project and a binary root.
<span style="font-size:small">However, the binary root does not contain the actual CFOpenDirectory file (</span>[<span style="font-size:small">http://darwinbuild.macosforge.org/trac/ticket/50</span>](http://darwinbuild.macosforge.org/trac/ticket/50)<span style="font-size:small">):</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">otool -L OpenDirectory.root/System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/OpenDirectory  | grep CFO</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="color:rgb(68,68,68)"><span style="font-size:small"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="color:rgb(68,68,68)"><span style="font-size:small">/System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/Frameworks/CFOpenDirectory.framework/Versions/A/</span></span><span style="font-weight:bold"><span style="color:rgb(68,68,68)"><span style="font-size:small">CFOpenDirectory</span></span></span><span style="color:rgb(68,68,68)"><span style="font-size:small"> (compatibility version 1.0.0, current version 1.0.0)</span><span style="color:rgb(0,0,0);font-family:Arial"><span style="font-size:small"> </span></span></span></span>
<span style="font-size:small">The sources cannot be built without being patched because it depends on missing CoreFoundation headers (e.g., CoreFoundation/CFBridgingPriv.h) and on DirectoryServiceCore (part of DirectoryService which cannot yet be built too).</span>

#### IOHDIXController.kext needed (image boot support)
BinaryDriver IOHDIXController.kext is missing ([used to be available](legal/binarydrivers.html) under Apple Driver License) in order to use [imageboot](developers/live-cd.html#TOC-Alternative-2:-Using-imageboot).
<span style="color:rgb(255,0,0)">Please let us know if you know a solution.</span>
#### OSvKernDSPLib.kext needed (audio support)
BinaryDriver OSvKernDSPLib.kext is missing, consequently IOAudioFamily.kext cannot be loaded resulting in no audio support.

<span style="color:rgb(255,0,0)">Please let us know if you know a solution.</span>
#### Shortage of network drivers
There is a shortage of network drivers (and of other drivers in general) for Darwin.
Of particular concern, the Intel e1000 driver AppleIntel8254XEthernet.kext, needed to run networking under VMWare, while available in OS X are not available for general distribution nor redistributable. 
Open source drivers for a vast number of network cards (and hardware of every type) are available for other platforms (e.g., BSD and GNU/Linux). See the [Network](developers/network.html) page for more information.
It would be great if someone skilled in driver programming could port some of these to Darwin (we are told that writing drivers for IOKit is really a rather nice experience).
#### SystemConfiguration.framework is incomplete
SystemConfiguration.framework (in the configd package) does not compile, and the binary root made available is incomplete. While some components can be made to compile individually (see the [Network](developers/network.html) page for a download), there are still important components (ATConfig and KernelEventMonitor) missing.
KernelEventMonitor can be built (part of configd_plugins which not build because it depends on configd which not build without patch and code sacrifice):
<span style="font-family:courier new,monospace;font-size:small">file BuildRoot/private/var/tmp/configd_plugins/configd_plugins-91.root/System/Library/SystemConfiguration/KernelEventMonitor.bundle/Contents/MacOS/KernelEventMonitor
BuildRoot/private/var/tmp/configd_plugins/configd_plugins-91.root/System/Library/SystemConfiguration/KernelEventMonitor.bundle/Contents/MacOS/KernelEventMonitor: Mach-O universal binary with 2 architectures
BuildRoot/private/var/tmp/configd_plugins/configd_plugins-91.root/System/Library/SystemConfiguration/KernelEventMonitor.bundle/Contents/MacOS/KernelEventMonitor (for architecture i386): Mach-O bundle i386
BuildRoot/private/var/tmp/configd_plugins/configd_plugins-91.root/System/Library/SystemConfiguration/KernelEventMonitor.bundle/Contents/MacOS/KernelEventMonitor (for architecture ppc7400): Mach-O bundle ppc</span>
#### gdb does not compile
Software development (for example, of PureFoundation or device drivers) is hampered by the lack of a native debugged for Darwin. gdb uses parts of the old Carbon runtime in a single component. However, this is preventing the package as a whole from compiling. Non-Apple gdb cannot be used because it does not understand Darwin's Mach-O binary format. (You only need to install DebugSymbols.framework and CoreServices.framework into PureDarwin Xmas to get gdb running, but since these are closed-source and non-distributable you wouldn't want to do that, would you?)
#### DirectoryService daemon depends on missing CFLite functions
DirectoryServices, the daemon responsible for (surprise surprise) Directory Services, makes use of CFFileDescriptors and CFNotificationCenters, neither of which are present in the current release of CFLite. The latest patched CFLite produced as part of the PureFoundation project includes basic implementations of these functions which allows DirectoryService to run. 

------------------------------------------------------------------------

### Problems with partial workarounds
#### OpenDirectory depends on Foundation
OpenDirectory depends on Foundation which is not available in Darwin.
This is a vital component of Darwin linked implicitly to the login infrastructure, consequently multi-user mode fails.
<span style="font-family:courier new,monospace"><span style="font-size:small">passwd</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">dyld: Library not loaded: /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">  Referenced from: /System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/OpenDirectory</span></span></span>
<span style="color:rgb(255,0,0)">The dependency of the OpenDirectory project on Foundation should be removed. <span style="color:rgb(0,0,0)"><http://darwinbuild.macosforge.org/trac/ticket/49> </span></span>
See Foundation replacement called [PureFoundation](news/purefoundation.html).
#### launchd does not build
This is a mission critical component of Darwin.
<http://darwinbuild.macosforge.org/trac/ticket/9>
Maybe related: "Logged as radar 5802196: Unable to build TOT launchd from macosforge.org" ([source](http://www.nabble.com/launchd-(257)-not-building-td16087000.html))
<span>[<span style="color:rgb(255,0,0)">Patched</span>](news/purity-patches.html)<span style="color:rgb(255,0,0)"> its</span></span><span style="color:rgb(255,0,0)"> sources. Please let us know if you know a cleaner solution.</span>
#### IOKitUser does not build
<span>[<span style="color:rgb(255,0,0)">Patched</span>](news/purity-patches.html)</span><span style="color:rgb(255,0,0)"> its sources. Please let us know if you know a cleaner solution.</span>

------------------------------------------------------------------------

### Problems that are problems no more
#### diskarbitrationd fails with "_SCSerialize() failure" errors
This was caused by CFLite not supporting a certain mode of operation of a particular CF function. Building CFLite with the latest PureDarwin patch will restore this functionality and allow diskarbitrationd to run correctly.
#### CF missing symbols
<span style="font-style:italic">_</span><span>_kCFBundleResourceSpecificationKey</span> referenced by some dependents (e.g., Security framework) is expected in CF but missing. Patching the source code to restore this symbol and others (for example, exception names) has proved successful. To apply these patches, follows the instructions for initialising the darwinbuild environment as described in [Using DarwinBuild](developers/darwinbuild.html).
#### libauto.dylib <span style="text-decoration:line-through">missing</span>
<span style="color:rgb(39,78,19)">Apple has </span>[<span style="color:rgb(39,78,19)">released</span>](news/autozone.html)<span style="color:rgb(39,78,19)"> autozone-77 under the Apache License 2.0. Thanks, Apple!</span>

