Universal binaries
==================

<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](../_/rsrc/1227613163252/developers/universal-binaries/175px-Universal_Binary_Logo.png%3Fheight=200&width=147)](universal-binaries/175px-Universal_Binary_Logo.png%3Fattredirects=0)
Mac OS X and Darwin can use so-called Mach-O (Mach Object) "fat" files, or universal binaries that contain code for more than one architecture, e.g., ppc and i386.
PureDarwin, however, currently uses i386 only (also referred to as "x86") but hopes to use x86_64 a day and future architectures.
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:350px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Finding and removing files that have no i386 code](universal-binaries.html#TOC-Finding-and-removing-files-that-have-no-i386-code)
2.  [**2** Example](universal-binaries.html#TOC-Example)
3.  [**3** Mach](universal-binaries.html#TOC-Mach)
    1.  [**3.1** What is Mach-o?](universal-binaries.html#TOC-What-is-Mach-o-)
    2.  [**3.2** Where does it come from?](universal-binaries.html#TOC-Where-does-it-come-from-)
    3.  [**3.3** What does it specify?](universal-binaries.html#TOC-What-does-it-specify-)
    4.  [**3.4** Structure](universal-binaries.html#TOC-Structure)
4.  [**4** References](universal-binaries.html#TOC-References)

### Finding and removing files that have no i386 code
The command-line tool <span style="font-family:courier new,monospace"><span style="font-size:small">lipo</span></span> can be used to inspect and modify the architecture-related aspects of executable files and libraries.

To find ppc-only files, you can use


<span style="font-family:courier new,monospace"><span style="font-size:small">find /some/path -exec lipo -i {} 2&gt;&1 ; | grep ppc | grep -v i386</span></span>

Since the PureDarwin project currently supports only the i386 platform, you should be able to safely delete files found by the command above.
### Example
The old UNIX <span style="font-family:courier new,monospace"><span style="font-size:small">file</span></span> command is also useful to determine fat file types.


<span style="font-family:courier new,monospace"><span style="font-size:small">file /usr/lib/libedit.2.dylib </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libedit.2.dylib: Mach-O universal binary with 4 architectures</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libedit.2.dylib (for architecture ppc7400):</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Mach-O dynamically linked shared library ppc</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libedit.2.dylib (for architecture ppc64):</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Mach-O 64-bit dynamically linked shared library ppc64</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libedit.2.dylib (for architecture i386):</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Mach-O dynamically linked shared library i386</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libedit.2.dylib (for architecture x86_64):</span></span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Mach-O 64-bit dynamically linked shared library x86_64</span></span></span>

Then we use <span style="font-family:courier new,monospace"><span style="font-size:small">lipo</span></span>. Compare the size before thin (565K) and after (128K).
### Mach
From /usr/share/file/magic:


<span style="font-family:courier new,monospace"><span style="font-size:small"># mach file description</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">#</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># Since Java bytecode and Mach-O universal binaries have the same magic number the test</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># must be preformed in the same "magic" sequence to get both right.  The long</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># at offset 4 in a universal binary tells the number of architectures.  The short at</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># offset 4 in a Java bytecode file is the compiler minor version and the</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># short at offset 6 is the compiler major version.  Since there are only </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># only 18 labeled Mach-O architectures at current, and the first released </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># Java class format was version 43.0, we can safely choose any number</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># between 18 and 39 to test the number of architectures against</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># (and use as a hack).</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">0</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">belong&0xfffffffe</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">0xfeedface</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">Mach-O</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>
#### What is Mach-o?
-   A file format
-   An ABI (Application Binary Interface)
#### Where does it come from?
OSF ([Open Software Foundation](http://en.wikipedia.org/wiki/Open_Software_Foundation)) for mach kernel.
#### What does it specify?
-   Processus address space
-   Dynamic loader to use
-   Shared library to load
#### Structure
+--------------------------------------------------------------------------+
| <span style="font-weight:bold"> Header                                 |
| </span>                                                                  |
+--------------------------------------------------------------------------+
| <span style="font-weight:bold"> Load commands                          |
| </span>                                                                  |
|   ---------------------                                                  |
|    Segment command 1                                                    |
|    Segment command 2                                                    |
|   ---------------------                                                  |
+--------------------------------------------------------------------------+
| <span style="font-weight:bold"> Raw data                               |
| </span>                                                                  |
| +--------------------------------------+-------------------------------- |
| ------+                                                                  |
| |  Segment 1                          |   -------------                 |
|       |                                                                  |
| |                                      |    Section 1                   |
|       |                                                                  |
| |                                      |    Section 2                   |
|       |                                                                  |
| |                                      |    Section 3                   |
|       |                                                                  |
| |                                      |   -------------                 |
|       |                                                                  |
| +--------------------------------------+-------------------------------- |
| ------+                                                                  |
| |  Segment 2                          |   -------------                 |
|       |                                                                  |
| |                                      |    Section 4                   |
|       |                                                                  |
| |                                      |    ...                         |
|       |                                                                  |
| |                                      |    Section n                   |
|       |                                                                  |
| |                                      |   -------------                 |
|       |                                                                  |
| +--------------------------------------+-------------------------------- |
| ------+                                                                  |
+--------------------------------------------------------------------------+

### References
<http://developer.apple.com/documentation/DeveloperTools/Conceptual/MachOTopics/introduction.html> 
<http://developer.apple.com/documentation/DeveloperTools/Conceptual/MachORuntime/Reference/reference.html> 

<http://en.wikipedia.org/wiki/Mach-O> 


<http://developer.apple.com/documentation/DeveloperTools/Conceptual/DynamicLibraries/Introduction.html> 

<http://en.wikipedia.org/wiki/Universal_Binaries>

<span style="font-family:courier new,monospace"><span style="font-size:small">man otool</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">man dyld</span></span>
<span style="font-family:courier new;font-size:12px">man Mach-o</span>

