X.Org
=====
<div style="margin:5px 10px;display:inline;float:right">
[![](http://upload.wikimedia.org/wikipedia/commons/thumb/9/90/X.Org_Logo.svg/431px-X.Org_Logo.svg.png)](http://upload.wikimedia.org/wikipedia/commons/thumb/9/90/X.Org_Logo.svg/431px-X.Org_Logo.svg.png)
This page is about X.Org on Darwin.
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** XDarwin](xorg.html#TOC-XDarwin)
2.  [**2** History of X.Org on Darwin](xorg.html#TOC-History-of-X.Org-on-Darwin)
3.  [**3** X.app](xorg.html#TOC-X.app)
4.  [**4** X.Org in MacPorts](xorg.html#TOC-X.Org-in-MacPorts)
5.  [**5** X.Org in fink](xorg.html#TOC-X.Org-in-fink)
6.  [**6** Ressources](xorg.html#TOC-Ressources)


### XDarwin

Update June 2012:
Guillaume Verdeau has released patches to get Xorg running on PureDarwin.
Please see the [announcement](../news/xorgforpuredarwin.html).
The remainder of this page is left here for historical reasons. It needs to be rewritten to reflect the above.
<span style="color:rgb(255,0,0)"><span style="color:rgb(0,0,0)">
</span></span>
### 
### 
### History of X.Org on Darwin
From <http://www.x.org/archive/X11R6.8.0/doc/Darwin2.html>


"<span style="font-style:italic">The X window server for Darwin and Mac OS X provided by the X.Org Foundation. is called XDarwin. (...) XDarwin can also be run from the Darwin console in IOKit mode. (...) From the console, the Darwin port of X11R6.8 uses the IOKit for device driver loading and discovery, rather than the X11R6.8 module loader. Because of this, the X11R6.8 configuration file is not used on Darwin or Mac OS X systems. The descriptions found elsewhere of devices supported by X11R6.8 for other operating systems also do not apply. (...) X11R6.8 for Darwin or Mac OS X will work with any video card that you have an IOKit driver for. (...) If you have a pure Darwin installation, you may need to download additional third-party drivers from Apple's Darwin site. IOKit drivers are typically installed in /System/Library/Extensions/ or /Library/Extensions/.</span>"
### X.app
The X.app that is shipped with Leopard apparently lacks the IOKit mode that would be needed for Darwin, as it apparently only supports the Quartz modes:


<span><span style="font-size:small"><span style="font-family:courier new,monospace">Quartz modes (Experimental / In Development):
 -fullscreen : run full screen in parallel with Mac OS X window server.
 -rootless : run rootless inside Mac OS X window server.</span></span></span>

Is there a way to get the IOKit mode back?
### X.Org in MacPorts
It seems like it needs some work, since all it currently does is <span style="text-decoration:line-through">print the following message:</span> build a version that needs Quartz (which is not available in PureDarwin). The source subdirectory **hw/darwin/iokit** apparently has been removed and needs to be resurrected.
``
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="text-decoration:line-through">---&gt;  Fetching xorg</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="text-decoration:line-through">Error: Target org.macports.fetch returned: </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="text-decoration:line-through">        Hi, my name is xorg, I am broken for the time being, so please do not file a bug for me.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="text-decoration:line-through">        Instead, you can use Apple's X11 that is provided on the OS X install CDs ...</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="text-decoration:line-through">            and also install the X11 SDK from Xcode Tools because they are both required.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="text-decoration:line-through">        There is also a working XFree86 port and ongoing development to port X11R7 to OS X.</span></span></span>
### X.Org in fink
fink (which is basically apt-get for Mac OS X and Darwin) contains two binary packages
-   [xorg-shlibs_6.8.2-1040_darwin-i386.deb](http://bindist.finkmirrors.net/bindist/dists/10.4/current/main/binary-darwin-i386/x11-system/xorg-shlibs_6.8.2-1040_darwin-i386.deb)
-   [xorg_6.8.2-1040_darwin-i386.deb](http://bindist.finkmirrors.net/bindist/dists/10.4/current/main/binary-darwin-i386/x11-system/xorg_6.8.2-1040_darwin-i386.deb)
These can be unpacked to a PureDarwin volume by:
    sudo su
    cd /Volumes/PureDarwin/
    UNP=$(find xorg*_darwin-i386.deb 2>/dev/null) && for UN in $UNP; 
    do ar p $UN data.tar.gz | zcat | tar xv ; done
Then we can try to run them on PureDarwin with
    export PATH=/usr/X11R6/bin:$PATH
    startx
However, it turns out that this links to ApplicationServices which is not a part of Darwin and hence makes these packages worthless for PureDarwin.
<span style="color:rgb(255,0,0)">Please let us know if otherwise!<span style="color:rgb(0,0,0)">
 </span></span>

### Ressources
<http://www.x.org/wiki/> 

