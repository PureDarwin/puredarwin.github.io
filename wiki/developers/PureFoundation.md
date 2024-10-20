PureFoundation
==============
This page is about the use of PureFoundation on Darwin. For details about its development, see the links section below. 

About PureFoundation
--------------------
PureFoundation is a binary-compatible, open source clone of Apple's Foundation framework, designed exclusively for Darwin. It uses the same components as Apple's Foundation: the Objective-C 2.0 Runtime, CoreFoundation, and (one day) the AutoZone garbage collector.
PureFoundation's primary goal is to allow certain dependant parts of Darwin run correctly. Objective-C is a great programming language, and Foundation provides a feature-rich and mature development environment, so it's hardly surprising that Apple chose it to write a number of key components of Darwin. However, since Foundation has not been released, this has left us in the position where these components simply will not run. While Apple's open source team usually do an excellent job of fixing such dependencies, in these cases the only fix would be to re-write the component in question using a different set of libraries, which is an impractical amount to ask.
Instructions for getting and installing PureFoundation can be found here: <http://code.google.com/p/purefoundation/wiki/InstallingPureFoundation>.
Status
------
**v0.003 (15/03/2009)** Latest test target, `dscl`, seems to run correctly.
### How to recognise a dependency on Foundation
At compile time, in the [darwinbuild](developers/darwinbuild.html) chroot, dependencies appear as missing header files (eg. "Foundation.h") or linker errors (eg. "unable to link to Foundation.framework"). At run time, dependencies are signalled by linker errors like:
> ` `
>
> <span>   dyld: Library not loaded: /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation
>       Referenced from: /System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/OpenDirectory</span>
or alternatively with a message like ``. Typically, if the symbol begins "NS", it is a problem which PureFoundation should be able to solve.
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


**In the beginning...**
"*One step at a time is a good walking*" dixit a chinese proverb.

**v0.0007**
All classes which can be directly bridged to CFLite (strings, arrays, dictionaries, sets, calendars, timezones, etc.) are present and at least 90% complete. It can now run dscl (which complains that the server isn't running and exits, but at least it doesn't crash).
------------------------------------------------------------------------
**v0.0006**
This version should now run 'arch' correctly. It also no longer causes the X server to break.
------------------------------------------------------------------------
**v0.0005**
We should think to change "our case study" from now.
`arch`
`i386`

Exactly the expected behavior!

`arch -p`
`arch: Unknown architecture: p`
``
------------------------------------------------------------------------
v0.0004
`Our case study:`

`arch`
`i386`

And
arch -p
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
`EXCEPTION!!!!`
` ``  name: NSInvalidArgumentException`
` ``reason: Attempting mutable dictionary op on a static NSDictionary`

__Note:__ This version, we have placed *Foundation.framework* and replaced *CoreFoundation.framework* plus *libobjc.A.dylib* in the BuildRoot.


`FoundationTool `

`2009-02-06 13:12:48.468 FoundationTool[12163:10b] CFLog: Hello, World!`
`-- back from CFLog --`


__Note:__ For your information, `FoundationTool' is "*the Cocoa command line tool you get by selecting "Foundation Tool" from the "Command Line Utility" section of XCode's "New Project..." window. I've compiled it here for your convenience. All it does is create an NSAutoreleasePool, write "Hello World!" using NSLog, then drains the pool. BUT this was compiled on OS X and will run on Darwin, proving that we've taken our first step towards a binary-compatible Foundation.framework*." quoting the Readme.

------------------------------------------------------------------------
**v0.0003**
`arch
i386 `
`arch -p
zsh: bus error arch -p `
__N____otes:__ Although the version 0.0003 *"relies on a patched CFLite, which in turn relies upon PureFoundation"* (dixit), it appears to work (at least for `arch') with the default CFLite for some binary.
------------------------------------------------------------------------
**v0.0002**

arch

`+[NSObject load] `
 `_cfisa before = 6186080`
`+[NSObject initialize] `
`+[NSObject class] `
`Continuing with +initialize -- means this is NSObject`
`address of self (NSObject Class) is 193376`
`Created retain dictionary.`
`+[NSString initialize] `
`+[NSString initialize] `
`+[NSCFString initialize] `
`+[NSObject class] `
`Setting _PFNSCFStringClass`
`_PFNSCFStringClass = 193504`
`+[NSCFString alloc] `
`_PFNSCFStringClass = 193504`
 `_cfisa after = 6186080`
`i386`


`arch -p`
`+[NSObject load] `
 `_cfisa before = 6186080`
`+[NSObject initialize] `
`+[NSObject class] `
`Continuing with +initialize -- means this is NSObject`
`address of self (NSObject Class) is 193376`
`Created retain dictionary.`
`+[NSString initialize] `
`+[NSString initialize] `
`+[NSCFString initialize] `
`+[NSObject class] `
`Setting _PFNSCFStringClass`
`_PFNSCFStringClass = 193504`
`+[NSCFString alloc] `
`_PFNSCFStringClass = 193504`
 `_cfisa after = 6186080`
`+[NSObject initialize] `
`+[NSObject class] `
`+[NSObject alloc] `
`NSAllocateObject `
 `value of aClass is 193696`
 `object var points to 10489024`
`-[NSAutoreleasePool init] `
`-[NSObject init] `
`+[NSAutoreleasePool __hello:] `
`+[NSObject initialize] `
`+[NSObject class] `
`+[NSObject initialize] `
`+[NSObject class] `
`+[NSString stringWithUTF8String:] `
`+[NSString stringWithCString:encoding:] `
`_PFBlessNSCFString `
`_PFBless old _cfisa = 0`
`zsh: bus error  arch -p `
``
------------------------------------------------------------------------
v0.0001


<span>
 </span>




