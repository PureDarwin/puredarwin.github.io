ZFS
===
.
 
MacZFS.org {style="font-family:Arial,Verdana,sans-serif;line-height:normal"}
----------
Enthusiasts of ZFS and of PureDarwin will want to read the whole web site from the beginning, for an idea of what's to come from the alliance of these two communities and their technologies. PureDarwin users will require [manual installation](http://code.google.com/p/maczfs/wiki/FAQ#How_do_I_install_MacZFS_manually?) for now, in order to upgrade to the latest stable release of MacZFS. From there, all other MacZFS.org documentation is generally relevant.
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">
 </span>All development of ZFS on Mac OS takes place at [MacZFS.org](http://maczfs.org/). They host packages for Mac OS, and that can be manually installed upon PureDarwin.


The ZFS implementation that runs on Mac OS X (and Darwin) can be downloaded or compiled.

Fyi, ZFS is [pure](../developers/macports/purity.html).
Parts of ZFS
------------
On Mac OS X (and Darwin), ZFS consists of the following parts:

<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">A filesystem,* /System/Library/Filesystems/*<span style="font-weight:bold">*zfs.fs*
 Contained therein is, among other things, a command-line tool called zfs.util</span></span>

Command-line tools in /usr/sbin, 
1.  **zpool** (configures ZFS storage pools)
2.  **zfs** (configures ZFS file systems)
3.  **zoink** (misc)
4.  zfs.util (ZFS file system utility)
A settings file, /etc/zfs/zpool.cache (a cache that describes active ZFS pools on the system)
The device **/dev/zfs**, this is created automatically when zfs.kext gets loaded (which happens whenever you call the zfs command-line tool, for example).
#### Filesystem kext
As mentioned above, zfs.kext is not a regular kernel extension but instead is a filesystem kext. Among other things, this means that it is not loaded at boot time, but is loaded automatically on demand through kextload. Unfortunately, documentation on filesystem kexts is hard to find.

### Performance, Integrity and Stability
Sun (and the FreeBSD project) recommend that at least 512MB of RAM is available, to ensure that ZFS performs reliably, although it will work on systems with less than 512MB with suboptimal performance. ZFS was designed to perform best on 64-bit systems, although it works on 32-bit systems.
### Building ZFS
*This section will be updated, pending the official integration of MacZFS into PureDarwin.  The old instructions are provided for reference in the hope that you will help to update it.*

Our favorite way is through [darwinbuild](../developers/darwinbuild.html) via a custom plist containing the paste below. You will notice that only two architectures have been specified, because it does not yet build on 64bits arch (ppc64 or x86_64). `darwinbuild zfs' is pretty straight forward.

 `zfs = {`
 `configuration = "Leopard_Release";`
 `dependencies = {`
 `lib = (`
 `Libsystem,`
 `dyld,`
 `libgcc,`
 `ncurses,`
 `);`
 `};`
 `environment = {`
 `"RC_ARCHS" = "i386 ppc";`
 `};`
 `"source_sites" = (`
 `"http://puredarwin.googlecode.com/hg/Mirror/",`
 `"http://puredarwin.googlecode.com/svn/Mirror/",`
 `);`
 `version = "119";`
 `};`
### Resources
<http://en.wikipedia.org/wiki/ZFS>
<http://opensolaris.org/os/community/zfs/>

<span style="font-family:arial,sans-serif;font-size:12px">[http://groups.google.com/group/zfs-macos](http://www.google.com/url?sa=D&q=http://groups.google.com/group/zfs-macos)</span>
<http://maczfs.org/>
[Sun Solaris ZFS Administration Guide](http://docs.sun.com/app/docs/doc/819-5461?l=en)
[Getting Started Guide for MacZFS](http://code.google.com/p/maczfs/wiki/GettingStarted)
[MacZFS FAQ](http://code.google.com/p/maczfs/wiki/FAQ)
[MacZFS mailing list](https://groups.google.com/forum/?fromgroups#!forum/zfs-macos)


