PureFoundation
==============
This page is about the use of PureFoundation on Darwin. For details about its development, see the links section below. 

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:400px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** About PureFoundation](purefoundation.html#TOC-About-PureFoundation)
2.  [**2** Status](purefoundation.html#TOC-Status)
    1.  [**2.1** How to recognise a dependency on Foundation](purefoundation.html#TOC-How-to-recognise-a-dependency-on-Foundation)
    2.  [**2.2** Report a dependent on Foundation](purefoundation.html#TOC-Report-a-dependent-on-Foundation)
3.  [**3** Links](purefoundation.html#TOC-Links)
4.  [**4** Resources](purefoundation.html#TOC-Resources)

About PureFoundation
--------------------
PureFoundation is a binary-compatible, open source clone of Apple's Foundation framework, designed exclusively for Darwin. It uses the same components as Apple's Foundation: the Objective-C 2.0 Runtime, CoreFoundation, and (one day) the AutoZone garbage collector.
PureFoundation's primary goal is to allow certain dependant parts of Darwin run correctly. Objective-C is a great programming language, and Foundation provides a feature-rich and mature development environment, so it's hardly surprising that Apple chose it to write a number of key components of Darwin. However, since Foundation has not been released, this has left us in the position where these components simply will not run. While Apple's open source team usually do an excellent job of fixing such dependencies, in these cases the only fix would be to re-write the component in question using a different set of libraries, which is an impractical amount to ask.
Instructions for getting and installing PureFoundation can be found here: <http://code.google.com/p/purefoundation/wiki/InstallingPureFoundation>.
Status
------
<span style="font-weight:bold">v0.003 (15/03/2009)</span> Latest test target, <span style="font-family:courier new,monospace"><span style="font-size:small">dscl</span></span>, seems to run correctly.
### How to recognise a dependency on Foundation
At compile time, in the [darwinbuild](developers/darwinbuild.html) chroot, dependencies appear as missing header files (eg. "Foundation.h") or linker errors (eg. "unable to link to Foundation.framework"). At run time, dependencies are signalled by linker errors like:
> <span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span>
>
> <span>   dyld: Library not loaded: /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation
>       Referenced from: /System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/OpenDirectory</span>
or alternatively with a message like <span style="font-family:courier new,monospace">"<span style="font-size:small">Symbol not found: NSInvalidArgumentException</span>"</span><span style="font-family:arial,sans-serif">. Typically, if the symbol begins "NS", it is a problem which PureFoundation should be able to solve.</span>
See [Current Blockers](blockers.html) for a list of some of the components affected.
### Report a dependent on Foundation
If (when) you encounter a tool or application which looks like it needs Foundation, please report it via the PureFoundation issue tracker at <http://code.google.com/p/purefoundation/issues/list>. 
Links
-----
PureFoundation is now hosted on Google Code, at <http://code.google.com/p/purefoundation/>.
Resources {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:22px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
---------
<http://www.hereapi.com/pf/index.html> 
[http://www.puredarwin.org/news/purefoundation](news/purefoundation.html) 

<http://developer.apple.com/DOCUMENTATION/Cocoa/Reference/Foundation/ObjC_classic/FoundationObjC.pdf> 

<http://developer.apple.com/documentation/Cocoa/Reference/Foundation/ObjC_classic/Intro/IntroFoundation.html> 


Another similar project apparently was [Objective-C Substrate](http://landonf.bikemonkey.org/code/objc/Announcing_ObjC_Substrate.20060913022551.6494.zadder.local.html)


<span style="font-size:20px;font-weight:bold">In the beginning...</span>
"<span style="font-style:italic">One step at a time is a good walking</span>" dixit a chinese proverb.

<span style="font-weight:bold">v0.0007</span>
All classes which can be directly bridged to CFLite (strings, arrays, dictionaries, sets, calendars, timezones, etc.) are present and at least 90% complete. It can now run <span style="font-family:courier new">dscl</span> (which complains that the server isn't running and exits, but at least it doesn't crash).
------------------------------------------------------------------------
<span style="font-weight:bold">v0.0006</span>
This version should now run 'arch' correctly. It also no longer causes the X server to break.
------------------------------------------------------------------------
<span style="font-weight:bold">v0.0005</span>
We should think to change "our case study" from now.
<span style="font-family:courier new,monospace"><span style="font-size:small">arch</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">i386</span></span></span>

Exactly the expected behavior!

<span style="font-family:courier new,monospace"><span style="font-size:small">arch -p</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">arch: Unknown architecture: p</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"></span></span></span>
------------------------------------------------------------------------
<span style="color:rgb(0,0,0);font-family:Arial;font-size:13px"><span style="font-weight:bold">v0.0004</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"><span style="color:rgb(0,0,0);font-family:Arial;font-size:13px">Our case study:</span></span></span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">arch</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">i386</span></span></span>

And
<span style="font-family:courier new;font-size:12px">arch -p</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">EXCEPTION!!!!</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">  name: NSInvalidArgumentException</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">reason: Attempting mutable dictionary op on a static NSDictionary</span></span>

<span style="text-decoration:underline">Note:</span> This version, we have placed <span style="font-style:italic">Foundation.framework</span> and replaced <span style="font-style:italic">CoreFoundation.framework</span> plus <span style="font-style:italic">libobjc.A.dylib</span> in the BuildRoot.


<span style="font-family:courier new,monospace"><span style="font-size:small">FoundationTool </span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">2009-02-06 13:12:48.468 FoundationTool[12163:10b] CFLog: Hello, World!</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-- back from CFLog --</span></span>


<span style="text-decoration:underline">Note:</span> For your information, `FoundationTool' is "<span style="font-style:italic">the Cocoa command line tool you get by selecting "Foundation Tool" from the "Command Line Utility" section of XCode's "New Project..." window. I've compiled it here for your convenience. All it does is create an NSAutoreleasePool, write "Hello World!" using NSLog, then drains the pool. BUT this was compiled on OS X and will run on Darwin, proving that we've taken our first step towards a binary-compatible Foundation.framework</span>." quoting the Readme<span>.
</span>
------------------------------------------------------------------------
<span style="font-weight:bold">v0.0003</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">arch
i386 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">arch -p
zsh: bus error arch -p </span></span>
<span style="text-decoration:underline">N</span><span style="text-decoration:underline">otes:</span> Although the version 0.0003 <span style="font-style:italic">"relies on a patched CFLite, which in turn relies upon PureFoundation"</span> (dixit), it appears to work (at least for `arch') with the default CFLite for some binary.
------------------------------------------------------------------------
<span style="font-weight:bold">v0.0002</span>

<span style="font-family:courier new;font-size:12px">arch</span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject load] </span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_cfisa before = 6186080</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject class] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Continuing with +initialize -- means this is NSObject</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">address of self (NSObject Class) is 193376</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Created retain dictionary.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSString initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSString initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSCFString initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject class] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Setting _PFNSCFStringClass</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_PFNSCFStringClass = 193504</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSCFString alloc] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_PFNSCFStringClass = 193504</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_cfisa after = 6186080</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">i386</span></span></span>


<span style="font-family:courier new,monospace"><span style="font-size:small">arch -p</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject load] </span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_cfisa before = 6186080</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject class] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Continuing with +initialize -- means this is NSObject</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">address of self (NSObject Class) is 193376</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Created retain dictionary.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSString initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSString initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSCFString initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject class] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Setting _PFNSCFStringClass</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_PFNSCFStringClass = 193504</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSCFString alloc] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_PFNSCFStringClass = 193504</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_cfisa after = 6186080</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject class] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject alloc] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">NSAllocateObject </span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">value of aClass is 193696</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">object var points to 10489024</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">-[NSAutoreleasePool init] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">-[NSObject init] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSAutoreleasePool __hello:] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject class] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject initialize] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSObject class] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSString stringWithUTF8String:] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">+[NSString stringWithCString:encoding:] </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_PFBlessNSCFString </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">_PFBless old _cfisa = 0</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">zsh: bus error  arch -p </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"></span></span></span>
------------------------------------------------------------------------
<span style="font-family:arial,sans-serif"><span style="font-size:small"><span style="color:rgb(0,0,0)"><span style="font-weight:bold">v0.0001</span></span></span></span>

<span><span style="font-family:courier new,monospace"><span style="font-size:small">arch
 <span style="color:rgb(68,68,68)">NSObject +load
 i386</span></span></span></span>
<span>
 </span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"><span style="color:rgb(0,0,0)">arch -p
 </span>NSObject +load
 NSObject +initialize
 NSObject +class
 Continuing with +initialize -- means this is NSObject
 address of self (NSObject Class) is 107040
 Created retain dictionary.
 NSObject +initialize
 NSObject +class
 NSObject +alloc
 NSAllocateObject()
 value of aClass is 107360
 object var points to 10488832
 -[NSAutoreleasePool init] NSAutoreleasePool -init
 NSObject -self
 +[NSAutoreleasePool __hello:] NSAutoreleasePool +__hello:
 zsh: bus error  arch -p</span></span></span></span>



