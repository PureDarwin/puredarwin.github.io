Visualize dependencies in MacPorts
==================================
<div style="margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px;display:inline;float:right">
<div style="display:block;margin-left:auto;text-align:right">
![](/img/developers/macports/macports-dependencies-overview/graphviz.png)


This page describes a way to track dependencies and related satellite information (e.g: as variants or blockers) in MacPorts.

Overview of dependencies, variants and blockers
-----------------------------------------------------------------------------------
[Graphviz](http://www.graphviz.org/) is an opensource graph visualization software from AT&T Laboratories and Bell Laboratories (Lucent Technologies).
#### Installing Graphviz {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
Not so common to beginning (instead of ending) with a "snake eating his tail", we will use *graphviz* from MacPorts to track dependencies and other information.
 
`port install graphviz +the_variants_you_need`

or grab and compile the source from [graphviz.org](http://graphviz.org/).

__Note:__ On Mac OS X, [Pixelglow](http://www.pixelglow.com/graphviz/) is a nice a front-end, you can even see the graph being built in real-time.
### Using pd_portviz to generate a graph
The *[pd_portviz](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/pd_portviz)* tool is available in the [svn or hg trunk](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/) location.
#### Preliminary {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
A rudimentary legend is generated in the DOT language:

![](/img/developers/macports/macports-dependencies-overview/portviz%20legend.png)

Three kinds of dependencies can be found in MacPorts:
-   Build dependencies
-   Library dependencies
-   Runtime dependencies
Sometimes there isn't any dependency, or the port is not installed ("Not here" in the legend), so we cannot scrutinize the content since there is no content.
When a port is already installed, the content is examined in order to find and count "[current blocker](../../blockers.html)".
Also, notice any variant explicitly given will be detected (if available) and highlighted on any dependencies.
#### An example across rrdtool dependencies
An example of hierarchical overview of *rrdtool* dependencies, where *glib2* (18 problematic objects) is identified as "impure":

Here the current script output:



`./pd_portviz.sh rrdtool +puredarwin`

`
`


Generate dependencies graphs of rrdtool +puredarwin


 Legend:

 1  + foo (variant_x1, ..., variant_xn)

 2  |`. bar (variant_y1, ..., variant_yn)               No dependency found

 2  |`+ baz **impure****!** /Blocker_1 -&gt; file_involved_1       Impurity detected

 2  |`+ baz **impure****!** /Blocker_. -&gt; file_involved_.       Impurity detected

 2  |`+ baz **impure!** /Blocker_n -&gt; file_involved_n       Impurity detected

 2  |`+ baz (variant_z1, ..., variant_zn)               Has Dependenc{y|ies}

 3  | |`- dependency_bar ()                             Already processed


Now generating dependencies tree and checking for ``purity'', please wait...


 1  + rrdtool (universal python)

 2  |`. XFree86 (darwin puredarwin macosx)

 2  |`+ xrender (universal)

 3  | |`- XFree86 ()

 3  | |`+ render ()

 4  | | |`. pkgconfig (universal darwin_6)

 2  |`. expat (universal no_static examples)

 2  |`+ fontconfig (universal doc vera macosx)

 3  | |`+ libiconv (universal darwin_7 darwin_8 freebsd linux disable_utf8mac disable_extra_encodings enable_cp932fix)

 4  | | |`. gperf (universal)

 3  | |`- expat ()

 3  | |`+ freetype (universal bytecode doc)

 4  | | |`. zlib (universal examples)

 2  |`- freetype ()

 2  |`+ glib2 (universal puredarwin darwin powerpc darwin_6 darwin_9)

 3  | |`- pkgconfig ()

 3  | |`+ gettext (universal darwin_6)

 4  | | |`- libiconv ()

 4  | | |`+ ncurses (universal freebsd)

 5  | | | |`. ncursesw (universal)

 4  | | |`- expat ()

 3  | |`- libiconv ()

 3  | |`. perl5.8 (darwin threads shared darwin_8 darwin_9)

 2  |`- libiconv ()

 2  |`- gettext ()

 2  |`+ pango (universal no_x11)

 3  | |`- pkgconfig ()

 3  | |`- glib2 ()

 3  | |`- XFree86 ()

 3  | |`+ Xft2 (universal)

 4  | | |`- pkgconfig ()

 4  | | |`+ xorg-xproto ()

 5  | | | |`+ xorg-util-macros ()

 6  | | | | |`- pkgconfig ()

 4  | | |`- zlib ()

 4  | | |`- xrender ()

 4  | | |`- freetype ()

 4  | | |`- fontconfig ()

 4  | | |`- expat ()

 3  | |`+ cairo (universal glitz no_x11 macosx)

 4  | | |`- pkgconfig ()

 4  | | |`. libpixman (universal)

 4  | | |`- xrender ()

 4  | | |`- fontconfig ()

 4  | | |`- freetype ()

 4  | | |`+ libpng (universal)

 5  | | | |`- zlib ()

 4  | | |`- render ()

 4  | | |`- zlib ()

 4  | | |`- expat ()

 3  | |`- fontconfig ()

 2  |`- cairo ()

 2  |`- perl5.8 ()

 2  |`. tcl (universal threads memdebug)

 2  |`- zlib ()

 2  |`- libpng ()

 2  |`+ libxml2 (universal debug)

 3  | |`- libiconv ()

 3  | |`- zlib ()


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

![](/img/developers/macports/macports-dependencies-overview/rrdtool_directed.png)


The circular view:

![](/img/developers/macports/macports-dependencies-overview/rrdtool_circular.png)


The radial view:


![](/img/developers/macports/macports-dependencies-overview/rrdtool_radial.png)


The first undirected view:

![](/img/developers/macports/macports-dependencies-overview/rrdtool_undirected.png)

The second undirected view:

![](/img/developers/macports/macports-dependencies-overview/rrdtool_undirectedBIS.png)

#### Purity?
Here an example of impurities detected in a port:


`[...]`

` 1` ` + graphviz **impure!** /ApplicationServices.framework -> /Applications/MacPorts/Graphviz.app/Contents/Frameworks/graphviz.framework/graphviz `

` 1` ` + graphviz **impure!** /ApplicationServices.framework -> /Applications/MacPorts/Graphviz.app/Contents/Frameworks/graphviz.framework/Versions/A/graphviz `

` 1` ` + graphviz **impure!** /Cocoa.framework -> /Applications/MacPorts/Graphviz.app/Contents/MacOS/Graphviz `

` 1` ` + graphviz (universal darwin_6 darwin_7 darwin_8 darwin_9 guile lua ocaml perl php python ruby tcl smyrna no_pangocairo no_x11 gui)`

`[...]`


And the corresponding result:

![](/img/developers/macports/macports-dependencies-overview/pd_portviz%20graphviz%20radial.png)



Also, see the [purity checking](purity.html) page.


### Miscellaneous
Illustration of irony?

![](/img/developers/macports/macports-dependencies-overview/graphviz_undirectedBIS.png)


Why is it hard to compile a "pure" *kde3*?


![](/img/developers/macports/macports-dependencies-overview/pd_portviz%20kde_directed.png)

Why is it also hard to compile a "pure" *gnome?*

![](/img/developers/macports/macports-dependencies-overview/pd_portviz%20gnome_directed.png)
Ressources
----------
<http://www.graphviz.org> 

