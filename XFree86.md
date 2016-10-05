XFree86
=======
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](../_/rsrc/1222686502548/developers/xfree86/Xfree86.logo.gif%3Fheight=100&width=200)](xfree86/Xfree86.logo.gif%3Fattredirects=0)
This page is about [XFree86](http://www.xfree86.org/) on Darwin.
<div style="margin:5px 10px;display:inline;float:right">
<span style="color:rgb(85,26,139);text-decoration:underline">
</span>
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:400px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** XFree86 4.7.0](xfree86.html#TOC-XFree86-4.7.0)
2.  [**2** XFree86 in MacPorts](xfree86.html#TOC-XFree86-in-MacPorts)
    1.  [**2.1** Compiling XFree86 for PureDarwin](xfree86.html#TOC-Compiling-XFree86-for-PureDarwin)
    2.  [**2.2** Compiling FreeType for PureDarwin](xfree86.html#TOC-Compiling-FreeType-for-PureDarwin)
    3.  [**2.3** Installing XFree86 on PureDarwin](xfree86.html#TOC-Installing-XFree86-on-PureDarwin)
3.  [**3** Screenshots](xfree86.html#TOC-Screenshots)
4.  [**4** Troubleshooting](xfree86.html#TOC-Troubleshooting)
    1.  [**4.1** Conflicting /usr/X11R6](xfree86.html#TOC-Conflicting-usr-X11R6)
    2.  [**4.2** MAXHOSTNAMELEN undeclared](xfree86.html#TOC-MAXHOSTNAMELEN-undeclared)
    3.  [**4.3** decompress.c error](xfree86.html#TOC-decompress.c-error)
    4.  [**4.4** Cannot establish any listening sockets](xfree86.html#TOC-Cannot-establish-any-listening-sockets)
    5.  [**4.5** Missing keymap](xfree86.html#TOC-Missing-keymap)
    6.  [**4.6** Font-related problem when launching xterm](xfree86.html#TOC-Font-related-problem-when-launching-xterm)
    7.  [**4.7** Failed to connect to the HID system](xfree86.html#TOC-Failed-to-connect-to-the-HID-system)
    8.  [**4.8** No screens found](xfree86.html#TOC-No-screens-found)
    9.  [**4.9** assert failed on line 416 of xfIOKit.c!](xfree86.html#TOC-assert-failed-on-line-416-of-xfIOKit.c-)
5.  [**5** Resources](xfree86.html#TOC-Resources)

### XFree86 4.7.0
XFree86 is another X11 implementation besides [X.Org](xorg.html). Version 4.7.0 was released in 2007.
Most binaries you can find on the net (e.g., in fink) are built for Mac OS X, and will fail to run on PureDarwin since they depend on closed frameworks such as ApplicationServices. Hence, we need to compile XFree86 specifically for PureDarwin, and MacPorts can help us with this task.
``
### XFree86 in MacPorts
MacPorts contains a portfile which can be used to compile XFree86 for PureDarwin. In old release notes, it is stated that "*Darwin/Mac OS X uses IOKit drivers and does not use the module loader drivers listed above. Further information can be found in [README.Darwin](http://cvsweb.xfree86.org/cvsweb/xc/programs/Xserver/hw/xfree86/doc/README.Darwin?rev=1.28&content-type=text/vnd.viewcvs-markup)*". Also take a look at [Using the MacPorts project](macports.1.html) page for more information about MacPorts.
``
<span><span style="font-family:arial,sans-serif"><span style="font-size:small">The portfile shows the following information about Xfree86, among other things:</span></span></span>
<div style="color:rgb(0,0,0)">
<span style="font-family:courier new">
 </span>
<div style="color:rgb(0,0,0)">
<span style="font-family:courier new,monospace"><span style="font-size:small">port info XFree86</span></span>
<span style="font-family:Arial;font-size:13px"> </span>
<div style="color:rgb(68,68,68)">
<span style="font-family:courier new,monospace"><span style="font-size:small">XFree86 4.7.0, x11/XFree86 (Variants: darwin, <span style="font-weight:bold">puredarwin</span>, macosx)</span></span>
<div style="color:rgb(68,68,68)">
<span style="font-family:courier new;font-size:12px">(...)</span>
<div style="color:rgb(68,68,68)">
<span style="font-family:courier new,monospace"><span style="font-size:small">Platforms: darwin freebsd</span></span>

In the case of <span style="font-family:courier new,monospace">+puredarwin</span> variant is choosen, this is what happens:


<span style="font-family:courier new;font-size:12px"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">platform puredarwin {</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">    post-patch {  </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        set hostfd [open "${worksrcpath}/config/cf/host.def" a+]</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        puts $hostfd "#define DarwinQuartzSupport NO"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        puts $hostfd "#define BuildGlxExt         YES"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        puts $hostfd "#define BuildGLXLibrary     YES"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        close $hostfd</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    }</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">}</span></span>

#### Compiling XFree86 for PureDarwin
We are using MacPorts on a Mac and transfer the final build products to a PureDarwin system thereafter, as described on the [MacPorts](macports.1.html) page. Later, we will be able to bootstrap MacPorts on PureDarwin in order to provide products built on a PureDarwin system for a PureDarwin system.

<span style="text-decoration:underline">Note:</span> You should configure MacPorts to procuce tbz2 archives as described on that page.

Add <span style="font-family:courier new,monospace"><span style="font-size:small">-v</span></span> for verbose output.

First, you need to move a symlink to Apple's X.Org (X11.app) so that it doesn't interfere with XFree86 from MacPorts:
<span style="color:rgb(68,68,68);font-family:courier new;font-size:12px">
 </span>
<span style="color:rgb(68,68,68);font-family:courier new;font-size:12px">sudo mv /usr/X11R6 /usr/X11R6.apple</span>


<span style="font-family:Arial;font-size:13px"> </span>
<span style="color:rgb(68,68,68);font-family:courier new;font-size:12px"> </span>
<div style="font-family:arial,sans-serif">
<span style="color:rgb(0,0,0);font-family:Helvetica;font-size:13px"><span style="color:rgb(255,0,0);font-size:12px"><span style="color:rgb(0,0,0);font-size:13px">Then do:</span></span></span>

<span style="color:rgb(0,0,0);font-family:Helvetica"> </span>


<span style="font-family:courier new">port archive xfree86 +puredarwin</span>
<span style="font-size:13px">
 </span>
<span style="font-size:13px">If the build succeeds, you should see:</span>
<span style="font-size:13px">
 </span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Warning: XFree86 requests to install files outside the common directory structure!</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">---&gt; Installing XFree86 4.7.0_0+macosx+puredarwin</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">---&gt; Activating XFree86 4.7.0_0+macosx+puredarwin</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">---&gt; Cleaning XFree86</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">---&gt; Removing build directory for XFree86</span></span></span>


<span style="font-family:courier new"><span style="color:rgb(68,68,68)"> </span></span>
<span style="font-family:Helvetica"><span style="color:rgb(0,0,0)">On Mac OS X, the symbolic link created with MacPorts is wrong.</span></span>
<span style="color:rgb(0,0,0);font-family:Helvetica;font-size:13px">
 </span>
<span style="font-family:Helvetica"> </span>
<span style="color:rgb(0,0,0)"><span style="font-family:courier new,monospace"><span style="font-size:small">ln -fs /usr/X11R6/bin/XDarwin /Applications/MacPorts/XDarwin.app</span></span> should resolve the link.</span>
<span style="color:rgb(0,0,0)">
 </span>
<span style="color:rgb(0,0,0)"><span style="font-family:arial,sans-serif"><span style="font-size:small">Before we install XFree86, let's build some libraries that are needed by many applications that run on X. </span></span></span>
<span style="color:rgb(0,0,0)"><span style="color:rgb(68,68,68);font-family:Helvetica;font-size:12px"><span style="font-family:arial,sans-serif"><span style="font-size:small"> </span></span></span></span>
#### Compiling FreeType for PureDarwin {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
<span style="font-family:arial,sans-serif"><span style="font-size:small">Many graphical applications need freetyp, so we need to compile it in a way that it can be used on PureDarwin.</span></span>
<span style="font-family:arial,sans-serif"><span style="font-size:small">We need to patch the Portfile with</span></span>


<span style="font-family:courier new,monospace">sed -i 's|--with-old-mac-fonts|--without-ats|g' 
 /opt/local/var/macports/sources/*/release/ports/print/freetype/Portfile</span>

<span style="color:rgb(255,0,0)"><span style="font-size:small">TODO: the portfile should get a "puredarwin" section that sets this option automatically.</span></span>
<span style="font-size:small">Build it with</span>
<span style="font-size:small">
</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">sudo /opt/local/bin/port archive freetype +puredarwin</span></span>
<span style="font-size:small">
</span>
<span style="font-size:small">To be sure, check that the output of</span>
<span style="font-size:small">
</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/var/macports/sources/*/release/ports/print/freetype/work/destroot/opt/local/bin/freetype-config --libs</span></span>
<span style="font-size:small">
</span>
<span style="font-size:small">does not contain ApplicationServices or other proprietary frameworks.</span>
<span style="font-size:small">The following output is fine</span>
<span style="font-size:small">
</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-L/opt/local/lib -lfreetype -lz</span></span>
<span style="font-size:small">
</span>
<span style="font-size:small">whereas this would not be fine</span>
<span style="font-size:small">
</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-L/opt/local/lib -lfreetype -lz -Wl,-framework,CoreServices -Wl,-framework,ApplicationServices</span></span>

#### Installing XFree86 on PureDarwin {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}


First, install on your PureDarwin system what you have compiled above.
<span style="font-size:13px">
</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">cd /Volumes/PureDarwin</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">tar xfvj /opt/local/var/macports/packages/darwin/i386/XFree86-4.7.0_0+macosx+puredarwin.i386.tbz2</span></span>
<span><span style="font-size:small"><span style="font-family:courier new,monospace">tar xfvj /o</span><span style="font-family:courier new,monospace">pt/local/var/</span><span style="font-family:courier new,monospace">macports/packages/darwin/i386/freetype-2.3.7_1.i386.tbz2</span></span></span>
<span><span style="font-family:courier new,monospace">curl http://src.macosforge.org/BinaryDrivers/8C46/GraphicsDrivers.root.tar.gz &gt; GraphicsDrivers.root.tar.gz</span></span>
<span><span style="font-family:courier new,monospace">tar xfvz GraphicsDrivers.root.tar.gz</span></span>
<span><span style="font-family:courier new,monospace">curl http://src.macosforge.org/Roots/9C31/IOGraphics.root.tar.gz &gt; IOGraphics.root.tar.gz</span></span>

<span style="font-family:courier new,monospace">tar xfvz IOGraphics.root.tar.gz </span>


The compiled XFree86 from the MacPorts project has the following library dependencies. Make sure these are present on your PureDarwin system:
-   <span style="font-size:small"><span style="font-family:arial,sans-serif">libfreetype.6.dylib</span></span>
-   <span style="font-size:small"><span style="font-family:arial,sans-serif">usr/lib/libz.1.dylib</span></span>
-   <span style="font-size:small"><span style="font-family:arial,sans-serif">/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit</span></span>
-   <span style="font-size:small"><span style="font-family:arial,sans-serif">/usr/lib/libgcc_s.1.dylib</span></span>
-   <span style="font-size:small"><span style="font-family:arial,sans-serif">/usr/lib/libSystem.B.dylib</span></span>

<span style="font-size:13px">Furthermore, you need to download some keymaps from [XDarwin.org](http://www.xdarwin.org/keymappings/) site (These will have to be integrated in a more nicely way. <span style="color:rgb(255,0,0)">TODO: Have them in MacPorts</span>). When you launch X, you can specify an alternative keymap used at the command line.</span>

<span style="font-size:13px">
 </span>

<span><span style="font-size:small">You also need to have in the PureDarwin system:</span></span><span style="font-size:small">
</span>
-   <span style="font-size:13px">IOGraphicsFamily.kext (from DarwinBuild)</span>
-   <span style="font-size:13px">[VMwareIOFramebuffer.kext](../downloads.html) (optional - if using VMware; from the VMware Tools)</span>

<span style="font-family:Arial;font-size:14px;font-weight:bold">Running XFree86 on PureDarwin</span>
<span style="font-size:13px">
 </span>

<span style="font-size:13px">Make sure the KEXTs are loaded:</span>


<span style="font-family:courier new,monospace"><span style="font-size:small">kextload /System/Library/Extensions/IOGraphicsFamily.kext</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">kextload /System/Library/Extensions/VMwareIOFramebuffer.kext</span></span>

Additionally, in order to add your keyboard, mouse and/or trackpad support for XFree86, you should load the corresponding kernel extension. In case of PS2, take a look at the [PS2 Controller](xnu/ps2-controller.html) page.
<span style="font-size:small"><span style="font-size:13px">
</span></span>
<span style="text-decoration:underline">Notes</span>: USB mouse and Apple MacBook trackpad works. PS2 not (yet) tested.
<span style="font-size:13px">
</span>
<span style="font-size:13px"><span style="font-size:12px"></span></span>
Launch X with


<span style="font-family:courier new,monospace"><span><span style="font-size:small">mount -uw / # need to be rw so that /tmp/.tX0-lock and /tmp/.X11-unix socket can be created</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">export PATH=/usr/X11R6/bin:$PATH</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">export DISPLAY=:0.0</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">X -nolisten tcp -size 800 600 -keymap USA.keymapping & sleep 3 && xeyes</span></span></span>


[![](../_/rsrc/1222645430661/developers/xorg/XFree86%204.7.0%20xeyes%20vmware.png%3Fheight=342&width=420)](xorg/XFree86%204.7.0%20xeyes%20vmware.png%3Fattredirects=0)

### Screenshots
The oldschool <span style="font-style:italic">twm</span> remains functional.


[![](../_/rsrc/1223002130567/developers/xfree86/XFree86%20on%20puredarwin%20nano.png%3Fheight=337&width=420)](xfree86/XFree86%20on%20puredarwin%20nano.png%3Fattredirects=0)



Also the minimalist <span style="font-style:italic">wmii.</span>


[![](../_/rsrc/1223036210964/developers/xfree86/wmii%20XFree86%20wmware.png%3Fheight=277&width=420)](xfree86/wmii%20XFree86%20wmware.png%3Fattredirects=0)



<span style="font-size:13px"><span style="font-style:italic">glxgears</span> appears to work and performances are not so bad inside a vm.</span>
<span style="font-size:13px">
 </span>

[![](../_/rsrc/1223036971869/developers/xfree86/glxgears%20XFree86%20vmware.png%3Fheight=279&width=420)](xfree86/glxgears%20XFree86%20vmware.png%3Fattredirects=0)



<span style="font-style:italic">Fluxbox</span> now!


[![](../_/rsrc/1223054667768/developers/xfree86/fluxbox%20XFree86%20vmware.png%3Fheight=278&width=420)](xfree86/fluxbox%20XFree86%20vmware.png%3Fattredirects=0)


[![](../_/rsrc/1223058912929/developers/xfree86/xterm%20fluxbox%20bis%20XFree86%20vmware.png%3Fheight=277&width=420)](xfree86/xterm%20fluxbox%20bis%20XFree86%20vmware.png%3Fattredirects=0)



<span style="font-style:italic">Windowmaker</span> compiles and runs like a charm as soon as we get rid of problematic dependencies.


[![](../_/rsrc/1223112720564/developers/xfree86/windowmaker%20XFree86%20vmware.png%3Fheight=278&width=420)](xfree86/windowmaker%20XFree86%20vmware.png%3Fattredirects=0)



Idem for <span style="font-style:italic">enlightenment</span> 17.


[![](../_/rsrc/1223252476544/developers/xfree86/enlightenment%20starting%20in%20XFree86%20in%20vmware.png%3Fheight=276&width=420)](xfree86/enlightenment%20starting%20in%20XFree86%20in%20vmware.png%3Fattredirects=0)


[![](../_/rsrc/1223252291709/developers/xfree86/enlightenment%20XFree86%20vmware.png%3Fheight=278&width=420)](xfree86/enlightenment%20XFree86%20vmware.png%3Fattredirects=0)



<span style="font-style:italic">qt3</span> and <span style="font-style:italic">qt4-x11</span> are almost ok.


[![](../_/rsrc/1223416292080/developers/xfree86/filelight%20with%20qt3.png%3Fheight=337&width=420)](xfree86/filelight%20with%20qt3.png%3Fattredirects=0)


[![](../_/rsrc/1223416289644/developers/xfree86/some%20qt3%20apps.png%3Fheight=332&width=420)](xfree86/some%20qt3%20apps.png%3Fattredirects=0)








### Troubleshooting
#### Conflicting /usr/X11R6
<span style="color:rgb(68,68,68);font-family:courier new;font-size:12px"></span>
<span style="color:rgb(0,0,0)"><span style="font-family:Arial;font-size:13px;font-weight:bold">Problem:</span></span>
<span style="color:rgb(0,0,0)">port install xfree86 +puredarwin</span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"><span style="color:rgb(0,0,0)">[...]</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">---&gt; Fetching XFree86</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Error: Target org.macports.fetch returned: </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
 </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> You have an Apple X11 installation already.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> MacPorts will not overwrite it.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
 </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> If you really want to use XFree86 instead,</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> please move it aside first :</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
 </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> sudo mv /usr/X11R6 /usr/X11R6.apple</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span>
<span style="font-family:Helvetica;font-size:12px;font-weight:normal"><span style="color:rgb(68,68,68);font-family:courier new">Error: Status 1 encountered during processing.</span></span>
<span style="font-family:Helvetica;font-size:12px">
</span>
<span style="font-family:Helvetica;font-size:12px"><span style="font-weight:bold"><span style="font-family:Arial;font-size:13px">Solution</span>:</span></span>
<span style="font-family:Helvetica;font-size:12px;font-weight:normal"><span style="color:rgb(68,68,68);font-family:courier new">sudo mv /usr/X11R6 /usr/X11R6.apple</span></span> <span style="color:rgb(68,68,68);font-family:courier new;font-size:12px"> </span>
#### MAXHOSTNAMELEN undeclared
<span style="color:rgb(0,0,0)"><span style="font-family:Arial;font-size:13px;font-weight:bold">Problem:</span></span>
<span style="color:rgb(0,0,0)">port install xfree86 +puredarwin</span>
<div style="font-family:arial,sans-serif">
<span style="font-family:courier new"><span style="font-size:small"><span style="font-family:courier new,monospace"><span style="color:rgb(0,0,0)">[...]</span></span></span></span>
<div style="font-family:arial,sans-serif">
<span style="font-family:courier new"><span style="font-size:small"><span style="font-family:courier new,monospace">/usr/bin/cc -c -Wall -Wpointer-arith -no-cpp-precomp -fno-common -I. -I../../exports/include "-I/opt/local/var/macports/build/_opt_local_var_macports_sources_rsync.macports.org_release_ports_x11_XFree86/work/include" -D__i386__ -D__DARWIN__ -DNO_ALLOCA -DCSRG_BASED -DXTHREADS -D_REENTRANT -DXUSE_MTSAFE_API -DXNO_MTSAFE_UNISTDAPI -DHAS_SNPRINTF -DLIBX11</span></span><span style="white-space:pre"><span style="font-size:small"><span style="font-family:courier new,monospace"> </span></span></span><span style="font-size:small"><span style="font-family:courier new,monospace">-DPOSTLOCALELIBDIR="lib" </span></span><span style="white-space:pre"><span style="font-size:small"><span style="font-family:courier new,monospace"> </span></span></span><span style="font-size:small"><span style="font-family:courier new,monospace">-Os -fno-strict-aliasing -I../../lib/xtrans -DTCPCONN -DUNIXCONN -DHAS_STICKY_DIR_BIT -DHAS_FCHOWN -DIPv6 -DBSD44SOCKETS -DX11_t -DTRANS_CLIENT x11trans.c -o unshared/x11trans.o</span></span></span>

<span style="font-size:small"><span style="font-family:courier new,monospace">In file included from x11trans.c:82:</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">../../lib/xtrans/Xtranssock.c:1378: error: 'MAXHOSTNAMELEN' undeclared here (not in a function)</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">make[4]: *** [x11trans.o] Error 1</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">make[3]: *** [all] Error 1</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">make[2]: *** [all] Error 1</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">make[1]: *** [World] Error 2</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">make: *** [World] Error 2</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">
 </span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">Error: Status 1 encountered during processing.</span></span>

<div style="font-family:arial,sans-serif">
<span style="font-family:courier new"><span style="font-family:arial,sans-serif"><span style="color:rgb(0,0,0)"><span style="font-weight:bold"><span style="font-family:Arial">Solution</span>:</span></span></span></span>
<div style="font-family:arial,sans-serif">
<span style="font-family:courier new"><span style="font-family:arial,sans-serif"><span style="color:rgb(0,0,0)">The corresponding ticket </span></span><span style="font-size:13px"><span style="font-size:12px"><span><span style="font-size:small">[<span style="color:rgb(0,0,0)">#13895</span>](https://trac.macports.org/ticket/13895)<span style="color:rgb(0,0,0)"> of the error just above has been resolved.</span></span></span></span></span></span>

<span style="font-family:arial;font-size:13px"><span style="color:rgb(0,0,0)">Patch is also available in ticket </span><span style="color:rgb(0,0,0)">[#16697](https://trac.macports.org/ticket/16697) and in the attachments below. It looks like:</span></span>
<span style="color:rgb(0,0,0);font-family:arial;font-size:13px">
 </span>
<span style="color:rgb(0,0,0);font-family:arial;font-size:13px"> </span>
<span style="font-family:courier new,monospace"><span style="font-size:small">--- xc/lib/xtrans/Xtranssock.c.origin</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">2008-09-29 21:07:46.000000000 +0200</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">+++ xc/lib/xtrans/Xtranssock.c</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">2008-09-29 21:40:00.000000000 +0200</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">@@ -284,6 +284,8 @@</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> #ifndef __USLC__</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> #pragma weak getaddrinfo</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> #endif</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">+#else</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">+#define MAXHOSTNAMELEN 256</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> #endif</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> static int haveIPv6 = 1;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> #endif</span></span>
#### decompress.c error
<span style="color:rgb(0,0,0)"><span style="font-family:Arial;font-size:13px;font-weight:bold">Problem:</span></span>
<span style="color:rgb(0,0,0)">port install xfree86 +puredarwin</span>
<span style="color:rgb(0,0,0)">[...]</span>
<span style="color:rgb(0,0,0)"><span style="color:rgb(68,68,68);font-family:Helvetica"><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/bin/cc -c -Wall -Wpointer-arith -no-cpp-precomp -fno-common -I. -I../include -I../../../programs/Xserver/include -I../../../exports/include "-I/opt/local/var/macports/build/_opt_local_var_macports_sources_rsync.macports.org_release_ports_x11_XFree86/work/include" -D__i386__ -D__DARWIN__ -DNO_ALLOCA -DCSRG_BASED -DFONTDIRATTRIB </span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> -DBUILD_SPEEDO -DBUILD_TYPE1 -DBUILD_CID </span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> -DBUILD_FREETYPE -DFONT_ENCODINGS_DIRECTORY="/usr/X11R6/lib/X11/fonts/encodings/encodings.dir" -DX_GZIP_FONT_COMPRESSION </span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">-Os -fno-strict-aliasing decompress.c -o unshared/decompress.o</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">decompress.c:96: error: syntax error before 'z_magic'</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">decompress.c:464: error: dereferencing pointer to incomplete type
 make[5]: *** [decompress.o] Error 1
 make[4]: *** [fontfile] Error 1
 make[3]: *** [all] Error 1
 make[2]: *** [all] Error 1
 make[1]: *** [World] Error 2
 make: *** [World] Error 2</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Warning: the following items did not execute (for XFree86): org.macports.activate org.macports.build org.macports.destroot org.macports.install</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Error: Status 1 encountered during processing.</span></span>
<div style="font-family:arial,sans-serif">
<span style="font-family:courier new"><span style="font-family:arial,sans-serif"><span style="color:rgb(0,0,0)"><span style="font-weight:bold">Solution:</span></span></span></span>
<div style="font-family:arial,sans-serif">
<span style="font-family:courier new"><span style="font-family:arial,sans-serif"><span style="color:rgb(0,0,0)"><span style="font-weight:bold"><span style="font-weight:normal">A Patch is available in ticket [#16697](https://trac.macports.org/ticket/16697) and in the attachments below too.</span></span></span></span></span>
<span style="color:rgb(0,0,0);font-family:Helvetica;font-size:13px"> </span>
<span style="font-family:arial;font-size:13px"><span style="color:rgb(0,0,0)">Changes are minimal:</span></span>
<span style="color:rgb(0,0,0);font-family:arial;font-size:13px">
 </span>
<span style="color:rgb(0,0,0);font-family:arial;font-size:13px"> </span>
<span style="font-family:courier new,monospace"><span style="font-size:small">--- xc/lib/font/fontfile/decompress.c.origin</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">2008-09-29 22:08:09.000000000 +0200</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">+++ xc/lib/font/fontfile/decompress.c</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">2008-09-29 22:06:41.000000000 +0200</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">@@ -77,7 +77,7 @@</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> #include "fontmisc.h"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> #include &lt;bufio.h&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-#ifdef __UNIXOS2__</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">+#if defined(__UNIXOS2__) || defined(__DARWIN__) </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> #include &lt;sys/types.h&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> #endif</span></span>


<span style="font-family:Helvetica;font-size:12px"> </span>
#### Cannot establish any listening sockets
<span style="font-size:13px"><span style="font-family:Arial;font-weight:bold">Problem:</span></span>
<span style="font-size:13px">It fails because missing network support:</span>


[![](../_/rsrc/1222632254842/developers/xorg/XFree86%204.7.0%20on%20puredarwin.png)](xorg/XFree86%204.7.0%20on%20puredarwin.png%3Fattredirects=0)


<span style="font-weight:bold">Solution:</span>

<span style="font-weight:bold"><span style="font-weight:normal">It looks like your system doesn't have a working network.</span></span>

The workaround is simply to add <span style="font-size:13px"><span style="color:rgb(68,68,68);font-size:12px"><span style="color:rgb(0,0,0)">-nolisten tcp</span></span></span>.
T<span style="font-size:12px"><span style="font-family:Arial;font-size:13px"><span style="font-family:Arial">his means that XFree86 will not listen on TCP port 6000. 
</span></span></span>
#### Missing keymap
<span style="font-weight:bold">Problem:</span>
The keymap appears mandatory (no default one embedded, but it looks for USA.keymapping by default).
Also, the option <span style="font-family:courier new,monospace"><span style="font-size:small">-nokeymap</span></span> is still present and working, it makes X to attempt to read keymap from the system but it will fail with a fatal "<span style="font-family:courier new,monospace"><span style="font-size:small">Could not build a valid keymap</span></span>".

<span style="font-family:Arial;font-size:13px">
</span>

<span style="font-family:Helvetica;font-size:13px;font-weight:normal"><span style="font-size:12px"></span></span>

[![](../_/rsrc/1222635272162/developers/xorg/X%20notcp%20on%20puredarwin.png)](xorg/X%20notcp%20on%20puredarwin.png%3Fattredirects=0)


<span style="font-size:13px;font-weight:bold">Solution:</span>

<span style="font-size:13px;font-weight:bold"><span style="font-weight:normal">Download some keymaps from the [XDarwin.org](http://www.xdarwin.org/keymappings/) site and move it into <span style="border-collapse:separate;font-family:Lucida Grande;font-size:12px"><span style="font-style:italic">/System/Library/Keyboards/</span>.</span></span></span>

<span style="font-size:13px;font-weight:bold"><span style="font-weight:normal"><span style="border-collapse:separate;font-family:Lucida Grande;font-size:12px">Or <span style="border-collapse:collapse;font-family:Helvetica;font-size:13px">specify that one of these is used on the command line:</span></span></span></span>

<span style="font-family:courier new">
 </span>

<span style="font-size:13px"><span style="font-family:courier new;font-size:12px">X -keymap <span style="font-weight:bold">USA.keymapping</span></span></span>

<span style="font-family:courier new;font-weight:bold">
</span>

<span style="font-family:arial,sans-serif"><span style="font-size:small">If you plan to use an alternative keymap without specifying it at the command line, you can use a symbolic link:</span></span>

<span style="font-family:arial">
</span>

<span style="font-family:arial"><span style="font-family:courier new">mv /System/Library/Keyboards/USA.keymapping /System/Library/Keyboards/US.keymapping</span></span>

<span style="font-family:courier new">ln -fs /System/Library/Keyboards/Francais.keymapping /System/Library/Keyboards/USA.keymapping</span>

<span style="font-family:courier new">
</span>

<span style="font-family:arial"><span style="text-decoration:underline"><span style="font-size:small">Note:</span></span><span style="font-size:small"> Take a look at  </span><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/X11R6/bin/</span></span>[<span style="font-family:courier new,monospace"><span style="font-size:small">dumpkeymap</span></span>](http://www.xfree86.org/current/dumpkeymap.1.html)<span style="font-size:small">, a diagnostic dump utility suited to keymapping files.</span></span>

<span style="font-family:arial;font-size:13px"><span style="color:rgb(255,0,0);font-family:Arial">Please let us know if you know how to generate a .keymapping file.</span></span>
<span style="font-size:small"> </span>
#### Font-related problem when launching xterm
<span style="font-family:Helvetica;font-size:12px"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="font-family:Arial;font-size:13px;font-weight:bold">Problem:</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">XFree86 Version 4.7.0 / X Window System</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">(protocol Version 11, revision 0)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Release Date: 12 August 2007</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">If the server is older than 6-12 months, or if your hardware is</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">newer than the above date, look for a newer version before</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">reporting problems. (See http://www.XFree86.Org/FAQ)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Operating System: Darwin Apple Computer, Inc.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Using keymapping provided in /USA.keymapping.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Display mode: IOKit</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span>Couldn't set hardware cursor visible with kernel return 0xe00002c7.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Screen 0 added: 800x600 @ (0,0)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)">Could not init font path element /usr/X11R6/lib/X11/fonts/CID/, removing from list!</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)">Fontconfig error: Cannot load default config file</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)">Warning: Cannot convert string "" to type XftFont</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">waiting for X server to shut down Quitting XDarwin...</span></span>
<span style="font-family:Helvetica;font-size:12px;font-weight:normal"><span style="font-family:courier new">X connection to :0.0 broken (explicit kill or server shutdown).</span></span>
<span style="font-family:Helvetica;font-size:12px">
 </span>
<span style="font-family:Helvetica;font-size:12px"><span style="font-weight:bold"><span style="font-size:13px">Pseudo-Solution</span>:</span></span><span style="font-family:Helvetica;font-size:12px;font-weight:normal"> </span>
Create font information cache files:

<span><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/X11R6/bin/fc-cache -v -f /</span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">usr/X11R6/lib/X11/fonts/</span></span></span>
<span style="font-family:courier new"></span>
<span style="color:rgb(153,153,153)">Fontconfig error: Cannot load default config file</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts/": caching, 0 fonts, 11 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//100dpi": caching, 398 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//75dpi": caching, 398 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//CID": caching, 0 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//Speedo": caching, 0 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//TTF": caching, 22 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//Type1": caching, 29 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//cyrillic": caching, 0 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//encodings": caching, 0 fonts, 1 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//encodings/large": caching, 0 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//local": caching, 0 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//misc": caching, 55 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: "/usr/X11R6/lib/X11/fonts//util": caching, 0 fonts, 0 dirs</span>
<span style="color:rgb(153,153,153)">/usr/X11R6/bin/fc-cache: succeeded</span>

<span style="font-family:courier new">
</span>
<span style="text-decoration:underline"><span style="font-size:small">Note:</span></span><span style="font-size:small"> It seems optional.
</span>
#### Failed to connect to the HID system
<span style="font-family:Helvetica;font-size:12px"></span>
<span style="font-family:courier new"><span style="font-family:Arial;font-weight:bold"><span style="font-size:small">Problem:</span></span></span>
<span><span style="font-size:small"><span style="font-family:courier new,monospace">Attempting to use width x height = 800 x 600</span></span></span>

<span style="font-family:courier new,monospace"><span><span style="font-size:small">
</span> </span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">XFree86 Version 4.7.0 / X Window System</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">(protocol Version 11, revision 0)</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Release Date: 12 August 2007</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span><span style="font-size:small"> </span></span></span></span><span style="font-family:courier new,monospace"><span><span style="font-size:small">If the server is older than 6-12 months, or if your hardware is</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span><span style="font-size:small"> </span></span></span></span><span style="font-family:courier new,monospace"><span><span style="font-size:small">newer than the above date, look for a newer version before</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span><span style="font-size:small"> </span></span></span></span><span style="font-family:courier new,monospace"><span><span style="font-size:small">reporting problems. (See http://www.XFree86.Org/FAQ)</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Operating System: Darwin Apple Computer, Inc.</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Using keymapping provided in USA.keymapping.</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Display mode: IOKit</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Couldn't set hardware cursor visible with kernel return 0xe00002c7.</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Screen 0 added: 800x600 @ (0,0)</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Could not init font path element /usr/X11R6/lib/X11/fonts/CID/, removing from list!</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Using keymapping provided in USA.keymapping.</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Display mode: IOKit</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="color:rgb(255,0,0)"><span style="font-size:small">Failed to connect to the HID System as the window server!</span></span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">
</span> </span></span>
<span style="font-family:courier new,monospace"><span><span style="color:rgb(255,0,0)"><span style="font-size:small">Fatal server error:</span></span></span></span>
<span style="font-family:courier new,monospace"><span><span style="color:rgb(255,0,0)"><span style="font-size:small">Make sure you have quit the Mac OS X window server.</span></span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">
</span> </span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small"> OsVendorFatalError</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small"> AbortDDX</span></span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">Quitting XDarwin...</span></span></span>


<span style="font-weight:bold"><span style="font-size:13px">Solution</span>:</span>
<span><span style="font-size:small">Although the default </span></span><span style="font-style:italic"><span><span style="font-size:small">xterm</span></span></span><span><span style="font-size:small"> fails, </span></span><span style="font-style:italic"><span><span style="font-size:small">xterm</span></span></span><span><span style="font-size:small"> and </span></span><span style="font-style:italic"><span><span style="font-size:small">aterm</span></span></span><span><span style="font-size:small"> compiled from MacPorts (and probably </span></span><span style="font-style:italic"><span><span style="font-size:small">Eterm</span></span></span><span><span style="font-size:small"> too) don't.</span></span>

<span><span style="font-size:small">Many "window managers" are linked with </span></span><span><span style="font-size:small">ApplicationServices framework</span></span><span style="font-style:italic"><span><span style="font-size:small">, </span></span></span><span><span style="font-size:small">directly or through their library dependencies, so they won't run.</span></span>
<span style="font-family:Helvetica"><span><span style="font-size:small">Compile FreeType as described above, be sure not to use </span></span><span style="color:rgb(68,68,68);font-family:courier new"><span><span style="font-size:small">--with-old-mac-fonts</span></span><span style="color:rgb(0,0,0);font-family:Helvetica"><span><span style="font-size:small"> but use </span></span></span><span><span style="font-size:small">--without-ats</span></span><span style="color:rgb(0,0,0);font-family:Helvetica"><span><span style="font-size:small">.</span></span></span></span></span>
#### No screens found
<span style="font-family:Helvetica"><span style="font-weight:bold"><span style="font-family:Arial"><span style="font-size:small">Problem</span></span><span style="font-size:small">:</span></span></span>
<span style="font-family:Helvetica"><span style="font-size:small">No screens found</span></span>
<span style="font-family:Helvetica;font-size:12px">
</span>
<span style="font-family:Helvetica"><span style="font-weight:bold"><span style="font-size:small">Solution:</span></span></span>
<span style="font-family:Helvetica"><span style="font-size:small">On VMware, ensure that VMwareIOFramebuffer.kext is loaded.</span></span>
#### assert failed on line 416 of xfIOKit.c!
<span style="font-family:Helvetica"><span style="font-weight:bold">Problem:</span>
A blue frozen screen and the message "assert failed on line 416 of xfIOKit.c!" in the (redirected) &2</span>
<span style="font-family:Helvetica">
</span>
<span style="font-family:Helvetica"><span style="font-weight:bold">Solution:</span></span>
<span style="font-family:Helvetica">Unknown, please let us know.</span>
<span style="font-family:Helvetica"><span style="font-size:small">
</span></span>
<span style="font-family:Helvetica;font-weight:normal"><span style="font-size:small">To be continued...</span></span><span style="font-size:small"> </span>
### Resources
<http://www.xfree86.org/current/Darwin.html> (old)
<http://xonx.sourceforge.net/>
<http://www.xdarwin.org/keymappings/> mirror <http://www.mit.edu/afs/sipb/project/darwin/src/modules/keymaps/keymappings/> 
<http://www.xfree86.org/current/Darwin.pdf> 

