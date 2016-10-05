Q - [kju:]
============
Some QEMU attempts through [Q](http://www.kju-app.org/), A CPU emulator for Macintosh.


<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:300px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Status](qemu-q.html#TOC-Status)
2.  [**2** UI](qemu-q.html#TOC-UI)
    1.  [**2.1** Q control manager](qemu-q.html#TOC-Q-control-manager)
    2.  [**2.2** Configuration](qemu-q.html#TOC-Configuration)
3.  [**3** Boot sequence](qemu-q.html#TOC-Boot-sequence)
    1.  [**3.1** DFE bootloader](qemu-q.html#TOC-DFE-bootloader)
        1.  [**3.1.1** CPU:FSB multiplier detection fails](qemu-q.html#TOC-CPU:FSB-multiplier-detection-fails)
    2.  [**3.2** Chameleon bootloader](qemu-q.html#TOC-Chameleon-bootloader)

Status
------
As of January 2010, Q.app still uses qemu 0.9.x, whereas PureDarwin needs 0.10 to function properly. Hence, we recommend to use [QEMU](../qemu.html) instead for now.

The latest version (Q-0.9.1d118) has been updated last year, creating a big gap between the latest official QEMU and the one used in Q front-end.
Consequently, Q is not usable for PureDarwin at this time.

We also tried to replace i386-softmmu with a newer version inside Q.app but no success since the usage is different between both parts (and also the features supported).
UI
--
### Q control manager

[![](../../_/rsrc/1237726830785/developers/qemu/qemu-q/Q%20manager.png%3Fheight=199&width=420)](qemu-q/Q%20manager.png%3Fattredirects=0)
### Configuration

[![](../../_/rsrc/1237726830785/developers/qemu/qemu-q/Q%20config.png%3Fheight=420&width=314)](qemu-q/Q%20config.png%3Fattredirects=0)
Boot sequence
-------------
### DFE bootloader

[![](../../_/rsrc/1237726830785/developers/qemu/qemu-q/Q%20dfe%20bootloader.png%3Fheight=268&width=420)](qemu-q/Q%20dfe%20bootloader.png%3Fattredirects=0)
#### CPU:FSB multiplier detection fails
<span style="color:rgb(255,0,0);font-weight:bold">Please, let us know if you have a solution.
</span>
[![](../../_/rsrc/1237726830785/developers/qemu/qemu-q/Q%20CPUFSB%20detection%20fails.png%3Fheight=269&width=420)](qemu-q/Q%20CPUFSB%20detection%20fails.png%3Fattredirects=0)
### Chameleon bootloader

[![](../../_/rsrc/1237726830785/developers/qemu/qemu-q/Q%20chameleon%20bootloader.png%3Fheight=267&width=420)](qemu-q/Q%20chameleon%20bootloader.png%3Fattredirects=0)

SMBIOS well-known problem is bypassed with Voodoo kernel (xnu-dev).


[![](../../_/rsrc/1237726830785/developers/qemu/qemu-q/Q%20SMBIOS%20not%20found.png%3Fheight=268&width=420)](qemu-q/Q%20SMBIOS%20not%20found.png%3Fattredirects=0)

Then, the real boot begins, but quickly ends with a problem related to APIC similar to the one in [VirtualBox](../virtualbox.html) page.


[![](../../_/rsrc/1237726830785/developers/qemu/qemu-q/Q%20local%20APIC%20version%20not%20as%20expected.png%3Fheight=101&width=420)](qemu-q/Q%20local%20APIC%20version%20not%20as%20expected.png%3Fattredirects=0)


Then, with <span style="font-family:courier new,monospace"><span style="font-size:small">&lt;string&gt;-f -v -x cpus=1 busratio=16 io=0x21&lt;/string&gt;</span></span> in <span style="font-style:italic">/Library/Preferences/SystemConfiguration/com.apple.Boot.plist</span>, things go far:


[![](../../_/rsrc/1237726830785/developers/qemu/qemu-q/Q%20busration%20and%20io.png%3Fheight=311&width=420)](qemu-q/Q%20busration%20and%20io.png%3Fattredirects=0)


<span style="font-size:22px;font-weight:bold">Ressources</span>

<http://www.kju-app.org/> (Q)
<http://bellard.org/qemu/> (QEMU)
<http://code.google.com/p/xnu-dev> (Voodoo, A fork of the XNU kernel)

