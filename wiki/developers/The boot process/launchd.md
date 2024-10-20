launchd
=======
launchd is a central component of the Darwin and Mac OS X boot process.

### About launchd
Starting with Darwin 8, launchd replaces different mechanisms for starting and stopping processes, thus replacing more traditional mechanisms found in other UNIX-like systems such as init, rc, the init.d and rc.d scripts, SystemStarter (Mac OS X), inetd and xinetd, atd, crond and watchdogd. As such, it plays a central role in the Darwin and Mac OS X [boot process](../booting.1.html). It is also a key element of [Mach IPC](../../curious/ipc.html) on Darwin and Mac OS X systems.
### Making launchd verbose
Whenever you need to debug boot problems that occur after the root device has been found, you should make launchd verbose. Put the following in your /etc/launchd.conf:
    log level debug
and append the following to your /etc/syslog.conf:
    *.debug     /dev/console
### Runtime dependencies
The 9F33 binary root of the launchd project has runtime dependencies on the following libraries and frameworks:
    find /Users/user/Downloads/launchd.root -exec otool -L {} 2>&1 ; 
    | grep "compatibility version" | sort | uniq
-   /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation 
-   /System/Library/Frameworks/IOKit.framework/Versions/A/IOKit
-   /System/Library/Frameworks/Security.framework/Versions/A/Security
-   /usr/lib/libSystem.B.dylib
-   /usr/lib/libbsm.dylib
-   /usr/lib/libedit.2.dylib
-   /usr/lib/libgcc_s.1.dylib
Unlike in earlier builds, libauto is no longer a runtime dependency of launchd. 
### launchd from SVN
The launchd project is developed in a publicly accessible subversion repository.
To check out the latest development version of launchd, use 


`svn co http://svn.macosforge.org/repository/launchd/trunk launchd`


Note that this might be developed against a later version of the Core OS than what is publicly available. So something like

`svn co http://svn.macosforge.org/repository/launchd/branches/SULeopard launchd`

might be more appropriate for Darwin 9.
### References
-   [Getting started with launchd](http://developer.apple.com/macosx/launchd.html)
-   [launchd site](http://launchd.macosforge.org/)
-   [AFP548 - launchd in Depth](http://www.afp548.com/article.php?story=20050620071558293)

