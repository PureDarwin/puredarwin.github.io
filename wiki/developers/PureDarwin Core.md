PureDarwin Core
===============
PureDarwin Core is a collection of packages which seeks to provide a Darwin system with networking and the features which make Darwin differ from other OSes (eg. the main security and configuration daemons). PureDarwin Core will be the first set of packages installed on a system, and will run the second stage of the installation process.

A possible package list would be (in no particular order):
#### Official Darwin packages
-   files
-   xnu
-   configd
-   configd_executables
-   launchd
-   bash
-   bsm
-   CoreOSMakefiles
-   dyld
-   gnuzip
-   gnutar
-   bzip2
-   Libsystem
-   Libm
-   libgcc
-   libiconv
-   securityd
-   ICU
-   ncurses
-   Security
-   syslog
-   system_config
-   objc4
-   autozone
-   zlib
-   BootCache
-   efiboot
-   system_cmds
-   Libc
-   Libcpp_kext (not sure about this)
-   notify
-   DiskArbitration
-   bootstrap_cmds
-   libutil
-   adv_cmds
-   diskdev_cmds
-   file_cmds
-   network_cmds
-   hfs
-   DirectoryService
-   DirectoryServiceDaemon
-   bootp
-   libresolv
-   passwordserver_sasl
-   OpenSSL
-   SQLite
#### PureDarwin additions
These can be found in the Roots directory of the PureDarwin Google Code svn/hg.
-   PureDarwinSettings
-   PureDarwinInstall
-   voodoo_kernel 
-   NotApple80211
-   libstdcxx_libs (not libstdcxx, which is approx. 196Mb on its own)
-   PureFoundation
-   CFNetwork
-   ddistnoted
-   PCSC
-   dm
-   lua
-   curl
-   libedit
#### KEXTs and related
-   IOKitUser
-   kext_tools
-   Apple3Com3C90x
-   AppleIntel8255x
-   AppleRTL8139Ethernet
-   AppleAPIC
-   AppleFileSystemDriver
-   AppleIntelPIIXATA
-   AppleSMBIOS
-   AppleUSBCDCDriver
-   IOACPIFamily
-   IOATAFamily
-   IOATAPIProtocolTransport
-   IOCDStorageFamily
-   IODVDStorageFamily
-   IOHIDFamily
-   IOPCIFamily
-   IOStorageFamily
-   IOUSBFamily
-   IOUSBMassStorageClass
-   AppleACPIPlatform
-   AppleRTC
-   IOATABlockStorage
-   IOBDStorageFamily
-   IOSCSIArchitectureModelFamily
-   IONetworkingFamily
-   ApplePS2Controller
-   ACPIPS2Nub
This little lot comes to just over 200Mb on disk, and will shrink to 67Mb as a gnu-zipped tarball.

