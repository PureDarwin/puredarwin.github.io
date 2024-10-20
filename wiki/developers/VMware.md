VMware
======

<div style="margin:5px 10px;display:inline;float:right">
!(../_/rsrc/1247515808697/developers/vmware/vmware.gif)(vmware/vmware.gif%3Fattredirects=0)

Many [VMware](http://www.vmware.com/) products are now able to run a Darwin system (e.g., PureDarwin).
From *VMware Fusion 2.0* (Mac OS X) to *VMware Player 2.5* (free download for Windows and Linux) via *VMware ESX* and later versions, PureDarwin should boot without any troubles.

**A more precise list will be constituted if respective [feedback](../todo.html) is received.**

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
    `qemu-img convert -O vmdk PureDarwin.iso PureDarwin.vmdk`

Launch VMware Fusion 2.0 or later and create a new machine based on the ISO or .vmdk - VMware Fusion will automatically recognize it as "Mac OS X Server" and configure the virtual machine accordingly. You do not need to change any settings. 
### Using VMware other than Fusion 
Two KEXTs appeard useful for VMware release(s) other than Fusion:

-   LegacyAppleIntelPIIXATA
-   NullCPUPowerManagement
They can be found in VMware-Drivers-OpenSource.zip. See [Downloads](../downloads.html) page.

Settings
--------
### VMware settings
#### Enable the built-in VNC server
Add these lines in the .vmx file:

`RemoteDisplay.vnc.port = "5900"
RemoteDisplay.vnc.enabled = "TRUE"
# optional password:
RemoteDisplay.vnc.password = "password"
`

Then simply connect your favorite VNC client to localhost.
### Boot arguments
(please add text)
### Faking guest OS detection
We need to fake VMware guest OS detection in order to avoid error message "*The guest operating system is not Mac OS X Server*" (implicitly to simply boot).

![](/img/developers/vmware/VMware%20guest%20os%20detection.png)

VMware guest OS detection is trivial, and so the way to avoid it:

 `touch "/Volumes/PureDarwin/System/Library/CoreServices/ServerVersion.plist"``
`
__Note:__ This tweak should/could be deprecated by time.

Devices
-------
VMware Fusion 2.0.5
**Host:** Mac OS X 9.7.0
**Guest:** PureDarwin (9J61)

Here's a vendor/device id list retrieved from the VMware guest OS:


`"0x8086","0x7191","Intel Corporation","82443BX/ZX","440BX/ZX AGPset PCI-to-PCI bridge"`
"0x8086","0x7110","Intel Corporation","82371AB/EB/MB","PIIX4/4E/4M ISBridgeA "
"0x8086","0x7113","Intel Corporation","82371AB/EB/MB","PIIX4/4E/4M Power Management Controller"
"0x8086","0x7111","Intel Corporation","82371AB/EB/MB","PIIX4/4E/4M IDE Controller"
"0x15ad","0x0790","",""
[...] <- + x 30

"0x15ad","0x0790","",""

"0x8086","0x7112","Intel Corporation","82371AB/EB/MB","PIIX4/4E/4M USB Interface"
"0x8086","0x100F","Intel Corporation","82545EM","Gigabit Ethernet Controller (copper)"
"0x15AD","0x0770","VMware Inc.","n/a","Standard Enhanced PCI to USB Host Controller"
"0x1274","0x1371","Ensoniq","ES 1371","AudioPCI"
"0x1000","0x0030","LSI Logic","LSI53C1020/1030","PCI-X to Ultra320 SCSI Controller"
"0x15AD","0x0405","VMware Inc.","9500MGS","NVIDIA"
"0x15AD","0x0740","VMware Inc.","0X0880","VMWare VMCI Bus Device"
"0x8086","0x7190","Intel Corporation","82443BX/ZX","440BX/ZX AGPset Host Bridge"

Boot
----
### VMware Fusion BIOS
VMware Fusion comes with a combo PhoenixBIOS/VMware BIOS.

![](/img/developers/vmware/VMware%20fusion%20bios%20boot.png)

![](/img/developers/vmware/VMware%20fusion%20bios.png)

![](/img/developers/vmware/VMware%20fusion%20bios%202.png)
### Bootloader
VMware uses darwin.iso (VMware Tools) which contains the DFE bootloader (Stage 2 boot file < 128K) to provide a bootloader.
#### darwin.iso

Located in /Library/Application Support/VMware Fusion/isoimages/original/darwin.iso
ISO 9660 CD-ROM filesystem data 'CD' (bootable)


pdisk reports:
Partition map (with 512 byte blocks) on 'original/darwin.iso'
 #:                type name                  length   base   ( size )
 1: Apple_partition_map Apple                     63 @ 1     
 2:           Apple_HFS DiscRecording 3.2.0f2   6940 @ 244    (  3.4M)


Device block size=2048, Number of Blocks=3339059200 (6.2T)
DeviceType=0x0, DeviceId=0x0


The DFE bootloader:
-r--r--r--@ 1 201  wheel  63520 Jun 23 00:20 /Volumes/VMware Tools/.hiddendir/boot (dfeâ€™)
In order to compare the siwe, Chameleon takes 295328B and the latest DFE 63648B.


Facing the bootloader size limitation:
![](/img/developers/vmware/VMware%20booter%20size%20limitation.png)


It is possible to alter the content of darwin.iso, but the package needs to be signed again.


hdiutil -readwrite attach darwin.iso
hdiutil eject..
openssl genrsa -out tools-priv.pem 2048
openssl rsa -in tools-priv.pem -pubout -out tools-key.pub
openssl dgst -sha1 -sign tools-priv.pem < darwin.iso > darwin.iso.sig
for A in *.iso ; do openssl dgst -sha1 -sign tools-priv.pem < $A > $A.sig ; done

### Single user mode
It boots.

![](../_/rsrc/1218489175310/developers/vmware/VMware%20single%20user-mode.png%3Fheight=150&width=200)
### Multi user mode
It boots but fails because of read-only medium when a connected CD/DVD drive is configured to use a disk image (ISO).
It works when a VMware disk image (.vmdk) is used since read-write is enabled (and functional) by default.
Network
-------
### Emulated NICs
**VMware seems to provide 3 emulated NIC:**
-   **e1000**
-   **VMware NIC - vmxnet
    **High performance (Gigabit), need VMware drivers in the guest.
    OK for production.
-   **VLANCE (aka AMD PCNET-32)
    **Lower perf, high CPU load, no kext available, problems solved. Update November 2012: A driver is in the works at <https://code.google.com/p/pcnet32-driver-for-puredarwin/> - **information about this driver still needs to be worked into this page**
#### e1000
VMware emulates an Intel e1000 network card.
"e1000" is apparently a generic term for a **series** of similar but different chips.
<http://www.intel.com/design/network/products/lan/controllers/82545.htm>

``
****
**82547EI-A1 8086h       1019h     Copper 
82547EI-B0 8086h       1019h     Copper 
82547EI-B0 8086h       101Ah     Mobile 
82547GI-B0 8086h       1019h     Copper 
82546EB-A1 8086h       1010h     Copper; Dual Port MAC Default 
82546EB-A1 8086h       1012h     Fiber; Dual Port 
82546EB-A1 8086h       101Dh     Copper; Quad Port 
82546GB-B0 8086h       1079h     Copper; Dual Port **
**82546GB-B0 8086h       107Ah     Fiber; Dual Port 
82546GB-B0 8086h       107Bh     SerDes; Dual Port **
**82545EM-A  8086h       100Fh     Copper**
**82545EM-A  8086h       1011h     Fiber**
**82545GM-B  8086h       1026h     Copper MAC Default **
**82545GM-B  8086h       1027h     Fiber **
**82545GM-B  8086h       1028h     SerDes**
**82544EI-A4 8086h       1107h     Copper MAC Default **
**82544GC-A4 8086h       1112h     Copper MAC Default **
**82541EI-A0 8086h       1013h     Cooper MAC Default **
**82541EI-A0 8086h       1013h     Cooper MAC Default **
**82541EI-B0 8086h       1013h     Cooper MAC Default **
**82541EI-B0 8086h       1018h     Mobile**
**82541GI-B1 8086h       1076h     Cooper **
**82541GI-B1 8086h       1077h     Mobile **
**82541PI-C0 8086h       1076h     Cooper **
**82541ER-C0 8086h       1078h     Cooper **
**82540EP-A  8086h       1017      Desktop **
**82540EP-A  8086h       1016      Mobile **
**82540EM-A  8086h       100E      Desktop **
**82540EM-A  8086h       1015      Mobile **

****
### Status

The VMware virtual device chipset seems to correspond to the Intel82545EM (Copper)

-   **Vendor ID:** 0x8086
-   **Primary device ID:** 0x100F


Mac OS X contains a driver (AppleIntel8254XEthernet) for the chip emulated by VMware which "should match and work".
**But** this driver is __not available__ for Darwin yet, neither in source nor binary form.

We found also two KEXTs close (but not enough "by nature") to the VMware 82545EM virtual device:
-   AppleIntel8255x (built from the [Darwinbuild](darwinbuild.html) project)
-   [82566mm-osx-driver](http://code.google.com/p/82566mm-osx-driver/) (an OpenSource one)
Both of the two KEXTs personality file (Info.plist) can be modified to match the VMware virtual device in order to be (kext)loaded at boot.
**But no interface (e.g., en0) is affected...**


The 
e1000 support quest
-------------------
### Notions
#### Driver and IOPCIDevice
PCI stands for Peripheral Component Interconnect.

A driver for a PCI Ethernet controller inherits from IOEthernetController but uses an instance of IOPCIDevice class (in order to connect to the PCI bus).
IOPCIDevice is a basic nub class representing any PCI device in any PCI slot.

Ethernet driver <-> IOPCIDevice <-> IOPCIBridge <-> IOPlatformDevice <-> ...
#### PCI matching summarization
A driver can control a device on a PCI bus.
A driver announces this fact by including a "*personality*" in its plist file.
This personality includes IOProviderClass=IOPCIDevice (Key=Value).
IOPCIDevice defines 2 sets of keys that a driver can use for matching:
-   a key based on standard PCI registers
-   a key based on Open Firmware (probably related to PPC only)
A PCI device driver can use one type of key or both of them (if personalities are disjoint)
### Vendor and Device IDs
#### Vendor ID (intel def.)
This uniquely identifies all Intel PCI products.
This field may be auto-loaded from the EEPROM at power on or upon the assertion of PCI_RST#.
A value of 0x8086 is the default for this field upon power up if the EEPROM does not respond or is not programmed. 
****
#### Device ID (Intel def.)
This uniquely identifies the Ethernet controller.
This field may be autoloaded from the EEPROM at power on or upon the assertion of RST#.
The default value for this field is used upon power up if the EEPROM does not respond or is not programmed.

#### PCI configuration space registers 

-   vendor and device ID (offsets 0x00 and 0x002)
-   subsystem vendor and device ID (offsets 0x2C and 0x2E)
-   class code (offset 0x09)
-   revision ID (not available in property matching)
-   header type (not available in property matching)
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
`<key>IOPCIMatch</key>`
``


Vendor ID: 0x8086
Primary device ID: 0x1000 or 0x100F

`<key>IOPCIMatch</key>`
`0x10008086 0x100F8086`



Vendor ID: 0x8086
Primary device ID: 0x1000..0x10FF (first two digits subsystem IDs are not checked)

`<key>IOPCIPrimaryMatch</key>`
<span style="font-family:courier new,monospace;font-size:small"><string>0x10008086&0xFF00FFFF</string></span>

Class code for ethernet controller (0x0200 (in fact 4bytes, last byte ignored))
`<key>IOPCIClassMatch</key>`
<span style="font-family:courier new,monospace;font-size:small"><string>0x02000000&0xffff0000</string></span>



Which is confirmed on
-   **FreeBSD:** **
-   **GNU/Linux:** 
-   **Intel:** From the "*Intel PCI/PCI-X Family of Gigabit Ethernet Controllers Software Developerâ€™s Manual*", 
    A list of pair model / device id is available in the Intel spec, which confirm the result above ( "IOModel" = "82545EM Copper" )
-   **e1000 from sourceforge:** *82540EP/EM, 82541xx, 82544GC/EI, 82545GM/EM, 82546GB/EB, and 82547xx*
    <http://kent.dl.sourceforge.net/sourceforge/e1000/OpenSDM_8254x-37.pdf>
-   <http://www.pcidatabase.com/vendor_details.php?id=1302> also.
<span style="font-size:small"><span style="font-size:x-small">__Note:__ "When running VMware ESX Server 3.0.0, you can experience a kernel panic if you use Intel e1000 network adapters with any of the following PCI IDs: <span style="font-size:13px">**0x100F**[...]" - <http://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=2221></span></span></span>
### Real KEXTs

#### w/o KEXT

Example without any network kext loaded (according to kextstat and grep):
Quickly finding the node into ioreg:
class is IOPCIDevice
even the IOName and name are the only "ethernet" occurence found
0x0200 is the class code for ethernet
0x8086 is the vendor id



    | |   |   |   {
    | |   |   |     "IOPCIResourced" = Yes
    | |   |   |     "IOInterruptControllers" = ("io-apic-0")

    | |   |   |     "subsystem-id" = <50070000>
    | |   |   |     "IODeviceMemory" = (({"address"=18446744073048031232,"length"=131072}),({"address"=18446744073047900160,"le$

    | |   |   |     "IOPowerManagement" = {"CurrentPowerState"=2}
    | |   |   |     "revision-id" = <01000000>
    | |   |   |     "IOInterruptSpecifiers" = (<1300000007000000>)
    | |   |   |     "assigned-addresses" = <1008028200000000000092d800000000000002001808028200000000000090d80000000000000100200$
    | |   |   |     "IOChildIndex" = 2
    | |   |   |     "built-in" = <00>
    | |   |   |     "acpi-device" = "IOACPIPlatformDevice is not serializable"
    | |   |   |     "device-id" = <0f100000>

    | |   |   |     "acpi-path" = "IOACPIPlane:/_SB/PCI0@0/P2P0@110000/S2F0@10000"
    | |   |   |     "subsystem-vendor-id" = <ad150000>
    | |   |   |     "name" = "ethernet"
    | |   |   |     "reg" = <00080200000000000000000000000000000000001008020200000000000000000000000000000200180802020000000000$
    | |   |   |     "compatible" = <"pci15ad,750","pci8086,100f","pciclass,020000">
    | |   |   |   }

#### AppleIntel8255x

Intel82566MM.kext can be build and loaded.

Info.plist needs to be modified to match VMware device.

No interface is shown..





With 0x8086 0x100F:


Jul 14 20:56:15 PureDarwin kernel[0]: i82557eeprom: checksum fffe incorrect

Jul 14 20:56:15 PureDarwin kernel[0]: Intel82557: couldn't allocate eeprom object


#### Intel82566MM

Intel82566MM.kext can be build and loaded.

Info.plist needs to be modified to match VMware device.

No interface is shown..




Jul 12 19:17:19 PureDarwin kernel[0]: venderid: 0x8086 deviceid: 0x100f.



It seems really clear that this kext has been derivated from the FreeBSD branch too (even comments are almost identic).

Editing the plist is naturally not enough, so after adding a couple of defines and enable debug on stdout, it looks like:


Jul 15 00:38:44 PureDarwin kernel[0]: Intel82566MM debug: bool Intel82566MM::Init(OSDictionary *properties).

Jul 15 00:38:44 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::start(IOService * provider)

Jul 15 00:38:44 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::createWorkLoop().

Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::getWorkLoop() const.

Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::createOutputQueue().

Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::getWorkLoop() const.

Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::getPacketBufferConstraints.

Jul 15 00:38:45 PureDarwin kernel[0]: venderid: 0x8086 deviceid: 0x100f.

Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: Intel82566MM::e1000_read_pcie_cap_reg(struct e1000_hw *hw, UInt32 reg, UInt16 *value)

Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: flashPCIAddress.

Jul 15 00:38:45 PureDarwin kernel[0]: Intel82566MM debug: void Intel82566MM::free()

The red part can be found in *Intel82566M.cpp* and corresponds to:

 
 if (flashPCIAddress == NULL) {
 e_debug("flashPCIAddress.n");
 goto FAILED_OPENED;
 }


Which irremediably leads to

FAILED_OPENED:
 pciDevice->close(this);
At "free()", it's already too late anyway..

After altering a bit the code, we can go further.. but not so far.

![](/img/developers/vmware/8266MM%20debug%20I.png)

In the FreeBSD src code:


/**

 *  e1000_read_mac_addr_82540 - Read device MAC address

 *  @hw: pointer to the HW structure

 *

 *  Reads the device MAC address from the EEPROM and stores the value.

 *  Since devices with two ports use the same EEPROM, we increment the

 *  last bit in the MAC address for the second port.

 *

 *  This version is being used over generic because of customer issues

 *  with VmWare and Virtual Box when using generic. It seems in

 *  the emulated 82545, RAR[0] does NOT have a valid address after a

 *  reset, this older method works and using this breaks nothing for

 *  these legacy adapters.

 **/




**kextload:**



![](/img/developers/vmware/82566MM.png)



**kextload more verbose:**

[...]


kextload: module /System/Library/Extensions/IONetworkingFamily.kext/Contents/MacOS/IONetworkingFamily (identifier com.apple.iokit.IONetworkingFamily) is already loaded

kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/IOKit.kext/IOKit

kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/Unsupported.kext/Unsupported

kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/Libkern.kext/Libkern

kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/Mach.kext/Mach

kextload: link/loading file /System/Library/Extensions/System.kext/PlugIns/BSDKernel.kext/BSDKernel

kextload: link/loading file /System/Library/Extensions/IOPCIFamily.kext/IOPCIFamily

kextload: using existing load address 0xd19a000 (0xd19ac40 with header pad)

kextload: kmod name: com.apple.iokit.IOPCIFamily

kextload: kmod start @ 0xd1a6333 (offset 0xb6f3)

kextload: kmod stop @ 0xd1a6376 (offset 0xb736)

kextload: link/loading file /System/Library/Extensions/IONetworkingFamily.kext/Contents/MacOS/IONetworkingFamily

kextload: using existing load address 0xf888000 (0xf888c40 with header pad)

kextload: kmod name: com.apple.iokit.IONetworkingFamily

kextload: kmod start @ 0xf8983e0 (offset 0xf7a0)

kextload: kmod stop @ 0xf898423 (offset 0xf7e3)

kextload: link/loading file /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext/Contents/MacOS/Intel82566MM

kextload: allocated 53248 bytes in kernel space at 0xff7d000

kextload: using load address of 0xff7d000

kextload: kmod name: com.tootoosoft.driver.Intel82566MM

kextload: kmod start @ 0xff802cd (offset 0x268d)

kextload: kmod stop @ 0xff80310 (offset 0x26d0)

kextload: module com.tootoosoft.driver.Intel82566MM created as # 64 at address 0xff7d000, size 53248

kextload: module # 64 reference counts incremented

kextload: module # 64 started

kextload: /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext loaded successfully

kextload: loading personalities for extension /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext and dependencies

kextload: sending personalities to kernel:

kextload:     from extension /System/Library/Extensions/IONetworkingFamily.kext:

kextload:         IONetworkStack

kextload:         Kernel Debugging Driver

kextload:     from extension /System/Library/Extensions/IOPCIFamily.kext:

kextload:         IOPCI2PCIBridge-Name

kextload:         IOPCI2PCIBridge-i386

kextload:         IOPCI2PCIBridge-PCI

kextload:     from extension /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext:

kextload:         Intel82566MM

kextload: sending 6 personalities to the kernel

kextload: matching started for /System/Library/Extensions/IONetworkingFamily.kext/Contents/PlugIns/Intel82566MM.kext


#### AppleIntel8254XEthernet
Cannot be built (no source).
Cannot be redistributed as binary form.
Load, match and work (interface en0 is affected, network is functional).


1017-Jul 12 19:25:51 PureDarwin kernel[0]: Ethernet [Intel8254X]: Link down on en0 called by disable() -- 
1018-Jul 12 19:25:51 PureDarwin kernel[0]: Can't unload com.apple.driver.AppleIntel8254XEthernet due to -
1019:Jul 12 19:26:28 PureDarwin kernel[0]: venderid: 0x8086 deviceid: 0x100f.
1020-Jul 12 19:26:28 PureDarwin kernel[0]: AppleIntel8254XEthernet: Ethernet address 00:0c:29:69:17:26
1021-Jul 12 19:26:28 PureDarwin kernel[0]: Ethernet [Intel8254x]: Link up on en0, 1-Gigabit, Full-duplex, No flow-control, Debug [796d,ac08,0de1,0200,41e1,7c00]
1022-Jul 12 19:26:29 PureDarwin mDNSResponder[24]: Note: Frequent transitions for interface en0 (FE80:0000:0000:0000:020C:29FF:FE69:1726); network traffic reduction measures in effect


This KEXTs seems to support all these chips:

82540EM
82540EM LOM
82540EP
82540EP LOM
82540EP LP
82543GC Copper
82543GC Fiber
82544EI Copper
82544EI Fiber
82544GC Copper
82544GC LOM
82545EM Copper
82545EM Fiber
82545GM Copper
82545GM Fiber
82545GM SERDES
82546EB Copper
82546EB Fiber
82546GB Copper
82546GB Fiber
82546GB SERDES
82541EI
82541EI Mobile
82541ER
82541GI
82541GI Mobile
82547EI
82547GI


Values found (non exhaustive) interesting have been highlighted.



    | |   |   +-o S2F0@1  &lt;class IOPCIDevice, registered, matched, active, busy 0, retain 9&gt;
    | |   |   | | {
    | |   |   | |   "IOPCIResourced" = Yes
    | |   |   | |   "IOInterruptControllers" = ("io-apic-0")
    | |   |   | |   "IOName" = "ethernet"
    | |   |   | |   "subsystem-id" = &lt;50070000&gt;
    | |   |   | |   "IODeviceMemory" = (({"address"=18446744073048031232,"length"=131072}),({"address"=18446744073047900160,"le$
    | |   |   | |   "IOPMPCIConfigSpaceVolatile" = No
    | |   |   | |   "class-code" = &lt;00000200&gt;
    | |   |   | |   "EEPROM Version" = "0.0"
    | |   |   | |   "IOPowerManagement" = {"ChildrenPowerState"=2,"CurrentPowerState"=2}
    | |   |   | |   "revision-id" = &lt;01000000&gt;
    | |   |   | |   "IOInterruptSpecifiers" = (&lt;1300000007000000&gt;)
    | |   |   | |   "assigned-addresses" = &lt;1008028200000000000092d800000000000002001808028200000000000090d80000000000000100200$
    | |   |   | |   "IOChildIndex" = 2
    | |   |   | |   "built-in" = &lt;00&gt;
    | |   |   | |   "acpi-device" = "IOACPIPlatformDevice is not serializable"
    | |   |   | |   "device-id" = <0f100000> 
    | |   |   | |   "vendor-id" = <86800000> 
    | |   |   | |   "acpi-path" = "IOACPIPlane:/_SB/PCI0@0/P2P0@110000/S2F0@10000"
    | |   |   | |   "subsystem-vendor-id" = &lt;ad150000&gt;
    | |   |   | |   "name" = "ethernet"
    | |   |   | |   "EEPROM Checksum Valid" = Yes
    | |   |   | |   "reg" = &lt;00080200000000000000000000000000000000001008020200000000000000000000000000000200180802020000000000$
    | |   |   | |   "compatible" = &lt;"pci15ad,750","pci8086,100f","pciclass,020000"&gt;
    | |   |   | | }
    | |   |   | | 
    | |   |   | +-o AppleIntel8254XEthernet  &lt;class AppleIntel8254XEthernet, !registered, !matched, active, busy 0, retain 6&gt;
    | |   |   |   | {
    | |   |   |   |   "IOProbeScore" = 10000
    | |   |   |   |   "Driver Parameters" = {"TxQueueSize"=4096,"RxAbsoluteTimer1000"=64,"Offload TCP/IP Checksum"=Yes,"EnableL$
    | |   |   |   |   "CFBundleIdentifier" = "com.apple.driver.AppleIntel8254XEthernet" 
    | |   |   |   |   "IODefaultMedium" = "00000020" 
    | |   |   |   |   "IOSelectedMedium" = "00000020"
    | |   |   |   |   "IOMatchCategory" = "IODefaultMatchCategory"
    | |   |   |   |   "IOLinkSpeed" = 1000000000
    | |   |   |   |   "IOPowerManagement" = {"CurrentPowerState"=1}
    | |   |   |   |   "IOVendor" = "Intel"
    | |   |   |   |   "IOPacketFilters" = {"IONetworkFilterGroup"=275,"IOEthernetWakeOnLANFilterGroup"=0}
    | |   |   |   |   "IOMACAddress" = &lt;000c29691726&gt;
    | |   |   |   |   "IOProviderClass" = "IOPCIDevice" 
    | |   |   |   |   "IOFeatures" = 10
    | |   |   |   |  <span style="background-color:rgb(180,167,214)"> "IOPCIClassMatch" = "0x02000000&0xffff0000" </span>
    | |   |   |   |   "IOLinkStatus" = 3
    | |   |   |   |   "IOMaxPacketSize" = 9018
    | |   |   |   |   "IOMinPacketSize" = 64
    | |   |   |   |   "IOMediumDictionary" = {"00500023"={"Type"=5242915,"Index"=6,"Flags"=0,"Speed"=10000000},"00100026"={"Typ$
    | |   |   |   |  <span style="background-color:rgb(159,197,232)"> "IOPCIPrimaryMatch" = "0x10008086&0x0000ffff" </span>
    | |   |   |   |   "IOModel" = "82545EM Copper" 
    | |   |   |   |   "IOClass" = "AppleIntel8254XEthernet" 
    | |   |   |   |   "IOActiveMedium" = "00100030"
    | |   |   |   |   "EN Number" = 0
    | |   |   |   | }
    | |   |   |   | 
    | |   |   |   +-o IOEthernetInterface  &lt;class IOEthernetInterface, registered, matched, active, busy 0, retain 10&gt;
    | |   |   |     | {
    | |   |   |     |   "IOMediaAddressLength" = 6
    | |   |   |     |   "IOPrimaryInterface" = Yes
    | |   |   |     |   "IOInterfaceType" = 6
    | |   |   |     |   "IORequiredPacketFilters" = {"IONetworkFilterGroup"=19,"IOEthernetWakeOnLANFilterGroup"=0}
    | |   |   |     |   "IOInterfaceFlags" = 34915
    | |   |   |     |   "IOInterfaceExtraFlags" = 1073744192
    | |   |   |     |   "IOInterfaceUnit" = 0
    | |   |   |     |   "IONetworkData" = {"IOEthernetStatsKey"={"Size"=216,"Data"=&lt;0000000000000000000000000000000000000000000$
    | |   |   |     |   "BSD Name" = "en0"
    | |   |   |     |   "IOLocation" = ""
    | |   |   |     |   "IOMaxTransferUnit" = 1500
    | |   |   |     |   "IOInterfaceNamePrefix" = "en"
    | |   |   |     |   "IOBuiltin" = Yes
    | |   |   |     |   "IOActivePacketFilters" = {"IONetworkFilterGroup"=19,"IOEthernetWakeOnLANFilterGroup"=0}
    | |   |   |     |   "IOMulticastAddressList" = &lt;01005e0000fb01005e0000013333000000fb33333e2cf1a83333000000013333ff691726&gt;
    | |   |   |     |   "IOInterfaceState" = 3
    | |   |   |     |   "IOMediaHeaderLength" = 14
    | |   |   |     |   "IOControllerEnabled" = Yes
    | |   |   |     | }
    | |   |   |     | 
    | |   |   |     +-o IONetworkStack  &lt;class IONetworkStack, registered, matched, active, busy 0, retain 7&gt;
    | |   |   |       | {
    | |   |   |       |   "IOProviderClass" = "IOResources"
    | |   |   |       |   "IOMatchCategory" = "IONetworkStack"
    | |   |   |       |   "IOProbeScore" = 0
    | |   |   |       |   "IOClass" = "IONetworkStack"
    | |   |   |       |   "CFBundleIdentifier" = "com.apple.iokit.IONetworkingFamily"
    | |   |   |       |   "IOResourceMatch" = "IOBSD"
    | |   |   |       | }
    | |   |   |       | 
    | |   |   |       +-o IONetworkStackUserClient  &lt;class IONetworkStackUserClient, !registered, !matched, active, busy 0, ret$
    | |   |   |           {
    | |   |   |           }



A // with its Info.plist (.. file) can be established:

[...]
&lt;dict&gt;

> `<key>CFBundleIdentifier</key>`
> ``
>
> > `<key>IOClass</key>`
> > `AppleIntel8254XEthernet`
> > `<key>IODefaultMedium</key>`
> > `00000020`
> > `<key>IOPCIClassMatch</key>`
> > <span style="font-family:courier new,monospace;font-size:small"><string>0x02000000&0xffff0000</string></span>
> > `<key>IOPCIPrimaryMatch</key>`
> > <span style="font-family:courier new,monospace;font-size:small"><string>0x10008086&0x0000ffff</string></span>
> > `<key>IOProviderClass</key>`
> > `IOPCIDevice`
> 
``

### a KEXT pseudo-life
The driver inspects and configure the PCI Device
1.  driver examines the values in the PCI configuration space registers (e.g., revision ID register)
2.  driver sets some value of them (e.g., enable memory write)
3.  driver interacts with its device

(random notes: ipconfig set en0 NONE before kextunload &lt;- not tested)




Pseudo-pre-deduction: If the kext is loaded but no interface, could it be?:

`start`{style="font-size:11px;font-family:Monaco,Courier,Consolas,monospace"}
:   The `start`{style="font-size:11px;font-family:Monaco,Courier,Consolas,monospace"} function should initialize the device to a working state. It also needs to create a network object and make it visible to the networking stack as an interface
    
    
network driver's start function:
-   set network interface object
-   a work loop
-   an output queue
-   specific resources
-   (also retains its provider nub (IOPCIDevice?))

In order to open the Provider nub, the driver should:
1.  verify that it is of the appropriate class
2.  retain a reference to it
3.  open it in order to access its services



****
### Host NIC

Restarts all the vmnet services on the **host side**:

`/Library/Application Support/VMware Fusion/boot.sh --restart`
Troubleshooting
---------------
### On read-only medium
The tty is flooded with log telling attempt to write on a read-only medium (ie: auth mechanism too) does not work.
**** Another obvious implicit goal is to install PureDarwin with PureDarwin.
****
### Random log
`Aug 28 18:58:15.129: vmx| Licensecheck: Invalid license file.`
`Aug 28 18:58:15.131: vmx| Host: SRAT tables not found in memory`
`
`

`Aug 28 18:58:15.480: vmx| Topology discovery error: /Library/Preferences/com.apple.windowserver.plist doesn't contain expected key.`
`
`

`Aug 28 18:58:15.742: vmx| DISK: Disabling unbuffered I/O on ide0:0 to work around Apple bugs 5679432 and 6048690.`
`
`

`Sep 27 11:52:13.472: vmx| PTSC: failed to read the TSCs.`
`
`

`Sep 27 11:52:17.727: vmx| Error: Encountered Apple bug #5202831.  Disconnecting.`
`
`

`Sep 27 11:52:36.086: vcpu-0| CDROM ide1:0: CMD 0xad (*UNKNOWN (0xad)*) FAILED (key 0x5 asc 0x24 ascq 0)`

Resources
---------
ftp://download.intel.com/design/network/specupdt/82545em.pdf
http://www.intel.com/design/network/products/lan/docs/82545.htm
http://download.intel.com/design/network/manuals/8254x_GBe_SDM.pdf

http://downloadcenter.intel.com/Detail_Desc.aspx?agr=Y&ProductID=990&DwnldID=3294&strOSs=52&OSFullName=FreeBSD*&lang=eng
FreeBSD* 4.7 to 4.10 driver for all Intel® PRO/1000 gigabit Ethernet adapters. Valid for the 82540, 82542, 82543, 82544, **82545**, 82546 and 82547 controllers. 


http://developer.apple.com/documentation/DeviceDrivers/Conceptual/NetworkDriver/1_Intro/Intro.html
http://developer.apple.com/documentation/DeviceDrivers/Conceptual/NetworkDriver/4_Writing%20the%20Driver/NetworkController.html

<http://developer.apple.com/documentation/HardwareDrivers/Conceptual/HWTech_Ethernet/Introduction/ENet_intro.html>
<http://developer.apple.com/documentation/Hardware/Conceptual/HWtech_PCI/Articles/pci_implementation.html>
<http://developer.apple.com/documentation/Darwin/Conceptual/NetworkKernelExtensions/about/about.html>
<http://developer.apple.com/documentation/Darwin/Conceptual/KEXTConcept/KEXTConceptIntro/KEXTIntro.html>
<http://developer.apple.com/documentation/DeviceDrivers/Conceptual/WritingPCIDrivers/pci_device/pci_device.html>
<http://download.intel.com/design/network/manuals/8255X_OpenSDM.pdf>

<https://code.google.com/p/pcnet32-driver-for-puredarwin/> - **information about this driver still needs to be worked into this page**