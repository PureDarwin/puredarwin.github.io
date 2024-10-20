NetBSD and the experimental Darwin binary compatibility
=======================================================

<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
![](/img/developers/universal-binaries/netbsd-compat-darwin/netbsd_logo.png)
This is a work in progress, attempting to run some mach-o binaries on NetBSD (macppc in this case).

Appeared as a significant [change](http://www.netbsd.org/changes/changes-3.0.html) in NetBSD 3.0.

Kernel stuff
------------
/netbsd
### Building the kernel with darwin support
Assuming you have set a default proper environment for compiling your kernel:
In the */usr/src/sys/arch/<your ARCH>/conf/<your CONFIG>*

At least, you have to enable these options:


`options ` `COMPAT_DARWIN` `# Darwin binary compatibility (experimental)`
`options ` `COMPAT_MACH` `# Mach compatibility, needed for COMPAT_DARWIN `
`options ` `EXEC_MACHO` `# Mach-O binary support, needed for COMPAT_MACH`

Optionnaly, uncomment the following:


`#options ` `DEBUG_DARWIN` `# COMPAT_DARWIN debugging`
`#options ` `DEBUG_MACH` `# COMPAT_MACH debugging`

After editing your configuration file, you can begin to build the kernel:



config <your CONFIG>
cd ../compile/<your CONFIG>
make depend
make
cp /netbsd /netbsd.old
cp netbsd /netbsd


Then reboot..




Assembler messages:
Error: bad expression
Error: syntax error; found `4' but expected `,'
Error: junk at end of line: `4,0'
Error: bad expression


### sysctl interface
By default:

`sysctl -a | grep darwin`
`emul.darwin.init.pid = 0`
`emul.darwin.ioframebuffer.unit = 0`
`emul.darwin.ioframebuffer.screen = 0`
`emul.darwin.iohidsystem.mux = 0`

In the source code of *darwin_sysctl.c*, we can read:

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
"*These libraries are part of the Darwin compatibility option for*

*NetBSD/powerpc and NetBSD/i386.*
*
*
*The kernel options `EXEC_MACHO', `COMPAT_MACH' and `COMPAT_DARWIN'*
*must be in your kernel config file for this to work.*" from /usr/pkgsrc/emulators/darwin_lib/DESCR


`cd /usr/pkgsrc/emulators/darwin_lib/`
`make install clean`

If the build fails, you will probably need to edit */usr/pkgsrc/emulators/darwin_lib/Makefile* and remove the problematic (XFree86) missing rpm in DISTFILES variable.
Attempt to run a mach-o binary
------------------------------
No *mach_init* is present by default, and *mach_init* has been dropped...

<span style="font-family:courier new,monospace"><span style="font-size:small">sysctl -w emul.darwin.init.pid=$$ && exec /emul/darwin/sbin/mach_init</span></span>

At the root of a mounted old darwin iso (ppc), populate the darwin userland shadow root:
 

`scp  -r bin sbin usr <NetBSD macppc host>:/emul/darwin`

`scp  -r System/Library <NetBSD macppc host>:/emul/darwin/System`

The process in `ps aux':


`USER PID %CPU %MEM VSZ   RSS TTY   STAT STARTED    TIME COMMAND`
`root 412  0.0  0.0   0     0 ttyE0 RW+        - 0:00.00 /emul/darwin/sbin/mach_init `

FAIL!


`cd /emul/darwin`
`./usr/bin/uname -a`

same state..


`root 421  0.0  0.0   0     0 ttyp0 RW+        - 0:00.00 ./usr/bin/uname -a `

FAIL!

At this time, 

__Note:__ It seems memory is not allocated, an the RW+ status seems curious.



**Please, let us know if you have a solution.**

Ressources
----------
<http://netbsd.gw.com/cgi-bin/man-cgi/man?compat_darwin+8+NetBSD-current> 
<http://www.netbsd.org/docs/compat.html#ports> 
<http://hcpnet.free.fr/applebsd.html> 

