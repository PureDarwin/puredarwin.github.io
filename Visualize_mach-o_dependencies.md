Visualize mach-o dependencies
=============================
In the spirit of [Vizualize dependencies in MacPorts](../macports/macports-dependencies-overview.html) and [Vizualize KEXTs dependencies](../kexts/kexts-dependencies-overview.html), this page describes a way to track mach-o file dependencies and related satellite information (e.g: blockers).

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:444px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Prerequisites](mach-o-dependencies-overview.html#TOC-Prerequisites)
2.  [**2** Using pd_machviz to generate a graph](mach-o-dependencies-overview.html#TOC-Using-pd_machviz-to-generate-a-graph)
    1.  [**2.1** A simple example across otool dependencies](mach-o-dependencies-overview.html#TOC-A-simple-example-across-otool-dependencies)
    2.  [**2.2** A circular view of xterm dependencies](mach-o-dependencies-overview.html#TOC-A-circular-view-of-xterm-dependencies)
    3.  [**2.3** Checking for purity in passwd](mach-o-dependencies-overview.html#TOC-Checking-for-purity-in-passwd)
3.  [**3** Resources](mach-o-dependencies-overview.html#TOC-Resources)

### Prerequisites

[Graphviz](http://www.graphviz.org/) is an opensource graph visualization software from AT&T Laboratories and Bell Laboratories (Lucent Technologies).

<div style="font-family:courier new,monospace">
<span style="font-size:small">port install graphviz +the_variants_you_need</span>

or grab and compile the source from [graphviz.org](http://graphviz.org/).
<span style="text-decoration:underline">Note:</span> On Mac OS X, [Pixelglow](http://www.pixelglow.com/graphviz/) is a nice a front-end, you can even see the graph being built in real-time.
### Using pd_machviz to generate a graph
The <span style="font-style:italic">[pd_machviz](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/pd_machviz)</span> tool is available in the [svn/hg trunk](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/).
#### A simple example across otool dependencies
A hierarchical view:

[![](../../_/rsrc/1224966874878/developers/otool/mach-o-dependencies-overview/otool.dot_directed.png)](mach-o-dependencies-overview/otool.dot_directed.png%3Fattredirects=0)

The corresponding script output:

<div style="font-family:courier new,monospace">
<span style="font-size:small">./pd_machviz /usr/bin/otool</span>
<div style="font-family:courier new,monospace">

<div style="font-family:courier new,monospace">
<span style="font-size:small">Generate dependencies graphs of /usr/bin/otool</span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> Legend:</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 1</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> + foo</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`- bar                                             No more dependency</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ baz impure! /Blocker_1 -&gt; file_involved_1       Impurity detected</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ baz impure! /Blocker_. -&gt; file_involved_.       Impurity detected</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ baz impure! /Blocker_n -&gt; file_involved_n       Impurity detected</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ baz                                             Dependency found</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`. qux                                           Cached file (Already processed)</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">Now generating dependencies tree, please wait...</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 1</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> + /usr/bin/otool</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`+ /usr/lib/libgcc_s.1.dylib</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 3</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> | |`+ /usr/lib/libSystem.B.dylib</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 4</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> | | |`- /usr/lib/system/libmathCommon.A.dylib</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)"> 2</span></span><span style="white-space:pre"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span><span style="font-size:small"><span style="color:rgb(68,68,68)"> |`. /usr/lib/libSystem.B.dylib</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">Generation of otool.dot complete.</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">Now drawing graphs from otool.dot, please wait...</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">Generation of otool.dot_directed.png complete.</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">Generation of otool.dot_circular.png complete.</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">Generation of otool.dot_radial.png complete.</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">Generation of otool.dot_undirected.png complete.</span></span>
<div style="font-family:courier new,monospace">
<span style="font-size:small"><span style="color:rgb(68,68,68)">Generation of otool.dot_undirectedBIS.png complete.</span></span>
#### A circular view of xterm dependencies

[![](../../_/rsrc/1224967011322/developers/otool/mach-o-dependencies-overview/xterm.dot_circular.png%3Fheight=346&width=420)](mach-o-dependencies-overview/xterm.dot_circular.png%3Fattredirects=0)
#### Checking for purity in passwd

[![](../../_/rsrc/1233266186202/developers/otool/mach-o-dependencies-overview/passwd.dot_undirectedBIS.png%3Fheight=420&width=399)](mach-o-dependencies-overview/passwd.dot_undirectedBIS.png%3Fattredirects=0)

### Resources {style="margin:10px 10px 10px 0px;background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:18px"}
[http://www.graphviz.org](http://www.graphviz.org/)
the [otool](../otool.html) page

