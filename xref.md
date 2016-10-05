xref
====
The xref database by [DarwinBuild](../darwinbuild.html) is roughly the equivalent to a package manager database on other systems.
 This page is intended to describe what is in the xref database, and how to use it.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** xref.db file format](xref.html#TOC-xref.db-file-format)
2.  [**2** darwinxref](xref.html#TOC-darwinxref)
    1.  [**2.1** darwinxref binary_sites](xref.html#TOC-darwinxref-binary_sites)
    2.  [**2.2** darwinxref source_sites](xref.html#TOC-darwinxref-source_sites)
    3.  [**2.3** darwinxref patchfiles](xref.html#TOC-darwinxref-patchfiles)
    4.  [**2.4** darwinxref dependencies](xref.html#TOC-darwinxref-dependencies)
    5.  [**2.5** darwinxref plug-ins](xref.html#TOC-darwinxref-plug-ins)
3.  [**3** Contents of xref.db](xref.html#TOC-Contents-of-xref.db)


### xref.db file format
The file xref.db is located in the .build directory of your [DarwinBuild](../darwinbuild.html) working directory (the one that contains BuildRoot, among other things). It is a mysql3 database file, which makes it convenient to open end edit using mysql3 (which comes with Leopard):


<span style="font-family:courier new,monospace"><span style="font-size:small">sqlite3 .build/xref.db</span></span>


You can now use sqlite SQL commands. However, you should limit yourself to read operations.
### darwinxref
darwinxref is the command line client for the xref database that comes with DarwinBuild. It abstracts from the actual sqlite3 commands. 

For example, to get a list of all the files contained in your BuildRoot and which projects they belong to, do:

<span style="font-family:courier new,monospace"><span style="font-size:small">darwinxref exportFiles &gt; darwinxref.exportFiles.txt</span></span>


This is handy to keep around.
<span style="font-weight:normal"> </span>
#### darwinxref binary_sites {style="color:rgb(0,0,0);margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
This command shows the URL(s) from which binary roots are tried to be downloaded. For example:

<span style="font-family:courier new;font-size:12px">darwinxref binary_sites</span>
<span style="font-family:courier new;font-size:12px">http://src.macosforge.org/Roots/9A581/</span>
<span style="font-family:courier new;font-size:12px">
 </span>
<span style="font-size:12px"><span style="font-family:inherit">Since each individual project can specify additional binary_sites, you can also pass the name of a certain project to it:</span></span>
<span style="font-size:12px">
 </span>
<span style="font-size:12px"><span style="font-size:13px"> </span></span>
<span style="font-family:courier new;font-size:12px">darwinxref binary_sites xnu</span>
<span style="font-family:courier new;font-size:12px">http://src.macosforge.org/Roots/9A581/</span>
<span style="font-family:courier new;font-size:12px">http://some.more.specific.to.xnu</span>
#### darwinxref source_sites
This command shows the URL(s) from which source packages are tried to be downloaded. For example:

<span style="font-family:courier new,monospace"><span style="font-size:small">darwinxref source_sites</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">http://src.macosforge.org/Projects/</span></span>


<span style="font-size:12px">Since each individual project can specify additional binary_sites, you can also pass the name of a certain project to it as in the binary_sites example.</span>
#### darwinxref patchfiles
Shows [patchfiles](patchfiles.html) that will be applied to a project, if any. For Example:

<span style="font-family:courier new,monospace"><span style="font-size:small">sh-3.2# darwinxref patchfiles xnu</span></span>

(more text to be written)
#### darwinxref dependencies
Shows build-time or run-time dependencies of a given project, For example:

<span style="font-family:courier new,monospace"><span style="font-size:small">sh-3.2# darwinxref dependencies -build boot</span></span>

shows a (recursive) list of build-time dependencies of the boot project.

(more text to be written)
#### darwinxref plug-ins
darwinxref functionality can be extended by plug-ins. See [descrip.txt](http://darwinbuild.macosforge.org/trac/browser/trunk/darwinxref/plugins/descrip.txt) for the currently available ones.
### Contents of xref.db
The xref database contains the following tables, with the following fields:

files 
-   build
-   project
-   path
groups 
-   build
-   name
-   member
mach_o_objects 
-   serial
-   magic
-   type
-   cputype
-   cpusubtype
-   flags
-   build
-   project
-   path
mach_o_symbols
-   mach_o_object
-   type
-   value
-   name
properties
-   build 
-   project
-   property
-   key
-   value
unresolved_dependencies
-   build
-   project
-   type
-   dependency

To be continued
Would it make sense to base a package manager on xref.db, [darwinup](http://darwinbuild.macosforge.org/trac/browser/trunk/darwinup/NOTES) and some package format like xar?

