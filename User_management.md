User management
===============
This page is about user management in Darwin. It is a work in progress.
Because user management has changed since Darwin 8 via Darwin 9 to Darwin10, this does not fully apply for versions prior to 9 and greater than 9.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:444px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Status](users.1.html#TOC-Status)
2.  [**2** Open Directory](users.1.html#TOC-Open-Directory)
3.  [**3** Directory Services](users.1.html#TOC-Directory-Services)
    1.  [**3.1** /var/db/dslocal/](users.1.html#TOC-var-db-dslocal-)
        1.  [**3.1.1** /var/db/dslocal/nodes/Default/users/](users.1.html#TOC-var-db-dslocal-nodes-Default-users-)
        2.  [**3.1.2** /var/db/dslocal/nodes/Default/group/](users.1.html#TOC-var-db-dslocal-nodes-Default-group-)
        3.  [**3.1.3** /var/db/shadow/hash/](users.1.html#TOC-var-db-shadow-hash-)
    2.  [**3.2** Command line tool: dscl](users.1.html#TOC-Command-line-tool:-dscl)
    3.  [**3.3** passwd tool](users.1.html#TOC-passwd-tool)
4.  [**4** PAM](users.1.html#TOC-PAM)
5.  [**5** F.A.Q.](users.1.html#TOC-F.A.Q.)
    1.  [**5.1** How to generate an Universally Unique IDentifier (UUID)?](users.1.html#TOC-How-to-generate-an-Universally-Unique-IDentifier-UUID-)
        1.  [**5.1.1** uuidgen](users.1.html#TOC-uuidgen)
        2.  [**5.1.2** openssl && xdd](users.1.html#TOC-openssl-xdd)
        3.  [**5.1.3** by hand](users.1.html#TOC-by-hand)
        4.  [**5.1.4** root UUID](users.1.html#TOC-root-UUID)
    2.  [**5.2** How to create or modify any user?](users.1.html#TOC-How-to-create-or-modify-any-user-)
    3.  [**5.3** How to add an user to admin group?](users.1.html#TOC-How-to-add-an-user-to-admin-group-)
    4.  [**5.4** How to disable a specified user?](users.1.html#TOC-How-to-disable-a-specified-user-)
    5.  [**5.5** How to delete a specified user?](users.1.html#TOC-How-to-delete-a-specified-user-)
    6.  [**5.6** About /etc/authorization](users.1.html#TOC-About-etc-authorization)

<span style="font-size:18px"><span style="font-size:22px">Status</span></span>
------------------------------------------------------------------------------
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="font-family:Arial;font-size:13px"><span style="font-weight:bold">Problem: </span>User cannot log in. After running login, `securityd' crashes (segmentation fault). This means tracing the system calls through <span style="font-style:italic">pam_securityserver</span> and into <span style="font-style:italic">OpenDirectory.framework</span> to see what call causes the crash. But do you want to know the <span style="font-style:italic">really</span> annoying bit? Sometimes it will work. Including always when it's being monitored by `gdb'. And even when it crashes it seems to get to different places each time. Oh, why, Apple? Why?</span></span></span></span>

<span style="font-weight:bold">Nasty nasty fix:</span> `securityd' seems to work reliably if you force it to stick to a single thread (by adding <span style="font-size:small">-</span><span style="font-family:courier new,monospace"><span style="font-size:small">t 1</span></span> to its .plist). Which is bound to cause us more problems in the future. The most problematic point is the frequency of deadlock (significant impact) with this workaround.

[![](../_/rsrc/1237640633039/users/users/login%20with%20security%20running%20in%20single%20thread.png)](users/login%20with%20security%20running%20in%20single%20thread.png%3Fattredirects=0)


<span style="font-weight:bold">Less nasty nasty fix:</span> `securityd' seems also to work reliably with 10 threads. Add <span style="font-family:courier new,monospace"><span style="font-size:small">-t 10</span></span> to its .plist, that will also decrease the chance to hit a deadlock.


<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="font-family:Arial;font-size:13px"><span style="font-weight:bold">Not quite so old problem: </span>Examining the output of a version of <span style="font-style:italic">libpam</span> built with full debugging, it would seem that authentication succeeds (the user name is verified against the given password), but session creation fails. (This can be confirmed by running </span><span style="font-size:13px">login -f<span style="font-family:arial,sans-serif">, which, since in PureDarwinXmas you are by default root, tells login that the user does not need to be authenticated.)</span></span><span style="font-family:Arial;font-size:13px"> Occasionally the following message is displayed:</span></span></span></span>

<span><span style="font-family:courier new,monospace"><span style="font-size:small">PAM Error (line 396): Cannot make/remove an entry for the specified session</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:arial,sans-serif">
</span>
Examining the config file /etc/pam.d/login, it would appear that the modules <span style="font-family:courier new,monospace"><span style="font-size:small">pam_launchd</span></span><span style="font-family:arial,sans-serif"> and </span><span style="font-family:courier new,monospace"><span style="font-size:small">pam_uwtmp</span></span><span style="font-family:arial,sans-serif"> are responsible for creating sessions. Further, it seems from debug output that the problem lies within </span><span style="font-family:courier new,monospace">pam_launchd</span><span style="font-family:arial,sans-serif">.</span>

Thanks to Apple's Damie<span style="font-family:arial,sans-serif">n </span><span style="border-collapse:separate;font-size:12px"><span style="font-family:arial,sans-serif">Sorresso on the launchd-dev mailing list for providing the answer to this. login needs a new security session created for it before it can set it up for the new user. This is what sshd does for in-coming users, and what loginwindow.app does for GUI users under OS X. For the moment, a small PAM module (pam_sessioncreate, available on the [Downloads](../downloads.html) page) can be added to /usr/lib/pam/ and to /etc/pam.d/login just above pam_launchd ("session required pam_sessioncreate.so") to create the necessary session. The file should now include:</span></span>
<span style="border-collapse:separate;font-size:12px">
</span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">[...]</span></span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">password</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">    required</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">    pam_deny.so</span></span></span></span><span style="border-collapse:separate"><span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">session</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">    </span></span><span style="font-family:courier new,monospace"><span style="font-size:small"> required</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">    pam_sessioncreate.so</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">   <span style="font-family:arial,sans-serif"> &lt;- (new line inserted here)</span></span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">session</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">    </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> required</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">    pam_launchd.so</span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">[...]</span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">
</span></span></span></span>
<span style="border-collapse:separate;font-size:12px">
</span>
<span style="border-collapse:separate;font-size:12px">And then...</span>
<span style="border-collapse:separate;font-size:12px">
</span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">Welcome to PureDarwin!</span></span></span><span style="border-collapse:separate"><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span></span>
<span style="font-family:courier new">
</span>

[![](../_/rsrc/1237640751991/users/users/login%20via%20ssh.png)](users/login%20via%20ssh.png%3Fattredirects=0)


<span style="font-size:12px"><span style="font-family:arial,sans-serif;font-weight:bold">Old problem:</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">PureDarwin login[23]: PAM unable to _pam_dlopen(/usr/lib/pam/pam_</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">securityserver.so)</span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">PureDarwin login[23]: PAM adding faulty module: /usr/lib/pam/pam_</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">securityserver.so</span></span></span>
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
<span style="font-size:small">Jul 22 23:31:07 PureDarwin com.apple.SecurityServer[18]: Entering service</span>
<span style="font-size:small">Jul 22 23:31:17 PureDarwin com.apple.SecurityServer[18]: getpwnam() failed for user toor, creating invalid credential</span>
<span style="font-size:small">Jul 22 23:31:17 PureDarwin com.apple.SecurityServer[18]: getpwnam() failed for user toor, creating invalid credential</span>
<span style="font-size:small">Jul 22 23:31:17 PureDarwin com.apple.SecurityServer[18]: Failed to authorize right system.login.tty by client /usr/bin/login for authorization created by /usr/bin/login.</span>

In the contrary, still no problem with the one from 9G55
<span style="font-size:small">Jul 22 23:33:58 PureDarwin com.apple.SecurityServer[18]: Entering service</span>
<span style="font-size:small">Jul 22 23:34:03 PureDarwin com.apple.SecurityServer[18]: checkpw() succeeded, creating credential for user toor</span>
<span style="font-size:small">Jul 22 23:34:03 PureDarwin com.apple.SecurityServer[18]: checkpw() succeeded, creating shared credential for user toor</span>
<span style="font-size:small">Jul 22 23:34:03 PureDarwin com.apple.SecurityServer[18]: Succeeded authorizing right system.login.tty by client /usr/bin/login for authorization created by /usr/bin/login.</span>

Some dependencies also differ between the both binaries (/usr/local/DirectoryService).

<span style="font-size:small">/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.17.0)</span>
<span style="font-size:small">/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.18.0)</span>
<span style="font-size:small">/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 677.22.0)</span>
<span style="font-size:small">/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 677.24.0)</span>

<span style="font-size:small">/System/Library/Frameworks/Security.framework/Versions/A/Security (compatibility version 1.0.0, current version 34102.0.0)</span>
<span style="font-size:small">/System/Library/Frameworks/Security.framework/Versions/A/Security (compatibility version 1.0.0, current version 36371.0.0)</span>

<span style="font-size:small">/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.3)</span>
<span style="font-size:small">/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.4)</span>

Need investigations.
### /var/db/dslocal/
This is the location where Directory Service stores information about users and permissions for a local machine (DirectoryService can be used over the network, too).
#### /var/db/dslocal/nodes/Default/users/
This directory contains many plist files.
The filename is related to the respective existing user.

The content of a (minimal?) generic <span style="font-style:italic">/var/db/dslocal/nodes/Default/&lt;user&gt;.plist</span> (shadowed hash enabled) looks like:


<span style="font-family:courier new,monospace"><span style="font-size:small">&lt;?xml version="1.0" encoding="UTF-8"?&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">&lt;!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd"&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">&lt;plist version="1.0"&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">&lt;dict&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;authentication_authority&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;;ShadowHash;&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;generateduid&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<span style="color:rgb(255,0,0)">&lt;uuid&gt;</span>&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;gid&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<span style="color:rgb(255,0,0)">&lt;gid&gt;</span>&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;home&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;/Users/<span style="color:rgb(255,0,0)">&lt;user&gt;</span>&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;name&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<span style="color:rgb(255,0,0)">&lt;user&gt;</span>&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;passwd&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;********&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;realname&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<span style="color:rgb(255,0,0)">&lt;realname&gt;</span>&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;shell&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<span style="color:rgb(255,0,0)">&lt;shell&gt;</span>&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;uid&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<span style="color:rgb(255,0,0)">&lt;uid&gt;</span>&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/dict&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/plist&gt;</span></span>

This authentication authority attribute line<span style="white-space:pre"> </span><span style="font-family:courier new"><span style="font-size:12px">&lt;string&gt;;ShadowHash;&lt;/string&gt; </span><span style="font-family:Arial">tells the password is shadowed. It is also possible but stupid to use plain text password.</span></span>

A generic authentication authority attribute (semicolon-delimited) looks like:


<span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<span style="color:rgb(255,0,0)">&lt;version (rarely used)&gt;</span>;<span style="color:rgb(255,0,0)">&lt;authority tag (auth type)&gt;</span>;<span style="color:rgb(255,0,0)">&lt;authority data (depends on auth type, may be empty)&gt;</span>&lt;/string&gt;</span></span>


<span style="font-family:courier new"><span style="font-family:Arial">In fact, Open Directory supports many types of authentication:</span></span>
-   <span style="font-family:courier new;font-size:12px">&lt;string&gt;;Basic;&lt;/string&gt; </span>Basic (supports Crypt password)
-   <span style="font-family:courier new;font-size:12px"><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;;</span></span><span style="border-collapse:separate;font-family:monaco;font-size:11px;white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small">ApplePasswordServer</span></span><span style="border-collapse:collapse;font-family:Arial;font-size:13px;white-space:normal"><span style="font-family:courier new,monospace"><span style="font-size:small">;0x3d...&lt;/string&gt; Apple Password Server (SASL)</span></span></span></span></span>
-   <span style="font-family:courier new;font-size:12px"><span style="border-collapse:separate;font-family:monaco;font-size:11px;white-space:pre"><span style="border-collapse:collapse;white-space:normal"><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;;ShadowHash;HASHLIST:&lt;SALTED-SHA-1,SMB-NT,SMB-LAN-MANAGER,CRAM-MD5,RECOVERABLE,SECURE&gt;&lt;/string&gt; </span></span></span><span style="border-collapse:collapse;font-family:Arial;font-size:13px;white-space:normal">Shadow hash (salted SHA-1)</span></span></span>
-   <span style="font-family:courier new;font-size:12px">&lt;string&gt;;LocalWindowsHash;&lt;/string&gt; </span>Local Windows (NTLM)
-   <span style="font-family:courier new;font-size:12px">&lt;string&gt;;LocalCachedUser;/LDAPv3/foobar.domain:<span style="color:rgb(255,0,0)">&lt;user&gt;</span>:<span style="color:rgb(255,0,0)">&lt;uuid&gt;</span>&lt;/string&gt; </span>Local Cached User (LDAP)
-   <span style="font-family:courier new;font-size:12px">&lt;string&gt;;Kerberosv5;; Kerberosv5 ;0x3f...&lt;/string&gt; </span>Kerberos v5
-   <span style="font-family:courier new;font-size:12px">&lt;string&gt;;DisabledUser;;ShadowHash;&lt;/string&gt; </span>Disabled (prevents any authentication, account is disabled)
Also, Inside <span style="font-family:courier new;font-size:12px">authentication_authority <span style="font-family:Arial;font-size:13px">array we could have optionally a string dedicated to kerberos, per example: </span></span>


<span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;;Kerberosv5;;</span></span><span style="color:rgb(255,0,0)"><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;user&gt;</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">@LKDC:SHA1.</span></span><span style="color:rgb(255,0,0)"><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;hexadecimal string&gt;</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">;LKDC:SHA1.</span></span><span style="color:rgb(255,0,0)"><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;hexadecimal string<span style="color:rgb(0,0,0);font-family:Arial;font-size:13px"><span style="font-family:courier new"><span style="font-size:12px">&gt;</span></span><span style="font-family:courier new"><span style="font-size:12px">;&lt;/string&gt;</span></span></span></span></span></span>


Notice the &lt;user&gt; is associated to an Universally Unique IDentifier (UUID) <span style="color:rgb(255,0,0);font-family:courier new;font-size:12px">&lt;uuid&gt;<span style="color:rgb(0,0,0);font-family:Arial;font-size:13px">, a 16-byte hexadecimal string, unique over both space and time, except for root account.</span></span>
According to `<span style="font-style:italic">man uuidgen</span>`:


<span style="font-family:courier new,monospace"><span style="font-size:small">     The UUID is printed to standard output as a hyphen-punctuated ASCII</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">     string of the form: EEF45689-BBE5-4FB6-9E80-41B78F6578E2 (in printf(3)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">     format "%08X-%04X-%04X-%04X-%012X") [...]</span></span>

Finally, this directory seems like the deprecated /etc/passwd file (Note that /etc/passwd is still used in single user mode), where xml plist files (newschool side) are lines (oldschool side).
In the same manner (oldschool, newschool, you should have better stay at school ;)), the shadowed passwords are not stored in /etc/shadow by lines, but by files in /var/db/shadow/hash/ directory.

For your information, root account UUID is fixed to <span style="font-family:courier new,monospace"><span style="font-size:small">FFFFEEEE-DDDD-CCCC-BBBB-AAAA00000000</span></span>. Not sure it can and/or should be changed.
#### /var/db/dslocal/nodes/Default/group/
This directory contains many plist files related to available and private groups.
The filename is related to the respective group name.

(please add text)
#### /var/db/shadow/hash/
This directory is populated with two kinds of file.
-   An optional <span style="font-style:italic">/var/db/shadown/hash/<span style="color:rgb(255,0,0)">&lt;uuid&gt;</span>.state<span style="font-style:normal">, a binary plist which can be converted with </span>plutil<span style="font-style:normal"> (is it available for Darwin ??).
    This file is created when it doesn't exist and while corresponding user logs in.
    See inside:</span></span>
> > <span style="font-family:courier new;font-size:12px">&lt;?xml version="1.0" encoding="UTF-8"?&gt;</span>
> > <span style="font-family:courier new;font-size:12px">&lt;!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd"&gt;</span>
> > <span style="font-family:courier new;font-size:12px">&lt;plist version="1.0"&gt;</span>
> > <span style="font-family:courier new;font-size:12px">&lt;dict&gt;</span>
> > <span style="white-space:pre"><span style="font-family:courier new"><span style="font-size:12px"> </span></span></span><span style="font-family:courier new"><span style="font-size:12px">&lt;key&gt;CreationDate&lt;/key&gt;</span></span>
> > <span style="white-space:pre"><span style="font-family:courier new"><span style="font-size:12px"> </span></span></span><span style="font-family:courier new"><span style="font-size:12px">&lt;date&gt;<span style="color:rgb(255,0,0)">xxxx-xx-xxTxx:xx:xxZ</span>&lt;/date&gt;</span></span>
> > <span style="white-space:pre"><span style="font-family:courier new"><span style="font-size:12px"> </span></span></span><span style="font-family:courier new"><span style="font-size:12px">&lt;key&gt;FailedLoginCount&lt;/key&gt;</span></span>
> > <span style="white-space:pre"><span style="font-family:courier new"><span style="font-size:12px"> </span></span></span><span style="font-family:courier new"><span style="font-size:12px">&lt;integer&gt;<span style="color:rgb(255,0,0)">x</span>&lt;/integer&gt;</span></span>
> > <span style="white-space:pre"><span style="font-family:courier new"><span style="font-size:12px"> </span></span></span><span style="font-family:courier new"><span style="font-size:12px">&lt;key&gt;LastLoginDate&lt;/key&gt;</span></span>
> > <span style="white-space:pre"><span style="font-family:courier new"><span style="font-size:12px"> </span></span></span><span style="font-family:courier new"><span style="font-size:12px">&lt;date&gt;<span style="color:rgb(255,0,0)">xxxx-xx-xxTxx:xx:xxZ</span>&lt;/date&gt;</span></span>
> > <span style="white-space:pre"><span style="font-family:courier new"><span style="font-size:12px"> </span></span></span><span style="font-family:courier new"><span style="font-size:12px">&lt;key&gt;NewPasswordRequired&lt;/key&gt;</span></span>
> > <span style="white-space:pre"><span style="font-family:courier new"><span style="font-size:12px"> </span></span></span><span style="font-family:courier new"><span style="font-size:12px">&lt;integer&gt;<span style="color:rgb(255,0,0)">x</span>&lt;/integer&gt;</span></span>
> > <span style="font-family:courier new;font-size:12px">&lt;/dict&gt;</span>
> > <span style="font-family:courier new;font-size:12px">&lt;/plist&gt;</span>
-   A shadow file <span style="font-style:italic">/var/db/shadown/hash/<span style="color:rgb(255,0,0)">&lt;uuid&gt;</span></span>, named according to the corresponding UUID found in <span style="font-style:italic">/var/db/dslocal/Default/nodes/users/<span style="color:rgb(255,0,0)">&lt;user&gt;</span>.plist</span>.
    One line of 620 bytes with around 96% of 0...
> <span style="font-family:courier new;font-size:12px"><span style="color:rgb(255,153,0)">00000000000000000000000000000000000000000000000000000000000000</span><span style="color:rgb(255,153,0)">00</span><span style="color:rgb(0,0,255)">0000000000000000000000000000000000000
> 000</span><span style="color:rgb(106,168,79)">0000000000000000000000000000000000000000000000000000000000000000</span><span style="color:rgb(255,0,0)">&lt;salt:4bytes&gt;&lt;sha1:20bytes&gt;</span>0000000
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
> The <span style="color:rgb(255,153,0)">orange</span> part corresponds to the LANMAN (NTLM) password (32 bytes).
> The <span style="color:rgb(0,0,255)">blue</span> part is reserved for "unsalted" SHA1 digest (20 bytes).
> The <span style="color:rgb(106,168,79)">green </span>part is for md5 hash, another power of 2 (32 bytes).
> The <span style="color:rgb(255,0,0);font-family:courier new;font-size:12px">&lt;salt:4bytes&gt;&lt;sha1:20bytes&gt;</span> (24 bytes) is composed of a salt and a corresponding hash generated from this salt and given password:
>
> -   The salt is easy to generate or can be choosen freely.
>     Remember to use uppercase letters (it seems lowercase are not expected leading to login fail).
> > <span style="font-family:courier new;font-size:12px"># openssl rand 4 | xxd -p | tr ' a-z' ' A-Z'</span>
> > <span style="font-family:courier new;font-size:12px">1E677D44
> > </span>
> -   The SHA1 hash, based on digest with provided password can be generated via openssl.
>     Notice the salt must be passed as a binary data. Also do not forget to use uppercase letters.
> > <span style="font-family:courier new;font-size:12px"># HEX_SALT=`openssl rand 4 | xxd -p | tr ' a-z' ' A-Z'`</span>
> > <span style="font-family:courier new;font-size:12px"># BIN_SALT=`echo -n ${HEX_SALT} | xxd -r -p`</span>
> > <span style="font-family:courier new;font-size:12px"># SHA_HASH=`printf "%s%s" ${BIN_SALT} "<span style="color:rgb(255,0,0)">&lt;password&gt;</span>"} | openssl dgst -sha1 | tr ' a-z' ' A-Z'`
> > 
> > # echo ${HEX_SALT}${SHA_HASH}
> > 1E677D44EE801D51CE90C5E845E232809FDB22FFF600F409
> > </span>

Most of the following content (<span style="font-family:courier new;font-size:12px">000000000000o...<span style="font-family:Arial;font-size:13px">) doesn't seem to be used right now, perhaps reserved for future use.</span></span>

Notes: It seems random UUID is allowed.
### Command line tool: dscl
The <span style="font-style:italic">dscl</span> ** (Directory Service Command Line) tool is used in Darwin to manage users. <span style="font-style:italic">dscl</span> is part of the Darwin project DSTools. <span style="font-style:italic">dscl</span> is now (mostly) usable in a PureDarwin environment using the latest PureFoundation.root. (Not every option has been explored yet, so use may result in unpredictable results.)
### passwd tool
So classic.
Caution: If root account is disabled, using `<span style="font-style:italic">passwd root</span>` will enable it, leading to potential security flaw (see [Armoring PureDarwin](../curious/armoring-puredarwin.html) page).

PAM
---
PAM ("Pluggable Authentication Modules", contained in the projects <span style="font-style:italic">pam</span> and <span style="font-style:italic">pam_modules</span> is required for a working login. PAM is what verifies the username and password at login time. If both are mising, you get an error about libpam missing when you try to log in. If only pam_modules is missing, then you get a "Login:" prompt but no "Password:" prompt, instead you get immediately "Login incorrect" (without getting a chance of entering the password at all).
F.A.Q.
------
### How to generate an Universally Unique IDentifier (UUID)?
A 16bytes generic UUID (4bytes-2bytes-2bytes-2bytes-6bytes):

<span style="font-family:courier new,monospace"><span style="font-size:small">xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx</span></span>
<span></span>
#### uuidgen
/usr/bin/uuidgen is available on Mac OS X.
<span style="text-decoration:underline">Example:</span>


<span style="font-family:courier new,monospace"><span style="font-size:small"># uuidgen</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">C30B3EB3-DAEB-487B-A5B7-B1A023A85593</span></span>
#### openssl && xdd
Entropy is provided by OpenSSL engine.
xdd is used in order to get a plain hexdump.

<span style="text-decoration:underline">Example:</span>


<span style="font-family:courier new,monospace"><span style="font-size:small">GENERATED_UUID</span></span><span style="font-family:courier new,monospace"><span style="font-size:small">="`openssl rand 4 | xxd -p`-`openssl rand 2 |</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">xxd -p`-`openssl rand 2 | xxd -p`-`openssl rand 2 |</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">xxd -p`-`openssl rand 6 |</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">xxd -p`"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">echo $GENERATED_UUID</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">f2bfd9bc-5c06-a572-5bc9-a1be9e081fd8</span></span>
#### by hand
Remember to only use base 16 (hexadecimal) values (0..9 and A..F).

<span style="text-decoration:underline">Example:</span>


<span style="font-family:courier new"><span style="font-size:12px">1ee7c0de-feed-dead-beef-c0ffeeeeeeee
</span></span>
#### root UUID
As said above, the root UUID is fixed to <span style="font-family:courier new,monospace"><span style="font-size:small">FFFFEEEE-DDDD-CCCC-BBBB-AAAA00000000.</span></span>
You shoudn't use another UUID for root account though (not yet tested) it could work.

### How to create or modify any user?
There are several ways to create or modify user, including these ones:
-   Use *dscl* (if available && no licence conflict) by hands, assuming you know how to use it and what you're doing.
-   Use *pd_adduser* script, a front-end of dscl, inspired by the original useradd script from OpenDarwin.
-   Use *pd_inject* script, a similar front-end from PureDarwin which uses *openssl* as backend tool instead of *dscl*.
### How to add an user to admin group?
In /var/db/dslocal/nodes/Default/groups/admin.plist, create a new string corresponding to the new preferential user like:
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;key&gt;users&lt;/key&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;array&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;root&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;<span style="color:rgb(255,0,0)">&lt;user&gt;</span>&lt;/string&gt;</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">&lt;/array&gt;</span></span>
### How to disable a specified user?
Add <span style="font-family:courier new;font-size:12px">DisabledUser</span> inside <span style="font-family:courier new;font-size:12px">authentication_authority <span style="font-family:Arial;font-size:13px">array, like:</span></span>
<span style="font-family:courier new;font-size:12px"><span>    </span><span>    </span>&lt;string&gt;;<span style="color:rgb(255,0,0)">DisabledUser</span>;;ShadowHash;&lt;/string&gt; </span>
### How to delete a specified user?
(please add text)

<span style="font-family:courier new,monospace"><span style="font-size:small">rm /var/db/dslocal/Default/nodes/users/<span style="color:rgb(255,0,0)">&lt;user&gt;</span>.plist
rm /var/db/shadow/hash/<span style="color:rgb(255,0,0)">&lt;uuid&gt;</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">rm /var/db/shadow/hash/<span style="color:rgb(255,0,0)">&lt;uuid&gt;</span>.state</span></span>
<span style="font-family:courier new;font-size:12px">rm -rf /Users/<span style="color:rgb(255,0,0)">&lt;user&gt;</span></span>

Also don't forget to remove <span style="font-family:courier new;font-size:12px"><span style="color:rgb(255,0,0)">&lt;user&gt; </span></span>from /var/db/dslocal/nodes/Default/groups/admin.plist group (if found inside).
### About /etc/authorization {style="margin:10px 10px 10px 0px;color:rgb(0,0,0)"}
We can see in /Developer/Examples/Security/README:
<span style="font-family:courier new,monospace"><span style="font-size:small">[...] Note: The preferred way to modify the /etc/authorization file is to use</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">the Authorization APIs in &lt;Security/AuthorizationDB.h&gt;. This is always</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">how it should be done in shipping products, as there may have been other</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">modifications to the /etc/authorization file. A code snippet to do this
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">is:</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">#include &lt;CoreFoundation/CoreFoundation.h&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">#include &lt;Security/AuthorizationDB.h&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">[...]
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    if (status) exit(1);</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">}</span></span>

