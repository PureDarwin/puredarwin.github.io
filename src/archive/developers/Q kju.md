Q - [kju:]
============

![This article is outdated and its information may no longer be relevant.](/archive/img/notice/article-outdated.svg)


Some QEMU attempts through [Q](http://www.kju-app.org/), A CPU emulator for Macintosh.

Status
------
As of January 2010, Q.app still uses qemu 0.9.x, whereas PureDarwin needs 0.10 to function properly. Hence, we recommend to use [QEMU](QEMU.md) instead for now.

The latest version (Q-0.9.1d118) has been updated last year, creating a big gap between the latest official QEMU and the one used in Q front-end.
Consequently, Q is not usable for PureDarwin at this time.

We also tried to replace i386-softmmu with a newer version inside Q.app but no success since the usage is different between both parts (and also the features supported).
UI
--
### Q control manager

![](/archive/img/developers/qemu/qemu-q/Q%20manager.png)
### Configuration

![](/archive/img/developers/qemu/qemu-q/Q%20config.png)
Boot sequence
-------------
### DFE bootloader

![](/archive/img/developers/qemu/qemu-q/Q%20dfe%20bootloader.png)
#### CPU:FSB multiplier detection fails
**Please, let us know if you have a solution.
**
![](/archive/img/developers/qemu/qemu-q/Q%20CPUFSB%20detection%20fails.png)
### Chameleon bootloader

![](/archive/img/developers/qemu/qemu-q/Q%20chameleon%20bootloader.png)

SMBIOS well-known problem is bypassed with Voodoo kernel (xnu-dev).


![](/archive/img/developers/qemu/qemu-q/Q%20SMBIOS%20not%20found.png)

Then, the real boot begins, but quickly ends with a problem related to APIC similar to the one in [VirtualBox](VirtualBox.md) page.


![](/archive/img/developers/qemu/qemu-q/Q%20local%20APIC%20version%20not%20as%20expected.png)


Then, with `<string>-f -v -x cpus=1 busratio=16 io=0x21</string>` in */Library/Preferences/SystemConfiguration/com.apple.Boot.plist*, things go far:


![](/archive/img/developers/qemu/qemu-q/Q%20busration%20and%20io.png)


**Ressources**

<http://www.kju-app.org/> (Q)
<http://bellard.org/qemu/> (QEMU)
<http://code.google.com/p/xnu-dev> (Voodoo, A fork of the XNU kernel)
