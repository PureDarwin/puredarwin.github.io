Armoring PureDarwin
===================
This page describes some ways to hardening PureDarwin (and intrinsically Darwin 9).
<span>Please feel free to contribute.</span>


Preamble
--------
_"Know your enemy"_ - Rage Against the Machine

Dictionary
--------
**hard** • <span style="font-weight:bold">en</span> |ˈhärdn|

verb
make or become hard or harder : [ intrans. ] _wait for the glue to harden_ | [ trans. ]_ bricks that seem to have been hardened by firing_.
-   make or become more severe and less sympathetic : [ trans. ] _she hardened her heart_.
-   make or become tougher and more clearly defined : [ intrans. ] _suspicion hardened into certainty_.
-   [ intrans. ] (of prices of stocks, commodities, etc.) _rise and remain steady at a higher level_.

## Disclaimer
<span style="color:rgb(255,0,0)"><span style="background-color:rgb(255,0,0)"><span style="color:rgb(0,0,0)"><span style="font-weight:bold"> WARNING! </span></span></span><span style="font-weight:bold"> YOU HAVE BEEN WARNED! NOW HOPE YOU KNOW WHAT YOU DO! <span style="background-color:rgb(255,0,0)"><span style="color:rgb(0,0,0)"> WARNING! </span></span></span></span>
<span style="font-weight:bold">
</span>

See above, you have been warned in <span style="color:rgb(255,0,0)">red</span>.
Also, take a look at [Legal](../legal.html) page.
<span style="color:rgb(176,189,204)">
</span>
<span style="color:rgb(176,189,204)">
</span>

![](http://www.hexley.com/images/hexley_450_pngs/hexley_bare_450.png)

Before installation
-------------------
### Usage
Assuming PureDarwin will be installed on<span style="font-family:courier new,monospace"><span style="font-size:small"> /Volume/Puredarwin</span></span><span style="font-family:arial,sans-serif">, these two variables below could be used in the following information.</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">export VOLUME="/Volume/PureDarwin"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">export DISK=`/bin/df | /usr/bin/grep "^/Volume/PureDarwin" | awk -F ' ' '{print $1}'`</span></span>
<span style="font-family:courier new">
</span>
You can also use setenv, according to your favorite shell.
Note that the ownership of the session is root.
### Command-line tools to securely erase
#### diskutil
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)

> > Securely erase a disk on $DISK
> > 
> > <span style="font-family:courier new">diskutil secureErase &lt;level&gt; $DISK</span>


<span style="font-family:courier new">
</span>
Securely erase freespace of a disk on $DISK

<span style="font-family:courier new,monospace">diskutil secureErase freespace &lt;level&gt; $DISK</span>
<span style="font-family:courier new">
</span>
3 levels are available in `man diskutil`:
1.  <span>Single pass randomly erase the disk</span>
2.  <span>US DoD 7 pass secure erase</span>
3.  <span>[Gutmann algorithm](http://www.cs.auckland.ac.nz/%7Epgut001/pubs/secure_del.html) 35 pass secure erase  </span>
#### rm
`rm' with <span style="font-family:courier new,monospace"><span style="font-size:small">-P</span></span> option will overwrite file(s) 3 times, first with the byte pattern 0xff, then 0x00 and finally 0xff before deleting them.
#### srm
Securely remove files or directories:

<span style="font-family:courier new,monospace">srm -r -m dir</span>
<span style="font-family:courier new">
</span>
Same as above, 3 levels available in `man srm':

> <span style="font-weight:bold">-s</span>  o<span>verwrites with a single pass of random data</span>
> <span><span style="font-weight:bold">-m</span> is the 7 US DoD compliant passes (0xF6, 0x00, 0xFF, random, 0x00, 0xFF, random)</span>
> <span>If neither is specified, the 35-pass [Gutmann algorithm](http://www.cs.auckland.ac.nz/%7Epgut001/pubs/secure_del.html) is used</span>

### Misc
#### Slim down pd_roots & pd_drivers list
Probability says <span style="font-style:italic">pd_roots</span> & <span style="font-style:italic">pd_drivers</span> may include unused packages with potential vulnerabilities.

By default, the list is big, too big:

<span style="font-family:courier new,monospace">cat pd_roots pd_drivers | wc -l</span>
<span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)">     183</span></span>
<span style="font-family:courier new">
</span>
Knowing what you're doing, you can safely remove more than hundred packages.
#### hdiutil compression
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)


> > hdiutil uses the DiskImages framework (FileVault encryption is supported) to manipulate disk images.
> > 
> > If you want to compress a folder:




<span style="font-family:courier new,monospace">hdiutil create -srcfolder "&lt;folder&gt;" -format UDBZ &lt;compressed folder&gt;.dmg</span>
<span style="font-family:courier new,monospace">srm -r &lt;folder&gt;</span>


In order to mount it later, it can be attached using hdiutil:

<span style="font-family:courier new,monospace">mkdir &lt;folder&gt;</span>
<span style="font-family:courier new,monospace">hdiutil attach -mountpoint &lt;compressed folder&gt;.dmg</span>
<span style="color:rgb(176,189,204);font-family:courier new">
</span>
<span style="color:rgb(176,189,204);font-family:courier new">
</span>
<span style="font-family:courier new"><span style="font-family:Arial">![](http://www.hexley.com/images/hexley_sits_450.png)</span></span>

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
<span style="font-family:courier new,monospace"><span style="font-size:small">if [ "${BootType}" = "singleuser" ];then </span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">    </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">authentification.sh</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">fi</span></span>
<span style="font-family:courier new">
</span>
Assuming authentification.sh is a "nice" script.
#### Using the deprecated /etc/passwd
According to the file itself, in the first comments:

<span style="font-family:courier new,monospace"><span style="font-size:small"># Note that this file is consulted directly only when the system is running</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># in single-user mode. At other times this information is provided by</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># Open Directory.</span></span>
<span style="font-family:courier new">
</span>
Try to change the shell PATH from:

<span style="font-family:courier new,monospace"><span style="font-size:small">root:*:0:0:System Administrator:/var/root:/bin/sh</span></span>

to:

<span style="font-family:courier new,monospace"><span style="font-size:small">root:*:0:0:System Administrator:/var/root:/dev/null</span></span>
#### Remove single user mode support from XNU
If you remove/disable the code portion of what activate/detect the single user mode (-s), there is no way to enter in single user mode.
A patch is needed in this case (<span style="font-weight:bold"><span style="color:rgb(255,0,0)">TODO</span>)</span>. 
#### Encrypt around
FIXME
### Configuring Access Warnings
FIXME
### PKI
PKI
<span style="color:rgb(176,189,204)">
</span>
<span style="color:rgb(176,189,204)">
</span>
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

<span style="font-family:courier new,monospace"><span style="font-size:small">sysctl -a | grep mem   </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">hw.physmem = 2147483648</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">hw.usermem = 1810808832</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">hw.memsize = 2147483648</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">hw.memsize: 2147483648</span></span></span>


A more human readable result of the swap usage:
<span style="font-family:courier new,monospace;font-size:small">sysctl -a | grep swap</span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">vm.swapusage: total = 1024.00M  used = 416.94M  free = 607.06M  </span></span></span>

#### hostinfo
<span style="font-family:courier new,monospace"><span style="font-size:small">Mach kernel version:</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Darwin Kernel Version 9.1.0: Wed Oct 31 17:46:22 PDT 2007; root:xnu-1228.0.2~1/RELEASE_I386</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Kernel configured for up to 2 processors.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">2 processors are physically available.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">2 processors are logically available.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Processor type: i486 (Intel 80486)Processors active: 0 1</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Primary memory available: 1.00 gigabytes</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Default processor set: 52 tasks, 211 threads, 2 processors</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Load average: 0.02, Mach factor: 1.96</span></span>
<span style="font-family:courier new"><span style="font-family:Arial"></span></span>
#### Mach virtual memory statistics: vm_stat
<span style="font-family:inherit">Rudimentary command, an (different) alternative of the missing `free' UNIX utility.</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">Mach Virtual Memory Statistics: (page size of 4096 bytes)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Pages free: 19385.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Pages active: 131831.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Pages inactive: 51339.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Pages wired down: 58216.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">"Translation faults": 6266580.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Pages copy-on-write: 161179.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Pages zero filled: 3302531.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Pages reactivated: 5342.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Pageins: 167299.</span></span>
<span style="font-weight:bold"><span style="font-family:courier new,monospace"><span style="font-size:small">Pageouts</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">: 3430.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Object cache: 24703 hits of 77103 lookups (32% hit rate)</span></span>

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
<span style="font-family:courier new,monospace"><span style="font-size:small">     boot - tell the kernel that system boot is complete (normally LoginWindow does this). May be useful to Darwin users.</span></span>

FIXME

#### Disable computer sleep
<span style="font-family:courier new,monospace"><span style="font-size:small">pmset -a sleep 0</span></span>
<span style="font-family:courier new">
</span>
0 to set the idle time to never
#### Enable hard disk sleep (disk spindown timer) 
<span style="font-family:courier new,monospace">pmset -a disksleep 1</span>
#### Disable wake on ethernet magic packet
<span style="font-family:courier new,monospace">pmset -a womp 0 </span>
#### Disable automatic restart on power loss
<span style="font-family:courier new,monospace"><span style="font-size:small">pmset -a autorestart 0</span></span>
#### Disable computer sleep when power button is pressed
<span style="font-family:courier new,monospace"><span style="font-size:small">pmset -a powerbutton 0</span></span>
### Permissions and filesystem
#### POSIX restrictive style
Use restrictive file mode as possible. Avoid file readable by anyone and writable (typically a 644) by the owner only.

<span style="font-family:courier new,monospace">chmod 600 *</span>
<span style="font-family:courier new">
</span>
Idem for folders.

<span style="font-family:courier new,monospace">sudo chmod 700 /Users/&lt;username&gt;</span>
#### Change global umask file permission
Persistent effects. (FIXME NOT TESTED)

<span style="font-family:courier new,monospace"><span style="font-size:small">sudo defaults write /Library/Preferences/.GlobalPreferences NSUmask 77</span></span>
<span style="font-family:courier new">
</span>
You can also use non persistent umask command illustrated by the example just below.

<span style="font-family:courier new,monospace"><span style="font-size:small">aladin@niwarderup:~/test% touch before_umask</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">aladin@niwarderup:~/test% mkdir before_umask_dir</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">aladin@niwarderup:~/test% umask 77</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">aladin@niwarderup:~/test% touch after_umask</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">aladin@niwarderup:~/test% mkdir after_umask_dir</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">aladin@niwarderup:~/test% ls -l</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">total 0</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-rw-r--r-- 1 aladin staff  0 Jun 20 19:07 before_umask</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">drwxr-xr-x 2 aladin staff 68 Jun 20 19:07 before_umask_dir</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-rw------- 1 aladin staff  0 Jun 20 19:07 after_umask</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">drwx------ 2 aladin staff 68 Jun 20 19:07 after_umask_dir</span></span>
#### Extended Attributes
Extended attributes extend the basic attributes associated with files and directories in the file system.
They are stored as name:data pairs associated with file system objects (files, directories, symlinks, etc).
xattr

<span style="font-family:courier new,monospace">ls -@l &lt;file&gt;</span>
FIXME
#### Locking file with chflags
Set the user immutable flag (owner or super-user only):

<span style="font-family:courier new,monospace">chflags uchg filename.txt</span>
#### Unlocking file with chflags
Clear the user immutable flag (owner or super-user only):

<span style="font-family:courier new,monospace">chflags nouchg filename.txt</span>
#### The suid/sgid (set-user/group-ID-on-execution) bit
Executable files with this bit set will run with effective uid set to the uid of the file owner. Moreover, directories with the set-user-id bit set will force all files and sub-directories created in them to be owned by the directory owner and not by the uid of the creating process.

<span style="font-family:courier new,monospace">find / -type f -perm -04001 -ls &gt; suid-files </span>
<span style="font-family:courier new,monospace">find / -type f -perm -02001 -ls &gt; sgid-files </span>
<span style="font-family:courier new,monospace">find / -type f -perm -04001 -user 0 -ls &gt; suid-root </span>
<span style="font-family:courier new,monospace">find / -type f -perm -02001 -group 0 -ls &gt; sgid-root </span>
<span style="font-family:courier new,monospace">find / -type f -perm -02001 -group 80 -ls &gt; sgid-admin
<span style="font-family:Arial">
This is a simple and effective example on Mac OS X (9.4.0) showing how suid is dangerous:
</span></span>
<div style="font-family:courier new,monospace">
whoami 
<div style="font-family:courier new,monospace">
<span style="color:rgb(102,102,102)">aladin</span>
<div style="font-family:courier new,monospace">
id
<div style="color:rgb(102,102,102)">
uid=501(aladin) gid=20(staff) groups=20(staff),98(_lpadmin),80(admin)

osascript -e "tell app "ARDAgent" to do shell script "whoami""
<span style="font-family:courier new,monospace"><span style="font-family:Arial"></span></span>
<div style="font-family:courier new,monospace;color:rgb(102,102,102)">
root
<div style="font-family:courier new,monospace">
osascript -e "tell app "ARDAgent" to do shell script "id""
<div style="font-family:courier new,monospace;color:rgb(102,102,102)">
uid=0(root) gid=0(wheel) egid=20(staff) groups=0(wheel),1(daemon),2(kmem),8(procview),29(certusers),3(sys),9(procmod),4(tty),5(operator),80(admin),20(staff)


#### Find writable file(s)
<span style="font-family:courier new,monospace">find / -type f -perm -02 -ls</span>
#### Find writable dir(s)
<span style="font-family:courier new,monospace">find / -type d -perm -02 -ls</span>
#### Kext permission rules
-   All files and folders in the KEXT, including the KEXT itself, must be owned by the root user (uid 0)
-   All files and folders in the KEXT, including the KEXT itself, must be owned by the wheel group (gid 0)
-   All folders in the KEXT, including the KEXT itself, must have the permissions 0755 (octal)
-   All files in the KEXT must have permissions 0644 (octal)
<!-- -->
-   A KEXT is not the place to store a user-space executable.
<span style="font-family:courier new,monospace">/usr/sbin/chown -R root:wheel MyKEXT.kext</span>
<span style="font-family:courier new">
</span>
<span style="font-family:courier new,monospace">find MyKEXT.kext -type d -exec /bin/chmod 0755 {} ;</span>
<span style="font-family:courier new,monospace">find MyKEXT.kext -type f -exec /bin/chmod 0644 {} ;</span>
#### Hard link
fixme
#### Symbolic link
fixme
### diskutil
#### Verify and repair permission
When you use diskutil to verify or repair disk permissions, it reads the Bill of Materials files from the Darwin installation and compares its list to the permissions on each file listed.

If the permissions differ, diskutil can repair them.

<span style="font-family:courier new,monospace">diskutil repairPermissions $PUREDARWIN</span>
#### Enable journaling (if supported by the FS)
<span style="font-family:courier new,monospace">diskutil enableJournal $PUREDARWIN/</span>
### Encrypting data
#### System swap
The kernel uses a pool of external swap files to support demand paging.
<span style="font-weight:bold">Caution</span>, it seems swap files aren't erased securely at startup.
<span style="font-family:inherit">Swap files reside in /private/var/vm/ directory:</span>


<span style="font-family:courier new">-rw------T  1 root  wheel    67108864 Jun 22 11:51 swapfile0</span>
<span style="font-family:courier new,monospace">-rw------T  1 root  wheel    67108864 Jun 22 19:02 swapfile1</span>

An external storage manager for dynamic pager is running as root, showing by `ps aux | grep dynamic`


<span style="font-family:courier new,monospace">root        26   0.0  0.1    75376    704   ??  Ss   11:50AM   0:00.01 /sbin/dynamic_pager -F /private/var/vm/swapfile</span>

Launched with /System/Library/LaunchDaemons/com.apple.dynamic_pager.plist
#### Disable swap file (caution)
Disabling swap needs caution.

Some program may require explicitly swap memory area.
What happens if no more physical memory available and swap is disabled?

Non persistent way:

<span style="font-family:courier new,monospace">sudo killall dynamic_pager</span>
<span style="font-family:courier new,monospace">sudo srm /private/var/vm/swapfile*</span>

Persistent way:
Edit /System/Library/LaunchDaemons/com.apple.dynamic_pager.plist and remove the nodes:
<span style="font-family:courier new,monospace">&lt;string&gt;/sbin/dynamic_pager&lt;/string&gt;
&lt;string&gt;-F&lt;/string&gt;
&lt;string&gt;/private/var/vm/swapfile&lt;/string&gt;</span>

Alternatively, the <span style="font-family:Courier New">Disabled &lt;boolean&gt;</span> optional key is used to disable (or not) the job.
Then wipe free space.
#### Encrypted swap file
#### <span style="font-family:courier new;font-size:13px;font-weight:normal"><span style="font-family:Arial">This is essentially used to prevent some potential local user "deviance".
PureDarwin, if it is not yet the case, will provide by default an encrypted swap partition.
The `dynamic_pager' daemon have an option to enable encryption:</span></span>
#### <span style="font-weight:normal"><span style="font-size:small"><span style="font-family:courier new,monospace">     -E      Encrypt the data in the swap files.</span></span></span>








Not sure if it is still working but.. try to put <span style="font-family:courier new,monospace">ENCRYPTSWAP=-YES-</span> in /etc/hostconfig or add the the respective launchd plist the corresponding arg.

<span style="font-family:inherit"><span style="text-decoration:underline">Notes:</span> Notice another mysterious option:</span>
<span style="font-family:courier new"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">     -P      This option is currently unimplemented.</span></span>
<span style="font-family:Arial"></span>
Although in the short getopt:

<span style="font-family:courier new,monospace"><span style="font-size:small">dynamic_pager: illegal option -- h</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">usage: dynamic_pager [-F filename] [-L low water alert trigger] [-H high water alert trigger] [-S file size] [</span></span><span style="font-weight:bold"><span style="font-family:courier new,monospace"><span style="font-size:small">-P priority</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">]</span></span>


#### Encrypt (and password protect) a folder with hdiutil
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)




> > <span style="font-family:courier new">hdiutil create -encryption AES-256 -stdinpass -srcfolder &lt;folder&gt; &lt;encrypted folder&gt;.dmg</span>




#### 
#### Decrypt a folder with hdiutil
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)



> > 
> > <span style="border-collapse:separate;color:rgb(37,37,37);font-family:courier new;line-height:21px">hdiutil attach -stdinpass &lt;encrypted folder&gt;.dmg</span>




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

<span><span style="font-family:courier new,monospace"><span style="font-size:small">fsck -fy</span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">mount -uw /</span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">launchctl load /System/Library/LaunchDaemons/com.apple.DirectoryServices.plist</span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">dscl . -passwd /Users/username [password]</span></span></span>
<span style="font-family:courier new">
</span>
Then reboot, or relaunch DirectoryServices.

Note that you can also use [pd_injectuser](../downloads.html) to recreate a user account, including his password.

<span><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/local/sbin/pd_injectuser</span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"></span></span>
#### Disable root account
<span style="font-weight:bold"><span style="font-weight:normal"><span><span style="font-family:courier new,monospace"><span style="font-size:small">dsenableroot -d -u username -p userpassword</span></span></span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"></span></span>
#### Enable root account (caution)
<span><span style="font-family:courier new,monospace"><span style="font-size:small">dsenableroot -u username -p userpassword -r rootpassword</span></span></span>
#### Restrict sudo use
Edit /etc/sudoers and limit the use of sudo to a single command per auth by adding:

<span style="font-family:courier new,monospace">Defaults timestamp_timeout=0</span>

Edit /etc/sudoers in order to restrict who can run sudo by removing:

<span style="font-family:courier new,monospace">%admin</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">ALL=(ALL) ALL</span>
<span style="font-family:courier new">
</span>
and add for each &lt;user&gt;:

<span style="font-family:courier new,monospace">&lt;user&gt; </span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">ALL=(ALL) ALL</span>
### ACL
#### Enable file ACL on the root file system
<span style="font-family:courier new,monospace">sudo fsaclctl â€“p / -e</span>
#### Disable file ACL on the root file system
<span style="font-family:courier new,monospace">sudo fsaclctl â€“p / -d</span>
#### Enable user based ACL for a file
Read access:

<span style="font-family:courier new,monospace">chmod +a "&lt;user&gt; allow read" &lt;file&gt;</span>
#### Enable group based ACL for a file
Allow write access:


<span style="font-family:courier new,monospace">chmod +a "&lt;group&gt; allow write" &lt;file&gt;</span>


Deny write access specifically:


<span style="font-family:courier new">chmod +a "&lt;user&gt; deny write" &lt;file&gt;</span>
#### View ACLs
<span style="font-family:courier new,monospace">ls -le &lt;file&gt;</span>
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

<span style="font-family:courier new,monospace">authpriv.*;remoteauth.crit /var/log/secure.log </span>

to

<span style="font-family:courier new,monospace">authpriv.*;remoteauth.err;auth.err /var/log/secure.log</span>
#### Limit number of message a syslogd rule generate
Enable facility of LOG_SECURITY:

<span style="font-family:courier new,monospace">/usr/sbin/sysctl -w net.inet.ip.fw.verbose=1</span>


Add <span style="font-family:courier new,monospace">logamount &lt;number&gt;</span> after the log keyword
Setting <span style="font-family:courier new,monospace">&lt;number&gt;</span> to <span style="font-family:courier new,monospace">0</span> removes limit.
#### local system logging
FIXME
/etc/newsyslog.conf configuration can sets
-   log file rotation based on size, last rotation time, or time of day
-   secure permissions to log files at rotation time
#### remote system logging
Local logging is not really reliable if the computer is compromised, local files can be modified, removed or short-circuited

Open /etc/syslog.conf to enable remote logging.
Add to the top:

<span style="font-family:courier new,monospace"><span style="font-size:small">*.* @&lt;remote log server address or host&gt;</span></span>

Restart `syslogd' with a hangup signal (or via launchctl):

<span style="font-family:courier new,monospace"><span style="font-size:small">sudo killall â€“HUP syslogd</span></span>

Edit /etc/syslog.conf and add /var/log/secure.log and /var/system.log to the host <span style="font-family:courier new,monospace"><span style="font-size:small">&lt;host&gt;</span></span>:


<span style="font-family:courier new,monospace"><span style="font-size:small">authpriv.*;remoteauth.err;auth.err @&lt;host&gt; </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">*.notice;authpriv,remoteauth,ftp,install.none;kern.debug;mail.crit @&lt;host&gt;</span></span>
<span style="font-family:courier new">
</span>
FIXME
#### Process accounting
FIXME
Logs all commands executed by all users.

To enable process accounting, create /var/account folder.

<span style="font-family:courier new,monospace">sudo mkdir -p /var/account</span>

Create /var/account/acct to store process accounting information:


<span style="font-family:courier new,monospace">sudo touch /var/account/acct</span>
<span style="font-family:courier new,monospace">chown -R root:admin /var/account</span>
<span style="font-family:courier new,monospace">chmod -R 660 /var/account</span>

Start accounting on the system:

<span style="font-family:courier new,monospace">sudo accton /var/account /acct</span>

It is launched at boot.

Use `lastcomm`to get information on previously executed commands.
#### Enable security audit
FIXME
Open /etc/hostconfig and add:

<span style="font-family:courier new,monospace">AUDIT=-YES-</span>

Restart.

<span style="font-family:courier new,monospace">audit -n</span> rotates the current log file.
<span style="font-family:courier new,monospace">audit -s</span> rotates the current log file and forces to reload settings from the audit_control file
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

<span style="font-family:courier new,monospace">kern.coredump=0 in /etc/sysctl.conf</span>

The non persistent way:

<span style="font-family:courier new,monospace">sysctl -w kern.coredump=0</span>
#### Limit core dump
Enable core dumps by adding the line <span style="font-family:courier new,monospace"><span style="font-size:small">limit core unlimited</span></span> in /etc/launchd.conf (persistent way).

The resulted dump(s) will be stored in /cores folder:

<span style="font-family:courier new,monospace"><span style="font-size:small">file /cores/core.57</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">/cores/core.57: Mach-O core i386</span></span>


Or from a shell (non persistent): <span style="font-size:small"><span style="font-family:courier new,monospace">ulimit -c unlimited</span></span>
<span style="font-family:courier new">
</span>
<span style="font-family:courier new"><span style="font-family:Arial"></span></span>
<span style="text-decoration:underline">Notes:</span> <span style="font-family:courier new,monospace"><span style="font-size:small">kill -ABRT &lt;pid&gt;</span></span> could be used in order to generate a core dump.
On Darwin8, change the line "COREDUMPS=-NO-" in /etc/hostconfig to "COREDUMPS=-YES-"
#### launchd 
FIXME
To send all launchd logs to a file, add in /etc/syslog.conf:

<span style="font-family:courier new,monospace">launchd.* /var/log/launchd.log</span>

Restart syslogd:

<span style="font-family:courier new,monospace">sudo kill -HUP `cat /var/run/syslog.pid`</span>

To increase the level of debugging:

<span style="font-family:courier new,monospace">sudo launchctl log level debug Password: ********</span>

FIXME
See [launchd](../developers/booting/launchd.html) page.
#### Enable lookupd debugging
<span style="font-family:courier new,monospace">sudo dscl . create /dsRecTypeStandard:Config/lookupd Debug YES</span>
<span style="font-family:courier new,monospace">sudo dscl . create /dsRecTypeStandard:Config/lookupd Trace YES</span>

Edit /etc/syslog.conf and replace <span style="font-family:courier new,monospace">netinfo.err</span> by <span style="font-family:courier new,monospace">netinfo.debug</span>

Restart daemons

<span style="font-family:courier new,monospace">sudo kill -HUP `cat /var/run/syslog.pid`</span>
<span style="font-family:courier new,monospace">sudo kill -HUP `cat /var/run/lookupd.pid`</span>
#### Disable lookupd debugging
<span style="font-family:courier new,monospace">sudo dscl . delete /dsRecTypeStandard:Config/lookupd</span>


Edit /etc/syslog.conf and replace <span style="font-family:courier new,monospace">netinfo.debug</span> with <span style="font-family:courier new,monospace">netinfo.err</span>

Restart daemons

<span style="font-family:courier new,monospace">sudo kill -HUP `cat /var/run/syslog.pid`</span>
<span style="font-family:courier new,monospace">sudo kill -HUP `cat /var/run/lookupd.pid</span>
#### diskarbitrationd
FIXME
Open /System/Library/LaunchDaemons/com.apple.diskarbitrationd.plist:


<span style="font-family:courier new,monospace">    &lt;key&gt;ProgramArguments&lt;/key&gt;</span>
<span style="font-family:courier new,monospace">    &lt;array&gt;</span>
<span style="font-family:courier new,monospace">        &lt;string&gt;/usr/sbin/diskarbitrationd&lt;/string&gt;</span>
<span style="font-family:courier new,monospace">    &lt;/array&gt;</span>


and simply append "-d":


<span style="font-family:courier new,monospace">    &lt;key&gt;ProgramArguments&lt;/key&gt;</span>
<span style="font-family:courier new,monospace">    &lt;array&gt;</span>
<span style="font-family:courier new,monospace">        &lt;string&gt;/usr/sbin/diskarbitrationd -d&lt;/string&gt;</span>
<span style="font-family:courier new,monospace">    &lt;/array&gt;</span>
FIXME
#### fs_usage
fs_usage reports system calls and page faults related to filesystem activity in real-time, often usefull for debugging.

Remember by default (without any options), fs_usage itself, Terminal, telnetd, sshd, rlogind, tcsh, csh and sh processes are excluded from the output.

Identify files used by an application at launchtime:

<span style="font-family:courier new,monospace">sudo fs_usage -w | grep &lt;application&gt;</span>

<span style="font-family:inherit">-w options forces wider, detailed, output.</span>

FIXME
#### DTrace {style="margin-top:10px;margin-bottom:10px;color:rgb(0,0,0);margin-left:10px;margin-right:0px"}
<span style="font-family:Helvetica"><span style="font-size:small">The generic front-end to the DTrace facility is a powerfull dynamic debugger and analysis tool.
See the [DTrace](dtrace.html) page.</span></span>


### Recompiling XNU
FIXME
See [The XNU kernel](../developers/xnu.1.html) page.
#### Usefull MacPorts
<span style="font-family:courier new,monospace">kernel-tools sysutils/kernel-tools 8J2135 Tools required to build xnu for Intel
gcc_select sysutils/gcc_select 0.1 Switch the default compiler
</span>After kernel-tools installed, the compilation will [fail](http://failblog.org) irremediably with some tool not found in /usr/local/bin/.
A quick fix with symbolic links:
<span style="font-family:courier new,monospace">/usr/local/bin/check_dylib-&gt;/opt/local/bin/check_dylib</span>
<span style="font-family:courier new,monospace">/usr/local/bin/checksyms-&gt;/opt/local/bin/checksyms</span>
<span style="font-family:courier new,monospace">/usr/local/bin/cmpshlib-&gt;/opt/local/bin/cmpshlib</span>
<span style="font-family:courier new,monospace">/usr/local/bin/decomment-&gt;/opt/local/bin/decomment</span>
<span style="font-family:courier new,monospace">/usr/local/bin/hack_libgcc-&gt;/opt/local/bin/hack_libgcc</span>
<span style="font-family:courier new,monospace">/usr/local/bin/indr-&gt;/opt/local/bin/indr</span>
<span style="font-family:courier new,monospace">/usr/local/bin/kern_tool-&gt;/opt/local/bin/kern_tool</span>
<span style="font-family:courier new,monospace">/usr/local/bin/kextsymboltool-&gt;/opt/local/bin/kextsymboltool</span>
<span style="font-family:courier new,monospace">/usr/local/bin/mkshlib-&gt;/opt/local/bin/mkshlib</span>
<span style="font-family:courier new,monospace">/usr/local/bin/seg_addr_table-&gt;/opt/local/bin/seg_addr_table</span>
<span style="font-family:courier new,monospace">/usr/local/bin/seg_hack-&gt;/opt/local/bin/seg_hack</span>
<span style="font-family:courier new,monospace">/usr/local/bin/relpath-&gt;/opt/local/bin/relpath</span>
#### Configuration files involved
FIXME
<span style="font-family:courier new,monospace">bsd/conf/MASTER           iokit/conf/MASTER.i386    libsa/conf/MASTER         osfmk/conf/MASTER.i386    security/conf/MASTER</span>
<span style="font-family:courier new,monospace">bsd/conf/MASTER.i386      libkern/conf/MASTER       libsa/conf/MASTER.i386    pexpert/conf/MASTER       security/conf/MASTER.i386</span>
<span style="font-family:courier new,monospace">iokit/conf/MASTER         libkern/conf/MASTER.i386  osfmk/conf/MASTER         pexpert/conf/MASTER.i386</span>

Note we don't use MASTER.ppc files although they are still existing.
#### Before
FIXME
ProductName:<span style="white-space:pre"> </span>Mac OS X
ProductVersion:<span style="white-space:pre"> </span>10.5.4
BuildVersion:<span style="white-space:pre"> </span>9E17

gcc version:
<span style="font-family:courier new,monospace">Using built-in specs.</span>
<span style="font-family:courier new,monospace">Target: i686-apple-darwin9</span>
<span style="font-family:courier new,monospace">Configured with: /var/tmp/gcc/gcc-5465~16/src/configure --disable-checking -enable-werror --prefix=/usr --mandir=/share/man --enable-languages=c,objc,c++,obj-c++ --program-transform-name=/^[cg][^.-]*$/s/$/-4.0/ --with-gxx-include-dir=/include/c++/4.0.0 --with-slibdir=/usr/lib --build=i686-apple-darwin9 --with-arch=apple --with-tune=generic --host=i686-apple-darwin9 --target=i686-apple-darwin9</span>
<span style="font-family:courier new,monospace">Thread model: posix</span>
<span style="font-family:courier new,monospace">gcc version 4.0.1 (Apple Inc. build 5465)</span>

#### Easy compilation
FIXME
<span style="font-size:13px"><span style="font-family:courier new,monospace">make KERNEL_CONFIGS="RELEASE" all VERBOSE=YES
</span></span>FIXME
#### After
FIXME
### Tweaking XNU
#### Secure levels "Ã  la OpenBSD"
<span style="color:rgb(255,153,0)">This is not yet implemented nor investigated.</span>
<span style="font-family:arial,sans-serif"><span style="font-size:small">Some security concepts "Ã  la OpenBSD" could be reused into Darwin, at least partially.</span></span>
<span style="font-family:arial,sans-serif"><span style="font-size:small">Security levels well known in OpenBSD â€œworldâ€? is going to be partially (and step by step) introduced and reused into PureDarwin. <span style="font-family:Arial"><span>According to [OpenBSD website](http://openbsd.org/), â€œ</span><span style="font-style:italic">Security levels essentially set how the kernel will handle system security</span>â€?.</span></span></span>
<span style="font-family:arial;font-size:13px">
</span>
<span style="font-family:arial,sans-serif"><span style="font-size:small">In OpenBSD, there are four security levels, from the less to the most secure level: -1, 0, 1, 2</span></span>
<span style="font-size:small">In PureDarwin, <span style="font-weight:bold">nyi</span>.</span>

In OpenBSD, securelevels are set from /etc/rc.securelevel
In PureDarwin, <span style="font-weight:bold">nyi. </span>securelevels are set from [unknown location/securelevel.plist]

In OpenBSD, the end of the boot process is showing which security level is used.
In PureDarwin, <span style="font-weight:bold">nyi</span>.

In OpenBSD, <span style="font-family:courier new,monospace"><span style="font-size:small">sysctl kern.securelevel=x</span></span> can be used to adjust "on live" the security level. In order to adjust from a higher security level to a lower security level, a reboot is needed.
In PureDarwin, `sysctl' is reporting the option (<span style="font-weight:bold">but not yet tested</span>)

<span style="font-family:courier new,monospace"><span style="font-size:small">kern.securelevel = 0</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">kern.securelevel: 0</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">kern.secure_kernel: 0</span></span>

In OpenBSD, securelevel -1: no additional kernel security features, nor restrictive permission. Not for production use.

In OpenBSD, securelevel 0: used at first boot. If securelevel 1 is set, it will be used after the boot process finish. There are no added features of securelevel 0.
In PureDarwin, ?

In OpenBSD, securelevel 1: /dev/mem and /dev/kmem cannot be write. Raw disk are read-only. etc...

In OpenBSD, securelevel 2: ...

#### Removing debug info
FIXME.
Take care of MACH_DEBUG.
According to <span style="font-family:Helvetica">osfmk/conf/MASTER configuration file:
</span>
<span style="font-family:Helvetica"></span>
<span style="font-family:courier new,monospace"># MACH_DEBUG enables the mach_debug_server, a message interface used to</span>
<span style="font-family:courier new,monospace">#</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">retrieve or control various statistics. This interface may expose data</span>
<span style="font-family:courier new,monospace">#</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">structures that would not normally be allowed outside the kernel, and</span>
<span style="font-family:courier new,monospace">#</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">MUST NOT be enabled on a released configuration.
options</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">MACH_DEBUG</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">#</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">#</span>
<span style="font-family:courier new,monospace">options</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">MACH_IPC_DEBUG</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">#</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">#</span>
<span style="font-family:courier new,monospace">#</span>
<span style="font-family:courier new,monospace">options</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">MACH_VM_DEBUG</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace">#</span><span style="white-space:pre"><span style="font-family:courier new,monospace"> </span></span><span style="font-family:courier new,monospace"># &lt;debug&gt;
</span>
FIXME
### authorization right
FIXME
/etc/authorization


<span style="color:rgb(0,0,0);text-decoration:none">![](http://www.hexley.com/images/hexley_450_pngs/hexley_worm_450.png)</span>
Network
-------
### Disable IPv6
<span style="font-family:courier new,monospace"><span style="font-size:small">networksetup -setv6off $iface</span></span><span style="font-size:small">
</span>
### ifconfig
Use a restrictive netmask.
### Detecting promiscuous mode
Several ways exist to detect promiscuous mode (potential running sniffer), you can use [DTrace](dtrace.html), simply parse `ifconfig' or even run a sniffer.
Without promisc mode, ifconfig looks like
<span style="font-family:courier new,monospace"><span style="font-size:small">/sbin/ifconfig en0</span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">en0: flags=8863&lt;UP,BROADCAST,SMART,RUNNING,SIMPLEX,MULTICAST&gt; mtu 1500</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-size:small">                </span></span></span><span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">ether 00:19:**:**:**:**</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-size:small">                </span></span></span><span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">media: autoselect status: inactive</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-size:small">                </span></span></span><span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">supported media: autoselect 10baseT/UTP &lt;half-duplex&gt; 10baseT/UTP &lt;full-duplex&gt; 10baseT/UTP &lt;full-duplex,hw-loopback&gt; 10baseT/UTP &lt;full-duplex,flow-control&gt; 100baseTX &lt;half-duplex&gt; 100baseTX &lt;full-duplex&gt; 100baseTX &lt;full-duplex,hw-loopback&gt; 100baseTX &lt;full-duplex,flow-control&gt; 1000baseT &lt;full-duplex&gt; 1000baseT &lt;full-duplex,hw-loopback&gt; 1000baseT &lt;full-duplex,flow-control&gt; none</span></span></span>

With promisc mode activated:

<span style="font-family:courier new,monospace"><span style="font-size:small">/sbin/ifconfig en0</span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">en0: flags=8963&lt;UP,BROADCAST,SMART,RUNNING,</span></span><span style="font-weight:bold"><span style="color:rgb(102,102,102)"><span style="font-size:small">PROMISC</span></span></span><span style="color:rgb(102,102,102)"><span style="font-size:small">,SIMPLEX,MULTICAST&gt; mtu 1500</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">        ether 00:19:**:**:**:** </span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">        media: autoselect status: inactive</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">        supported media: autoselect 10baseT/UTP &lt;half-duplex&gt; 10baseT/UTP &lt;full-duplex&gt; 10baseT/UTP &lt;full-duplex,hw-loopback&gt; 10baseT/UTP &lt;full-duplex,flow-control&gt; 100baseTX &lt;half-duplex&gt; 100baseTX &lt;full-duplex&gt; 100baseTX &lt;full-duplex,hw-loopback&gt; 100baseTX &lt;full-duplex,flow-control&gt; 1000baseT &lt;full-duplex&gt; 1000baseT &lt;full-duplex,hw-loopback&gt; 1000baseT &lt;full-duplex,flow-control&gt; none</span></span></span>
### netstat
<span style="font-family:inherit">Be carefull with netstat, it is not so hard to compromise "its results".</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">netstat -anp tcp </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">netstat -anp udp</span></span>
### lsof
<span style="font-family:courier new,monospace"><span style="font-size:small">lsof -i tcp</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">lsof -i udp</span></span>
<span style="font-family:courier new"><span style="font-family:Arial"></span></span>
### Firewall {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
#### ipfw {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
The default rule is not really restrictive:

<span style="font-family:courier new,monospace"><span style="font-size:small">#ipfw list</span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">65535 allow ip from any to any</span></span></span>

Same for the IPv6 network stack, the default rules list looks like:

<span style="font-family:courier new,monospace"><span style="font-size:small">ip6fw list</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">33300 deny ipv6-icmp from any to any in icmptype 128</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">65535 allow ipv6 from any to any</span></span></span>
#### ipfw traffic shapping {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
If the bandwidth used can be known (estimation at least; if the use is "constant" it is really efficient) in advance, allocating only the requested amount will not let enough "space" (bandwidth) available for an intruder.

As an example, create a pipe that only allows up to 42KB/s to go through.

<span style="font-family:courier new,monospace"><span style="font-size:small">sudo ipfw pipe 1 cg</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">onfi</span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> bw 42KByte/s</span></span>

Attach that pipe to the outgoing traffic on port 22, effectively limiting the outgoing traffic of sshd.

<div style="font-family:courier new,monospace">
<span style="font-size:small">sudo ipfw add 1 pipe 1 src-port 22</span>

Remove the pipe from the port.

<div style="font-family:courier new,monospace">
<span style="font-size:small">sudo ipfw delete 1</span>
#### firewall state in sysctl {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
The state of the firewall (enabled or disabled) can be changed by directly changing a kernel parameter.

Enable the firewall (default):
<span style="font-family:courier new,monospace"><span style="font-size:small">sysctl -w net.inet.ip.fw.enable=0 </span></span>

Disables the firewall:
<span style="font-family:courier new,monospace"><span style="font-size:small">sysctl -w net.inet.ip.fw.enable=1 </span></span>

More info:
<div style="font-family:courier new,monospace">
net.inet.ip.fw.verbose_limit: 0
<div style="font-family:courier new,monospace">
net.inet.ip.fw.verbose: 2
<div style="font-family:courier new,monospace">
net.inet.ip.fw.debug: 0
<div style="font-family:courier new,monospace">
net.inet.ip.fw.one_pass: 0
<div style="font-family:courier new,monospace">
net.inet.ip.fw.autoinc_step: 100
<div style="font-family:courier new,monospace">
net.inet.ip.fw.enable: 1
#### Rules examples {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
TODO
#### Block dns multicast (5353)
<span style="font-family:courier new,monospace"><span style="font-size:small">grep -i 5353 /etc/services </span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">mdns            5353/udp    # Multicast DNS</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-size:small">mdns            5353/tcp    # Multicast DNS</span></span></span>
FIXME
#### Activating NAT on server side {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
FIXME
Create /etc/natd.conf and add:

<span style="font-family:courier new,monospace">interface en0 </span>
<span style="font-family:courier new,monospace">same_ports yes </span>
<span style="font-family:courier new,monospace">use_sockets yes </span>
<span style="font-family:courier new,monospace">unregistered_only yes</span>

Add <span style="font-family:courier new,monospace">dynamic yes</span> if you have a dynamic IP.
Add <span style="font-family:courier new,monospace">log_denied no</span> if you want to log packets blocked by the NAT device

Configure internal interface en0 with a private address (i.e: 192.168.1.1)

Enable IP forwarding in the kernel, it's needed.
Non persistent way:

<span style="font-family:courier new,monospace">sysctl -w net.inet.ip.forwarding=1</span>

Persistent way, in /etc/hostconfig, add or change the value to <span style="font-family:courier new,monospace">IPFORWARDING=-YES-</span>

Route packets from the internal network to the external one via en0:

<span style="font-family:courier new,monospace">ipfw add divert natd ip from any to any via en0</span>

Launch natd:

<span style="font-family:courier new,monospace">/usr/sbin/natd -f /etc/natd.conf</span>
#### Use NAT on client side
IP address: 192.168.1.* (obviously 192.168.1.1 is reserved)
Subnet mask: 255.255.254.0 
Gateway/default router: 192.168.1.1 
DNS servers: same as the router (but not necessarily)
#### Enable a caching name server on NAT server side
In /etc/hostconfig, add or change the line to <span style="font-family:courier new,monospace">DNSSERVER=-YES-</span>
<span style="color:rgb(0,102,204);text-decoration:underline">
</span>


<span style="color:rgb(0,0,0);text-decoration:none">![](http://www.hexley.com/images/hexley_450_pngs/hexley_pkg_450.png)</span>
Services
--------
### Cups
FIXME
By default, all local user can access to http://127.0.0.1:631 (a web admin front-end).
#### Enable cupsd service
<span style="font-family:courier new,monospace">sudo launchctl load -w /System/Library/LaunchDaemons/org.cups.cupsd.plist </span>
#### Disable cupsd service
<span style="font-family:courier new,monospace">sudo launchctl unload -w /System/Library/LaunchDaemons/org.cups.cupsd.plist </span>
FIXME
### ftp
#### Disable ftp
<span style="font-family:courier new,monospace">launctl unload -w /System/Library/LaunchDaemons/ftp.plist</span>
#### Enable ftp
<span style="font-family:courier new,monospace">launctl load -w /System/Library/LaunchDaemons/ftp.plist </span>
### Samba
#### Disable SMB
<span style="font-family:courier new,monospace">defaults delete /Library/Preferences/SystemConfiguration/com.apple.smb.server EnabledServices</span>

<span style="font-family:courier new,monospace">launctl unload -w /System/Library/LaunchDaemons/nmbd.plist </span>
<span style="font-family:courier new,monospace">launctl unload -w /System/Library/LaunchDaemons/smbd.plist </span>

### AFP
#### Disable Apple File Server
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)
<span style="font-family:courier new">
</span>





> > <span style="font-family:courier new">launctl unload -w /System/Library/LaunchDaemons/com.apple.AppleFileServer.plist</span>






<span style="font-family:courier new">
</span>
### ntp
FIXME
/etc/ntp.conf
### NFS
FIXME
#### Disable NFS
<span style="font-family:courier new,monospace">launchctl unload -w /System/Library/LaunchDaemons/com.apple.portmap.plist</span>
<span style="font-family:courier new,monospace">launchctl unload -w /System/Library/LaunchDaemons/org.postfix.master.plist</span>

#### Enable NFS
<span style="font-family:courier new,monospace">launchctl load -w /System/Library/LaunchDaemons/com.apple.portmap.plist</span>
<span style="font-family:courier new,monospace">launchctl load -w /System/Library/LaunchDaemons/org.postfix.master.plist</span>
### Bonjour
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0)






> > FIXME






#### Disable Bonjour
<span style="font-family:courier new,monospace">sudo launchctl load -w /System/Library/LaunchDaemons/com.apple.mDNSResponder.plist</span>
#### Enable Bonjour
<span style="font-family:courier new,monospace">sudo launchctl load -w /System/Library/LaunchDaemons/com.apple.mDNSResponder.plist</span>
#### Change Bonjour hostname
No spaces or non-DNS characters allowed for &lt;hostname&gt;

<span style="font-family:courier new,monospace">scutil --set LocalHostName &lt;hostname&gt;</span>

...

### SSH
FIXME
There are so many tutorials available about how to configure and/or secure sshd that we do not need to explain these points.
#### Check fingerprint
Prints fingerprint of the serverâ€™s RSA key:

<span style="font-family:courier new,monospace">ssh-keygen -l -f /private/etc/ssh_host_rsa_key.pub</span>


FIXME
#### sshd
FIXME
#### Client's side
FIXME
Edit /private/etc/sshd_config

Change <span style="font-family:courier new,monospace">PasswordAuthentication yes</span> to <span style="font-family:courier new,monospace">PasswordAuthentication no</span>
Change <span style="font-family:courier new,monospace">RSAAuthentication yes</span> to <span style="font-family:courier new,monospace">RSAAuthentication no</span> if key-based authentication is used
#### more
FIXME
#### Tunneling
From the man:


<span style="font-family:courier new,monospace"><span style="font-size:small"> The following example tunnels an IRC session from client machine ``127.0.0.1'' (localhost) to remote server</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">     ``server.example.com'':</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">         $ ssh -f -L 1234:localhost:6667 server.example.com sleep 10</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">         $ irc -c '#users' -p 1234 pinky 127.0.0.1</span></span>

<span style="color:rgb(176,189,204)">
</span>
![](http://www.hexley.com/images/hexley_450_pngs/hexley_key_450.png)
Perimetric security
-------------------
### Preventing RF eavesdroppers
#### Faraday cage
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Blocks out external static electrical fields and shield the interior from external electromagnetic radiation. </span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Named after physicist [Michael Faraday](http://en.wikipedia.org/wiki/Michael_Faraday "Michael Faraday"), who built one in 1836.</span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">
</span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">You can also encrypt your communication and/or add noise if you cannot managed to block output emits, though according to "[Shannon](http://en.wikipedia.org/wiki/Claude_E._Shannon)", it's probably not the most efficient way.</span>
#### Wireless emission
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">No driver reported to work at this time. See [Network page](../developers/network.html) for update.</span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">freeradius and openradius (802.11X could be then tested, though wireless is not mandatory for this kind of service).</span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Reduce power emit.</span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Add "many" fakeap clones.</span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">WPA2 minimum.</span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">etc... </span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px"><span style="font-family:Arial;line-height:normal;border-collapse:collapse">http://www.swisswireless.org/wlan_calc_en.html</span></span>
#### Bluetooth
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">No support known on Darwin (need investigation).</span>
#### Screen disclosure
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Away from the screen, no information nor open privileged prompt should remain.</span>
<span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Potential solution(s):</span>
-   <span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">removing scrollback buffer (is it possible on Darwin? is there any scrollback first?)</span>
-   <span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Screen blanking</span>
-   <span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Automatic logout (nyi)</span>
-   <span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">Screensaver</span>
-   <span style="border-collapse:separate;font-family:-webkit-sans-serif;line-height:19px">etc..</span>
### Disable some kext to avoid potential physical security flaws 
#### Remove Airport support
No driver available at this time or reported to work, although the operation should be similar as below.

You can safely remove it if you don't plan to use wireless network interface:
<span style="font-family:courier new;font-size:12px">sudo srm -Rf /System/Library/Extensions/AppleAirPort.kext</span>
<span style="font-family:courier new;font-size:12px">sudo touch /System/Library/Extensions</span>













#### Remove bluetooth support
No driver available at this time or reported to work, although the operation should be similar as below.

Prevent someone to reach your computer bluetooth:
<span style="font-family:courier new,monospace"><span style="font-size:small">sudo srm -Rf /System/Library/Extensions/IOBluetoothFamily.kext</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">sudo srm -Rf /System/Library/Extensions/IOBluetoothHIDDriver.kext</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">sudo touch /System/Library/Extensions</span></span>
#### Removing audio support
#### <span style="font-size:13px;font-weight:normal">No driver available at this time or reported to work, although the operation should be similar as below.</span>
#### <span style="font-size:13px;font-weight:normal">Prevent someone to listen your microphone:</span>
<span style="font-family:courier new,monospace;font-size:small">sudo srm -Rf /System/Library/Extensions/AppleOnboardAudio.kext 
sudo srm -Rf /System/Library/Extensions/AppleUSBAudio.kext 
sudo srm -Rf /System/Library/Extensions/AudioDeviceTreeUpdater.kext 
sudo srm -Rf /System/Library/Extensions/IOAudioFamily.kext 
sudo srm -Rf /System/Library/Extensions/VirtualAudioDriver.kext
sudo touch /System/Library/Extensions</span>












#### Removing video support
No driver available at this time or reported to work, although the operation should be similar as below.
Prevent someone trying to watch your webcam:
<span style="font-family:courier new;font-size:12px">sudo srm -rf /System/Library/Extensions/Apple_iSight.kext</span>
<span style="font-family:courier new;font-size:12px">sudo srm -rf /System/Library/Extensions/IOUSBFamily.kext/Contents/PlugIns/AppleUSBVideoSupport.kext </span>
<span style="font-family:courier new;font-size:12px">sudo touch /System/Library/Extensions</span>













#### Removing USB support
<span style="font-weight:bold">Warning: </span>Since we boot on USB we shouldn't remove this one.
You probably can safely remove this one if you boot on firewire, cdrom, in a vm or other medium:

<span style="font-family:courier new,monospace"><span style="font-size:small">sudo srm -rf /System/Library/Extensions/IOUSBMassStorageClass.kext</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">sudo touch /System/Library/Extensions</span></span>
#### Removing FireWire support
Except if you boot on firewire or simply need it, you could safely remove this one:

<span style="font-family:courier new,monospace"><span style="font-size:small">sudo srm -rf /System/Library/Extensions/IOFireWireSerialBusProtocolTransport.kext</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">sudo touch /System/Library/Extensions</span></span>
<span style="font-family:courier new"><span style="font-family:Arial"></span></span>
### Serialization {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
#### <span style="font-size:15px">i</span>oreg
The I/O Kit registry is an abstraction layer of some logical and physical information. We can use it to retrieve some unique identifiers.
Write somewhere (away from your computer) as serials you will find as possible:

<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -c "IOPlatformExpertDevice" | awk -F '"' '/IOPlatformSerialNumber/ {print $4}'</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">Q723******</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -c "IOPlatformExpertDevice" | awk -F '"' '/product-name/ {print $4}'</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">MacBook2,1</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -c "IOPlatformExpertDevice" | awk -F '"' '/board-id/ {print $4}'</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">Mac-F420****</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -c "IOPlatformExpertDevice" | awk -F '"' '/IOPlatformUUID/ {print $4}'</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">00000000-0000-**00-**00-0019E33****</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -c "ATADeviceNub" | awk -F '"' '/device serial/ {print $4}'          </span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">K0075******</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -c "AppleAHCIDiskDriver" | awk -F '"' '/Serial Number/ {print $4}'</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">        K439T7******</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>

<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -l | grep -i 'serial number'</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">    | |   |         |   "Serial Number" = "        K439********"</span></span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span></span>

<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -l | grep -i 'serialnumber'</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">    |   "IOPlatformSerialNumber" = "WQ7********"</span></span></span></span>

<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">    | |           "BatterySerialNumber" = "DP-ASM****-3***-3***"</span></span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">    | |           "SerialNumber" = 12***</span></span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span></span>

<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -l | grep -i 'serial-number' </span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">    |   "serial-number" = &lt;594***0000000000000000000057513************941**00000000000000000000000000000000000000&gt;</span></span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span></span>

<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -l | grep -i 'device serial'</span></span></span>
<span><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">    | |   |   |     |   "device serial" = "K0075S*****         "</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>

<span><span style="font-family:courier new,monospace"><span style="font-size:small">ioreg -l -w0 -p IODeviceTree | grep device-prop
</span></span></span><span style="font-family:courier new,monospace"><span style="color:rgb(102,102,102)"><span style="font-family:courier new,monospace"><span style="font-size:small">   | |   "device-properties" = &lt;ef0900000100000002000000280900002700000002010c00d.....</span></span>
</span></span>

<span style="font-family:inherit"></span>
![](http://www.hexley.com/images/hexley_450_pngs/hexley_sits_450.png)
Backup and checksum
-------------------
Usefull behaviors.
### Pseudo backup tools
This list is <span style="font-weight:bold">not exhaustive</span> and this page is not about a complete guide on "how to backup well"; depending your tastes and tool availability, there are several ways to achieve correct backuping and many tools:
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
<span style="color:rgb(255,0,0)"><span style="font-weight:bold">Paranoid:</span></span> Strong Fingerprints must be trusted and encrypted or stored in an encrypted disk image.
#### md5
Try to avoid for historic security purposes, collisions are easy to create.
#### SHA-1
Collisions can be created but it's "ok" for literal integrity purpose (not for fingerprint security purpose).

<span style="font-family:courier new,monospace"><span style="font-size:small">/usr/bin/openssl sha1 mach_kernel</span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(68,68,68)"><span style="font-size:small">SHA1(BuildRoot/mach_kernel)= 19cecd3bd87c10bc4e2c167188a299a40c10d199</span></span></span>


<span style="color:rgb(255,0,0)"><span style="font-weight:bold">Paranoid:</span></span> Best is to use a concatenation of several strong checksums.

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
<span style="font-family:courier new"><span style="font-family:Arial"></span></span>
### Disable Spotlight for a volume and erase its current meta data

[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/xicon.jpg)](armoring-puredarwin/xicon.jpg%3Fattredirects=0) 







> > <span style="font-family:courier new"><span style="font-size:small">mdutil -E -i off $PUREDARWIN</span></span>







<span style="font-family:courier new"><span style="font-family:Arial"></span></span>


### Defeat nmap fingerprint
Choose value between available choices:


<span style="font-family:courier new,monospace"><span style="font-size:small">sysctl -w net.inet.tcp.blackhole=[0 | 1 | 2]</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">sysctl -w net.inet.udp.blackhole=[0 | 1]</span></span>
<span style="font-family:courier new">
</span>
<span style="font-family:courier new"><span style="font-family:Arial"></span></span>
<span style="color:rgb(255,0,0)">It doesnt seem to have any effect.<span style="color:rgb(0,0,0)">
</span></span>
### Tools and more
bro
<span style="color:rgb(255,0,0)"><span style="color:rgb(0,0,0)">prelude
Found in MacPorts
SourceFire/Snort (MP)
chkrootkit (MP)
nmap (MP)
rkhunter (?)
tripwire (MP)</span></span>
etc..

<span style="font-size:10px"></span>
------------------------------------------------------------------------
<span style="font-size:10px">Initial version on MMVIII VI VIII  2008/06/08</span>