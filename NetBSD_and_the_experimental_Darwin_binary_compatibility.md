NetBSD and the experimental Darwin binary compatibility
=======================================================

<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](../../_/rsrc/1227063742891/developers/universal-binaries/netbsd-compat-darwin/netbsd_logo.png%3Fheight=72&width=96)](netbsd-compat-darwin/netbsd_logo.png%3Fattredirects=0)
This is a work in progress, attempting to run some mach-o binaries on NetBSD (macppc in this case).
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Kernel stuff](netbsd-compat-darwin.html#TOC-Kernel-stuff)
    1.  [**1.1** Building the kernel with darwin support](netbsd-compat-darwin.html#TOC-Building-the-kernel-with-darwin-support)
    2.  [**1.2** sysctl interface](netbsd-compat-darwin.html#TOC-sysctl-interface)
2.  [**2** darwin_lib](netbsd-compat-darwin.html#TOC-darwin_lib)
3.  [**3** Attempt to run a mach-o binary](netbsd-compat-darwin.html#TOC-Attempt-to-run-a-mach-o-binary)
4.  [**4** Ressources](netbsd-compat-darwin.html#TOC-Ressources)


<span style="font-family:arial,sans-serif"><span style="font-size:small">Appeared as a significant [change](http://www.netbsd.org/changes/changes-3.0.html) in NetBSD 3.0 (</span></span><span style="border-collapse:separate;font-family:Tahoma;line-height:16px"><span style="font-family:arial,sans-serif"><span style="font-size:small">Support for MacOS X.3 binaries. </span></span>*<span style="font-family:arial,sans-serif"><span style="font-size:small">[manu 20040825]<span style="font-style:normal">).</span></span></span>*</span>
<span style="border-collapse:separate;line-height:16px">*<span style="font-style:normal"><span style="font-family:arial,sans-serif"><span style="font-size:small">"</span></span>[<span style="font-family:arial,sans-serif"><span style="font-size:small"><span style="font-style:italic">compat_darwin(8)</span></span></span>](http://netbsd.gw.com/cgi-bin/man-cgi?compat_darwin+8+NetBSD-3.0)<span style="font-family:arial,sans-serif"><span style="font-size:small"><span style="font-style:italic"> emulation now supports Mac OS X version 10.3 binarie</span>s" was [announced](http://www.netbsd.org/releases/formal-3/NetBSD-3.0.html).</span></span></span>*</span>
Kernel stuff
------------
/netbsd
### Building the kernel with darwin support
Assuming you have set a default proper environment for compiling your kernel:
In the <span style="font-style:italic">/usr/src/sys/arch/&lt;your ARCH&gt;/conf/&lt;your CONFIG&gt;</span>

At least, you have to enable these options:


<span style="font-family:courier new,monospace"><span style="font-size:small">options </span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">COMPAT_DARWIN</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"># Darwin binary compatibility (experimental)</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">options </span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">COMPAT_MACH</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"># Mach compatibility, needed for COMPAT_DARWIN </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">options </span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">EXEC_MACHO</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"># Mach-O binary support, needed for COMPAT_MACH</span></span>

Optionnaly, uncomment the following:


<span style="font-family:courier new,monospace"><span style="font-size:small">#options </span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">DEBUG_DARWIN</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"># COMPAT_DARWIN debugging</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">#options </span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">DEBUG_MACH</span></span><span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"># COMPAT_MACH debugging</span></span>

After editing your configuration file, you can begin to build the kernel:


<span style="border-collapse:separate"><span style="font-family:courier new,monospace"><span style="font-size:small">cd </span></span><span style="border-collapse:collapse"><span style="font-family:courier new,monospace"><span style="font-size:small">/usr/src/sys/arch/&lt;your ARCH&gt;/conf/</span></span></span></span>
<span style="border-collapse:separate"><span style="font-family:courier new"><span style="font-size:12px">config &lt;your CONFIG&gt;</span></span></span>
<span style="border-collapse:separate"><span style="font-family:courier new"><span style="font-size:12px">cd ../compile/&lt;your CONFIG&gt;</span></span></span>
<span style="border-collapse:separate"><span style="font-family:courier new"><span style="font-size:12px">make depend</span></span></span>
<span style="border-collapse:separate"><span style="font-family:courier new"><span style="font-size:12px">make</span></span></span>
<span style="border-collapse:separate"><span style="font-family:courier new"><span style="font-size:12px">cp /netbsd /netbsd.old</span></span></span>
<span style="border-collapse:separate"><span style="font-family:courier new"><span style="font-size:12px">cp netbsd /netbsd</span></span></span>
<span style="border-collapse:separate;font-family:courier new;font-size:12px">
</span>
<span style="border-collapse:separate;font-family:courier new;font-size:12px"><span style="font-family:Arial;font-size:13px">Then reboot..</span></span>
<span style="border-collapse:separate">
</span>

<span style="font-family:arial,sans-serif"><span style="font-size:small"><span style="font-weight:bold">Problem: </span>The build fails in </span></span><span style="border-collapse:separate"><span style="font-family:arial,sans-serif"><span style="font-size:small"><span style="font-style:italic">darwin_commpage_machdep.S</span> with this kind of errors:</span></span></span>
<span style="border-collapse:separate;font-family:courier new;font-size:12px">Assembler messages:</span>
<span style="border-collapse:separate"><span style="font-family:courier new,monospace"><span style="font-size:small">Error: bad expression
Error: syntax error; found `4' but expected `,'
Error: junk at end of line: `4,0'
Error: bad expression
</span></span></span>
<span style="border-collapse:separate"><span style="font-weight:bold">Solution: <span style="font-weight:normal">You need to remove all "%" character before each asm register names (e.g.; %r4 should become r4) in the problematic file, then redo all the necessary steps from the beginning to build the kernel</span></span></span>
### sysctl interface
<span style="border-collapse:separate">By default:</span>
<span style="border-collapse:separate"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">sysctl -a | grep darwin</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">emul.darwin.init.pid = 0</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">emul.darwin.ioframebuffer.unit = 0</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">emul.darwin.ioframebuffer.screen = 0</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">emul.darwin.iohidsystem.mux = 0</span></span>

In the source code of <span style="font-style:italic">darwin_sysctl.c</span>, we can read:
<span style="font-family:Times;font-size:16px"></span>
    /*
     * On Darwin, mach_init is the system bootstrap process. It is responsible
     * for forking the traditional UNIX init(8) and it does the Mach port naming
     * service. We need mach_init for the naming service, but unfortunately, it
     * will only act as such if its PID is 1. We use a sysctl
     * (emul.darwin.init.pid) to fool a given process into thinking its PID is 1.
     * That way we can run mach_init when we want to.
     * Typical use:
     * sysctl -w emul.darwin.init.pid=$$; exec /emul/darwin/sbin/mach_init
     *
     * The same problem exists after mach_init has forked init: the fork libc stub
     * really insist on the child to have PID 2 (if PID is not 2, then the stub
     * will issue bootstrap calls to an already running mach_init, which fails,
     * of course).
     */
darwin_lib
-----------
"<span style="font-style:italic">These libraries are part of the Darwin compatibility option for</span>

<span style="font-style:italic">NetBSD/powerpc and NetBSD/i386.</span>
<span style="font-style:italic">
</span>
<span style="font-style:italic">The kernel options `EXEC_MACHO', `COMPAT_MACH' and `COMPAT_DARWIN'</span>
<span style="font-style:italic">must be in your kernel config file for this to work.</span>" <span style="font-size:x-small">from /usr/pkgsrc/emulators/darwin_lib/DESCR</span>


<span style="font-family:courier new,monospace"><span style="font-size:small">cd /usr/pkgsrc/emulators/darwin_lib/</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">make install clean</span></span>

If the build fails, you will probably need to edit <span style="font-style:italic">/usr/pkgsrc/emulators/darwin_lib/Makefile</span> and remove the problematic (XFree86) missing rpm in DISTFILES variable.
Attempt to run a mach-o binary
------------------------------
No <span style="font-style:italic">mach_init</span> is present by default, and <span style="font-style:italic">mach_init</span> has been dropped...

<span style="font-family:courier new,monospace"><span style="font-size:small">sysctl -w emul.darwin.init.pid=$$ && exec /emul/darwin/sbin/mach_init</span></span>

At the root of a mounted old <span style="font-family:Lucida Grande;font-size:12px">darwin iso (ppc), populate the darwin userland shadow root:</span>
<span style="font-family:Lucida Grande;font-size:12px"> </span>

<span style="font-family:courier new,monospace"><span style="font-size:small">scp  -r bin sbin usr &lt;NetBSD macppc host&gt;:/emul/darwin</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">scp  -r System/Library &lt;NetBSD macppc host&gt;:/emul/darwin/System</span></span>

The process in `ps aux':


<span style="font-family:courier new,monospace"><span style="font-size:small">USER PID %CPU %MEM VSZ   RSS TTY   STAT STARTED    TIME COMMAND</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">root 412  0.0  0.0   0     0 ttyE0 RW+        - 0:00.00 /emul/darwin/sbin/mach_init </span></span>

FAIL!


<span style="font-family:courier new,monospace"><span style="font-size:small">cd /emul/darwin</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">./usr/bin/uname -a</span></span>

same state..


<span style="font-family:courier new,monospace"><span style="font-size:small">root 421  0.0  0.0   0     0 ttyp0 RW+        - 0:00.00 ./usr/bin/uname -a </span></span>

FAIL!

At this time, <span style="font-family:Lucida Grande;font-size:12px">darwinppc-141, <span style="font-family:Arial;font-size:13px">OpenDarwin6.6.2, <span style="font-family:Lucida Grande;font-size:12px">darwin-701PPC and darwinx86-801 binaries has been tested without any success.</span></span></span>
<span style="font-family:Lucida Grande;font-size:12px"><span style="font-family:Arial;font-size:13px"></span></span>
<span style="text-decoration:underline">Note:</span> It seems memory is not allocated, an the RW+ status seems curious.

<span style="font-family:Lucida Grande;font-size:12px">
</span>
<span style="font-weight:bold"><span style="font-family:arial,sans-serif"><span style="font-size:small"><span style="color:rgb(255,0,0)">Please, let us know if you have a solution.</span></span></span></span>

Ressources
----------
<http://netbsd.gw.com/cgi-bin/man-cgi/man?compat_darwin+8+NetBSD-current> 
<http://www.netbsd.org/docs/compat.html#ports> 
<http://hcpnet.free.fr/applebsd.html> 

