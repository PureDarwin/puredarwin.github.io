Armoring PureDarwin
===================
This page describes some ways to hardening PureDarwin (and intrinsically Darwin 9).
Please feel free to contribute.


Preamble
--------
_"Know your enemy"_ - Rage Against the Machine

Dictionary
--------
**hard** • **en** |ˈhärdn|

verb
make or become hard or harder : [ intrans. ] _wait for the glue to harden_ | [ trans. ]_ bricks that seem to have been hardened by firing_.
-   make or become more severe and less sympathetic : [ trans. ] _she hardened her heart_.
-   make or become tougher and more clearly defined : [ intrans. ] _suspicion hardened into certainty_.
-   [ intrans. ] (of prices of stocks, commodities, etc.) _rise and remain steady at a higher level_.

## Disclaimer

**
**

See above, you have been warned in red.
Also, take a look at [Legal](../legal.html) page.





![](http://www.hexley.com/images/hexley_450_pngs/hexley_bare_450.png)

Before installation
-------------------
### Usage
Assuming PureDarwin will be installed on` /Volume/Puredarwin`, these two variables below could be used in the following information.

`export VOLUME="/Volume/PureDarwin"`
`export DISK=`/bin/df | /usr/bin/grep "^/Volume/PureDarwin" | awk -F ' ' '{print $1}'``


You can also use setenv, according to your favorite shell.
Note that the ownership of the session is root.
### Command-line tools to securely erase
#### diskutil
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)

> > Securely erase a disk on $DISK
> > 
> > diskutil secureErase <level> $DISK




Securely erase freespace of a disk on $DISK

`diskutil secureErase freespace <level> $DISK`


3 levels are available in `man diskutil`:
1.  Single pass randomly erase the disk
2.  US DoD 7 pass secure erase
3.  [Gutmann algorithm](http://www.cs.auckland.ac.nz/%7Epgut001/pubs/secure_del.html) 35 pass secure erase  
#### rm
`rm' with `-P` option will overwrite file(s) 3 times, first with the byte pattern 0xff, then 0x00 and finally 0xff before deleting them.
#### srm
Securely remove files or directories:

`srm -r -m dir`


Same as above, 3 levels available in `man srm':

> **-s**  overwrites with a single pass of random data
> 
> If neither is specified, the 35-pass [Gutmann algorithm](http://www.cs.auckland.ac.nz/%7Epgut001/pubs/secure_del.html) is used

### Misc
#### Slim down pd_roots & pd_drivers list
Probability says *pd_roots* & *pd_drivers* may include unused packages with potential vulnerabilities.

By default, the list is big, too big:

`cat pd_roots pd_drivers | wc -l`
`     183`


Knowing what you're doing, you can safely remove more than hundred packages.
#### hdiutil compression
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)


> > hdiutil uses the DiskImages framework (FileVault encryption is supported) to manipulate disk images.
> > 
> > If you want to compress a folder:




`hdiutil create -srcfolder "<folder>" -format UDBZ <compressed folder>.dmg`
`srm -r <folder>`


In order to mount it later, it can be attached using hdiutil:

`mkdir <folder>`
`hdiutil attach -mountpoint <compressed folder>.dmg`




![](http://www.hexley.com/images/hexley_sits_450.png)

System startup
--------------
### Extensible Firmware Interface (EFI)
EFI determines which partition or disk to load. It also determines whether the user can enter (or not) in singe-user mode.
More information in [efiboot](../developers/booting/efiboot.html), [boot](../developers/booting/boot.html) and [the boot process](../developers/booting.1.html) pages.

Creating an EFI password disables:
-   the single-user mode
-   loading of unapproved partition or disk
-   target disk mode at startup
### BIOS
"ClichÃ©", assign a BIOS password in order to prevent potential way to access the OS by booting alternative media.
### Fortify single-user mode
#### Altering rc.common (caution)
`if [ "${BootType}" = "singleuser" ];then `
    `authentification.sh`
`fi`


Assuming authentification.sh is a "nice" script.
#### Using the deprecated /etc/passwd
According to the file itself, in the first comments:

`# Note that this file is consulted directly only when the system is running`
`# in single-user mode. At other times this information is provided by`
`# Open Directory.`


Try to change the shell PATH from:

`root:*:0:0:System Administrator:/var/root:/bin/sh`

to:

`root:*:0:0:System Administrator:/var/root:/dev/null`
#### Remove single user mode support from XNU
If you remove/disable the code portion of what activate/detect the single user mode (-s), there is no way to enter in single user mode.
A patch is needed in this case (****. 
#### Encrypt around
FIXME
### Configuring Access Warnings
FIXME
### PKI
PKI




![](http://www.hexley.com/images/hexley_fork_450.png)
System
------
### Processus & memory
Keep in mind, that any binary you would like to run, can have already been compromised or can be compromised at run-time.
A possible approach is to use your own trusted binary from a read-only medium (when possible), taking in account how your binary is loaded and run in memory. As an illustrative example, `netstat' is well known to be easily short-circuited in order to not show some connections (and several ways exist..).
#### Oldschool UNIX utility
There are plenty "oldschool" UNIX utility, for historical causes, posterity purpose or simply because there are still usefull, as some of them:
-   kill, killall, netstat, ps, sysctl, top, uptime, w, who, ...
We can also find specific utility to Darwin, or at least to BSD subsystems also detailled below.
#### sysctl {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
Retrieving memory status is easy:

`sysctl -a | grep mem   `
`hw.physmem = 2147483648`
`hw.usermem = 1810808832`
`hw.memsize = 2147483648`
`hw.memsize: 2147483648`


A more human readable result of the swap usage:
`sysctl -a | grep swap`

`vm.swapusage: total = 1024.00M  used = 416.94M  free = 607.06M  `

#### hostinfo
`Mach kernel version:`
`Darwin Kernel Version 9.1.0: Wed Oct 31 17:46:22 PDT 2007; root:xnu-1228.0.2~1/RELEASE_I386`
`Kernel configured for up to 2 processors.`
`2 processors are physically available.`
`2 processors are logically available.`
`Processor type: i486 (Intel 80486)Processors active: 0 1`
`Primary memory available: 1.00 gigabytes`
`Default processor set: 52 tasks, 211 threads, 2 processors`
`Load average: 0.02, Mach factor: 1.96`

#### Mach virtual memory statistics: vm_stat
Rudimentary command, an (different) alternative of the missing `free' UNIX utility.

`Mach Virtual Memory Statistics: (page size of 4096 bytes)`
`Pages free: 19385.`
`Pages active: 131831.`
`Pages inactive: 51339.`
`Pages wired down: 58216.`
`"Translation faults": 6266580.`
`Pages copy-on-write: 161179.`
`Pages zero filled: 3302531.`
`Pages reactivated: 5342.`
`Pageins: 167299.`
**Pageouts**`: 3430.`
`Object cache: 24703 hits of 77103 lookups (32% hit rate)`

Some particular value needs to be watch, as the Pageouts number values. If it goes more than 0, it simply means that your memory is swapping which is not what you want, most of the time.
Swapping can result in potential sensitive information dumped from memory to the harddisk (in the swapfile(s)).
Swapping can also happen simply because not enough memory is available.

#### Moving swap file
FIXME
### Manipulate power management settings with pmset
According to the man, pmset changes and reads power management settings such as idle sleep timing, wake on administrative access, automatic restart on power loss, etc.

Changes are saved in a persistent plist file at /Library/Preferences/SystemConfiguration/com.apple.PowerManagement.plist
Scheduled power on/off events are stored separately in /Library/Preferences/SystemConfiguration/com.apple.AutoWake.plist
From the man:
`     boot - tell the kernel that system boot is complete (normally LoginWindow does this). May be useful to Darwin users.`

FIXME

#### Disable computer sleep
`pmset -a sleep 0`


0 to set the idle time to never
#### Enable hard disk sleep (disk spindown timer) 
`pmset -a disksleep 1`
#### Disable wake on ethernet magic packet
`pmset -a womp 0 `
#### Disable automatic restart on power loss
`pmset -a autorestart 0`
#### Disable computer sleep when power button is pressed
`pmset -a powerbutton 0`
### Permissions and filesystem
#### POSIX restrictive style
Use restrictive file mode as possible. Avoid file readable by anyone and writable (typically a 644) by the owner only.

`chmod 600 *`


Idem for folders.

`sudo chmod 700 /Users/<username>`
#### Change global umask file permission
Persistent effects. (FIXME NOT TESTED)

`sudo defaults write /Library/Preferences/.GlobalPreferences NSUmask 77`


You can also use non persistent umask command illustrated by the example just below.

`aladin@niwarderup:~/test% touch before_umask`
`aladin@niwarderup:~/test% mkdir before_umask_dir`
`aladin@niwarderup:~/test% umask 77`
`aladin@niwarderup:~/test% touch after_umask`
`aladin@niwarderup:~/test% mkdir after_umask_dir`
`aladin@niwarderup:~/test% ls -l`
`total 0`
`-rw-r--r-- 1 aladin staff  0 Jun 20 19:07 before_umask`
`drwxr-xr-x 2 aladin staff 68 Jun 20 19:07 before_umask_dir`
`-rw------- 1 aladin staff  0 Jun 20 19:07 after_umask`
`drwx------ 2 aladin staff 68 Jun 20 19:07 after_umask_dir`
#### Extended Attributes
Extended attributes extend the basic attributes associated with files and directories in the file system.
They are stored as name:data pairs associated with file system objects (files, directories, symlinks, etc).
xattr

`ls -@l <file>`
FIXME
#### Locking file with chflags
Set the user immutable flag (owner or super-user only):

`chflags uchg filename.txt`
#### Unlocking file with chflags
Clear the user immutable flag (owner or super-user only):

`chflags nouchg filename.txt`
#### The suid/sgid (set-user/group-ID-on-execution) bit
Executable files with this bit set will run with effective uid set to the uid of the file owner. Moreover, directories with the set-user-id bit set will force all files and sub-directories created in them to be owned by the directory owner and not by the uid of the creating process.

`find / -type f -perm -04001 -ls > suid-files `
`find / -type f -perm -02001 -ls > sgid-files `
`find / -type f -perm -04001 -user 0 -ls > suid-root `
`find / -type f -perm -02001 -group 0 -ls > sgid-root `
``

whoami 

aladin

id

uid=501(aladin) gid=20(staff) groups=20(staff),98(_lpadmin),80(admin)

osascript -e "tell app "ARDAgent" to do shell script "whoami""
``
<div style="font-family:courier new,monospace;color:rgb(102,102,102)">
root

osascript -e "tell app "ARDAgent" to do shell script "id""
<div style="font-family:courier new,monospace;color:rgb(102,102,102)">
uid=0(root) gid=0(wheel) egid=20(staff) groups=0(wheel),1(daemon),2(kmem),8(procview),29(certusers),3(sys),9(procmod),4(tty),5(operator),80(admin),20(staff)


#### Find writable file(s)
`find / -type f -perm -02 -ls`
#### Find writable dir(s)
`find / -type d -perm -02 -ls`
#### Kext permission rules
-   All files and folders in the KEXT, including the KEXT itself, must be owned by the root user (uid 0)
-   All files and folders in the KEXT, including the KEXT itself, must be owned by the wheel group (gid 0)
-   All folders in the KEXT, including the KEXT itself, must have the permissions 0755 (octal)
-   All files in the KEXT must have permissions 0644 (octal)
<!-- -->
-   A KEXT is not the place to store a user-space executable.
`/usr/sbin/chown -R root:wheel MyKEXT.kext`


`find MyKEXT.kext -type d -exec /bin/chmod 0755 {} ;`
`find MyKEXT.kext -type f -exec /bin/chmod 0644 {} ;`
#### Hard link
fixme
#### Symbolic link
fixme
### diskutil
#### Verify and repair permission
When you use diskutil to verify or repair disk permissions, it reads the Bill of Materials files from the Darwin installation and compares its list to the permissions on each file listed.

If the permissions differ, diskutil can repair them.

`diskutil repairPermissions $PUREDARWIN`
#### Enable journaling (if supported by the FS)
`diskutil enableJournal $PUREDARWIN/`
### Encrypting data
#### System swap
The kernel uses a pool of external swap files to support demand paging.
**Caution**, it seems swap files aren't erased securely at startup.
Swap files reside in /private/var/vm/ directory:


-rw------T  1 root  wheel    67108864 Jun 22 11:51 swapfile0
`-rw------T  1 root  wheel    67108864 Jun 22 19:02 swapfile1`

An external storage manager for dynamic pager is running as root, showing by `ps aux | grep dynamic`


`root        26   0.0  0.1    75376    704   ??  Ss   11:50AM   0:00.01 /sbin/dynamic_pager -F /private/var/vm/swapfile`

Launched with /System/Library/LaunchDaemons/com.apple.dynamic_pager.plist
#### Disable swap file (caution)
Disabling swap needs caution.

Some program may require explicitly swap memory area.
What happens if no more physical memory available and swap is disabled?

Non persistent way:

`sudo killall dynamic_pager`
`sudo srm /private/var/vm/swapfile*`

Persistent way:
Edit /System/Library/LaunchDaemons/com.apple.dynamic_pager.plist and remove the nodes:
`<string>/sbin/dynamic_pager</string>
<string>-F</string>
<string>/private/var/vm/swapfile</string>`

Alternatively, the Disabled <boolean> optional key is used to disable (or not) the job.
Then wipe free space.
#### Encrypted swap file
#### This is essentially used to prevent some potential local user "deviance".
PureDarwin, if it is not yet the case, will provide by default an encrypted swap partition.
The `dynamic_pager' daemon have an option to enable encryption:
####      -E      Encrypt the data in the swap files.








Not sure if it is still working but.. try to put `ENCRYPTSWAP=-YES-` in /etc/hostconfig or add the the respective launchd plist the corresponding arg.



`     -P      This option is currently unimplemented.`

Although in the short getopt:

`dynamic_pager: illegal option -- h`

`usage: dynamic_pager [-F filename] [-L low water alert trigger] [-H high water alert trigger] [-S file size] [`**-P priority**`]`


#### Encrypt (and password protect) a folder with hdiutil
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)




> > hdiutil create -encryption AES-256 -stdinpass -srcfolder <folder> <encrypted folder>.dmg




#### 
#### Decrypt a folder with hdiutil
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)



> > 
> > hdiutil attach -stdinpass <encrypted folder>.dmg




#### 
#### FileVault
256-bit and 128-bit AES keys support.

Bad, filevault key are protected by user/password.
FIXME
#### gpg
FIXME
### Users & accounts
#### Creating user account
Some scripts as `pd_adduser' or `pd_injectuser', or the more regular `dscl' and `passwd' binaries can be used in order to create and manage user accounts. See [Download](../downloads.html) page and [User management](../users/users.1.html) page.
#### Reset a user's password in single user mode
Boot into single user mode. Replace username with the targeted user and password with the desired password, then:

fsck -fy
mount -uw /
launchctl load /System/Library/LaunchDaemons/com.apple.DirectoryServices.plist
dscl . -passwd /Users/username [password]


Then reboot, or relaunch DirectoryServices.

Note that you can also use [pd_injectuser](../downloads.html) to recreate a user account, including his password.

/usr/local/sbin/pd_injectuser
****
#### Disable root account
**dsenableroot -d -u username -p userpassword**
****
#### Enable root account (caution)
dsenableroot -u username -p userpassword -r rootpassword
#### Restrict sudo use
Edit /etc/sudoers and limit the use of sudo to a single command per auth by adding:

`Defaults timestamp_timeout=0`

Edit /etc/sudoers in order to restrict who can run sudo by removing:

`%admin` `ALL=(ALL) ALL`


and add for each &lt;user&gt;:

`<user> ` `ALL=(ALL) ALL`
### ACL
#### Enable file ACL on the root file system
`sudo fsaclctl â€“p / -e`
#### Disable file ACL on the root file system
`sudo fsaclctl â€“p / -d`
#### Enable user based ACL for a file
Read access:

`chmod +a "<user> allow read" <file>`
#### Enable group based ACL for a file
Allow write access:


`chmod +a "<group> allow write" <file>`


Deny write access specifically:


chmod +a "<user> deny write" <file>
#### View ACLs
`ls -le <file>`
#### sandbox: a role-based access control system
FIXME
A kernel-enforced access control, applied at the system call of XNU.
Flexible policies?

Compiled from Scheme (LISP inside ;)) programs/rules in /usr/share/sandbox.
Rules support from SYSV IPC to BSD sysctl via signals.
FIXME 
### Logging
#### Cron audit
Look /etc/periodic/*
FIXME
#### syslogd
Edit /etc/syslog.conf.

To log authentication error messages (also the remote ones) in /var/log/secure.log, change the line

`authpriv.*;remoteauth.crit /var/log/secure.log `

to

`authpriv.*;remoteauth.err;auth.err /var/log/secure.log`
#### Limit number of message a syslogd rule generate
Enable facility of LOG_SECURITY:

`/usr/sbin/sysctl -w net.inet.ip.fw.verbose=1`


Add `logamount <number>` after the log keyword
Setting `<number>` to `0` removes limit.
#### local system logging
FIXME
/etc/newsyslog.conf configuration can sets
-   log file rotation based on size, last rotation time, or time of day
-   secure permissions to log files at rotation time
#### remote system logging
Local logging is not really reliable if the computer is compromised, local files can be modified, removed or short-circuited

Open /etc/syslog.conf to enable remote logging.
Add to the top:

`*.* @<remote log server address or host>`

Restart `syslogd' with a hangup signal (or via launchctl):

`sudo killall â€“HUP syslogd`

Edit /etc/syslog.conf and add /var/log/secure.log and /var/system.log to the host `<host>`:


`authpriv.*;remoteauth.err;auth.err @<host> `
`*.notice;authpriv,remoteauth,ftp,install.none;kern.debug;mail.crit @<host>`


FIXME
#### Process accounting
FIXME
Logs all commands executed by all users.

To enable process accounting, create /var/account folder.

`sudo mkdir -p /var/account`

Create /var/account/acct to store process accounting information:


`sudo touch /var/account/acct`
`chown -R root:admin /var/account`
`chmod -R 660 /var/account`

Start accounting on the system:

`sudo accton /var/account /acct`

It is launched at boot.

Use `lastcomm`to get information on previously executed commands.
#### Enable security audit
FIXME
Open /etc/hostconfig and add:

`AUDIT=-YES-`

Restart.

`audit -n` rotates the current log file.
`audit -s` rotates the current log file and forces to reload settings from the audit_control file
#### last, wtmp & utmp
The file /var/run/utmp stores information about the currently logged-in user, whereas /var/log/wtmp tracks all user logins/logouts, shutdowns, reboots, and crashes.
Deprecated but sometimes usefull.
#### Log files (non exhaustive list)
FIXME
/var/log/cups
/var/log/ftp.log
/var/log/httpd
/var/log/lastlog
/var/log/wtmp
/var/log/lookupd.log
/var/log/lpr.log
/var/log/secure.log
/var/log/system.log
/var/log/ipfw.log
/var/log/fsck_hfs.log

/var/run/utmp

Library/Logs/
### Debugging
#### Some tools
FIXME
#### leak
FIXME
Leaked memory identification and other unreferenced malloc buffers.
#### heap
FIXME
List all the malloc-allocated buffers in the process's heap.
#### malloc_history
FIXME
malloc_history inspects a given process and lists the malloc allocations performed by it.
#### vmmap
FIXME

#### Disable Core Dumps
FIXME
To prevent the kernel from creating core dumps:

`kern.coredump=0 in /etc/sysctl.conf`

The non persistent way:

`sysctl -w kern.coredump=0`
#### Limit core dump
Enable core dumps by adding the line `limit core unlimited` in /etc/launchd.conf (persistent way).

The resulted dump(s) will be stored in /cores folder:

`file /cores/core.57`
`/cores/core.57: Mach-O core i386`


Or from a shell (non persistent): ulimit -c unlimited



__Notes:__ `kill -ABRT <pid>` could be used in order to generate a core dump.
On Darwin8, change the line "COREDUMPS=-NO-" in /etc/hostconfig to "COREDUMPS=-YES-"
#### launchd 
FIXME
To send all launchd logs to a file, add in /etc/syslog.conf:

`launchd.* /var/log/launchd.log`

Restart syslogd:

`sudo kill -HUP `cat /var/run/syslog.pid``

To increase the level of debugging:

`sudo launchctl log level debug Password: ********`

FIXME
See [launchd](../developers/booting/launchd.html) page.
#### Enable lookupd debugging
`sudo dscl . create /dsRecTypeStandard:Config/lookupd Debug YES`
`sudo dscl . create /dsRecTypeStandard:Config/lookupd Trace YES`

Edit /etc/syslog.conf and replace `netinfo.err` by `netinfo.debug`

Restart daemons

`sudo kill -HUP `cat /var/run/syslog.pid``
`sudo kill -HUP `cat /var/run/lookupd.pid``
#### Disable lookupd debugging
`sudo dscl . delete /dsRecTypeStandard:Config/lookupd`


Edit /etc/syslog.conf and replace `netinfo.debug` with `netinfo.err`

Restart daemons

`sudo kill -HUP `cat /var/run/syslog.pid``
`sudo kill -HUP `cat /var/run/lookupd.pid`
#### diskarbitrationd
FIXME
Open /System/Library/LaunchDaemons/com.apple.diskarbitrationd.plist:


`    <key>ProgramArguments</key>`
`    <array>`
`        <string>/usr/sbin/diskarbitrationd</string>`
`    </array>`


and simply append "-d":


`    <key>ProgramArguments</key>`
`    <array>`
`        <string>/usr/sbin/diskarbitrationd -d</string>`
`    </array>`
FIXME
#### fs_usage
fs_usage reports system calls and page faults related to filesystem activity in real-time, often usefull for debugging.

Remember by default (without any options), fs_usage itself, Terminal, telnetd, sshd, rlogind, tcsh, csh and sh processes are excluded from the output.

Identify files used by an application at launchtime:

`sudo fs_usage -w | grep <application>`

-w options forces wider, detailed, output.

FIXME
#### DTrace {style="margin-top:10px;margin-bottom:10px;color:rgb(0,0,0);margin-left:10px;margin-right:0px"}
The generic front-end to the DTrace facility is a powerfull dynamic debugger and analysis tool.
See the [DTrace](dtrace.html) page.


### Recompiling XNU
FIXME
See [The XNU kernel](../developers/xnu.1.html) page.
#### Usefull MacPorts
`kernel-tools sysutils/kernel-tools 8J2135 Tools required to build xnu for Intel
gcc_select sysutils/gcc_select 0.1 Switch the default compiler
`After kernel-tools installed, the compilation will [fail](http://failblog.org) irremediably with some tool not found in /usr/local/bin/.
A quick fix with symbolic links:
`/usr/local/bin/check_dylib->/opt/local/bin/check_dylib`
`/usr/local/bin/checksyms->/opt/local/bin/checksyms`
`/usr/local/bin/cmpshlib->/opt/local/bin/cmpshlib`
`/usr/local/bin/decomment->/opt/local/bin/decomment`
`/usr/local/bin/hack_libgcc->/opt/local/bin/hack_libgcc`
`/usr/local/bin/indr->/opt/local/bin/indr`
`/usr/local/bin/kern_tool->/opt/local/bin/kern_tool`
`/usr/local/bin/kextsymboltool->/opt/local/bin/kextsymboltool`
`/usr/local/bin/mkshlib->/opt/local/bin/mkshlib`
`/usr/local/bin/seg_addr_table->/opt/local/bin/seg_addr_table`
`/usr/local/bin/seg_hack->/opt/local/bin/seg_hack`
`/usr/local/bin/relpath->/opt/local/bin/relpath`
#### Configuration files involved
FIXME
`bsd/conf/MASTER           iokit/conf/MASTER.i386    libsa/conf/MASTER         osfmk/conf/MASTER.i386    security/conf/MASTER`
`bsd/conf/MASTER.i386      libkern/conf/MASTER       libsa/conf/MASTER.i386    pexpert/conf/MASTER       security/conf/MASTER.i386`
`iokit/conf/MASTER         libkern/conf/MASTER.i386  osfmk/conf/MASTER         pexpert/conf/MASTER.i386`

Note we don't use MASTER.ppc files although they are still existing.
#### Before
FIXME
ProductName: Mac OS X
ProductVersion: 10.5.4
BuildVersion: 9E17

gcc version:
`Using built-in specs.`
`Target: i686-apple-darwin9`
`Configured with: /var/tmp/gcc/gcc-5465~16/src/configure --disable-checking -enable-werror --prefix=/usr --mandir=/share/man --enable-languages=c,objc,c++,obj-c++ --program-transform-name=/^[cg][^.-]*$/s/$/-4.0/ --with-gxx-include-dir=/include/c++/4.0.0 --with-slibdir=/usr/lib --build=i686-apple-darwin9 --with-arch=apple --with-tune=generic --host=i686-apple-darwin9 --target=i686-apple-darwin9`
`Thread model: posix`
`gcc version 4.0.1 (Apple Inc. build 5465)`

#### Easy compilation
FIXME
make KERNEL_CONFIGS="RELEASE" all VERBOSE=YES
FIXME
#### After
FIXME
### Tweaking XNU
#### Secure levels "Ã  la OpenBSD"
This is not yet implemented nor investigated.
Some security concepts "Ã  la OpenBSD" could be reused into Darwin, at least partially.



In OpenBSD, there are four security levels, from the less to the most secure level: -1, 0, 1, 2


In OpenBSD, securelevels are set from /etc/rc.securelevel
In PureDarwin, **nyi. **securelevels are set from [unknown location/securelevel.plist]

In OpenBSD, the end of the boot process is showing which security level is used.
In PureDarwin, **nyi**.

In OpenBSD, `sysctl kern.securelevel=x` can be used to adjust "on live" the security level. In order to adjust from a higher security level to a lower security level, a reboot is needed.
In PureDarwin, `sysctl' is reporting the option (**but not yet tested**)

`kern.securelevel = 0`
`kern.securelevel: 0`
`kern.secure_kernel: 0`

In OpenBSD, securelevel -1: no additional kernel security features, nor restrictive permission. Not for production use.

In OpenBSD, securelevel 0: used at first boot. If securelevel 1 is set, it will be used after the boot process finish. There are no added features of securelevel 0.
In PureDarwin, ?

In OpenBSD, securelevel 1: /dev/mem and /dev/kmem cannot be write. Raw disk are read-only. etc...

In OpenBSD, securelevel 2: ...

#### Removing debug info
FIXME.
Take care of MACH_DEBUG.
According to osfmk/conf/MASTER configuration file:


`# MACH_DEBUG enables the mach_debug_server, a message interface used to`
`#` `retrieve or control various statistics. This interface may expose data`
`#` `structures that would not normally be allowed outside the kernel, and`
`#` `MUST NOT be enabled on a released configuration.
options` `MACH_DEBUG` `#` `#`
`options` `MACH_IPC_DEBUG` `#` `#`
`#`
`options` `MACH_VM_DEBUG` `#` `# <debug>
`
FIXME
### authorization right
FIXME
/etc/authorization


![](http://www.hexley.com/images/hexley_450_pngs/hexley_worm_450.png)
Network
-------
### Disable IPv6
`networksetup -setv6off $iface`

### ifconfig
Use a restrictive netmask.
### Detecting promiscuous mode
Several ways exist to detect promiscuous mode (potential running sniffer), you can use [DTrace](dtrace.html), simply parse `ifconfig' or even run a sniffer.
Without promisc mode, ifconfig looks like
`/sbin/ifconfig en0`
`en0: flags=8863<UP,BROADCAST,SMART,RUNNING,SIMPLEX,MULTICAST> mtu 1500`
                `ether 00:19:**:**:**:**`
                `media: autoselect status: inactive`
                `supported media: autoselect 10baseT/UTP <half-duplex> 10baseT/UTP <full-duplex> 10baseT/UTP <full-duplex,hw-loopback> 10baseT/UTP <full-duplex,flow-control> 100baseTX <half-duplex> 100baseTX <full-duplex> 100baseTX <full-duplex,hw-loopback> 100baseTX <full-duplex,flow-control> 1000baseT <full-duplex> 1000baseT <full-duplex,hw-loopback> 1000baseT <full-duplex,flow-control> none`

With promisc mode activated:

`/sbin/ifconfig en0`
``
`        ether 00:19:**:**:**:** `
`        media: autoselect status: inactive`
`        supported media: autoselect 10baseT/UTP <half-duplex> 10baseT/UTP <full-duplex> 10baseT/UTP <full-duplex,hw-loopback> 10baseT/UTP <full-duplex,flow-control> 100baseTX <half-duplex> 100baseTX <full-duplex> 100baseTX <full-duplex,hw-loopback> 100baseTX <full-duplex,flow-control> 1000baseT <full-duplex> 1000baseT <full-duplex,hw-loopback> 1000baseT <full-duplex,flow-control> none`
### netstat
Be carefull with netstat, it is not so hard to compromise "its results".

`netstat -anp tcp `
`netstat -anp udp`
### lsof
`lsof -i tcp`
`lsof -i udp`

### Firewall {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
#### ipfw {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
The default rule is not really restrictive:

`#ipfw list`
`65535 allow ip from any to any`

Same for the IPv6 network stack, the default rules list looks like:

`ip6fw list`
`33300 deny ipv6-icmp from any to any in icmptype 128`
`65535 allow ipv6 from any to any`
#### ipfw traffic shapping {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
If the bandwidth used can be known (estimation at least; if the use is "constant" it is really efficient) in advance, allocating only the requested amount will not let enough "space" (bandwidth) available for an intruder.

As an example, create a pipe that only allows up to 42KB/s to go through.

`sudo ipfw pipe 1 cg``onfi`` bw 42KByte/s`

Attach that pipe to the outgoing traffic on port 22, effectively limiting the outgoing traffic of sshd.


sudo ipfw add 1 pipe 1 src-port 22

Remove the pipe from the port.


sudo ipfw delete 1
#### firewall state in sysctl {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
The state of the firewall (enabled or disabled) can be changed by directly changing a kernel parameter.

Enable the firewall (default):
`sysctl -w net.inet.ip.fw.enable=0 `

Disables the firewall:
`sysctl -w net.inet.ip.fw.enable=1 `

More info:

net.inet.ip.fw.verbose_limit: 0

net.inet.ip.fw.verbose: 2

net.inet.ip.fw.debug: 0

net.inet.ip.fw.one_pass: 0

net.inet.ip.fw.autoinc_step: 100

net.inet.ip.fw.enable: 1
#### Rules examples {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
TODO
#### Block dns multicast (5353)
`grep -i 5353 /etc/services `
`mdns            5353/udp    # Multicast DNS`
`mdns            5353/tcp    # Multicast DNS`
FIXME
#### Activating NAT on server side {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
FIXME
Create /etc/natd.conf and add:

`interface en0 `
`same_ports yes `
`use_sockets yes `
`unregistered_only yes`

Add `dynamic yes` if you have a dynamic IP.
Add `log_denied no` if you want to log packets blocked by the NAT device

Configure internal interface en0 with a private address (i.e: 192.168.1.1)

Enable IP forwarding in the kernel, it's needed.
Non persistent way:

`sysctl -w net.inet.ip.forwarding=1`

Persistent way, in /etc/hostconfig, add or change the value to `IPFORWARDING=-YES-`

Route packets from the internal network to the external one via en0:

`ipfw add divert natd ip from any to any via en0`

Launch natd:

`/usr/sbin/natd -f /etc/natd.conf`
#### Use NAT on client side
IP address: 192.168.1.* (obviously 192.168.1.1 is reserved)
Subnet mask: 255.255.254.0 
Gateway/default router: 192.168.1.1 
DNS servers: same as the router (but not necessarily)
#### Enable a caching name server on NAT server side
In /etc/hostconfig, add or change the line to `DNSSERVER=-YES-`
__
__


![](http://www.hexley.com/images/hexley_450_pngs/hexley_pkg_450.png)
Services
--------
### Cups
FIXME
By default, all local user can access to http://127.0.0.1:631 (a web admin front-end).
#### Enable cupsd service
`sudo launchctl load -w /System/Library/LaunchDaemons/org.cups.cupsd.plist `
#### Disable cupsd service
`sudo launchctl unload -w /System/Library/LaunchDaemons/org.cups.cupsd.plist `
FIXME
### ftp
#### Disable ftp
`launctl unload -w /System/Library/LaunchDaemons/ftp.plist`
#### Enable ftp
`launctl load -w /System/Library/LaunchDaemons/ftp.plist `
### Samba
#### Disable SMB
`defaults delete /Library/Preferences/SystemConfiguration/com.apple.smb.server EnabledServices`

`launctl unload -w /System/Library/LaunchDaemons/nmbd.plist `
`launctl unload -w /System/Library/LaunchDaemons/smbd.plist `

### AFP
#### Disable Apple File Server
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)







> > launctl unload -w /System/Library/LaunchDaemons/com.apple.AppleFileServer.plist








### ntp
FIXME
/etc/ntp.conf
### NFS
FIXME
#### Disable NFS
`launchctl unload -w /System/Library/LaunchDaemons/com.apple.portmap.plist`
`launchctl unload -w /System/Library/LaunchDaemons/org.postfix.master.plist`

#### Enable NFS
`launchctl load -w /System/Library/LaunchDaemons/com.apple.portmap.plist`
`launchctl load -w /System/Library/LaunchDaemons/org.postfix.master.plist`
### Bonjour
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)






> > FIXME






#### Disable Bonjour
`sudo launchctl load -w /System/Library/LaunchDaemons/com.apple.mDNSResponder.plist`
#### Enable Bonjour
`sudo launchctl load -w /System/Library/LaunchDaemons/com.apple.mDNSResponder.plist`
#### Change Bonjour hostname
No spaces or non-DNS characters allowed for &lt;hostname&gt;

`scutil --set LocalHostName <hostname>`

...

### SSH
FIXME
There are so many tutorials available about how to configure and/or secure sshd that we do not need to explain these points.
#### Check fingerprint
Prints fingerprint of the serverâ€™s RSA key:

`ssh-keygen -l -f /private/etc/ssh_host_rsa_key.pub`


FIXME
#### sshd
FIXME
#### Client's side
FIXME
Edit /private/etc/sshd_config

Change `PasswordAuthentication yes` to `PasswordAuthentication no`
Change `RSAAuthentication yes` to `RSAAuthentication no` if key-based authentication is used
#### more
FIXME
#### Tunneling
From the man:


` The following example tunnels an IRC session from client machine ``127.0.0.1'' (localhost) to remote server`
`     ``server.example.com'':`
`
`
`         $ ssh -f -L 1234:localhost:6667 server.example.com sleep 10`
`         $ irc -c '#users' -p 1234 pinky 127.0.0.1`



![](http://www.hexley.com/images/hexley_450_pngs/hexley_key_450.png)
Perimetric security
-------------------
### Preventing RF eavesdroppers
#### Faraday cage
Blocks out external static electrical fields and shield the interior from external electromagnetic radiation. 
Named after physicist [Michael Faraday](http://en.wikipedia.org/wiki/Michael_Faraday "Michael Faraday"), who built one in 1836.


You can also encrypt your communication and/or add noise if you cannot managed to block output emits, though according to "[Shannon](http://en.wikipedia.org/wiki/Claude_E._Shannon)", it's probably not the most efficient way.
#### Wireless emission
No driver reported to work at this time. See [Network page](../developers/network.html) for update.
freeradius and openradius (802.11X could be then tested, though wireless is not mandatory for this kind of service).
Reduce power emit.
Add "many" fakeap clones.
WPA2 minimum.
etc... 
http://www.swisswireless.org/wlan_calc_en.html
#### Bluetooth
No support known on Darwin (need investigation).
#### Screen disclosure
Away from the screen, no information nor open privileged prompt should remain.
Potential solution(s):
-   removing scrollback buffer (is it possible on Darwin? is there any scrollback first?)
-   Screen blanking
-   Automatic logout (nyi)
-   Screensaver
-   etc..
### Disable some kext to avoid potential physical security flaws 
#### Remove Airport support
No driver available at this time or reported to work, although the operation should be similar as below.

You can safely remove it if you don't plan to use wireless network interface:
sudo srm -Rf /System/Library/Extensions/AppleAirPort.kext
sudo touch /System/Library/Extensions













#### Remove bluetooth support
No driver available at this time or reported to work, although the operation should be similar as below.

Prevent someone to reach your computer bluetooth:
`sudo srm -Rf /System/Library/Extensions/IOBluetoothFamily.kext`
`sudo srm -Rf /System/Library/Extensions/IOBluetoothHIDDriver.kext`
`sudo touch /System/Library/Extensions`
#### Removing audio support
#### No driver available at this time or reported to work, although the operation should be similar as below.
#### Prevent someone to listen your microphone:
`sudo srm -Rf /System/Library/Extensions/AppleOnboardAudio.kext 
sudo srm -Rf /System/Library/Extensions/AppleUSBAudio.kext 
sudo srm -Rf /System/Library/Extensions/AudioDeviceTreeUpdater.kext 
sudo srm -Rf /System/Library/Extensions/IOAudioFamily.kext 
sudo srm -Rf /System/Library/Extensions/VirtualAudioDriver.kext
sudo touch /System/Library/Extensions`












#### Removing video support
No driver available at this time or reported to work, although the operation should be similar as below.
Prevent someone trying to watch your webcam:
sudo srm -rf /System/Library/Extensions/Apple_iSight.kext
sudo srm -rf /System/Library/Extensions/IOUSBFamily.kext/Contents/PlugIns/AppleUSBVideoSupport.kext 
sudo touch /System/Library/Extensions













#### Removing USB support
**Warning: **Since we boot on USB we shouldn't remove this one.
You probably can safely remove this one if you boot on firewire, cdrom, in a vm or other medium:

`sudo srm -rf /System/Library/Extensions/IOUSBMassStorageClass.kext`
`sudo touch /System/Library/Extensions`
#### Removing FireWire support
Except if you boot on firewire or simply need it, you could safely remove this one:

`sudo srm -rf /System/Library/Extensions/IOFireWireSerialBusProtocolTransport.kext`
`sudo touch /System/Library/Extensions`

### Serialization {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
#### ioreg
The I/O Kit registry is an abstraction layer of some logical and physical information. We can use it to retrieve some unique identifiers.
Write somewhere (away from your computer) as serials you will find as possible:

ioreg -c "IOPlatformExpertDevice" | awk -F '"' '/IOPlatformSerialNumber/ {print $4}'
Q723******
`
`
ioreg -c "IOPlatformExpertDevice" | awk -F '"' '/product-name/ {print $4}'
MacBook2,1
`
`
ioreg -c "IOPlatformExpertDevice" | awk -F '"' '/board-id/ {print $4}'
Mac-F420****
`
`
ioreg -c "IOPlatformExpertDevice" | awk -F '"' '/IOPlatformUUID/ {print $4}'
00000000-0000-**00-**00-0019E33****
`
`
ioreg -c "ATADeviceNub" | awk -F '"' '/device serial/ {print $4}'          
K0075******
`
`
ioreg -c "AppleAHCIDiskDriver" | awk -F '"' '/Serial Number/ {print $4}'
        K439T7******
`
`

ioreg -l | grep -i 'serial number'
    | |   |         |   "Serial Number" = "        K439********"
`
`

ioreg -l | grep -i 'serialnumber'
    |   "IOPlatformSerialNumber" = "WQ7********"

    | |           "BatterySerialNumber" = "DP-ASM****-3***-3***"
    | |           "SerialNumber" = 12***
`
`

ioreg -l | grep -i 'serial-number' 
    |   "serial-number" = <594***0000000000000000000057513************941**00000000000000000000000000000000000000>
`
`

ioreg -l | grep -i 'device serial'
    | |   |   |     |   "device serial" = "K0075S*****         "
`
`

ioreg -l -w0 -p IODeviceTree | grep device-prop
``


![](http://www.hexley.com/images/hexley_450_pngs/hexley_sits_450.png)
Backup and checksum
-------------------
Usefull behaviors.
### Pseudo backup tools
This list is **not exhaustive** and this page is not about a complete guide on "how to backup well"; depending your tastes and tool availability, there are several ways to achieve correct backuping and many tools:
-   ditto
-   dump/restore
-   pax
-   rsync
-   scp
-   tar
For more information, take a look at <http://developer.apple.com/macosx/backuponmacosx.html>.
### Checksum
We use internally a checksum list for binary roots and binary drivers intregrity (not for security purpose).
The DarwinBuild project and the MacPorts project also maintain and check integrity of their sources and binaries.
Paranoid: Strong Fingerprints must be trusted and encrypted or stored in an encrypted disk image.
#### md5
Try to avoid for historic security purposes, collisions are easy to create.
#### SHA-1
Collisions can be created but it's "ok" for literal integrity purpose (not for fingerprint security purpose).

`/usr/bin/openssl sha1 mach_kernel`
`SHA1(BuildRoot/mach_kernel)= 19cecd3bd87c10bc4e2c167188a299a40c10d199`


Paranoid: Best is to use a concatenation of several strong checksums.

#### SHA-2 family
FIXME
Appendix
--------
### The dynamic linker library (dyld)
FIXME
dyld can:
-   Dynamically link new libraries into memory
-   Recover base addresses for existing libraries
Library offsets are not randomized between
-   invocations of the same program
-   invocations of different programs
but seems to not be the same from different leopard install.

FIXME

### Disable Spotlight for a volume and erase its current meta data

[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0) 







> > mdutil -E -i off $PUREDARWIN










### Defeat nmap fingerprint
Choose value between available choices:


`sysctl -w net.inet.tcp.blackhole=[0 | 1 | 2]`
`sysctl -w net.inet.udp.blackhole=[0 | 1]`




### Tools and more
bro
prelude
Found in MacPorts
SourceFire/Snort (MP)
chkrootkit (MP)
nmap (MP)
rkhunter (?)
tripwire (MP)
etc..


------------------------------------------------------------------------
Initial version on MMVIII VI VIII  2008/06/08