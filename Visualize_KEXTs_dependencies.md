Visualize KEXTs dependencies
============================
In the spirit of [Vizualize dependencies in MacPorts](../macports/macports-dependencies-overview.html), this page describes a way to track kernel extension dependencies and related satellite information (e.g: blockers).

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:350px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Prerequisites](kexts-dependencies-overview.html#TOC-Prerequisites)
2.  [**2** Using pd_kextviz to generate a graph](kexts-dependencies-overview.html#TOC-Using-pd_kextviz-to-generate-a-graph)
    1.  [**2.1** Preliminary](kexts-dependencies-overview.html#TOC-Preliminary)
    2.  [**2.2** An example across IOBDStorageFamily.kext](kexts-dependencies-overview.html#TOC-An-example-across-IOBDStorageFamily.kext)
    3.  [**2.3** Detecting blocker inside KEXTs](kexts-dependencies-overview.html#TOC-Detecting-blocker-inside-KEXTs)
    4.  [**2.4** Massive generation](kexts-dependencies-overview.html#TOC-Massive-generation)
    5.  [**2.5** Miscellaneous](kexts-dependencies-overview.html#TOC-Miscellaneous)
3.  [**3** Ressources](kexts-dependencies-overview.html#TOC-Ressources)

### Prerequisites
[Graphviz](http://www.graphviz.org/) is an opensource graph visualization software from AT&T Laboratories and Bell Laboratories (Lucent Technologies).


<span style="font-family:courier new,monospace"><span style="font-size:small">port install graphviz +the_variants_you_need</span></span>

or grab and compile the source from [graphviz.org](http://graphviz.org/).
<span style="text-decoration:underline">Note:</span> On Mac OS X, [Pixelglow](http://www.pixelglow.com/graphviz/) is a nice a front-end, you can even see the graph being built in real-time.
### Using pd_kextviz to generate a graph
The <span style="font-style:italic">[pd_kextviz](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/pd_kextviz)</span> tool is available in the [svn or hg trunk](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/)s.
#### Preliminary
A rudimentary legend is generated in the DOT language:

[![](../../_/rsrc/1224217629680/developers/kexts/kexts-dependencies-overview/pd_kextviz%20legend.png)](kexts-dependencies-overview/pd_kextviz%20legend.png%3Fattredirects=0)


A KEXT is simply linked to ia bundle identifier (which can be linked to one or many KEXTs).

For clarity purpose, the bundle identifiers are hidden by default.

For purity purpose, each KEXT is examined once in order to find and count potential "[current blocker](../../blockers.html)".

The number of symbols missing (returned by <span style="font-style:italic">kextlibs</span>) is also displayed on the respective KEXT.
#### An example across IOBDStorageFamily.kext
The hierarchical view:

[![](../../_/rsrc/1224170222152/developers/kexts/kexts-dependencies-overview/pd_kextviz%20IOBDStorageFamily%20hierarchical%20view.png%3Fheight=241&width=420)](kexts-dependencies-overview/pd_kextviz%20IOBDStorageFamily%20hierarchical%20view.png%3Fattredirects=0)

This circular view:

[![](../../_/rsrc/1224170219802/developers/kexts/kexts-dependencies-overview/pd_kextviz%20IOBDStorageFamily%20circular%20view.png%3Fheight=310&width=420)](kexts-dependencies-overview/pd_kextviz%20IOBDStorageFamily%20circular%20view.png%3Fattredirects=0)


The corresponding script output:


<span style="font-family:courier new,monospace"><span style="font-size:small">./pd_kextviz /System/Library/Extensions/IOBDStorageFamily.kext</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">G</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">enerate dependencies graphs of /System/Library/Extensions/IOBDStorageFamily.kext</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> Legend:</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 1</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> + foo ()</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`- bar (bundle id)                                 No more dependency</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ baz impure! /Blocker_1 -&gt; file_involved_1       Impurity detected</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ baz impure! /Blocker_. -&gt; file_involved_.       Impurity detected</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ baz impure! /Blocker_n -&gt; file_involved_n       Impurity detected</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ qux ()                                          Dependency found</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. bar (cached: bundle id)                       Cached bundle identifier</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 1</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> . qux                                               Cached kext (Already processed)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Now generating dependencies graphs of kexts, please wait...</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 1</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> + /System/Library/Extensions/IOBDStorageFamily.kext ()</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`- /System/Library/Extensions/System.kext/PlugIns/Mach.kext (com.apple.kpi.mach)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`- /System/Library/Extensions/System.kext/PlugIns/Libkern.kext (com.apple.kpi.libkern)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`- /System/Library/Extensions/System.kext/PlugIns/IOKit.kext (com.apple.kpi.iokit)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`- /System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext (com.apple.kpi.bsd)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ /System/Library/Extensions/IOStorageFamily.kext (com.apple.iokit.IOStorageFamily)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`- /System/Library/Extensions/System.kext/PlugIns/Unsupported.kext (com.apple.kpi.unsupported)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/Mach.kext&gt; (cached: com.apple.kpi.mach)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/Libkern.kext&gt; (cached: com.apple.kpi.libkern)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/IOKit.kext&gt; (cached: com.apple.kpi.iokit)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext&gt; (cached: com.apple.kpi.bsd)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ /System/Library/Extensions/IODVDStorageFamily.kext (com.apple.iokit.IODVDStorageFamily)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/Mach.kext&gt; (cached: com.apple.kpi.mach)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/Libkern.kext&gt; (cached: com.apple.kpi.libkern)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/IOKit.kext&gt; (cached: com.apple.kpi.iokit)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext&gt; (cached: com.apple.kpi.bsd)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. &lt;/System/Library/Extensions/IOStorageFamily.kext&gt; (cached: com.apple.iokit.IOStorageFamily)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`+ /System/Library/Extensions/IOCDStorageFamily.kext (com.apple.iokit.IOCDStorageFamily)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/Mach.kext&gt; (cached: com.apple.kpi.mach)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/Libkern.kext&gt; (cached: com.apple.kpi.libkern)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/IOKit.kext&gt; (cached: com.apple.kpi.iokit)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | | |`. &lt;/System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext&gt; (cached: com.apple.kpi.bsd)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> | | |`. &lt;/System/Library/Extensions/IOStorageFamily.kext&gt; (cached: com.apple.iokit.IOStorageFamily)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> 1</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`. &lt;/System/Library/Extensions/IOCDStorageFamily.kext&gt; (cached: com.apple.iokit.IOCDStorageFamily)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span>
<span style="font-family:courier new;font-size:12px"><span style="color:rgb(68,68,68)">Generation of IOBDStorageFamily.kext.dot complete.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Now drawing graphs from IOBDStorageFamily.kext.dot, please wait...</span></span></span>
<span style="font-family:courier new;font-size:12px"><span style="color:rgb(68,68,68)">Generation of IOBDStorageFamily.kext_directed.png complete.</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span><span style="color:rgb(68,68,68)">Generation of IOBDStorageFamily.kext_circular. png complete.</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span><span style="color:rgb(68,68,68)">Generation of IOBDStorageFamily.kext_radial. png complete.</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span><span style="color:rgb(68,68,68)">Generation of IOBDStorageFamily.kext_undirected. png complete.</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span><span style="color:rgb(68,68,68)">Generation of IOBDStorageFamily.kext_undirectedBIS.png complete.</span></span></span></span>
#### Detecting blocker inside KEXTs
The example below has been generated on Mac OS X with <span style="font-style:italic">IOSerialFamily.kext</span>, since we don't have any blocker on PureDarwin.


[![](../../_/rsrc/1224171074199/developers/kexts/kexts-dependencies-overview/pd_kextviz%20impure%20IOSerialFamily.png)](kexts-dependencies-overview/pd_kextviz%20impure%20IOSerialFamily.png%3Fattredirects=0)

The corresponding output:


<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -&gt; /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/AppleVerizonSupport.kext/Contents/Resources/FixNetworkConfig </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext impure! /AppKit.framework -&gt; /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext impure! /ApplicationServices.framework -&gt; /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext impure! /Cocoa.framework -&gt; /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -&gt; /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext impure! /Foundation.framework -&gt; /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalModemSupport.kext/Contents/Resources/AppleModemOnHold.app/Contents/MacOS/AppleModemOnHold </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -&gt; /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/InternalUSBModem.kext/Contents/Resources/modemd </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -&gt; /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/MotorolaSM56K.kext/Contents/Resources/MDCPd </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext impure! /CoreServices.framework -&gt; /System/Library/Extensions/IOSerialFamily.kext/Contents/PlugIns/MotorolaSM56KUSB.kext/Contents/Resources/MDCPdUSB</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + /System/Library/Extensions/IOSerialFamily.kext ()</span></span>
<span style="font-family:courier new;font-size:12px">[...]</span>
<span style="font-family:courier new;font-size:12px">
</span>
<span style="font-family:courier new;font-size:12px"></span>
Generation of IOSerialFamily.kext.dot complete.


#### Massive generation
We generate the whole dependencies tree with:

<span style="font-family:courier new,monospace"><span style="font-size:small">./pd_kextviz `find /System/Library/Extensions/ -name '*.kext'`</span></span>

At this time, it looks like:

[![](../../_/rsrc/1224212607569/developers/kexts/kexts-dependencies-overview/pd_kextviz%20all%20KEXTs.png%3Fheight=420&width=272)](kexts-dependencies-overview/pd_kextviz%20all%20KEXTs.png%3Fattredirects=0)

The circular overview is usefull (but often too big) to isolate node with a number of links lower than 2:
[![](../../_/rsrc/1224212618987/developers/kexts/kexts-dependencies-overview/pd_kextviz%20circular%20all%20kexts%20in%20puredarwin.png%3Fheight=410&width=420)](kexts-dependencies-overview/pd_kextviz%20circular%20all%20kexts%20in%20puredarwin.png%3Fattredirects=0)
#### Miscellaneous
The Mac OS X whole graph:

[![](../../_/rsrc/1224217472176/developers/kexts/kexts-dependencies-overview/pd_kextviz%20all%20KEXTs%20in%20MacOSX.png%3Fheight=420&width=168)](kexts-dependencies-overview/pd_kextviz%20all%20KEXTs%20in%20MacOSX.png%3Fattredirects=0)
### Ressources
[http://www.graphviz.org](http://www.graphviz.org/)
The [Kernel Extensions (KEXTs)](../kexts.html) page


