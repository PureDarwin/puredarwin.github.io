Current Blockers
================
This page lists the current issues we are having that prevent us from making a Darwin 9 ISO. The contents of this page are subject to change.

### 1. Problems to be solved
#### 1.1 `CFOpenDirectory` missing in `CFOpenDirectory` binary root
`OpenDirectory` framework depends on `CFOpenDirectory` framework, for which there is both a project and a binary root.
However, the binary root does not contain the actual `CFOpenDirectory` file ([http://darwinbuild.macosforge.org/trac/ticket/50](http://darwinbuild.macosforge.org/trac/ticket/50)):

    otool -L OpenDirectory.root/System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/OpenDirectory | grep CFO
    /System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/Frameworks/CFOpenDirectory.framework/Versions/A/CFOpenDirectory 
    (compatibility version 1.0.0, current version 1.0.0) 

The sources cannot be built without being patched because it depends on missing `CoreFoundation` headers (e.g., `CoreFoundation/CFBridgingPriv.h`) and on `DirectoryServiceCore` (part of `DirectoryService` which cannot yet be built too).

#### 1.2 `IOHDIXController.kext` needed (image boot support)
BinaryDriver `IOHDIXController.kext` is missing ([used to be available](Legal#licensed-material) under Apple Driver License) in order to use [imageboot](Live_CD#alternative-2-using-imageboot).
Please let us know if you know a solution.
#### 1.3 `OSvKernDSPLib.kext` needed (audio support)
BinaryDriver `OSvKernDSPLib.kext` is missing, consequently `IOAudioFamily.kext` cannot be loaded resulting in no audio support.

Please let us know if you know a solution.
#### 1.4 Shortage of network drivers
There is a shortage of network drivers (and of other drivers in general) for Darwin.
Of particular concern, the Intel e1000 driver `AppleIntel8254XEthernet.kext`, needed to run networking under VMWare, while available in OS X are not available for general distribution nor redistributable. 
Open source drivers for a vast number of network cards (and hardware of every type) are available for other platforms (e.g., BSD and GNU/Linux). See the [Network](Network) page for more information.
It would be great if someone skilled in driver programming could port some of these to Darwin (we are told that writing drivers for IOKit is really a rather nice experience).
#### 1.5 `SystemConfiguration.framework` is incomplete
SystemConfiguration.framework (in the configd package) does not compile, and the binary root made available is incomplete. While some components can be made to compile individually (see the [Network](Network) page for a download), there are still important components (ATConfig and KernelEventMonitor) missing.
KernelEventMonitor can be built (part of configd_plugins which not build because it depends on configd which not build without patch and code sacrifice):

    file BuildRoot/private/var/tmp/configd_plugins/configd_plugins- 
    91.root/System/Library/SystemConfiguration/KernelEventMonitor.bundle/Contents/MacOS/KernelEventMonitor
    BuildRoot/private/var/tmp/configd_plugins/configd_plugins- 
    91.root/System/Library/SystemConfiguration/KernelEventMonitor.bundle/Contents/MacOS/KernelEventMonitor: Mach-O universal binary with 2 
    architectures
    BuildRoot/private/var/tmp/configd_plugins/configd_plugins- 
    91.root/System/Library/SystemConfiguration/KernelEventMonitor.bundle/Contents/MacOS/KernelEventMonitor (for architecture i386): Mach-O 
    bundle i386
    BuildRoot/private/var/tmp/configd_plugins/configd_plugins- 
    91.root/System/Library/SystemConfiguration/KernelEventMonitor.bundle/Contents/MacOS/KernelEventMonitor (for architecture ppc7400): Mach-O 
    bundle ppc

#### 1.6 gdb does not compile
Software development (for example, of PureFoundation or device drivers) is hampered by the lack of a native debugged for Darwin. gdb uses parts of the old Carbon runtime in a single component. However, this is preventing the package as a whole from compiling. Non-Apple gdb cannot be used because it does not understand Darwin's Mach-O binary format. (You only need to install DebugSymbols.framework and CoreServices.framework into PureDarwin Xmas to get gdb running, but since these are closed-source and non-distributable you wouldn't want to do that, would you?)
#### 1.7 DirectoryService daemon depends on missing CFLite functions
DirectoryServices, the daemon responsible for (surprise surprise) Directory Services, makes use of CFFileDescriptors and CFNotificationCenters, neither of which are present in the current release of CFLite. The latest patched CFLite produced as part of the PureFoundation project includes basic implementations of these functions which allows DirectoryService to run. 

------------------------------------------------------------------------

### 2. Problems with partial workarounds
#### 2.1 OpenDirectory depends on Foundation
OpenDirectory depends on Foundation which is not available in Darwin.
This is a vital component of Darwin linked implicitly to the login infrastructure, consequently multi-user mode fails.

    passwd
    dyld: Library not loaded: /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation
      Referenced from: /System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/OpenDirectory

The dependency of the OpenDirectory project on Foundation should be removed. http://darwinbuild.macosforge.org/trac/ticket/49
See Foundation replacement called [PureFoundation](PureFoundation).
#### 2.2 launchd does not build
This is a mission critical component of Darwin.
<http://darwinbuild.macosforge.org/trac/ticket/9>
Maybe related: "Logged as radar 5802196: Unable to build TOT launchd from macosforge.org" ([source](http://www.nabble.com/launchd-(257)-not-building-td16087000.html))

[Patched](Purity_patches_for_IOKitUser,_launchd,_objc4) its sources. Please let us know if you know a cleaner solution.
#### 2.3 IOKitUser does not build
[Patched](Purity_patches_for_IOKitUser,_launchd,_objc4) its sources. Please let us know if you know a cleaner solution.

------------------------------------------------------------------------

### 3. Problems that are problems no more
#### 3.1 diskarbitrationd fails with "_SCSerialize() failure" errors
This was caused by CFLite not supporting a certain mode of operation of a particular CF function. Building CFLite with the latest PureDarwin patch will restore this functionality and allow diskarbitrationd to run correctly.
#### 3.2 CF missing symbols
__kCFBundleResourceSpecificationKey referenced by some dependents (e.g., Security framework) is expected in CF but missing. Patching the source code to restore this symbol and others (for example, exception names) has proved successful. To apply these patches, follows the instructions for initialising the darwinbuild environment as described in [Using DarwinBuild](DarwinBuild).
#### 3.3 libauto.dylib ~~missing~~
Apple has [released](news/autozone.html) autozone-77 under the Apache License 2.0. Thanks, Apple!

