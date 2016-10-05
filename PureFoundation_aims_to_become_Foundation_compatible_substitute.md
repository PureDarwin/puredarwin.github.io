PureFoundation aims to become Foundation compatible substitute
==============================================================
<span style="font-family:arial">[PureFoundation](http://www.hereapi.com/pf/index.html) is an attempt to create an open-source, binary compatible substitute for Apple's closed-source [Foundation framework](http://developer.apple.com/documentation/Cocoa/Reference/Foundation/ObjC_classic/Intro/IntroFoundation.html). The foundation framework is an essential piece of Mac OS X and has lately also become a dependency of some Darwin projects.</span>
<span>
</span>
<span style="font-family:arial">PureFoundation developer Stuart Crook descibes his new project as follows: In many ways it is similar to [GNUStep Base](http://www.gnustep.org/resources/documentation/Developer/Base/Reference/Base.html) (and may even share some of its code one day), but it differs in that it makes use of Apple's own [Objective-C 2.0 runtime](http://developer.apple.com/DOCUMENTATION/Cocoa/Reference/ObjCRuntimeRef/Reference/reference.html) and [AutoZone Garbage Collector](http://www.opensource.apple.com/darwinsource/10.5.5/autozone-77.1/README.html)  (a nice side effect of which is binary compatibility with Mac OS X.) The main purpose of PureFoundation is to get portions of Darwin up and running with as little patching of the original code as possible. Sometimes just having a framework in place called "Foundation" and identifying itself with the correct version strings is enough to spur recalcitrant apps into life. Many functions will be implemented by bridging to Apple's [CF-Lite](http://developer.apple.com/opensource/cflite.html). Many more will be provided thanks to GNUStep. However, it is unlikely PureFoundation will every replicate all aspects of Apple's Foundation, and the project will certainly never stray into AppKit and beyond.</span>
<span>
</span>
It is hoped that PureFoundation can be used to solve issues like [DarwinBuild ticket #49](http://darwinbuild.macosforge.org/trac/ticket/49).

<span>For more information on PureFoundation, please see its homepage at</span>
<span><span style="font-family:arial"><http://www.hereapi.com/pf/></span></span>
