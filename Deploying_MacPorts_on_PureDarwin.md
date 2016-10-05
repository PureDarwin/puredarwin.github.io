Deploying MacPorts on PureDarwin
================================

The recommended way to use MacPorts to produce binaries for PureDarwin is now to run MacPorts on a PureDarwin system.
This page is about deploying MacPorts on a PureDarwin system (thus, making PureDarwin a bit more self-hosted).
<span style="color:rgb(255,0,0)">If you are interested in getting MacPorts to run on PureDarwin as quickly as possible, you can skip to the "quick method" at the end of this page.</span>
**
**

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:450px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Status](macportsonpuredarwin.html#TOC-Status)
2.  [**2** Getting MacPorts](macportsonpuredarwin.html#TOC-Getting-MacPorts)
    1.  [**2.1** Fetching MacPorts in a PureDarwin VM](macportsonpuredarwin.html#TOC-Fetching-MacPorts-in-a-PureDarwin-VM)
        1.  [**2.1.1** Via Network](macportsonpuredarwin.html#TOC-Via-Network)
        2.  [**2.1.2** Local copy](macportsonpuredarwin.html#TOC-Local-copy)
3.  [**3** Building MacPorts](macportsonpuredarwin.html#TOC-Building-MacPorts)
    1.  [**3.1** Compiling MacPorts in a PureDarwin vm](macportsonpuredarwin.html#TOC-Compiling-MacPorts-in-a-PureDarwin-vm)
        1.  [**3.1.1** configure](macportsonpuredarwin.html#TOC-configure)
        2.  [**3.1.2** make](macportsonpuredarwin.html#TOC-make)
        3.  [**3.1.3** make install](macportsonpuredarwin.html#TOC-make-install)
    2.  [**3.2** Compiling MacPorts 1.7.0 in DarwinBuild](macportsonpuredarwin.html#TOC-Compiling-MacPorts-1.7.0-in-DarwinBuild)
4.  [**4** Running MacPorts](macportsonpuredarwin.html#TOC-Running-MacPorts)
    1.  [**4.1** Running a compiled MacPorts on PureDarwin](macportsonpuredarwin.html#TOC-Running-a-compiled-MacPorts-on-PureDarwin)
        1.  [**4.1.1** port selfupdate](macportsonpuredarwin.html#TOC-port-selfupdate)
        2.  [**4.1.2** port install most](macportsonpuredarwin.html#TOC-port-install-most)
    2.  [**4.2** Compiling MacPorts in PureDarwin](macportsonpuredarwin.html#TOC-Compiling-MacPorts-in-PureDarwin)
5.  [**5** Deprecated stuff](macportsonpuredarwin.html#TOC-Deprecated-stuff)
    1.  [**5.1** Compiling MacPorts 1.7.1 in a PureDarwin chroot](macportsonpuredarwin.html#TOC-Compiling-MacPorts-1.7.1-in-a-PureDarwin-chroot)
    2.  [**5.2** Deprecated (Compiling MacPorts 1.6.0 on DarwinBuild)](macportsonpuredarwin.html#TOC-Deprecated-Compiling-MacPorts-1.6.0-on-DarwinBuild-)
6.  [**6** Quick method: Install MacPorts on PureDarwin using the binary pkg provided by the MacPorts project](macportsonpuredarwin.html#TOC-Quick-method:-Install-MacPorts-on-PureDarwin-using-the-binary-pkg-provided-by-the-MacPorts-project)
7.  [**7** Resources](macportsonpuredarwin.html#TOC-Resources)

Status
------
MacPorts is functional on PureDarwin 9 using the "quick method" at the end of this page.


[![](../../_/rsrc/1264333931811/developers/macports/macportsonpuredarwin/macports_on_pd.jpg%3Fheight=300&width=400)](macportsonpuredarwin/macports_on_pd.jpg%3Fattredirects=0)

<span style="font-size:small">
</span>
<span style="font-size:small">MacP</span><span style="font-size:small">orts 1.8.0 states depending its host.</span>
<span style="font-size:small">
</span>
  ----------------------------------------------------------------------------------------------------------- ----------------------------------------------------------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------- -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  <span style="font-size:small"> </span>                                                                     <span style="font-weight:bold"><span style="font-size:small"> Mac OS X</span></span>                                                                             <span style="font-size:small"> </span><span style="font-weight:bold"><span style="font-size:small">DarwinBuild</span></span>   <span style="font-weight:bold"><span style="font-size:small"> PureDarwin</span></span>
  <span style="font-weight:bold"><span style="font-size:small"> build and deployement </span></span>        <span style="font-size:small"> </span><span style="font-weight:bold"><span style="color:rgb(56,118,29)"><span style="font-size:small">YES</span></span></span>   <span style="font-weight:bold"><span style="color:rgb(56,118,29)"><span style="font-size:small"> YES</span></span></span>      <span style="font-weight:bold"><span style="color:rgb(56,118,29)"><span style="font-size:small"> YES</span></span></span>
  <span style="font-weight:bold"><span style="font-size:small"> port fetch &lt;port&gt;</span></span>        <span style="font-size:small"> </span><span style="font-weight:bold"><span style="color:rgb(56,118,29)"><span style="font-size:small">YES</span></span></span>   <span style="font-weight:bold"><span style="color:rgb(56,118,29)"><span style="font-size:small"> YES</span></span></span>      <span style="font-size:small"> </span>**<span style="font-size:small">YES <span style="font-weight:normal">(OK in QEMU or real hardware, missing Network support in VMware)</span></span>**
  <span style="font-size:small"> </span>**<span style="font-size:small">port install &lt;port&gt;</span>**   <span style="font-size:small"> </span>**<span style="font-size:small">YES</span>**                                                                               <span style="font-size:small"> </span>**<span style="font-size:small">YES</span>**                                             <span style="font-size:small"> </span>**<span style="font-size:small">YES</span>**
  <span style="font-size:small">**/opt/local/[...]/&lt;port&gt;**</span>                                    <span style="font-size:small"> </span><span style="color:rgb(56,118,29)"><span style="font-weight:bold"><span style="font-size:small">YES</span></span></span>   <span style="color:rgb(56,118,29)"><span style="font-weight:bold"><span style="font-size:small"> YES</span></span></span>      <span style="font-size:small"> </span>**<span style="font-size:small">YES</span>**
  ----------------------------------------------------------------------------------------------------------- ----------------------------------------------------------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------- -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

As an example, the fortune project (one workaround consists to fetch the source only in a puredarwin chroot where the network is available from Mac OS X or to use [QEMU](../qemu.html) user mode network stack ) built and run:

<span style="font-size:small"><span style="font-size:12px"></span></span>
[![](../../_/rsrc/1246401686874/developers/macports/macportsonpuredarwin/fortune_from_macports.png)](macportsonpuredarwin/fortune_from_macports.png%3Fattredirects=0)

<span style="font-family:Helvetica,Verdana,sans-serif"></span>
<span style="text-decoration:underline"><span style="font-size:small">Notes:</span></span><span style="font-size:small"> On Mac OS X (the host and build environment), darwinbuild comes from macports (port install darwinbuild).</span>
<span style="font-size:small">And in the custom plist of darwinbuild, there is an entry for MacPorts 1.7.0, in order to install it in the BuildRoot (the guest and pseudo darwin environement) of darwinbuild.</span>
<span style="font-size:small">Then, in the BuildRoot, the freshly installed MacPorts project could be used to install the DarwinBuild project inside.</span>
<span style="font-size:small">"Infinite loop" makes sense.</span>
<span style="font-size:small">
</span>
<span style="font-size:small">To illustrate:</span>

[![](../../_/rsrc/1234066038309/developers/macports/macportsonpuredarwin/macportsvsdarwinbuild.png)](macportsonpuredarwin/macportsvsdarwinbuild.png%3Fattredirects=0)
Getting MacPorts
----------------
### Fetching MacPorts in a PureDarwin VM
#### Via Network
With [QEMU user mode network stack](../qemu.html), retrieve MacPorts sources via curl 

[![](../../_/rsrc/1246837422604/developers/macports/macportsonpuredarwin/macportscurldownload.png)](macportsonpuredarwin/macportscurldownload.png%3Fattredirects=0)
#### Local copy
Opening the archive file in rw (.vmdk, .iso, etc..), and drop the source inside.

Building MacPorts
-----------------
### Compiling MacPorts in a PureDarwin vm
Do not remove headers and others needed files in `pd_setup' stages.


<span style="font-size:small">E</span><span style="font-size:small">x</span><span style="font-size:small">t</span><span style="font-size:small">e</span><span style="font-size:small">r</span><span style="font-size:small">n</span><span style="font-size:small">a</span><span style="font-size:small">l</span><span style="font-size:small"> </span><span style="font-size:small">r</span><span style="font-size:small">equirements (built in MacPorts):</span>
<span style="font-size:13px"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.6_0+threads.i386.tbz2</span></span>
<span style="font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:12px"></span></span>

<span style="font-family:Arial,Verdana,sans-serif">It will not be missing in the future releases, but in case for `env':</span>

CFLAGS=-I/opt/local/include
LDFLAGS=-L/usr/local/lib

In order to provide the famous *Availability.h* (part of Carbon which has been released (thx Apple!) as headers) needed by many projects in darwinbuild:
tar xzvf /Users/aladin/PureDarwin/darwinbuild/9J61/Packages/CarbonHeaders.hdrs.tar.gz
tar xzvf /Users/aladin/PureDarwin/darwinbuild/9J61/Packages/CarbonHeaders.root.tar.gz (if there is a diff)
#### configure

Without X11:

<span><span style="font-family:courier new,monospace">TCLSH=/opt/local/bin/tclsh </span><span style="font-family:courier new,monospace">./configure --without-objc-foundation --without-objc-runtime  --without-x  --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include --with-included-tclthread</span></span>

With X11 from MacPorts:

<span style="font-family:courier new,monospace">tar xjvf /opt/local/var/macports/packages/darwin/i386/xorg-libX11-1.1.5_1+x11_xcb.i386.tbz2</span>
<span style="font-family:courier new,monospace">TCLSH=/opt/local/bin/tclsh </span><span style="font-family:courier new,monospace">./configure --without-objc-foundation --without-objc-runtime --with-x --x-includes=/usr/X11R6/include/ --x-libraries=/usr/X11R6/lib/ --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include --with-included-tclthread</span>


[![](../../_/rsrc/1246397774959/developers/macports/macportsonpuredarwin/compiling_macports_in_puredarwin_configure.png%3Fheight=364&width=420)](macportsonpuredarwin/compiling_macports_in_puredarwin_configure.png%3Fattredirects=0)

#### make

[![](../../_/rsrc/1246397789524/developers/macports/macportsonpuredarwin/compiling_macports_in_puredarwin_make_install.png%3Fheight=366&width=420)](macportsonpuredarwin/compiling_macports_in_puredarwin_make_install.png%3Fattredirects=0)
#### make install

[![](../../_/rsrc/1246397782884/developers/macports/macportsonpuredarwin/compiling_macports_in_puredarwin_make.png%3Fheight=366&width=420)](macportsonpuredarwin/compiling_macports_in_puredarwin_make.png%3Fattredirects=0)

### Compiling MacPorts 1.7.0 in DarwinBuild

A first interesting way is to use the DarwinBuild project to build (and package) MacPorts for PureDarwin.

This is a work in progress, a new entry in a custom plist is needed:

<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">MacPorts = {</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">"source_sites" = (</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">    </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">    </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">    </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">    </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">    </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">    </span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">"http://puredarwin.googlecode.com/svn/Mirror",</span></span>
<span style="white-space:pre"><span style="font-family:courier new"><span style="font-size:12px"> </span></span></span><span style="font-family:courier new"><span style="font-size:12px">"http://svn.macports.org/repository/macports/downloads/MacPorts-1.7.0",</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">);</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">version = 1.7.0;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">};</span></span>
<span style="font-weight:bold">Problem: </span><span style="font-family:courier new,monospace"><span style="font-size:small">/Volumes/Builds/9G55/BuildRoot/private/var/tmp/MacPorts/MacPorts-1.7.0.root is empty. Build verification failed.</span></span>
How can we tell to darwinbuild to configure & make the project (except the way consisting of repackaging the archive with a custom makefile (makefile is autodetected by darwinbuild))?
<span style="font-weight:bold">Solution: <span style="color:rgb(255,0,0)">Please, let us know if you have one.</span></span>


We can continue the compilation process by hand for now..

<span style="font-family:courier new,monospace"><span style="font-size:small">cd /Volumes/Builds/9G55/BuildRoot </span></span>
<span style="font-family:arial,sans-serif"><span style="font-size:small">
</span></span>
<span style="font-family:arial,sans-serif"><span style="font-size:small">TCL is a must for MacPorts.</span></span>
<span style="font-family:arial;font-size:13px">
</span>
<span style="font-size:small"><span style="font-family:courier new,monospace">tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.6_0+threads.i386.tbz2</span></span>
<span style="font-family:arial,sans-serif"><span style="font-size:small">
</span></span>
<span style="font-family:arial,sans-serif"><span style="font-size:small">Obviously, we need curl.</span></span>
<span style="font-family:arial;font-size:13px">
</span>
<span style="font-size:small"><span style="font-family:courier new,monospace">tar xjvf /opt/local/var/macports/packages/darwin/i386/curl-7.19.2_0+ipv6.i386.tbz2</span></span>
<span style="font-family:courier new;font-size:12px">
</span>

<span style="font-family:arial,sans-serif"><span style="font-size:small">or</span></span>

<span style="font-size:small"><span style="font-family:courier new,monospace">cd .. && darwinbuild -init 9G55pd1</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">darwinbuild curl && darwinbuild -load curl && cd BuildRoot</span></span>

<span><span style="font-family:arial,sans-serif"><span style="font-size:small">
Why not?</span></span></span>
<span><span style="font-family:arial,sans-serif"><span style="font-size:small">
<span style="font-family:courier new,monospace">tar xjvf /opt/local/var/macports/packages/darwin/i386/XFree86-4.7.0_0+macosx+puredarwin.i386.tbz2
tar xjvf /opt/local/var/macports/packages/darwin/i386/xorg-libX11-1.1.5_1+x11_xcb.i386.tbz2
</span>
</span></span></span>
<span><span style="font-family:arial,sans-serif"><span style="font-size:small">Then the configure step(s)..</span></span></span>
<span><span style="font-family:arial,sans-serif"><span style="font-size:small">
<span style="font-family:courier new,monospace">chroot .</span></span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">cd SourceCache/MacPorts/MacPorts-1.7.0</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">mount -t devfs devfs /dev</span></span>
<span style="font-family:courier new;font-size:12px">ln -s /opt/local/bin/tclsh /usr/bin/</span>
<span style="font-family:courier new;font-size:12px">./configure --without-objc-foundation --with-x --x-includes=/usr/X11R6/include/ --x-libraries=/usr/X11R6/lib/ --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include --with-included-tclthread</span>

<span style="font-family:Helvetica;font-size:12px"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">[...]</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">configure: creating ./config.status</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">config.status: creating Makefile</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">config.status: creating pkgIndex.tcl</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">make</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">[...]</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">===&gt; making all in src/port</span></span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">sed -e 's,@TCLSH@,/usr/bin/tclsh,g' -e 's,@TCL_PACKAGE_DIR@,/opt/local/lib/tcl8.5,g' portmirror.tcl &gt; portmirror</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">sed -e 's,@TCLSH@,/usr/bin/tclsh,g' -e 's,@TCL_PACKAGE_DIR@,/opt/local/lib/tcl8.5,g' portindex.tcl &gt; portindex</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">sed -e 's,@TCLSH@,/usr/bin/tclsh,g' -e 's,@TCL_PACKAGE_DIR@,/opt/local/lib/tcl8.5,g' port.tcl &gt; port</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">===&gt; making all in src/programs</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">make install</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">[...]</span></span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">/usr/bin/tclsh src/dep_map_clean.tcl /opt/local/lib/tcl8.5</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">
</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">Congratulations, you have successfully installed the MacPorts system. To get the Portfiles and update the system, run:</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">
</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">sudo port -v selfupdate</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">
</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">Please read "man port", the MacPorts guide at http://guide.macports.org/ and Wiki at http://trac.macports.org/ for full documentation.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">
</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">Stray sources might have been left in the legacy /opt/local/var/db/dports directory after this upgrade, which moved most of what it could to /opt/local/var/macports, so you might want to look in the former and cleanup manually.</span></span></span>

o/ yeah!



<span style="font-family:courier new,monospace"><span style="font-size:small">port</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">MacPorts 1.700</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">Entering interactive mode... ("help" for help, "quit" to quit)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">[MacPorts/MacPorts-1.7.0] &gt; </span>version</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">Version: 1.700</span></span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">[MacPorts/MacPorts-1.7.0] &gt; </span>^D</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(102,102,102)">Goodbye</span></span></span>
<span style="color:rgb(102,102,102);font-family:courier new">
</span>
<span style="color:rgb(102,102,102);font-family:courier new"><span style="color:rgb(0,0,0);font-family:Helvetica"></span></span>

More commands soon.. 


<span style="color:rgb(102,102,102);font-family:courier new"></span>
<span style="color:rgb(0,0,0)">port installed</span>
No ports are installed.

<span style="color:rgb(0,0,0)">port selfupdate</span>

MacPorts base version 1.700 installed
Downloaded MacPorts base version 1.700

The MacPorts installation is not outdated so it was not updated
<span style="color:rgb(0,0,0);font-family:Helvetica"></span>


In conclusion, `port' command should be able to run in a PureDarwin system.
<span style="font-family:Arial;font-size:13px"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">cd /Volumes/Builds/9G55/
darwinbuild bzip2 && darwinbuild -load bzip2
chroot BuildRoot
port install fortune
<span style="color:rgb(102,102,102)">---&gt; Extracting fortune
---&gt; Applying patches to fortune
---&gt; Configuring fortune
---&gt; Building fortune
---&gt; Staging fortune into destroot
---&gt; Installing fortune @6.2.0-RELEASE_0
---&gt; Activating fortune @6.2.0-RELEASE_0
<span style="color:rgb(204,0,0)">Error: Target org.macports.activate returned: Image error: fortune @6.2.0-RELEASE_0 not installed as an image.
Error: Status 1 encountered during processing.</span> <span style="color:rgb(0,0,0);font-family:Arial;font-size:13px;font-weight:bold">*** Problem ***
<span style="font-family:Arial,Verdana,sans-serif">Solution: <span style="color:rgb(255,0,0)">Please, let us know if you know how to avoid this error.
Pseudo-solution: <span style="font-size:12px;font-weight:normal">To circumvent (unfortunately not for all ports (e.g., fortune)) the "activation error" (see above in this page), change the type of installation to do for ports from
portinstalltype<span style="white-space:pre"> </span>image<span style="white-space:pre"> <span style="font-family:Arial,Verdana,sans-serif;white-space:normal">to
portinstalltype direct </span></span></span></span></span></span></span></span></span>
<span style="font-size:12px"></span>
<span style="font-size:13px">**<span style="font-size:12px;font-weight:normal;white-space:pre"><span style="font-family:Arial,Verdana,sans-serif;font-size:13px;white-space:normal;color:rgb(56,118,29);font-weight:bold">This problem (</span><span style="font-family:Arial,Verdana,sans-serif;font-size:13px;white-space:normal;color:rgb(56,118,29)">hopefully</span><span style="font-family:Arial,Verdana,sans-serif;font-size:13px;white-space:normal;color:rgb(56,118,29);font-weight:bold">) cannot be reproduced in a real running PureDarwin system.</span></span>**</span>





Running MacPorts
----------------
### Running a compiled MacPorts on PureDarwin
<span style="font-family:courier new,monospace;white-space:pre">[![](../../_/rsrc/1246398754457/developers/macports/macportsonpuredarwin/running_macports_in_puredarwin.png%3Fheight=366&width=420)](macportsonpuredarwin/running_macports_in_puredarwin.png%3Fattredirects=0)</span>

<span style="font-size:small">The next step involves network support (but could be also done via a local repository (see MacPorts documentation for more information)), which is at this time only functional via [QEMU](../qemu.html) user mode network stack and some workaround.</span>
#### port selfupdate
<span style="font-size:small"></span>
[![](../../_/rsrc/1246830815984/developers/macports/macportsonpuredarwin/macportsselfupdateqemu.png%3Fheight=330&width=420)](macportsonpuredarwin/macportsselfupdateqemu.png%3Fattredirects=0)

<span style="font-size:small">The end of the selfupdate process should look like:</span>
<span style="font-size:small"></span>
[![](../../_/rsrc/1246830807822/developers/macports/macportsonpuredarwin/macportsselfupdated.png)](macportsonpuredarwin/macportsselfupdated.png%3Fattredirects=0)
#### port install most
<span style="font-size:small">For more information, see the [Using MacPorts](../macports.1.html) page.</span>
<span style="font-size:small">
</span>
<span style="font-size:small">A</span><span style="font-size:small">s an example with a port called `most' which is built (+ deps) then run:</span>

<span style="font-size:small"># port install most</span>
<span style="font-size:small">---&gt;  Fetching gperf</span>
<span style="font-size:small">---&gt;  Attempting to fetch gperf-3.0.4.tar.gz from http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/gperf</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for gperf</span>
<span style="font-size:small">---&gt;  Extracting gperf</span>
<span style="font-size:small">---&gt;  Configuring gperf</span>
<span style="font-size:small">---&gt;  Building gperf</span>
<span style="font-size:small">---&gt;  Staging gperf into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for gperf 3.0.4_0</span>
<span style="font-size:small">---&gt;  Installing gperf @3.0.4_0</span>
<span style="font-size:small">---&gt;  Cleaning gperf</span>
<span style="font-size:small">---&gt;  Fetching libiconv</span>
<span style="font-size:small">---&gt;  Attempting to fetch libiconv-1.13.tar.gz from http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/libiconv</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for libiconv</span>
<span style="font-size:small">---&gt;  Extracting libiconv</span>
<span style="font-size:small">---&gt;  Applying patches to libiconv</span>
<span style="font-size:small">---&gt;  Configuring libiconv</span>
<span style="font-size:small">---&gt;  Building libiconv</span>
<span style="font-size:small">---&gt;  Staging libiconv into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for libiconv 1.13_0</span>
<span style="font-size:small">---&gt;  Installing libiconv @1.13_0</span>
<span style="font-size:small">---&gt;  Cleaning libiconv</span>
<span style="font-size:small">---&gt;  Fetching zlib</span>
<span style="font-size:small">---&gt;  Attempting to fetch zlib-1.2.3.tar.bz2 from http://mesh.dl.sourceforge.net/libpng</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for zlib</span>
<span style="font-size:small">---&gt;  Extracting zlib</span>
<span style="font-size:small">---&gt;  Applying patches to zlib</span>
<span style="font-size:small">---&gt;  Configuring zlib</span>
<span style="font-size:small">---&gt;  Building zlib</span>
<span style="font-size:small">---&gt;  Staging zlib into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for zlib 1.2.3_2</span>
<span style="font-size:small">---&gt;  Installing zlib @1.2.3_2</span>
<span style="font-size:small">---&gt;  Cleaning zlib</span>
<span style="font-size:small">---&gt;  Fetching libpng</span>
<span style="font-size:small">---&gt;  Attempting to fetch libpng-1.2.37.tar.bz2 from http://mesh.dl.sourceforge.net/libpng</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for libpng</span>
<span style="font-size:small">---&gt;  Extracting libpng</span>
<span style="font-size:small">---&gt;  Configuring libpng</span>
<span style="font-size:small">---&gt;  Building libpng</span>
<span style="font-size:small">---&gt;  Staging libpng into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for libpng 1.2.37_0</span>
<span style="font-size:small">---&gt;  Installing libpng @1.2.37_0</span>
<span style="font-size:small">---&gt;  Cleaning libpng</span>
<span style="font-size:small">---&gt;  Fetching bzip2</span>
<span style="font-size:small">---&gt;  Attempting to fetch bzip2-1.0.5.tar.gz from http://www.bzip.org/1.0.5</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for bzip2</span>
<span style="font-size:small">---&gt;  Extracting bzip2</span>
<span style="font-size:small">---&gt;  Applying patches to bzip2</span>
<span style="font-size:small">---&gt;  Configuring bzip2</span>
<span style="font-size:small">---&gt;  Building bzip2</span>
<span style="font-size:small">---&gt;  Staging bzip2 into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for bzip2 1.0.5_2</span>
<span style="font-size:small">---&gt;  Installing bzip2 @1.0.5_2</span>
<span style="font-size:small">---&gt;  Cleaning bzip2</span>
<span style="font-size:small">---&gt;  Fetching ncursesw</span>
<span style="font-size:small">---&gt;  Attempting to fetch ncurses-5.7.tar.gz from http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/ncurses</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for ncursesw</span>
<span style="font-size:small">---&gt;  Extracting ncursesw</span>
<span style="font-size:small">---&gt;  Configuring ncursesw</span>
<span style="font-size:small">---&gt;  Building ncursesw</span>
<span style="font-size:small">---&gt;  Staging ncursesw into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for ncursesw 5.7_0</span>
<span style="font-size:small">---&gt;  Installing ncursesw @5.7_0</span>
<span style="font-size:small">---&gt;  Cleaning ncursesw</span>
<span style="font-size:small">---&gt;  Fetching ncurses</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for ncurses</span>
<span style="font-size:small">---&gt;  Extracting ncurses</span>
<span style="font-size:small">---&gt;  Configuring ncurses</span>
<span style="font-size:small">---&gt;  Building ncurses</span>
<span style="font-size:small">---&gt;  Staging ncurses into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for ncurses 5.7_0</span>
<span style="font-size:small">---&gt;  Installing ncurses @5.7_0</span>
<span style="font-size:small">---&gt;  Cleaning ncurses</span>
<span style="font-size:small">---&gt;  Fetching readline</span>
<span style="font-size:small">---&gt;  Attempting to fetch readline-6.0.tar.gz from http://www.mirrorservice.org/sites/ftp.gnu.org/gnu/readline</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for readline</span>
<span style="font-size:small">---&gt;  Extracting readline</span>
<span style="font-size:small">---&gt;  Applying patches to readline</span>
<span style="font-size:small">---&gt;  Configuring readline</span>
<span style="font-size:small">---&gt;  Building readline</span>
<span style="font-size:small">---&gt;  Staging readline into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for readline 6.0.000_1</span>
<span style="font-size:small">---&gt;  Installing readline @6.0.000_1</span>
<span style="font-size:small">---&gt;  Cleaning readline</span>
<span style="font-size:small">---&gt;  Fetching pcre</span>
<span style="font-size:small">---&gt;  Attempting to fetch pcre-7.9.tar.bz2 from http://mesh.dl.sourceforge.net/pcre</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for pcre</span>
<span style="font-size:small">---&gt;  Extracting pcre</span>
<span style="font-size:small">---&gt;  Configuring pcre</span>
<span style="font-size:small">---&gt;  Building pcre</span>
<span style="font-size:small">---&gt;  Staging pcre into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for pcre 7.9_0</span>
<span style="font-size:small">---&gt;  Installing pcre @7.9_0</span>
<span style="font-size:small">---&gt;  Cleaning pcre</span>
<span style="font-size:small">---&gt;  Fetching slang2</span>
<span style="font-size:small">---&gt;  Attempting to fetch slang-2.1.4.tar.bz2 from ftp://ftp.plig.org/pub/slang/v2.1/</span>
<span style="font-size:small">---&gt;  Attempting to fetch slang-2.1.4.tar.bz2 from http://trd.no.distfiles.macports.org/slang2</span>
<span style="font-size:small">---&gt;  Attempting to fetch slang-2.1.4.tar.bz2 from ftp://ftp.ntua.gr/pub/lang/slang/slang/v2.1/</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for slang2</span>
<span style="font-size:small">---&gt;  Extracting slang2</span>
<span style="font-size:small">---&gt;  Configuring slang2</span>
<span style="font-size:small">---&gt;  Building slang2</span>
<span style="font-size:small">---&gt;  Staging slang2 into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for slang2 2.1.4_0</span>
<span style="font-size:small">---&gt;  Installing slang2 @2.1.4_0</span>
<span style="font-size:small">---&gt;  Cleaning slang2</span>
<span style="font-size:small">---&gt;  Fetching most</span>
<span style="font-size:small">---&gt;  Attempting to fetch most-5.0.0a.tar.bz2 from http://trd.no.distfiles.macports.org/most</span>
<span style="font-size:small">---&gt;  Attempting to fetch most-5.0.0a.tar.bz2 from ftp://space.mit.edu/pub/davis/most/</span>
<span style="font-size:small">---&gt;  Verifying checksum(s) for most</span>
<span style="font-size:small">---&gt;  Extracting most</span>
<span style="font-size:small">---&gt;  Configuring most</span>
<span style="font-size:small">---&gt;  Building most</span>
<span style="font-size:small">---&gt;  Staging most into destroot</span>
<span style="font-size:small">---&gt;  Packaging tbz2 archive for most 5.0.0a_1</span>
<span style="font-size:small">---&gt;  Installing most @5.0.0a_1</span>
<span style="font-size:small">---&gt;  Cleaning most</span>
<span style="font-size:small"># most</span>
<span style="font-size:small">MOST version 5.0.0 (S-Lang version 2.1.4)</span>
<span style="font-size:small">Usage:</span>
<span style="font-size:small">most [-1Cbcdkstvw] [+/string] [+line number] [+s] [+d] file...</span>
<span style="font-size:small">[...]</span>


<span style="font-size:18px;font-weight:bold">Troubleshooting</span>

### Compiling MacPorts in PureDarwin

<span style="font-size:13px">**<span style="font-family:Arial,Verdana,sans-serif;font-weight:normal"></span>**</span>
<span style="font-weight:bold"><span style="font-size:small">Problem: </span><span style="font-family:courier new,monospace;font-weight:normal"><span style="font-size:small">/usr/include/sys/stat.h:75:26: error: Availability.h: No such file or directory</span></span></span>
<span style="font-size:12px"></span>
<span style="font-family:arial"><span style="font-size:small">There is a new CarbonHeaders-9G55 posted which adds the rest of the Availability*.h headers that were missing. Install it.</span></span>
<span style="font-family:arial"><span style="font-size:small">Solution: </span><span style="font-family:courier new,monospace;font-weight:normal"><span style="font-size:small">cd /Volume/PureDarwin</span></span></span>

<span style="font-size:small">tar xzvf [...]9J61/Packages/CarbonHeaders.hdrs.tar.gz</span>

<span style="font-size:small">tar xzvf [...]9J61/Packages/CarbonHeaders.root.tar.gz</span>
<span style="font-size:small">
</span>


<span style="font-family:courier new,monospace;font-size:small"><span style="font-family:Arial;font-size:13px;font-weight:bold">Problem: </span>/usr/bin/tclsh src/dep_map_clean.tcl /opt/local/lib/tcl8.5</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">can't find package Pextlib 1.0</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    while executing</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">"package require Pextlib 1.0"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    (file "/opt/local/share/macports/Tcl/registry1.0/receipt_flat.tcl" line 37)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    invoked from within</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">"source /opt/local/share/macports/Tcl/registry1.0/receipt_flat.tcl"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    ("package ifneeded receipt_flat 1.0" script)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    invoked from within</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">"package require receipt_flat 1.0"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    (file "/opt/local/share/macports/Tcl/registry1.0/registry.tcl" line 35)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    invoked from within</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">"source /opt/local/share/macports/Tcl/registry1.0/registry.tcl"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    ("package ifneeded registry 1.0" script)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    invoked from within</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">"package require registry 1.0"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    (file "src/dep_map_clean.tcl" line 10)</span></span>
<span style="font-family:courier new;font-size:12px"><span style="font-family:Arial;font-size:13px"></span></span>
<span style="font-weight:bold">Solution: Please, let us know if you have one. <span style="font-weight:normal">See the [attached compilation output](macportsonpuredarwin/configure_output_MP1.7.0%3Fattredirects=0) for more details.</span></span>
Seems to be fixed since MacPorts v1.7.1
Deprecated stuff
----------------
<span style="font-size:12px"></span>
### Compiling MacPorts 1.7.1 in a PureDarwin chroot
Depending the case, the archive can come from DarwinBuild or MacPorts since most of these projects can be built into DarwinBuild and/or MacPorts.

<span style="font-family:courier new,monospace"><span style="font-size:small">cd /Volumes/PureDarwin</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf [...]MacPorts-1.7.1.tar.gz</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gcc.root.tar.gz</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gcc_42.root.tar.gz</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gcc_os.root.tar.gz</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gcc_select.root.tar.gz (optional?)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/gccfast.root.tar.gz   </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/Libc_headers.root.tar.gz</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/tcsh.root.tar.gz (needed?)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/OpenSSL.root.tar.gz</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/SQLite.root.tar.gz </span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Packages/curl.root.tar.gz </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf /Volumes/Builds/9G55/Packages/gnumake.root.tar.gz            </span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.6_0+threads.i386.tbz2</span></span>
<span style="font-size:small">bzip2.root.tar.bz2</span>


These steps (tar tar tar...) can be replaced by a proper `pd_roots' (soon available) file at setup, and a minimal amount of tar:

<span style="font-family:courier new,monospace"><span style="font-size:small">cd /Volumes/PureDarwin</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">tar xzvf [...]/MacPorts-1.7.1.tar.gz</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.6_0+threads.i386.tbz2</span></span>
<span style="font-size:small">bzip2.root.tar.bz2</span>

Then

<span style="font-family:courier new,monospace"><span style="font-size:small">chroot .</span></span>


Since the tcl project (idem for X11) cannot be built right now in DarwinBuild, we're using one built from MacPorts.
<span>We alterate in consequences some configure flags and vars (e.g., <span style="font-style:italic">TCLSH</span>), because `dtrace' told to us when `configure' hits tclsh test:</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  1  18023                       stat:entry sh /bin/tclsh</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  1  18023                       stat:entry sh /sbin/tclsh</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  1  18023                       stat:entry sh /usr/bin/tclsh</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  1  18023                       stat:entry sh /usr/sbin/tclsh</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  1  18023                       stat:entry sh /usr/local/bin/tclsh</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  1  18023                       stat:entry sh /usr/local/sbin/tclsh</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  1  18023                       stat:entry sh /usr/libexec/tclsh</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  1  18023                       stat:entry sh /System/Library/CoreServices/tclsh</span></span>

<span>Also, after a quick look in the `configure' file:</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">ac_cv_path_TCLSH="$TCLSH" # Let the user override the test with a path.</span></span>
<span style="font-family:Helvetica;font-size:12px">Exactly what we need, in fact! </span>



Without X11:

<span><span style="font-family:courier new,monospace"><span style="font-size:small">TCLSH=/opt/local/bin/tclsh </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">./configure --without-objc-foundation --without-objc-runtime  --without-x  --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include --with-included-tclthread</span></span></span>

With X11 from MacPorts:

<span style="font-family:courier new,monospace"><span style="font-size:small">tar xjvf /opt/local/var/macports/packages/darwin/i386/xorg-libX11-1.1.5_1+x11_xcb.i386.tbz2</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">TCLSH=/opt/local/bin/tclsh </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">./configure --without-objc-foundation --without-objc-runtime --with-x --x-includes=/usr/X11R6/include/ --x-libraries=/usr/X11R6/lib/ --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include --with-included-tclthread</span></span></span>

Then simply:

<span style="font-family:courier new">make</span>
make install
[...]

Congratulations, you have successfully installed the MacPorts system. To get the Portfiles and update the system, run:

sudo port -v selfupdate

Please read "man port", the MacPorts guide at http://guide.macports.org/ and Wiki at http://trac.macports.org/ for full documentation.

Stray sources might have been left in the legacy /opt/local/var/db/dports directory after this upgrade, which moved most of what it could to /opt/local/var/macports, so you might want to look in the former and cleanup manually.


<span style="font-size:12px"></span>
<span style="font-family:Helvetica;font-size:12px"></span>
### Deprecated (Compiling MacPorts 1.6.0 on DarwinBuild)

<span style="font-weight:bold"><span style="font-family:arial,sans-serif"><span style="font-size:small">Problem</span></span><span style="font-size:small">:</span></span><span style="font-size:small"> </span><span style="font-family:courier new"><span style="font-size:small">checking for Tcl configuration... configure: error: Can't find Tcl configuration definitions</span></span>

<span style="font-family:courier new"><span style="font-family:Arial;font-weight:bold"><span style="font-size:small">Solution: </span><span style="font-weight:normal"><span style="font-size:small">darwinbuild tcl && darwinbuild -load tcl</span><span style="font-size:small"> (it fails to build at this time (carbon headers missing))</span></span></span></span>
<span style="font-size:small">or alternatively, use some binary roots from MacPorts:</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">cd BuildRoot</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xjvf /opt/local/var/macports/packages/darwin/i386/tcl-8.5.4_0+threads.i386.tbz2</span></span>
<span style="font-family:courier new"><span style="font-size:small">chroot .</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">ln -s /opt/local/bin/tclsh8.5 /usr/bin/   </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">ln -s /opt/local/bin/tclsh8.5 /usr/bin/tclsh</span></span>

<span style="font-size:small">Be sure to precise the alternative path in case you MacPorts: </span><span style="font-family:courier new"><span style="font-size:small">./configure --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include</span></span>

<span style="font-weight:bold"><span style="font-size:small">Problem:</span></span><span style="font-size:small"> </span><span style="font-family:courier new,monospace"><span style="font-size:small">configure: error: cannot find curl-config. Is libcurl installed?</span></span>
<span style="font-weight:bold"><span style="font-size:small">Solution:</span></span><span style="font-size:small"> </span><span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild curl && darwinbuild -load curl</span></span>

<span style="font-size:small">
</span>
<span style="font-size:small">Then we can run `make' but it fails on:</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">gcc -pipe -DPACKAGE_NAME="thread" -DPACKAGE_TARNAME="thread" -DPACKAGE_VERSION="2.6" -DPACKAGE_STRING="thread 2.6" -DPACKAGE_BUGREPORT="" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DNO_VALUES_H=1 -DHAVE_LIMITS_H=1 -DHAVE_SYS_PARAM_H=1 -DUSE_THREAD_ALLOC=1 -D_REENTRANT=1 -D_THREAD_SAFE=1 -DHAVE_PTHREAD_ATTR_SETSTACKSIZE=1 -DHAVE_READDIR_R=1 -DTCL_THREADS=1 -DTCL_WIDE_INT_TYPE=long long -DHAVE_STRUCT_STAT64=1 -DUSE_TCL_STUBS=1   -I"/opt/local/include"    -I/opt/local/include -Os -Wall -Wno-implicit-int -fno-common -c `echo ./generic/threadPoolCmd.c` -o threadPoolCmd.o</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">In file included from /usr/include/sys/time.h:77,</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">                 from ./generic/threadPoolCmd.c:1707:</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">/usr/include/sys/_structs.h: In function 'GetTime':</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">/usr/include/sys/_structs.h:192: error: nested functions are disabled, use -fnested-functions to re-enable</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">/usr/include/sys/_structs.h:192: error: invalid storage class for function '__darwin_fd_isset'</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">make[2]: *** [threadPoolCmd.o] Error 1</span></span>
<span style="font-size:small">
</span>

<span style="font-size:small">Without tclthread seems to make a difference:</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">./configure --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include -without-included-tclthread</span></span>
<span style="font-size:small">
</span>
<span style="font-size:small">But the classic missing foundation header appears:</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">tclobjc.m:42:35: error: Foundation/Foundation.h: No such file or directory</span></span>

<span style="font-size:small">
</span>
<span style="font-size:small">So, let's try with Foundation replacement from GNUstep compiled through MacPorts:</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">cd BuildRoot</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xjvf /opt/local/var/macports/packages/darwin/i386/gnustep-base-1.14.0_0+ffi.i386.tbz2</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">GNUSTEP_SYSTEM_ROOT=/opt/local/GNUstep/System ./configure --with-tcl=/opt/local/lib --with-tclinclude=/opt/local/include -without-included-tclthread</span></span>
<span style="font-size:small">It fails on:</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">In file included from /opt/local/GNUstep/System/Library/Headers/Foundation/NSObjCRuntime.h:33,</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">                 from /opt/local/GNUstep/System/Library/Headers/Foundation/Foundation.h:33,</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">                 from conftest.m:25:</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/GNUstep/System/Library/Headers/GNUstepBase/GSObjCRuntime.h: In function 'GSObjCClass':</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/GNUstep/System/Library/Headers/GNUstepBase/GSObjCRuntime.h:186: error: 'struct objc_object' has no member named 'class_pointer'</span></span>
<span style="font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:12px"></span></span>
Quick method: Install MacPorts on PureDarwin using the binary pkg provided by the MacPorts project
--------------------------------------------------------------------------------------------------

On the MacPorts website, there is a pkg that contains MacPorts for the Mac. In this section, we are trying to use this pkg to install MacPorts on PureDarwin. For a PureDarwin 9 system, we need to download the MacPorts version for Leopard. Next, we need to delete the file MacPorts-1.8.2.pkg/Contents/Resources/InstallationCheck, otherwise we just get "Error - This package is meant to be installed on Mac OS X 10.5.". Next, we can install the package into our PureDarwin system: 

<span style="font-size:small">installer -pkg MacPorts-1.8.2.pkg -target /Volumes/PureDarwin/</span>

Now we chroot into the PureDarwin system and try to run the "port" command:

<span style="font-size:small">sh-3.2# port</span>
<span style="font-size:small">/opt/local/bin/port: line 4: /usr/bin/tclsh: No such file or directory</span>
<span style="font-size:small">/opt/local/bin/port: line 4: exec: /usr/bin/tclsh: cannot execute: No such file or directory</span>

Hence we need to symlink tclsh from /opt/local/bin:

<span style="font-size:small">sh-3.2# ln -s /opt/local/bin/tclsh /usr/bin/</span>

Now the port command almost runs, but for some strange reason the con files are missing, so we need to do

<span style="font-size:small">cp /opt/local/etc/macports/macports.conf.default /opt/local/etc/macports/macports.conf</span>
<span style="font-size:small">cp /opt/local/etc/macports/sources.conf.default /opt/local/etc/macports/sources.conf</span>
<span style="font-size:small">cp /opt/local/etc/macports/variants.conf.default /opt/local/etc/macports/variants.conf</span>

**Important: **Now we need to configure MacPorts as described on the [MacPorts](../macports.1.html) page.

At this point, the port command should be launchable and working.



<span style="font-size:12px"></span>
Resources
---------
<http://www.macports.org/> 


<http://svn.macosforge.org/repository/macports/branches/>

