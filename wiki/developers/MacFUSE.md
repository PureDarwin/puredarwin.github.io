MacFUSE
=======
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
![](/img/developers/macfuse/macfuse-icon.png)
[MacFUSE](http://code.google.com/p/macfuse/) is a filesystem in userland. It runs well on PureDarwin and can be used to mount sshfs, ramdisk and other FUSE-based filesystems. It is, according to its maintainers, "The Easiest and Fastest Way to Create File Systems for Mac OS X" (and PureDarwin, one might add).

### Installing MacFUSE
MacFUSE can be installed from the official MacFUSE.pkg (from the MacFUSE site) on PureDarwin with the following commands:

cd / ; gunzip -c "MacFUSE.pkg/Contents/Resources/10.5/MacFUSE Core.pkg/Contents/Archive.pax.gz"  | pax -r
chown -R root:wheel /Library/Filesystems/fusefs.fs/Support/fusefs.kext  
chmod -R 755 /Library/Filesystems/fusefs.fs/Support/fusefs.kext

Now MacFUSE is ready to use on PureDarwin.
### sshfs
sshfs allows you to mount volumes over SSH.

Install the sshfs filesystem with
curl "http://macfuse.googlecode.com/svn/trunk/filesystems/sshfs/binary/sshfs-static-leopard" > /usr/sbin/mount_sshfs
chmod a+x /usr/sbin/mount_sshfs

Now we can mount a remote filesystem with
mkdir /Volumes/SSHVolume/
mount_sshfs user@some.host:/ /Volumes/SSHVolume/ -oauto_cache,reconnect,volname=SSHVolume
### ramdisk
**Status:** functional in PureDarwin (Darwin 9)

ramdisk is, as its name implies, a ramdisk implemented in MacFUSE.
Install it with

svn co http://thebends.googlecode.com/svn/trunk/ramdisk/ ramdisk
cd ramdisk/
make
cp ramdisk /usr/sbin/mount_ramdisk
cd -
rm -rf ramdisk/


Now we can use the ramdisk command to create ramdisks:

mkdir /some/path
mount_ramdisk /some/path
#### Troubleshooting in building ramdisk and targetting Darwin 9
In case you plan to build it on Darwin 10, a couple of adjustements must be made.
Edit the Makefile and replace this line in order to be able to run it on Darwin 9:

CC = g++

by this line
CC = MACOSX_DEPLOYMENT_TARGET=10.5  g++

And this line

OPTS = -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26
by this line
OPTS = -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -arch i386


**Problem:** If you encounter:

file.cpp: In constructor 'ramdisk::File::File(ramdisk::Dir*, mode_t)':
file.cpp:17: error: 'assert' was not declared in this scope
cc1plus: warnings being treated as errors
or encounter

<span style="font-size:small">dir.cpp: In function 'void ramdisk::assertNoSubdirs(const std::string&)':</span>
dir.cpp:11: error: 'assert' was not declared in this scope
[...]
dir.cpp:228: error: 'assert' was not declared in this scope
**Solution: **Simply add #include <assert.h> in *file.h* per example.

**Problem:** cc1plus: warnings being treated as errors
file.cpp: In member function 'virtual size_t ramdisk::File::Read(char*, size_t, off_t)':
file.cpp:26: warning: comparison between signed and unsigned integer expressions
**Solution:** Replace in file.cpp this line

  if (offset < len) {

by this line

  if ((size_t) offset < len) {

Then after a `make clean' and `make', everything should be fine and run on a PureDarwin release based on Darwin9:

MACOSX_DEPLOYMENT_TARGET=10.5 g++ -Wall -Werror -g -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -c node.cpp
MACOSX_DEPLOYMENT_TARGET=10.5 g++ -Wall -Werror -g -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -c file.cpp
MACOSX_DEPLOYMENT_TARGET=10.5 g++ -Wall -Werror -g -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -c dir.cpp
MACOSX_DEPLOYMENT_TARGET=10.5 g++ -Wall -Werror -g -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -c ramdisk.cpp
ar rcs libcommon.a node.o file.o dir.o ramdisk.o
MACOSX_DEPLOYMENT_TARGET=10.5 g++  -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -DFUSE_USE_VERSION=26 -o ramdisk main.cpp -L. -lcommon -lfuse



To be continued

