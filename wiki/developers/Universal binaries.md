Universal binaries
==================

<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
![](/img/developers/universal-binaries/175px-Universal_Binary_Logo.png)
Mac OS X and Darwin can use so-called Mach-O (Mach Object) "fat" files, or universal binaries that contain code for more than one architecture, e.g., ppc and i386.
PureDarwin, however, currently uses i386 only (also referred to as "x86") but hopes to use x86_64 a day and future architectures.

### Finding and removing files that have no i386 code
The command-line tool `lipo` can be used to inspect and modify the architecture-related aspects of executable files and libraries.

To find ppc-only files, you can use


<span style="font-family:courier new,monospace"><span style="font-size:small">find /some/path -exec lipo -i {} 2&gt;&1 ; | grep ppc | grep -v i386</span></span>

Since the PureDarwin project currently supports only the i386 platform, you should be able to safely delete files found by the command above.
### Example
The old UNIX `file` command is also useful to determine fat file types.


`file /usr/lib/libedit.2.dylib `
`/usr/lib/libedit.2.dylib: Mach-O universal binary with 4 architectures`
`/usr/lib/libedit.2.dylib (for architecture ppc7400):` `Mach-O dynamically linked shared library ppc`
`/usr/lib/libedit.2.dylib (for architecture ppc64):` `Mach-O 64-bit dynamically linked shared library ppc64`
`/usr/lib/libedit.2.dylib (for architecture i386):` `Mach-O dynamically linked shared library i386`
`/usr/lib/libedit.2.dylib (for architecture x86_64):` `Mach-O 64-bit dynamically linked shared library x86_64`

Then we use `lipo`. Compare the size before thin (565K) and after (128K).
### Mach
From /usr/share/file/magic:


`# mach file description`
`#`
`# Since Java bytecode and Mach-O universal binaries have the same magic number the test`
`# must be preformed in the same "magic" sequence to get both right.  The long`
`# at offset 4 in a universal binary tells the number of architectures.  The short at`
`# offset 4 in a Java bytecode file is the compiler minor version and the`
`# short at offset 6 is the compiler major version.  Since there are only `
`# only 18 labeled Mach-O architectures at current, and the first released `
`# Java class format was version 43.0, we can safely choose any number`
`# between 18 and 39 to test the number of architectures against`
`# (and use as a hack).`
`[...]`

`0` <span style="font-family:courier new,monospace"><span style="font-size:small">belong&0xfffffffe</span></span> `0xfeedface` `Mach-O`
`[...]`
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
| ** Header                                 |
| **                                                                  |
+--------------------------------------------------------------------------+
| ** Load commands                          |
| **                                                                  |
|   ---------------------                                                  |
|    Segment command 1                                                    |
|    Segment command 2                                                    |
|   ---------------------                                                  |
+--------------------------------------------------------------------------+
| ** Raw data                               |
| **                                                                  |
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

`man otool`
`man dyld`
man Mach-o

