Code Signing
============

This page is about binary signature.

Background
----------
As of Mac OS X and Darwin, a Mach-O code signature system (similar in concept to Microsoft AuthentiCode for PE binaries on Windows, and Solaris ELF signing) has been implemented. At least on Darwin, this system is not "formally" used, and no binaries are signed.

On Mac OS X, the code signature system forms part of the basis of the "Seatbelt" GPC (Granular Process Control)/RBAC (Role Based Access Control) mechanism (an implementation detail of the Parental Control feature), and most binaries shipped are signed.

I've got a binary, is it signed?
--------------------------------
There are probably many ways of checking if a binary is signed on Darwin (although some techniques could also be possible on other operating systems), and Mac OS X ships with tools for checking code signatures.

### The otool Way

On Darwin, you can quickly check for the presence of a code signature with <span style="font-size:small">otool -l /YourBinaryOfChoice</span><span style="font-family:courier new,monospace"><span style="font-size:small"> | grep LC_CODE_SIGNATURE</span></span>. You're looking for the "<span style="font-size:small">cmd LC_CODE_SIGNATURE</span><span style="font-family:arial,sans-serif">"</span> line (regardless of whether or not you decided to <span style="font-style:italic">grep</span>).
 Without grepping, output similar to the following is produced:

 <span><span style="font-family:courier new,monospace"><span style="font-size:small">Load command 13</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">cmd LC_CODE_SIGNATURE</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">cmdsize 16</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">dataoff 574</span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">704</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">datasize 7968</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
 The binary used in the example above was (naturally) <span style="font-style:italic">otool</span> from Mac OS X Leopard.</span>
### Other ways
<span><span style="font-family:courier new,monospace"><span style="font-size:small">strings YourBinaryOfChoice | grep "Apple Code Signing Certification Authority"
</span></span></span>
<span style="font-family:courier new;font-size:12px">
</span>
or
<div style="font-family:courier new,monospace">
<span style="font-size:12px">
</span>
<div style="font-family:courier new,monospace">
<span style="font-size:12px"><span style="font-size:13px"></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">grep -b </span></span><span><span><span style="font-family:courier new,monospace"><span style="font-size:small">"Apple Code Signing Certification Authority"</span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> YourBinaryOfChoice</span></span>
### Examples on Mac OS X
<span style="font-family:arial,sans-serif"><span style="font-size:small">On Mac OS X, the `codesign' binary "<span style="font-style:italic">is used to create, check, and display code signatures, as well as inquire into the dynamic status of signed code in the system.</span>" according to the man description.</span></span>
#### Inspecting otool
<span style="font-family:arial"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">codesign -dvvvv /usr/bin/otool </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Executable=/usr/bin/otool</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Identifier=com.apple.otool</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Format=Mach-O universal (i386 ppc7400)</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">CodeDirectory v=20001 size=2920 flags=0x0(none) hashes=141+2 location=embedded</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">CDHash=ea392676d34975966fcc4471c3d85dee70978255</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Signature size=4064</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Authority=Software Signing</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Authority=Apple Code Signing Certification Authority</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Authority=Apple Root CA</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Info.plist=not bound</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Sealed Resources=none</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Internal requirements count=0 size=12</span></span></span>

The Apple object file utility shipped with Mac OS X is signed, in the contrary of the one built from DarwinBuild.


<span style="font-family:courier new,monospace"><span style="font-size:small">codesign -dvvvv /Volumes/Builds/9F33/BuildRoot/usr/bin/otool </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/Volumes/Builds/9F33/BuildRoot/usr/bin/otool: code object is not signed</span></span></span>


<span style="text-decoration:underline">Note:</span> No "impurity" detected at `codesign' inspection with `otool', so perhaps it could be build with the DarwinBuild project and be available in PureDarwin.
#### Verifying the dynamic validity of a process
In this example, we will take `launchd' process, which also run as an `init' replacement.

<span style="font-family:courier new,monospace"><span style="font-size:small">ps ux -p1</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">USER   PID %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">root     1   0.0  0.0   600820    552   ??  Ss    9:46PM   0:00.42 /sbin/launchd</span></span></span>


<span style="font-family:courier new,monospace"><span style="font-size:small">codesign -vvvv 1</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">1: dynamically valid</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">1: satisfies its Designated Requirement</span></span></span>
<span style="color:rgb(68,68,68);font-family:courier new;font-size:12px"><span style="color:rgb(0,0,0);font-family:arial;font-size:13px"></span></span>

<span style="text-decoration:underline">Note:</span> The "-h" options seems not (yet) documented but remains functional:

<span style="font-family:courier new,monospace"><span style="font-size:small">codesign -h 1</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/sbin/launchd</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/mach_kernel</span></span></span>


Miscellaneous
-------------
<span style="font-family:arial"><span style="font-size:small">Related fields found in Xcode:</span></span>

[![](../../_/rsrc/1227919887971/developers/universal-binaries/code-signing/Xcode%20codesign%20options.png)](code-signing/Xcode%20codesign%20options.png%3Fattredirects=0)

Resources
---------
[Apple Technical Note TN2206: Mac OS X Code Signing In Depth](http://www.webcitation.org/query?url=http%3A%2F%2Fdeveloper.apple.com%2Ftechnotes%2Ftn2007%2Ftn2206.html&date=2008-10-11)
The Apple Mac OS X 10.5 codesign Manual Page is attached to this page (PDF)
[Sun Solaris 10 elfsign(1) Manual Page](http://www.webcitation.org/query?url=http%3A%2F%2Fdocs.sun.com%2Fapp%2Fdocs%2Fdoc%2F819-2239%2Felfsign-1%3Fa%3Dview&date=2008-10-11)

<span style="font-family:courier new,monospace"><span style="font-size:small">man codesign</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">man csreq</span></span>
