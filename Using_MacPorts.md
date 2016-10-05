Using MacPorts
==============
<div style="margin:5px 10px;display:inline;float:right">
[![](../_/rsrc/1222694606788/developers/macports/macports-logo-top.png)](http://www.puredarwin.org/developers/goog_1222698405894)
[MacPorts](http://www.macports.org/), formerly known as DarwinPorts, is a variant of the BSD ports system for Darwin and Mac OS X.
This page describes how to use MacPorts to create binary packages that can be deployed to PureDarwin. <span style="text-decoration:line-through">At a later time, we might try to get</span> We now have [MacPorts running on PureDarwin](macports/macportsonpuredarwin.html) itself. Deploying MacPorts on a PureDarwin system and building binaries there is preferable, since you will save a lot of hassle.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:360px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Prerequisites](macports.1.html#TOC-Prerequisites)
2.  [**2** Installation](macports.1.html#TOC-Installation)
3.  [**3** Configuration](macports.1.html#TOC-Configuration)
4.  [**4** Use](macports.1.html#TOC-Use)
    1.  [**4.1** Searching for a port](macports.1.html#TOC-Searching-for-a-port)
    2.  [**4.2** Getting information about a port found](macports.1.html#TOC-Getting-information-about-a-port-found)
    3.  [**4.3** Building a port](macports.1.html#TOC-Building-a-port)
    4.  [**4.4** +puredarwin variant](macports.1.html#TOC-puredarwin-variant)
    5.  [**4.5** Purity checking](macports.1.html#TOC-Purity-checking)
    6.  [**4.6** Updating MacPorts](macports.1.html#TOC-Updating-MacPorts)
    7.  [**4.7** Upgrading deprecated port(s)](macports.1.html#TOC-Upgrading-deprecated-port-s-)
    8.  [**4.8** Cleaning MacPorts](macports.1.html#TOC-Cleaning-MacPorts)
    9.  [**4.9** Removing inactive port(s)](macports.1.html#TOC-Removing-inactive-port-s-)
5.  [**5** Troubleshooting](macports.1.html#TOC-Troubleshooting)
6.  [**6** Credits](macports.1.html#TOC-Credits)
7.  [**7** Resources](macports.1.html#TOC-Resources)


### Prerequisites
For MacPorts, you need
-   An Intel-based Macintosh with Max OS X 10.5 Leopard (latest version)
-   Xcode Tools
-   X11 (optional?)
The actual requirement might be less than that, but this is the configuration currently tested and used by us.
At a later time, we might attempt to use MacPorts on the PureDarwin system itself, but at this time our approach is to build binaries using MacPorts on the Mac and deploy these to PureDarwin.
### Installation
On the Mac, simply download and install the latest MacPorts dmg from the [MacPorts download page](http://www.macports.org/install.php).
It will install the MacPorts system under */opt/local/*.
Instead of using binary, you can also compile tarball or svn source.
See the [MacPorts download page](http://www.macports.org/install.php) for more information about how to get more information around installing MacPorts.
### Configuration
Since we would like MacPorts to create binary packages of the software that we build with it that can then be deployed to PureDarwin systems, we must enable the archive mode.
For that, edit the file */opt/local/etc/macports/macports.conf* so that it contains:


<span style="font-family:courier new,monospace"><span style="font-size:small"># Create and use binary archive packages for installation/reinstallation ease </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">portarchivemode         </span></span><span style="font-weight:bold"><span style="font-family:courier new,monospace"><span style="font-size:small">yes</span></span></span>
<span style="font-family:courier new;font-weight:bold">
</span>
Since we are using .tbz2 files as thinned DarwinBuild binary roots, we'd like to create the same type of packages with MacPorts too:


<span style="font-family:courier new,monospace"><span style="font-size:small"># Supported types: tgz (default), tar, tbz, tbz2, tlz, xar, zip, cpgz, cpio</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">portarchivetype         </span></span><span style="font-weight:bold"><span style="font-family:courier new,monospace"><span style="font-size:small">tbz2</span></span></span>


MacPorts is now configured to create binary archives in the tbz2 format.

**Important:** Since Snow Leopard/Darwin 10, you need to explicitly set the architecture to i386 or you will get binaries that don't run on 32-bit only CPUs. The PureDarwin project is about building i386 binaries, so please make sure that you have the following in your */opt/local/etc/macports/macports.conf*:


<span style="font-size:small"># The machine architecture to build for in normal use.</span>
<span style="font-size:small">build_arch</span><span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">i386</span>

Otherwise, you'll get 64-bit binaries that are incompatible with 32-bit only CPUs, such as Intel Core Solo, Core Duo and Atom CPUs.

### Use
#### Searching for a port
<span style="font-family:courier new,monospace">sudo port search xfree86</span>
#### Getting information about a port found
Remember you must match the exact port name (no sensitive case).
This is usefull to know which variants are available and which wants you would like in case
<span style="color:rgb(0,0,0)"><span style="font-family:courier new,monospace"><span style="font-size:small">sudo port info xfree86</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span><span style="color:rgb(68,68,68)"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">XFree86 @4.7.0 (x11)</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">Variants:    darwin, macosx, puredarwin</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">The XFree86 project's X window system implementation</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Homepage:    http://www.xfree86.org/</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Platforms:            darwin, freebsd</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Maintainers:          nomaintainer@macports.org</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>

<span><span style="font-family:courier new,monospace"><span style="font-size:small">Maintainers: nomaintainer@macports.org</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
#### Building a port
To build XFree86, for example, use:

<span style="font-family:courier new,monospace"><span style="font-size:small">sudo port -d archive xfree86 +puredarwin</span></span>

This is just an example. If you really want to build XFree86, see the [XFree86](xfree86.html) page for additional information.
This should download, compile, and after a while return
 
<span style="font-family:courier new,monospace"><span style="font-size:small">---&gt;  Archive XFree86-4.7.0_0+macosx+puredarwin.i386.tbz2 packaged</span></span>

The resulting package should be located at */opt/local/var/macports/packages/darwin/i386/XFree86-4.7.0_0+macosx+puredarwin.i386.tbz2* and should be ready for deployment to a PureDarwin system.
#### +puredarwin variant
MacPorts includes various build targets or "variants". Here is a quick, approximate overview:


[![](../_/rsrc/1223575691028/developers/macports/Bild%208.png)](macports/Bild%208.png%3Fattredirects=0)


Maybe you noticed the "+puredarwin" build target in the command above. Note that "+darwin" is a superset of both "+puredarwin" and "+macosx", so binaries made using the "+darwin" variant will in many cases <span style="font-weight:bold">not</span> run on PureDarwin. 

It is probably fair to say that the "+puredarwin" variant in MacPorts is the most appropriate variant if you are targeting the PureDarwin distribution. 
This build target may be defined in the portfile of the respective project that you are building.

Talking about variants, use <span style="font-family:courier new;font-size:12px">sudo port variants XFree86 </span>in order to list them and their respective description.
The raw content of a portfile can be displayed via <span style="font-family:courier new;font-size:12px">sudo port cat XFree86</span> command.
The portfile of XFree86,* /opt/local/var/macports/sources/rsync.macports.org/release/ports/x11/XFree86/Portfile*, defines:


<span style="font-family:courier new,monospace"><span style="font-size:small">platform puredarwin {</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    post-patch {  </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        set hostfd [open "${worksrcpath}/config/cf/host.def" a+]</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        puts $hostfd "#define DarwinQuartzSupport NO"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        puts $hostfd "#define BuildGlxExt         YES"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        puts $hostfd "#define BuildGLXLibrary     YES"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">        close $hostfd</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    }</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">}</span></span>

Other projects might or might not need and/or have a "+puredarwin" variant.
If they need but lack one, please consider submitting patches for the respective portfiles.
To see which projects already have a puredarwin variant, click [here](http://www.macports.org/ports.php?by=variant&substr=puredarwin).

Probably you want to set MacPorts to always use the +puredarwin variant, if possible.
Do that by adding "+puredarwin" to variants.conf:
<span style="border-collapse:separate">
</span>
<span style="border-collapse:separate;font-weight:bold"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="font-weight:normal">echo "+puredarwin" &gt;&gt; /opt/local/etc/macports/variants.conf</span></span></span></span>
<span style="border-collapse:separate;font-weight:bold"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="font-weight:normal">echo "-macosx" &gt;&gt; /opt/local/etc/macports/variants.conf</span></span></span></span>
#### Purity checking
<span style="border-collapse:separate;font-weight:bold"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="font-weight:normal"><span style="border-collapse:collapse;font-family:Arial;font-size:13px">It is crucial that you [check the build results for "purity"](macports/purity.html).</span></span></span></span></span>
#### Updating MacPorts
Do not hesitate to "cron" it.
Also run it after your first installation of MacPorts.
<span style="font-family:courier new,monospace">sudo port selfupdate</span>
After a "selfupdate", you can also list outdated port(s) (in version) with:
<span style="font-family:courier new,monospace">sudo port outdated</span>
#### Upgrading deprecated port(s)
In order to upgrade a specific port, use:
<span style="font-family:courier new,monospace">sudo port upgrade XFree86</span>
If you want to upgrade all deprecated ports found since the latest selfupdate:
<span style="font-family:courier new,monospace">sudo port upgrade outdated</span>
#### Cleaning MacPorts
In order to clean a specific port, use:
<span style="font-family:courier new,monospace">sudo port clean XFree86</span>
If you want to clean all ports:
<span style="font-family:courier new,monospace">port clean all</span>
#### Removing inactive port(s)
<span style="font-family:courier new,monospace"><span style="font-size:small">port -f uninstall inactive<span style="font-family:Arial;font-size:13px"><span style="font-family:Arial;font-size:13px">
</span></span></span></span>
### Troubleshooting
<span style="font-weight:bold">Problem (1.6.0):</span> port rpm cairo +puredarwin -macosx returns
Error: Unable to execute port: invalid command name "univers...
<span style="font-weight:bold">Solution:</span> Apply the patch below

### Credits
Thanks afb for lots of help with MacPorts and for the portmain.tcl patch below.
### Resources
[MacPorts.org](http://www.macports.org/)
[man port](macports/port.html)
