top
===
This page is about the well-known UNIX tool 'top', which display and update sorted information about processes, but differs a little bit from the 'top' on other BSDs and/or GNU/Linux.

<span style="font-weight:bold">Problem:</span> logged as a user, `top' fails in "Bus error" as illustrated below:

[![](../_/rsrc/1238319956058/users/top/top%20fails%20as%20user.png)](top/top%20fails%20as%20user.png%3Fattredirects=0)

<span style="font-weight:bold">
Solution:</span> Unknown. Please contact us if you know a solution.

'otool' says:

<span style="font-family:courier new,monospace"><span style="font-size:small">/usr/bin/top:</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.13.0)</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit (compatibility version 1.0.0, current version 275.0.0)</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/lib/libpanel.5.4.dylib (compatibility version 5.4.0, current version 5.4.0)</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/lib/libncurses.5.4.dylib (compatibility version 5.4.0, current version 5.4.0)</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/lib/libutil.dylib (compatibility version 1.0.0, current version 1.0.0)</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)</span></span>


As root, there is no problem:

[![](../_/rsrc/1238319790319/users/top/top%20classic.png%3Fheight=335&width=420)](top/top%20classic.png%3Fattredirects=0)

