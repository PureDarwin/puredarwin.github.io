PureDarwin Xmas
===============

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/PD-Xmas.jpg)

The PureDarwin project announces the immediate availability of "PureDarwin Xmas", a developer preview of the upcoming operating system based on Apple's Darwin 9 sources and other Open Source projects such as X11. At the same time, the PureDarwin project would like to invite the community to discuss, participate and contribute. The developer preview is available for download as a pre-configured virtual machine for VMware Fusion 2.0 on Macintosh, and the code used to generate it is available in a Subversion repository.

[Darwin](http://en.wikipedia.org/wiki/Darwin_%28operating_system%29) is the Open Source operating system from Apple that forms the basis for Mac OS X, and PureDarwin is a community project to make Darwin more usable (some people think of it as the informal successor to OpenDarwin). One current goal of this project is to provide a bootable ISO of Darwin 9.x (the version that corresponds to 10.5.x Leopard). Another goal of this project is to provide additional documentation. [More](https://github.com/PureDarwin/PureDarwin/wiki/About)...

### Download
-   [XZ-compressed TAR archive](http://code.google.com/p/puredarwin/downloads/detail?name=puredarwinxmas.tar.xz) (hosted on Google Code) - SHA-1 checksum: `80f88f44cc540ea05aa847bb18b94bdd133b6c07`
-   [BZip2-compressed TAR archive](http://xref.puredarwin.org/puredarwinxmas.tar.bz2) (hosted on XRef) - MD5 checksum: `fd0ade4da224475e5dc33c2c11d9d0bc`

[VMware](https://github.com/PureDarwin/PureDarwin/wiki/VMware) Fusion 2 virtual machine or [VirtualBox](https://github.com/PureDarwin/PureDarwin/wiki/VirtualBox)

### Showcase 

This is expected to work.

with VMware
-   Darwin 9 boots in a VMware Fusion 2 virtual machine on a Macintosh
-   DTrace 
-   X11
-   ZFS

with VirtualBox
-   see [VirtualBox](https://github.com/PureDarwin/PureDarwin/wiki/VirtualBox)

A [screencast](http://video.google.com/videoplay?docid=2258011422088941976) demonstrating some of Xmas's functionality is available on Google Video.

### Known issues

These issues will be addressed in future releases.
-   Works with VMware Fusion 2 on Macintosh, VirtualBox on Linux
-   login does not work, user is working as root
-   Lots of error messages during the boot process
-   X11 does not work with mach_kernel.voodoo
-   WindowMaker will not be the default WM
-   halt doesn't work reliably, "shutdown -h now" doesn't work reliably
-   /var/log gets filled quickly
-   No network
-   Due to a [restriction](http://communities.vmware.com/thread/183426) of VMware Fusion 2.0.1, you cannot run PureDarwin Xmas on 32-bit CPUs such as the Core Duo in the first-generation Intel Macs (Thanks gireesh). However, you can downgrade to VMware Fusion 2.0.0 which seems to run Darwin fine on a 32-bit CPU (thanks Stuart).

Want to help us on these? Check out the code from svn or hg repository and start hacking...

### Frequently asked questions

-   **What is PureDarwin Xmas?**
This is a developer preview to get people interested in PureDarwin and to attract developers.
It is intended to run on VMware Fusion 2 on Macintosh.
We call this developer preview "Xmas" because it contains X11, and after all it's Christmas time.

-   **Is this close to what the final PureDarwin will be?**
Not at all. It is just a proof-of-concept to show that Darwin 9 is alive.

-   **Is this an Apple product?**
No. Darwin is an upstream project from Apple, but the PureDarwin project is not affiliated with Apple. We pay attention to follow any Apple and third-party licenses closely, though.

-   **Which license is this under?**
This is a distribution that packages various individual parts. What the PureDarwin project has done from scratch is generally licensed under the new BSD license. However, most parts come from upstream (Apple and third-party) projects and are licensed under their respective licenses, such as the APSL, the Apple Driver License, the GPL, and others.

-   **Where are the sources?**
Sources for Darwin can be found at [http://opensource.apple.com](http://opensource.apple.com/) and <http://darwinbuild.macosforge.org/>, sources for third-party software can be found at <http://www.macports.org/>, and sources from the PureDarwin project migrated from
can now be found here: <http://github.com/PureDarwin/PureDarwin>
<http://code.google.com/p/puredarwin/source/checkout>

-   **How do I contact the PureDarwin project?**
We are on #puredarwin on irc.freenode.net most of the time, and this is our preferred communications channel. We also read the Darwin mailing lists, especially darwin-dev and darwinbuild-dev.

### Screenshots

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/puredarwin_Xmas_red_X.png)

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/puredarwin%20Xmas%20green%20dtrace.png)

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/puredarwin_xmas_zfs_blue.png)

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/puredarxin_xmas_UNIX_yellow.png)
