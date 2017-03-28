++++++++++++++++++++++++++++++++++++
+ PureDarwin Progress and Research +
++++++++++++++++++++++++++++++++++++

______________________________________________
Currently the project is still moving forward 
______________________________________________
Current Projects being actively worked

Working on Dyld patching currently 
Completed on libplatform project files as not opensourced with the code This has been fixed due to some amazing help from Ethan and we have a build working correctly. 
Working on libdispatch and Libsystem(Patching Required)
Working on ACHI Family and Kext work for Darwin use only it will have private headers that will be built into the Kext.
Working on CoreFoundation code pulled from latest https://github.com/apple/swift-corelibs-foundation/tree/master/CoreFoundation
______________________________________________
Projects Still to be worked

Port/Upgrade Mac OSX 10.8.4 UsbFamily to macOS 10.12.3 as UsbFamily no longer open sourced (Unless we know some apple people to talk too)

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
-rw-r--r--    1 root    admin   9.2K Mar  6 21:12 AppleAPIC.root.tar.gz
-rw-r--r--    1 root    admin   8.4K Feb 26 13:27 AppleFileSystemDriver.root.tar.gz
-rw-r--r--    1 root    admin    27K Mar  6 21:53 AppleIntelPIIXATA.root.tar.gz
-rw-r--r--    1 insane  admin   807B Feb 25 03:52 AvailabilityVersions.root.tar.gz
-rw-r--r--    1 insane  admin    23M Feb 25 03:52 BerkeleyDB.root.tar.gz
-rw-r--r--    1 insane  admin    17K Feb 25 03:52 CoreOSMakefiles.root.tar.gz
-rw-r--r--    1 insane  admin   605K Feb 25 03:52 CrackLib.root.tar.gz
-rw-r--r--    1 insane  admin   4.0K Feb 25 03:52 Csu.root.tar.gz
-rw-r--r--    1 insane  admin    12M Feb 25 03:52 ICU.root.tar.gz
-rw-r--r--    1 insane  admin    58K Feb 25 03:52 IOATAFamily.root.tar.gz
-rw-r--r--    1 insane  admin   121K Feb 25 03:52 IOPCIFamily.root.tar.gz
-rw-r--r--    1 insane  admin    33K Feb 25 03:52 IOSerialFamily.root.tar.gz
-rw-r--r--    1 root    admin   866B Mar 27 23:54 Libm.root.tar.gz
-rw-r--r--    1 root    admin    36K Mar  6 13:54 Libnotify.root.tar.gz
-rw-r--r--    1 insane  admin    34K Feb 25 03:52 Librpcsvc.root.tar.gz
-rw-r--r--    1 insane  admin   1.4K Feb 25 03:52 Liby.root.tar.gz
-rw-r--r--    1 insane  admin    40K Mar  7 00:13 OpenPAM.root.tar.gz
-rw-r--r--    1 root    admin   2.7K Mar  2 02:05 PowerManagement.root.tar.gz
-rw-r--r--    1 insane  admin   1.2M Feb 25 03:52 TimeZoneData.root.tar.gz
-rw-r--r--    1 insane  admin   2.0K Feb 25 03:52 UserNotification.root.tar.gz
-rw-r--r--    1 root    admin   161K Feb 27 16:51 adv_cmds.root.tar.gz
-rw-r--r--    1 insane  admin   381K Mar  2 03:54 apr.root.tar.gz
-rw-r--r--    1 insane  admin    18K Feb 25 03:52 architecture.root.tar.gz
-rw-r--r--    1 insane  admin    51K Feb 25 03:52 awk.root.tar.gz
-rw-r--r--    1 root    admin   2.2M Mar  6 10:06 bash.root.tar.gz
-rw-r--r--    1 insane  admin    17K Feb 25 03:52 basic_cmds.root.tar.gz
-rw-r--r--    1 insane  admin   5.8M Feb 25 03:52 bind9.root.tar.gz
-rw-r--r--    1 insane  admin   169K Feb 25 03:52 bison.root.tar.gz
-rw-r--r--    1 insane  admin   276K Feb 25 03:52 bmalloc.root.tar.gz
-rw-r--r--    1 insane  admin    74K Feb 25 03:52 bootstrap_cmds.root.tar.gz
-rw-r--r--    1 root    admin    41M Feb 28 02:11 clang.root.tar.gz
-rw-r--r--    1 root    admin    89K Mar 27 23:54 copyfile.root.tar.gz
-rw-r--r--    1 insane  admin   4.6K Mar 14 03:37 coreTLS.root.tar.gz
-rw-r--r--    1 root    admin    94K Mar  2 02:05 ctfconvert.root.tar.gz
-rw-r--r--    1 root    admin    57K Mar  2 02:05 ctfdump.root.tar.gz
-rw-r--r--    1 insane  admin   6.6M Feb 25 03:52 cups.root.tar.gz
-rw-r--r--    1 root    admin   569K Feb 25 03:52 curl.root.tar.gz
-rw-r--r--    1 insane  admin   214K Feb 25 03:52 cxxfilt.root.tar.gz
-rw-r--r--    1 root    admin    86K Feb 26 13:27 developer_cmds.root.tar.gz
-rw-r--r--    1 root    admin    84K Mar  6 09:20 diskdev_cmds.root.tar.gz
-rw-r--r--    1 insane  admin    11K Feb 25 03:52 disklabel.root.tar.gz
-rw-r--r--    1 root    admin    23K Feb 25 03:52 doc_cmds.root.tar.gz
-rw-r--r--    1 insane  admin    57K Feb 27 01:04 dtrace.root.tar.gz
-rw-r--r--    1 insane  admin    32M Feb 25 03:52 emacs.root.tar.gz
-rw-r--r--    1 root    admin    67K Feb 25 03:52 expat.root.tar.gz
-rw-r--r--    1 root    admin   607K Feb 25 03:52 file.root.tar.gz
-rw-r--r--    1 root    admin   1.4M Feb 25 03:52 files.root.tar.gz
-rw-r--r--    1 root    admin    26K Feb 25 03:52 gcc_select.root.tar.gz
-rw-r--r--    1 root    admin    80K Feb 25 03:52 gm4.root.tar.gz
-rw-r--r--    1 root    admin   149K Feb 25 03:52 gnudiff.root.tar.gz
-rw-r--r--    1 root    admin    93K Feb 25 03:52 gnumake.root.tar.gz
-rw-r--r--    1 root    admin    49K Mar  6 09:18 gnuserv.root.tar.gz
-rw-r--r--    1 root    admin   156K Mar  6 09:13 gnutar.root.tar.gz
-rw-r--r--    1 insane  admin    60K Feb 25 03:52 gpatch.root.tar.gz
-rw-r--r--    1 root    admin    49K Feb 25 03:52 gperf.root.tar.gz
-rw-r--r--    1 root    admin    18K Feb 27 01:05 gpt.root.tar.gz
-rw-r--r--    1 root    admin   2.5M Feb 25 03:52 groff.root.tar.gz
-rw-r--r--    1 root    admin   182K Feb 27 01:05 hfs.root.tar.gz
-rw-r--r--    1 root    admin   148K Feb 25 03:52 hunspell.root.tar.gz
-rw-r--r--    1 insane  admin   4.7K Mar 27 23:54 keymgr.root.tar.gz
-rw-r--r--    1 insane  admin   706K Feb 25 03:52 ksh.root.tar.gz
-rw-r--r--    1 insane  admin    85K Mar  6 13:48 less.root.tar.gz
-rw-r--r--    1 insane  admin   7.2K Mar  2 03:54 libauto.root.tar.gz
-rw-r--r--    1 root    admin   6.6K Mar  2 05:06 libclosure.root.tar.gz
-rw-r--r--    1 root    admin    42K Mar 27 23:54 libdispatch.root.tar.gz
-rw-r--r--    1 insane  admin    92K Feb 25 03:52 libedit.root.tar.gz
-rw-r--r--    1 root    admin   368K Mar 14 06:02 libevent.root.tar.gz
-rw-r--r--    1 root    admin    15K Mar  6 09:10 libffi.root.tar.gz
-rw-r--r--    1 root    admin   4.4K Mar  6 13:45 libgcc.root.tar.gz
-rw-r--r--    1 root    admin   748K Mar  6 13:47 libiconv.root.tar.gz
-rw-r--r--    1 root    admin   409K Mar  2 04:17 libmalloc.root.tar.gz
-rw-r--r--    1 root    admin    43K Mar 13 01:01 libplatform.root.tar.gz
-rw-r--r--    1 root    admin   259K Mar 27 23:54 libpthread.root.tar.gz
-rw-r--r--    1 insane  admin   871K Feb 25 03:52 libstdcxx.root.tar.gz
-rw-r--r--    1 root    admin    20K Feb 25 03:52 libtelnet.root.tar.gz
-rw-r--r--    1 root    admin    36K Mar  6 09:10 libunwind.root.tar.gz
-rw-r--r--    1 insane  admin    26K Feb 24 23:36 libutil.root.tar.gz
-rw-r--r--    1 root    admin   651K Feb 28 00:40 libxml2.root.tar.gz
-rw-r--r--    1 insane  admin   166K Feb 25 03:52 libxslt.root.tar.gz
-rw-r--r--    1 root    admin    89K Feb 25 03:52 lukemftp.root.tar.gz
-rw-r--r--    1 root    admin    83K Feb 25 03:52 lukemftpd.root.tar.gz
-rw-r--r--    1 root    admin    69K Feb 25 03:52 mail_cmds.root.tar.gz
-rw-r--r--    1 root    admin   122K Feb 25 03:52 misc_cmds.root.tar.gz
-rw-r--r--    1 root    admin    31K Feb 25 03:52 modemccl.root.tar.gz
-rw-r--r--    1 root    admin    78K Feb 25 03:52 msdosfs.root.tar.gz
-rw-r--r--    1 insane  admin    83K Feb 25 03:52 nano.root.tar.gz
-rw-r--r--    1 root    admin   239K Feb 25 03:52 ntfs.root.tar.gz
-rw-r--r--    1 root    admin    20K Feb 25 03:52 patch_cmds.root.tar.gz
-rw-r--r--    1 insane  admin    53K Feb 25 03:52 pb_makefiles.root.tar.gz
-rw-r--r--    1 root    admin   509K Feb 25 03:52 pcre.root.tar.gz
-rw-r--r--    1 insane  admin    27K Feb 25 03:52 pdisk.root.tar.gz
-rw-r--r--    1 root    admin    29K Mar 27 23:54 removefile.root.tar.gz
-rw-r--r--    1 root    admin   209K Mar 14 06:02 rsync.root.tar.gz
-rw-r--r--    1 root    admin   526K Mar  6 08:22 screen.root.tar.gz
-rw-r--r--    1 root    admin   300K Feb 26 13:27 shell_cmds.root.tar.gz
-rw-r--r--    1 root    admin   304K Feb 25 03:52 sudo.root.tar.gz
-rw-r--r--    1 insane  admin   902K Feb 25 03:52 swig.root.tar.gz
-rw-r--r--    1 insane  admin   2.8K Feb 25 03:52 system_config.root.tar.gz
-rw-r--r--    1 insane  admin   244K Feb 25 03:52 tcsh.root.tar.gz
-rw-r--r--    1 root    admin   913K Feb 25 03:52 texinfo.root.tar.gz
-rw-r--r--    1 root    admin    56K Feb 25 03:52 top.root.tar.gz
-rw-r--r--    1 root    admin   7.1K Feb 25 03:52 usertemplate.root.tar.gz
-rw-r--r--    1 root    admin   584K Feb 25 03:52 uucp.root.tar.gz
-rw-r--r--    1 root    admin   7.3M Feb 25 03:52 vim.root.tar.gz
-rw-r--r--    1 insane  admin   8.1M Mar 27 23:54 xnu.root.tar.gz
-rw-r--r--    1 insane  admin    75K Feb 25 03:52 zlib.root.tar.gz
-rw-r--r--    1 root    admin   2.1M Feb 25 03:52 zsh.root.tar.gz

___________________________________________________________________________________________________________________________
