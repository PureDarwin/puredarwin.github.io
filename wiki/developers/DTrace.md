DTrace
======

This page is about the DTrace facility in _"Darwin-land"_.

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
__Notes:__ Although PureDarwin is focused on i386, DTrace supports most of common architectures (`-arch i386|x86_64|ppc|ppc64`).
In Mac OS X 10.5, Instruments.app found in developer tools is another front-end to the DTrace facility.
__Warning:__

### Pros
-   Every process, or specific processes, can be traced "simultaneously".
-   Output is fully flexible.
-   Nanosecond timestamp for function execution measurements.
-   Minimum performance impact when used smartly.
-   No need to restart anything in order to trace.
-   Relatively safe.

### Cons

-   Partially supported (around 20K probes available instead of 60K) on Darwin (
-   DTrace cannot fetch low levels hardware data.
-   Performance impact when probe count goes under 36,000 probes (every kernel function entry/return) and 100,000 probes function in user-land.
    Consequently, not really suited for security auditing, because DTrace may drop events if the system is really busy or simply (but dramatically in this case) abort.
-   Need to be run as root (not sure it should belong to "cons" part).


Examples
--------

### A real world example: show missing files

<span style="font-size:13px">On Linux systems, "strace -eopen -f ... 2&gt;&1 | grep ENOENT" can be used to see which files a process tries to open. Using dtrace, the equivalent is:</span>
1.  Open two terminals
2.  In the first terminal, run:
    opensnoop -ex
3.  In the second terminal, run the command that you want to inspect
In the first terminal, you will see the files that are tried to be opened but fail to open (e.g., ENOENT).

### A _cliché_ example: "Hello world!"


#### Inline
dtrace -n "BEGIN { trace("Hello World!"); exit(0);}"
dtrace: description 'BEGIN ' matched 1 probe
CPU     ID                    FUNCTION:NAME
  0      1                           :BEGIN   Hello World!
#### In a file
Edit and save Hello.d:
BEGIN 
{ 
 trace("Hello World!"); 
 exit(0); 
}
Then run the script:
dtrace -s Hello.d 
 
dtrace: script 'Hello.d' matched 1 probe
CPU     ID                    FUNCTION:NAME
  0      1                           :BEGIN   Hello World!
### Detect new process (successfully started)
` proc:::exec-success`
` {`
` printf("%s(pid=%d) started by uid - %dn",execname, pid, uid);`
` }`

### Detect sigkill

proc:::signal-send
/args[2] == SIGKILL/
{
  printf("to %s",args[1]->pr_fname);
  printf(" at %d", timestamp);
  printf(" by (%d)", uid);
  printf(" from %sn", execname);
}
### Detect promiscuous mode changes
fbt:mach_kernel:ifnet_set_promiscuous:*
`{`
`   printf("%s", execname);
`
`}`
### Watch setuid/setgid calls
`/* '*' == {entry|return} */`
`
`
`fbt:mach_kernel:setuid:*`
`{`
`   printf("%s", execname);`
`}`
`
`
`fbt:mach_kernel:setgid:*`
`{`
`   printf("%s", execname);`
`}`
### Classic examples
DTrace [one-liners](http://www.solarisinternals.com/wiki/index.php/DTrace_Topics_One_Liners)
The [DTraceToolkit](http://www.opensolaris.org/os/community/dtrace/dtracetoolkit) (~100 scripts)
D Programming language
----------------------
It seems to have been based on C language for some parts.
(please add text)
1.  D programs are compiled in user-land
2.  And sent to the DTrace virtual machine in the kernel-land
3.  Then run inside the kernel's address space (not in the DTrace process, nor in the target process)



     copyin()      Copies len bytes of data from the user-space address uaddr
                   to the kernel-space address kaddr.


     copyinstr()   Copies a NUL-terminated string, at most len bytes long,
                   from user-space address uaddr to kernel-space address
                   kaddr.  The number of bytes actually copied, including the
                   terminating NUL, is returned in *done.
### A generic D script example
`probe description /predicate/ {    action }`{style="font-family:courier new,monospace"}


### Probes and providers
A provider is a collection of probe.

#### Probe syntax
Four fields describe a probe:
provider:module:function:name`
`
Examples:
fbt:mach_kernel:setuid:entry`
`syscall::open*:entry`
`
Notes: Some special characters *, ?, [, and ] are allowed.
* is the well known wildcard extension. 
? character is for any single character in the name. 
[ and ] characters are used to specify a set of specific characters in the name.
#### Listing probes
dtrace -l lists all available probes.


`   ID   PROVIDER            MODULE                          FUNCTION NAME`
`    1     dtrace                                                     BEGIN`
`    2     dtrace                                                     END`
`    3     dtrace                                                     ERROR`
`    4   lockstat       mach_kernel                      lck_mtx_lock adaptive-acquire`
`[...]`

`22527 plockstat1 libSystem.B.dylib    pthread_rwlock_unlock$UNIX2003 rw-release`

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
### Kernel destructive actions
Understand "destructive for the running OS".
#### "-w" flag required for...
 -w  permit destructive actions


-   void stop()
-   voir raise()
-   void breakpoint(void)
-   void chill(int nanoseconds)
-   void panic(void)
panic: We are hanging here... 
It can force a kernel crash dump.
FIXME

References
----------
[`man dtrace`](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man1/dtrace.1.html)`
`[`man dtruss`](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man1/dtruss.1m.html)`
`[man procsystime](http://developer.apple.com/documentation/Darwin/Reference/ManPages/man1/procsystime.1m.html)

<span style="font-size:small">Jon Haslam. <http://wikis.sun.com/display/DTrace/Security>, Sun Microsystems, 2008.</span>
<span style="font-size:small">Glenn Brunette & Jon Haslam. *Enhancing Security Awareness with DTrace*, Sun Microsystems, 2006.</span>
<span style="font-size:small">*How To Use DTrace.* <http://www.sun.com/software/solaris/howtoguides/dtracehowto.jsp>, Sun Microsystems, 2005.</span>
<span style="font-size:small">*Solaris Dynamic Tracing Guide.* <http://docs.sun.com/app/docs/doc/817-6223>, Sun Microsystems, 2005.</span>