# GNUstep

GNUstep is a cross-platform environment that provides partially Cocoa-compatible frameworks.
This page is a work in progress and is currently just a placeholder and space for collecting all things related to GNUstep.

## About GNUstep

GNUstep is a cross-platform environment loosely compatible with Cocoa. It is available for Linux, for example, and also for PureDarwin (via MacPorts). By the way, WindowMaker and GNUstep are different things and are often confused by people.

## Building GNUstep for PureDarwin

Follow the instructions on the [MacPorts](macports.1.html) page (important) and <https://trac.macports.org/ticket/14176>, <https://trac.macports.org/ticket/16425>, then do

```sh
sudo /opt/local/bin/port archive gnustep +puredarwin
```

(This is a work in progress.)

## Compiling a "Cocoa" hello world on Ubuntu

```sh
apt-get install gnustep build-essential libfoundation1.0-dev gnustep-devel gnustep-make libgnustep-base-dev gobjc # maybe too much
```

### source.m

```objc
#import <Foundation/Foundation.h>
int
main (void)
{ 
  NSLog (@"Executing");
  return 0;
}
```

### GNUmakefile

```make
include $(GNUSTEP_MAKEFILES)/common.make
TOOL_NAME = LogTest
LogTest_OBJC_FILES = source.m
include $(GNUSTEP_MAKEFILES)/tool.make
```

### Compile

```sh
export GNUSTEP_MAKEFILES=/usr/share/GNUstep/Makefiles # needed?
. /usr/share/GNUstep/Makefiles/GNUstep.sh
make
obj/LogTest # runs
make clean
make
```

## References

 - http://wiki.gnustep.org/
 - http://www.cocoabuilder.com/archive/message/cocoa/2007/12/10/194725
 - http://www.gnustep.it/nicola/Tutorials/WritingMakefiles/WritingMakefiles.html
