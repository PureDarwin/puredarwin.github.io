DTrace
======

This page is about the DTrace facility in _"Darwin-land"_.

# Contents
1.  [**1** What is DTrace?](#whatisdtrace)
    1.  [**1.1** Pros](#pros)
    2.  [**1.2** Cons](#cons)
2.  [**2** Examples](#examples)
    1.  [**2.1** A real world example: show missing files](dtrace.html#TOC-A-real-world-example:-show-missing-files)
    2.  [**2.2** A _cliché_ example: "Hello world!"](dtrace.html#TOC-A-clich-example:-Hello-world-)
        1.  [**2.2.1** Inline](dtrace.html#TOC-Inline)
        2.  [**2.2.2** In a file](dtrace.html#TOC-In-a-file)
    3.  [**2.3** Detect new process (successfully started)](dtrace.html#TOC-Detect-new-process-successfully-started-)
    4.  [**2.4** Detect sigkill](dtrace.html#TOC-Detect-sigkill)
    5.  [**2.5** Detect promiscuous mode changes](dtrace.html#TOC-Detect-promiscuous-mode-changes)
    6.  [**2.6** Watch setuid/setgid calls](dtrace.html#TOC-Watch-setuid-setgid-calls)
    7.  [**2.7** Classic examples](dtrace.html#TOC-Classic-examples)
3.  [**3** D Programming language](dtrace.html#TOC-D-Programming-language)
    1.  [**3.1** A generic D script example](dtrace.html#TOC-A-generic-D-script-example)
    2.  [**3.2** Probes and providers](dtrace.html#TOC-Probes-and-providers)
        1.  [**3.2.1** Probe syntax](dtrace.html#TOC-Probe-syntax)
        2.  [**3.2.2** Listing probes](dtrace.html#TOC-Listing-probes)
        3.  [**3.2.3** Available providers](dtrace.html#TOC-Available-providers)
        4.  [**3.2.4** Default variables](dtrace.html#TOC-Default-variables)
        5.  [**3.2.5** Macro variables](dtrace.html#TOC-Macro-variables)
    3.  [**3.3** Predicate (optional)](dtrace.html#TOC-Predicate-optional-)
    4.  [**3.4** Action (optional)](dtrace.html#TOC-Action-optional-)
    5.  [**3.5** Kernel destructive actions](dtrace.html#TOC-Kernel-destructive-actions)
        1.  [**3.5.1** "-w" flag required for...](dtrace.html#TOC--w-flag-required-for...)
4.  [**4** References](dtrace.html#TOC-References)

What is DTrace?
-----------------
According to ```man dtrace```\:

    The dtrace command is a generic front-end to the DTrace facility. The 
    command  implements  a  simple  interface to invoke the D language com-
    piler, the ability to retrieve buffered trace data from the DTrace ker-
    nel  facility,  and  a set of basic routines to format and print traced
    data.

Simply, DTrace is:

-   a dynamic debugger and analysis tool (first appeared in Solaris 10 and OpenSolaris, then in Mac OS X 10.5)
-   a D programming language interpreter 
-   a monitoring tool (ie: Observing devices, such as disk or network activity) 
-   a profiling tool (performance analysis) 
-   a process, library, user function, (some) kernel function, the operating system (itself) inspector tool 
-   a bug finder
-   scalable 

DTrace may also be used as (or be a part of) 
-   a malware investigation tool 
-   a process deciphering tool 
-   a Troubleshooting software bugs 
-   a partial intrusion detection system 
-   an educative software (in order to explore, and understand how this operating system works)
<span style="text-decoration:underline">Notes:</span><span style="font-size:small"> Although PureDarwin is focused on i386, DTrace supports most of common architectures (</span><span style="font-family:courier new,monospace"><span style="font-size:small">-arch i386|x86_64|ppc|ppc64</span></span><span style="font-size:small">).</span>
In Mac OS X 10.5, Instruments.app found in developer tools is another front-end to the DTrace facility.
<span style="text-decoration:underline"><span style="font-size:small">Warning:</span></span><span style="font-size:small"> If the operating system becomes too busy or if you attempt to trace too many events (ie: all function entry related to the kernel), DTrace can drop events and even abort tracing and execution. Consequently, security auditing with DTrace is impacted and more,<span style="font-family:Helvetica"> system() action is not synchronous (so unreliable for security purpose).</span></span>

### Pros
-   <span style="font-size:13px">Every process, or specific processes, can be traced "simultaneously".</span>
-   <span style="font-size:13px">Output is fully flexible.</span>
-   <span style="font-size:13px">Nanosecond timestamp for function execution measurements.</span>
-   <span style="font-size:13px">Minimum performance impact when used smartly.</span>
-   <span style="font-size:13px">No need to restart anything in order to trace.</span>
-   <span style="font-size:13px">Relatively safe.</span>

### Cons

-   Partially supported (around 20K probes available instead of 60K) on Darwin (<span style="font-size:12px;font-family:Helvetica"><span style="font-family:courier new,monospace">dtrace -l | wc -l</span><span style="font-size:13px;font-family:Arial"> returns </span><span style="font-family:courier new,monospace">22466</span>).</span>
-   <span style="font-family:Helvetica">DTrace cannot fetch low levels hardware data.</span>
-   <span style="font-family:Helvetica">Performance impact when probe count goes under 36,000 probes (every kernel function entry/return) and 100,000 probes function in user-land.
    Consequently, not really suited for security auditing, because DTrace may drop events if the system is really busy or simply (but dramatically in this case) abort.</span>
-   <span style="font-family:Helvetica">Need to be run as root (not sure it should belong to "cons" part).</span>
<span style="font-size:small"></span>

Examples
--------

### A real world example: show missing files

<span style="font-size:13px">On Linux systems, "strace -eopen -f ... 2&gt;&1 | grep ENOENT" can be used to see which files a process tries to open. Using dtrace, the equivalent is:</span>
1.  Open two terminals
2.  In the first terminal, run:
    <span><span style="font-family:courier new,monospace"><span style="font-size:small">opensnoop -ex</span></span></span>
3.  <span style="font-family:Helvetica">In the second terminal, run the command that you want to inspect</span>
<span style="font-family:Helvetica">In the first terminal, you will see the files that are tried to be opened but fail to open (e.g., ENOENT).</span>

### A _cliché_ example: "Hello world!"
<span style="font-size:small"></span>

#### Inline
<span style="font-size:small"><span style="font-family:courier new,monospace">dtrace -n "BEGIN { trace("Hello World!"); exit(0);}"</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span><span style="color:rgb(68,68,68)">dtrace: description 'BEGIN ' matched 1 probe</span></span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span><span style="color:rgb(68,68,68)">CPU     ID                    FUNCTION:NAME</span></span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span><span style="color:rgb(68,68,68)">  0      1                           :BEGIN   Hello World!</span></span></span></span>
#### In a file
<span style="font-size:small">Edit and save Hello.d:</span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">BEGIN </span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">{ </span></span></span>
<span style="white-space:pre"><span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">trace("Hello World!"); </span></span></span>
<span style="white-space:pre"><span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">exit(0); </span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">}</span></span></span>
Then run the script:
<span style="font-family:courier new">dtrace -s Hello.d </span>
<span style="font-size:12px"> </span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span><span style="color:rgb(68,68,68)">dtrace: script 'Hello.d' matched 1 probe</span></span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span><span style="color:rgb(68,68,68)">CPU     ID                    FUNCTION:NAME</span></span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span><span style="color:rgb(68,68,68)">  0      1                           :BEGIN   Hello World!</span></span></span></span>
### Detect new process (successfully started)
<span style="font-family:courier new,monospace"> proc:::exec-success</span>
<span style="font-family:courier new,monospace"> {</span>
<span style="font-family:courier new,monospace"> printf("%s(pid=%d) started by uid - %dn",execname, pid, uid);</span>
<span style="font-family:courier new,monospace"> }</span>
<span style="font-size:small"></span>
### Detect sigkill
<span style="font-size:12px"></span>
<span style="font-family:courier new">proc:::signal-send</span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span>/args[2] == SIGKILL/</span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span>{</span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span>  printf("to %s",args[1]-&gt;pr_fname);</span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span>  printf(" at %d", timestamp);</span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span>  printf(" by (%d)", uid);</span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span>  printf(" from %sn", execname);</span></span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span>}</span></span></span>
### Detect promiscuous mode changes
<span style="font-family:courier new">fbt:mach_kernel:ifnet_set_promiscuous:*</span>
<span style="font-family:courier new,monospace"><span>{</span></span>
<span style="font-family:courier new,monospace"><span>   printf("%s", execname);
</span></span>
<span style="font-family:courier new,monospace"><span>}</span></span>
### Watch setuid/setgid calls
<span style="font-family:courier new,monospace"><span style="font-size:small">/* '*' == {entry|return} */</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">fbt:mach_kernel:setuid:*</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">{</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">   printf("%s", execname);</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">}</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">fbt:mach_kernel:setgid:*</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">{</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">   printf("%s", execname);</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">}</span></span>
### Classic examples
DTrace [one-liners](http://www.solarisinternals.com/wiki/index.php/DTrace_Topics_One_Liners)
The [DTraceToolkit](http://www.opensolaris.org/os/community/dtrace/dtracetoolkit) (~100 scripts)
D Programming language
----------------------
It seems to have been based on C language for some parts.
(please add text)
1.  <span style="font-size:small">D programs are compiled in user-land</span>
2.  <span style="font-size:small">And sent to the DTrace virtual machine in the kernel-land</span>
3.  <span style="font-size:small">Then run inside the kernel's address space (not in the DTrace process, nor in the target process)</span>
<span style="font-size:small">Most of the times, you will use <span style="font-family:courier new,monospace">copyin</span> or <span style="font-family:courier new,monospace">copyinstr</span> in order to copy data from user-land to kernel-land:
</span>
<span style="font-size:small">
</span>
<span style="font-size:small"><span style="font-family:courier new,monospace">     copyin()      Copies len bytes of data from the user-space address uaddr</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">                   to the kernel-space address kaddr.</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">
</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">     copyinstr()   Copies a NUL-terminated string, at most len bytes long,</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">                   from user-space address uaddr to kernel-space address</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">                   kaddr.  The number of bytes actually copied, including the</span></span>
<span style="font-size:small"><span style="font-family:courier new,monospace">                   terminating NUL, is returned in *done.</span></span>
### A generic D script example
`probe description /predicate/ {    action }`{style="font-family:courier new,monospace"}
<span style="font-size:12px"></span>
<span style="font-size:small"><span style="font-family:courier new,monospace"><span style="font-family:Arial;font-size:13px"></span></span></span>
### Probes and providers
<span style="font-size:small"><span style="font-family:courier new,monospace"><span style="font-family:Arial;font-size:13px">A provider is a collection of probe.
</span></span></span>
#### Probe syntax
Four fields describe a probe:
<span><span style="font-family:courier new,monospace"><span style="font-size:small">provider:module:function:name</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
Examples:
<span><span style="font-family:courier new,monospace"><span style="font-size:small">fbt:mach_kernel:setuid:entry</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">syscall::open*:entry</span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
Notes: Some special characters *, ?, [, and ] are allowed.
* is the well known wildcard extension. 
? character is for any single character in the name. 
[ and ] characters are used to specify a set of specific characters in the name.
#### Listing probes
<span style="font-family:courier new"><span style="font-size:12px">dtrace -l</span></span> lists all available probes.


<span style="font-family:courier new,monospace"><span style="font-size:small">   ID   PROVIDER            MODULE                          FUNCTION NAME</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    1     dtrace                                                     BEGIN</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    2     dtrace                                                     END</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    3     dtrace                                                     ERROR</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">    4   lockstat       mach_kernel                      lck_mtx_lock adaptive-acquire</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">22527 plockstat1 libSystem.B.dylib    pthread_rwlock_unlock$UNIX2003 rw-release</span></span>

#### Available providers
Some providers (non exhaustive list):

  ------------------ --------------------------------
   **Probe name**    **Description**
   fbt               Function boundary tracing
                     
   io                Physical I/O requests/events
   mach_trap        Kernel traps
                     
   proc              Process functions
                     
   profile           Sample count activity?
                     
   syscall           Kernel system calls
                     
   vminfo            
  ------------------ --------------------------------
#### Default variables
FIXME
  ---------------------- --------------------------------------------
  ** Variable name**    **Description**
                         
   arg0...argN           Function arguments and return value
   curpsinfo             Structure of current process information
   errno                 Error code
   execname              Processname
   pid                   Process id
   probefunc             Probe function name
   probename             Probe name
   tid                   Thread id
   timestamp             Nanoseconds since boot
  ---------------------- --------------------------------------------

#### Macro variables
FIXME
+--------------------------------------+--------------------------------------+
| <span                                | <span                                |
| style="font-weight:bold"> Macro     | style="font-weight:bold"> Descripti |
| name                                | on</span>                            |
| </span>                              |                                      |
+--------------------------------------+--------------------------------------+
|  $[0-9]+                         |  macro arguments                    |
+--------------------------------------+--------------------------------------+
|  $egid                             |  effective group id                 |
+--------------------------------------+--------------------------------------+
|  $euid                             |  effective user id                  |
+--------------------------------------+--------------------------------------+
|  $gid                              |  real group id                      |
+--------------------------------------+--------------------------------------+
|  $pid                              |  process id                         |
+--------------------------------------+--------------------------------------+
|  $pgid                             |  process group id                   |
+--------------------------------------+--------------------------------------+
|  $ppid                             |  parent process id                  |
+--------------------------------------+--------------------------------------+
|  $projid                           |  project id                         |
+--------------------------------------+--------------------------------------+
|  $sid                              |  session id                         |
+--------------------------------------+--------------------------------------+
|  $target                           |  target process id                  |
+--------------------------------------+--------------------------------------+
|  $taskid                           |  task id                            |
+--------------------------------------+--------------------------------------+
|  $uid                              |  real user id                       |
+--------------------------------------+--------------------------------------+
### Predicate (optional)
When the predicate evaluates to true, "action" is executed.
  ------------------------- -------------------------------------------
  ** Predicate Name**     ** Description**
                            
   cpu == 0                 true if the probe executes on cpu0
   ppid !=0                 true if the parent process id is not 0
                            
   arg0 == 0                true if first argument is 0
   ppid !=0 && arg0 == 0    ...
  ------------------------- -------------------------------------------
### Action (optional)
C-style functions and semicolon (;) separation for the "body".
Examples: printf(), ustack(), trace, ...
### <span style="font-size:large">Kernel destructive actions</span>
<span style="font-family:Arial;font-size:13px;font-weight:normal"><span style="font-size:small">Understand "destructive for the running OS".</span></span>
#### "-w" flag required for...
<span style="white-space:pre"><span style="font-size:small"><span style="font-family:courier new,monospace"> </span></span></span><span style="font-size:small"><span style="font-family:courier new,monospace">-w  permit destructive actions
</span></span>
<span style="font-family:Helvetica;font-size:12px"></span>
-   <span style="font-size:13px">void stop()</span>
-   <span style="font-size:13px">voir raise()</span>
-   <span style="font-size:13px">void breakpoint(void)</span>
-   <span style="font-size:13px">void chill(int nanoseconds)</span>
-   <span style="font-size:13px">void panic(void)</span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)">panic: We are hanging here... </span></span></span></span>
<span style="font-family:Arial;font-size:13px">It can force a kernel crash dump.
FIXME
</span>
References
----------
<span>[<span style="font-family:courier new,monospace"><span style="font-size:small">man dtrace</span></span>](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man1/dtrace.1.html)<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>[<span style="font-family:courier new,monospace"><span style="font-size:small">man dtruss</span></span>](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man1/dtruss.1m.html)<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span></span>[<span><span style="font-family:courier new,monospace"><span style="font-size:small">man procsystime</span></span></span>](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man1/procsystime.1m.html)<span style="font-size:small">
</span>
<span style="font-size:small">Jon Haslam. <http://wikis.sun.com/display/DTrace/Security>, Sun Microsystems, 2008.</span>
<span style="font-size:small">Glenn Brunette & Jon Haslam. <span style="font-style:italic">Enhancing Security Awareness with DTrace</span>, Sun Microsystems, 2006.</span>
<span style="font-size:small"><span style="font-style:italic">How To Use DTrace.</span> <http://www.sun.com/software/solaris/howtoguides/dtracehowto.jsp>, Sun Microsystems, 2005.</span>
<span style="font-size:small"><span style="font-style:italic">Solaris Dynamic Tracing Guide.</span> <http://docs.sun.com/app/docs/doc/817-6223>, Sun Microsystems, 2005.</span>