Using DarwinBuild
=================
<span style="font-size:small"><span>The DarwinBuild project provides an integrated build environment for Darwin projects.</span></span>
<span style="font-size:small"><span>There are [many reasons](http://darwinbuild.macosforge.org/) why you should use DarwinBuild and although some parts of Darwin can be built without DarwinBuild, it is easier with it.</span></span>
<span style="font-size:small"><span>This page describes some ways to use [DarwinBuild](http://darwinbuild.macosforge.org/) in order to build Darwin projects.</span></span>
<span style="font-size:small"><span style="font-weight:bold">It is a work in progess. Please post your comments below or edit this wiki page.</span></span>

<span style="font-size:small">
 </span>
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:350px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Prerequisites](darwinbuild.html#TOC-Prerequisites)
2.  [**2** Terminology](darwinbuild.html#TOC-Terminology)
3.  [**3** Installation](darwinbuild.html#TOC-Installation)
    1.  [**3.1** From SVN](darwinbuild.html#TOC-From-SVN)
        1.  [**3.1.1** Darwin 10](darwinbuild.html#TOC-Darwin-10)
        2.  [**3.1.2** Darwin 9](darwinbuild.html#TOC-Darwin-9)
    2.  [**3.2** From MacPorts](darwinbuild.html#TOC-From-MacPorts)
4.  [**4** Initialize Darwinbuild](darwinbuild.html#TOC-Initialize-Darwinbuild)
    1.  [**4.1** Some part of the environment](darwinbuild.html#TOC-Some-part-of-the-environment)
        1.  [**4.1.1** The BuildRoot directory](darwinbuild.html#TOC-The-BuildRoot-directory)
        2.  [**4.1.2** Logs folder](darwinbuild.html#TOC-Logs-folder)
5.  [**5** Building projects](darwinbuild.html#TOC-Building-projects)
    1.  [**5.1** CoreFoundation as a first test case](darwinbuild.html#TOC-CoreFoundation-as-a-first-test-case)
    2.  [**5.2** xnu](darwinbuild.html#TOC-xnu)
    3.  [**5.3** /XCD/loper](darwinbuild.html#TOC-XCD-loper)
6.  [**6** More cool stuff DarwinBuild can do](darwinbuild.html#TOC-More-cool-stuff-DarwinBuild-can-do)
    1.  [**6.1** darwinxref](darwinbuild.html#TOC-darwinxref)
        1.  [**6.1.1** Listing all the projects for a given branch](darwinbuild.html#TOC-Listing-all-the-projects-for-a-given-branch)
        2.  [**6.1.2** Searching the project of a given file](darwinbuild.html#TOC-Searching-the-project-of-a-given-file)
        3.  [**6.1.3** Building all the projects (brutus way)](darwinbuild.html#TOC-Building-all-the-projects-brutus-way-)
    2.  [**6.2** Package the built binaries](darwinbuild.html#TOC-Package-the-built-binaries)
7.  [**7** Resources](darwinbuild.html#TOC-Resources)
    1.  [**7.1** Deprecated](darwinbuild.html#TOC-Deprecated)
        1.  [**7.1.1** Workaround DarwinBuild ticket #1 (no longer needed)](darwinbuild.html#TOC-Workaround-DarwinBuild-ticket-1-no-longer-needed-)
        2.  [**7.1.2** Populate BuildRoot (no longer needed)](darwinbuild.html#TOC-Populate-BuildRoot-no-longer-needed-)
    2.  [**7.2** Credits](darwinbuild.html#TOC-Credits)

Prerequisites
-------------
<span style="font-size:small">Have a look at <http://darwinbuild.macosforge.org/trac/browser/trunk/README>.</span>
<span style="font-family:inherit"><span style="font-size:small">(to be determined)</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">A Mac with the latest Xcode installed (whether it needs to be an Intel Mac and whether it needs to be (Snow)Leopard is still to be determined)
     (Some projects require Xcode and hence a Mac OS X system to build: those do not use a makefile, but instead a .pbproj or .xcode project file.
    **It is unclear** at this time whether the requirement for a Mac with XCode could also be satisfied using just Darwin and the [XCode sources](http://lists.apple.com/archives/Darwin-dev/2008/Mar/msg00080.html).</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">Subversion available (Leopard comes with it, otherwise use the [binaries from fink](http://pdb.finkproject.org/pdb/package.php/svn-client) or compile sources from [the MacPorts project](http://www.macports.org/))</span></span>
-   <span style="font-size:13px">Some coffee</span>
<span style="font-family:inherit"><span style="font-size:small">If you are using svn from fink, you need to put it in your path by</span></span>
    PATH=/sw/bin:$PATH # If you are using svn from fink
    In case you use MacPorts, your path should already and probably be set to
    export PATH=/opt/local/bin:/opt/local/sbin:$PATH
Terminology
-----------
<span>Since the terminology used by DarwinBuild and PureDarwin is slightly different from what you might know from Linux, it makes sense to look at some commonly used terms now.</span>

  --------------------------------------------------------- ---------------------------------------------- ----------------------------------------------- ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  <span style="font-weight:bold">DarwinBuild term</span>   <span style="font-weight:bold">Approximate    <span style="font-weight:bold">Example</span>   <span style="font-weight:bold">Comments</span>
                                                             Linux equivalent</span>                                                                       
  Project                                                   Upstream project's source code; .orig.tar.gz   bash                                            Most of Apple's own projects are under the APSL, other upstream open source projects have been converted to DarwinBuild projects and are under the respective project's sources
  [xref database](darwinbuild/xref.html)                    Database of the package manager                dpkg, rpm                                       The xref database has (so far) only been used during the build process, but not as a package manager for a running Darwin system. Like package manager databases, the xref database knows about build-time and run-time dependencies
  Roots                                                    Binary packages                                deb                                             Binary roots that contain code for all architectures ("universal/fat binaries") are packed as .tar.gz files, whereas binary roots that contain code for just one architecture ("stripped", e.g., i386) are usually packed as .tar.bz2 files
  binary roots                                                                                                                                             
  BinaryDrivers                                             Closed-source                                 AppleRTC                                        As of May 2008, 6 projects are released by Apple in binary-only form
                                                             binary packages                                                                               
  --------------------------------------------------------- ---------------------------------------------- ----------------------------------------------- ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Installation
------------
### From SVN

Go to the location where you want your DarwinBuild to live.
    sudo su
    mkdir darwinbuild
    cd darwinbuild/
    svn checkout http://svn.macosforge.org/repository/darwinbuild/trunk/
    Darwin 10Now Darwin 10 is out and the Darwinbuild project is targeting different releases via branches, xcodebuild is needed:cd trunk
    xcodebuild install DSTROOT=/[...]=== BUILD AGGREGATE TARGET world OF PROJECT darwinbuild WITH THE DEFAULT CONFIGURATION (Public) ===Check dependencies** BUILD SUCCEEDED **
    A fresh darwinbuild folder is now present: "/usr/local/share/darwinbuild".Darwin 9Before Darwin 10 was released, simply compile DarwinBuild.cd trunk/
    make
    make install
    export PATH=/usr/local/bin:$PATH 
    DarwinBuild should now be installed.
    If you want to update later, back to your svn sources directory:
    cd darwinbuild/trunksvn updateU darwinbuild/installXcode31U plists/9A581.plistUpdated to revision 394.
    Finally,
    make clean && make && make install
### From MacPorts
Simply run:
    port install darwinbuild
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
    In order to upgrade to the latest revision of trunk
    port selfupdate
    port -f upgrade darwinbuild
Initialize Darwinbuild
----------------------
    Some part of the environment
#### The BuildRoot directory
<span style="font-size:13px">This place could also be called the BuildChroot directory, everything fetch or built by darwinbuild will reside inside this directory.</span>
<span style="font-family:inherit"><span style="font-size:small"><span><span style="text-decoration:underline">Notes:</span> The build version "9J61" (2009/05) used below is just an example.
(At the time of this writing, [9F33pd1.plist](http://puredarwin.googlecode.com/svn/trunk/plists/9F33pd1.plist) and [9G55pd1.plist](http://puredarwin.googlecode.com/svn/trunk/plists/9G55pd1.plist) are  recommended, as it includes PureDarwin-specific patches. You can get it from the [PureDarwin SVN repository](http://code.google.com/p/puredarwin/source/browse/trunk/plists/).)</span></span></span>
<span style="font-family:inherit"><span style="font-size:small">Create and select a BuildRoot location hierarchy in the current working directory:</span></span>
    cd /<somewhere>/darwinbuild
    mkdir 9J61
    cd 9J61
    The DarwinBuild ticket#1 workaround (DarwinBuild inherits a bug from Xcode that makes it impossible to use it on a HFS+ volume, the workaround(s) involve(s) setting up NFS locally or using an UFS disk image) is no longer needed since on the Darwinbuild website, we can read (news from 2009/04/17): "The latest revision of trunk has support for sparsebundles and NFS Loopback in order to avoid the problems with xcodebuild inside of chroots. If you do not change the way you use darwinbuild, you will start seeing the sparsebundle storage. Nothing else is needed and Xcode-based projects will build on whatever filesystem you have."darwinbuild -init 9J61 -nfs
    If you want to avoid the use of NFS, the old fashioned method is still available with: darwinbuild -init 9J61 -nodmg
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
    Notes: Keep in mind that/etc/exports must be cleaned sometimes, since there is no concept of "uninitializing" (implicitly removing the added line from /etc/exports). An example of what is added:
    # Added by darwinbuild on 20090523154428
    /Users/aladin/PureDarwin/darwinbuild/9J61/.build/buildroot.nfs -maproot=0:10
    Take a look at http://darwinbuild.macosforge.org/trac/ticket/86 if your /etc/exports grows to fast.
#### Logs folder
Later on, if a project fails to build (and depending your tty), you will want to look into the entire history of build logs.
So simply look into the "<span style="font-style:italic">Logs/&lt;project&gt;/&lt;project&gt;-&lt;version&gt;~&lt;build attempts&gt;</span>" folder for a detailled compilation loh. In this case the "CommonCrypto" project has been successfully built at the first attempt and its log can be found in <span style="font-style:italic">[...]/9J61/Logs/CommonCrypto/CommonCrypto-32207.log~1.</span>
The entire content cannot be pasted here, but most the time, the end crowns with:
<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">** BUILD SUCCEEDED **</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> BUILD TIME: Xh Ym Zs</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">EXIT STATUS: 0</span></span>

With a project which has failed to build, the end can looks like:

<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> BUILD TIME: 0h 0m 0s</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">EXIT STATUS: 2</span></span>


Building projects
-----------------
Before building a project, it is mandatory to initialize again (refresh) the darwinbuild environment. Same apply if the initialized darwinbuild shell session has been closed. After running <span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild -init</span></span> ..., the output should look like for:
-    <span style="font-weight:bold"><span style="font-size:small">darwinbuild -init 9J61</span></span>


> > <span style="font-size:small">Creating build root disk image ...</span><span style="font-size:small">
> > </span><span style="font-size:small">Found 9J61.plist in .build</span><span style="font-size:small">
> > </span><span style="font-size:small">Found 9G55.plist in .build</span><span style="font-size:small">
> > </span><span style="font-size:small">Found 9F33.plist in .build</span><span style="font-size:small">
> > </span><span style="font-size:small">Found 9E17.plist in .build</span><span style="font-size:small">
> > </span><span style="font-size:small">Found 9D34.plist in .build</span><span style="font-size:small">
> > </span><span style="font-size:small">Found 9C31.plist in .build</span><span style="font-size:small">
> > </span><span style="font-size:small">Found 9B18.plist in .build</span><span style="font-size:small">
> > </span><span style="font-size:small">Found 9A581.plist in .build</span><span style="font-size:small">
> > </span><span style="font-size:small">Initialization Complete</span>


-   <span style="font-weight:bold"><span style="font-size:small">darwinbuild -init 9J61 -nfs</span></span>


> > <span style="font-size:small">Adding build root to NFS exports file ...
> > Checking exports file ...
> > Found 9J61.plist in .build
> > Found 9G55.plist in .build
> > Found 9F33.plist in .build
> > Found 9E17.plist in .build
> > Found 9D34.plist in .build
> > Found 9C31.plist in .build
> > Found 9B18.plist in .build
> > Found 9A581.plist in .build
> > Initialization Complete</span>




Ideally, one could transfer the contents of the BuildRoot to a volume, bless it, and boot a fully working Darwin system from it. In fact, it's not so simple.
Whenever you build something using DarwinBuild and don't specifiy otherwise (using <span style="font-family:courier new,monospace"><span style="font-size:small">-nochroot</span></span>), you will be building inside a chrooted environment using the DarwinBuild directory.
    Consequently, your build results, hence, will be "built on Darwin" as opposed to "built on Mac OS X".
    If during the process of downloading you get errors like "ERROR: could not find root: AppleUSBIrDA", this simply means that a binary root of the respective project has not been uploaded to the DarwinBuild server yet.
    (Perhaps it does not build correctly with DarwinBuild yet.)
<span style="font-family:Arial;white-space:normal">The file xref.db contains the [Darwin xref database](darwinbuild/xref.html). It keeps track of the Darwin projects installed in your BuildRoot and their files and version numbers (think of xref roughly as a package manager like "apt" for Darwin binary roots). The xref database has been filled by the <span><span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild -load</span></span></span> command, and will be updated whenever you build something with DarwinBuild.                                                                                                                                                                         </span>
    CoreFoundation as a first test case
<span style="font-family:inherit"><span style="font-size:small">To build a specific package, e.g., CF, type:</span></span>
    darwinbuild CF
<span style="font-family:inherit"><span style="font-size:small">[Troubles with CF building](darwinbuild/troubleshooting.html#TOC-CF-ok-)
</span></span>
<span style="font-family:inherit"><span style="font-size:small">CF is a test case to build. On the first build in the new BuildRoot, DarwinBuild will do some initializations, e.g., copy some header files from the host OS. If it fails, then some prerequisites might be missing or you might need to use <span style="font-family:courier new,monospace">-nochroot</span> (in case not all prerequisites are uploaded to DarwinBuild yet; this would then use the files from the currently running OS rather than from DarwinBuild).</span></span>
If the build succeeds, you should see a <span style="font-weight:bold"><span style="font-weight:normal"><span style="font-style:italic">Roots/CF/CF-476.10.root~1</span></span><span><span style="font-weight:normal"><span style="font-style:italic"> </span></span></span><span style="font-weight:normal">directory containing the files you just built.</span></span>
### xnu
A classic test case is xnu, the kernel.
The command below will fetch and build the xnu project. Before that step, some binaryroots (dependencies of the xnu project. as e.g., libgcc, dylib, developer_cmds, etc..) will be downloaded and loaded into the BuildRoot.
<span style="font-family:courier new,monospace">darwinbuild xnu</span>
If the build succeeds, you can see a <span style="font-style:italic">xnu/xnu-1228.12.14.root~1</span> directory containing the built project. the <span style="font-style:italic">~1</span> stands for the number of time the project has been built.
<span style="font-family:arial,sans-serif">T</span><span style="font-family:arial,sans-serif">h</span><span style="font-family:arial,sans-serif">e</span><span style="font-family:arial,sans-serif">n, in order to populate the BuildRoot dir with the freshly built project:</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild -load xnu
<span style="color:rgb(102,102,102)">Copying xnu from /Volumes/Builds/9J61/Roots/xnu/xnu-1228.12.14.root~1 ...
xnu - 2640 files registered.</span></span></span>
### /XCD/loper {style="margin:10px 10px 10px 0px;background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:18px"}
<span style="font-size:13px;font-weight:normal">You might come across a warning that <span style="font-family:courier new,monospace"><span style="font-size:small">/XCD/loper is missing</span></span>.</span>
<span style="font-size:13px;font-weight:normal">Inside BuildRoot, there should be a directory called <span style="font-style:italic">XCD/</span> which contains Xcode and its dependencies (e.g., Xcode requires a proper CoreFoundation, not CF-Lite).</span>
<span style="font-size:13px;font-weight:normal">Anything under XCD should only link or refer to any other thing in XCD in order to "keep away" Xcode dependencies. If not, there's something wrong.
 The contents of <span style="font-style:italic">XCD/ </span>are copied there from the host system by DarwinBuild's <span style="font-family:courier new,monospace"><span style="font-size:small">installXcode</span></span>.
 This can be invoked manually as well:</span>
<span style="font-size:13px;font-weight:normal">
 <span style="font-family:courier new,monospace"><span style="font-size:small">/usr/local/share/darwinbuild/installXcode</span></span></span>
<span style="font-size:13px;font-weight:normal"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/Developer/darwinbuild/9C31/BuildRoot/ Analyzing Xcode dependencies ...</span></span></span></span>
<span style="font-weight:normal"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Copying Xcode and dependencies ...</span></span></span></span>
<span style="font-size:13px;font-weight:normal"></span>
More cool stuff DarwinBuild can do
----------------------------------
<span style="font-family:inherit"><span style="font-size:small">These need to be documented here</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">buildorder.pl</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">ditto.sh</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">log-index.pl</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">packageRoots.sh</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">thinFile.sh</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">buildlist.sh</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">createChroot</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">darwinmaster.sh</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">installXcodebuild</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">manifest</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">processtrace.sh</span></span>
-   <span style="font-family:inherit"><span style="font-size:small">thinPackages.sh</span></span>
### darwinxref
#### Listing all the projects for a given branch
<span style="font-family:courier new,monospace"><span style="font-size:small">darwinxref -b 9G55 version '*'</span></span>
#### Searching the project of a given file
<span style="font-family:courier new,monospace"><span style="font-size:small">darwinxref findFile launchctl</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">launchd:</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/bin/launchctl</span></span></span>
#### Building all the projects (brutus way)

<span style="font-family:courier new,monospace"><span style="font-size:small">for X in $(darwinxref version '*' | cut -f 1 -d '-'); do </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild $X; done</span></span>
<span style="font-family:courier new">
</span>
<span style="font-family:courier new;font-size:12px"><span style="font-family:Arial;font-size:13px"> </span></span>
<span style="text-decoration:underline">Note:</span> Of course, this doesn't mean all the projects will be compiled.

### Package the built binaries {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:18px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
<span style="font-family:inherit"><span style="font-size:small">Time to package them up!</span></span>
    {DarwinBuild_Checkout_Dir}/packageRoots.sh
    Archive tool: tar (GNU tar) 1.14
    *** Packaging Headers
    *** Packaging Roots
<span style="font-family:inherit"><span><span style="font-family:courier new,monospace"><span style="font-size:small">{DarwinBuild_Checkout_Dir}<span style="font-family:arial,sans-serif"> is your working copy from SVN of DarwinBuild. If you followed the article as suggested at the beginning, it must be located in <span style="font-style:italic">/Developer/darwinbuild/trunk/darwinbuild/</span></span></span></span></span></span>
<span style="font-family:inherit"><span style="font-size:small">We now have a nice Darwin binary root archive in the <span><span style="font-style:italic">Packages/</span></span> directory:</span></span>
    ls Packages/
    CF.root.tar.gz
<span style="font-family:inherit"><span style="font-size:small">Why doesn't it have a version <span style="font-size:12px">number?
</span></span></span>
Resources
---------
### Deprecated
#### Workaround DarwinBuild ticket #1 (no longer needed)
<span style="font-family:inherit"><span style="font-size:small"><span style="font-size:12px">The DarwinBuild ticket#1 workaround is <span style="font-weight:bold">no longer needed</span> since on the [Darwinbuild website](http://darwinbuild.macosforge.org/), we can read (news from 2009/04/17): "<span style="font-style:italic">The latest revision of trunk has support for sparsebundles and NFS Loopback in order to avoid the problems with xcodebuild inside of chroots. If you do not change the way you use darwinbuild, you will start seeing the sparsebundle storage. Nothing else is needed and Xcode-based projects will build on whatever filesyste</span><span style="font-style:italic">m you h<span style="font-style:normal">ave."
Since DarwinBuild currently inherits a bug from Xcode that makes it impossible to use it on a HFS+ volume, we are going to use a workaround that involves setting up NFS locally.<span style="font-family:courier new,monospace">
</span></span></span></span></span></span>
<span style="font-family:inherit"><span style="font-size:small"><span style="font-size:12px"><span style="font-style:italic"><span style="font-style:normal"><span style="font-family:courier new,monospace">sudo su
cat &gt;&gt; /etc/exports &lt;&lt;EOF
/Developer -maproot=root localhost
EOF
nfsd restart
sleep 20
mkdir /DeveloNFS
mount -t nfs localhost:/Developer /DeveloNFS</span>
You should use /DeveloNFS for your DarwinBuild-related work, then you should not encounter [DarwinBuild ticket #1](http://darwinbuild.macosforge.org/trac/ticket/1)
<span style="font-weight:bold">Notes:</span> Using an UFS disk image (a bit deprecated though) is another possible alternative not described here.</span></span></span></span></span>
    Populate BuildRoot (no longer needed)
    Populating the BuildRoot directory via the way below is no longer needed because the dependencies of a project are automatically retrieved and loaded in the BuildRoot.
    Theoretically you could begin building projects with DarwinBuild now. However, this would mean that you would have to build binaries using your host Mac OS X as the build environment (using -nochroot). This would clearly not be ideal, since the resulting binaries would not be guaranteed to run on Darwin. Hence, we want to build Darwin projects using Darwin itself as the build environment ("self-hosted").
    To do this, we use a chroot environment which resides in the BuildRoot directory. We can fill this BuildRoot with all available Darwin binaries using the following command:
    for X in `darwinxref version '*'` ; do darwinbuild -load ${X/-*/} ; done
    This downloads any Darwin components that are available in pre-compiled form (called "binary roots") to Roots/.DownloadCache and installs them into our BuildRoot directory. Since it downloads all available binary roots, it is obviously going to take some time, even on a fast Internet connection.
    The result is an almost-complete Darwin system inside the BuildRoot directory.
    May 27, 2008, a 9C31 Roots/.DownloadCache populated in this way was 714M in size, and the BuildRoot consisted of about 69,000 files taking up 2.21 GB of space.
    September 29, 2008, a 9F33 Roots/.DownloadCache populated was 811M. The BuildRoot took around 2.6GB of disk space.
    February 12, 2009, a 9G55 Roots/.DownloadCache is still at 811M. And the BuildRoot is taking 4.5G of space.
    May 25, 2009, a 9J61/ seems to need more than 11G (related to svk infinite loop) and fools nicely (4Ti !!!) `df' available space: /dev/disk1s2    11Gi   11Gi  4.0Ti     1%    /Volumes/Builds
    As of June 13, 2009, situation fixed and more than the half of the projects are built and packaged.
    Help and further reading
<span style="font-family:inherit"><span style="font-size:small"><http://darwinbuild.macosforge.org/> The DarwinBuild Project
 <http://darwinbuild.macosforge.org/trac/browser/trunk/README> </span></span>
<span style="font-family:inherit"><span style="font-size:small">[Archives](http://lists.macosforge.org/pipermail/darwinbuild-dev/) darwinbuild-dev mailing list at lists.macosforge.org</span></span>
### Credits
<span style="font-size:small">Credits go to kvv and _wms for their work on DarwinBuild and for their excellent online support. 
 This page was started by probono in the spirit of the </span>[<span style="font-family:inherit"><span style="font-size:small">DarwinBuild newbie guide</span></span>](http://lists.apple.com/archives/darwin-dev/2006/Nov/msg00000.html "http://lists.apple.com/archives/darwin-dev/2006/Nov/msg00000.html")<span style="font-family:inherit"><span style="font-size:small"> by Craig Harman, but specifically covers Darwin versions starting with 9.</span></span>


