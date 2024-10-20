XNU, the kernel
===============

**Please note:** This page has not been updated to take changes made in Darwin 10, or later into account.

This page is about the XNU kernel.

Both Apple vanilla mach_kernel and Voodoo [xnu-dev](http://code.google.com/p/xnu-dev/) are available and functional in PureDarwin.

It is a work in progress. Please contribute.

### What is XNU

XNU is the kernel used by Darwin and Mac OS X (similar to what GNU/Linux kernel is in a Linux distro).
XNU acronym stands for "X is Not Unix" (although Mac OS X has been Unix certified in 2007).

### Common myths about XNU

(please add some text)

-   *Not* a microkernel (although using parts of the Mach microkernel)
-   *Not* 64-bit (although able to run 64-bit binaries)
-   *Not* so hard to recompile
See [here](http://developer.apple.com/documentation/Darwin/Conceptual/KernelProgramming/Architecture/chapter_3_section_3.html) why the term kernel is used somewhat differently than you might expect.

### Common parts of XNU

-   Mach 3.0
-   BSD
-   I/O Kit

### Creating a prelinked mach_kernel

XNU cannot boot by itself, since it always needs a [certain set](../downloads/puredarwin-nano.html) of kernel extensions (kexts) to be present. However, you can create a mach_kernel file that not only contains XNU itself, but also a defined set of kexts:
```
kextcache -a i386 -K  /Volumes/PureDarwin/mach_kernel  -c /tmp/mach_kernel.prelinked /Volumes/PureDarwin/System/Library/Extensions
```

The result is that you should have a file in /tmp/mach_kernel_prelinked that contains both XNU and the kexts.

Another example, fast boot and kext autoloaded:

```
kextcache -a i386 -s -l -n -c "$MOUNT/System/Library/Caches/com.apple.kernelcaches/kernelcache.DEADBEEF" -k -K "$MOUNT/mach_kernel" -m "$MOUNT/System/Library/Extensions.mkext" "$MOUNT/System/Library/Extensions"
```

### Resources

* <http://en.wikipedia.org/wiki/XNU> 
* <http://osxbook.com/book/bonus/ancient/whatismacosx/arch_xnu.html> 
* <http://code.google.com/p/xnu-dev/>