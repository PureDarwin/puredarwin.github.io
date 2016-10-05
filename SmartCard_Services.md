SmartCard Services
==================

****
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](../_/rsrc/1258934378474/curious/smartcard/SCChip-1.png%3Fheight=200&width=181)](smartcard/SCChip-1.png%3Fattredirects=0)

**draft.**
**<span style="color:rgb(0,0,0);font-family:Lucida Grande,Verdana,Arial,Helvetica,sans-serif;font-weight:normal">The [SmartCard Services](http://smartcardservices.macosforge.org/) project. </span>**
Overview
--------
**<span style="color:rgb(0,0,0);font-family:Lucida Grande,Verdana,Arial,Helvetica,sans-serif;font-weight:normal">Sources from Apple are divided in two branches respectively corresponding to Darwin 9 and Darwin 10.</span>**
**<span style="color:rgb(0,0,0);font-family:Lucida Grande,Verdana,Arial,Helvetica,sans-serif;font-weight:normal">Each branch contains these three nested subprojects:</span>**
-   SmartcardCCID
-   SmartCardServices
-   Tokend
<span style="font-family:Arial,Verdana,sans-serif"></span>
### Status
#### Darwin10
SmartCardServices build
Tokend build
#### Darwin 9
SmartcardCCID build
### Smart Card CCID
*Licensed under LGPL v2.1*

ccid
libusb (statically linked insto Smart Card CCID)

### Smart Card Services
*Licensed under APSL v2*

Contains:
<span style="font-family:Lucida Grande,Verdana,Arial,Helvetica,sans-serif">reader drivers (.bundle) for readers not supported by USB CCID Class Driver</span>
<span style="font-family:Lucida Grande,Verdana,Arial,Helvetica,sans-serif">reader drivers KErnel eXTension (PPC only?)</span>
manual pages
pcscd (PCSC daemon)
-   <span style="font-family:Lucida Grande,Verdana,Arial,Helvetica,sans-serif">responsible of reader drivers dynamic (de)allocation at run-time</span>
-   manage reader connections
PKCS11 library (legacy SC abstraction layer)
various scripts
### TokenD
*Licensed under APSL v2*
#### Darwin 10
-   BELPIC.Tokend - Belgian National ID (BELPIC) compliant Smart Cards
-   CAC.Tokend - Common Access Card (CAC) compliant Smart Cards
-   JPKI.Tokend - Japanese PKI (JPKI) compliant Smart Cards
-   PIV.Tokend - Personal Identity Verification (PIV) compliant Smart Cards
-   tokendPKCS11.so - PKCS#11 Shim over Tokend
#### Darwin 9
-   BELPIC.Tokend - Belgian National ID (BELPIC) compliant Smart Cards
-   CAC.Tokend - Common Access Card (CAC) compliant Smart Cards
-   JPKI.Tokend - Japanese PKI (JPKI) compliant Smart Cards
-   PIV.Tokend - Personal Identity Verification (PIV) compliant Smart Cards
Building
--------
### darwinbuild
Host: Darwin 10 (Snow Leopard)
Buildroot: Darwin9 (9J61)

#### SmartCardServices
**Problem:** /Developer/usr/bin/xcodebuild fails with 11 - Resource deadlock avoided
**Solution:** ...
#### Tokend
**Problem: <span style="font-weight:normal">/Developer/usr/bin/xcodebuild fails with 11 - Resource deadlock avoided</span>**

#### SmartcardCCID
<span style="font-size:small">cd 9J61</span>
<span style="font-size:small">darwinbuild -init http://smartcardservices.macosforge.org/trac/export/71/trunk/SmartcardCCID/SmartcardCCID.plist -nfs</span>

<span style="font-size:small">darwinbuild SmartcardCCID</span>

**Problem: <span style="font-weight:normal"><span style="font-size:small">(cd /SourceCache/SmartcardCCID/SmartcardCCID-1/ccid/ccid && ./MacOSX/configure --no-configure --disable-opensc )</span></span>**
<span style="font-size:small">/bin/sh: line 0: cd: /SourceCache/SmartcardCCID/SmartcardCCID-1/ccid/ccid: No such file or directory</span>
<span style="font-size:small">make: *** [install] Error 1</span>
**Solution:** <span style="font-size:small">cd BuildRoot/SourceCache/SmartcardCCID/SmartcardCCID-1/ccid</span>
<span style="font-size:small">tar xjvf ccid-1.3.8.tar.bz2</span>
<span style="font-size:small">ln -s ccid-1.3.8 ccid</span>

**Problem:** <span style="font-size:small">/bin/sh: /SourceCache/SmartcardCCID/SmartcardCCID-1/libusb/libusb/configure: No such file or directory</span>
<span style="font-size:small">make[1]: *** [/private/var/tmp/SmartcardCCID/SmartcardCCID-1.obj/libusb/configure-stamp] Error 127</span>
<span style="font-size:small">make: *** [install] Error 1</span>

**Solution:** <span style="font-size:small">chroot BuildRoot</span>
<span style="font-size:small">cd SourceCache/SmartcardCCID/SmartcardCCID-1/libusb</span>
<span style="font-size:small">tar xzvf libusb-0.1.13b.tar.gz</span>
<span style="font-size:small">ln -s libusb-0.1.13b libusb</span>
<span style="font-size:small">cd libusb</span>
<span style="font-size:small">./autogen.sh</span>
<span style="font-size:small">make distclean</span>


Then the build succeeds:
<span style="font-size:small">BUILD TIME: 0h 2m 8s</span>
<span style="font-size:small">EXIT STATUS: 0</span>
<span style="font-size:small">SmartcardCCID - 7 files registered.</span>

Resources
---------
http://smartcardservices.macosforge.org
http://smartcardservices.macosforge.org/trac/wiki

