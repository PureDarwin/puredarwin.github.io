Netatalk
========

<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/netatalk.png)](netatalk/netatalk.png%3Fattredirects=0)
Mac OS X comes with a Apple File Protocol (AFP) server which is closed source and unavailable for PureDarwin. Hence, if you would like to use PureDarwin as a file, print and time server for Macintosh computers, you need to use netatalk, a third-party, open source implementation of the AppleTalk suite of protocols. It allows PureDarwin to act as an AFP server and can act as a Time Machine server similar to Apple's Time Capsule. This page describes how to install and configure netatalk on PureDarwin.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Installing netatalk on PureDarwin](netatalk.html#TOC-Installing-netatalk-on-PureDarwin)
2.  [**2** Configuring netatalk](netatalk.html#TOC-Configuring-netatalk)
3.  [**3** Announcing to Bonjour (mDNSResponder)](netatalk.html#TOC-Announcing-to-Bonjour-mDNSResponder-)

Installing netatalk on PureDarwin
---------------------------------
netatalk can be installed from MacPorts. Execute the following command to start it, and to cause it to launch at startup:

```sudo launchctl load -w /Library/LaunchDaemons/org.macports.netatalk.plist```

This, among other things, launches ```/opt/local/sbin/afpd```, which is netatalk's AFP server.
From this moment on, you should be able to connect to your server from any mac using afp://servername or afp://0.0.0.0 (using your server's IP adress). 
Configuring netatalk
--------------------
After installation, you will be unable to log in. Instead, you will get a message that the username/password is wrong, and /opt/local/var/log/netatalk.log shows 

<span style="font-size:small">[uams_dhx_pam.c:497]: I:UAMSDaemon: uams_dhx_pam.c :PAM: PAM_Error: Authentication failure</span>

This can be fixed by creating the file <span style="font-size:small">/etc/pam.d/netatalk</span> with the following content:

<span style="font-size:small">auth       required       pam_nologin.so</span>
<span style="font-size:small">auth       sufficient     pam_securityserver.so</span>
<span style="font-size:small">auth       sufficient     pam_unix.so</span>
<span style="font-size:small">auth       required       pam_deny.so</span>
<span style="font-size:small">account    required       pam_permit.so</span>
<span style="font-size:small">password   required       pam_deny.so</span>
<span style="font-size:small">session    required       pam_uwtmp.so</span>


Now you should be able to log in using your username and password, and should be able to access your files. See MacPorts [#23313](https://trac.macports.org/ticket/23313)

By default, every user can access his home directory. Note however that every user can mark other areas he has (read) access to as shared, including the entire hard disk. All he has to do is create a file <span style="font-size:small">.AppleVolumes</span> in his home directory with the following content:

<span style="font-size:small"># Export the entire hard disk</span>
<span style="font-size:small">/</span><span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">"/"</span>

Is it possible to disallow users from this?
Announcing to Bonjour (mDNSResponder)
-------------------------------------
This section is about announcing the server on the local network, so that it shows up in the Finder:

[![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/Bildschirmfoto%202010-01-17%20um%2002.58.49.png)](netatalk/Bildschirmfoto%202010-01-17%20um%2002.58.49.png%3Fattredirects=0)

[](netatalk/Bildschirmfoto%202010-01-17%20um%2002.58.49.png%3Fattredirects=0)On the Mac, the AppleFileServer is launched and announced on the local network via [Bonjour](bonjour.html) using the following LaunchDaemons plist file. We would like to do the same with netatalk, but we are running into problems...


<span style="font-size:small">&lt;!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd"&gt;</span>
<span style="font-size:small">&lt;plist version="1.0"&gt;</span>
<span style="font-size:small">&lt;dict&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;key&gt;Disabled&lt;/key&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;true/&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;key&gt;EnableTransactions&lt;/key&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;true/&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;key&gt;GroupName&lt;/key&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;string&gt;wheel&lt;/string&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;key&gt;Label&lt;/key&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;string&gt;com.apple.AppleFileServer&lt;/string&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;key&gt;MachServices&lt;/key&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;dict&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;key&gt;com.apple.AppleFileServer&lt;/key&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;dict&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;key&gt;HideUntilCheckIn&lt;/key&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;true/&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;/dict&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;/dict&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;key&gt;ProgramArguments&lt;/key&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;array&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;string&gt;/usr/sbin/AppleFileServer&lt;/string&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;/array&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;key&gt;Sockets&lt;/key&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;dict&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;key&gt;Listener&lt;/key&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;dict&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;key&gt;Bonjour&lt;/key&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;true/&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;key&gt;SockServiceName&lt;/key&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;string&gt;afpovertcp&lt;/string&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;/dict&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> **** </span></span><span style="font-size:small">**&lt;/dict&gt;**</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;key&gt;WaitForDebugger&lt;/key&gt;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">&lt;false/&gt;</span>
<span style="font-size:small">&lt;/dict&gt;</span>
<span style="font-size:small">&lt;/plist&gt;</span>

This tells launchd to announce the AFP server on the local network with Bonjour and launch the AFP server whenever the "afpovertcp" port is accessed. The file ```/etc/services``` contains the definition that this equals port 548. 

If we copy the bold part from above into the netatalk LaunchDaemon plist, then netatalk gets announced on the local network as a server (i.e., it shows up automatically on the left-hand side in Finder), but we get
```E:AFPDaemon: main: dsi_init: Address already in use```
in the syslog and cannot connect to the server because afpd can't start.

Please let us know what to do. <span style="color:rgb(0,0,0)">See MacPorts [#23315](https://trac.macports.org/ticket/23315). According to the maintainer, this has been discussed upstream. As of January 2010, there is a proposal for a possible solution, which might be included in some future Netatalk release.</span>

As a workaround, you can edit ```/opt/local/etc/netatalk/initscript``` so that it starts and stops dns-sd. While this is not elegant, it does work at least. Insert the three bold lines into ```/opt/local/etc/netatalk/initscript```:


```"$PREFIX/sbin/afpd" $AFPD_UAMLIST -g $AFPD_GUEST -c $AFPD_MAX_CLIENTS```

```**dns-sd -R . _afpovertcp._tcp . 548 &**```

```printf " Done.n"```

```    kill $CNID_PID```

```**DNS_SD_PID=`ps aux | grep -v awk | awk '/^root.*afpovertcp/ {print $2}'**```

```**    kill DNS_SD_PID**```

```fi```

Reload with:
```sudo launchctl unload -w /Library/LaunchDaemons/org.macports.netatalk.plist```
```sudo launchctl load -w /Library/LaunchDaemons/org.macports.netatalk.plist```

Now you should see your PureDarwin server in the Finder of the Macs in your local network and should be able to connect and log in using the server username and password.

