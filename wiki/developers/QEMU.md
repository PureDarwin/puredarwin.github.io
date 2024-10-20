QEMU
====
This page is about running PureDarwin on the QEMU emulator and is *not *about running Mac OS X.

[QEMU](http://en.wikipedia.org/wiki/QEMU) is a hardware emulator that can be used to run operating systems on virtualized hardware, not unlike VMware or Parallels. It is an open source project.
The ability to run PureDarwin on emulated hardware can be very useful, especially for development, testing and debugging.
**If you get the "Error parsing plist file", then you need to increase the amount of virtual RAM. At least 330 MB seem to be required. If the kernel just crashes and the boot prompt appears again, press F8 and enter mach_kernel.voodoo <enter>.**

Running PureDarwin Xmas on QEMU
-------------------------------
### On Linux hosts
~~To get [PureDarwin Xmas](../downloads/xmas.html) to run in QEMU, fetch QEMU from svn, compile, run without kqemu (it might work on OSX-supported cpus). **Update:** if you can get a **0.10** binary of qemu for your platform (some are linked below), you don't necessarily need to compile from svn any more.~~ **Update 2:** As of Ubuntu 9.10, the QEMU that can be installed with sudo apt-get install qemu is sufficient, so you don't need to compile or download a special version of QEMU any more. Use the following configuration:



or

`-hda puredarwinxmas.vmdk -cdrom purdarwinxmas.vmdk `-boot d -m 512


or


`-hda puredarwinxmas.vmdk -cdrom purdarwinxmas.iso `-boot d -m 512



QEMU can (at least on some platforms) emulate the Realtek RTL8139 network interface.
An open source driver for this NIC is included with PureDarwinXmas. Enable the interface in QEMU with the -net nic,model=rtl8139 -no-kvm-irqchip -net user option.

Run it using the instructions above (although `-hda puredarwinxmas.vmdk -cdrom puredarwinxmas.vmdk -boot d -m 512` seems the more reliable option).
X will probably fail to start first time, but can then be kicked into life with `startx` or `pd_startx`.




[![](http://img356.imageshack.us/img356/4199/puredarwinxmasinqemudh5.png)](http://img356.imageshack.us/img356/4199/puredarwinxmasinqemudh5.png)

PureDarwin Xmas running on openSUSE. __Credits:__ oxygene 



![](/img/developers/qemu/qemu-ubuntu.png)
PureDarwin Xmas on Ubuntu 8.10 (using the binary linked below) and mach_kernel.voodoo. 

Command used:
`qemu -hda 'puredarwinxmas.vmdk' -cdrom 'puredarwinxmas.vmdk' -boot d -m 512`
press F8 when asked
`mach_kernel.voodoo`


### On Windows hosts
[![](http://img7.imageshack.us/img7/6195/qemupdwin32.jpg)](http://img7.imageshack.us/img7/6195/qemupdwin32.jpg)

PureDarwin Xmas on MS Windows XP (using the binary linked above).
__Credits:__ oxygene
### On Mac OS X hosts

QEMU 0.10.1 from MacPorts can run PureDarwin Xmas with


qemu -hda puredarwinxmas.vmdk -cdrom puredarwinxmas.vmdk -boot d -m 512


__Note:__ if you want to run qemu from a different location, use the -L option as:

qemu -L ./pc-bios/ -hda puredarwinxmas.vmdk -cdrom puredarwinxmas.vmdk -boot d -m 512





![](/img/developers/qemu/Qemu%20first%20stage.png)

If you don't boot by default with the Voodoo kernel (xnu-dev), at boot press F8...
![](/img/developers/qemu/Qemu%20bootloader%20stage.png)

And enter
`mach_kernel.voodoo rd=disk1s3 -v`

or, if you have the vmdk as -hda:

`mach_kernel.voodoo rd=disk0s3 -v`

Wait for a bit on `failed to open/create the journal`... if that happens.

![](/img/developers/qemu/Qemu%20PD%20booting.png)

At the end of the KEXTs decompression phase, the CPU FSB clock and ration should be adjusted by the voodoo kernel.

![](/img/developers/qemu/Qemu%20PD%20booting2.png)
After the KEXTs decompression phase, you should see the kernel booting (notice the network adapter supported).

![](/img/developers/qemu/Qemu%20PD%20booting3.png)
Then depending your settings, a login prompt or X should be waiting for you.

It is necessary to launch X11 manually by issuing /usr/X11R6/bin/startx.




![](/img/developers/qemu/pd-qemu-mp.jpg)

QEMU 0.10.1 from MacPorts running PureDarwin on Mac OS X 10.5.
QEMU devices
------------
Here is a list of potential devices found in a QEMU guest OS.

"0x1013","0x00B8","Cirrus Logic","CL-GD5446","64-bit VisualMedia Accelerator"
"0x8086","0x7000","Intel Corporation","82371SB","PIIX3 PCI-to-ISA Bridge (Triton II)"
"0x8086","0x7113","Intel Corporation","82371AB/EB/MB","PIIX4/4E/4M Power Management Controller"
"0x1af4","0x1002","",""
"0x10EC","0x8139","Realtek Semiconductor","RTL-8139/8139C/8139C","Realtek RTL8139 Family PCI Fast Ethernet NIC"
"0x8086","0x7010","Intel Corporation","82371SB","PIIX3 IDE Interface (Triton II)"
"0x8086","0x1237","Intel Corporation","82440LX/EX","PCI & Memory"

QEMU network
------------
The dawn of networking support in PureDarwin finally appears with QEMU.

QEMU vlan network capability is entangled with the "user mode network stack".
This network stack supports ip, tcp, udp, dhcp, tftp, etc.. but ICMP.
It also acts as a proxy between the qemu process and the target process, with tcp/udp data field decapsulation and forward.
### The user network stack

__Credits:__ Partial network support already existed, thanks to "hingwah" who helped and pointed its existence to us.

As said in [3.7.3 Using the user mode network stack](http://www.qemu.org/qemu-doc.html#SEC3) QEMU documentation ("*The DHCP server assign addresses to the hosts starting from 10.0.2.15.*"), the interface is well auto-assigned (notes: KernelEventMonitor (confid_plugins) has been added and seems to be responsible of the client DHCP capability) as the route to the virtual available gateway (a firewall / dhcp server).

### Requirements
Append -net user if it is not already there to the qemu command line:
[...] -net nic,model={i82551|i82557b|rtl8139} -no-kvm-irqchip -net user [...]

~~Be prepare to ping the gateway continuously, it's a workaround.~~
As user inp reported on #puredarwin, adding '-no-kvm-irqchip' to the qemu call solves this issue with the rtl8139 driver.

Of course, it's mandatory to have a Kernel EXTension matching its respective device.

E.g. below with the realtek kext matching its respective virtual RTL8139 device in QEMU:

![](/img/developers/qemu/guest%20ip%20auto%20set.png)

### DHCP (IPv4)
An example of a "correct" configuration, where everything has been provided automatically (KernelEventMonitor) via DHCP.

![](/img/developers/qemu/qemunusermodenetworkstacksupport.png)

**What expected:**

10.0.2.2 should respond to ping (gateway firewall/dhcpd).
10.0.2.2 should be the default route.
10.0.2.3 should answer to DNS query.
10.0.2.4 should answer to SMB (if available).
10.0.2.15 is where starts the first guest ip address.

**What is well known:**

~~It seems that network hangs easily if the gateway is not pinged when network operations are needed.~~ As user inp reported on #puredarwin, adding '-no-kvm-irqchip' to the qemu call solves this issue with the rtl8139 driver.
### Ping workaround
~~ping the gateway (10.0.2.2) from the guest side (PureDarwin) seems necessary at this time.~~
~~If it is not the done, the connection simply hangs or fails to establish sometimes.~~
As user inp reported on #puredarwin, adding '-no-kvm-irqchip' to the qemu call solves this issue with the rtl8139 driver.

Depending the ping interval (-i) against the virtual gateway, the bandwith varies (a pseudo bandwith control state; qos?).
Below is an example across the time, where the interval took the no value, then 0.9, 0.5, 0.1 and 0 (This example was done downloading nmap).

![](/img/developers/qemu/picbd.png)
### Miscellaneous
#### Guest fingerprint (10.0.2.15)
The famous Fyodor `[nmap](http://nmap.org/)' basic fingerprint result against 10.0.2.15 (guest: en0) looks like (X running without --no-listen tcp as shown).

![](/img/developers/qemu/nmapinqemuusermodenetstack.png)

#### Gateway fingerprint (10.0.2.2)
Interesting to see what looks like from nmap point of view the virtual gateway (user mode network stack):


![](/img/developers/qemu/nmapinqemuusermodethegw.png)
#### DNS server fingerprint (10.0.2.3)

..

![](/img/developers/qemu/nmapinqemuusermodednsd.png)

QEMU options
------------

This is another non exhaustive list of (reported to work) options available. Some part also needs investigations and feedback.
### Standard options
`-M machine      select emulated machine (-M ? for list) `**Need investigations.** (could be interesting to see how it is close or not the reality when it is possible to compare the cases)
`-cpu cpu        select CPU (-cpu ? for list) `**Need investigations.**

`-fda/-fdb file  use 'file' as floppy disk 0/1 image` **No thanks.**

`-hda/-hdb file  use 'file' as IDE hard disk 0/1 image` **Reported to work with a iso, dmg, vmdk (convert or not).**
`-hdc/-hdd file  use 'file' as IDE hard disk 2/3 image` **Need investigations.**
`-cdrom file     use 'file' as IDE cdrom image (cdrom is ide1 master)` **Reported to work with a iso, dmg, vmdk (convert or not).**

``

`-smp n          set the number of CPUs to 'n' [default=1]` ****

`-k language     use keyboard layout (for example "fr" for French)` **Need investigations, not working.**

`-vga [std|cirrus|vmware] `****
`-usb            enable the USB driver (will be the default soon)` **Need investigations.**

`-usbdevice name add the host or guest USB device 'name'` **Need investigations.**

`-name string    set the name of the guest `**PureDarwin.**

`-uuid %08x-%04x-%04x-%04x-%012x specify machine` **Need investigations, UUID C0FFEEC0-FFEE-C0FF-EEC0-FFEEC0FFEEC0 has no effect.**

### Network options
According to the `man', "*The NIC is an ne2k_pci by default on the PC target*", but some other valid values are: 
i82551, i82557b, i82559er, ne2k_pci, ne2k_isa, pcnet, rtl8139, e1000, smc91c111, lance and mcf_fec.


`-net nic[,vlan=n][,macaddr=addr][,model=type]`
create a new Network Interface Card and connect it to VLAN 'n'-net nic,model=rtl8139 is enabled by PureFoundation. Need investigations.


`-boot [a|c|d|n] boot on floppy (a), hard disk (c), CD-ROM (d), or network (n)`** "d" with the corresponding target is functional.**
****

-redir to test. **Need investigations**
**-tftp prefix**
-smb
-macaddr addr
-nics




**
**
The option "-net nic,model={i82551|i82557b}" seems to match with [AppletIntel8255x](http://src.macosforge.org/Roots/9A581/AppleIntel8255x.root.tar.gz) from DarwinBuild:


![](/img/developers/qemu/qemu%20net%208255x%20bis.png)


![](/img/developers/qemu/qemu%20net%208255x.png)
### Live options
Press ctrl+alt+2 to switch to QEMU monitor:

![](/img/developers/qemu/qemu%20ctrl%20alt%202.png)

![](/img/developers/qemu/qemu%20ctrl%20alt%202%20help.png)


Press ctrl+alt+3 to switch to serial0 console:

![](/img/developers/qemu/qemu%20ctrl%20alt%203.png)

Press ctrl+alt+4 to switch to parallel0 console:

![](/img/developers/qemu/qemu%20ctrl%20alt%204.png)

**Patches to run stock XNU on QEMU**

Currently, it appears that one needs to used a patched version of the XNU kernel called mach_kernel.voodoo to run on QEMU. This is even true when running QEMU on an Intel Mac on Mac OS X (tested with a MacBook Pro).

Alexander Graf has sent patches to the QEMU mailing list that allow Darwin to run on QEMU natively.
Specifically, these patches
-   [Add HPET](http://lists.gnu.org/archive/html/qemu-devel/2008-01/msg00173.html)
-   [Add a dummy LPC device](http://lists.gnu.org/archive/html/qemu-devel/2008-01/msg00174.html) on which the HPET is located
-   [Identify CPU as Core Duo](http://lists.gnu.org/archive/html/qemu-devel/2008-01/msg00176.html) by setting family 13, adding a MSR and a CPUID instruction
-   [Add partial ICH6](http://lists.gnu.org/archive/html/qemu-devel/2008-01/msg00179.html) IDE controller emulation
-   [Add support for multiboot](http://lists.gnu.org/archive/html/qemu-devel/2008-01/msg00178.html) (such as a modified boot-132 boot loader)
-   [Add ACPI entries](http://lists.gnu.org/archive/html/qemu-devel/2008-01/msg00180.html) to Bochs 
They also add some other functionality that is not relevant for running Darwin.

It seems that the necessary patches have made their way into QEMU 0.10, as this version doesn't need special patching any more.

probono's networking experiments 12/2011
----------------------------------------
The experiments are done with a "fuller" PureDarwin installation than Xmas or Nano. Above it says "everything has been provided automatically (KernelEventMonitor) via DHCP", however it doesn't do that for me (I must be missing something still). Hence I set up networking by hand, which is a bit cumbersome:
<!--
`The following are my tests on Ubuntu 12/2011; probono`
`# qemu: pci_add_option_rom: failed to find romfile "pxe-rtl8139.bin"`
`# can be solved with`
`sudo apt-get install kvm-pxe`
`# Launch qemu as root and with -redir tcp:22::22 for SSH access`
`sudo qemu -hda /dev/sdc -net nic,model=rtl8139 -no-kvm-irqchip -net user -redir tcp:22::22`
`# Inside qemu`
`ifconfig en2 10.0.2.15 up`
`ping 10.0.2.2 # works (which is the gateway provided by qemu)`
`# Create /etc/rc.local with the following content to`
`# bring en2 up automatically at boot time `
`#!/bin/bash`
`ifconfig en2 10.0.2.15 up`
`sudo route add 0.0.0.0 10.0.2.2`
`# Headless SSH server inside qemu`
`sudo qemu -hda /dev/sdc -net nic,model=rtl8139 -no-kvm-irqchip -net user -redir tcp:22::22 -vnc :1 -redir tcp:80::80`
`# Works :-)`
`# The only thing that does not work yet is DNS`
`# scutil --dns # resolver #1 is empty, which is a problem -- very ugly workaround:`
echo 'nameserver 10.0.2.3' &gt; /etc/resolver/com
echo 'nameserver 10.0.2.3' &gt; /etc/resolver/org
echo 'nameserver 10.0.2.3' &gt; /etc/resolver/net
echo 'nameserver 10.0.2.3' &gt; /etc/resolver/de
echo 'nameserver 10.0.2.3' &gt; /etc/resolver/edu-->
The following are my tests on Ubuntu 12/2011; probono
```sh
# qemu: pci_add_option_rom: failed to find romfile "pxe-rtl8139.bin"
# can be solved with
sudo apt-get install kvm-pxe
# Launch qemu as root and with -redir tcp:22::22 for SSH access
sudo qemu -hda /dev/sdc -net nic,model=rtl8139 -no-kvm-irqchip -net user -redir tcp:22::22
# Inside qemu
ifconfig en2 10.0.2.15 up
ping 10.0.2.2 # works (which is the gateway provided by qemu)
# Create /etc/rc.local with the following content to
# bring en2 up automatically at boot time 
#!/bin/bash
ifconfig en2 10.0.2.15 up
sudo route add 0.0.0.0 10.0.2.2
# Headless SSH server inside qemu
sudo qemu -hda /dev/sdc -net nic,model=rtl8139 -no-kvm-irqchip -net user -redir tcp:22::22 -vnc :1 -redir tcp:80::80
# Works :-)
# The only thing that does not work yet is DNS
# scutil --dns # resolver #1 is empty, which is a problem -- very ugly workaround:
echo 'nameserver 10.0.2.3' > /etc/resolver/com
echo 'nameserver 10.0.2.3' > /etc/resolver/org
echo 'nameserver 10.0.2.3' > /etc/resolver/net
echo 'nameserver 10.0.2.3' > /etc/resolver/de
echo 'nameserver 10.0.2.3' > /etc/resolver/edu
```

Rafael's networking information 01/2012
---------------------------------------
Our reader Rafael writes:

<pre>
For the network problem it's just a matter of patching kvm module and you can use full acceleration, the patch is know (qemu dev don't want it because it's specific to qemu userland software and they want kvm module to remain compatible with other userland software - which ones? ):
Pick the latest kernel module from:
<http://sourceforge.net/projects/kvm/files/kvm-kmod/>
Open the x86/ioapic.c file:
search for this function:
int kvm_ioapic_set_irq(struct kvm_ioapic *ioapic, int irq, int level)
and change:
        level ^= entry.fields.polarity;
to
        //level ^= entry.fields.polarity;
        
And then rtl8139 will work as well as AppleIntelE1000 from :
svn co https://osx86drivers.svn.sourceforge.net/svnroot/osx86drivers/AppleIntelE1000/AppleIntelE1000
--> but this last is derived from linux so it lacks debug specific part but I think this is the more interesting given you can redistribute it.
If you use recent xnu kernel you also need to patch qemu (or use kernel patched) to tell you use apic version 14 ( qemu dev don't want ton upgrade apic version as they don't have too to run linux or windows) or you will hit an assert/kp from kernel.
Open hw/apic.c from qemu source:
In this function:
static uint32_t apic_mem_readl(void *opaque, target_phys_addr_t addr)
Change:
        val = 0x11 | ((APIC_LVT_NB - 1) << 16); /* version 0x11 */
to
        val = 0x14 | ((APIC_LVT_NB - 1) << 16); /* version 0x14 */ 
</pre>
Thanks Rafael for sharing this information, which is not easy to find. kvm is doing really great these days.

QSOC project on Darwin support in QEMU
--------------------------------------
http://wiki.qemu.org/Google_Summer_of_Code_2012#Finish_OS_X_Virtualization_Support

References
----------
-   [Darwin on QEMU Forum](http://qemu-forum.ipi.fi/viewforum.php?f=13)
-   [T2 KVM packages](http://www.t2-project.org/packages/kvm.html) which are able to boot PureDarwin nano (thanks rxr)
-   [QEMU 0.10 binary for Windows](http://www.coresystems.de/%7Epatrick/qemu-0.10.0-bin.zip) which is able to boot PureDarwin (thanks oxygene)
-   [QEMU 0.10 binary for Ubuntu](http://www.getdeb.net/release/4079) which is able to boot PureDarwin
-   [QEMU 0.10.1 binary for Mac OS X ](../downloads.html)which is able to boot PureDarwin
-   <http://bellard.org/qemu/> (QEMU)
-   <http://www.kju-app.org/> (Q) this front-end is unfortunately not usable (last update was one year ago) for PureDarwin.

hfsprogs
========
debian and Ubuntu have a package called "hfsprogs", which can be used to create HFS+ disk images:
`apt-get install hfsprogs`
`mkfs.hfsplus disk.hfsplus `
`Initialized disk.hfsplus as a 100 MB HFS Plus volume`
`file disk.hfsplus `
`disk.hfsplus: Macintosh HFS Extended version 4 data last mounted by: '10.0', created: Mon Mar 23 18:32:16 2009, last modified: Mon Mar 23 18:32:16 2009, last checked: Mon Mar 23 18:32:16 2009, block size: 4096, number of blocks: 25600, free blocks: 25197`
`sudo mkdir /media/hfsplus`
`sudo mount disk.hfsplus /media/hfsplus/ -o loop`
Now we can copy something there
(How) can we use this disk image with qemu?
If we want to make this bootable with a boot loader, we need to have a partition table inside the disk image!
Probably we need to do this along these lines:
http://wiki.eeeuser.com/howtocustomrestoreimage:pt2mkcustomimage
