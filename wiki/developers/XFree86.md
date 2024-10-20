XFree86
=======
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
![](/img/developers/xfree86/Xfree86.logo.gif)
This page is about [XFree86](http://www.xfree86.org/) on Darwin.
<div style="margin:5px 10px;display:inline;float:right">
__
__

### XFree86 4.7.0
XFree86 is another X11 implementation besides [X.Org](xorg.html). Version 4.7.0 was released in 2007.
Most binaries you can find on the net (e.g., in fink) are built for Mac OS X, and will fail to run on PureDarwin since they depend on closed frameworks such as ApplicationServices. Hence, we need to compile XFree86 specifically for PureDarwin, and MacPorts can help us with this task.
``
### XFree86 in MacPorts
MacPorts contains a portfile which can be used to compile XFree86 for PureDarwin. In old release notes, it is stated that "*Darwin/Mac OS X uses IOKit drivers and does not use the module loader drivers listed above. Further information can be found in [README.Darwin](http://cvsweb.xfree86.org/cvsweb/xc/programs/Xserver/hw/xfree86/doc/README.Darwin?rev=1.28&content-type=text/vnd.viewcvs-markup)*". Also take a look at [Using the MacPorts project](macports.1.html) page for more information about MacPorts.
``
The portfile shows the following information about Xfree86, among other things:

<span style="font-family:courier new">
 </span>

`port info XFree86`
 

``

(...)

`Platforms: darwin freebsd`

In the case of `+puredarwin` variant is choosen, this is what happens:



`platform puredarwin {`

`    post-patch {  `
`        set hostfd [open "${worksrcpath}/config/cf/host.def" a+]`
`        puts $hostfd "#define DarwinQuartzSupport NO"`
`        puts $hostfd "#define BuildGlxExt         YES"`
`        puts $hostfd "#define BuildGLXLibrary     YES"`
`        close $hostfd`
`    }`
`}`

#### Compiling XFree86 for PureDarwin
We are using MacPorts on a Mac and transfer the final build products to a PureDarwin system thereafter, as described on the [MacPorts](macports.1.html) page. Later, we will be able to bootstrap MacPorts on PureDarwin in order to provide products built on a PureDarwin system for a PureDarwin system.

__Note:__ You should configure MacPorts to procuce tbz2 archives as described on that page.

Add `-v` for verbose output.

First, you need to move a symlink to Apple's X.Org (X11.app) so that it doesn't interfere with XFree86 from MacPorts:
<span style="color:rgb(68,68,68);font-family:courier new;font-size:12px">
 </span>
sudo mv /usr/X11R6 /usr/X11R6.apple


 
 

Then do:

 


port archive xfree86 +puredarwin
<span style="font-size:13px">
 </span>
If the build succeeds, you should see:
<span style="font-size:13px">
 </span>

`Warning: XFree86 requests to install files outside the common directory structure!`
`---> Installing XFree86 4.7.0_0+macosx+puredarwin`
`---> Activating XFree86 4.7.0_0+macosx+puredarwin`
`---> Cleaning XFree86`
`---> Removing build directory for XFree86`


 
On Mac OS X, the symbolic link created with MacPorts is wrong.
<span style="color:rgb(0,0,0);font-family:Helvetica;font-size:13px">
 </span>
 

<span style="color:rgb(0,0,0)">
 </span>
Before we install XFree86, let's build some libraries that are needed by many applications that run on X. 
 
#### Compiling FreeType for PureDarwin {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
Many graphical applications need freetyp, so we need to compile it in a way that it can be used on PureDarwin.
We need to patch the Portfile with


`sed -i 's|--with-old-mac-fonts|--without-ats|g' 
 /opt/local/var/macports/sources/*/release/ports/print/freetype/Portfile`

TODO: the portfile should get a "puredarwin" section that sets this option automatically.
Build it with


`sudo /opt/local/bin/port archive freetype +puredarwin`


To be sure, check that the output of


`/opt/local/var/macports/sources/*/release/ports/print/freetype/work/destroot/opt/local/bin/freetype-config --libs`


does not contain ApplicationServices or other proprietary frameworks.
The following output is fine


`-L/opt/local/lib -lfreetype -lz`


whereas this would not be fine


`-L/opt/local/lib -lfreetype -lz -Wl,-framework,CoreServices -Wl,-framework,ApplicationServices`

#### Installing XFree86 on PureDarwin {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}


First, install on your PureDarwin system what you have compiled above.


`cd /Volumes/PureDarwin`
`tar xfvj /opt/local/var/macports/packages/darwin/i386/XFree86-4.7.0_0+macosx+puredarwin.i386.tbz2`

curl http://src.macosforge.org/BinaryDrivers/8C46/GraphicsDrivers.root.tar.gz > GraphicsDrivers.root.tar.gz
tar xfvz GraphicsDrivers.root.tar.gz
curl http://src.macosforge.org/Roots/9C31/IOGraphics.root.tar.gz > IOGraphics.root.tar.gz

`tar xfvz IOGraphics.root.tar.gz `


The compiled XFree86 from the MacPorts project has the following library dependencies. Make sure these are present on your PureDarwin system:
-   libfreetype.6.dylib
-   usr/lib/libz.1.dylib
-   /System/Library/Frameworks/IOKit.framework/Versions/A/IOKit
-   /usr/lib/libgcc_s.1.dylib
-   /usr/lib/libSystem.B.dylib



<span style="font-size:13px">
 </span>

You also need to have in the PureDarwin system:

-   IOGraphicsFamily.kext (from DarwinBuild)
-   [VMwareIOFramebuffer.kext](../downloads.html) (optional - if using VMware; from the VMware Tools)

**Running XFree86 on PureDarwin**
<span style="font-size:13px">
 </span>

Make sure the KEXTs are loaded:


`kextload /System/Library/Extensions/IOGraphicsFamily.kext`

`kextload /System/Library/Extensions/VMwareIOFramebuffer.kext`

Additionally, in order to add your keyboard, mouse and/or trackpad support for XFree86, you should load the corresponding kernel extension. In case of PS2, take a look at the [PS2 Controller](xnu/ps2-controller.html) page.


__Notes__: USB mouse and Apple MacBook trackpad works. PS2 not (yet) tested.



Launch X with


`mount -uw / # need to be rw so that /tmp/.tX0-lock and /tmp/.X11-unix socket can be created`
`export PATH=/usr/X11R6/bin:$PATH`
`export DISPLAY=:0.0`
<span style="font-family:courier new,monospace"><span><span style="font-size:small">X -nolisten tcp -size 800 600 -keymap USA.keymapping & sleep 3 && xeyes</span></span></span>


![](/img/developers/xorg/XFree86%204.7.0%20xeyes%20vmware.png)

### Screenshots
The oldschool *twm* remains functional.


![](/img/developers/xfree86/XFree86%20on%20puredarwin%20nano.png)



Also the minimalist *wmii.*


![](/img/developers/xfree86/wmii%20XFree86%20wmware.png)




<span style="font-size:13px">
 </span>

![](/img/developers/xfree86/glxgears%20XFree86%20vmware.png)



*Fluxbox* now!


![](/img/developers/xfree86/fluxbox%20XFree86%20vmware.png)


![](/img/developers/xfree86/xterm%20fluxbox%20bis%20XFree86%20vmware.png)



*Windowmaker* compiles and runs like a charm as soon as we get rid of problematic dependencies.


![](/img/developers/xfree86/windowmaker%20XFree86%20vmware.png)



Idem for *enlightenment* 17.


![](/img/developers/xfree86/enlightenment%20starting%20in%20XFree86%20in%20vmware.png)


![](/img/developers/xfree86/enlightenment%20XFree86%20vmware.png)



*qt3* and *qt4-x11* are almost ok.


![](/img/developers/xfree86/filelight%20with%20qt3.png)


![](/img/developers/xfree86/some%20qt3%20apps.png)








### Troubleshooting
#### Conflicting /usr/X11R6

Problem:
port install xfree86 +puredarwin
`[...]`
`---> Fetching XFree86`
`Error: Target org.macports.fetch returned: `
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
 </span></span></span>
` You have an Apple X11 installation already.`
` MacPorts will not overwrite it.`
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
 </span></span></span>
` If you really want to use XFree86 instead,`
` please move it aside first :`
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
 </span></span></span>
` sudo mv /usr/X11R6 /usr/X11R6.apple`
` `
Error: Status 1 encountered during processing.



sudo mv /usr/X11R6 /usr/X11R6.apple  
#### MAXHOSTNAMELEN undeclared
Problem:
port install xfree86 +puredarwin

[...]



In file included from x11trans.c:82:
../../lib/xtrans/Xtranssock.c:1378: error: 'MAXHOSTNAMELEN' undeclared here (not in a function)
make[4]: *** [x11trans.o] Error 1
make[3]: *** [all] Error 1
make[2]: *** [all] Error 1
make[1]: *** [World] Error 2
make: *** [World] Error 2
<span style="font-size:small"><span style="font-family:courier new,monospace">
 </span></span>
Error: Status 1 encountered during processing.







<span style="color:rgb(0,0,0);font-family:arial;font-size:13px">
 </span>
 
`--- xc/lib/xtrans/Xtranssock.c.origin`` ``2008-09-29 21:07:46.000000000 +0200`
`+++ xc/lib/xtrans/Xtranssock.c`` ``2008-09-29 21:40:00.000000000 +0200`
`@@ -284,6 +284,8 @@`
` #ifndef __USLC__`
` #pragma weak getaddrinfo`
` #endif`
`+#else`
`+#define MAXHOSTNAMELEN 256`
` #endif`
` static int haveIPv6 = 1;`
` #endif`
#### decompress.c error
Problem:
port install xfree86 +puredarwin
[...]
`/usr/bin/cc -c -Wall -Wpointer-arith -no-cpp-precomp -fno-common -I. -I../include -I../../../programs/Xserver/include -I../../../exports/include "-I/opt/local/var/macports/build/_opt_local_var_macports_sources_rsync.macports.org_release_ports_x11_XFree86/work/include" -D__i386__ -D__DARWIN__ -DNO_ALLOCA -DCSRG_BASED -DFONTDIRATTRIB `` `` -DBUILD_SPEEDO -DBUILD_TYPE1 -DBUILD_CID `` `` -DBUILD_FREETYPE -DFONT_ENCODINGS_DIRECTORY="/usr/X11R6/lib/X11/fonts/encodings/encodings.dir" -DX_GZIP_FONT_COMPRESSION `` ``-Os -fno-strict-aliasing decompress.c -o unshared/decompress.o`
`decompress.c:96: error: syntax error before 'z_magic'`
`[...]`
`decompress.c:464: error: dereferencing pointer to incomplete type
 make[5]: *** [decompress.o] Error 1
 make[4]: *** [fontfile] Error 1
 make[3]: *** [all] Error 1
 make[2]: *** [all] Error 1
 make[1]: *** [World] Error 2
 make: *** [World] Error 2`
`Warning: the following items did not execute (for XFree86): org.macports.activate org.macports.build org.macports.destroot org.macports.install`
`Error: Status 1 encountered during processing.`

Solution:

A Patch is available in ticket [#16697](https://trac.macports.org/ticket/16697) and in the attachments below too.
 
Changes are minimal:
<span style="color:rgb(0,0,0);font-family:arial;font-size:13px">
 </span>
 
`--- xc/lib/font/fontfile/decompress.c.origin`` ``2008-09-29 22:08:09.000000000 +0200`
`+++ xc/lib/font/fontfile/decompress.c`` ``2008-09-29 22:06:41.000000000 +0200`
`@@ -77,7 +77,7 @@`
` `
` #include "fontmisc.h"`
` #include <bufio.h>`
`-#ifdef __UNIXOS2__`
`+#if defined(__UNIXOS2__) || defined(__DARWIN__) `
` #include <sys/types.h>`
` #endif`


 
#### Cannot establish any listening sockets
Problem:
It fails because missing network support:


![](/img/developers/xorg/XFree86%204.7.0%20on%20puredarwin.png)


**Solution:**

**It looks like your system doesn't have a working network.**

The workaround is simply to add -nolisten tcp.
This means that XFree86 will not listen on TCP port 6000. 

#### Missing keymap
**Problem:**
The keymap appears mandatory (no default one embedded, but it looks for USA.keymapping by default).
Also, the option `-nokeymap` is still present and working, it makes X to attempt to read keymap from the system but it will fail with a fatal "`Could not build a valid keymap`".






![](/img/developers/xorg/X%20notcp%20on%20puredarwin.png)


**Solution:**

****

****

<span style="font-family:courier new">
 </span>



**
**

If you plan to use an alternative keymap without specifying it at the command line, you can use a symbolic link:




mv /System/Library/Keyboards/USA.keymapping /System/Library/Keyboards/US.keymapping

ln -fs /System/Library/Keyboards/Francais.keymapping /System/Library/Keyboards/USA.keymapping






Please let us know if you know how to generate a .keymapping file.
 
#### Font-related problem when launching xterm

`**Problem:**`
`XFree86 Version 4.7.0 / X Window System`
`(protocol Version 11, revision 0)`
`Release Date: 12 August 2007`
` ``If the server is older than 6-12 months, or if your hardware is`
` ``newer than the above date, look for a newer version before`
` ``reporting problems. (See http://www.XFree86.Org/FAQ)`
`Operating System: Darwin Apple Computer, Inc.`
`Using keymapping provided in /USA.keymapping.`
`Display mode: IOKit`
`Couldn't set hardware cursor visible with kernel return 0xe00002c7.`
`Screen 0 added: 800x600 @ (0,0)`
`Could not init font path element /usr/X11R6/lib/X11/fonts/CID/, removing from list!`
`Fontconfig error: Cannot load default config file`
`Warning: Cannot convert string "" to type XftFont`
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
`waiting for X server to shut down Quitting XDarwin...`
X connection to :0.0 broken (explicit kill or server shutdown).
<span style="font-family:Helvetica;font-size:12px">
 </span>
 
Create font information cache files:

/usr/X11R6/bin/fc-cache -v -f /usr/X11R6/lib/X11/fonts/

Fontconfig error: Cannot load default config file
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts/": caching, 0 fonts, 11 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//100dpi": caching, 398 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//75dpi": caching, 398 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//CID": caching, 0 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//Speedo": caching, 0 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//TTF": caching, 22 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//Type1": caching, 29 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//cyrillic": caching, 0 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//encodings": caching, 0 fonts, 1 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//encodings/large": caching, 0 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//local": caching, 0 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//misc": caching, 55 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//util": caching, 0 fonts, 0 dirs
/usr/X11R6/bin/fc-cache: succeeded



__Note:__ It seems optional.

#### Failed to connect to the HID system

Problem:
Attempting to use width x height = 800 x 600

<span style="font-family:courier new,monospace"><span>
 </span></span>
`XFree86 Version 4.7.0 / X Window System`
`(protocol Version 11, revision 0)`
`Release Date: 12 August 2007`
 `If the server is older than 6-12 months, or if your hardware is`
 `newer than the above date, look for a newer version before`
 `reporting problems. (See http://www.XFree86.Org/FAQ)`
`Operating System: Darwin Apple Computer, Inc.`
`Using keymapping provided in USA.keymapping.`
`Display mode: IOKit`
`Couldn't set hardware cursor visible with kernel return 0xe00002c7.`
`Screen 0 added: 800x600 @ (0,0)`
`Could not init font path element /usr/X11R6/lib/X11/fonts/CID/, removing from list!`
`Using keymapping provided in USA.keymapping.`
`Display mode: IOKit`
`Failed to connect to the HID System as the window server!`
<span style="font-family:courier new,monospace"><span>
 </span></span>
`Fatal server error:`
`Make sure you have quit the Mac OS X window server.`
<span style="font-family:courier new,monospace"><span>
 </span></span>
` OsVendorFatalError`
` AbortDDX`
`Quitting XDarwin...`


****
Although the default *xterm* fails, *xterm* and *aterm* compiled from MacPorts (and probably *Eterm* too) don't.

Many "window managers" are linked with ApplicationServices framework*, *directly or through their library dependencies, so they won't run.

#### No screens found

No screens found


Solution:
On VMware, ensure that VMwareIOFramebuffer.kext is loaded.
#### assert failed on line 416 of xfIOKit.c!
<span style="font-family:Helvetica">**Problem:**
A blue frozen screen and the message "assert failed on line 416 of xfIOKit.c!" in the (redirected) &2</span>


**Solution:**
Unknown, please let us know.


To be continued... 
### Resources
<http://www.xfree86.org/current/Darwin.html> (old)
<http://xonx.sourceforge.net/>
<http://www.xdarwin.org/keymappings/> mirror <http://www.mit.edu/afs/sipb/project/darwin/src/modules/keymaps/keymappings/> 
<http://www.xfree86.org/current/Darwin.pdf> 

