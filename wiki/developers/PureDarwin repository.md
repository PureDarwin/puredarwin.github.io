PureDarwin Repository
=====================


### Note: This document is a draft

The PureDarwin project uses a Mercurial (and used a Subversion) repository (hosted on Google Code) to maintain sources, patches, other code and binary roots that are or that are not part of one of our favorite upstream projects.

This page describes how to use the contents of the repository to build your own PureDarwin ISOs and virtual machines.

**Please [contact us](http://www.puredarwin.org/#contact-us) if you need write access. Everyone who wants to make Darwin more usable is invited.**

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
_The latest revision of the repository can be browsed at http://puredarwin.googlecode.com/._

Usage
-----
### Requirements
The actual state still needs
-   A Mac to create various PureDarwin images.
    However, deploying PureDarwin can be done from PureDarwin ("bootstrap").
    
-   [Mercurial](http://mercurial.selenic.com/wiki/) in order to clone, commit, archive and push fixes, modifications and enhancements to the project.
    We have compiled and packaged Mercurial with (hopefully) all its dependencies, you can download it [here](http://sourceforge.net/projects/puredarwin/files/tools/mercurial-1.4.1.dmg/download), this package installs it to /opt/local/bin/hg.
    Alternatively, you may build it from MacPorts.
-   A local copy of the remote PureDarwin repository obtained via
    `hg clone https://puredarwin.googlecode.com/hg/ puredarwin`
    
    See "[Source checkout](http://code.google.com/p/puredarwin/source/checkout)" for more information on Google Code. If you get "*abort: could not import module architecture!*" then you could try the package linked above.
    
Optionally,
-   The DarwinBuild project (in order to deploy your own binaryroots)
-   The MacPorts project
-   Xcode (which is a requirement via transitivity)
### Quick steps
After [cloning of the PureDarwin repository](http://code.google.com/p/puredarwin/source/checkout), the quickest way is to modify __nothing__ and keep the default configuration ([pd_config](http://code.google.com/p/puredarwin/source/browse/setup/pd_config)).
Simply fetch binaryroots, thin them and build/deploy PureDarwin to the requested target after selection the `setup' folder.
1.  `./pd_fetch`
2.  `./pd_thin`
3.  `./pd_setup` (a usage should display potential choices)
    **Important:** Be aware that a full (non-nano) PureDarwin system currently cannot be run from a read-only disk such as a CD-ROM, DVD, or an ISO file. It needs a r/w hard disk (real hardware) or virtual disk. This might be solved once we go the [Live CD](live-cd.html) way.

!![](/img/developers/repository/setup_process_overview.gif)

### Configuration
In case you decided to edit [pd_config](http://code.google.com/p/puredarwin/source/browse/setup/pd_config) to reflect your needs, keep in mind only few variables need to be edited in the most cases.

All options are not fully yet described here. Please see also the comments inside [pd_config](http://code.google.com/p/puredarwin/source/browse/setup/pd_config).

#### DARWIN_RELEASE
Simply target the Operating System major release version, a.k.a Darwin 9 or Darwin 10.


> `DARWIN_RELEASE="9"`
> or
> `DARWIN_RELEASE="10"`

This variable is used by
-   pd_config
-   pd_fetch
-   pd_thin
-   pd_setup

#### ARCH

Target the architecture.

>  `ARCH="i386"`
At this time, only "i386" is supported, but we're convinced that minor efforts (e.g., adapting bootloader steps to different OpenFirmware, adding some needed projects specific/related to the PPC support in "pd_roots", etc...) should be involved in order to bring PPC support in Darwin 9. Idem for "X86_64".

Feel free to help us in this quest too.

This variable is used by
-   pd_config
-   pd_thin
-   pd_setup

#### PUREDARWIN_RELEASE
This variable enables a profiling of the release. Depending the value, specific options are enabled or disabled.
Note: Most of the time, the choice should be "synced" with the `BINARYROOTS_LIST_FILE` variable.
It is possible to override the value of `PUREDARWIN_RELEASE` via exporting it in the environment, prior to the script execution. See this [example](http://code.google.com/p/puredarwin/issues/detail?id=16#c5k).


> `PUREDARWIN_RELEASE=""`
> or
> `PUREDARWIN_RELEASE="bootstrap"`
> or
> `PUREDARWIN_RELEASE="nano"`
This variable is used by
-   pd_setup

#### BINARYROOTS_LIST_FILE
This variable references a file containing the list of binaryroot project names.

By default, the `BINARYROOTS_LIST_FILE` variable is automatically set to the corresponding `PUREDARWIN_RELEASE.`

**Note: Most of the time, the choice should be "synced" with the `PUREDARWIN_RELEASE` variable.**

![](/img/developers/repository/pd_roots_overview.gif)

> `BINARYROOTS_LIST_FILE="pd_roots"`
> or
> `BINARYROOTS_LIST_FILE="pd_roots.bootstrap"`
> or
> `BINARYROOTS_LIST_FILE="pd_roots.nano"`

A trivial set theory is visible: "`pd_roots.nano`âˆˆ `pd_roots.bootstrap` âˆˆ `pd_roots`"
The binaryroots in pd_roots.nano also belong to pd_roots.bootstrap and pd_roots sets.
The binaryroots in pd_roots.bootstrap also belong to pd_roots.




This variable is used by:
-   pd_fetch
-   pd_thin
-   pd_setup

#### DARWINBUILD_DIR

Binaryroots built locally via [DarwinBuild](darwinbuild.html) can be used (prior to the one fetched remotely on MacOS Forge in case it has not already been fetched) if `DARWINBUILD_DIR` variable is correctly filled in [pd_config](http://code.google.com/p/puredarwin/source/browse/setup/pd_config). However that can also result in one or more conflict between all the dependents and the dependencies living in the system (e.g., missing symbols) if you tend to mix binaryroots built in different BuildRoots.

```
#
# Dir of darwinbuild build directories

#

# WARNING: The binaryroots built on your local computer can,
# depending on the constellation of your buildroot resulting
# in problematic relation between dependents and dependencies.
#
# First Roots/.DownloadCache/ is checked then Packages/ if nothing found
#DARWINBUILD_DIR="/[...]/darwinbuild"
```


This variable should points to a directory containing build directories (e.g., 9J61, 9L30, 10C540, etc...).

This variable is used by
-   pd_fetch
-   pd_thin
**Notes:** DarwinBuild may access the PureDarwin repository automatically (and/or remotely) if you initialize it with a [Puredarwin plist](http://puredarwin.googlecode.com/hg/trunk/plists).

#### ADD_CLONE
..
### "Genetic" constraints
#### Basic overview
Which kind of PureDarwin you will be able to generate from the PureDarwin you generated is conditioned by the couple of (`PUREDARWIN_RELEASE`/`BINARYROOTS_LIST_FILE`) and `ADD_CLONE`.


![](/img/developers/repository/releases_chicken_egg.gif)

The picture above shows that nothing can be generated from PureDarwin nano.

PureDarwin and PureDarwin bootstrap are able to generate themselves and respectively the other ones.


**Note:** Implicitly, that's not (yet) entirely true concerning PureDarwin boostrap.


PureDarwin will contains the same packages (c.f. pd_roots) which have been used to make it in */usr/local/share/puredarwin/*...

PureDarwin bootstrap will contains the same packages (c.f. pd_roots.bootstrap)  which have been used to make it. Because "`pd_roots.nano` âˆˆ `pd_roots.bootstrap` âˆˆ `pd_roots", PureDarwin bootstrap will be only able to generate itself or a PureDarwin nano.</span>


![](/img/developers/repository/pd_roots_overview_without_shortcircuiting_arcs.gif)

#### Zooming chickens and eggs
This is a more detailed and realistic, where there is (by default) no alteration of the couple of (`PUREDARWIN_RELEASE`/`BINARYROOTS_LIST_FILE`) and `ADD_CLONE`.


_Where obviously everything can be generated from a Mac (green dotted arrow), it's "almost" the contrary a fortiori depending the flavor of PureDarwin._

The black arrow represents a successful deployment.

A blue dotted arrow shows that the deployment could be successful if the expected binaryroots are present.

A red one faces [a blocker](../blockers.html).


![](/img/developers/repository/releases_chicken_egg_x2.gif)

Resources
---------

The full chaotic history is available on request.

[PureDarwin Google Code repository](http://puredarwin.googlecode.com/)

[Mercurial](http://mercurial.selenic.com/wiki/)