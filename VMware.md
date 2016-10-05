VMware
======

<div style="margin:5px 10px;display:inline;float:right">
<span>    </span>[![](../_/rsrc/1247515808697/developers/vmware/vmware.gif)](vmware/vmware.gif%3Fattredirects=0)
Many [VMware](http://www.vmware.com/) products are now able to run a Darwin system (e.g., PureDarwin).
From *VMware Fusion 2.0* (Mac OS X) to *VMware Player 2.5* (free download for Windows and Linux) via *VMware ESX* and later versions, PureDarwin should boot without any troubles.

**A more precise list will be constituted if respective [feedback](../todo.html) is received.
**
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:357px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Running PureDarwin in VMware](vmware.html#TOC-Running-PureDarwin-in-VMware)
    1.  [**1.1** Requirements](vmware.html#TOC-Requirements)
    2.  [**1.2** Using VMware other than Fusion ](vmware.html#TOC-Using-VMware-other-than-Fusion-)
2.  [**2** Settings](vmware.html#TOC-Settings)
    1.  [**2.1** VMware settings](vmware.html#TOC-VMware-settings)
        1.  [**2.1.1** Enable the built-in VNC server](vmware.html#TOC-Enable-the-built-in-VNC-server)
    2.  [**2.2** Boot arguments](vmware.html#TOC-Boot-arguments)
    3.  [**2.3** Faking guest OS detection](vmware.html#TOC-Faking-guest-OS-detection)
3.  [**3** Devices](vmware.html#TOC-Devices)
4.  [**4** Boot](vmware.html#TOC-Boot)
    1.  [**4.1** VMware Fusion BIOS](vmware.html#TOC-VMware-Fusion-BIOS)
    2.  [**4.2** Bootloader](vmware.html#TOC-Bootloader)
        1.  [**4.2.1** darwin.iso](vmware.html#TOC-darwin.iso)
    3.  [**4.3** Single user mode](vmware.html#TOC-Single-user-mode)
    4.  [**4.4** Multi user mode](vmware.html#TOC-Multi-user-mode)
5.  [**5** Network](vmware.html#TOC-Network)
    1.  [**5.1** Emulated NICs](vmware.html#TOC-Emulated-NICs)
        1.  [**5.1.1** e1000](vmware.html#TOC-e1000)
    2.  [**5.2** Status](vmware.html#TOC-Status)
6.  [**6** e1000 support quest](vmware.html#TOC-e1000-support-quest)
    1.  [**6.1** Notions](vmware.html#TOC-Notions)
        1.  [**6.1.1** Driver and IOPCIDevice](vmware.html#TOC-Driver-and-IOPCIDevice)
        2.  [**6.1.2** PCI matching summarization](vmware.html#TOC-PCI-matching-summarization)
    2.  [**6.2** Vendor and Device IDs](vmware.html#TOC-Vendor-and-Device-IDs)
        1.  [**6.2.1** Vendor ID (intel def.)](vmware.html#TOC-Vendor-ID-intel-def.-)
        2.  [**6.2.2** Device ID (Intel def.)](vmware.html#TOC-Device-ID-Intel-def.-)
        3.  [**6.2.3** PCI configuration space registers ](vmware.html#TOC-PCI-configuration-space-registers-)
        4.  [**6.2.4** PCI matching dictionary](vmware.html#TOC-PCI-matching-dictionary)
    3.  [**6.3** Real KEXTs](vmware.html#TOC-Real-KEXTs)
        1.  [**6.3.1** w/o KEXT](vmware.html#TOC-w-o-KEXT)
        2.  [**6.3.2** AppleIntel8255x](vmware.html#TOC-AppleIntel8255x)
        3.  [**6.3.3** Intel82566MM](vmware.html#TOC-Intel82566MM)
        4.  [**6.3.4** AppleIntel8254XEthernet](vmware.html#TOC-AppleIntel8254XEthernet)
    4.  [**6.4** a KEXT pseudo-life](vmware.html#TOC-a-KEXT-pseudo-life)
    5.  [**6.5** Host NIC](vmware.html#TOC-Host-NIC)
7.  [**7** Troubleshooting](vmware.html#TOC-Troubleshooting)
    1.  [**7.1** On read-only medium](vmware.html#TOC-On-read-only-medium)
    2.  [**7.2** Random log](vmware.html#TOC-Random-log)
8.  [**8** Resources](vmware.html#TOC-Resources)

Running PureDarwin in VMware
----------------------------
It is very easy to run PureDarwin with VMware.
### Requirements
a VMware product
a PureDarwin system (can be downloaded or produced)
-   a ready-to-run .vmwarevm (read-write) or .vmdk
-   a PureDarwin ISO, and either use it directly (read-only)
    This ISO can be converted into a VMware disk image (.vmdk) file using a little conversion tool called `qemu-img'.
    The resulting disk image will be read-write, and can be mounted by double-clicking so that you can change its contents from the host system:
    <span style="font-family:courier new,monospace;font-size:small;white-space:pre">qemu-img convert -O vmdk PureDarwin.iso PureDarwin.vmdk</span>

Launch VMware Fusion 2.0 or later and create a new machine based on the ISO or .vmdk - VMware Fusion will automatically recognize it as "Mac OS X Server" and configure the virtual machine accordingly. You do not need to change any settings. 
### Using VMware other than Fusion 
Two KEXTs appeard useful for VMware release(s) other than Fusion:

-   LegacyAppleIntelPIIXATA
-   NullCPUPowerManagement
They can be found in VMware-Drivers-OpenSource.zip. See [Downloads](../downloads.html) page.

Settings
--------
### VMware settings
#### Enable the built-in VNC server
Add these lines in the .vmx file:

<span style="font-family:courier new,monospace"><span style="font-size:small">RemoteDisplay.vnc.port = "5900"
RemoteDisplay.vnc.enabled = "TRUE"
# optional password:
RemoteDisplay.vnc.password = "password"
</span></span>

Then simply connect your favorite VNC client to localhost.
### Boot arguments
(please add text)
### Faking guest OS detection
We need to fake VMware guest OS detection in order to avoid error message "*The guest operating system is not Mac OS X Server*" (implicitly to simply boot).

[![](../_/rsrc/1247429745836/developers/vmware/VMware%20guest%20os%20detection.png)](vmware/VMware%20guest%20os%20detection.png%3Fattredirects=0)

VMware guest OS detection is trivial, and so the way to avoid it:

 `touch "/Volumes/PureDarwin/System/Library/CoreServices/ServerVersion.plist"`<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="text-decoration:underline">Note:</span> This tweak should/could be deprecated by time.

Devices
-------
VMware Fusion 2.0.5
**Host:** Mac OS X 9.7.0
**Guest:** PureDarwin (9J61)

Here's a vendor/device id list retrieved from the VMware guest OS:


<span style="font-family:courier new,monospace;font-size:small">"0x8086","0x7191","Intel Corporation","82443BX/ZX","440BX/ZX AGPset PCI-to-PCI bridge"</span>
<span style="font-size:small">"0x8086","0x7110","Intel Corporation","82371AB/EB/MB","PIIX4/4E/4M ISBridgeA "</span>
<span style="font-size:small">"0x8086","0x7113","Intel Corporation","82371AB/EB/MB","PIIX4/4E/4M Power Management Controller"</span>
<span style="font-size:small">"0x8086","0x7111","Intel Corporation","82371AB/EB/MB","PIIX4/4E/4M IDE Controller"</span>
<span style="font-size:small">"0x15ad","0x0790","",""</span>
<span style="font-size:small">[...] &lt;- + x 30</span>
<span style="font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:13px"></span></span>
"0x15ad","0x0790","",""

<span style="font-size:small">"0x8086","0x7112","Intel Corporation","82371AB/EB/MB","PIIX4/4E/4M USB Interface"</span>
<span style="font-size:small">"0x8086","0x100F","Intel Corporation","82545EM","Gigabit Ethernet Controller (copper)"</span>
<span style="font-size:small">"0x15AD","0x0770","VMware Inc.","n/a","Standard Enhanced PCI to USB Host Controller"</span>
<span style="font-size:small">"0x1274","0x1371","Ensoniq","ES 1371","AudioPCI"</span>
<span style="font-size:small">"0x1000","0x0030","LSI Logic","LSI53C1020/1030","PCI-X to Ultra320 SCSI Controller"</span>
<span style="font-size:small">"0x15AD","0x0405","VMware Inc.","9500MGS","NVIDIA"</span>
<span style="font-size:small">"0x15AD","0x0740","VMware Inc.","0X0880","VMWare VMCI Bus Device"</span>
<span style="font-size:small">"0x8086","0x7190","Intel Corporation","82443BX/ZX","440BX/ZX AGPset Host Bridge"</span>

Boot
----
### VMware Fusion BIOS
VMware Fusion comes with a combo PhoenixBIOS/VMware BIOS.

[![](../_/rsrc/1247951753818/developers/vmware/VMware%20fusion%20bios%20boot.png%3Fheight=291&width=420)](vmware/VMware%20fusion%20bios%20boot.png%3Fattredirects=0)

[![](../_/rsrc/1247951748803/developers/vmware/VMware%20fusion%20bios.png%3Fheight=371&width=420)](vmware/VMware%20fusion%20bios.png%3Fattredirects=0)

[![](../_/rsrc/1247951743546/developers/vmware/VMware%20fusion%20bios%202.png%3Fheight=371&width=420)](vmware/VMware%20fusion%20bios%202.png%3Fattredirects=0)
### Bootloader
<span style="font-family:Lucida Grande,Verdana,sans-serif;font-size:12px">VMware uses darwin.iso (VMware Tools) which contains the DFE bootloader (Stage 2 boot file &lt; 128K) to provide a bootloader.</span>
#### darwin.iso
<span style="font-size:12px"></span>
<span style="font-size:small">Located in /Library/Application Support/VMware Fusion/isoimages/original/darwin.iso</span>
<span style="font-size:small">ISO 9660 CD-ROM filesystem data 'CD' (bootable)</span>
<span style="font-size:small">
</span>
<span style="font-size:small">pdisk reports:</span>
<span style="font-size:small">Partition map (with 512 byte blocks) on 'original/darwin.iso'</span>
<span style="font-size:small"> #:                type name                  length   base   ( size )</span>
<span style="font-size:small"> 1: Apple_partition_map Apple                     63 @ 1     </span>
<span style="font-size:small"> 2:           Apple_HFS DiscRecording 3.2.0f2   6940 @ 244    (  3.4M)</span>
<span style="font-size:small">
</span>
<span style="font-size:small">Device block size=2048, Number of Blocks=3339059200 (6.2T)</span>
<span style="font-size:small">DeviceType=0x0, DeviceId=0x0</span>
<span style="font-size:small">
</span>
<span style="font-size:small">The DFE bootloader:</span>
<span style="font-size:small">-r--r--r--@ 1 201  wheel  63520 Jun 23 00:20 /Volumes/VMware Tools/.hiddendir/boot (dfeâ€™)</span>
<span style="font-size:small">In order to compare the siwe, Chameleon takes 295328B and the latest DFE 63648B.</span>
<span style="font-size:small">
</span>
<span style="font-size:small">Facing the bootloader size limitation:</span>
[<span style="font-size:small">![](../_/rsrc/1248034226480/developers/vmware/VMware%20booter%20size%20limitation.png)</span>](vmware/VMware%20booter%20size%20limitation.png%3Fattredirects=0)
<span style="font-size:small">
</span>
<span style="font-size:small">It is possible to alter the content of darwin.iso, but the package needs to be signed again.</span>
<span style="font-size:small">
</span>
<span style="font-size:small">hdiutil -readwrite attach darwin.iso</span>
<span style="font-size:small">h</span><span style="font-size:small">diutil eject..</span>
<span style="font-size:small">openssl genrsa -out tools-priv.pem 2048
openssl rsa -in tools-priv.pem -pubout -out tools-key.pub
openssl dgst -sha1 -sign tools-priv.pem &lt; darwin.iso &gt; darwin.iso.sig
for A in *.iso ; do openssl dgst -sha1 -sign tools-priv.pem &lt; $A &gt; $A.sig ; done</span>

### Single user mode
It boots.

![](../_/rsrc/1218489175310/developers/vmware/VMware%20single%20user-mode.png%3Fheight=150&width=200)
### Multi user mode
It boots but fails because of read-only medium when a connected CD/DVD drive is configured to use a disk image (ISO).
It works when a VMware disk image (.vmdk) is used since read-write is enabled (and functional) by default.
Network
-------
### Emulated NICs
<span style="font-weight:bold"><span style="font-weight:normal">VMware seems to provide 3 emulated NIC:</span></span>
-   **e1000**
-   **VMware NIC - vmxnet
    **High performance (Gigabit), need VMware drivers in the guest.
    OK for production.
-   **VLANCE (aka AMD PCNET-32)
    **Lower perf, high CPU load, no kext available, problems solved. Update November 2012: A driver is in the works at <https://code.google.com/p/pcnet32-driver-for-puredarwin/> - **information about this driver still needs to be worked into this page**
#### e1000
VMware emulates an Intel e1000 network card.
"e1000" is apparently a generic term for a <span style="font-weight:bold">series</span> of similar but different chips.
<http://www.intel.com/design/network/products/lan/controllers/82545.htm>

<span style="font-family:courier new,monospace;font-size:x-small"></span>
<span style="font-family:Arial,Verdana,sans-serif;font-size:16px;font-weight:bold"><span style="font-size:13px;font-weight:normal">From Intel:
<span style="font-size:small">Stepping   Vendor ID   Device ID Description 
82547EI-A0 8086h       1019h     Copper </span></span></span>
<span style="font-family:Arial,Verdana,sans-serif;font-size:16px;font-weight:bold"><span style="font-size:13px;font-weight:normal"><span style="font-size:small">82547EI-A1 8086h       1019h     Copper 
82547EI-B0 8086h       1019h     Copper 
82547EI-B0 8086h       101Ah     Mobile 
82547GI-B0 8086h       1019h     Copper 
82546EB-A1 8086h       1010h     Copper; Dual Port MAC Default 
82546EB-A1 8086h       1012h     Fiber; Dual Port 
82546EB-A1 8086h       101Dh     Copper; Quad Port 
82546GB-B0 8086h       1079h     Copper; Dual Port </span></span></span>
<span style="font-family:Arial,Verdana,sans-serif;font-size:16px;font-weight:bold"><span style="font-size:13px;font-weight:normal"><span style="font-size:small">82546GB-B0 8086h       107Ah     Fiber; Dual Port 
82546GB-B0 8086h       107Bh     SerDes; Dual Port </span></span></span>
<span style="font-family:Arial,Verdana,sans-serif;font-size:16px;font-weight:bold"><span style="font-size:13px;font-weight:normal">**<span style="font-size:small">82545EM-A  8086h<span style="font-weight:normal">      <span style="font-weight:bold"> 100Fh     Copper </span></span></span>**</span></span>
<span style="font-family:Arial,Verdana,sans-serif;font-size:16px;font-weight:bold"><span style="font-size:13px;font-weight:normal"><span style="font-size:small">82545EM-A  8086h       1011h     Fiber</span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82545GM-B  8086h       1026h     Copper MAC Default </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82545GM-B  8086h       1027h     Fiber </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82545GM-B  8086h       1028h     SerDes</span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82544EI-A4 8086h       1107h     Copper MAC Default </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82544GC-A4 8086h       1112h     Copper MAC Default </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82541EI-A0 8086h       1013h     Cooper MAC Default </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82541EI-A0 8086h       1013h     Cooper MAC Default </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82541EI-B0 8086h       1013h     Cooper MAC Default </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82541EI-B0 8086h       1018h     Mobile</span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82541GI-B1 8086h       1076h     Cooper </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82541GI-B1 8086h       1077h     Mobile </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82541PI-C0 8086h       1076h     Cooper </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82541ER-C0 8086h       1078h     Cooper </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82540EP-A  8086h       1017      Desktop </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82540EP-A  8086h       1016      Mobile </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82540EM-A  8086h       100E      Desktop </span></span></span>
<span style="font-weight:bold"><span style="font-weight:normal"><span style="font-size:small">82540EM-A  8086h       1015      Mobile </span></span></span>

<span style="font-weight:bold"><span style="font-weight:normal"></span></span>
### Status

The VMware virtual device chipset seems to correspond to the Intel<span style="font-family:arial,Verdana,sans-serif">82545EM (Copper)</span>

-   **Vendor ID:** 0x8086
-   **Primary device ID:** 0x100F


Mac OS X contains a driver (AppleIntel8254XEthernet) for the chip emulated by VMware which "should match and work".
**But** this driver is <span style="text-decoration:underline">not available</span> for Darwin yet, neither in source nor binary form.

We found also two KEXTs close (but not enough "by nature") to the VMware <span style="font-family:arial,Verdana,sans-serif">82545EM virtual device:</span>
-   AppleIntel8255x (built from the [Darwinbuild](darwinbuild.html) project)
-   [82566mm-osx-driver](http://code.google.com/p/82566mm-osx-driver/) (an OpenSource one)
Both of the two KEXTs personality file (Info.plist) can be modified to match the VMware virtual device in order to be (kext)loaded at boot.
**But no interface (e.g., en0) is affected...**


The <span style="font-family:arial,Verdana,sans-serif">82566MM<span style="font-family:Arial,Verdana,sans-serif"> driver currently only supports<span style="border-collapse:separate;font-family:arial"> chips (e.g., 82566MM) which appear to be slightly different to the 82545EM that VMware apparently emulates.</span></span></span>
e1000 support quest
-------------------
### Notions
#### Driver and IOPCIDevice
PCI stands for Peripheral Component Interconnect.

A driver for a PCI Ethernet controller inherits from IOEthernetController but uses an instance of IOPCIDevice class (in order to connect to the PCI bus).
IOPCIDevice is a basic nub class representing any PCI device in any PCI slot.

<span style="font-size:small">Ethernet driver &lt;-&gt; IOPCIDevice &lt;-&gt; IOPCIBridge &lt;-&gt; IOPlatformDevice &lt;-&gt; ...</span>
#### PCI matching summarization
A driver can control a device on a PCI bus.
A driver announces this fact by including a "*personality*" in its plist file.
This personality includes IOProviderClass=IOPCIDevice (Key=Value).
IOPCIDevice defines 2 sets of keys that a driver can use for matching:
-   a key based on standard PCI registers
-   a key based on Open Firmware (probably related to PPC only)
A PCI device driver can use one type of key or both of them (if personalities are disjoint)
### Vendor and Device IDs
#### Vendor ID (intel def.)
<span style="font-family:arial,sans-serif;font-size:small">This uniquely identifies all Intel PCI products.
This field may be auto-loaded from the EEPROM at power on or upon the assertion of PCI_RST#.
A value of 0x8086 is the default for this field upon power up if the EEPROM does not respond or is not programmed. </span>
<span style="font-family:arial,sans-serif;font-size:small;font-weight:bold"></span>
#### Device ID (Intel def.)
<span style="font-weight:normal">This uniquely identifies the Ethernet controller.
This field may be autoloaded from the EEPROM at power on or upon the assertion of RST#.
The default value for this field is used upon power up if the EEPROM does not respond or is not programmed.</span>
<span style="font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:13px"></span></span>
#### PCI configuration space registers 

-   vendor and device ID (offsets 0x00 and 0x002)
-   subsystem vendor and device ID (offsets 0x2C and 0x2E)
-   class code (offset 0x09)
-   <span style="color:rgb(153,153,153)">revision ID (not available in property matching)</span>
-   <span style="color:rgb(153,153,153)">header type (not available in property matching)</span>
#### PCI matching dictionary
Value for a key can be a single register value or a list (space separator).
Register values are little-endian hexa strings (device ID first then vendor ID).
A mask can be included (only a part of the value is compared), bits set to 0 are ignored by the mask 
-   IOPCIMatch
    matches against primary vendor/device ID registers (checked first)
    or
    matches aganst the subsystem vendor/device ID
-   IOPCIPrimaryMatch
    matches against primary vendor/device ID registers
-   IOPCISecondaryMatch
    matches against the subsystem vendor/device ID registers
-   IOPCIClassMatch
    matches against the class code register
Examples of corresponding key/value based on vendor and device id which can be expected in *Info.plist*:

Vendor ID: 0x8086
Primary device ID: 0x100F
<span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;IOPCIMatch&lt;/key&gt;</span>
<span style="font-family:courier new,monospace;font-size:small"><span style="background-color:rgb(255,255,255)">&lt;string&gt;</span><span style="background-color:rgb(159,197,232)">0x100F8086</span><span style="background-color:rgb(255,255,255)">&lt;/string&gt;</span></span>


Vendor ID: 0x8086
Primary device ID: 0x1000 or 0x100F

<span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;IOPCIMatch&lt;/key&gt;</span>
<span style="font-family:courier new,monospace;font-size:small"><span style="background-color:rgb(255,255,255)">&lt;string&gt;</span><span style="background-color:rgb(159,197,232)">0x10008086 0x100F8086&lt;/string&gt;</span></span>
<span style="font-size:small">
</span>

Vendor ID: 0x8086
Primary device ID: 0x1000..0x10FF (first two digits subsystem IDs are not checked)

<span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;IOPCIPrimaryMatch&lt;/key&gt;</span>
<span style="font-family:courier new,monospace;font-size:small"><span style="background-color:rgb(255,255,255)">&lt;string&gt;</span><span style="background-color:rgb(159,197,232)">0x10008086&amp;0xFF00FFFF</span><span style="background-color:rgb(255,255,255)">&lt;/string&gt;</span></span>

Class code for ethernet controller (0x0200 (in fact 4bytes, last byte ignored))
<span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;IOPCIClassMatch&lt;/key&gt;</span>
<span style="font-family:courier new,monospace;font-size:small"><span style="background-color:rgb(255,255,255)">&lt;string&gt;</span><span style="background-color:rgb(180,167,214)">0x02000000&amp;0xffff0000</span><span style="background-color:rgb(255,255,255)">&lt;/string&gt;</span></span>
<span style="font-size:small">
</span>
<span style="font-size:small">Consequently, the <span style="font-family:Arial,Verdana,sans-serif;font-size:13px">PCI ID associated to the 82545EM chipset should be "</span>100F:8086<span style="font-family:Arial,Verdana,sans-serif;font-size:13px">"</span></span>
Which is confirmed on
-   **FreeBSD:** <span style="font-style:italic"><span style="font-size:small">100F8086</span> -&gt; 82545EM Gigabit ethernet controller Coper</span>
-   **GNU/Linux:** <span style="font-size:x-small"><span style="font-size:small">*pci 8086:100F kmod-e1000 *</span><span style="font-size:13px">*corresponds to e1000.ko*</span></span>
-   **Intel:** From the "*Intel PCI/PCI-X Family of Gigabit Ethernet Controllers Software Developerâ€™s Manual*", 
    A list of pair model / device id is available in the Intel spec, which confirm the result above ( "IOModel" = "82545EM Copper" )
-   **e1000 from sourceforge:** *82540EP/EM, 82541xx, 82544GC/EI, 82545GM/EM, 82546GB/EB, and 82547xx*
    <http://kent.dl.sourceforge.net/sourceforge/e1000/OpenSDM_8254x-37.pdf>
-   <http://www.pcidatabase.com/vendor_details.php?id=1302> also.
<span style="font-size:small"><span style="font-size:x-small"><span style="font-size:13px"><span style="text-decoration:underline">Note:</span> "When running VMware ESX Server 3.0.0, you can experience a kernel panic if you use Intel e1000 network adapters with any of the following PCI IDs: </span><span style="font-size:13px">**0x100F**[...]" - <http://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=2221></span></span></span>
### Real KEXTs
<span style="font-size:small"><span style="font-size:x-small"><span style="font-size:13px"></span></span></span>
#### w/o KEXT

Example without any network kext loaded (according to kextstat and grep):
Quickly finding the node into ioreg:
class is IOPCIDevice
even the IOName and name are the only "ethernet" occurence found
0x0200 is the class code for ethernet
0x8086 is the vendor id


<span style="font-size:x-small">    | |   |   +-o S2F0@1  &lt;class <span style="background-color:rgb(255,255,0)">IOPCIDevice</span>, registered, matched, active, busy 0, retain 6&gt;</span>
<span style="font-size:x-small">    | |   |   |   {</span>
<span style="font-size:x-small">    | |   |   |     "IOPCIResourced" = Yes</span>
<span style="font-size:x-small">    | |   |   |     "IOInterruptControllers" = ("io-apic-0")</span>
<span style="font-size:x-small">    | |   |   |     "IOName" = "<span style="background-color:rgb(255,255,0)">ethernet</span>"</span>
<span style="font-size:x-small">    | |   |   |     "subsystem-id" = &lt;50070000&gt;</span>
<span style="font-size:x-small">    | |   |   |     "IODeviceMemory" = (({"address"=18446744073048031232,"length"=131072}),({"address"=18446744073047900160,"le$</span>
<span style="font-size:x-small">    | |   |   |     "class-code" = &lt;<span style="background-color:rgb(255,255,0)">00000200</span>&gt;</span>
<span style="font-size:x-small">    | |   |   |     "IOPowerManagement" = {"CurrentPowerState"=2}</span>
<span style="font-size:x-small">    | |   |   |     "revision-id" = &lt;01000000&gt;</span>
<span style="font-size:x-small">    | |   |   |     "IOInterruptSpecifiers" = (&lt;1300000007000000&gt;)</span>
<span style="font-size:x-small">    | |   |   |     "assigned-addresses" = &lt;1008028200000000000092d800000000000002001808028200000000000090d80000000000000100200$</span>
<span style="font-size:x-small">    | |   |   |     "IOChildIndex" = 2</span>
<span style="font-size:x-small">    | |   |   |     "built-in" = &lt;00&gt;</span>
<span style="font-size:x-small">    | |   |   |     "acpi-device" = "IOACPIPlatformDevice is not serializable"</span>
<span style="font-size:x-small">    | |   |   |     "device-id" = &lt;0f100000&gt;</span>
<span style="font-size:x-small">    | |   |   |     "vendor-id" = &lt;<span style="background-color:rgb(255,255,0)">86800000</span>&gt;</span>
<span style="font-size:x-small">    | |   |   |     "acpi-path" = "IOACPIPlane:/_SB/PCI0@0/P2P0@110000/S2F0@10000"</span>
<span style="font-size:x-small">    | |   |   |     "subsystem-vendor-id" = &lt;ad150000&gt;</span>
<span style="font-size:x-small">    | |   |   |     "name" = "<span style="background-color:rgb(255,255,0)">ethernet</span>"</span>
<span style="font-size:x-small">    | |   |   |     "reg" = &lt;00080200000000000000000000000000000000001008020200000000000000000000000000000200180802020000000000$</span>
<span style="font-size:x-small">    | |   |   |     "compatible" = &lt;"pci15ad,750","pci8086,100f","pciclass,020000"&gt;</span>
<span style="font-size:x-small">    | |   |   |   }</span>

#### AppleIntel8255x
<div style="display:block">
Intel82566MM.kext can be build and loaded.
<div style="display:block">
Info.plist needs to be modified to match VMware device.
<div style="display:block">
No interface is shown..
<div style="display:block">

<div style="display:block">

<div style="display:block">
With 0x8086 0x100F:
<div style="display:block">
<div style="display:block">
<span style="font-size:small">Jul 14 20:56:15 PureDarwin kernel[0]: i82557eeprom: checksum fffe incorrect</span>

<span style="font-size:small">Jul 14 20:56:15 PureDarwin kernel[0]: Intel82557: couldn't allocate eeprom object</span>


#### Intel82566MM
<div style="display:block">
Intel82566MM.kext can be build and loaded.
<div style="display:block">
Info.plist needs to be modified to match VMware device.
<div style="display:block">
No interface is shown..
<div style="display:block">

<div style="display:block">
<div style="display:block">
<span style="font-size:small">Jul 12 19:17:19 PureDarwin kernel[0]: venderid: 0x8086 deviceid: 0x100f.</span>
<div style="display:block">
<span style="font-size:small">
</span>
It seems really clear that this kext has been derivated from the FreeBSD branch too (even comments are almost identic).
<div style="display:block">
Editing the plist is naturally not enough, so after adding a couple of defines and enable debug on stdout, it looks like:
<div style="display:block">
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:44 PureDarwin kernel[0]: Intel82566MM debug: bool Intel82566MM::Init(OSDictionary *properties).</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:44 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::start(IOService * provider)</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:44 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::createWorkLoop().</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::getWorkLoop() const.</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::createOutputQueue().</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::getWorkLoop() const.</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::getPacketBufferConstraints.</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:45 PureDarwin kernel[0]: venderid: 0x8086 deviceid: 0x100f.</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::e1000_read_pcie_cap_reg(struct e1000_hw *hw, UInt32 reg, UInt16 *value)</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: flashPCIAddress.</span>
<div style="display:block">
<span style="font-size:small">Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: void Intel82566MM::free()</span>

The red part can be found in *Intel82566M.cpp* and corresponds to:

<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">**flashPCIAddress = pciDevice-&gt;mapDeviceMemoryWithRegister(kIOPCIConfigBaseAddress1); <span style="font-weight:normal">&lt;- This function failed! why?</span>**</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">if (flashPCIAddress == NULL) {</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">e_debug("flashPCIAddress.n");</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">goto FAILED_OPENED;</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">}</span>


Which irremediably leads to

<span style="font-size:small">FAILED_OPENED:</span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">pciDevice-&gt;close(this);</span>
At "free()", it's already too late anyway..

After altering a bit the code, we can go further.. but not so far.

[![](../_/rsrc/1247615901391/developers/vmware/8266MM%20debug%20I.png%3Fheight=366&width=420)](vmware/8266MM%20debug%20I.png%3Fattredirects=0)

In the FreeBSD src code:


/**

 *  e1000_read_mac_addr_82540 - Read device MAC address

 *  @hw: pointer to the HW structure

 *

 *  Reads the device MAC address from the EEPROM and stores the value.

 *  Since devices with two ports use the same EEPROM, we increment the

 *  last bit in the MAC address for the second port.

 *

 *  This version is being used over generic because of customer issues

 *  with VmWare and Virtual Box when using generic. It seems in

 *  the emulated 82545, RAR[0] does NOT have a valid address after a

 *  reset, this older method works and using this breaks nothing for

 *  these legacy adapters.

 **/




**kextload:**
<div style="display:block">

<div style="display:block">
[![](../_/rsrc/1234903619594/developers/vmware/82566MM.png)](vmware/82566MM.png%3Fattredirects=0)
<div style="display:block">

<div style="display:block">
**kextload more verbose:**
<div style="display:block">
<span style="font-size:x-small">[...]</span>
<div style="display:block">
<div style="display:block">
<span style="font-size:x-small">kextload: module /System/Library/Extensions/IONetworkingFamily.kext/Contents/MacOS/IONetworkingFamily (identifier com.apple.iokit.IONetworkingFamily) is already loaded</span>
<div style="display:block">
<span style="font-size:x-small">kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/IOKit.kext/IOKit</span>
<div style="display:block">
<span style="font-size:x-small">kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/Unsupported.kext/Unsupported</span>
<div style="display:block">
<span style="font-size:x-small">kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/Libkern.kext/Libkern</span>
<div style="display:block">
<span style="font-size:x-small">kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/Mach.kext/Mach</span>
<div style="display:block">
<span style="font-size:x-small">kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext/BSDKernel</span>
<div style="display:block">
<span style="font-size:x-small">kextload: link/loading file /System/Library/Extensions/IOPCIFamily.kext/IOPCIFamily</span>
<div style="display:block">
<span style="font-size:x-small">kextload: using existing load address 0xd19a000 (0xd19ac40 with header pad)</span>
<div style="display:block">
<span style="font-size:x-small">kextload: kmod name: com.apple.iokit.IOPCIFamily</span>
<div style="display:block">
<span style="font-size:x-small">kextload: kmod start @ 0xd1a6333 (offset 0xb6f3)</span>
<div style="display:block">
<span style="font-size:x-small">kextload: kmod stop @ 0xd1a6376 (offset 0xb736)</span>
<div style="display:block">
<span style="font-size:x-small">kextload: link/loading file /System/Library/Extensions/IONetworkingFamily.kext/Contents/MacOS/IONetworkingFamily</span>
<div style="display:block">
<span style="font-size:x-small">kextload: using existing load address 0xf888000 (0xf888c40 with header pad)</span>
<div style="display:block">
<span style="font-size:x-small">kextload: kmod name: com.apple.iokit.IONetworkingFamily</span>
<div style="display:block">
<span style="font-size:x-small">kextload: kmod start @ 0xf8983e0 (offset 0xf7a0)</span>
<div style="display:block">
<span style="font-size:x-small">kextload: kmod stop @ 0xf898423 (offset 0xf7e3)</span>
<div style="display:block">
<span style="font-size:x-small">kextload: link/loading file /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext/Contents/MacOS/Intel82566MM</span>
<div style="display:block">
<span style="font-size:x-small">kextload: allocated 53248 bytes in kernel space at 0xff7d000</span>
<div style="display:block">
<span style="font-size:x-small">kextload: using load address of 0xff7d000</span>
<div style="display:block">
<span style="font-size:x-small">kextload: kmod name: com.tootoosoft.driver.Intel82566MM</span>
<div style="display:block">
<span style="font-size:x-small">kextload: kmod start @ 0xff802cd (offset 0x268d)</span>
<div style="display:block">
<span style="font-size:x-small">kextload: kmod stop @ 0xff80310 (offset 0x26d0)</span>
<div style="display:block">
<span style="font-size:x-small">kextload: module com.tootoosoft.driver.Intel82566MM created as # 64 at address 0xff7d000, size 53248</span>
<div style="display:block">
<span style="font-size:x-small">kextload: module # 64 reference counts incremented</span>
<div style="display:block">
<span style="font-size:x-small">kextload: module # 64 started</span>
<div style="display:block">
<span style="font-size:x-small">kextload: /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext loaded successfully</span>
<div style="display:block">
<span style="font-size:x-small">kextload: loading personalities for extension /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext and dependencies</span>
<div style="display:block">
<span style="font-size:x-small">kextload: sending personalities to kernel:</span>
<div style="display:block">
<span style="font-size:x-small">kextload:     from extension /System/Library/Extensions/IONetworkingFamily.kext:</span>
<div style="display:block">
<span style="font-size:x-small">kextload:         IONetworkStack</span>
<div style="display:block">
<span style="font-size:x-small">kextload:         Kernel Debugging Driver</span>
<div style="display:block">
<span style="font-size:x-small">kextload:     from extension /System/Library/Extensions/IOPCIFamily.kext:</span>
<div style="display:block">
<span style="font-size:x-small">kextload:         IOPCI2PCIBridge-Name</span>
<div style="display:block">
<span style="font-size:x-small">kextload:         IOPCI2PCIBridge-i386</span>
<div style="display:block">
<span style="font-size:x-small">kextload:         IOPCI2PCIBridge-PCI</span>
<div style="display:block">
<span style="font-size:x-small">kextload:     from extension /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext:</span>
<div style="display:block">
<span style="font-size:x-small">kextload:         Intel82566MM</span>
<div style="display:block">
<span style="font-size:x-small">kextload: sending 6 personalities to the kernel</span>
<div style="display:block">
<span style="font-size:x-small">kextload: matching started for /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext</span>


#### AppleIntel8254XEthernet
Cannot be built (no source).
Cannot be redistributed as binary form.
Load, match and work (interface en0 is affected, network is functional).


<span style="font-size:small">1017-Jul 12 19:25:51 PureDarwin kernel[0]: Ethernet [Intel8254X]: Link down on en0 called by disable() -- </span>
<span style="font-size:small">1018-Jul 12 19:25:51 PureDarwin kernel[0]: Can't unload com.apple.driver.AppleIntel8254XEthernet due to -</span>
<span style="font-size:small">1019:Jul 12 19:26:28 PureDarwin kernel[0]: venderid: 0x8086 deviceid: 0x100f.</span>
<span style="font-size:small">1020-Jul 12 19:26:28 PureDarwin kernel[0]: AppleIntel8254XEthernet: Ethernet address 00:0c:29:69:17:26</span>
<span style="font-size:small">1021-Jul 12 19:26:28 PureDarwin kernel[0]: Ethernet [Intel8254x]: Link up on en0, 1-Gigabit, Full-duplex, No flow-control, Debug [796d,ac08,0de1,0200,41e1,7c00]</span>
<span style="font-size:small">1022-Jul 12 19:26:29 PureDarwin mDNSResponder[24]: Note: Frequent transitions for interface en0 (FE80:0000:0000:0000:020C:29FF:FE69:1726); network traffic reduction measures in effect</span>


This KEXTs seems to support all these chips:

<span style="font-size:x-small">82540EM</span>
<span style="font-size:x-small">82540EM LOM</span>
<span style="font-size:x-small">82540EP</span>
<span style="font-size:x-small">82540EP LOM</span>
<span style="font-size:x-small">82540EP LP</span>
<span style="font-size:x-small">82543GC Copper</span>
<span style="font-size:x-small">82543GC Fiber</span>
<span style="font-size:x-small">82544EI Copper</span>
<span style="font-size:x-small">82544EI Fiber</span>
<span style="font-size:x-small">82544GC Copper</span>
<span style="font-size:x-small">82544GC LOM</span>
<span style="font-size:x-small">82545EM Copper</span>
<span style="font-size:x-small">82545EM Fiber</span>
<span style="font-size:x-small">82545GM Copper</span>
<span style="font-size:x-small">82545GM Fiber</span>
<span style="font-size:x-small">82545GM SERDES</span>
<span style="font-size:x-small">82546EB Copper</span>
<span style="font-size:x-small">82546EB Fiber</span>
<span style="font-size:x-small">82546GB Copper</span>
<span style="font-size:x-small">82546GB Fiber</span>
<span style="font-size:x-small">82546GB SERDES</span>
<span style="font-size:x-small">82541EI</span>
<span style="font-size:x-small">82541EI Mobile</span>
<span style="font-size:x-small">82541ER</span>
<span style="font-size:x-small">82541GI</span>
<span style="font-size:x-small">82541GI Mobile</span>
<span style="font-size:x-small">82547EI</span>
<span style="font-size:x-small">82547GI</span>


Values found (non exhaustive) interesting have been highlighted.


<span style="font-size:x-small"></span>
    | |   |   +-o S2F0@1  &lt;class IOPCIDevice, registered, matched, active, busy 0, retain 9&gt;
    | |   |   | | {
    | |   |   | |   "IOPCIResourced" = Yes
    | |   |   | |   "IOInterruptControllers" = ("io-apic-0")
    | |   |   | |   "IOName" = "ethernet"
    | |   |   | |   "subsystem-id" = &lt;50070000&gt;
    | |   |   | |   "IODeviceMemory" = (({"address"=18446744073048031232,"length"=131072}),({"address"=18446744073047900160,"le$
    | |   |   | |   "IOPMPCIConfigSpaceVolatile" = No
    | |   |   | |   "class-code" = &lt;00000200&gt;
    | |   |   | |   "EEPROM Version" = "0.0"
    | |   |   | |   "IOPowerManagement" = {"ChildrenPowerState"=2,"CurrentPowerState"=2}
    | |   |   | |   "revision-id" = &lt;01000000&gt;
    | |   |   | |   "IOInterruptSpecifiers" = (&lt;1300000007000000&gt;)
    | |   |   | |   "assigned-addresses" = &lt;1008028200000000000092d800000000000002001808028200000000000090d80000000000000100200$
    | |   |   | |   "IOChildIndex" = 2
    | |   |   | |   "built-in" = &lt;00&gt;
    | |   |   | |   "acpi-device" = "IOACPIPlatformDevice is not serializable"
    | |   |   | |  <span style="background-color:rgb(255,255,0)"> "</span><span style="background-color:rgb(255,255,0)">device-id" = &lt;0f100000&gt; </span>
    | |   |   | |  <span style="background-color:rgb(255,255,0)"> "vendor-id" = &lt;86800000&gt; </span>
    | |   |   | |   "acpi-path" = "IOACPIPlane:/_SB/PCI0@0/P2P0@110000/S2F0@10000"
    | |   |   | |   "subsystem-vendor-id" = &lt;ad150000&gt;
    | |   |   | |   "name" = "ethernet"
    | |   |   | |   "EEPROM Checksum Valid" = Yes
    | |   |   | |   "reg" = &lt;00080200000000000000000000000000000000001008020200000000000000000000000000000200180802020000000000$
    | |   |   | |   "compatible" = &lt;"pci15ad,750","pci8086,100f","pciclass,020000"&gt;
    | |   |   | | }
    | |   |   | | 
    | |   |   | +-o AppleIntel8254XEthernet  &lt;class AppleIntel8254XEthernet, !registered, !matched, active, busy 0, retain 6&gt;
    | |   |   |   | {
    | |   |   |   |   "IOProbeScore" = 10000
    | |   |   |   |   "Driver Parameters" = {"TxQueueSize"=4096,"RxAbsoluteTimer1000"=64,"Offload TCP/IP Checksum"=Yes,"EnableL$
    | |   |   |   |  <span style="background-color:rgb(234,153,153)"> "CFBundleIdentifier" = "com.apple.driver.AppleIntel8254XEthernet" </span>
    | |   |   |   |  <span style="background-color:rgb(182,215,168)"> "IODefaultMedium" = "00000020" </span>
    | |   |   |   |   "IOSelectedMedium" = "00000020"
    | |   |   |   |   "IOMatchCategory" = "IODefaultMatchCategory"
    | |   |   |   |   "IOLinkSpeed" = 1000000000
    | |   |   |   |   "IOPowerManagement" = {"CurrentPowerState"=1}
    | |   |   |   |   "IOVendor" = "Intel"
    | |   |   |   |   "IOPacketFilters" = {"IONetworkFilterGroup"=275,"IOEthernetWakeOnLANFilterGroup"=0}
    | |   |   |   |   "IOMACAddress" = &lt;000c29691726&gt;
    | |   |   |   |  <span style="background-color:rgb(162,196,201)"> "IOProviderClass" = "IOPCIDevice" </span>
    | |   |   |   |   "IOFeatures" = 10
    | |   |   |   |  <span style="background-color:rgb(180,167,214)"> "IOPCIClassMatch" = "0x02000000&0xffff0000" </span>
    | |   |   |   |   "IOLinkStatus" = 3
    | |   |   |   |   "IOMaxPacketSize" = 9018
    | |   |   |   |   "IOMinPacketSize" = 64
    | |   |   |   |   "IOMediumDictionary" = {"00500023"={"Type"=5242915,"Index"=6,"Flags"=0,"Speed"=10000000},"00100026"={"Typ$
    | |   |   |   |  <span style="background-color:rgb(159,197,232)"> "IOPCIPrimaryMatch" = "0x10008086&0x0000ffff" </span>
    | |   |   |   |  <span style="background-color:rgb(255,255,0)"> "IOModel" = "82545EM Copper" </span>
    | |   |   |   |  <span style="background-color:rgb(213,166,189)"> "IOClass" = "AppleIntel8254XEthernet" </span>
    | |   |   |   |   "IOActiveMedium" = "00100030"
    | |   |   |   |   "EN Number" = 0
    | |   |   |   | }
    | |   |   |   | 
    | |   |   |   +-o IOEthernetInterface  &lt;class IOEthernetInterface, registered, matched, active, busy 0, retain 10&gt;
    | |   |   |     | {
    | |   |   |     |   "IOMediaAddressLength" = 6
    | |   |   |     |   "IOPrimaryInterface" = Yes
    | |   |   |     |   "IOInterfaceType" = 6
    | |   |   |     |   "IORequiredPacketFilters" = {"IONetworkFilterGroup"=19,"IOEthernetWakeOnLANFilterGroup"=0}
    | |   |   |     |   "IOInterfaceFlags" = 34915
    | |   |   |     |   "IOInterfaceExtraFlags" = 1073744192
    | |   |   |     |   "IOInterfaceUnit" = 0
    | |   |   |     |   "IONetworkData" = {"IOEthernetStatsKey"={"Size"=216,"Data"=&lt;0000000000000000000000000000000000000000000$
    | |   |   |     |   "BSD Name" = "en0"
    | |   |   |     |   "IOLocation" = ""
    | |   |   |     |   "IOMaxTransferUnit" = 1500
    | |   |   |     |   "IOInterfaceNamePrefix" = "en"
    | |   |   |     |   "IOBuiltin" = Yes
    | |   |   |     |   "IOActivePacketFilters" = {"IONetworkFilterGroup"=19,"IOEthernetWakeOnLANFilterGroup"=0}
    | |   |   |     |   "IOMulticastAddressList" = &lt;01005e0000fb01005e0000013333000000fb33333e2cf1a83333000000013333ff691726&gt;
    | |   |   |     |   "IOInterfaceState" = 3
    | |   |   |     |   "IOMediaHeaderLength" = 14
    | |   |   |     |   "IOControllerEnabled" = Yes
    | |   |   |     | }
    | |   |   |     | 
    | |   |   |     +-o IONetworkStack  &lt;class IONetworkStack, registered, matched, active, busy 0, retain 7&gt;
    | |   |   |       | {
    | |   |   |       |   "IOProviderClass" = "IOResources"
    | |   |   |       |   "IOMatchCategory" = "IONetworkStack"
    | |   |   |       |   "IOProbeScore" = 0
    | |   |   |       |   "IOClass" = "IONetworkStack"
    | |   |   |       |   "CFBundleIdentifier" = "com.apple.iokit.IONetworkingFamily"
    | |   |   |       |   "IOResourceMatch" = "IOBSD"
    | |   |   |       | }
    | |   |   |       | 
    | |   |   |       +-o IONetworkStackUserClient  &lt;class IONetworkStackUserClient, !registered, !matched, active, busy 0, ret$
    | |   |   |           {
    | |   |   |           }



A // with its Info.plist (.. file) can be established:
<span style="font-size:small"><span style="font-size:13px"></span></span>
[...]
&lt;dict&gt;

> <span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;CFBundleIdentifier&lt;/key&gt;</span>
> <span style="font-family:courier new,monospace;font-size:small">&lt;string&gt;<span style="background-color:rgb(234,153,153)">com.apple.driver.AppleIntel8254XEthernet</span>&lt;/string&gt;</span>
>
> > <span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;IOClass&lt;/key&gt;</span>
> > <span style="font-family:courier new,monospace;font-size:small"><span style="background-color:rgb(255,255,255)">&lt;string&gt;</span><span style="background-color:rgb(213,166,189)">AppleIntel8254XEthernet</span><span style="background-color:rgb(255,255,255)">&lt;/string&gt;</span></span>
> > <span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;IODefaultMedium&lt;/key&gt;</span>
> > <span style="font-family:courier new,monospace;font-size:small"><span style="background-color:rgb(255,255,255)">&lt;string&gt;</span><span style="background-color:rgb(182,215,168)">00000020</span><span style="background-color:rgb(255,255,255)">&lt;/string&gt;</span></span>
> > <span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;IOPCIClassMatch&lt;/key&gt;</span>
> > <span style="font-family:courier new,monospace;font-size:small"><span style="background-color:rgb(255,255,255)">&lt;string&gt;</span><span style="background-color:rgb(180,167,214)">0x02000000&amp;0xffff0000</span><span style="background-color:rgb(255,255,255)">&lt;/string&gt;</span></span>
> > <span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;IOPCIPrimaryMatch&lt;/key&gt;</span>
> > <span style="font-family:courier new,monospace;font-size:small"><span style="background-color:rgb(255,255,255)">&lt;string&gt;</span><span style="background-color:rgb(159,197,232)">0x10008086&amp;0x0000ffff</span><span style="background-color:rgb(255,255,255)">&lt;/string&gt;</span></span>
> > <span style="font-family:courier new,monospace;font-size:small">&lt;key&gt;IOProviderClass&lt;/key&gt;</span>
> > <span style="font-family:courier new,monospace;font-size:small"><span style="background-color:rgb(255,255,255)">&lt;string&gt;</span><span style="background-color:rgb(162,196,201)">IOPCIDevice</span><span style="background-color:rgb(255,255,255)">&lt;/string&gt;</span></span>
> 
<span style="font-family:courier new,monospace;font-size:x-small"></span>
<span style="font-size:13px"></span>
### a KEXT pseudo-life
The driver inspects and configure the PCI Device
1.  driver examines the values in the PCI configuration space registers (e.g., revision ID register)
2.  driver sets some value of them (e.g., enable memory write)
3.  driver interacts with its device

(random notes: ipconfig set en0 NONE before kextunload &lt;- not tested)




Pseudo-pre-deduction: If the kext is loaded but no interface, could it be?:
<span style="font-family:Lucida Grande,Geneva,Helvetica,Arial,sans-serif;font-size:12px"></span>
`start`{style="font-size:11px;font-family:Monaco,Courier,Consolas,monospace"}
:   The `start`{style="font-size:11px;font-family:Monaco,Courier,Consolas,monospace"} function should initialize the device to a working state. It also needs to create a network object and make it visible to the networking stack as an interface
    
    
network driver's <span style="font-size:small">start</span> function:
-   set network interface object
-   a work loop
-   an output queue
-   specific resources
-   (also retains its provider nub (IOPCIDevice?))

In order to open the Provider nub, the driver should:
1.  verify that it is of the appropriate class
2.  retain a reference to it
3.  open it in order to access its services



<span style="font-family:Arial,Verdana,sans-serif;font-size:16px;font-weight:bold"><span style="font-size:13px;font-weight:normal"></span></span>
### Host NIC

Restarts all the vmnet services on the <span style="font-weight:bold">host side</span>:

<span style="font-family:courier new,monospace"><span style="font-size:small">/Library/Application Support/VMware Fusion/boot.sh --restart</span></span>
Troubleshooting
---------------
### On read-only medium
The tty is flooded with log telling attempt to write on a read-only medium (ie: auth mechanism too) does not work.
<span style="font-weight:bold"><span style="color:rgb(255,0,0)">Shadow read-Write support is needed</span>.</span> Another obvious implicit goal is to install PureDarwin with PureDarwin.
<span style="font-weight:bold">FIXME: <span style="font-weight:normal">It will probably use <span style="font-style:italic">/usr/libexec/vndevice</span> with a shadow file and some node in <span style="font-style:italic">/dev/vn*</span>.</span></span>
### Random log
<span style="font-family:courier new,monospace"><span style="font-size:small">Aug 28 18:58:15.129: vmx| Licensecheck: Invalid license file.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">Aug 28 18:58:15.131: vmx| Host: SRAT tables not found in memory</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">Aug 28 18:58:15.480: vmx| Topology discovery error: /Library/Preferences/com.apple.windowserver.plist doesn't contain expected key.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">Aug 28 18:58:15.742: vmx| DISK: Disabling unbuffered I/O on ide0:0 to work around Apple bugs 5679432 and 6048690.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">Sep 27 11:52:13.472: vmx| PTSC: failed to read the TSCs.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">Sep 27 11:52:17.727: vmx| Error: Encountered Apple bug #5202831.  Disconnecting.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">Sep 27 11:52:36.086: vcpu-0| CDROM ide1:0: CMD 0xad (*UNKNOWN (0xad)*) FAILED (key 0x5 asc 0x24 ascq 0)</span></span>

Resources
---------
ftp://download.intel.com/design/network/specupdt/82545em.pdf
http://www.intel.com/design/network/products/lan/docs/82545.htm
http://download.intel.com/design/network/manuals/8254x_GBe_SDM.pdf

http://downloadcenter.intel.com/Detail_Desc.aspx?agr=Y&ProductID=990&DwnldID=3294&strOSs=52&OSFullName=FreeBSD*&lang=eng
<span style="font-family:Arial,sans-serif;font-size:small;color:rgb(85,85,85)">FreeBSD* 4.7 to 4.10 driver for all Intel® PRO/1000 gigabit Ethernet adapters. Valid for the 82540, 82542, 82543, 82544, **82545**, 82546 and 82547 controllers. 
</span>

http://developer.apple.com/documentation/DeviceDrivers/Conceptual/NetworkDriver/1_Intro/Intro.html
http://developer.apple.com/documentation/DeviceDrivers/Conceptual/NetworkDriver/4_Writing%20the%20Driver/NetworkController.html

<http://developer.apple.com/documentation/HardwareDrivers/Conceptual/HWTech_Ethernet/Introduction/ENet_intro.html>
<http://developer.apple.com/documentation/Hardware/Conceptual/HWtech_PCI/Articles/pci_implementation.html>
<http://developer.apple.com/documentation/Darwin/Conceptual/NetworkKernelExtensions/about/about.html>
<http://developer.apple.com/documentation/Darwin/Conceptual/KEXTConcept/KEXTConceptIntro/KEXTIntro.html>
<http://developer.apple.com/documentation/DeviceDrivers/Conceptual/WritingPCIDrivers/pci_device/pci_device.html>
<http://download.intel.com/design/network/manuals/8255X_OpenSDM.pdf>

<https://code.google.com/p/pcnet32-driver-for-puredarwin/> - **information about this driver still needs to be worked into this page**



