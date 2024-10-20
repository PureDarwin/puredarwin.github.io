CFNetwork
=========

CFNetwork is a companion to CoreFoundation, and provides key networking features to applications.

While it was available as part of Darwin 8 (OS X 10.4), with the release of Darwin 9 (OS X 10.5) it became closed source. However, the source code for the last version released under Darwin 8 is still available from Apple, and with minor patching can be made to compile in the darwinbuild chroot.

CFNetwork is part of the CoreServices umbrella framework. CoreServices itself is a basic stub, existing solely to link to the framework under it.

Below as an attachement is a binary version of *CFNetwork.framework*, wrapped inside a *CoreServices.framework*.
Also included is the *CarbonCore.framework*, which contains only header files.

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/CoreServicesPureFoundation.png)

#### Status and testing to date

Code written, compiled and linked to CoreServices on OS X will run successfully on PureDarwinXmas.
The CFNetService type (the only part tested so far) operates correctly.

This software is covered by the [APSL](../legal/apsl.html).

#### Resources

Apple [Introduction to CFNetwork Programming Guide](http://developer.apple.com/DOCUMENTATION/Networking/Conceptual/CFNetwork/Introduction/chapter_1_section_1.html)
