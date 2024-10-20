Using DarwinBuild
=================
The DarwinBuild project provides an integrated build environment for Darwin projects.
There are [many reasons](http://darwinbuild.macosforge.org/) why you should use DarwinBuild and although some parts of Darwin can be built without DarwinBuild, it is easier with it.
This page describes some ways to use [DarwinBuild](http://darwinbuild.macosforge.org/) in order to build Darwin projects.
It is a work in progress. Please post your comments below or edit this wiki page.

Prerequisites
-------------
Have a look at
(to be determined)
-   A Mac with the latest Xcode installed (whether it needs to be an Intel Mac and whether it needs to be (Snow) Leopard is still to be determined).  
    (Some projects require Xcode and hence a Mac OS X system to build: those do not use a makefile, but instead a .pbproj or .xcode project file.  
    **It is unclear** at this time whether the requirement for a Mac with Xcode could also be satisfied using just Darwin and the [Xcode sources](http://lists.apple.com/archives/darwin-dev/2008/Mar/msg00080.html).
-   Subversion available (Leopard comes with it, otherwise use the [binaries from fink](http://pdb.finkproject.org/pdb/package.php/svn-client) or compile sources from [the MacPorts project](http://www.macports.org/))
-   Some coffee

If you are using svn from fink, you need to put it in your path by
```bash
PATH=/sw/bin:$PATH # If you are using svn from fink
```

In case you use MacPorts, your path should already and probably be set to

```bash
export PATH=/opt/local/bin:/opt/local/sbin:$PATH
```

Terminology
-----------

Since the terminology used by DarwinBuild and PureDarwin is slightly different from what you might know from Linux, it makes sense to look at some commonly used terms now.



## Project

Upstream project's source code; .orig.tar.gz

#### Example

bash *(as a project not command)*

##### Comments

Most of Apple's own projects are under the APSL, other upstream open source projects have been converted to DarwinBuild projects and are under the respective project's sources

### [xref database](https://web.archive.org/web/20160826114642/http://www.puredarwin.org/developers/darwinbuild/xref)

Database of the package manager

#### Example

dpkg, rpm

#### Comments

The xref database has (so far) only been used during the build process, but not as a package manager for a running Darwin system. Like package manager databases, the xref database knows about build-time and run-time dependencies

### Roots

binary roots

#### Example

Binary packages (.deb, .rpm)

#### Comments

Binary roots that contain code for all architectures ("universal/fat binaries") are packed as .tar.gz files, whereas binary roots that contain code for just one architecture ("stripped", e.g., i386) are usually packed as .tar.bz2 files 

### BinaryDrivers

Closed-source binary packages

#### Example

AppleRTC

#### Comments

As of May 2008, 6 projects are released by Apple in binary-only form.

Development on macosforge's darwinbuild seem stopped on github, and subversion repository seems to be offline. Use the git repo bellow for now.

Installation
------------

### From Git

```
git clone https://github.com/PureDarwin/darwinbuild.git
```

### Generic Instructions (after getting darwinbuild source)

Change directory to ensure you are in darwinbuild (if not already)

```
cd darwinbuild
xcodebuild install DSTROOT=/
```

A fresh darwinbuild folder is now present: "/usr/local/share/darwinbuild".


### From MacPorts

Simply run:
`% port install darwinbuild`

Output:
```
    ---> Computing dependencies for darwinbuild
    ---> Fetching darwinbuild
    ---> Verifying checksum(s) for darwinbuild
    ---> Extracting darwinbuild
    ---> Configuring darwinbuild
    ---> Building darwinbuild
    ---> Staging darwinbuild into destroot
    ---> Installing darwinbuild @0.8.0_508
    ---> Activating darwinbuild @0.8.0_508
    ---> Cleaning darwinbuild
```

In order to upgrade to the latest revision of trunk:
```
    % port selfupdate
    % port -f upgrade darwinbuild
```

Initialize Darwinbuild
----------------------

### Some part of the environment

#### The BuildRoot directory

This place could also be called the BuildChroot directory, everything fetch or built by darwinbuild will reside inside this directory.

Notes: The build version "9J61" (2009/05) used below is just an example.

(At the time of this writing, [9F33pd1.plist](https://github.com/PureDarwin/PureDarwin/blob/master/plists/9F33pd1.plist) and [9G55pd1.plist](https://github.com/PureDarwin/PureDarwin/blob/master/plists/9G55pd1.plist) are recommended, as it includes PureDarwin-specific patches. You can get them from the [PureDarwin repository](https://github.com/PureDarwin/PureDarwin/tree/master/plists/).)

Create and select a BuildRoot location hierarchy in the current working directory:
```
cd //darwinbuild
mkdir 9J61
cd 9J61
```

The DarwinBuild ticket#1 workaround (DarwinBuild inherits a bug from Xcode that makes it impossible to use it on a HFS+ volume, the workaround(s) involve(s) setting up NFS locally or using an UFS disk image) is no longer needed since on the Darwinbuild website, we can read (news from 2009/04/17): "The latest revision of trunk has support for sparsebundles and NFS Loopback in order to avoid the problems with xcodebuild inside of chroots. If you do not change the way you use darwinbuild, you will start seeing the sparsebundle storage. Nothing else is needed and Xcode-based projects will build on whatever filesystem you have."


    darwinbuild -init 9J61 -nfs

If you want to avoid the use of NFS, the old fashioned method is still available with: darwinbuild -init 9J61 -nodmg
The command above should download the .plist files (it will run nfsd if it is not yet the case and will mount the build root over NFS loopback when a project will be built) from the darwinbuild website and give:

    Adding build root to NFS exports file ...
    nfsd: nfsd not running?
    Checking exports file ...
    Downloading http://svn.macosforge.org/repository/darwinbuild/trunk/plists//9J61.plist ...
    Download complete
    Downloading http://svn.macosforge.org/repository/darwinbuild/trunk/plists//9G55.plist ...
    Download complete
    Downloading http://svn.macosforge.org/repository/darwinbuild/trunk/plists//9F33.plist ...
    Download complete
    Downloading http://svn.macosforge.org/repository/darwinbuild/trunk/plists//9E17.plist ...
    Download complete
    Downloading http://svn.macosforge.org/repository/darwinbuild/trunk/plists//9D34.plist ...
    Download complete
    Downloading http://svn.macosforge.org/repository/darwinbuild/trunk/plists//9C31.plist ...
    Download complete
    Downloading http://svn.macosforge.org/repository/darwinbuild/trunk/plists//9B18.plist ...
    Download complete
    Downloading http://svn.macosforge.org/repository/darwinbuild/trunk/plists//9A581.plist ...
    Download complete
    Initialization Complete

If you get ".build/9F33.plist: No such file or directory", it can be necessary to repeat this step.
As a result, you should now have inside the current working directory:

    ./.build
    ./.build/9A581.plist
    ./.build/9B18.plist
    ./.build/9C31.plist
    ./.build/9D34.plist
    ./.build/9E17.plist
    ./.build/9F33.plist
    ./.build/9G55.plist
    ./.build/9J61.plist
    ./.build/build
    ./.build/buildroot.nfs
    ./.build/xref.db
    ./Headers
    ./Logs
    ./Roots
    ./Sources
    ./Symbols

 Whenever there are new Darwin projects or versions, you should do darwinbuild -init again in order to refresh the .plist files (think of it as "apt-get update" for Darwin source projects).  
Notes: Keep in mind that/etc/exports must be cleaned sometimes, since there is no concept of "uninitializing" (implicitly removing the added line from /etc/exports). An example of what is added:

    # Added by darwinbuild on 20090523154428
    /Users/aladin/PureDarwin/darwinbuild/9J61/.build/buildroot.nfs -maproot=0:10

Take a look at http://darwinbuild.macosforge.org/trac/ticket/86 if your /etc/exports grows to fast.


#### Logs folder

Later on, if a project fails to build (and depending your tty), you will want to look into the entire history of build logs.
So simply look into the "Logs/<project>/<project>-<version>~<build attempts>" folder for a detailled compilation loh. In this case the "CommonCrypto" project has been successfully built at the first attempt and its log can be found in [...]/9J61/Logs/CommonCrypto/CommonCrypto-32207.log~1.
The entire content cannot be pasted here, but most the time, the end crowns with:

```
[...]

** BUILD SUCCEEDED **
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 BUILD TIME: Xh Ym Zs
EXIT STATUS: 0

With a project which has failed to build, the end can looks like:

[...]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 BUILD TIME: 0h 0m 0s
EXIT STATUS: 2
```

Building projects
-----------------

Before building a project, it is mandatory to initialize again (refresh) the darwinbuild environment. Same apply if the initialized darwinbuild shell session has been closed. After running `darwinbuild -init ...`, the output should look like for:
```
$ darwinbuild -init 9J61


> > Creating build root disk image ...
> > Found 9J61.plist in .build
> > Found 9G55.plist in .build
> > Found 9F33.plist in .build
> > Found 9E17.plist in .build
> > Found 9D34.plist in .build
> > Found 9C31.plist in .build
> > Found 9B18.plist in .build
> > Found 9A581.plist in .build
> > Initialization Complete


$ darwinbuild -init 9J61 -nfs


> > Adding build root to NFS exports file ...
> > Checking exports file ...
> > Found 9J61.plist in .build
> > Found 9G55.plist in .build
> > Found 9F33.plist in .build
> > Found 9E17.plist in .build
> > Found 9D34.plist in .build
> > Found 9C31.plist in .build
> > Found 9B18.plist in .build
> > Found 9A581.plist in .build
> > Initialization Complete
```



Ideally, one could transfer the contents of the BuildRoot to a volume, bless it, and boot a fully working Darwin system from it. In fact, it's not so simple.  
Whenever you build something using DarwinBuild and don't specifiy otherwise (using -nochroot), you will be building inside a chrooted environment using the DarwinBuild directory.  
    Consequently, your build results, hence, will be "built on Darwin" as opposed to "built on Mac OS X".  
    If during the process of downloading you get errors like "ERROR: could not find root: AppleUSBIrDA", this simply means that a binary root of the respective project has not been uploaded to the DarwinBuild server yet.  
    (Perhaps it does not build correctly with DarwinBuild yet.)  
The file xref.db contains the [Darwin xref database](darwinbuild/xref.html). It keeps track of the Darwin projects installed in your BuildRoot and their files and version numbers (think of xref roughly as a package manager like "apt" for Darwin binary roots). The xref database has been filled by the darwinbuild -load command, and will be updated whenever you build something with DarwinBuild.                                                                                                                                      

#### CoreFoundation as a first test case

To build a specific package, e.g., CF, type:
```
$ darwinbuild CF
```

[Troubles with CF building](darwinbuild/troubleshooting.html#TOC-CF-ok-)

CF is a test case to build. On the first build in the new BuildRoot, DarwinBuild will do some initializations, e.g., copy some header files from the host OS. If it fails, then some prerequisites might be missing or you might need to use -nochroot (in case not all prerequisites are uploaded to DarwinBuild yet; this would then use the files from the currently running OS rather than from DarwinBuild).
If the build succeeds, you should see a Roots/CF/CF-476.10.root~1 directory containing the files you just built.

### xnu

A classic test case is xnu, the kernel.
The command below will fetch and build the xnu project. Before that step, some binaryroots (dependencies of the xnu project. as e.g., libgcc, dylib, developer_cmds, etc..) will be downloaded and loaded into the BuildRoot.
```
$ darwinbuild xnu
```
If the build succeeds, you can see a xnu/xnu-1228.12.14.root~1 directory containing the built project. The ~1 stands for the number of time the project has been built.
Then, in order to populate the BuildRoot dir with the freshly built project:

```
$ darwinbuild -load xnu
Copying xnu from /Volumes/Builds/9J61/Roots/xnu/xnu-1228.12.14.root~1 ...
xnu - 2640 files registered.
```

### /XCD/loper

You might come across a warning that /XCD/loper is missing.
Inside BuildRoot, there should be a directory called XCD/ which contains Xcode and its dependencies (e.g., Xcode requires a proper CoreFoundation, not CF-Lite).
Anything under XCD should only link or refer to any other thing in XCD in order to "keep away" Xcode dependencies. If not, there's something wrong.
 The contents of XCD/ are copied there from the host system by DarwinBuild's installXcode.
 This can be invoked manually as well:

 /usr/local/share/darwinbuild/installXcode
/Developer/darwinbuild/9C31/BuildRoot/ Analyzing Xcode dependencies ...
Copying Xcode and dependencies ...


More cool stuff DarwinBuild can do
----------------------------------

These need to be documented here
-   buildorder.pl
-   ditto.sh
-   log-index.pl
-   packageRoots.sh
-   thinFile.sh
-   buildlist.sh
-   createChroot
-   darwinmaster.sh
-   installXcodebuild
-   manifest
-   processtrace.sh
-   thinPackages.sh

### darwinxref

#### Listing all the projects for a given branch

```
darwinxref -b 9G55 version '*'
```

#### Searching the project of a given file

```
darwinxref findFile launchctl
launchd:
 /bin/launchctl
```

#### Building all the projects (brutus way)

```
for X in $(darwinxref version '*' | cut -f 1 -d '-'); do darwinbuild $X; done
```

 
Note: Of course, this doesn't mean all the projects will be compiled.

### Package the built binaries

Time to package them up!

    {DarwinBuild_Checkout_Dir}/packageRoots.sh
    Archive tool: tar (GNU tar) 1.14
    *** Packaging Headers
    *** Packaging Roots

`{DarwinBuild_Checkout_Dir}` is your working copy from SVN of DarwinBuild. If you followed the article as suggested at the beginning, it must be located in /Developer/darwinbuild/trunk/darwinbuild/.  
We now have a nice Darwin binary root archive in the Packages/ directory:

    ls Packages/
    CF.root.tar.gz
    
Why doesn't it have a version number?

Resources
---------

### Deprecated

#### Workaround DarwinBuild ticket #1 (no longer needed)

The DarwinBuild ticket#1 workaround is no longer needed since on the [Darwinbuild website](http://darwinbuild.macosforge.org/), we can read (news from 2009/04/17): "The latest revision of trunk has support for sparsebundles and NFS Loopback in order to avoid the problems with xcodebuild inside of chroots. If you do not change the way you use darwinbuild, you will start seeing the sparsebundle storage. Nothing else is needed and Xcode-based projects will build on whatever filesystem you have."
Since DarwinBuild currently inherits a bug from Xcode that makes it impossible to use it on a HFS+ volume, we are going to use a workaround that involves setting up NFS locally.

```
sudo su
cat >> /etc/exports <<EOF
/Developer -maproot=root localhost
EOF
nfsd restart
sleep 20
mkdir /DeveloNFS
mount -t nfs localhost:/Developer /DeveloNFS
```

You should use /DeveloNFS for your DarwinBuild-related work, then you should not encounter [DarwinBuild ticket #1](http://darwinbuild.macosforge.org/trac/ticket/1).  
Notes: Using an UFS disk image (a bit deprecated though) is another possible alternative not described here.
    
#### Populate BuildRoot (no longer needed)

Populating the BuildRoot directory via the way below is no longer needed because the dependencies of a project are automatically retrieved and loaded in the BuildRoot.  
Theoretically you could begin building projects with DarwinBuild now. However, this would mean that you would have to build binaries using your host Mac OS X as the build environment (using -nochroot). This would clearly not be ideal, since the resulting binaries would not be guaranteed to run on Darwin. Hence, we want to build Darwin projects using Darwin itself as the build environment ("self-hosted").  
To do this, we use a chroot environment which resides in the BuildRoot directory. We can fill this BuildRoot with all available Darwin binaries using the following command:  
```
for X in `darwinxref version '*'` ; do darwinbuild -load ${X/-*/} ; done
```
This downloads any Darwin components that are available in pre-compiled form (called "binary roots") to Roots/.DownloadCache and installs them into our BuildRoot directory. Since it downloads all available binary roots, it is obviously going to take some time, even on a fast Internet connection.  
The result is an almost-complete Darwin system inside the BuildRoot directory.  
 - May 27, 2008, a 9C31 Roots/.DownloadCache populated in this way was 714M in size, and the BuildRoot consisted of about 69,000 files taking up 2.21 GB of space.
 - September 29, 2008, a 9F33 Roots/.DownloadCache populated was 811M. The BuildRoot took around 2.6GB of disk space.
 - February 12, 2009, a 9G55 Roots/.DownloadCache is still at 811M. And the BuildRoot is taking 4.5G of space.
 - May 25, 2009, a 9J61/ seems to need more than 11G (related to svk infinite loop) and fools nicely (4Ti !!!) `df' available space: /dev/disk1s2    11Gi   11Gi  4.0Ti     1%    /Volumes/Builds
 - As of June 13, 2009, situation fixed and more than the half of the projects are built and packaged.

### Help and further reading
The DarwinBuild Project [Archives](http://lists.macosforge.org/pipermail/darwinbuild-dev/) (darwinbuild-dev mailing list at lists.macosforge.org)

### Credits

Credits go to kvv and _wms for their work on DarwinBuild and for their excellent online support.   
This page was started by probono in the spirit of the [DarwinBuild newbie guide](http://lists.apple.com/archives/darwin-dev/2006/Nov/msg00000.html "http://lists.apple.com/archives/darwin-dev/2006/Nov/msg00000.html") by Craig Harman, but specifically covers Darwin versions starting with 9.