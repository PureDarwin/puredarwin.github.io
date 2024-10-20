Deploying MacPorts on PureDarwin
================================

The recommended way to use MacPorts to produce binaries for PureDarwin is now to run MacPorts on a PureDarwin system.
This page is about deploying MacPorts on a PureDarwin system (thus, making PureDarwin a bit more self-hosted).
If you are interested in getting MacPorts to run on PureDarwin as quickly as possible, you can skip to the "quick method" at the end of this page.
**
**

Status
------
MacPorts is functional on PureDarwin 9 using the "quick method" at the end of this page.


![](/img/developers/macports/macportsonpuredarwin/macports_on_pd.jpg)



MacPorts 1.8.0 states depending its host.


  ----------------------------------------------------------------------------------------------------------- ----------------------------------------------------------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------- -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                        ** Mac OS X**                                                                              **DarwinBuild**   ** PureDarwin**
  ** build and deployement **         **YES**   ** YES**      ** YES**
  ** port fetch <port>**         **YES**   ** YES**       ****
   **port install <port>**    **YES**                                                                                **YES**                                              **YES**
  **/opt/local/[...]/<port>**                                     YES    YES       **YES**
  ----------------------------------------------------------------------------------------------------------- ----------------------------------------------------------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------- -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

As an example, the fortune project (one workaround consists to fetch the source only in a puredarwin chroot where the network is available from Mac OS X or to use [QEMU](../qemu.html) user mode network stack ) built and run:


![](/img/developers/macports/macportsonpuredarwin/fortune_from_macports.png)


__Notes:__ On Mac OS X (the host and build environment), darwinbuild comes from macports (port install darwinbuild).
And in the custom plist of darwinbuild, there is an entry for MacPorts 1.7.0, in order to install it in the BuildRoot (the guest and pseudo darwin environement) of darwinbuild.
Then, in the BuildRoot, the freshly installed MacPorts project could be used to install the DarwinBuild project inside.
"Infinite loop" makes sense.


To illustrate:

![](/img/developers/macports/macportsonpuredarwin/macportsvsdarwinbuild.png)
Getting MacPorts
----------------
### Fetching MacPorts in a PureDarwin VM
#### Via Network
With [QEMU user mode network stack](../qemu.html), retrieve MacPorts sources via curl 

![](/img/developers/macports/macportsonpuredarwin/macportscurldownload.png)
#### Local copy
Opening the archive file in rw (.vmdk, .iso, etc..), and drop the source inside.

Building MacPorts
-----------------
### Compiling MacPorts in a PureDarwin vm
Do not remove headers and others needed files in `pd_setup' stages.


External requirements (built in MacPorts):

`tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.6_0+threads.i386.tbz2`


It will not be missing in the future releases, but in case for `env':

CFLAGS=-I/opt/local/include
LDFLAGS=-L/usr/local/lib

In order to provide the famous *Availability.h* (part of Carbon which has been released (thx Apple!) as headers) needed by many projects in darwinbuild:
tar xzvf /Users/aladin/PureDarwin/darwinbuild/9J61/Packages/CarbonHeaders.hdrs.tar.gz
tar xzvf /Users/aladin/PureDarwin/darwinbuild/9J61/Packages/CarbonHeaders.root.tar.gz (if there is a diff)
#### configure

Without X11:



With X11 from MacPorts:

`tar xjvf /opt/local/var/macports/packages/darwin/i386/xorg-libX11-1.1.5_1+x11_xcb.i386.tbz2`
`TCLSH=/opt/local/bin/tclsh ``./configure --without-objc-foundation --without-objc-runtime --with-x --x-includes=/usr/X11R6/include/ --x-libraries=/usr/X11R6/lib/ --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include --with-included-tclthread`


![](/img/developers/macports/macportsonpuredarwin/compiling_macports_in_puredarwin_configure.png)

#### make

![](/img/developers/macports/macportsonpuredarwin/compiling_macports_in_puredarwin_make_install.png)
#### make install

![](/img/developers/macports/macportsonpuredarwin/compiling_macports_in_puredarwin_make.png)

### Compiling MacPorts 1.7.0 in DarwinBuild

A first interesting way is to use the DarwinBuild project to build (and package) MacPorts for PureDarwin.

This is a work in progress, a new entry in a custom plist is needed:

 `MacPorts = {`
 `"source_sites" = (`
 `"http://puredarwin.googlecode.com/svn/Mirror",`
 "http://svn.macports.org/repository/macports/downloads/MacPorts-1.7.0",
 `);`
 `version = 1.7.0;`
 `};`
**Problem: **`/Volumes/Builds/9G55/BuildRoot/private/var/tmp/MacPorts/MacPorts-1.7.0.root is empty. Build verification failed.`
How can we tell to darwinbuild to configure & make the project (except the way consisting of repackaging the archive with a custom makefile (makefile is autodetected by darwinbuild))?
****


We can continue the compilation process by hand for now..

`cd /Volumes/Builds/9G55/BuildRoot `


TCL is a must for MacPorts.


tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.6_0+threads.i386.tbz2


Obviously, we need curl.


tar xjvf /opt/local/var/macports/packages/darwin/i386/curl-7.19.2_0+ipv6.i386.tbz2



or

<span style="font-size:small"><span style="font-family:courier new,monospace">cd .. && darwinbuild -init 9G55pd1</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">darwinbuild curl && darwinbuild -load curl && cd BuildRoot</span></span>


Why not?

Then the configure step(s)..

cd SourceCache/MacPorts/MacPorts-1.7.0
`mount -t devfs devfs /dev`
ln -s /opt/local/bin/tclsh /usr/bin/
./configure --without-objc-foundation --with-x --x-includes=/usr/X11R6/include/ --x-libraries=/usr/X11R6/lib/ --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include --with-included-tclthread


`[...]`
`configure: creating ./config.status`
`config.status: creating Makefile`
`config.status: creating pkgIndex.tcl`
`make`

`[...]`
`===> making all in src/port`

`sed -e 's,@TCLSH@,/usr/bin/tclsh,g' -e 's,@TCL_PACKAGE_DIR@,/opt/local/lib/tcl8.5,g' portmirror.tcl > portmirror`
`sed -e 's,@TCLSH@,/usr/bin/tclsh,g' -e 's,@TCL_PACKAGE_DIR@,/opt/local/lib/tcl8.5,g' portindex.tcl > portindex`
`sed -e 's,@TCLSH@,/usr/bin/tclsh,g' -e 's,@TCL_PACKAGE_DIR@,/opt/local/lib/tcl8.5,g' port.tcl > port`
`===> making all in src/programs`
`make install`
`[...]`

`/usr/bin/tclsh src/dep_map_clean.tcl /opt/local/lib/tcl8.5`
`
`
`Congratulations, you have successfully installed the MacPorts system. To get the Portfiles and update the system, run:`
`
`
`sudo port -v selfupdate`
`
`
`Please read "man port", the MacPorts guide at http://guide.macports.org/ and Wiki at http://trac.macports.org/ for full documentation.`
`
`
`Stray sources might have been left in the legacy /opt/local/var/db/dports directory after this upgrade, which moved most of what it could to /opt/local/var/macports, so you might want to look in the former and cleanup manually.`

o/ yeah!



`port`
`MacPorts 1.700`
`Entering interactive mode... ("help" for help, "quit" to quit)`
``
`Version: 1.700`

<span style="font-family:courier new,monospace"><span style="font-size:small">[MacPorts/MacPorts-1.7.0] > ^D</span></span>
`Goodbye`




More commands soon.. 



port installed
No ports are installed.

port selfupdate

MacPorts base version 1.700 installed
Downloaded MacPorts base version 1.700

The MacPorts installation is not outdated so it was not updated



In conclusion, `port' command should be able to run in a PureDarwin system.

<span style="font-family:courier new,monospace"><span style="font-size:small">cd /Volumes/Builds/9G55/
darwinbuild bzip2 && darwinbuild -load bzip2
chroot BuildRoot
port install fortune
</span></span>







Running MacPorts
----------------
### Running a compiled MacPorts on PureDarwin
![](/img/developers/macports/macportsonpuredarwin/running_macports_in_puredarwin.png)

The next step involves network support (but could be also done via a local repository (see MacPorts documentation for more information)), which is at this time only functional via [QEMU](../qemu.html) user mode network stack and some workaround.
#### port selfupdate

![](/img/developers/macports/macportsonpuredarwin/macportsselfupdateqemu.png)

The end of the selfupdate process should look like:

![](/img/developers/macports/macportsonpuredarwin/macportsselfupdated.png)
#### port install most
For more information, see the [Using MacPorts](../macports.1.html) page.


As an example with a port called `most' which is built (+ deps) then run:

# port install most
--->  Fetching gperf
--->  Attempting to fetch gperf-3.0.4.tar.gz from http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/gperf
--->  Verifying checksum(s) for gperf
--->  Extracting gperf
--->  Configuring gperf
--->  Building gperf
--->  Staging gperf into destroot
--->  Packaging tbz2 archive for gperf 3.0.4_0
--->  Installing gperf @3.0.4_0
--->  Cleaning gperf
--->  Fetching libiconv
--->  Attempting to fetch libiconv-1.13.tar.gz from http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/libiconv
--->  Verifying checksum(s) for libiconv
--->  Extracting libiconv
--->  Applying patches to libiconv
--->  Configuring libiconv
--->  Building libiconv
--->  Staging libiconv into destroot
--->  Packaging tbz2 archive for libiconv 1.13_0
--->  Installing libiconv @1.13_0
--->  Cleaning libiconv
--->  Fetching zlib
--->  Attempting to fetch zlib-1.2.3.tar.bz2 from http://mesh.dl.sourceforge.net/libpng
--->  Verifying checksum(s) for zlib
--->  Extracting zlib
--->  Applying patches to zlib
--->  Configuring zlib
--->  Building zlib
--->  Staging zlib into destroot
--->  Packaging tbz2 archive for zlib 1.2.3_2
--->  Installing zlib @1.2.3_2
--->  Cleaning zlib
--->  Fetching libpng
--->  Attempting to fetch libpng-1.2.37.tar.bz2 from http://mesh.dl.sourceforge.net/libpng
--->  Verifying checksum(s) for libpng
--->  Extracting libpng
--->  Configuring libpng
--->  Building libpng
--->  Staging libpng into destroot
--->  Packaging tbz2 archive for libpng 1.2.37_0
--->  Installing libpng @1.2.37_0
--->  Cleaning libpng
--->  Fetching bzip2
--->  Attempting to fetch bzip2-1.0.5.tar.gz from http://www.bzip.org/1.0.5
--->  Verifying checksum(s) for bzip2
--->  Extracting bzip2
--->  Applying patches to bzip2
--->  Configuring bzip2
--->  Building bzip2
--->  Staging bzip2 into destroot
--->  Packaging tbz2 archive for bzip2 1.0.5_2
--->  Installing bzip2 @1.0.5_2
--->  Cleaning bzip2
--->  Fetching ncursesw
--->  Attempting to fetch ncurses-5.7.tar.gz from http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/ncurses
--->  Verifying checksum(s) for ncursesw
--->  Extracting ncursesw
--->  Configuring ncursesw
--->  Building ncursesw
--->  Staging ncursesw into destroot
--->  Packaging tbz2 archive for ncursesw 5.7_0
--->  Installing ncursesw @5.7_0
--->  Cleaning ncursesw
--->  Fetching ncurses
--->  Verifying checksum(s) for ncurses
--->  Extracting ncurses
--->  Configuring ncurses
--->  Building ncurses
--->  Staging ncurses into destroot
--->  Packaging tbz2 archive for ncurses 5.7_0
--->  Installing ncurses @5.7_0
--->  Cleaning ncurses
--->  Fetching readline
--->  Attempting to fetch readline-6.0.tar.gz from http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/readline
--->  Verifying checksum(s) for readline
--->  Extracting readline
--->  Applying patches to readline
--->  Configuring readline
--->  Building readline
--->  Staging readline into destroot
--->  Packaging tbz2 archive for readline 6.0.000_1
--->  Installing readline @6.0.000_1
--->  Cleaning readline
--->  Fetching pcre
--->  Attempting to fetch pcre-7.9.tar.bz2 from http://mesh.dl.sourceforge.net/pcre
--->  Verifying checksum(s) for pcre
--->  Extracting pcre
--->  Configuring pcre
--->  Building pcre
--->  Staging pcre into destroot
--->  Packaging tbz2 archive for pcre 7.9_0
--->  Installing pcre @7.9_0
--->  Cleaning pcre
--->  Fetching slang2
--->  Attempting to fetch slang-2.1.4.tar.bz2 from ftp://ftp.plig.org/pub/slang/v2.1/
--->  Attempting to fetch slang-2.1.4.tar.bz2 from http://trd.no.distfiles.macports.org/slang2
--->  Attempting to fetch slang-2.1.4.tar.bz2 from ftp://ftp.ntua.gr/pub/lang/slang/slang/v2.1/
--->  Verifying checksum(s) for slang2
--->  Extracting slang2
--->  Configuring slang2
--->  Building slang2
--->  Staging slang2 into destroot
--->  Packaging tbz2 archive for slang2 2.1.4_0
--->  Installing slang2 @2.1.4_0
--->  Cleaning slang2
--->  Fetching most
--->  Attempting to fetch most-5.0.0a.tar.bz2 from http://trd.no.distfiles.macports.org/most
--->  Attempting to fetch most-5.0.0a.tar.bz2 from ftp://space.mit.edu/pub/davis/most/
--->  Verifying checksum(s) for most
--->  Extracting most
--->  Configuring most
--->  Building most
--->  Staging most into destroot
--->  Packaging tbz2 archive for most 5.0.0a_1
--->  Installing most @5.0.0a_1
--->  Cleaning most
# most
MOST version 5.0.0 (S-Lang version 2.1.4)
Usage:
most [-1Cbcdkstvw] [+/string] [+line number] [+s] [+d] file...
[...]


**Troubleshooting**

### Compiling MacPorts in PureDarwin


****

There is a new CarbonHeaders-9G55 posted which adds the rest of the Availability*.h headers that were missing. Install it.


tar xzvf [...]9J61/Packages/CarbonHeaders.hdrs.tar.gz

tar xzvf [...]9J61/Packages/CarbonHeaders.root.tar.gz




``

`can't find package Pextlib 1.0`
`    while executing`
`"package require Pextlib 1.0"`
`    (file "/opt/local/share/macports/Tcl/registry1.0/receipt_flat.tcl" line 37)`
`    invoked from within`
`"source /opt/local/share/macports/Tcl/registry1.0/receipt_flat.tcl"`
`    ("package ifneeded receipt_flat 1.0" script)`
`    invoked from within`
`"package require receipt_flat 1.0"`
`    (file "/opt/local/share/macports/Tcl/registry1.0/registry.tcl" line 35)`
`    invoked from within`
`"source /opt/local/share/macports/Tcl/registry1.0/registry.tcl"`
`    ("package ifneeded registry 1.0" script)`
`    invoked from within`
`"package require registry 1.0"`
`    (file "src/dep_map_clean.tcl" line 10)`

****
Seems to be fixed since MacPorts v1.7.1
Deprecated stuff
----------------

### Compiling MacPorts 1.7.1 in a PureDarwin chroot
Depending the case, the archive can come from DarwinBuild or MacPorts since most of these projects can be built into DarwinBuild and/or MacPorts.

`cd /Volumes/PureDarwin`

`tar xzvf [...]MacPorts-1.7.1.tar.gz`
`tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gcc.root.tar.gz`
`tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gcc_42.root.tar.gz`
`tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gcc_os.root.tar.gz`
`tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gcc_select.root.tar.gz (optional?)`
`tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gccfast.root.tar.gz   `
`tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/Libc_headers.root.tar.gz`
`tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/tcsh.root.tar.gz (needed?)`
`tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/OpenSSL.root.tar.gz`

`tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/SQLite.root.tar.gz `

`tar xzvf /Volumes/Builds/9G55/Packages/curl.root.tar.gz `
`tar xzvf /Volumes/Builds/9G55/Packages/gnumake.root.tar.gz            `

`tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.6_0+threads.i386.tbz2`
bzip2.root.tar.bz2


These steps (tar tar tar...) can be replaced by a proper `pd_roots' (soon available) file at setup, and a minimal amount of tar:

`cd /Volumes/PureDarwin`

`tar xzvf [...]/MacPorts-1.7.1.tar.gz`

`tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.6_0+threads.i386.tbz2`
bzip2.root.tar.bz2

Then

`chroot .`


Since the tcl project (idem for X11) cannot be built right now in DarwinBuild, we're using one built from MacPorts.

`  1  18023                       stat:entry sh /bin/tclsh`
`  1  18023                       stat:entry sh /sbin/tclsh`
`  1  18023                       stat:entry sh /usr/bin/tclsh`
`  1  18023                       stat:entry sh /usr/sbin/tclsh`
`  1  18023                       stat:entry sh /usr/local/bin/tclsh`
`  1  18023                       stat:entry sh /usr/local/sbin/tclsh`
`  1  18023                       stat:entry sh /usr/libexec/tclsh`
`  1  18023                       stat:entry sh /System/Library/CoreServices/tclsh`

Also, after a quick look in the `configure' file:
`ac_cv_path_TCLSH="$TCLSH" # Let the user override the test with a path.`
Exactly what we need, in fact! 



Without X11:



With X11 from MacPorts:

`tar xjvf /opt/local/var/macports/packages/darwin/i386/xorg-libX11-1.1.5_1+x11_xcb.i386.tbz2`
`TCLSH=/opt/local/bin/tclsh ``./configure --without-objc-foundation --without-objc-runtime --with-x --x-includes=/usr/X11R6/include/ --x-libraries=/usr/X11R6/lib/ --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include --with-included-tclthread`

Then simply:

make
make install
[...]

Congratulations, you have successfully installed the MacPorts system. To get the Portfiles and update the system, run:

sudo port -v selfupdate

Please read "man port", the MacPorts guide at http://guide.macports.org/ and Wiki at http://trac.macports.org/ for full documentation.

Stray sources might have been left in the legacy /opt/local/var/db/dports directory after this upgrade, which moved most of what it could to /opt/local/var/macports, so you might want to look in the former and cleanup manually.




### Deprecated (Compiling MacPorts 1.6.0 on DarwinBuild)

**** checking for Tcl configuration... configure: error: Can't find Tcl configuration definitions

<span style="font-family:courier new"><span style="font-family:Arial;font-weight:bold">Solution: <span style="font-weight:normal"><span style="font-size:small">darwinbuild tcl && darwinbuild -load tcl</span> (it fails to build at this time (carbon headers missing))</span></span></span>
or alternatively, use some binary roots from MacPorts:

`cd BuildRoot`
`tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.4_0+threads.i386.tbz2`
chroot .

`ln -s /opt/local/bin/tclsh8.5 /usr/bin/   `
`ln -s /opt/local/bin/tclsh8.5 /usr/bin/tclsh`

Be sure to precise the alternative path in case you MacPorts: ./configure --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include

**Problem:** `configure: error: cannot find curl-config. Is libcurl installed?`
**Solution:** <span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild curl && darwinbuild -load curl</span></span>



Then we can run `make' but it fails on:

`gcc -pipe -DPACKAGE_NAME="thread" -DPACKAGE_TARNAME="thread" -DPACKAGE_VERSION="2.6" -DPACKAGE_STRING="thread 2.6" -DPACKAGE_BUGREPORT="" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DNO_VALUES_H=1 -DHAVE_LIMITS_H=1 -DHAVE_SYS_PARAM_H=1 -DUSE_THREAD_ALLOC=1 -D_REENTRANT=1 -D_THREAD_SAFE=1 -DHAVE_PTHREAD_ATTR_SETSTACKSIZE=1 -DHAVE_READDIR_R=1 -DTCL_THREADS=1 -DTCL_WIDE_INT_TYPE=long long -DHAVE_STRUCT_STAT64=1 -DUSE_TCL_STUBS=1   -I"/opt/local/include"    -I/opt/local/include -Os -Wall -Wno-implicit-int -fno-common -c `echo ./generic/threadPoolCmd.c` -o threadPoolCmd.o`
`In file included from /usr/include/sys/time.h:77,`
`                 from ./generic/threadPoolCmd.c:1707:`
`/usr/include/sys/_structs.h: In function 'GetTime':`
`/usr/include/sys/_structs.h:192: error: nested functions are disabled, use -fnested-functions to re-enable`
`/usr/include/sys/_structs.h:192: error: invalid storage class for function '__darwin_fd_isset'`
`make[2]: *** [threadPoolCmd.o] Error 1`



Without tclthread seems to make a difference:
`./configure --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include -without-included-tclthread`


But the classic missing foundation header appears:

`tclobjc.m:42:35: error: Foundation/Foundation.h: No such file or directory`



So, let's try with Foundation replacement from GNUstep compiled through MacPorts:

`cd BuildRoot`
`tar xjvf /opt/local/var/macports/packages/darwin/i386/gnustep-base-1.14.0_0+ffi.i386.tbz2`
`GNUSTEP_SYSTEM_ROOT=/opt/local/GNUstep/System ./configure --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include -without-included-tclthread`
It fails on:

`In file included from /opt/local/GNUstep/System/Library/Headers/Foundation/NSObjCRuntime.h:33,`
`                 from /opt/local/GNUstep/System/Library/Headers/Foundation/Foundation.h:33,`
`                 from conftest.m:25:`
`/opt/local/GNUstep/System/Library/Headers/GNUstepBase/GSObjCRuntime.h: In function 'GSObjCClass':`
`/opt/local/GNUstep/System/Library/Headers/GNUstepBase/GSObjCRuntime.h:186: error: 'struct objc_object' has no member named 'class_pointer'`

Quick method: Install MacPorts on PureDarwin using the binary pkg provided by the MacPorts project
--------------------------------------------------------------------------------------------------

On the MacPorts website, there is a pkg that contains MacPorts for the Mac. In this section, we are trying to use this pkg to install MacPorts on PureDarwin. For a PureDarwin 9 system, we need to download the MacPorts version for Leopard. Next, we need to delete the file MacPorts-1.8.2.pkg/Contents/Resources/InstallationCheck, otherwise we just get "Error - This package is meant to be installed on Mac OS X 10.5.". Next, we can install the package into our PureDarwin system: 

installer -pkg MacPorts-1.8.2.pkg -target /Volumes/PureDarwin/

Now we chroot into the PureDarwin system and try to run the "port" command:

sh-3.2# port
/opt/local/bin/port: line 4: /usr/bin/tclsh: No such file or directory
/opt/local/bin/port: line 4: exec: /usr/bin/tclsh: cannot execute: No such file or directory

Hence we need to symlink tclsh from /opt/local/bin:

sh-3.2# ln -s /opt/local/bin/tclsh /usr/bin/

Now the port command almost runs, but for some strange reason the con files are missing, so we need to do

cp /opt/local/etc/macports/macports.conf.default /opt/local/etc/macports/macports.conf
cp /opt/local/etc/macports/sources.conf.default /opt/local/etc/macports/sources.conf
cp /opt/local/etc/macports/variants.conf.default /opt/local/etc/macports/variants.conf

**Important: **Now we need to configure MacPorts as described on the [MacPorts](../macports.1.html) page.

At this point, the port command should be launchable and working.




Resources
---------
<http://www.macports.org/> 


<http://svn.macosforge.org/repository/macports/branches/>

