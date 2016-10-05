GNUstep
=======
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[ ![](../_/rsrc/1222698421626/developers/gnustep/GNUstep_Logo_clipped-1.png)](gnustep/GNUstep_Logo_clipped-1.png%3Fattredirects=0)
GNUstep is a cross-platform environment that provides partially Cocoa-compatible frameworks.
This page is a work in progress and is currently just a placeholder and space for collecting all things related to GNUstep.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** About GNUstep](gnustep.html#TOC-About-GNUstep)
2.  [**2** Building GNUstep for PureDarwin](gnustep.html#TOC-Building-GNUstep-for-PureDarwin)
3.  [**3** Compiling a "Cocoa" hello world on Ubuntu](gnustep.html#TOC-Compiling-a-Cocoa-hello-world-on-Ubuntu)
    1.  [**3.1** source.m](gnustep.html#TOC-source.m)
    2.  [**3.2** GNUmakefile](gnustep.html#TOC-GNUmakefile)
    3.  [**3.3** Compile](gnustep.html#TOC-Compile)
4.  [**4** References](gnustep.html#TOC-References)


### About GNUstep
GNUstep is a cross-platform environment loosely compatible with Cocoa. It is available for Linux, for example, and also for PureDarwin (via MacPorts). For more general information about what GNUstep is, see the [Introduction to GNUstep](../index.html). By the way, WindowMaker and GNUstep are different things and are often confused by people.
### Building GNUstep for PureDarwin
Follow the instructions on the [MacPorts](macports.1.html) page (important) and <https://trac.macports.org/ticket/14176>, <https://trac.macports.org/ticket/16425>, then do

<span style="font-family:courier new,monospace">sudo /opt/local/bin/port archive gnustep +puredarwin</span>

(This is a work in progress.)
### Compiling a "Cocoa" hello world on Ubuntu
apt-get install gnustep build-essential libfoundation1.0-dev gnustep-devel gnustep-make libgnustep-base-dev gobjc # maybe too much
#### source.m
    #import <Foundation/Foundation.h>
    int
    main (void)
    { 
      NSLog (@"Executing");
      return 0;
    }
#### GNUmakefile
    include $(GNUSTEP_MAKEFILES)/common.make
    TOOL_NAME = LogTest
    LogTest_OBJC_FILES = source.m
    include $(GNUSTEP_MAKEFILES)/tool.make
#### Compile
export GNUSTEP_MAKEFILES=/usr/share/GNUstep/Makefiles # needed?
 . /usr/share/GNUstep/Makefiles/GNUstep.sh
 make
 obj/LogTest # runs
 make clean
 make

### References {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:18px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
http://wiki.gnustep.org/
http://www.cocoabuilder.com/archive/message/cocoa/2007/12/10/194725
http://www.gnustep.it/nicola/Tutorials/WritingMakefiles/WritingMakefiles.html
