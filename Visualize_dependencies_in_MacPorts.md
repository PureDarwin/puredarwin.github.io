Visualize dependencies in MacPorts
==================================
<div style="margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px;display:inline;float:right">
<div style="display:block;margin-left:auto;text-align:right">
[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/graphviz.png)](macports-dependencies-overview/graphviz.png%3Fattredirects=0)


This page describes a way to track dependencies and related satellite information (e.g: as variants or blockers) in MacPorts.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:360px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Overview of dependencies, variants and blockers](macports-dependencies-overview.html#TOC-Overview-of-dependencies-variants-and-blockers)
    1.  [**1.1** Installing Graphviz](macports-dependencies-overview.html#TOC-Installing-Graphviz)
    2.  [**1.2** Using pd_portviz to generate a graph](macports-dependencies-overview.html#TOC-Using-pd_portviz-to-generate-a-graph)
        1.  [**1.2.1** Preliminary](macports-dependencies-overview.html#TOC-Preliminary)
        2.  [**1.2.2** An example across rrdtool dependencies](macports-dependencies-overview.html#TOC-An-example-across-rrdtool-dependencies)
        3.  [**1.2.3** Purity?](macports-dependencies-overview.html#TOC-Purity-)
    3.  [**1.3** Miscellaneous](macports-dependencies-overview.html#TOC-Miscellaneous)
2.  [**2** Ressources](macports-dependencies-overview.html#TOC-Ressources)

<span style="font-size:18px">O</span>verview of dependencies, variants and blockers
-----------------------------------------------------------------------------------
[Graphviz](http://www.graphviz.org/) is an opensource graph visualization software from AT&T Laboratories and Bell Laboratories (Lucent Technologies).
#### Installing Graphviz {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
Not so common to beginning (instead of ending) with a "snake eating his tail", we will use <span style="font-style:italic">graphviz</span> from MacPorts to track dependencies and other information.
 
<span style="font-family:courier new,monospace"><span style="font-size:small">port install graphviz +the_variants_you_need</span></span>

or grab and compile the source from [graphviz.org](http://graphviz.org/).

<span style="text-decoration:underline">Note:</span> On Mac OS X, [Pixelglow](http://www.pixelglow.com/graphviz/) is a nice a front-end, you can even see the graph being built in real-time.
### Using pd_portviz to generate a graph
The <span style="font-style:italic">[pd_portviz](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/pd_portviz)</span> tool is available in the [svn or hg trunk](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/) location.
#### Preliminary {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
A rudimentary legend is generated in the DOT language:

[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/portviz%20legend.png)](macports-dependencies-overview/portviz%20legend.png%3Fattredirects=0)

Three kinds of dependencies can be found in MacPorts:
-   Build dependencies
-   Library dependencies
-   Runtime dependencies
Sometimes there isn't any dependency, or the port is not installed ("Not here" in the legend), so we cannot scrutinize the content since there is no content.
When a port is already installed, the content is examined in order to find and count "[current blocker](../../blockers.html)".
Also, notice any variant explicitly given will be detected (if available) and highlighted on any dependencies.
#### An example across rrdtool dependencies
An example of hierarchical overview of <span style="font-style:italic">rrdtool</span> dependencies, where <span style="font-style:italic">glib2</span> (18 problematic objects) is identified as "impure":

Here the current script output:



<span style="font-family:courier new,monospace"><span style="font-size:small">./pd_portviz.sh rrdtool +puredarwin</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span>

<span style="color:rgb(68,68,68);font-family:courier new;font-size:12px"></span>
Generate dependencies graphs of rrdtool +puredarwin


 Legend:

 1<span style="white-space:pre"> </span> + foo (variant_x1, ..., variant_xn)

 2<span style="white-space:pre"> </span> |`. bar (variant_y1, ..., variant_yn)               No dependency found

 2<span style="white-space:pre"> </span> |`+ baz <span style="font-weight:bold">impure</span><span style="font-weight:bold">!</span> /Blocker_1 -&gt; file_involved_1       Impurity detected

 2<span style="white-space:pre"> </span> |`+ baz <span style="font-weight:bold">impure</span><span style="font-weight:bold">!</span> /Blocker_. -&gt; file_involved_.       Impurity detected

 2<span style="white-space:pre"> </span> |`+ baz <span style="font-weight:bold">impure!</span> /Blocker_n -&gt; file_involved_n       Impurity detected

 2<span style="white-space:pre"> </span> |`+ baz (variant_z1, ..., variant_zn)               Has Dependenc{y|ies}

 3<span style="white-space:pre"> </span> | |`- dependency_bar ()                             Already processed


Now generating dependencies tree and checking for ``purity'', please wait...


 1<span style="white-space:pre"> </span> + rrdtool (universal python)

 2<span style="white-space:pre"> </span> |`. XFree86 (darwin puredarwin macosx)

 2<span style="white-space:pre"> </span> |`+ xrender (universal)

 3<span style="white-space:pre"> </span> | |`- XFree86 ()

 3<span style="white-space:pre"> </span> | |`+ render ()

 4<span style="white-space:pre"> </span> | | |`. pkgconfig (universal darwin_6)

 2<span style="white-space:pre"> </span> |`. expat (universal no_static examples)

 2<span style="white-space:pre"> </span> |`+ fontconfig (universal doc vera macosx)

 3<span style="white-space:pre"> </span> | |`+ libiconv (universal darwin_7 darwin_8 freebsd linux disable_utf8mac disable_extra_encodings enable_cp932fix)

 4<span style="white-space:pre"> </span> | | |`. gperf (universal)

 3<span style="white-space:pre"> </span> | |`- expat ()

 3<span style="white-space:pre"> </span> | |`+ freetype (universal bytecode doc)

 4<span style="white-space:pre"> </span> | | |`. zlib (universal examples)

 2<span style="white-space:pre"> </span> |`- freetype ()

 2<span style="white-space:pre"> </span> |`+ glib2 (universal puredarwin darwin powerpc darwin_6 darwin_9)

 3<span style="white-space:pre"> </span> | |`- pkgconfig ()

 3<span style="white-space:pre"> </span> | |`+ gettext (universal darwin_6)

 4<span style="white-space:pre"> </span> | | |`- libiconv ()

 4<span style="white-space:pre"> </span> | | |`+ ncurses (universal freebsd)

 5<span style="white-space:pre"> </span> | | | |`. ncursesw (universal)

 4<span style="white-space:pre"> </span> | | |`- expat ()

 3<span style="white-space:pre"> </span> | |`- libiconv ()

 3<span style="white-space:pre"> </span> | |`. perl5.8 (darwin threads shared darwin_8 darwin_9)

 2<span style="white-space:pre"> </span> |`- libiconv ()

 2<span style="white-space:pre"> </span> |`- gettext ()

 2<span style="white-space:pre"> </span> |`+ pango (universal no_x11)

 3<span style="white-space:pre"> </span> | |`- pkgconfig ()

 3<span style="white-space:pre"> </span> | |`- glib2 ()

 3<span style="white-space:pre"> </span> | |`- XFree86 ()

 3<span style="white-space:pre"> </span> | |`+ Xft2 (universal)

 4<span style="white-space:pre"> </span> | | |`- pkgconfig ()

 4<span style="white-space:pre"> </span> | | |`+ xorg-xproto ()

 5<span style="white-space:pre"> </span> | | | |`+ xorg-util-macros ()

 6<span style="white-space:pre"> </span> | | | | |`- pkgconfig ()

 4<span style="white-space:pre"> </span> | | |`- zlib ()

 4<span style="white-space:pre"> </span> | | |`- xrender ()

 4<span style="white-space:pre"> </span> | | |`- freetype ()

 4<span style="white-space:pre"> </span> | | |`- fontconfig ()

 4<span style="white-space:pre"> </span> | | |`- expat ()

 3<span style="white-space:pre"> </span> | |`+ cairo (universal glitz no_x11 macosx)

 4<span style="white-space:pre"> </span> | | |`- pkgconfig ()

 4<span style="white-space:pre"> </span> | | |`. libpixman (universal)

 4<span style="white-space:pre"> </span> | | |`- xrender ()

 4<span style="white-space:pre"> </span> | | |`- fontconfig ()

 4<span style="white-space:pre"> </span> | | |`- freetype ()

 4<span style="white-space:pre"> </span> | | |`+ libpng (universal)

 5<span style="white-space:pre"> </span> | | | |`- zlib ()

 4<span style="white-space:pre"> </span> | | |`- render ()

 4<span style="white-space:pre"> </span> | | |`- zlib ()

 4<span style="white-space:pre"> </span> | | |`- expat ()

 3<span style="white-space:pre"> </span> | |`- fontconfig ()

 2<span style="white-space:pre"> </span> |`- cairo ()

 2<span style="white-space:pre"> </span> |`- perl5.8 ()

 2<span style="white-space:pre"> </span> |`. tcl (universal threads memdebug)

 2<span style="white-space:pre"> </span> |`- zlib ()

 2<span style="white-space:pre"> </span> |`- libpng ()

 2<span style="white-space:pre"> </span> |`+ libxml2 (universal debug)

 3<span style="white-space:pre"> </span> | |`- libiconv ()

 3<span style="white-space:pre"> </span> | |`- zlib ()


Generation of rrdtool.dot complete.


Now drawing graphs from rrdtool.dot, please wait...

Generation of rrdtool_directed.png complete.

Generation of rrdtool_circular.png complete.

Generation of rrdtool_radial.png complete.

Generation of rrdtool_undirected.png complete.

Generation of rrdtool_undirectedBIS.png complete.


The dot file, then five PNG graphs are generated.
-   rrdtool.dot
-   rrdtool_directed.png
-   rrdtool_circular.png
-   rrdtool_radial.png
-   rrdtool_undirected.png
-   rrdtool_undirectedBIS.png

The directed (hierarchical) view:

[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/rrdtool_directed.png%3Fheight=219&width=420)](macports-dependencies-overview/rrdtool_directed.png%3Fattredirects=0)


The circular view:

[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/rrdtool_circular.png%3Fheight=420&width=401)](macports-dependencies-overview/rrdtool_circular.png%3Fattredirects=0)


The radial view:


[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/rrdtool_radial.png%3Fheight=349&width=420)](macports-dependencies-overview/rrdtool_radial.png%3Fattredirects=0)


The first undirected view:

[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/rrdtool_undirected.png%3Fheight=372&width=420)](macports-dependencies-overview/rrdtool_undirected.png%3Fattredirects=0)

The second undirected view:

[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/rrdtool_undirectedBIS.png%3Fheight=229&width=420)](macports-dependencies-overview/rrdtool_undirectedBIS.png%3Fattredirects=0)

#### Purity?
Here an example of impurities detected in a port:


<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + graphviz <span style="font-weight:bold">impure!</span> /ApplicationServices.framework -&gt; /Applications/MacPorts/Graphviz.app/Contents/Frameworks/graphviz.framework/graphviz </span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + graphviz <span style="font-weight:bold">impure!</span> /ApplicationServices.framework -&gt; /Applications/MacPorts/Graphviz.app/Contents/Frameworks/graphviz.framework/Versions/A/graphviz </span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + graphviz <span style="font-weight:bold">impure!</span> /Cocoa.framework -&gt; /Applications/MacPorts/Graphviz.app/Contents/MacOS/Graphviz </span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"> 1</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> + graphviz (universal darwin_6 darwin_7 darwin_8 darwin_9 guile lua ocaml perl php python ruby tcl smyrna no_pangocairo no_x11 gui)</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>


And the corresponding result:

[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/pd_portviz%20graphviz%20radial.png%3Fheight=380&width=420)](macports-dependencies-overview/pd_portviz%20graphviz%20radial.png%3Fattredirects=0)



Also, see the [purity checking](purity.html) page.


### Miscellaneous
Illustration of irony?

[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/graphviz_undirectedBIS.png%3Fheight=304&width=420)](macports-dependencies-overview/graphviz_undirectedBIS.png%3Fattredirects=0)


Why is it hard to compile a "pure" <span style="font-style:italic">kde3</span>?


[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/pd_portviz%20kde_directed.png%3Fheight=267&width=420)](macports-dependencies-overview/pd_portviz%20kde_directed.png%3Fattredirects=0)

Why is it also hard to compile a "pure" <span style="font-style:italic">gnome?</span>

[![](../../_/rsrc/1224167778940/developers/macports/macports-dependencies-overview/pd_portviz%20gnome_directed.png%3Fheight=119&width=420)](macports-dependencies-overview/pd_portviz%20gnome_directed.png%3Fattredirects=0)
Ressources
----------
<http://www.graphviz.org> 

