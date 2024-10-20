Visualize KEXTs dependencies
============================
In the spirit of [Vizualize dependencies in MacPorts](../macports/macports-dependencies-overview.html), this page describes a way to track kernel extension dependencies and related satellite information (e.g: blockers).

### Prerequisites
[Graphviz](http://www.graphviz.org/) is an opensource graph visualization software from AT&T Laboratories and Bell Laboratories (Lucent Technologies).


`port install graphviz +the_variants_you_need`

or grab and compile the source from [graphviz.org](http://graphviz.org/).
__Note:__ On Mac OS X, [Pixelglow](http://www.pixelglow.com/graphviz/) is a nice a front-end, you can even see the graph being built in real-time.
### Using pd_kextviz to generate a graph
The *[pd_kextviz](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/pd_kextviz)* tool is available in the [svn or hg trunk](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/)s.
#### Preliminary
A rudimentary legend is generated in the DOT language:

![](/img/developers/kexts/kexts-dependencies-overview/pd_kextviz%20legend.png)


A KEXT is simply linked to ia bundle identifier (which can be linked to one or many KEXTs).

For clarity purpose, the bundle identifiers are hidden by default.

For purity purpose, each KEXT is examined once in order to find and count potential "[current blocker](../../blockers.html)".

The number of symbols missing (returned by *kextlibs*) is also displayed on the respective KEXT.
#### An example across IOBDStorageFamily.kext
The hierarchical view:

![](/img/developers/kexts/kexts-dependencies-overview/pd_kextviz%20IOBDStorageFamily%20hierarchical%20view.png)

This circular view:

![](/img/developers/kexts/kexts-dependencies-overview/pd_kextviz%20IOBDStorageFamily%20circular%20view.png)


The corresponding script output:


`./pd_kextviz /System/Library/Extensions/IOBDStorageFamily.kext`



`
`
` Legend:`
` 1` ` + foo ()`
` 2` ` |`- bar (bundle id)                                 No more dependency`
` 2` ` |`+ baz impure! /Blocker_1 -> file_involved_1       Impurity detected`
` 2` ` |`+ baz impure! /Blocker_. -> file_involved_.       Impurity detected`
` 2` ` |`+ baz impure! /Blocker_n -> file_involved_n       Impurity detected`
` 2` ` |`+ qux ()                                          Dependency found`
` 3` ` | |`. bar (cached: bundle id)                       Cached bundle identifier`
` 1` ` . qux                                               Cached kext (Already processed)`
`
`
`Now generating dependencies graphs of kexts, please wait...`
`
`
` 1` ` + /System/Library/Extensions/IOBDStorageFamily.kext ()`
` 2` ` |`- /System/Library/Extensions/System.kext/PlugIns/Mach.kext (com.apple.kpi.mach)`
` 2` ` |`- /System/Library/Extensions/System.kext/PlugIns/Libkern.kext (com.apple.kpi.libkern)`
` 2` ` |`- /System/Library/Extensions/System.kext/PlugIns/IOKit.kext (com.apple.kpi.iokit)`
` 2` ` |`- /System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext (com.apple.kpi.bsd)`
` 2` ` |`+ /System/Library/Extensions/IOStorageFamily.kext (com.apple.iokit.IOStorageFamily)`
` 3` ` | |`- /System/Library/Extensions/System.kext/PlugIns/Unsupported.kext (com.apple.kpi.unsupported)`
` 2` ` | |`. </System/Library/Extensions/System.kext/PlugIns/Mach.kext> (cached: com.apple.kpi.mach)`
` 2` ` | |`. </System/Library/Extensions/System.kext/PlugIns/Libkern.kext> (cached: com.apple.kpi.libkern)`
` 2` ` | |`. </System/Library/Extensions/System.kext/PlugIns/IOKit.kext> (cached: com.apple.kpi.iokit)`
` 2` ` | |`. </System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext> (cached: com.apple.kpi.bsd)`
` 2` ` |`+ /System/Library/Extensions/IODVDStorageFamily.kext (com.apple.iokit.IODVDStorageFamily)`
` 2` ` | |`. </System/Library/Extensions/System.kext/PlugIns/Mach.kext> (cached: com.apple.kpi.mach)`
` 2` ` | |`. </System/Library/Extensions/System.kext/PlugIns/Libkern.kext> (cached: com.apple.kpi.libkern)`
` 2` ` | |`. </System/Library/Extensions/System.kext/PlugIns/IOKit.kext> (cached: com.apple.kpi.iokit)`
` 2` ` | |`. </System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext> (cached: com.apple.kpi.bsd)`
` 2` ` | |`. </System/Library/Extensions/IOStorageFamily.kext> (cached: com.apple.iokit.IOStorageFamily)`
` 3` ` | |`+ /System/Library/Extensions/IOCDStorageFamily.kext (com.apple.iokit.IOCDStorageFamily)`
` 3` ` | | |`. </System/Library/Extensions/System.kext/PlugIns/Mach.kext> (cached: com.apple.kpi.mach)`
` 3` ` | | |`. </System/Library/Extensions/System.kext/PlugIns/Libkern.kext> (cached: com.apple.kpi.libkern)`
` 3` ` | | |`. </System/Library/Extensions/System.kext/PlugIns/IOKit.kext> (cached: com.apple.kpi.iokit)`
` 3` ` | | |`. </System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext> (cached: com.apple.kpi.bsd)`
` 3` ` | | |`. </System/Library/Extensions/IOStorageFamily.kext> (cached: com.apple.iokit.IOStorageFamily)`
` 1` ` |`. </System/Library/Extensions/IOCDStorageFamily.kext> (cached: com.apple.iokit.IOCDStorageFamily)`
`
`
Generation of IOBDStorageFamily.kext.dot complete.
`
`
`Now drawing graphs from IOBDStorageFamily.kext.dot, please wait...`
Generation of IOBDStorageFamily.kext_directed.png complete.

`Generation of IOBDStorageFamily.kext_circular. png complete.`
`Generation of IOBDStorageFamily.kext_radial. png complete.`
`Generation of IOBDStorageFamily.kext_undirected. png complete.`
`Generation of IOBDStorageFamily.kext_undirectedBIS.png complete.`
#### Detecting blocker inside KEXTs
The example below has been generated on Mac OS X with *IOSerialFamily.kext*, since we don't have any blocker on PureDarwin.


![](/img/developers/kexts/kexts-dependencies-overview/pd_kextviz%20impure%20IOSerialFamily.png)

The corresponding output:


`[...]`
` 1` ` + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -> /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/AppleVerizonSupport.kext/Contents/Resources/FixNetworkConfig `
` 1` ` + /System/Library/Extensions/IOSerialFamily.kext impure! /AppKit.framework -> /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold `
` 1` ` + /System/Library/Extensions/IOSerialFamily.kext impure! /ApplicationServices.framework -> /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold `
` 1` ` + /System/Library/Extensions/IOSerialFamily.kext impure! /Cocoa.framework -> /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold `
` 1` ` + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -> /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold `
` 1` ` + /System/Library/Extensions/IOSerialFamily.kext impure! /Foundation.framework -> /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold `
` 1` ` + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -> /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalUSBModem.kext/Contents/Resources/modemd `
` 1` ` + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -> /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/MotorolaSM56K.kext/Contents/Resources/MDCPd `
` 1` ` + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -> /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/MotorolaSM56KUSB.kext/Contents/Resources/MDCPdUSB`

` 1` ` + /System/Library/Extensions/IOSerialFamily.kext ()`
[...]



Generation of IOSerialFamily.kext.dot complete.


#### Massive generation
We generate the whole dependencies tree with:

`./pd_kextviz `find /System/Library/Extensions/ -name '*.kext'``

At this time, it looks like:

![](/img/developers/kexts/kexts-dependencies-overview/pd_kextviz%20all%20KEXTs.png)

The circular overview is usefull (but often too big) to isolate node with a number of links lower than 2:
![](/img/developers/kexts/kexts-dependencies-overview/pd_kextviz%20circular%20all%20kexts%20in%20puredarwin.png)
#### Miscellaneous
The Mac OS X whole graph:

![](/img/developers/kexts/kexts-dependencies-overview/pd_kextviz%20all%20KEXTs%20in%20MacOSX.png)
### Ressources
[http://www.graphviz.org](http://www.graphviz.org/)
The [Kernel Extensions (KEXTs)](../kexts.html) page


