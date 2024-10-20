User management
===============
This page is about user management in Darwin. It is a work in progress.
Because user management has changed since Darwin 8 via Darwin 9 to Darwin10, this does not fully apply for versions prior to 9 and greater than 9.

Status
------------------------------------------------------------------------------


**Nasty nasty fix:** `securityd' seems to work reliably if you force it to stick to a single thread (by adding -`t 1` to its .plist). Which is bound to cause us more problems in the future. The most problematic point is the frequency of deadlock (significant impact) with this workaround.

![](/img/users/users/login%20with%20security%20running%20in%20single%20thread.png)


**Less nasty nasty fix:** `securityd' seems also to work reliably with 10 threads. Add `-t 10` to its .plist, that will also decrease the chance to hit a deadlock.




PAM Error (line 396): Cannot make/remove an entry for the specified session`
`


Examining the config file /etc/pam.d/login, it would appear that the modules `pam_launchd` and `pam_uwtmp` are responsible for creating sessions. Further, it seems from debug output that the problem lies within `pam_launchd`.

Thanks to Apple's Damien Sorresso on the launchd-dev mailing list for providing the answer to this. login needs a new security session created for it before it can set it up for the new user. This is what sshd does for in-coming users, and what loginwindow.app does for GUI users under OS X. For the moment, a small PAM module (pam_sessioncreate, available on the [Downloads](../downloads.html) page) can be added to /usr/lib/pam/ and to /etc/pam.d/login just above pam_launchd ("session required pam_sessioncreate.so") to create the necessary session. The file should now include:


[...]





[...]



And then...


Welcome to PureDarwin!`
`



![](/img/users/users/login%20via%20ssh.png)


Old problem:


This was solved using the latest PureFoundation root, which added missing symbols (CFStringTransform(), CFPreferencesValueIsForced()) to CFLite and fixed a few bugs it introduced itself.
Open Directory
--------------
[Open Directory](http://developer.apple.com/documentation/Networking/Conceptual/Open_Directory/), which covers client and server side, is composed of
-   DirectoryServices daemon
-   Open Directory plug-ins (LDAPv2v3, NetInfo, AppleTalk, Bonjour, Windows...)
Directory Services
------------------
[Directory Services](http://developer.apple.com/opensource/dirservices/) is the component that manages users and permissions, among other things (ie: mount records, service discovery, etc...).
Commands of this abstraction layer (here an API) related to Directory Service operate on Open Directory nodes (list, create, read and manage data).

A directory service is a collection of one or more nodes, where a node is a place that can be searched for information.

Notes: All security framework auth uses Directory Services

It seems that the DirectoryServicesDaemon provided in 9J61 prevents any user to login:
Jul 22 23:31:07 PureDarwin com.apple.SecurityServer[18]: Entering service
Jul 22 23:31:17 PureDarwin com.apple.SecurityServer[18]: getpwnam() failed for user toor, creating invalid credential
Jul 22 23:31:17 PureDarwin com.apple.SecurityServer[18]: getpwnam() failed for user toor, creating invalid credential
Jul 22 23:31:17 PureDarwin com.apple.SecurityServer[18]: Failed to authorize right system.login.tty by client /usr/bin/login for authorization created by /usr/bin/login.

In the contrary, still no problem with the one from 9G55
Jul 22 23:33:58 PureDarwin com.apple.SecurityServer[18]: Entering service
Jul 22 23:34:03 PureDarwin com.apple.SecurityServer[18]: checkpw() succeeded, creating credential for user toor
Jul 22 23:34:03 PureDarwin com.apple.SecurityServer[18]: checkpw() succeeded, creating shared credential for user toor
Jul 22 23:34:03 PureDarwin com.apple.SecurityServer[18]: Succeeded authorizing right system.login.tty by client /usr/bin/login for authorization created by /usr/bin/login.

Some dependencies also differ between the both binaries (/usr/local/DirectoryService).

/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.17.0)
/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.18.0)
/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 677.22.0)
/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 677.24.0)

/System/Library/Frameworks/Security.framework/Versions/A/Security (compatibility version 1.0.0, current version 34102.0.0)
/System/Library/Frameworks/Security.framework/Versions/A/Security (compatibility version 1.0.0, current version 36371.0.0)

/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.3)
/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.4)

Need investigations.
### /var/db/dslocal/
This is the location where Directory Service stores information about users and permissions for a local machine (DirectoryService can be used over the network, too).
#### /var/db/dslocal/nodes/Default/users/
This directory contains many plist files.
The filename is related to the respective existing user.

The content of a (minimal?) generic */var/db/dslocal/nodes/Default/<user>.plist* (shadowed hash enabled) looks like:


`<?xml version="1.0" encoding="UTF-8"?>`
`<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">`
`<plist version="1.0">`
`<dict>`
 `<key>authentication_authority</key>`
 `<array>`
 `<string>;ShadowHash;</string>`
 `</array>`
 `<key>generateduid</key>`
 `<array>`
 ``
 `</array>`
 `<key>gid</key>`
 `<array>`
 ``
 `</array>`
 `<key>home</key>`
 `<array>`
 ``
 `</array>`
 `<key>name</key>`
 `<array>`
 <span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<user>&lt;/string&gt;</span></span>
 `</array>`
 `<key>passwd</key>`
 `<array>`
 `<string>********</string>`
 `</array>`
 `<key>realname</key>`
 `<array>`
 ``
 `</array>`
 `<key>shell</key>`
 `<array>`
 ``
 `</array>`
 `<key>uid</key>`
 `<array>`
 ``
 `</array>`
`</dict>`
`</plist>`

This authentication authority attribute line 

A generic authentication authority attribute (semicolon-delimited) looks like:


``


In fact, Open Directory supports many types of authentication:
-   <string>;Basic;</string> Basic (supports Crypt password)
-   
-   
-   <string>;LocalWindowsHash;</string> Local Windows (NTLM)
-   <span style="font-family:courier new;font-size:12px">&lt;string&gt;;LocalCachedUser;/LDAPv3/foobar.domain:<user>:<uuid>&lt;/string&gt; </span>Local Cached User (LDAP)
-   <string>;Kerberosv5;; Kerberosv5 ;0x3f...</string> Kerberos v5
-   <string>;DisabledUser;;ShadowHash;</string> Disabled (prevents any authentication, account is disabled)
Also, Inside 


`<string>;Kerberosv5;;`<user>`@LKDC:SHA1.`<hexadecimal string>`;LKDC:SHA1.`


Notice the &lt;user&gt; is associated to an Universally Unique IDentifier (UUID) 
According to `*man uuidgen*`:


`     The UUID is printed to standard output as a hyphen-punctuated ASCII`
`     string of the form: EEF45689-BBE5-4FB6-9E80-41B78F6578E2 (in printf(3)`
`     format "%08X-%04X-%04X-%04X-%012X") [...]`

Finally, this directory seems like the deprecated /etc/passwd file (Note that /etc/passwd is still used in single user mode), where xml plist files (newschool side) are lines (oldschool side).
In the same manner (oldschool, newschool, you should have better stay at school ;)), the shadowed passwords are not stored in /etc/shadow by lines, but by files in /var/db/shadow/hash/ directory.

For your information, root account UUID is fixed to `FFFFEEEE-DDDD-CCCC-BBBB-AAAA00000000`. Not sure it can and/or should be changed.
#### /var/db/dslocal/nodes/Default/group/
This directory contains many plist files related to available and private groups.
The filename is related to the respective group name.

(please add text)
#### /var/db/shadow/hash/
This directory is populated with two kinds of file.
-   An optional <span style="font-style:italic">/var/db/shadown/hash/<uuid>.state, a binary plist which can be converted with plutil (is it available for Darwin ??).
    This file is created when it doesn't exist and while corresponding user logs in.
    See inside:</span>
> > <?xml version="1.0" encoding="UTF-8"?>
> > <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
> > <plist version="1.0">
> > <dict>
> >  <key>CreationDate</key>
> >  
> >  <key>FailedLoginCount</key>
> >  
> >  <key>LastLoginDate</key>
> >  
> >  <key>NewPasswordRequired</key>
> >  
> > </dict>
> > </plist>
-   A shadow file <span style="font-style:italic">/var/db/shadown/hash/<uuid></span>, named according to the corresponding UUID found in <span style="font-style:italic">/var/db/dslocal/Default/nodes/users/<user>.plist</span>.
    One line of 620 bytes with around 96% of 0...
> <span style="font-family:courier new;font-size:12px">0000000000000000000000000000000000000000000000000000000000000000<span style="color:rgb(0,0,255)">0000000000000000000000000000000000000
> 000</span>0000000000000000000000000000000000000000000000000000000000000000<salt:4bytes><sha1:20bytes>0000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
> 0000000</span>
> 
> The orange part corresponds to the LANMAN (NTLM) password (32 bytes).
> The blue part is reserved for "unsalted" SHA1 digest (20 bytes).
> The green part is for md5 hash, another power of 2 (32 bytes).
> The <salt:4bytes><sha1:20bytes> (24 bytes) is composed of a salt and a corresponding hash generated from this salt and given password:
>
> -   The salt is easy to generate or can be choosen freely.
>     Remember to use uppercase letters (it seems lowercase are not expected leading to login fail).
> > # openssl rand 4 | xxd -p | tr ' a-z' ' A-Z'
> > <span style="font-family:courier new;font-size:12px">1E677D44
> > </span>
> -   The SHA1 hash, based on digest with provided password can be generated via openssl.
>     Notice the salt must be passed as a binary data. Also do not forget to use uppercase letters.
> > # HEX_SALT=`openssl rand 4 | xxd -p | tr ' a-z' ' A-Z'`
> > # BIN_SALT=`echo -n ${HEX_SALT} | xxd -r -p`
> > <span style="font-family:courier new;font-size:12px"># SHA_HASH=`printf "%s%s" ${BIN_SALT} "<password>"} | openssl dgst -sha1 | tr ' a-z' ' A-Z'`
> > 
> > # echo ${HEX_SALT}${SHA_HASH}
> > 1E677D44EE801D51CE90C5E845E232809FDB22FFF600F409
> > </span>

Most of the following content (

Notes: It seems random UUID is allowed.
### Command line tool: dscl
The *dscl* ** (Directory Service Command Line) tool is used in Darwin to manage users. *dscl* is part of the Darwin project DSTools. *dscl* is now (mostly) usable in a PureDarwin environment using the latest PureFoundation.root. (Not every option has been explored yet, so use may result in unpredictable results.)
### passwd tool
So classic.
Caution: If root account is disabled, using `*passwd root*` will enable it, leading to potential security flaw (see [Armoring PureDarwin](../curious/armoring-puredarwin.html) page).

PAM
---
PAM ("Pluggable Authentication Modules", contained in the projects *pam* and *pam_modules* is required for a working login. PAM is what verifies the username and password at login time. If both are mising, you get an error about libpam missing when you try to log in. If only pam_modules is missing, then you get a "Login:" prompt but no "Password:" prompt, instead you get immediately "Login incorrect" (without getting a chance of entering the password at all).
F.A.Q.
------
### How to generate an Universally Unique IDentifier (UUID)?
A 16bytes generic UUID (4bytes-2bytes-2bytes-2bytes-6bytes):

`xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx`

#### uuidgen
/usr/bin/uuidgen is available on Mac OS X.
__Example:__


`# uuidgen`
`C30B3EB3-DAEB-487B-A5B7-B1A023A85593`
#### openssl && xdd
Entropy is provided by OpenSSL engine.
xdd is used in order to get a plain hexdump.

__Example:__


`GENERATED_UUID``="`openssl rand 4 | xxd -p`-`openssl rand 2 |`
`xxd -p`-`openssl rand 2 | xxd -p`-`openssl rand 2 |`
`xxd -p`-`openssl rand 6 |`
`xxd -p`"`
`
`
`echo $GENERATED_UUID`
`f2bfd9bc-5c06-a572-5bc9-a1be9e081fd8`
#### by hand
Remember to only use base 16 (hexadecimal) values (0..9 and A..F).

__Example:__


1ee7c0de-feed-dead-beef-c0ffeeeeeeee

#### root UUID
As said above, the root UUID is fixed to `FFFFEEEE-DDDD-CCCC-BBBB-AAAA00000000.`
You shoudn't use another UUID for root account though (not yet tested) it could work.

### How to create or modify any user?
There are several ways to create or modify user, including these ones:
-   Use *dscl* (if available && no licence conflict) by hands, assuming you know how to use it and what you're doing.
-   Use *pd_adduser* script, a front-end of dscl, inspired by the original useradd script from OpenDarwin.
-   Use *pd_inject* script, a similar front-end from PureDarwin which uses *openssl* as backend tool instead of *dscl*.
### How to add an user to admin group?
In /var/db/dslocal/nodes/Default/groups/admin.plist, create a new string corresponding to the new preferential user like:
 `<key>users</key>`
 `<array>`
 `<string>root</string>`
 <span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<user>&lt;/string&gt;</span></span>
 `</array>`
### How to disable a specified user?
Add DisabledUser inside 

### How to delete a specified user?
(please add text)

<span style="font-family:courier new,monospace"><span style="font-size:small">rm /var/db/dslocal/Default/nodes/users/<user>.plist
rm /var/db/shadow/hash/<uuid></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">rm /var/db/shadow/hash/<uuid>.state</span></span>
<span style="font-family:courier new;font-size:12px">rm -rf /Users/<user></span>

Also don't forget to remove <user> from /var/db/dslocal/nodes/Default/groups/admin.plist group (if found inside).
### About /etc/authorization {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
We can see in /Developer/Examples/Security/README:
`[...] Note: The preferred way to modify the /etc/authorization file is to use`
`the Authorization APIs in <Security/AuthorizationDB.h>. This is always`
`how it should be done in shipping products, as there may have been other`
`modifications to the /etc/authorization file. A code snippet to do this
`
`is:`
`
`
`#include <CoreFoundation/CoreFoundation.h>`
`#include <Security/AuthorizationDB.h>`
`[...]
`
`    if (status) exit(1);`
`}`

