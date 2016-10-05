ZFS
===
<span style="border-collapse:separate;line-height:19px">ZFS stands for "[Zettabyte File System](http://en.wikipedia.org/wiki/ZFS)". It was designed and implemented by a team at Sun Microsystems led by <span style="font-style:italic">Jeff Bonwick</span>. Since the release of Darwin 9, ZFS became a core platform technology; and work is well underway to realise its full potential within PureDarwin</span><span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">.
 </span>
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:432px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** MacZFS.org](zfs.html#TOC-MacZFS.org)
2.  [**2** Parts of ZFS](zfs.html#TOC-Parts-of-ZFS)
    1.  [**2.1** Filesystem kext](zfs.html#TOC-Filesystem-kext)
    2.  [**2.2** Performance, Integrity and Stability](zfs.html#TOC-Performance-Integrity-and-Stability)
    3.  [**2.3** Building ZFS](zfs.html#TOC-Building-ZFS)
    4.  [**2.4** Resources](zfs.html#TOC-Resources)


<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px"> </span>
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
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">A filesystem kext, <span style="font-style:italic">System/Library/Extensions/</span><span style="font-weight:bold"><span style="font-style:italic">zfs.kext</span></span>
 Whenever zfs is used, this kext gets loaded. Being a filesystem kext, it is not loaded at boot time (unlike other kexts), but dynamically when needed (this requires a working kextload on the system).
 There may also be a <span style="font-style:italic">zfs.readonly.kext</span>, which is a temporary placeholder on Mac OS X and is not needed for the purposes of PureDarwin.</span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">A filesystem,<span style="font-style:italic"> /System/Library/Filesystems/</span><span style="font-weight:bold"><span style="font-style:italic">zfs.fs</span>
 <span style="font-weight:normal">Contained therein is, among other things, a command-line tool called </span>zfs.util</span></span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">A library, <span style="font-weight:bold">libzfs.dylib</span></span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Command-line tools in /usr/sbin, </span>
1.  <span style="font-weight:bold">zpool</span> (configures ZFS storage pools)
2.  <span style="font-weight:bold">zfs</span> (configures ZFS file systems)
3.  <span style="font-weight:bold">zoink</span> (misc)
4.  zfs.util (ZFS file system utility)
A settings file, /etc/zfs/zpool.cache (a cache that describes active ZFS pools on the system)
The device <span style="font-weight:bold">/dev/zfs</span>, this is created automatically when zfs.kext gets loaded (which happens whenever you call the zfs command-line tool, for example).
#### Filesystem kext
As mentioned above, zfs.kext is not a regular kernel extension but instead is a filesystem kext. Among other things, this means that it is not loaded at boot time, but is loaded automatically on demand through kextload. Unfortunately, documentation on filesystem kexts is hard to find.

### Performance, Integrity and Stability
Sun (and the FreeBSD project) recommend that at least 512MB of RAM is available, to ensure that ZFS performs reliably, although it will work on systems with less than 512MB with suboptimal performance. ZFS was designed to perform best on 64-bit systems, although it works on 32-bit systems.
### Building ZFS
*This section will be updated, pending the official integration of MacZFS into PureDarwin.  The old instructions are provided for reference in the hope that you will help to update it.*

Our favorite way is through [darwinbuild](../developers/darwinbuild.html) via a custom plist containing the paste below. You will notice that only two architectures have been specified, because it does not yet build on 64bits arch (ppc64 or x86_64). `darwinbuild zfs' is pretty straight forward.

<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">zfs = {</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">configuration = "Leopard_Release";</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">dependencies = {</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">lib = (</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">Libsystem,</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">dyld,</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">libgcc,</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">ncurses,</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">);</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">};</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">environment = {</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">"RC_ARCHS" = "i386 ppc";</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">};</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">"source_sites" = (</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">"http://puredarwin.googlecode.com/hg/Mirror/",</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">"http://puredarwin.googlecode.com/svn/Mirror/",</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">);</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">version = "119";</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">};</span></span>
### Resources
<http://en.wikipedia.org/wiki/ZFS>
<http://opensolaris.org/os/community/zfs/>

<span style="font-family:arial,sans-serif;font-size:12px">[http://groups.google.com/group/zfs-macos](http://www.google.com/url?sa=D&q=http://groups.google.com/group/zfs-macos)</span>
<http://maczfs.org/>
[Sun Solaris ZFS Administration Guide](http://docs.sun.com/app/docs/doc/819-5461?l=en)
[Getting Started Guide for MacZFS](http://code.google.com/p/maczfs/wiki/GettingStarted)
[MacZFS FAQ](http://code.google.com/p/maczfs/wiki/FAQ)
[MacZFS mailing list](https://groups.google.com/forum/?fromgroups#!forum/zfs-macos)


