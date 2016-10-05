TODO
====
This page lists (from higher to lower layers, but non exhaustively) some of the areas where work is needed to make Darwin tends to the truly world-class OS it should be.

Would you like to help out with PureDarwin?
Don't know where to start? 


<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:333px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Feedback](todo.html#TOC-Feedback)
    1.  [**1.1** Catalogue compatible hardware](todo.html#TOC-Catalogue-compatible-hardware)
    2.  [**1.2** Test other applications](todo.html#TOC-Test-other-applications)
    3.  [**1.3** Complaints](todo.html#TOC-Complaints)
    4.  [**1.4** Legal aspects](todo.html#TOC-Legal-aspects)
2.  [**2** Packages and binary roots](todo.html#TOC-Packages-and-binary-roots)
    1.  [**2.1** Test available packages](todo.html#TOC-Test-available-packages)
    2.  [**2.2** Build missing packages](todo.html#TOC-Build-missing-packages)
3.  [**3** Device drivers ](todo.html#TOC-Device-drivers-)
    1.  [**3.1** Locate and list available device drivers](todo.html#TOC-Locate-and-list-available-device-drivers)
    2.  [**3.2** Write device drivers](todo.html#TOC-Write-device-drivers)

Feedback
--------
Feedback is "crucial", whatever the form it takes, from the container to the content including the way of sending it.
### Catalogue compatible hardware
If you've got PureDarwin to run somewhere - either in a VM we don't know about, or on a real piece of hardware - then please let us know so that we can add it to our compatible hardware page.
### Test other applications
With the X window system up and running, PureDarwin becomes a very compatible BSD clone, meaning that it should run any of the wide range of software available for that platform. As an example, most of the [pure](developers/macports/purity.html) binaries compiled through [the MacPorts project](developers/macports.1.html) can easily be copied and used into a PureDarwin release. Let us know what you got running.
### Complaints
Truly much appreciated if the critics are a bit (not literally) "constructive".
### Legal aspects
Help us to improve several legal aspects, including non exhaustively how to handle intellectual property, trademarks, patents, copyright and licenses. What to provide? Where? How?

Packages and binary roots
-------------------------
### Test available packages
The basic Darwin system as provided by Apple is made up of over 400 different packages. Many of these have been included in releases of PureDarwin ([Xmas](downloads/xmas.html) and [Nano](downloads/puredarwin-nano.html)). Many more are available from http://src.macosforge.org.
<span style="font-weight:bold">And they all need testing.</span>
We know this method is empiric but we simply need to know what works, and (more importantly) what doesn't, so that we can focus our efforts there.

A particular interest at the moment is per example the high level web application stack: Apache, MySQL, and PHP (or lighttpd, rrdtool and postgresql, etc..). That also could be the other scripting languages as Python, Perl, Ruby... or also some more low level behavior via the use of DTrace per example.
We haven't had a chance to put them through their paces yet, so maybe you could try them and let us know.
### Build missing packages
Not every Darwin project is available as a pre-built binary root. There's a list of these 'missing' packages (about 80 in all) in the svn/hg (under [trunk/projects/PureDarwinPackageDatabase/PackageLists](http://code.google.com/p/puredarwin/source/browse/trunk/projects/PureDarwinPackageDatabase/PackageLists/) in the file [missing.txt](http://code.google.com/p/puredarwin/source/browse/trunk/projects/PureDarwinPackageDatabase/PackageLists/missing.txt)). Some of these are known not to build.
Others are untested. If you succeed in building them, let us know so we can host a copy of the binary root for others and make them available for testing.
Device drivers<span style="font-size:13px;font-weight:normal"> </span>
-----------------------------------------------------------------------
### Locate and list available device drivers
Like all operating systems, Darwin will live or die by its hardware support.
There are a great many IOKit device drivers created by Apple and 3rd parties available.
We first need to collect a list together, so that they can be tested and then bundled with future versions of PureDarwin. 

<span style="text-decoration:underline">Notes:</span> See the [Network](developers/network.html#TOC-Availability-and-investigation) page, the [KEXTs](developers/kexts.html) page, the [Graphics](developers/graphics.html) page, the [Binary drivers](legal/binarydrivers.html) page, the [ZFS](curious/zfs.html) page, etc...
### Write device drivers
This is a crucial mission.
In case the previous item wasn't enough for you! Even pulling together all of the 3rd party drivers available, there will still be plenty of unsupported hardware. And we also have the problem of device drivers which are available in OS X but which haven't been made available for free redistribution in any form by Apple (e.g., the e1000 support via *AppleIntel82454XEthernet* driver springs instantly to mind).
So if you have the skills in this area, why not roll up your sleeves and get stuck in?

