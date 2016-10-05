Interprocess Communication (IPC)
================================
Interprocess communication is a "means of information sharing and synchronization" (Singh) between processs. This page describes the various forms of IPC on a Darwin system and also shows forms of IPC not present in Darwin, but in Mac OS X.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Introduction](ipc.html#TOC-Introduction)
2.  [**2** Forms of IPC](ipc.html#TOC-Forms-of-IPC)
    1.  [**2.1** Mach IPC](ipc.html#TOC-Mach-IPC)
    2.  [**2.2** Mach Exceptions](ipc.html#TOC-Mach-Exceptions)
    3.  [**2.3** Unix Signals](ipc.html#TOC-Unix-Signals)
    4.  [**2.4** Unnamed pipes](ipc.html#TOC-Unnamed-pipes)
    5.  [**2.5** Named pipes (fifos)](ipc.html#TOC-Named-pipes-fifos-)
    6.  [**2.6** XSI/System V IPC](ipc.html#TOC-XSI-System-V-IPC)
    7.  [**2.7** POSIX IPC](ipc.html#TOC-POSIX-IPC)
    8.  [**2.8** notifyd](ipc.html#TOC-notifyd)
3.  [**3** Missing forms of IPC](ipc.html#TOC-Missing-forms-of-IPC)
    1.  [**3.1** Distributed Objects](ipc.html#TOC-Distributed-Objects)
    2.  [**3.2** Notifications](ipc.html#TOC-Notifications)
    3.  [**3.3** Apple Events](ipc.html#TOC-Apple-Events)
4.  [**4** Credits](ipc.html#TOC-Credits)
5.  [**5** References](ipc.html#TOC-References)


### Introduction
Processes on a typical Darwin system need to communicate with each other. The Darwin OS provides several mechanisms for such Interprocess Communication (IPC).
### Forms of IPC
Since Darwin and Mac OS X are composed from various systems and infrastructures, they provide means for IPC on several different levels of the OS which will be discussed below. For a more detailed overview, read Chapter 9 of [Mac OS X Internals](http://macosxbook.com/) by Amit Singh which this page is loosely structured after. 
#### Mach IPC {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:14px;margin-top:10px;margin-right:10px;margin-bottom:10px;margin-left:0px"}
<span style="font-size:13px;font-weight:normal">Mach IPC can approximately be compared with BSD sockets, but is more powerful and is mainly used for local machine communication. Mach IPC is a facility of the XNU kernel; it falls into two distinct categories, ports and messages. The XNU kernel implements most aspects of Mach IPC except network-transparent IPC.</span> 

<span style="font-size:13px"><span style="font-weight:bold">Mach ports:</span></span><span style="font-size:13px"><span style="font-weight:bold"> </span></span><span style="font-size:13px;font-weight:normal">Kernel-provided queues of Mach messages. Tasks can send Mach messages to and receive Mach messages from Mach ports. The kernel blocks sending to full and receiving from empty Mach ports. There is also permission control for Mach ports ("port rights") so that unauthorized processes cannot randomly access Mach ports. The kernel itself provides Mach ports to interact with resources such as tasks, threads, etc. Hence, one can see the XNU kernel as a server that serves objects through Mach ports.</span> 

<span style="font-size:13px"><span style="font-weight:bold">Mach messages:</span></span><span style="font-size:13px"><span style="font-weight:bold"> </span></span><span style="font-size:13px;font-weight:normal">Can be sent and received by userspace processes through the mach_msg family of functions. Mach messages in Darwin and Mac OS X have the following structure: header, body, and trailer. There are simple and complex Mach messages, where in simple messages the body is untyped and in complex messages the body is structured. Messages can be passive (meaningful only to the sender and the receiver, but not processed by the kernel) or active (interpreted by the kernel).</span> 

<span style="font-size:13px"><span style="font-weight:bold">XNU aspects:</span> </span><span style="font-size:13px;font-weight:normal">The Mach IPC implementation of Darwin and Mac OS X resides in the osfmk/ipc/ and osfmk/kern/ipc_ trees of the XNU kernel source. It is an essential part of XNU, since Mach ports play a pivotal role in the creation of Mach tasks and threads.</span> 

<span style="font-size:13px"><span style="font-weight:bold">launchd aspects:</span> </span><span style="font-size:13px;font-weight:normal">However, the Mach IPC implementation in Darwin and Mac OS X is not purely a matter of the XNU kernel. Mach systems typically use a <span style="font-style:italic">Network Message Server </span>as an intermediary between sender and receiver for implementing access control. Darwin and Mac OS X, however, use a <span style="font-style:italic">Bootstrap Server </span>as the intermediary instead, which is implemented in </span><span style="font-size:13px"><span style="font-style:italic">launchd</span></span><span style="font-size:13px;font-weight:normal">. The bootstrap server also acts as a <span style="font-style:italic">Name Server<span style="font-weight:bold"> </span><span style="font-style:normal">which allows to announce Mach ports under a human-readable name such as </span></span></span><span style="font-size:13px;font-weight:normal"><span style="font-family:courier new,monospace"><span style="font-size:small">com.apple.SecurityServer</span></span>. Tasks on the local machine can announce ports to launchd, and other tasks can send messages to the ports announced by launchd. Hence, launchd is required in order to allow tasks to use Mach IPC on a Darwin or Mac OS X system. Debug messages containing the word <span style="font-family:courier new,monospace"><span style="font-size:small">bootstrap</span></span> usually refer to this aspect of launchd. To view a list of announced Mach ports on a Darwin or Mac OS X system, use the command <span style="font-family:courier new,monospace"><span style="font-size:small">launchctl bslist</span></span>.</span>
#### Mach Exceptions
Mach Exceptions are interruptions of a program's normal flow of operation when special conditions arise, such as errors (e.g., trying to divide by zero), when debugging (e.g., breakpoints), when using emulation/virtualization or as part of memory management.

When an exception occurs, Mach sends a Mach message to a special Mach port called an <span style="font-style:italic">e</span><span style="font-style:italic">xception port</span>, where an exception handler (e.g., a debugger) can pick it up and react to it. Exception ports exist at the host, task and thread levels. There is a special exception handler called the <span style="font-style:italic">Unix exception handler</span> which translates certain Mach exception messages to Unix signals (see below), thus bridging the Mach and Unix worlds.

#### Unix Signals
Unix signals are messages that are sent to running processes. Typical signals are SUGHUP, SIGKILL, SIGSEGV and others. Users most commonly use the <span style="font-family:courier new,monospace"><span style="font-size:small">kill</span></span> command to send signals to processes. For more information on Unix signals, see [Tech FAQ](http://www.tech-faq.com/unix-signals.shtml). In Darwin and Mac OS X, Unix signals are implemented on top of Mach Exceptions, derived from FreeBSD's implementation.
#### Unnamed pipes
<span style="font-family:courier new,monospace"><span style="font-size:small">man ftok</span></span>?
#### Named pipes (fifos)
<span style="font-family:courier new,monospace"><span style="font-size:small">man 2 mkfifo</span></span>
#### XSI/System V IPC
The X/Open System Interface (XSI) defines a set of IPC interfaces similar to those of System V, especially [message queues](http://www.opengroup.org/onlinepubs/009695399/basedefs/sys/msg.h.html), [semaphores](http://www.opengroup.org/onlinepubs/009695399/basedefs/semaphore.h.html), and shared memory.
#### POSIX IPC
POSIX IPC is defined in the POSIX Real-time Extensions of the POSIX 1003.1b-1993 standard. They are different from XSI/System V IPC despite similar names.


To be written

#### notifyd
notifyd is a daemon which provides basic system-wide notification support. Notifications, in the form of simple text labels, can be posted by any application using a basic Mach API. Other processes can register to receive notifications as they occur, either through signals or Mach ports.
On OS X, CoreFoundation provides features, through its CFNotificationCenter functions, to post and listen for these notifications. These are missing in CFLite, although the presence of the notifyd means that patching these back in should be relatively simple.
### Missing forms of IPC
#### Distributed Objects
Distributed Objects are a form of Remote Procedure Call (RPC) which originally appeared under NeXT. They are a feature of the Foundation.framework, which is exclusive to Mac OS X. The PureFoundation project is (slowly) bringing its features to Darwin, and hopes to eventually provide a compatible implementation of Distributed Objects.
#### Notifications
The form of notifications, as marshalled by notification centres, allow both intra- and interprocess communication. On OS X, compatible implementations are provided by both CoreFoundation and Foundation. CFLite lacks these functions. It is likely that a version of these functions will be patched back into CFLite.
#### Apple Events
Apple Events is an IPC mechanism provided by Mac OS X, but not available on Darwin. Apple Events are mainly used by the AppleScript scripting language to communicate with GUI applications. Although supported by Foundation, the PureFoundation project currently has no plans to implement Apple Events.

### Credits
Chapter 9 of [Mac OS X Internals](http://macosxbook.com/) by Amit Singh


### References
-   [Wikipedia: Inter-process communication](http://en.wikipedia.org/wiki/Inter-process_communication)
-   [Apple: Mach Messaging and Mach Interprocess Communication (IPC)](http://developer.apple.com/documentation/Darwin/Conceptual/KernelProgramming/boundaries/chapter_14_section_4.html)
-   [Amit Singh: Mac OS X Internals](http://macosxbook.com/)
-   [Mach Exception Handlers 101](http://www.wodeveloper.com/omniLists/macosx-dev/2000/June/msg00137.html)
-   [Tech FAQ: What are Unix signals?](http://www.tech-faq.com/unix-signals.shtml)
