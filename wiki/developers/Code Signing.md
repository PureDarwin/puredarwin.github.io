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

On Darwin, you can quickly check for the presence of a code signature with otool -l /YourBinaryOfChoice` | grep LC_CODE_SIGNATURE`. You're looking for the "cmd LC_CODE_SIGNATURE" line (regardless of whether or not you decided to *grep*).
 Without grepping, output similar to the following is produced:

 Load command 13`
`` `cmd LC_CODE_SIGNATURE`
`` `cmdsize 16`
`` `dataoff 574`704``
`` ``datasize 7968``
`
 The binary used in the example above was (naturally) *otool* from Mac OS X Leopard.
### Other ways
strings YourBinaryOfChoice | grep "Apple Code Signing Certification Authority"



or





`grep -b `"Apple Code Signing Certification Authority"` YourBinaryOfChoice`
### Examples on Mac OS X

#### Inspecting otool

`codesign -dvvvv /usr/bin/otool `
`Executable=/usr/bin/otool`
`Identifier=com.apple.otool`
`Format=Mach-O universal (i386 ppc7400)`
`CodeDirectory v=20001 size=2920 flags=0x0(none) hashes=141+2 location=embedded`
`CDHash=ea392676d34975966fcc4471c3d85dee70978255`
`Signature size=4064`
`Authority=Software Signing`
`Authority=Apple Code Signing Certification Authority`
`Authority=Apple Root CA`
`Info.plist=not bound`
`Sealed Resources=none`
`Internal requirements count=0 size=12`

The Apple object file utility shipped with Mac OS X is signed, in the contrary of the one built from DarwinBuild.


`codesign -dvvvv /Volumes/Builds/9F33/BuildRoot/usr/bin/otool `
`/Volumes/Builds/9F33/BuildRoot/usr/bin/otool: code object is not signed`


__Note:__ No "impurity" detected at 'codesign' inspection with 'otool', so perhaps it could be build with the DarwinBuild project and be available in PureDarwin.
#### Verifying the dynamic validity of a process
In this example, we will take 'launchd' process, which also run as an 'init' replacement.

`ps ux -p1`
`USER   PID %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND`
`root     1   0.0  0.0   600820    552   ??  Ss    9:46PM   0:00.42 /sbin/launchd`


`codesign -vvvv 1`
`1: dynamically valid`
`1: satisfies its Designated Requirement`


__Note:__ The "-h" options seems not (yet) documented but remains functional:

`codesign -h 1`
`/sbin/launchd`
`/mach_kernel`


Miscellaneous
-------------
Related fields found in Xcode:

![](/img/developers/universal-binaries/code-signing/Xcode%20codesign%20options.png)

Resources
---------
[Apple Technical Note TN2206: Mac OS X Code Signing In Depth](http://www.webcitation.org/query?url=http%3A%2F%2Fdeveloper.apple.com%2Ftechnotes%2Ftn2007%2Ftn2206.html&date=2008-10-11)
The Apple Mac OS X 10.5 codesign Manual Page is attached to this page (PDF)
[Sun Solaris 10 elfsign(1) Manual Page](http://www.webcitation.org/query?url=http%3A%2F%2Fdocs.sun.com%2Fapp%2Fdocs%2Fdoc%2F819-2239%2Felfsign-1%3Fa%3Dview&date=2008-10-11)

`man codesign`
`man csreq`
