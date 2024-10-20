Visualize mach-o dependencies
=============================
In the spirit of [Vizualize dependencies in MacPorts](../macports/macports-dependencies-overview.html) and [Vizualize KEXTs dependencies](../kexts/kexts-dependencies-overview.html), this page describes a way to track mach-o file dependencies and related satellite information (e.g: blockers).

### Prerequisites

[Graphviz](http://www.graphviz.org/) is an opensource graph visualization software from AT&T Laboratories and Bell Laboratories (Lucent Technologies).


port install graphviz +the_variants_you_need

or grab and compile the source from [graphviz.org](http://graphviz.org/).
__Note:__ On Mac OS X, [Pixelglow](http://www.pixelglow.com/graphviz/) is a nice a front-end, you can even see the graph being built in real-time.
### Using pd_machviz to generate a graph
The *[pd_machviz](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/pd_machviz)* tool is available in the [svn/hg trunk](http://code.google.com/p/puredarwin/source/browse/trunk/scripts/).
#### A simple example across otool dependencies
A hierarchical view:

![](/img/developers/otool/mach-o-dependencies-overview/otool.dot_directed.png)

The corresponding script output:


./pd_machviz /usr/bin/otool



Generate dependencies graphs of /usr/bin/otool




 Legend:

 1  + foo

 2  |`- bar                                             No more dependency

 2  |`+ baz impure! /Blocker_1 -> file_involved_1       Impurity detected

 2  |`+ baz impure! /Blocker_. -> file_involved_.       Impurity detected

 2  |`+ baz impure! /Blocker_n -> file_involved_n       Impurity detected

 2  |`+ baz                                             Dependency found

 3  | |`. qux                                           Cached file (Already processed)




Now generating dependencies tree, please wait...




 1  + /usr/bin/otool

 2  |`+ /usr/lib/libgcc_s.1.dylib

 3  | |`+ /usr/lib/libSystem.B.dylib

 4  | | |`- /usr/lib/system/libmathCommon.A.dylib

 2  |`. /usr/lib/libSystem.B.dylib

Generation of otool.dot complete.




Now drawing graphs from otool.dot, please wait...

Generation of otool.dot_directed.png complete.

Generation of otool.dot_circular.png complete.

Generation of otool.dot_radial.png complete.

Generation of otool.dot_undirected.png complete.

Generation of otool.dot_undirectedBIS.png complete.
#### A circular view of xterm dependencies

![](/img/developers/otool/mach-o-dependencies-overview/xterm.dot_circular.png)
#### Checking for purity in passwd

![](/img/developers/otool/mach-o-dependencies-overview/passwd.dot_undirectedBIS.png)

### Resources {style="margin:10px 10px 10px 0px;background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:18px"}
[http://www.graphviz.org](http://www.graphviz.org/)
the [otool](../otool.html) page

