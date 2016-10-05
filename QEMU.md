QEMU
====
This page is about running PureDarwin on the QEMU emulator and is <span style="font-style:italic">not </span>about running Mac OS X.

[QEMU](http://en.wikipedia.org/wiki/QEMU) is a hardware emulator that can be used to run operating systems on virtualized hardware, not unlike VMware or Parallels. It is an open source project.
The ability to run PureDarwin on emulated hardware can be very useful, especially for development, testing and debugging.
**
<span style="color:rgb(255,0,0)">If you get the "Error parsing plist file", then you need to increase the amount of virtual RAM. At least 330 MB seem to be required. If the kernel just crashes and the boot prompt appears again, press F8 and enter mach_kernel.voodoo &lt;enter&gt;.</span>**


<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Running PureDarwin Xmas on QEMU](qemu.html#TOC-Running-PureDarwin-Xmas-on-QEMU)
    1.  [**1.1** On Linux hosts](qemu.html#TOC-On-Linux-hosts)
    2.  [**1.2** On Windows hosts](qemu.html#TOC-On-Windows-hosts)
    3.  [**1.3** On Mac OS X hosts](qemu.html#TOC-On-Mac-OS-X-hosts)
2.  [**2** QEMU devices](qemu.html#TOC-QEMU-devices)
3.  [**3** QEMU network](qemu.html#TOC-QEMU-network)
    1.  [**3.1** The user network stack](qemu.html#TOC-The-user-network-stack)
    2.  [**3.2** Requirements](qemu.html#TOC-Requirements)
    3.  [**3.3** DHCP (IPv4)](qemu.html#TOC-DHCP-IPv4-)
    4.  [**3.4** Ping workaround](qemu.html#TOC-Ping-workaround)
    5.  [**3.5** Miscellaneous](qemu.html#TOC-Miscellaneous)
        1.  [**3.5.1** Guest fingerprint (10.0.2.15)](qemu.html#TOC-Guest-fingerprint-10.0.2.15-)
        2.  [**3.5.2** Gateway fingerprint (10.0.2.2)](qemu.html#TOC-Gateway-fingerprint-10.0.2.2-)
        3.  [**3.5.3** DNS server fingerprint (10.0.2.3)](qemu.html#TOC-DNS-server-fingerprint-10.0.2.3-)
4.  [**4** QEMU options](qemu.html#TOC-QEMU-options)
    1.  [**4.1** Standard options](qemu.html#TOC-Standard-options)
    2.  [**4.2** Network options](qemu.html#TOC-Network-options)
    3.  [**4.3** Live options](qemu.html#TOC-Live-options)
5.  [**5** probono's networking experiments 12/2011](qemu.html#TOC-probono-s-networking-experiments-12-2011)
6.  [**6** Rafael's networking information 01/2012](qemu.html#TOC-Rafael-s-networking-information-01-2012)
7.  [**7** QSOC project on Darwin support in QEMU](qemu.html#TOC-QSOC-project-on-Darwin-support-in-QEMU)
8.  [**8** References](qemu.html#TOC-References)

Running PureDarwin Xmas on QEMU
-------------------------------
### On Linux hosts
~~To get [PureDarwin Xmas](../downloads/xmas.html) to run in QEMU, fetch QEMU from svn, compile, run without kqemu (it might work on OSX-supported cpus). **Update:** if you can get a **0.10** binary of qemu for your platform (some are linked below), you don't necessarily need to compile from svn any more.~~ **Update 2:** As of Ubuntu 9.10, the QEMU that can be installed with sudo apt-get install qemu is sufficient, so you don't need to compile or download a special version of QEMU any more. Use the following configuration:
<span style="border-collapse:separate;font-family:courier new;font-size:12px">
</span>
<span style="border-collapse:separate;font-family:Monaco;font-size:9px"><span style="font-family:courier new,monospace"><span style="font-size:small">-hda someemptydiskimage (if you want some disk to work on) -hdb puredarwinxmas.vmdk -cdrom purdarwinxmas.vmdk </span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">-boot d -m 512
</span></span></span></span>
or

<span style="border-collapse:separate;font-family:Monaco;font-size:9px"><span style="font-family:courier new,monospace"><span style="font-size:small">-hda puredarwinxmas.vmdk -cdrom purdarwinxmas.vmdk </span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">-boot d -m 512
</span></span></span></span>
<span style="border-collapse:separate;font-family:courier new;font-size:12px"><span style="border-collapse:collapse;font-family:Arial;font-size:13px"></span></span>
or

<span style="border-collapse:separate;font-family:courier new;font-size:12px"><span style="border-collapse:collapse;font-family:Arial;font-size:13px"></span></span>
<span style="border-collapse:separate;font-family:Monaco;font-size:9px"><span style="font-family:courier new,monospace"><span style="font-size:small">-hda puredarwinxmas.vmdk -cdrom purdarwinxmas.iso </span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">-boot d -m 512
</span></span></span></span>


QEMU can (at least on some platforms) emulate the Realtek RTL8139 network interface.
An open source driver for this NIC is included with PureDarwinXmas. Enable the interface in QEMU with the <span><span style="font-family:courier new,monospace"><span style="font-size:small">-net nic,model=rtl8139 -no-kvm-irqchip -net user</span></span></span> option.

Run it using the instructions above (although <span style="font-family:courier new,monospace"><span style="font-size:small">-hda puredarwinxmas.vmdk -cdrom puredarwinxmas.vmdk -boot d -m 512</span></span><span style="font-size:small"> </span>seems the more reliable option).
X will probably fail to start first time, but can then be kicked into life with <span style="font-family:courier new,monospace"><span style="font-size:small">startx</span></span> or <span style="font-family:courier new,monospace"><span style="font-size:small">pd_startx</span></span>.




[![](http://img356.imageshack.us/img356/4199/puredarwinxmasinqemudh5.png)](http://img356.imageshack.us/img356/4199/puredarwinxmasinqemudh5.png)

PureDarwin Xmas running on openSUSE. <span style="text-decoration:underline">Credits:</span> oxygene 



[![](../_/rsrc/1237829354226/developers/qemu/qemu-ubuntu.png%3Fheight=336&width=420)](qemu/qemu-ubuntu.png%3Fattredirects=0)
PureDarwin Xmas on Ubuntu 8.10 (using the binary linked below) and mach_kernel.voodoo. 

Command used:
<span style="font-family:courier new,monospace">qemu -hda 'puredarwinxmas.vmdk' -cdrom 'puredarwinxmas.vmdk' -boot d -m 512</span>
press F8 when asked
<span style="font-family:courier new,monospace">mach_kernel.voodoo</span>
<span style="font-family:courier new;font-size:12px"><span style="font-family:Arial;font-size:13px">Then have to launch X11 manually:
<span style="font-family:courier new,monospace"><span style="font-size:small">/usr/X11/bin/startx</span></span></span></span>

### On Windows hosts
[![](http://img7.imageshack.us/img7/6195/qemupdwin32.jpg)](http://img7.imageshack.us/img7/6195/qemupdwin32.jpg)

PureDarwin Xmas on MS Windows XP (using the binary linked above).
<span style="text-decoration:underline">Credits:</span> oxygene
### On Mac OS X hosts

QEMU 0.10.1 from MacPorts can run PureDarwin Xmas with

<span style="font-family:courier new;font-size:12px"></span>
qemu -hda puredarwinxmas.vmdk -cdrom puredarwinxmas.vmdk -boot d -m 512

<span style="font-family:Arial;font-size:13px"></span>
<span style="text-decoration:underline">Note:</span> if you want to run qemu from a different location, use the -L option as:

<span style="font-size:small">qemu -L ./pc-bios/ -hda puredarwinxmas.vmdk -cdrom puredarwinxmas.vmdk -boot d -m 512
</span>


<span style="font-family:Arial;font-size:13px"></span>
<span style="border-collapse:separate;font-family:courier new;font-size:12px"><span style="border-collapse:collapse;font-family:Arial;font-size:13px"></span></span>
[![](../_/rsrc/1237722501980/developers/qemu/Qemu%20first%20stage.png%3Fheight=263&width=420)](qemu/Qemu%20first%20stage.png%3Fattredirects=0)

If you don't boot by default with the Voodoo kernel (xnu-dev), at boot press F8...
[![](../_/rsrc/1237722807563/developers/qemu/Qemu%20bootloader%20stage.png%3Fheight=263&width=420)](qemu/Qemu%20bootloader%20stage.png%3Fattredirects=0)

And enter
<span style="font-family:courier new,monospace"><span style="font-size:small">mach_kernel.voodoo rd=disk1s3 -v</span></span>

or, if you have the vmdk as -hda:

<span style="font-family:courier new,monospace"><span style="font-size:small">mach_kernel.voodoo rd=disk0s3 -v</span></span>

Wait for a bit on <span style="font-family:courier new,monospace"><span style="font-size:small">failed to open/create the journal</span></span>... if that happens.

[![](../_/rsrc/1237722991136/developers/qemu/Qemu%20PD%20booting.png%3Fheight=263&width=420)](qemu/Qemu%20PD%20booting.png%3Fattredirects=0)

At the end of the KEXTs decompression phase, the CPU FSB clock and ration should be adjusted by the voodoo kernel.

[![](../_/rsrc/1237723452364/developers/qemu/Qemu%20PD%20booting2.png%3Fheight=255&width=420)](qemu/Qemu%20PD%20booting2.png%3Fattredirects=0)
After the KEXTs decompression phase, you should see the kernel booting (notice the network adapter supported).

[![](../_/rsrc/1237723486088/developers/qemu/Qemu%20PD%20booting3.png%3Fheight=331&width=420)](qemu/Qemu%20PD%20booting3.png%3Fattredirects=0)
Then depending your settings, a login prompt or X should be waiting for you.

It is necessary to launch X11 manually by issuing <span style="font-size:small">/usr/X11R6/bin/startx</span>.




[![](../_/rsrc/1239274247269/developers/qemu/pd-qemu-mp.jpg%3Fheight=310&width=420)](qemu/pd-qemu-mp.jpg%3Fattredirects=0)

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

<span style="text-decoration:underline">Credits:</span> Partial network support already existed, thanks to "hingwah" who helped and pointed its existence to us.

<div style="display:block">
As said in [3.7.3 Using the user mode network stack](http://www.qemu.org/qemu-doc.html#SEC3) QEMU documentation ("*The DHCP server assign addresses to the hosts starting from 10.0.2.15.*"), the interface is well auto-assigned (notes: KernelEventMonitor (confid_plugins) has been added and seems to be responsible of the client DHCP capability) as the route to the virtual available gateway (a firewall / dhcp server).

<div style="display:block">
### Requirements
<div style="display:block">
Append -net user if it is not already there to the qemu command line:
<div style="display:block">
<span style="font-size:small">[...] -net nic,model={i82551|i82557b|rtl8139} -no-kvm-irqchip -net user [...]</span>
<div style="display:block">

<div style="display:block">
<span style="text-decoration:line-through">Be prepare to ping the gateway continuously, it's a workaround.</span>
<div style="display:block">
As user inp reported on #puredarwin, adding '-no-kvm-irqchip' to the qemu call solves this issue with the rtl8139 driver.
<div style="display:block">

<div style="display:block">
Of course, it's mandatory to have a Kernel EXTension matching its respective device.
<div style="display:block">
E.g. below with the realtek kext matching its respective virtual RTL8139 device in QEMU:
<div style="display:block">

<div style="display:block">
[![](../_/rsrc/1246698469464/developers/qemu/guest%20ip%20auto%20set.png%3Fheight=223&width=420)](qemu/guest%20ip%20auto%20set.png%3Fattredirects=0)
### DHCP (IPv4)
<div style="display:block">
An example of a "correct" configuration, where everything has been provided automatically (KernelEventMonitor) via DHCP.
<div style="display:block">
[![](../_/rsrc/1246830041720/developers/qemu/qemunusermodenetworkstacksupport.png)](qemu/qemunusermodenetworkstacksupport.png%3Fattredirects=0)
<div style="display:block">
<div style="display:block">
**
**
<div style="display:block">
**What expected:**
<div style="display:block">
10.0.2.2 should respond to ping (gateway firewall/dhcpd).
<div style="display:block">
10.0.2.2 should be the default route.
<div style="display:block">
10.0.2.3 should answer to DNS query.
<div style="display:block">
10.0.2.4 should answer to SMB (if available).
<div style="display:block">
10.0.2.15 is where starts the first guest ip address.
<div style="display:block">

<div style="display:block">
**What is well known:**
<div style="display:block">
<span style="text-decoration:line-through">It seems that network hangs easily if the gateway is not pinged when network operations are needed.</span> As user inp reported on #puredarwin, adding '-no-kvm-irqchip' to the qemu call solves this issue with the rtl8139 driver.
### Ping workaround
<span style="text-decoration:line-through">ping the gateway (10.0.2.2) from the guest side (PureDarwin) seems necessary at this time.</span>
<span style="text-decoration:line-through">If it is not the done, the connection simply hangs or fails to establish sometimes.</span>
As user inp reported on #puredarwin, adding '-no-kvm-irqchip' to the qemu call solves this issue with the rtl8139 driver.

<div style="display:block">
Depending the ping interval (-i) against the virtual gateway, the bandwith varies (a pseudo bandwith control state; qos?).
<div style="display:block">
Below is an example across the time, where the interval took the no value, then 0.9, 0.5, 0.1 and 0 (This example was done downloading nmap).
<div style="display:block">

<div style="display:block">
[![](../_/rsrc/1246836722256/developers/qemu/picbd.png)](qemu/picbd.png%3Fattredirects=0)
### Miscellaneous
#### Guest fingerprint (10.0.2.15)
The famous Fyodor `[nmap](http://nmap.org/)' basic fingerprint result against 10.0.2.15 (guest: en0) looks like (X running without --no-listen tcp as shown).

[![](../_/rsrc/1246919277534/developers/qemu/nmapinqemuusermodenetstack.png)](qemu/nmapinqemuusermodenetstack.png%3Fattredirects=0)

#### Gateway fingerprint (10.0.2.2)
Interesting to see what looks like from nmap point of view the virtual gateway (user mode network stack):


[![](../_/rsrc/1246919580801/developers/qemu/nmapinqemuusermodethegw.png)](qemu/nmapinqemuusermodethegw.png%3Fattredirects=0)
#### DNS server fingerprint (10.0.2.3)

..

[![](../_/rsrc/1246920031759/developers/qemu/nmapinqemuusermodednsd.png)](qemu/nmapinqemuusermodednsd.png%3Fattredirects=0)

QEMU options
------------

This is another non exhaustive list of (reported to work) options available. Some part also needs investigations and feedback.
### Standard options
<span style="font-family:courier new,monospace"><span style="font-size:small">-M machine      select emulated machine (-M ? for list) </span></span><span style="font-weight:bold"><span style="color:rgb(255,0,0)">Need investigations.</span></span> (could be interesting to see how it is close or not the reality when it is possible to compare the cases)
<span style="font-family:courier new,monospace"><span style="font-size:small">-cpu cpu        select CPU (-cpu ? for list) </span></span><span style="color:rgb(255,0,0);font-weight:bold">Need investigations.</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">-fda/-fdb file  use 'file' as floppy disk 0/1 image</span></span> <span style="font-weight:bold"><span style="color:rgb(61,133,198)">No thanks.</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">-hda/-hdb file  use 'file' as IDE hard disk 0/1 image</span></span> <span style="font-weight:bold"><span style="color:rgb(56,118,29)">Reported to work with a iso, dmg, vmdk (convert or not).</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-hdc/-hdd file  use 'file' as IDE hard disk 2/3 image</span></span> <span style="color:rgb(255,0,0);font-weight:bold">Need investigations.</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-cdrom file     use 'file' as IDE cdrom image (cdrom is ide1 master)</span></span> <span style="color:rgb(56,118,29);font-weight:bold">Reported to work with a iso, dmg, vmdk (convert or not).</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">-m megs         set virtual RAM size to megs MB [default=128]<span style="font-family:Arial;font-size:13px"><span style="font-weight:bold"><span style="color:rgb(56,118,29)">384 and 512 are ok.</span></span></span></span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">-smp n          set the number of CPUs to 'n' [default=1]</span></span> <span style="color:rgb(56,118,29);font-weight:bold">Work well with default value or 1.<span style="color:rgb(0,0,0);font-weight:normal"> <span style="color:rgb(255,0,0);font-weight:bold">Need investigations</span> ([Kernel panic with voodoo kernel](qemu/qemusmp2voodookernelpanic.png%3Fattredirects=0) even with reflecting modifications (<span style="font-family:courier new,monospace"><span style="font-size:small">cpus=2</span></span>) in /<span style="font-style:italic">Library/Preferences/SystemConfiguration/com.apple.Boot.plist</span>)</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">-k language     use keyboard layout (for example "fr" for French)</span></span> <span style="color:rgb(255,0,0);font-weight:bold">Need investigations, not working.</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">-vga [std|cirrus|vmware] </span></span><span style="color:rgb(56,118,29);font-weight:bold"><span style="color:rgb(255,0,0)">Need investigations. </span>Seems to works fine without -vga .... provided (default settings cyrus?). </span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-usb            enable the USB driver (will be the default soon)</span></span> <span style="color:rgb(255,0,0);font-weight:bold">Need investigations.</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">-usbdevice name add the host or guest USB device 'name'</span></span> <span style="color:rgb(255,0,0);font-weight:bold">Need investigations.</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">-name string    set the name of the guest </span></span><span style="color:rgb(56,118,29);font-weight:bold">PureDarwin.</span>

<span style="font-family:courier new,monospace"><span style="font-size:small">-uuid %08x-%04x-%04x-%04x-%012x specify machine</span></span> <span style="color:rgb(255,0,0);font-weight:bold">Need investigations, UUID C0FFEEC0-FFEE-C0FF-EEC0-FFEEC0FFEEC0 has no effect.</span>

### Network options
According to the `man', "<span style="font-style:italic">The NIC is an ne2k_pci by default on the PC target</span>", but some other valid values are: 
<span style="color:rgb(56,118,29)">i82551</span>, <span style="color:rgb(56,118,29)">i82557b</span>, i82559er, ne2k_pci, ne2k_isa, pcnet, rtl8139, e1000, smc91c111, lance and mcf_fec.


<span style="font-family:courier new,monospace"><span style="font-size:small">-net nic[,vlan=n][,macaddr=addr][,model=type]</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">                create a new Network Interface Card and connect it to VLAN 'n' <span style="font-family:Arial;font-size:13px"><span style="font-weight:bold"><span style="color:rgb(56,118,29)">-net nic,model=rtl8139 is enabled by PureFoundation. <span style="color:rgb(255,0,0)">Need investigations.</span></span></span></span></span></span>


<span style="font-family:courier new,monospace"><span style="font-size:small">-boot [a|c|d|n] boot on floppy (a), hard disk (c), CD-ROM (d), or network (n)</span></span><span style="font-weight:bold"><span style="color:rgb(56,118,29)"> "d" with the corresponding target is functional.</span></span>
**<span style="color:rgb(0,0,0);font-weight:normal"></span>**
<div style="display:block">
-redir to test. <span style="font-family:Arial,monospace;font-size:13px;color:rgb(255,0,0);font-weight:bold">Need investigations</span>
<span style="font-family:Arial,monospace;font-size:13px;color:rgb(255,0,0);font-weight:bold"><span style="color:rgb(0,0,0);font-family:monospace,Verdana,Tahoma,Helvetica,Geneva,sans-serif;font-size:12px;font-weight:normal">-tftp prefix</span></span>
-smb
-macaddr addr
-nics

<span style="font-family:Arial,Verdana,Tahoma,Helvetica,Geneva,sans-serif"></span>


<span style="color:rgb(56,118,29);font-weight:bold">
</span>
The option "-net nic,model={i82551|i82557b}" seems to match with [AppletIntel8255x](http://src.macosforge.org/Roots/9A581/AppleIntel8255x.root.tar.gz) from DarwinBuild:


[![](../_/rsrc/1241395561706/developers/qemu/qemu%20net%208255x%20bis.png%3Fheight=41&width=200)](qemu/qemu%20net%208255x%20bis.png%3Fattredirects=0)


[![](../_/rsrc/1241395552721/developers/qemu/qemu%20net%208255x.png%3Fheight=126&width=420)](qemu/qemu%20net%208255x.png%3Fattredirects=0)
### Live options
Press ctrl+alt+2 to switch to QEMU monitor:

[![](../_/rsrc/1242469974108/developers/qemu/qemu%20ctrl%20alt%202.png%3Fheight=279&width=420)](qemu/qemu%20ctrl%20alt%202.png%3Fattredirects=0)

[![](../_/rsrc/1242469999869/developers/qemu/qemu%20ctrl%20alt%202%20help.png%3Fheight=283&width=420)](qemu/qemu%20ctrl%20alt%202%20help.png%3Fattredirects=0)


Press ctrl+alt+3 to switch to serial0 console:

[![](../_/rsrc/1242470018471/developers/qemu/qemu%20ctrl%20alt%203.png%3Fheight=275&width=420)](qemu/qemu%20ctrl%20alt%203.png%3Fattredirects=0)

Press ctrl+alt+4 to switch to parallel0 console:

[![](../_/rsrc/1242470037379/developers/qemu/qemu%20ctrl%20alt%204.png%3Fheight=283&width=420)](qemu/qemu%20ctrl%20alt%204.png%3Fattredirects=0)

<span style="font-size:18px;font-weight:bold">Patches to run stock XNU on QEMU</span>

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

<span style="font-family:courier new,monospace">The following are my tests on Ubuntu 12/2011; probono</span>
<span style="font-family:courier new,monospace"># qemu: pci_add_option_rom: failed to find romfile "pxe-rtl8139.bin"</span>
<span style="font-family:courier new,monospace"># can be solved with</span>
<span style="font-family:courier new,monospace">sudo apt-get install kvm-pxe</span>
<span style="font-family:courier new,monospace"># Launch qemu as root and with -redir tcp:22::22 for SSH access</span>
<span style="font-family:courier new,monospace">sudo qemu -hda /dev/sdc -net nic,model=rtl8139 -no-kvm-irqchip -net user -redir tcp:22::22</span>
<span style="font-family:courier new,monospace"># Inside qemu</span>
<span style="font-family:courier new,monospace">ifconfig en2 10.0.2.15 up</span>
<span style="font-family:courier new,monospace">ping 10.0.2.2 # works (which is the gateway provided by qemu)</span>
<span style="font-family:courier new,monospace"># Create /etc/rc.local with the following content to</span>
<span style="font-family:courier new,monospace"># bring en2 up automatically at boot time </span>
<span style="font-family:courier new,monospace">#!/bin/bash</span>
<span style="font-family:courier new,monospace">ifconfig en2 10.0.2.15 up</span>
<span style="font-family:courier new,monospace">sudo route add 0.0.0.0 10.0.2.2</span>
<span style="font-family:courier new,monospace"># Headless SSH server inside qemu</span>
<span style="font-family:courier new,monospace">sudo qemu -hda /dev/sdc -net nic,model=rtl8139 -no-kvm-irqchip -net user -redir tcp:22::22 -vnc :1 -redir tcp:80::80</span>
<span style="font-family:courier new,monospace"># Works :-)</span>
<span style="font-family:courier new,monospace"># The only thing that does not work yet is DNS</span>
<span style="font-family:courier new,monospace"># scutil --dns # resolver #1 is empty, which is a problem -- very ugly workaround:
</span>echo 'nameserver 10.0.2.3' &gt; /etc/resolver/com
echo 'nameserver 10.0.2.3' &gt; /etc/resolver/org
echo 'nameserver 10.0.2.3' &gt; /etc/resolver/net
echo 'nameserver 10.0.2.3' &gt; /etc/resolver/de
echo 'nameserver 10.0.2.3' &gt; /etc/resolver/edu
Rafael's networking information 01/2012
---------------------------------------
Our reader Rafael writes:

<span style="border-collapse:collapse;color:rgb(34,34,34)">For the network problem it's just a matter of patching kvm module and you can use full acceleration, the patch is know (qemu dev don't want it because it's specific to qemu userland software and they want kvm module to remain compatible with other userland software - which ones? ):
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
--&gt; but this last is derived from linux so it lacks debug specific part but I think this is the more interesting given you can redistribute it.
If you use recent xnu kernel you also need to patch qemu (or use kernel patched) to tell you use apic version 14 ( qemu dev don't want ton upgrade apic version as they don't have too to run linux or windows) or you will hit an assert/kp from kernel.
Open hw/apic.c from qemu source:
In this function:
static uint32_t apic_mem_readl(void *opaque, target_phys_addr_t addr)
Change:
        val = 0x11 | ((APIC_LVT_NB - 1) &lt;&lt; 16); /* version 0x11 */
to
        val = 0x14 | ((APIC_LVT_NB - 1) &lt;&lt; 16); /* version 0x14 */ 
</span>
Thanks Rafael for sharing this information, which is not easy to find. <span style="border-collapse:collapse;color:rgb(34,34,34);font-family:arial,sans-serif">kvm is doing really great these days.</span>
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
