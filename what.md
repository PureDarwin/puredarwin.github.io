what
====
`what' is a tool showing what versions of object modules were used to construct a file.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Using `what'](what.html#TOC-Using-what-)
2.  [**2** Ressource](what.html#TOC-Ressource)

Using `what'
-------------
As example:


<span style="font-family:courier new,monospace"><span style="font-size:small">what /usr/lib/libSystem.B.dylib</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libSystem.B.dylib</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> Libsyscall-1228.5.18~1 05/23/08 00:34:41 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> Libc-498.1.1~5 04/15/08 22:44:26 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> Libsystem-111.1.1~2 07/10/08 18:12:54 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">PROGRAM:commonCrypto  PROJECT:CommonCrypto-32207</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> libdyld-96.2~143 05/23/08 00:33:39 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> Libinfo-278.0.3~2 04/07/08 12:29:06 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> libdns_sd mDNSResponder-171.4 (Apr 20 2008 11:16:45)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> Libm-292.4 Mar 11 2008 23:06:24</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">LIBRARY:libmacho  PROJECT:cctools_ofiles-667.3~138  DEVELOPER:root  BUILT:Mon Apr  7 16:19:07 PDT 2008</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> Libnotify-35~3 09/23/07 14:39:00 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> Libunc-21~150 09/23/07 14:39:04 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> launchd_libs-258.12~1 04/03/08 17:35:26 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> copyfile-42~24 03/04/08 21:17:45 PST</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> Seatbelt_libs-107.1~456 05/23/08 00:33:32 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> quarantine-22~35 09/23/07 14:38:59 PDT</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> removefile-11~1 12/12/07 13:59:48 PST</span></span></span>

Ressource
---------
<span style="font-family:courier new,monospace"><span style="font-size:small">man what</span></span>
