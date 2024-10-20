xref
====
The xref database by [DarwinBuild](../darwinbuild.html) is roughly the equivalent to a package manager database on other systems.
This page is intended to describe what is in the xref database, and how to use it.

### xref.db file format
The file xref.db is located in the .build directory of your [DarwinBuild](../darwinbuild.html) working directory (the one that contains BuildRoot, among other things). It is a mysql3 database file, which makes it convenient to open end edit using mysql3 (which comes with Leopard):


`sqlite3 .build/xref.db`


You can now use sqlite SQL commands. However, you should limit yourself to read operations.
### darwinxref
darwinxref is the command line client for the xref database that comes with DarwinBuild. It abstracts from the actual sqlite3 commands. 

For example, to get a list of all the files contained in your BuildRoot and which projects they belong to, do:

`darwinxref exportFiles > darwinxref.exportFiles.txt`


This is handy to keep around.
 
#### darwinxref binary_sites {style="color:rgb(0,0,0);margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
This command shows the URL(s) from which binary roots are tried to be downloaded. For example:

darwinxref binary_sites
http://src.macosforge.org/Roots/9A581/
<span style="font-family:courier new;font-size:12px">
 </span>
Since each individual project can specify additional binary_sites, you can also pass the name of a certain project to it:
<span style="font-size:12px">
 </span>
 
darwinxref binary_sites xnu
http://src.macosforge.org/Roots/9A581/
http://some.more.specific.to.xnu
#### darwinxref source_sites
This command shows the URL(s) from which source packages are tried to be downloaded. For example:

`darwinxref source_sites`
`http://src.macosforge.org/Projects/`


Since each individual project can specify additional binary_sites, you can also pass the name of a certain project to it as in the binary_sites example.
#### darwinxref patchfiles
Shows [patchfiles](patchfiles.html) that will be applied to a project, if any. For Example:

`sh-3.2# darwinxref patchfiles xnu`

(more text to be written)
#### darwinxref dependencies
Shows build-time or run-time dependencies of a given project, For example:

`sh-3.2# darwinxref dependencies -build boot`

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

