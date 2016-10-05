MacFUSE
=======
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](../_/rsrc/1263740487482/developers/macfuse/macfuse-icon.png)](macfuse/macfuse-icon.png%3Fattredirects=0)
[MacFUSE](http://code.google.com/p/macfuse/) is a filesystem in userland. It runs well on PureDarwin and can be used to mount sshfs, ramdisk and other FUSE-based filesystems. It is, according to its maintainers, "The Easiest and Fastest Way to Create File Systems for Mac OS X" (and PureDarwin, one might add).
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Installing MacFUSE](macfuse.html#TOC-Installing-MacFUSE)
2.  [**2** sshfs](macfuse.html#TOC-sshfs)
3.  [**3** ramdisk](macfuse.html#TOC-ramdisk)
    1.  [**3.1** Troubleshooting in building ramdisk and targetting Darwin 9](macfuse.html#TOC-Troubleshooting-in-building-ramdisk-and-targetting-Darwin-9)

### Installing MacFUSE
MacFUSE can be installed from the official MacFUSE.pkg (from the MacFUSE site) on PureDarwin with the following commands:

<span style="font-size:small">cd / ; gunzip -c "MacFUSE.pkg/Contents/Resources/10.5/MacFUSE Core.pkg/Contents/Archive.pax.gz"  | pax -r</span>
<span style="font-size:small">chown -R root:wheel /Library/Filesystems/fusefs.fs/Support/fusefs.kext  </span>
<span style="font-size:small">chmod -R 755 /Library/Filesystems/fusefs.fs/Support/fusefs.kext</span>

Now MacFUSE is ready to use on PureDarwin.
### sshfs
sshfs allows you to mount volumes over SSH.

Install the sshfs filesystem with
<span style="font-size:small">curl "http://macfuse.googlecode.com/svn/trunk/filesystems/sshfs/binary/sshfs-static-leopard" &gt; /usr/sbin/mount_sshfs</span>
<span style="font-size:small">chmod a+x /usr/sbin/mount_sshfs</span>

Now we can mount a remote filesystem with
<span style="font-size:small">mkdir /Volumes/SSHVolume/</span>
<span style="font-size:small">mount_sshfs user@some.host:/ /Volumes/SSHVolume/ -oauto_cache,reconnect,volname=SSHVolume</span>
### ramdisk
**Status:** functional in PureDarwin (Darwin 9)

ramdisk is, as its name implies, a ramdisk implemented in MacFUSE.
Install it with

<span style="font-size:small">svn co http://thebends.googlecode.com/svn/trunk/ramdisk/ ramdisk</span>
<span style="font-size:small">cd ramdisk/</span>
<span style="font-size:small">make</span>
<span style="font-size:small">cp ramdisk /usr/sbin/mount_ramdisk</span>
<span style="font-size:small">cd -</span>
<span style="font-size:small">rm -rf ramdisk/</span>


Now we can use the ramdisk command to create ramdisks:

<span style="font-size:small">mkdir /some/path</span>
<span style="font-size:small">mount_ramdisk /some/path</span>
#### Troubleshooting in building ramdisk and targetting Darwin 9
In case you plan to build it on Darwin 10, a couple of adjustements must be made.
Edit the Makefile and replace this line in order to be able to run it on Darwin 9:

<span style="font-size:small">CC = g++</span>

by this line
<span style="font-size:small">CC = MACOSX_DEPLOYMENT_TARGET=10.5  g++</span>

And this line

<span style="font-size:small">OPTS = -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26</span>
by this line
<span style="font-size:small">OPTS = -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -arch i386</span>


**Problem:** If you encounter:

<span style="font-size:small">file.cpp: In constructor 'ramdisk::File::File(ramdisk::Dir*, mode_t)':</span>
<span style="font-size:small">file.cpp:17: error: 'assert' was not declared in this scope</span>
<span style="font-size:small">cc1plus: warnings being treated as errors</span>
or encounter

<span style="font-size:small">dir.cpp: In function 'void ramdisk::assertNoSubdirs(const std::string&)':</span>
<span style="font-size:small">dir.cpp:11: error: 'assert' was not declared in this scope</span>
<span style="font-size:small">[...]</span>
<span style="font-size:small">dir.cpp:228: error: 'assert' was not declared in this scope</span>
<span style="font-weight:bold">Solution: </span>Simply add <span style="font-size:small">#include &lt;assert.h&gt;</span> in *file.h* per example.

**Problem:** <span style="font-size:small">cc1plus: warnings being treated as errors</span>
<span style="font-size:small">file.cpp: In member function 'virtual size_t ramdisk::File::Read(char*, size_t, off_t)':</span>
<span style="font-size:small">file.cpp:26: warning: comparison between signed and unsigned integer expressions</span>
**Solution:** Replace in file.cpp this line

<span style="font-size:small">  if (offset &lt; len) {</span>

by this line

<span style="font-size:small">  if ((size_t) offset &lt; len) {</span>

Then after a `make clean' and `make', everything should be fine and run on a PureDarwin release based on Darwin9:

<span style="font-size:small">MACOSX_DEPLOYMENT_TARGET=10.5 g++ -Wall -Werror -g -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -c node.cpp</span>
<span style="font-size:small">MACOSX_DEPLOYMENT_TARGET=10.5 g++ -Wall -Werror -g -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -c file.cpp</span>
<span style="font-size:small">MACOSX_DEPLOYMENT_TARGET=10.5 g++ -Wall -Werror -g -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -c dir.cpp</span>
<span style="font-size:small">MACOSX_DEPLOYMENT_TARGET=10.5 g++ -Wall -Werror -g -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -c ramdisk.cpp</span>
<span style="font-size:small">ar rcs libcommon.a node.o file.o dir.o ramdisk.o</span>
<span style="font-size:small">MACOSX_DEPLOYMENT_TARGET=10.5 g++  -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -o ramdisk main.cpp -L. -lcommon -lfuse</span>



To be continued

