![](/PD-Opennow.jpg)

[Darwin](http://en.wikipedia.org/wiki/Darwin_%28operating_system%29) is the Open Source operating system from Apple that forms the basis for macOS, and PureDarwin is a community project to make Darwin more usable (some people think of it as the informal successor to OpenDarwin).

One current goal of this project is to provide a useful bootable IMG and Virtual of Darwin 10.x
Another goal of this project is to provide additional documentation. [More](https://github.com/PureDarwin/PureDarwin/wiki/About)...

Documentation and quick hints
-----------------------------
Please see our [PureDarwin Wiki](https://github.com/PureDarwin/PureDarwin/wiki/) It would be very kind if you could fix the wiki as we have links that are broken as we p

See the [Changelog](https://github.com/PureDarwin/PureDarwin/wiki/_history) for recent updates of this Wiki.

*NEW!* Getting the code
-------------------------
We have [GitHub](https://github.com/PureDarwin/), and encourage visitors to use the GitHub repository for both contribution, and checking out the latest build source. 

Additionally, as an interim measure, a [version of PureDarwin Xmas](https://github.com/PureDarwin/LegacyDownloads/releases/download/PDXMASNBE01/NewBootEnvironment-XMas-1.7z) with a fixed boot sector, which is compatible with QEMU is also available. 

Status
------

PureDarwin is currently working on AHCI and eMMC family/drivers for Darwin only they will not support/work on Apple's macOS. We have a PoC(Point of Concept) of PureDarwin 2.2 qemu image that's based on Apple's open source code of [macOS 10.10.5](http://opensource.apple.com/release/os-x-10105/) that is only currently available to those who join our IRC channel #puredarwin on freenode. 

We are currently working on getting a base Image of PureDarwin 3.6 that's based on  Apple's open source code of [macOS 10.12.3](https://opensource.apple.com/release/macos-10123.html)

We are looking for supporters/coders that can help bring about faster Development of PureDarwin while showing Apple that there is still a community of Open Source Darwin Supporters that would like to see more openness from them whether it be from them releasing Binary Drivers for our use as they once did or open source projects like libxpc/launchd again.

[PureDarwin's Current Build Status](https://puredarwin.github.io/Status.md)

Please join us on freenode.net #puredarwin for our info we have USA/UK/Europe Devs who which can receive hardware.



## **Something to the Open Source Community!**

### **Here's a guide on Building XNU of the 16.4(10.12.3) Kernel!**  
   
### Open Terminal && Run these commands in order to build a useable XNU Kernel

### Make a Directory called "xnu_build" on your Desktop && cd to it 

```
mkdir -p ~/Desktop/xnu_build
cd ~/Desktop/xun_build
```

### Curl these files from opensource.apple.com

```
curl -O https://opensource.apple.com/tarballs/dtrace/dtrace-209.20.4.tar.gz && curl -O https://opensource.apple.com/tarballs/AvailabilityVersions/AvailabilityVersions-26.30.3.tar.gz && curl -O https://opensource.apple.com/tarballs/xnu/xnu-3789.41.3.tar.gz 
```

### Run this command to untar all downloaded files and rm the tar.gz files

```
 	for file in *.tar.gz; do tar -zxf $file; done && rm -f *.tar.gz
```

### Setting up Pre-build Envoerment 
```
git clone https://github.com/PureDarwin/XNU-16.4-Setup-Build.git   

cd XNU-16.4-Setup-Build   

SDK_ROOT=`xcodebuild -version -sdk macosx Path`
CURRENT_DIR=`pwd`
sudo mkdir -p "${SDK_ROOT}/usr/local/include/kernel/os"
sudo mkdir -p "${SDK_ROOT}/usr/local/lib/kernel"
sudo cp -rf "${CURRENT_DIR}/libdispatch/firehose_buffer_private.h" "${SDK_ROOT}/usr/local/include/kernel/os/"
sudo cp -rf "${CURRENT_DIR}/libdispatch/libfirehose_kernel.a" "${SDK_ROOT}/usr/local/lib/kernel/"   

cd ../

```

### Building Dtrace and Avaliablilty -- copy each line by line and paste into terminal 

```
	cd dtrace-209.20.4
	mkdir -p obj sym dst
	xcodebuild install -target ctfconvert -target ctfdump -target ctfmerge ARCHS="x86_64" SRCROOT=$PWD OBJROOT=$PWD/obj SYMROOT=$PWD/sym DSTROOT=$PWD/dst
	sudo ditto $PWD/dst/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain
	cd ..
	cd AvailabilityVersions-26.30.3
	mkdir -p dst
	make install SRCROOT=$PWD DSTROOT=$PWD/dst
	sudo ditto $PWD/dst/usr/local `xcrun -sdk macosx -show-sdk-path`/usr/local
	cd ..
```

### Building XNU 16.4

```
cd xnu-3789.41.3/
sudo make SDKROOT=macosx ARCH_CONFIGS=X86_64 KERNEL_CONFIGS=RELEASE
```



FAQ
-------

What is Darwin?

Darwin is the Open Source operating
system from Apple that forms the
basis for Mac OS X, and PureDarwin is
a community project to make Darwin
more usable (some people think of it
as the informal successor to OpenDarwin).

What is PureDarwin?

The goal of this project is to make
Darwin more usable by providing an
installation ISO, documentation, and
add-on software. You are welcome to
join #puredarwin on irc.freenode.net
if you would like to join PureDarwin
development and to add to
www.puredarwin.org

How usable is PureDarwin?

PureDarwin can run on VMware as well
as real Intel-based hardware. We are
successfully running a web server, have
built hundreds of software packages
with MacPorts running on PureDarwin,
including ssh, apache2, tightvnc, Xfce,
and others.

Why spend time on Darwin?

For learning and fun.

How does PureDarwin relate to the
former OpenDarwin project?

Although some people have been
seeing PureDarwin as the informal
successor to OpenDarwin, there is no
official relationship other than the fact
that OpenDarwin and PureDarwin are
both downstream Darwin projects.
Also, it is no secret that PureDarwin
would not exist if OpenDarwin had not
closed down. Coming later in time,
PureDarwin is in the fortunate position
to be able to benefit from the valuable
contributions that were rooted in the
OpenDarwin project.

How does PureDarwin relate to the
DarwinBuild project?

DarwinBuild is one of PureDarwin‘s
main upstream projects.

What does the „Pure“ in PureDarwin
stand for?

Pure as in beer! It means that we just use components specifically released
by Apple for use with Darwin, as well as other Open Source components (coll
ectively called „upstream code“). Specifically, it means that we do not
use any components from macOS. It also means that we try to stay as close
as possible to the „outside world“ as in macOS (e.g., regarding the choice
of compilers, options, etc.). It does not
mean, however, that we do not modify
and add to the upstream code, to
the extent that the respective licenses
allow.

How can I help PureDarwin?

Pretty much on all fronts. Especially if
you are skilled in C, C++, ObjC, Mac OS
X, BSD, etc. you should consider joining
#puredarwin on irc.freenode.net

Credits
-------

We would like to thank
-   Apple, Inc. for releasing Darwin as Open Source 
-   kvv and _wms for their continuing help
-   David Elliott for his work on boot-132
-   The Chameleon team for their work on boot-132
-   The xnu-dev team for their work on the XNU kernel
-   Stuart Crook for his work on PureFoundation
-   Guillaume Verdeau for his work on X.Org
-   [Rafirafi](https://github.com/rafirafi) for his work on Generic Platform kexts
-   [Clifford Sekel](https://github.com/csekel/) aka IRC InSaneDarwin for his work on AHCI and eMMC Family/Drivers(still in active development)
-   Mac OS Forge 
-   The DarwinBuild project 
-   The MacPorts project
-   The folks at #macosforge, #macports, #macdev, #opendarwin, #puredarwin, 
-   Everyone else contributing to Darwin 

© 2017 PureDarwin Foundation 
