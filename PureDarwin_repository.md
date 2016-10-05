PureDarwin repository
=====================

draft.
The PureDarwin project uses a Mercurial (and used a Subversion) repository (hosted on Google Code) to maintain sources, patches, other code and binary roots that are or that are not part of one of our favorite upstream projects.

This page describes how to use the contents of the repository to build your own PureDarwin ISOs and virtual machines.


<span style="font-family:arial,Verdana,sans-serif">Please [contact us](../contact.html) if you need write access. Everyone who wants to make Darwin more usable is invited.</span>


<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:430px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Basic structure](repository.html#TOC-Basic-structure)
2.  [**2** Usage](repository.html#TOC-Usage)
    1.  [**2.1** Requirements](repository.html#TOC-Requirements)
    2.  [**2.2** Quick steps](repository.html#TOC-Quick-steps)
    3.  [**2.3** Configuration](repository.html#TOC-Configuration)
        1.  [**2.3.1** DARWIN_RELEASE](repository.html#TOC-DARWIN_RELEASE)
        2.  [**2.3.2** ARCH](repository.html#TOC-ARCH)
        3.  [**2.3.3** PUREDARWIN_RELEASE](repository.html#TOC-PUREDARWIN_RELEASE)
        4.  [**2.3.4** BINARYROOTS_LIST_FILE](repository.html#TOC-BINARYROOTS_LIST_FILE)
        5.  [**2.3.5** DARWINBUILD_DIR](repository.html#TOC-DARWINBUILD_DIR)
        6.  [**2.3.6** ADD_CLONE](repository.html#TOC-ADD_CLONE)
    4.  [**2.4** "Genetic" constraints](repository.html#TOC-Genetic-constraints)
        1.  [**2.4.1** Basic overview](repository.html#TOC-Basic-overview)
        2.  [**2.4.2** Zooming chickens and eggs](repository.html#TOC-Zooming-chickens-and-eggs)
3.  [**3** Resources](repository.html#TOC-Resources)

Basic structure
---------------
The current Mercurial repository is composed of the sub repositories.
-   **default**
    The default full release, hosts the setup scripts and settings in order to build a fully PureDarwin release in various form.
    It also contains setup scripts and settings in order to make an Installer (called bootstrap) or a minimalist PureDarwin release (a.k.a. nano) where only one process will run, a shell.
    *http://code.google.com/p/puredarwin/source/browse/*
-   **Roots**
    This repository is dedicated to the hosting of binaryroots (not all of them) from DarwinBuild, MacPorts and PureDarwin.
    It is also used by the default and the nano release.
    Few sources and files have been mirrored inside it too.
    *http://code.google.com/p/puredarwin/source/browse/?repo=roots*
<span style="font-size:small"><span style="font-size:13px">The latest revision of the repository can be browsed at <http://puredarwin.googlecode.com/>.
</span></span>

Usage
-----
### Requirements
The actual state still needs
-   A Mac to create various PureDarwin images.
    However, deploying PureDarwin can be done from PureDarwin ("bootstrap").
    
-   [Mercurial](http://mercurial.selenic.com/wiki/) in order to clone, commit, archive and push fixes, modifications and enhancements to the project.
    We have compiled and packaged Mercurial with (hopefully) all its dependencies, you can download it [here](http://sourceforge.net/projects/puredarwin/files/tools/mercurial-1.4.1.dmg/download) - this package installs it to /opt/local/bin/hg.
    You can also simply build it from MacPorts.
<!-- -->
-   A local copy of the remote PureDarwin repository obtained via
    <span style="font-size:small">hg clone https://puredarwin.googlecode.com/hg/ puredarwin
    </span>
    
    <span style="font-size:13px">See "[Source checkout](http://code.google.com/p/puredarwin/source/checkout)" for more information on Google Code. If you get "*abort: could not import module architecture!*" then you could try the package linked above.</span>
    
Optionally,
-   The DarwinBuild project (in order to deploy your own binaryroots)
-   The MacPorts project
-   Xcode (which is a requirement via transitivity)
### Quick steps
After [cloning of the PureDarwin repository](http://code.google.com/p/puredarwin/source/checkout), the quickest way is to modify <span style="text-decoration:underline">nothing</span> and keep the default configuration ([pd_config](http://code.google.com/p/puredarwin/source/browse/setup/pd_config)).
Simply fetch binaryroots, thin them and build/deploy PureDarwin to the requested target after selection the `setup' folder.
1.  <span style="font-size:small">./pd_fetch</span>
2.  <span style="font-size:small">./pd_thin</span>
3.  <span style="font-size:small">./pd_setup</span> (a usage should display potential choices)
    **Important:** Be aware that a full (non-nano) PureDarwin system currently cannot be run from a read-only disk such as a CD-ROM, DVD, or an ISO file. It needs a r/w hard disk (real hardware) or virtual disk. This might be solved once we go the [Live CD](live-cd.html) way.

[![](../_/rsrc/1260870057546/developers/repository/setup_process_overview.gif)](repository/setup_process_overview.gif%3Fattredirects=0)
### Configuration
In case you decided to edit [pd_config](http://code.google.com/p/puredarwin/source/browse/setup/pd_config) to reflect your needs, keep in mind only few variables need to be edited in the most cases.

All options are not fully yet described here. Please see also the comments inside [pd_config](http://code.google.com/p/puredarwin/source/browse/setup/pd_config).

#### DARWIN_RELEASE
Simply target the Operating System major release version, a.k.a Darwin 9 or Darwin 10.


> <span style="font-family:courier new,monospace;font-size:small">DARWIN_RELEASE="9"</span>
> or
> <span style="font-family:courier new,monospace;font-size:small">DARWIN_RELEASE="10"
> </span>

This variable is used by
-   pd_config
-   pd_fetch
-   pd_thin
-   pd_setup

#### ARCH

Target the architecture.

>  <span style="font-family:courier new,monospace;font-size:small">ARCH="i386"
> 
> </span>
<span style="font-family:courier new,monospace;font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:13px">At this time, only "i386" is supported, but we're convinced that minor efforts (e.g., adapting bootloader steps to different OpenFirmware, adding some needed projects specific/related to the PPC support in "pd_roots", etc...) should be involved in order to bring PPC support in Darwin 9. Idem for "X86_64".</span></span>

Feel free to help us in this quest too.

This variable is used by
-   pd_config
-   pd_thin
-   pd_setup

#### PUREDARWIN_RELEASE
<div style="text-align:auto">
This variable enables a profiling of the release. Depending the value, specific options are enabled or disabled.
<div style="text-align:auto">
<span style="text-decoration:underline">Note:</span> Most of the time, the choice should be "synced" with the<span style="font-family:courier new,monospace;font-size:small"> <span style="font-family:Arial,Verdana,sans-serif;font-size:13px"><span style="font-family:courier new,monospace;font-size:small">BINARYROOTS_LIST_FILE</span> variable.</span></span>
It is possible to override the value of <span style="font-family:courier new,monospace;font-size:small">PUREDARWIN_RELEASE<span style="font-family:Arial,Verdana,sans-serif;font-size:13px"> via exporting it in the environment, prior to the script execution. See this [example](http://code.google.com/p/puredarwin/issues/detail?id=16#c5).</span></span>


> <span style="font-family:courier new,monospace;font-size:small">PUREDARWIN_RELEASE=""</span><span style="font-family:courier new,monospace;font-size:small"> </span>
> or
> <span style="font-family:courier new,monospace;font-size:small">PUREDARWIN_RELEASE="bootstrap"</span>
> <span style="font-family:courier new,monospace;font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:13px">or
> <span style="font-family:courier new,monospace;font-size:small">PUREDARWIN_RELEASE="nano"<span style="color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:13px"><span style="font-family:courier new,monospace;font-size:small">
> </span></span><span style="font-size:13px"><span style="font-size:small">
> </span></span></span></span></span>
This variable is used by
-   pd_setup

#### BINARYROOTS_LIST_FILE
This variable references a file containing the list of binaryroot project names.

By default, the <span style="font-family:courier new,monospace;font-size:small">BINARYROOTS_LIST_FILE</span> variable is automatically set to the corresponding <span style="font-family:courier new,monospace;font-size:small">PUREDARWIN_RELEASE.</span>
<span style="font-size:small">
</span>

<span style="text-decoration:underline">Note:</span> Most of the time, the choice should be "synced" with the<span style="font-family:courier new,monospace;font-size:small"> PUREDARWIN_RELEASE<span style="font-family:Arial,Verdana,sans-serif;font-size:13px"> variable.</span></span>
<div style="display:inline;float:left;margin-top:5px;margin-right:10px;margin-bottom:0px;margin-left:0px">
[![](../_/rsrc/1260870064777/developers/repository/pd_roots_overview.gif)](repository/pd_roots_overview.gif%3Fattredirects=0)
> <span style="font-family:courier new,monospace;font-size:small;color:rgb(153,153,153)">
> </span><span style="font-family:courier new,monospace;font-size:small">
> BINARYROOTS_LIST_FILE="pd_roots" </span>
> or
> <span style="font-family:courier new,monospace;font-size:small">BINARYROOTS_LIST_FILE="pd_roots.bootstrap"</span>
> or
> <span style="font-family:courier new,monospace;font-size:small">BINARYROOTS_LIST_FILE="pd_roots.nano"  </span>
<span style="font-size:small">
</span>
<span style="font-size:small">
</span>
A trivial set theory is visible: "<span style="font-family:arial,sans-serif;font-size:small">pd_roots.nano <span style="font-size:medium">âˆˆ</span> pd_roots.bootstrap <span style="font-size:medium">âˆˆ</span> pd_roots"</span>
The binaryroots in pd_roots.nano also belong to pd_roots.bootstrap and pd_roots sets.
The binaryroots in pd_roots.bootstrap also belong to pd_roots.




This variable is used by:
-   pd_fetch
-   pd_thin
-   pd_setup

#### DARWINBUILD_DIR

Binaryroots built locally via [DarwinBuild](darwinbuild.html) can be used (prior to the one fetched remotely on MacOS Forge in case it has not already been fetched) if <span style="font-size:small">DARWINBUILD_DIR</span> variable is correctly filled in [pd_config](http://code.google.com/p/puredarwin/source/browse/setup/pd_config). However that can also result in one or more conflict between all the dependents and the dependencies living in the system (e.g., missing symbols) if you tend to mix binaryroots built in different BuildRoots.

<span style="font-family:courier new,monospace;font-size:small">#</span>

<span style="font-size:small"># Dir of darwinbuild build directories</span>

<span style="font-size:small">#</span>

<span style="font-size:small"># WARNING: The binaryroots built on your local computer can,</span>
<span style="font-size:small"># depending on the constellation of your buildroot resulting</span>
<span style="font-size:small"># in problematic relation between dependents and dependencies.</span>
<span style="font-size:small">#</span>
<span style="font-size:small"># First Roots/.DownloadCache/ is checked then Packages/ if nothing found</span>
<span style="font-size:small">#DARWINBUILD_DIR="/[...]/darwinbuild"</span>


This variable should points to a directory containing build directories (e.g., 9J61, 9L30, 10C540, etc...).

This variable is used by
-   pd_fetch
-   pd_thin
<span style="text-decoration:underline">Notes:</span> DarwinBuild may access the PureDarwin repository automatically (and/or remotely) if you initialize it with a [Puredarwin plist](http://puredarwin.googlecode.com/hg/trunk/plists).

#### ADD_CLONE
..
### "Genetic" constraints
#### Basic overview
<span style="font-family:courier new,monospace;font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:13px"><span style="font-family:courier new,monospace;font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:13px">Which kind of PureDarwin you will be able to generate from the PureDarwin you generated is conditioned by the couple of (<span style="font-family:courier new,monospace;font-size:small">PUREDARWIN_RELEASE<span style="font-family:Arial,Verdana,sans-serif;font-size:13px">/<span style="font-family:courier new,monospace;font-size:small">BINARYROOTS_LIST_FILE<span style="font-family:Arial,Verdana,sans-serif;font-size:13px">) and </span>ADD_CLONE<span style="font-family:Arial,Verdana,sans-serif;font-size:13px">.</span></span></span></span></span></span></span></span>


[![](../_/rsrc/1260876454164/developers/repository/releases_chicken_egg.gif)](repository/releases_chicken_egg.gif%3Fattredirects=0)

The picture above shows that nothing can be generated from PureDarwin nano.

PureDarwin and PureDarwin bootstrap are able to generate themselves and respectively the other ones.


<span style="text-decoration:underline">Note:</span> Implicitly, that's not (yet) entirely true concerning PureDarwin boostrap.


PureDarwin will contains the same packages (c.f. pd_roots) which have been used to make it in */usr/local/share/puredarwin/*...

PureDarwin bootstrap will contains the same packages (c.f. pd_roots.bootstrap)  which have been used to make it. Because "<span style="font-size:small">pd_roots.nano <span style="font-size:medium">âˆˆ</span> pd_roots.bootstrap <span style="font-size:medium">âˆˆ</span> pd_roots", PureDarwin bootstrap will be only able to generate itself or a PureDarwin nano.</span>

<span style="font-size:small">
</span>

<span style="font-size:small"></span>
[![](../_/rsrc/1263245272700/developers/repository/pd_roots_overview_without_shortcircuiting_arcs.gif)](repository/pd_roots_overview_without_shortcircuiting_arcs.gif%3Fattredirects=0)
#### Zooming chickens and eggs
<span style="font-size:small">This is a more detailled and realistic, where there is (by default) <span style="font-family:Arial,Verdana,sans-serif;font-size:13px">no alteration of the couple of (<span style="font-family:courier new,monospace;font-size:small">PUREDARWIN_RELEASE<span style="font-family:Arial,Verdana,sans-serif;font-size:13px">/<span style="font-family:courier new,monospace;font-size:small">BINARYROOTS_LIST_FILE<span style="font-family:Arial,Verdana,sans-serif;font-size:13px">) and </span>ADD_CLONE<span style="font-family:Arial,Verdana,sans-serif;font-size:13px">.</span></span></span></span></span></span>


<span style="font-size:small">Where obviously everything can be generated from a Mac (green dotted arrow), it's "almost" the contrary a fortiori depending the flavor of PureDarwin.</span>

<span style="font-family:arial,sans-serif;font-size:small">The black arrow represents a successfull deployment.</span>

<span style="font-size:small">A blue dotted arrow shows that the deployment could be successfull if the expected binaryroots are present.</span>

<span style="font-size:small">A red one faces [a blocker](../blockers.html).</span>

<span style="font-size:small">
</span>

<span style="font-size:small"></span>
[![](../_/rsrc/1263244777135/developers/repository/releases_chicken_egg_x2.gif)](repository/releases_chicken_egg_x2.gif%3Fattredirects=0)

Resources
---------
<span style="font-size:20px">**<span style="font-size:13px;font-weight:normal"></span>**</span>
The full chaotic history is available on request.


<http://puredarwin.googlecode.com/> (PureDarwin repository)

<http://mercurial.selenic.com/wiki/> (Mercurial)


<span style="border-collapse:separate;font-family:arial"></span>

