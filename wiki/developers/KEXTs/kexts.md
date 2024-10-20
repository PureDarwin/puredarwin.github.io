Kernel Extensions (KEXTs)
=========================
Darwin kernel extensions (KEXT) are modules that provide aditional functionality to the kernel, e.g., in the form of device drivers.

### Minimal set of kexts needed

The kernel cannot boot at all (crashes) if there is not at least a certain set of KEXTs present.
The minimal set of KEXTs required to boot Darwin 9 from USB appears to be:

-   AppleACPIPlatform.kext
-   AppleAPIC.kext
-   AppleFileSystemDriver.kext
-   AppleRTC.kext
-   AppleSMBIOS.kext
-   IOACPIFamily.kext
-   IOATAFamily.kext
-   IOHIDFamily.kext
-   IOPCIFamily.kext
-   IOSCSIArchitectureModelFamily.kext
-   IOStorageFamily.kext
-   IOUSBFamily.kext
-   IOUSBMassStorageClass.kext
-   System.kext

This should get the system booting from USB (At the very least, it should go beyond the `Got boot device` phase, so that no message `Still waiting for boot device...` appears).

### Installing kexts

Copy the KEXT to `$VOLUME/System/Library/Extensions/` and fix permissions (important):

chown -R root:wheel $VOLUME/System/Library/Extensions/
chmod -R 755 $VOLUME/System/Library/Extensions/
### Determining kext dependencies
The minimal set of KEXTs above cannot, for example, boot from a CD, since the CD driver is not there. Hence, if we want to boot from CD, for example, we need to install the CD driver KEXT and its dependencies. Thus, we need to identify the dependencies.

In order to determine the dependencies of a KEXT, we can use [kextlibs](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man8/kextlibs.8.html).
Example:


kextlibs $VOLUME/System/Library/Extensions/IOUSBFamily.kext/Contents/PlugIns/AppleUSBCDC.kext
com.apple.kpi.libkern = 9.2.2
com.apple.kpi.iokit = 9.2.2
com.apple.iokit.IOUSBFamily = 3.0.8

So in this example, `AppleUSBCDC.kext` has three dependencies. To see which KEXT satisfies a dependency (aka dependents), use [kextfind](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man8/kextfind.8.html):

kextfind -case-insensitive -bundle-id -substring 'com.apple.iokit.IOUSBFamily' -print
/System/Library/Extensions/IOUSBFamily.kext

Of course, `IOUSBFamily.kext` itself has its own dependencies, so we need to make that recursive if we want to find out all dependencies.
#### A visual overview of dependencies
Take a look at [Visualize KEXTs dependencies](kexts/kexts-dependencies-overview.html) page.
### Extensions.mkext
A cache of installed KEXTs is kept in order to speed up boot time.
#### Unpack Extensions.mkext
Extensions.mkext can be unpacked with the [mkextunpack](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man8/mkextunpack.8.html) command:

mkextunpack -v -d /tmp/Extensions Extensions.mkext
### Force cache update {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}


To force cache update, simply change the modification date of *$VOLUME/System/Library/Extensions*:

touch $VOLUME/System/Library/Extensions

### Types of kexts
#### Driver KEXTs
(To be written)
#### Family KEXTs
Family KEXTs are not drivers. Family KEXTs generally contain classes that you are to subclass
#### Filesystem KEXTs {style="margin:10px 10px 10px 0px;background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px"}
Filesystem KEXTs are not drivers. 

