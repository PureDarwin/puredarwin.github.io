++++++++++++++++++++++++++++++++++++
 ## PureDarwin Progress and Research 
++++++++++++++++++++++++++++++++++++

We've just moved to Apple's latest code of 10.12.4

______________________________________________
## Currently the project is still moving forward 
______________________________________________
#### Current Projects being actively worked
Working on ACHI Family and Kext work for Darwin use only it will have private headers that will be built into the Kext.
Working on CoreFoundation code pulled from latest https://github.com/apple/swift-corelibs-foundation/tree/master/CoreFoundation

#### Completed Lib's 

Thanks to Ethan we have dyld, libdispatch and libsystem patches along with libplatform project code and built Roots. 

______________________________________________
Projects Still to be worked

Port/Upgrade Mac OSX 10.8.4 UsbFamily to macOS 10.12.4 as UsbFamily no longer open sourced (Unless we know some apple people to talk too)

___________________________________________________________________________________
Example of command to compile  libfirehose_kernel.a needed for XNU building on OSX
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
___________________
Using Darwinbuild
 
sudo darwinbuild -nochroot -target=libfirehose_kernel libdispatch

** INSTALL SUCCEEDED **

 BUILD TIME: 0h 0m 1s
EXIT STATUS: 0
libdispatch - 4 files registered.
                                         40755 0 0 0 ./usr
                                         40755 0 0 0 ./usr/local
                                         40755 0 0 0 ./usr/local/include
                                         40755 0 0 0 ./usr/local/include/kernel
                                         40755 0 0 0 ./usr/local/include/kernel/os
ee27353e97833d9a61d67724b5330e74634f7fce 100644 0 0 3273 ./usr/local/include/kernel/os/firehose_buffer_private.h
                                         40755 0 0 0 ./usr/local/lib
                                         40755 0 0 0 ./usr/local/lib/kernel
a99bc86fe2a3a0b967c9da72102ea6dc2ad7b2a1 100644 0 0 36184 ./usr/local/lib/kernel/libfirehose_kernel.a
5829603c6ba1eecb57e05272440364ab63712aad 100644 0 0 37464 ./usr/local/lib/kernel/libfirehose_kernel_debug.a
a99bc86fe2a3a0b967c9da72102ea6dc2ad7b2a1 100644 0 0 36184 ./usr/local/lib/kernel/libfirehose_kernel_profile.a

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__________________
Using Xcodebuild

xcodebuild -sdk macosx10.12 install -target=libfirehose_kernel -project=libdispatch.xcodeproj
The following build commands
	build/Release/libfirehose_server.a 
	build/Release/libfirehose_server_profile.a 
	build/Release/libfirehose_server_debug.a 



+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Built Roots with OpenSource Headers added into the macosx10.12.sdk under Xcode
This plist https://github.com/PureDarwin/PureDarwin-System-Plist/blob/master/16D32pd1.plist
This Modified Darwinbuild for macOS(Database code sqlite changes) https://github.com/PureDarwin/darwinbuild 



+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

libplatform has been built**** Ethan rocks! 


** INSTALL SUCCEEDED **

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 BUILD TIME: 0h 0m 2s
EXIT STATUS: 0
libplatform - 23 files registered.
                                         40755 0 0 0 ./usr
                                         40755 0 0 0 ./usr/include
d699b626d16c8271fdef328f1da84f95946bb2f2 100644 0 0 1651 ./usr/include/OSAtomic.h
58481d3f98392795650329fc456e51f087edfb91 100644 0 0 43094 ./usr/include/OSAtomicDeprecated.h
c260f5ba655dc7c1b6ee5e11f7bf7a9cc29923ed 100644 0 0 6662 ./usr/include/OSAtomicQueue.h
cfe2e5f61f05eced206eaab55aa1e6dcd8b9a4f0 100644 0 0 2344 ./usr/include/OSCacheControl.h
3a1e10e4fcb8781e68dc30001a1ed51017c37437 100644 0 0 6632 ./usr/include/OSSpinLockDeprecated.h
3de726adedb1c184243d04eee2528368742fb51f 100644 0 0 5682 ./usr/include/_simple.h
29ae8f4a130f58f1eba6ab291c738fcb6133d67e 100644 0 0 2614 ./usr/include/alloc_once_impl.h
9da4359535b777460d0ebdd6baf2cd4aaf566012 100644 0 0 15300 ./usr/include/atomic.h
8d0493ad759089903983797cd90b2b41172491be 100644 0 0 7167 ./usr/include/base.h
254ca8737698de8ffcb9b64a9497d9eee2b41d07 100644 0 0 1138 ./usr/include/base_private.h
5e3181377f01dc0b30b366d4ba3019703e1e2566 100644 0 0 2368 ./usr/include/compat.h
6f069e852ff3d00bfaf31628e2bc2d5e89303096 100644 0 0 1678 ./usr/include/crashlog.h
3cc65922de5049d8345bb504553bf3661f0db1fb 100644 0 0 1785 ./usr/include/internal_shared.h
69e27b55c2d1de6aeb5a852cddb230f849701b3a 100644 0 0 12484 ./usr/include/introspection_private.h
17e697b9c6e75dd650cdaa2965e82939ad0b94e1 100644 0 0 4382 ./usr/include/lock.h
99f1158b2f88c89b6f6bb9bac4f28f389ec5c6bd 100644 0 0 20652 ./usr/include/lock_private.h
77b1c40e6004be6fdef3bd29eae6e0e4af888944 100644 0 0 1851 ./usr/include/once_private.h
3dde0d4b8cef814c45bcdf34bd1a6ff548abb679 100644 0 0 2401 ./usr/include/semaphore_private.h
79d7c60b7fe04d405d6b053e357dad4e8915e59d 100644 0 0 3139 ./usr/include/setjmp.h
b108c703fa83cf3145743844646ea977dd2dd732 100644 0 0 3127 ./usr/include/string.h
2b808d6255928e200b4e7a15a105ee63b09bf658 100644 0 0 2054 ./usr/include/ucontext.h
                                         40755 0 0 0 ./usr/lib
                                         40755 0 0 0 ./usr/lib/system
da39a3ee5e6b4b0d3255bfef95601890afd80709 100755 0 0 42712 ./usr/lib/system/libsystem_platform.dylib
                                         40755 0 0 0 ./usr/local
                                         40755 0 0 0 ./usr/local/include
d00e308ffee156e164dd5c76f63f2f8fa77647a3 100644 0 0 1410 ./usr/local/include/OSAtomic.h
______________________________________________________________________________________________________________________




__________________________________________
#Roots built so far being updated daily* 

___________________________________________________________________________________________________________________
InSanes-iMac:InSaneDarwin insane$ ls -alh Packages/ | grep .root.tar.gz
-rw-r--r--    1 root    admin   9.2K Apr 18 11:46 AppleAPIC.root.tar.gz
-rw-r--r--    1 root    admin   8.4K Apr 11 16:38 AppleFileSystemDriver.root.tar.gz
-rw-r--r--    1 root    admin    27K Apr 18 11:46 AppleIntelPIIXATA.root.tar.gz
-rw-r--r--    1 root    admin   814B Apr 11 16:38 AvailabilityVersions.root.tar.gz
-rw-r--r--    1 root    admin    24M Apr 11 16:38 BerkeleyDB.root.tar.gz
-rw-r--r--    1 root    admin   605K Apr 11 16:38 CrackLib.root.tar.gz
-rw-r--r--    1 root    admin   3.9K Apr 11 16:38 Csu.root.tar.gz
-rw-r--r--    1 root    admin    12M Apr 11 16:38 ICU.root.tar.gz
-rw-r--r--    1 root    admin    17K Apr 18 11:46 IOACPIFamily.root.tar.gz
-rw-r--r--    1 root    admin    58K Apr 11 16:38 IOATAFamily.root.tar.gz
-rw-r--r--    1 root    admin   141K Apr 11 16:38 IOAudioFamily.root.tar.gz
-rw-r--r--    1 root    admin    26K Apr 11 16:38 IOBDStorageFamily.root.tar.gz
-rw-r--r--    1 root    admin    38K Apr 11 16:38 IOCDStorageFamily.root.tar.gz
-rw-r--r--    1 root    admin    28K Apr 11 16:38 IODVDStorageFamily.root.tar.gz
-rw-r--r--    1 root    admin    74K Apr 11 16:38 IOFireWireAVC.root.tar.gz
-rw-r--r--    1 root    admin   324K Apr 11 16:38 IOFireWireFamily.root.tar.gz
-rw-r--r--    1 root    admin    58K Apr 11 16:38 IOFireWireIP.root.tar.gz
-rw-r--r--    1 root    admin    87K Apr 11 16:38 IOFireWireSBP2.root.tar.gz
-rw-r--r--    1 root    admin   163K Apr 11 16:38 IONetworkingFamily.root.tar.gz
-rw-r--r--    1 root    admin   122K Apr 11 16:38 IOPCIFamily.root.tar.gz
-rw-r--r--    1 root    admin    33K Apr 11 16:38 IOSerialFamily.root.tar.gz
-rw-r--r--    1 root    admin   109K Apr 11 16:38 IOStorageFamily.root.tar.gz
-rw-r--r--    1 root    admin   4.6M Apr 12 10:14 Libc.root.tar.gz
-rw-r--r--    1 root    admin    34K Apr 11 16:38 Librpcsvc.root.tar.gz
-rw-r--r--    1 root    admin   1.4K Apr 11 16:38 Liby.root.tar.gz
-rw-r--r--    1 root    admin    40K Apr 11 16:38 OpenPAM.root.tar.gz
-rw-r--r--    1 root    admin    91K Apr 11 16:38 SmartcardCCID.root.tar.gz
-rw-r--r--    1 root    admin   1.2M Apr 11 16:38 TimeZoneData.root.tar.gz
-rw-r--r--    1 root    admin   2.0K Apr 11 16:38 UserNotification.root.tar.gz
-rw-r--r--    1 root    admin   905K Apr 11 16:38 WebInspectorUI.root.tar.gz
-rw-r--r--    1 root    admin   160K Apr 11 16:38 adv_cmds.root.tar.gz
-rw-r--r--    1 root    admin   389K Apr 11 16:38 apr.root.tar.gz
-rw-r--r--    1 root    admin    18K Apr 11 16:38 architecture.root.tar.gz
-rw-r--r--    1 root    admin    51K Apr 11 16:38 awk.root.tar.gz
-rw-r--r--    1 root    admin    17K Apr 11 16:38 basic_cmds.root.tar.gz
-rw-r--r--    1 root    admin   5.7M Apr 11 16:39 bind9.root.tar.gz
-rw-r--r--    1 root    admin   271K Apr 11 16:39 bmalloc.root.tar.gz
-rw-r--r--    1 root    admin    74K Apr 11 16:39 bootstrap_cmds.root.tar.gz
-rw-r--r--    1 root    admin    60K Apr 11 16:39 bzip2.root.tar.gz
-rw-r--r--    1 root    admin    53K Apr 11 16:39 copyfile.root.tar.gz
-rw-r--r--    1 root    admin   4.6K Apr 11 16:39 coreTLS.root.tar.gz
-rw-r--r--    1 root    admin   6.8M Apr 11 16:39 cups.root.tar.gz
-rw-r--r--    1 root    admin   568K Apr 11 16:39 curl.root.tar.gz
-rw-r--r--    1 root    admin   213K Apr 11 16:39 cxxfilt.root.tar.gz
-rw-r--r--    1 root    admin    84K Apr 11 16:39 diskdev_cmds.root.tar.gz
-rw-r--r--    1 root    admin    11K Apr 11 16:39 disklabel.root.tar.gz
-rw-r--r--    1 root    admin    23K Apr 11 16:39 doc_cmds.root.tar.gz
-rw-r--r--    1 root    admin    32M Apr 11 16:39 emacs.root.tar.gz
-rw-r--r--    1 root    admin    66K Apr 11 16:39 expat.root.tar.gz
-rw-r--r--    1 root    admin   606K Apr 11 16:39 file.root.tar.gz
-rw-r--r--    1 root    admin   254K Apr 11 16:39 file_cmds.root.tar.gz
-rw-r--r--    1 root    admin   1.4M Apr 11 16:39 files.root.tar.gz
-rw-r--r--    1 root    admin   148K Apr 11 16:39 gnudiff.root.tar.gz
-rw-r--r--    1 root    admin    49K Apr 11 16:39 gnuserv.root.tar.gz
-rw-r--r--    1 root    admin   155K Apr 11 16:39 gnutar.root.tar.gz
-rw-r--r--    1 root    admin    60K Apr 11 16:39 gpatch.root.tar.gz
-rw-r--r--    1 root    admin    18K Apr 11 16:39 gpt.root.tar.gz
-rw-r--r--    1 root    admin   2.5M Apr 11 16:39 groff.root.tar.gz
-rw-r--r--    1 root    admin   544K Apr 11 16:39 hfs.root.tar.gz
-rw-r--r--    1 root    admin   148K Apr 11 16:39 hunspell.root.tar.gz
-rw-r--r--    1 root    admin   2.8K Apr 11 16:39 keymgr.root.tar.gz
-rw-r--r--    1 root    admin   696K Apr 11 16:39 ksh.root.tar.gz
-rw-r--r--    1 root    admin    85K Apr 11 16:39 less.root.tar.gz
-rw-r--r--    1 root    admin   7.2K Apr 11 16:39 libauto.root.tar.gz
-rw-r--r--    1 root    admin    40K Apr 12 06:17 libdispatch.root.tar.gz
-rw-r--r--    1 root    admin    92K Apr 11 16:39 libedit.root.tar.gz
-rw-r--r--    1 root    admin   369K Apr 11 16:39 libevent.root.tar.gz
-rw-r--r--    1 root    admin    15K Apr 11 16:39 libffi.root.tar.gz
-rw-r--r--    1 root    admin    40K Apr 12 06:17 libfirehose_kernel.root.tar.gz
-rw-r--r--    1 root    admin   147K Apr 12 06:17 libfirehose_server.root.tar.gz
-rw-r--r--    1 root    admin   4.4K Apr 11 16:39 libgcc.root.tar.gz
-rw-r--r--    1 root    admin   747K Apr 11 16:39 libiconv.root.tar.gz
-rw-r--r--    1 root    admin    33K Apr 11 16:39 libkxld.root.tar.gz
-rw-r--r--    1 root    admin   104K Apr 12 01:48 libplatform.root.tar.gz
-rw-r--r--    1 root    admin   104K Apr 12 01:49 libplatform_dyld.root.tar.gz
-rw-r--r--    1 root    admin   104K Apr 12 01:49 libplatform_static.root.tar.gz
-rw-r--r--    1 root    admin    27K Apr 12 08:35 libpthread.root.tar.gz
-rw-r--r--    1 root    admin    33K Apr 12 08:45 libpthread_dyld_static.root.tar.gz
-rw-r--r--    1 root    admin    83K Apr 12 08:45 libpthread_eOS_static.root.tar.gz
-rw-r--r--    1 root    admin    83K Apr 12 08:45 libpthread_generic_static.root.tar.gz
-rw-r--r--    1 root    admin    98K Apr 11 16:39 libresolv.root.tar.gz
-rw-r--r--    1 root    admin   871K Apr 11 16:39 libstdcxx.root.tar.gz
-rw-r--r--    1 root    admin    20K Apr 11 16:39 libtelnet.root.tar.gz
-rw-r--r--    1 root    admin    31K Apr 11 16:39 libutil.root.tar.gz
-rw-r--r--    1 root    admin   648K Apr 11 16:39 libxml2.root.tar.gz
-rw-r--r--    1 root    admin   165K Apr 11 16:39 libxslt.root.tar.gz
-rw-r--r--    1 root    admin    89K Apr 11 16:39 lukemftp.root.tar.gz
-rw-r--r--    1 root    admin    83K Apr 11 16:39 lukemftpd.root.tar.gz
-rw-r--r--    1 root    admin    69K Apr 11 16:39 mail_cmds.root.tar.gz
-rw-r--r--    1 root    admin   122K Apr 11 16:39 misc_cmds.root.tar.gz
-rw-r--r--    1 root    admin    30K Apr 11 16:39 modemccl.root.tar.gz
-rw-r--r--    1 root    admin    78K Apr 11 16:39 msdosfs.root.tar.gz
-rw-r--r--    1 root    admin    82K Apr 11 16:39 nano.root.tar.gz
-rw-r--r--    1 root    admin   822K Apr 11 16:39 ncurses.root.tar.gz
-rw-r--r--    1 root    admin   237K Apr 11 16:39 ntfs.root.tar.gz
-rw-r--r--    1 root    admin    20K Apr 11 16:39 patch_cmds.root.tar.gz
-rw-r--r--    1 root    admin   507K Apr 11 16:39 pcre.root.tar.gz
-rw-r--r--    1 root    admin    27K Apr 11 16:39 pdisk.root.tar.gz
-rw-r--r--    1 root    admin    27K Apr 12 08:35 pthread_kext.root.tar.gz
-rw-r--r--    1 root    admin    16K Apr 11 16:39 removefile.root.tar.gz
-rw-r--r--    1 root    admin   208K Apr 11 16:39 rsync.root.tar.gz
-rw-r--r--    1 root    admin   307K Apr 11 16:39 sudo.root.tar.gz
-rw-r--r--    1 root    admin   899K Apr 11 16:39 swig.root.tar.gz
-rw-r--r--    1 root    admin   2.8K Apr 11 16:39 system_config.root.tar.gz
-rw-r--r--    1 root    admin   245K Apr 11 16:39 tcsh.root.tar.gz
-rw-r--r--    1 root    admin   912K Apr 11 16:39 texinfo.root.tar.gz
-rw-r--r--    1 root    admin   251K Apr 11 16:39 text_cmds.root.tar.gz
-rw-r--r--    1 root    admin    56K Apr 11 16:39 top.root.tar.gz
-rw-r--r--    1 root    admin   7.1K Apr 11 16:39 usertemplate.root.tar.gz
-rw-r--r--    1 root    admin   581K Apr 11 16:39 uucp.root.tar.gz
-rw-r--r--    1 root    admin   7.3M Apr 11 16:39 vim.root.tar.gz
-rw-r--r--    1 root    admin   115K Apr 18 11:46 xar.root.tar.gz
-rw-r--r--    1 root    admin   8.1M Apr 18 11:46 xnu.root.tar.gz
-rw-r--r--    1 root    admin    75K Apr 12 06:28 zlib.root.tar.gz
-rw-r--r--    1 root    admin   2.1M Apr 11 16:39 zsh.root.tar.gz

___________________________________________________________________________________________________________________________

Todos:

