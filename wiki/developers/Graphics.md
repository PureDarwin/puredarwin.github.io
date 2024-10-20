Graphics
========
This page describes the graphics infrastructure on both Darwin and Mac OS X.

Sections marked with the "X" logo only apply to Mac OS X and not to Darwin. They are included here to increase the understanding of the differences between PureDarwin and Mac OS X only. 

This page is a work in progress, please contribute.

### Overview

While Darwin is the operating system underlying Mac OS X, the graphical environments of PureDarwin and Mac OS X are very different. This is because most graphical aspects of Mac OS X (especially Quartz and Aqua) are proprietary, closed-source software and are not available for PureDarwin. Hence, PureDarwin uses a more traditional UNIX-like graphics system (X server), waiting a better alternative.

### PureDarwin![](http://sites.google.com/a/puredarwin.org/puredarwin/_/rsrc/1212143186078/users/prerequisites/darwin9.gif) 

What follows is an overview about the various terms and components that make up the graphical infrastructure of PureDarwin.

#### IOGraphics

The IOGraphics project consists of
-   IOGraphicsFamily.kext
-   IONDRVSupport.kext (legacy; apparently for very old graphics chips such as  [ATI Rage series](http://en.wikipedia.org/wiki/Comparison_of_ATI_Graphics_Processing_Units#Rage_series) cards from around 1997, Chips and Technologies [Asiliant 65550](http://www.asiliant.com/65550.htm) from around 1997, used in PowerBook 2400/3400)

It is open source.

#### GraphicsDrivers

GraphicsDrivers is a proprietary, closed-source project that consists (or doesn't yet include) of the following drivers:
**ATI**
-   **Radeon**: Drivers for a series of ATI [R100](http://en.wikipedia.org/wiki/Radeon_R100)-based graphics cards from 2001 
    (ATIRadeon.kext, ATIRadeonDVDDriver.bundle, ATIRadeonGA.plugin, ATIRadeonGLDriver.bundle)
-   **Radeon 8500**:** **Drivers for a series of ATI [R200](http://en.wikipedia.org/wiki/Radeon_R200)-based graphics cards from 2001 
    (ATIRadeon8500.kext, ATIRadeon8500DVDDriver.bundle, ATIRadeon8500GA.plugin,
    ATIRadeon8500GLDriver.bundle, ATIRadeon8500VADriver.bundle)
-   **Radeon 9700**: Drivers for a series of ATI [R300](http://en.wikipedia.org/wiki/Radeon_R300)-based graphics cards from 2002 
    (ATIRadeon9700.kext, ATIRadeon9700DVDDriver.bundle, ATIRadeon9700GA.plugin, 
    ATIRadeon9700GLDriver.bundle, ATIRadeon9700VADriver.bundle)
-   **Radeon X1000** (missing): Drivers for a series of ATI [R520](http://en.wikipedia.org/wiki/Radeon_R520)-based graphics cards from 2005
    (ATIRadeonX1000.kext, ATIRadeonX1000GA.plugin, ATIRadeonX1000GLDriver.bundle, ATIRadeonX1000VADriver.bundle)
-   **Radeon X2000** (missing): Drivers for a series of ATI [R600](http://en.wikipedia.org/wiki/Radeon_R600)-based graphics cards from 2006
    (ATIRadeonX2000.kext, ATIRadeonX2000GA.plugin, ATIRadeonX2000GLDriver.bundle, ATIRadeonX2000VADriver.bundle)
**Intel**
-   **AppleIntel830**: Drivers for a series of Intel 82830M-based on-board graphics found in [830M, 830MG, and 830MP chipsets](http://www.intel.com/support/chipsets/sb/CS-009234.htm) from 2003 (AppleIntel830.kext, AppleIntel830GA.plugin, AppleIntel830GLDriver.bundle)
-   **AppleIntel915**: Drivers for a series of Intel 82915G/82910GL-based on-board graphics found in the [Intel 915 Express Chipset family](http://www.intel.com/support/chipsets/sb/CS-011594.htm) from 2004 (AppleIntel915GA.plugin, AppleIntel915GLDriver.bundle)
-   ****: Drivers for a series of Intel [GMA 950](http://en.wikipedia.org/wiki/Intel_GMA#GMA_950)-based on-board graphics from 2005 
    found in the Mac mini and early MacBook 
    (AppleIntelIntegratedFramebuffer.kext, AppleIntelGMA950.kext, AppleIntelGMA950GA.plugin, 
    AppleIntelGMA950GLDriver.bundle, AppleIntelGMA950VADriver.bundle)
-   **AppleIntelGMAX3100 (missing)**: Drivers for a series of Intel [GMA X3100](http://en.wikipedia.org/wiki/Intel_GMA#GMA_X3100)-based on-board graphics from 2007
    found in the MacBook
    (AppleIntelGMAX3100.kext, AppleIntelGMAX3100FB.kext, AppleIntelGMAX3100GA.plugin, 
    AppleIntelGMAX3100GLDriver.bundle, AppleIntelGMAX3100VADriver.bundle)
**Legacy**
-   AppleAltiVecDVDDriver.bundle (relevant on PPC only)
-   AppleNDRV/ATIDriver.bundle
-   AppleNDRV/ATIRuntime.bundle
**NVidia**
-   GeForce.kext
-   GeForce2MXGLDriver.bundle
-   GeForce3GLDriver.bundle
-   GeForceFXGLDriver.bundle
-   GeForceGA.plugin
-   NVDA**NV10**Hal.kext: Driver for a series of [NV10](http://en.wikipedia.org/wiki/GeForce_256)-based graphics cards from 1999 known as "GeForce 256"
-   NVDA**NV20**Hal.kext: Driver for a series of [NV20](http://en.wikipedia.org/wiki/GeForce_3_Series)-based graphics cards from 2001 known as "GeForce 3 Series"
-   NVDA**NV30**Hal.kext: Driver for a series of [NV30](http://en.wikipedia.org/wiki/GeForce_FX_Series)-based graphics cards from 2003 known as "GeForce FX Series"/"GeForce 5"
-   NVDA**NV40**Hal.kext: Driver for a series of [NV40](http://en.wikipedia.org/wiki/GeForce_6_Series)-based graphics cards from 2004 known as "GeForce 6 Series"
-   NVDA**NV50**Hal.kext (missing): Driver for a series of [G8x](../index.html)-based graphics cards from 2006 known as "GeForce 8 Series", "8x00" models
-   NVDAResman.kext
The GraphicsDrivers project is available for use with Darwin under the Apple Driver License.
The drivers in Mac OS X 10.5.5 are SourceVersion 53017 (GraphicsDrivers-5.30.17). The [MacBook, MacBook Pro Software Update 1.2](http://www.apple.com/downloads/macosx/apple/application_updates/macbookmacbookprosoftwareupdate12.html) contains SourceVersion 53410 (GraphicsDrivers-5.34.10). The version available for Darwin seems to be still 40024.

#### X server

Like most other UNIX-like operating systems, PureDarwin uses an X server to display on-screen graphics. Please see the [XFree86](xfree86.html) and [X.Org](xorg.html) pages for details.

#### VMware framebuffer

This is a framebuffer kext included in the VMware Tools for Mac.

#### IOProxyVideoFamily

<http://code.google.com/p/ioproxyvideofamily/> **need investigation**

### Mac OS X

<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">

![](/img/users/prerequisites/xicon.jpg)

What follows is an overview about the various terms and components that make up the graphical infrastructure of Mac OS X.

#### Quartz

Apple describes Quartz as the "graphics system which forms the foundation of the imaging model for Mac OS X". The Quatz drawing engine internally uses the PDF format. It can be seen as the successor of the "Display PostScript"-based engine used in NeXTSTEP. Quartz is also responsible for rendering effects like drop shadows in the Mac OS X user interface. Quartz is contained in the closed-source, proprietary** Core Graphics** framework. According to Apple, the terms Quartz and Core Graphics are often used synonymously: "The Quartz 2D API is part of the Core Graphics framework, so you may see Quartz referred to as Core Graphics or, simply, CG". For more information on Quartz, see the [ADC documentation on Quartz](http://developer.apple.com/documentation/GraphicsImaging/Quartz-date.html). (It is roughly equivalent to what is known as a "window server" and "window manager" on other systems.)

#### Aqua
The term Aqua is used to describe the visual theme of the Mac OS X user interface. (It is roughly equivalent to what is known as a "skin" on other systems.)

#### Framebuffer

AppleIntelIntegratedFramebuffer.kext is loaded by default on Mac OS X.

### Troubleshooting

#### AppleIntel830.kext fails to load

AppleIntel830.kext is part of the GraphicsDrivers project.
**
**
**Problem:**
14Intel830Memory is not compatible with its superclass, 8OSObject superclass changed?
**
**
**Solution:**
Please let us know if you know the solution.
