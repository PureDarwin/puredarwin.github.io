SmartCard Services
==================

****
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
![](/img/curious/smartcard/SCChip-1.png)

**draft.**
**The [SmartCard Services](http://smartcardservices.macosforge.org/) project. **
Overview
--------
**Sources from Apple are divided in two branches respectively corresponding to Darwin 9 and Darwin 10.**
**Each branch contains these three nested subprojects:**
-   SmartcardCCID
-   SmartCardServices
-   Tokend

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
reader drivers (.bundle) for readers not supported by USB CCID Class Driver
reader drivers KErnel eXTension (PPC only?)
manual pages
pcscd (PCSC daemon)
-   responsible of reader drivers dynamic (de)allocation at run-time
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
**Problem: /Developer/usr/bin/xcodebuild fails with 11 - Resource deadlock avoided**

#### SmartcardCCID
cd 9J61
darwinbuild -init http://smartcardservices.macosforge.org/trac/export/71/trunk/SmartcardCCID/SmartcardCCID.plist -nfs

darwinbuild SmartcardCCID

**Problem: <span style="font-weight:normal"><span style="font-size:small">(cd /SourceCache/SmartcardCCID/SmartcardCCID-1/ccid/ccid && ./MacOSX/configure --no-configure --disable-opensc )</span></span>**
/bin/sh: line 0: cd: /SourceCache/SmartcardCCID/SmartcardCCID-1/ccid/ccid: No such file or directory
make: *** [install] Error 1
**Solution:** cd BuildRoot/SourceCache/SmartcardCCID/SmartcardCCID-1/ccid
tar xjvf ccid-1.3.8.tar.bz2
ln -s ccid-1.3.8 ccid

**Problem:** /bin/sh: /SourceCache/SmartcardCCID/SmartcardCCID-1/libusb/libusb/configure: No such file or directory
make[1]: *** [/private/var/tmp/SmartcardCCID/SmartcardCCID-1.obj/libusb/configure-stamp] Error 127
make: *** [install] Error 1

**Solution:** chroot BuildRoot
cd SourceCache/SmartcardCCID/SmartcardCCID-1/libusb
tar xzvf libusb-0.1.13b.tar.gz
ln -s libusb-0.1.13b libusb
cd libusb
./autogen.sh
make distclean


Then the build succeeds:
BUILD TIME: 0h 2m 8s
EXIT STATUS: 0
SmartcardCCID - 7 files registered.

Resources
---------
http://smartcardservices.macosforge.org
http://smartcardservices.macosforge.org/trac/wiki

