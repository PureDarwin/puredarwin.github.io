VirtualBox archive
==================

**as of 2011 January: Virtualbox runs with PureDarwin nano**
**please see: **[http://www.puredarwin.org/developers/virtualbox](developers/virtualbox.html)
**
**
**
**
**the following info is kept here for historical reasons!**
**
**
**
**
**<span style="font-family:Arial,sans-serif;font-weight:normal"></span>**
(Pure)Darwin 9 guest OS **not supported** or it doesn't seem to be trivial to make it works.
No problem concerning loading the bootloader.
Latest versions tested:
-   VirtualBox 3.0.2 on Mac OS X
-   VirtualBox 3.0.6 on Windows XP 32 bits

**
**
**Problem:** black screen at kernel loading (just after kexts decompression), framebuffer unsupported?
Settings {style="text-align:left"}
--------
### VirtualBox random settings
Set up "OS Type" variable as a "FreeBSD" machine.
VT-x/AMD-v is a must.
(ACPI must be disabled)
PAE/NX seems to be needed^1^ and enabled^2^
(please add more text)
#### Physical Address Extension (PAE)
"<span style="font-style:italic">Physical addresses greater than 32 bits are supported:</span>
<span style="font-style:italic">extended page table entry formats, an extra level in the page translation tables is defined, 2-MByte pages are supported instead of 4 Mbyte pages if PAE bit is 1.</span>
<span style="font-style:italic">The actual number of address bits beyond 32 is not defined, and is implementation specific.</span>" said Intel MacCPUID.app.
Boot
----
### Boot arguments
*-v* is not needed since it is enabled by default.
(please add more text)
### dfe bootloader
Note: Pressing *?* + *Enter *doesn't give any output.
![](_/rsrc/1217284235961/developers/virtualbox/virtualbox%20bootloader.png%3Fheight=248&width=420)
#### ?video flag
<span style="font-style:italic">?video</span> works in booter and returns:


[![](_/rsrc/1217701995353/developers/virtualbox/video.png%3Fheight=376&width=420)](developers/virtualbox/video.png%3Fattredirects=0)


<span style="text-decoration:underline">Note:</span> Passing kernel flag "Graphics Mode"="&lt;value&gt;" also seems to work.
#### ?memory flag

[![](_/rsrc/1217702113592/developers/virtualbox/memory.png%3Fheight=79&width=420)](developers/virtualbox/memory.png%3Fattredirects=0)

A bit obscure...
<span style="color:rgb(255,0,0)">Please let us know if you know about.</span>
#### SMBIOS table not found
Then it fails, attempting to find SMBIOS table.
![](_/rsrc/1217285927363/developers/virtualbox/UnableToFindSMBIOSTable.png%3Fheight=264&width=420)
<span style="border-collapse:separate;font-family:Verdana;font-size:12px;line-height:18px"></span>
After using booter <span style="font-style:italic">boot-132_dfe_r146</span> (instead of <span style="font-style:italic">dfe_r28</span> version) from David Elliott, another problematic error is raised about determination of CPU:FSB multiplier (0 is found...).

![](_/rsrc/1217620838320/developers/virtualbox/CPU_FSB_multiplier_equal_0.png%3Fheight=264&width=420)
Pressing 'y' leads irremediably to a (resized) blank screen, full cpu load, and a critical error forcing to poweroff the vm.
See corresponding VirtualBox log of pressing 'y':

<span style="font-family:courier new,monospace"><span style="font-size:small">00:00:03.572 Display::handleDisplayResize(): uScreenId = 0, pvVRAM=184d9000 w=640 h=480 bpp=32 cbLine=0xA00
00:00:05.906 Guest Log: Key pressed: 0086
00:00:05.942 Display::handleDisplayResize(): uScreenId = 0, pvVRAM=00000000 w=720 h=400 bpp=0 cbLine=0x0</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">00:00:09.600 Guest Log: Key pressed: 002E</span></span>

<span style="font-weight:bold"><span style="color:rgb(255,0,0)">Please, let us know if you have a solution.</span></span>
### Chameleon bootloader and Voodoo kernel
<span style="font-weight:bold"><span style="color:rgb(255,0,0)"><span style="color:rgb(0,0,0);font-weight:normal">Other attempts have been made, combining xnu-dev kernel (Voodoo BETA 2b ) and chameleon bootloader (v1.0.11).</span></span></span>
We can bypass the error above about CPU:FSB multiplier with the boot argument <span style="font-style:italic">busratio=...</span>


[![](_/rsrc/1226191734836/developers/virtualbox/Virtualbox%20voodoo%20chameleon%20bootloader.png%3Fheight=263&width=420)](developers/virtualbox/Virtualbox%20voodoo%20chameleon%20bootloader.png%3Fattredirects=0)


With ACPI enabled in VirtualBox, the vm hangs at "Local APIC version not 0x14 as expected":

[![](_/rsrc/1226191756456/developers/virtualbox/Virtualbox%20voodoo%20chameleon%20ACPI.png%3Fheight=122&width=420)](developers/virtualbox/Virtualbox%20voodoo%20chameleon%20ACPI.png%3Fattredirects=0)

Without ACPI, it complains about and irremediably lead to a kernel panic.
<span style="font-weight:bold"></span>
[![](_/rsrc/1226191822137/developers/virtualbox/Virtualbox%20voodoo%20chameleon%20NOACPI.png%3Fheight=239&width=420)](developers/virtualbox/Virtualbox%20voodoo%20chameleon%20NOACPI.png%3Fattredirects=0)<span style="font-weight:normal">
</span>
### Troubleshooting
Problem: <span style="font-weight:normal">"Unable to find SMBIOS table"
</span>Solution 0: <span style="font-weight:normal">So, need another BIOS (with correct offset)?</span>

<span style="font-weight:normal">Another solution would be to use the host SMBIOS table, or a copy of it.
</span><span style="font-weight:normal">See <http://www.virtualbox.org/ticket/1751> for more information.
</span>Solution 1: <span style="font-weight:normal">It's still remain possible to modify and recompile the VirtualBox sources in order to give a correct SMBIOS.
</span><span style="font-weight:normal">See VirtualBox/src/VBox/Devices/PC/DevPcBios.cpp
</span>
Solution 2: use another kernel (xnu-dev) and/or another bootloader (chameleon)
#### Machine Specific Registers (MSR)About MSR?
"The processor provides a variety of machine specific registers (accessed via the RDMSR and WRMSR instructions) that are used to control and report on processor performance. Virtually all MSRs handle system related functions and are not accessible to an application program. One exception to this rule is the time-stamp counter." said Intel MacCPUID.app.
#### CPU:FSB multiplier
According to Wikipedia: "*The clock multiplier (or CPU multiplier or bus/core ratio) is the ratio of the internal CPU clock rate to the frequency of its external address/data bus, today often termed front side bus(FSB). A system with a CPU multiplier of 10x will have its CPU execute 10 complete cycles for every cycle of its FSB. For example, a system with an FSB running at 133 MHz and a clock multiplier of 10x, the CPU will run at 1.33 GHz*."

CPU model seems OK:

<span style="font-family:courier new,monospace"><span style="font-size:small">00:00:02.889 Full Name:                       Intel(R) Core(TM)2 CPU         T7400  @ 2.16GHz</span></span>
#### T7400 specs example
-   <span style="font-weight:bold">FSB:</span> 667 Mhz
-   <span style="font-weight:bold">Multiplier:</span> 13x
#### Auto resize and blank screen
The highlighted line could explain why suddenly the screen is auto resized, and consequently why the screen goes blank.
*<span style="font-style:normal"></span>*

<span style="font-family:courier new,monospace"><span style="color:rgb(153,153,153)"><span style="font-size:small">00:00:09.666 Guest Log: BIOS: Booting from CD-ROM...</span></span></span>
*<span style="font-style:normal"></span>*
<span style="font-family:courier new,monospace"><span style="font-size:small">00:00:58.579 Display::handleDisplayResize(): uScreenId = 0, pvVRAM=184d9000 w=1024 h=768 bpp=32 cbLine=0x1000</span></span>
<span style="font-family:courier new,monospace"><span><span style="font-size:small">00:00:58.608 VERR_REM_TOO_MANY_TRAPS -&gt; uTrap=d error=6a next_eip=ffe01890 eip=ffe01890 cr2=ffe01890</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(153,153,153)"><span style="font-size:small">00:00:58.608 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(153,153,153)"><span style="font-size:small">00:00:58.608 !!</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(153,153,153)"><span style="font-size:small">00:00:58.608 !!                 Guru Meditation -2304 (VERR_REM_TOO_MANY_TRAPS)</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(153,153,153)"><span style="font-size:small">00:00:58.608 !!</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(153,153,153)"><span style="font-size:small">00:00:58.608 !!</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(153,153,153)"><span style="font-size:small">00:00:58.608 !! {mappings, &lt;NULL&gt;}</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(153,153,153)"><span style="font-size:small">00:00:58.608 !!</span></span></span>
<span style="font-family:courier new,monospace"><span style="color:rgb(153,153,153)"><span style="font-size:small">00:00:58.608 </span></span></span>
 

<span style="font-size:20px;font-weight:bold">Footnotes</span>
^1^Why PAE/NX seems to be needed?
[![](_/rsrc/1217285973856/developers/virtualbox/ExperimentalPAE.png)](developers/virtualbox/ExperimentalPAE.png%3Fattredirects=0)
^2^How to enable PAE/NX?
Via command-line, assuming <span style="font-family:courier new,monospace"><span style="font-size:small">PureDarwin</span></span> is the name of your vm:
<span style="font-family:courier new,monospace"><span style="font-size:small">/Applications/VirtualBox.app/Contents/MacOS/</span><span style="font-size:small">VBoxManage modifyvm PureDarwin -pae on
</span></span>Via gui, a simple checkbox in the settings.
Ressources
----------
<http://alex.csgraf.de/self/?part/projects&folder/Qemu%20OSX&type/&project/projects&parameters/id=Qemu%20OSX/qemu>
<http://www.virtualbox.org/ticket/1071>
<http://www.virtualbox.org/ticket/1751> (Allow SMBIOS information to be copied from host)
<http://softwarecommunity.intel.com/articles/eng/1107.htm> (MacCPUID.app)


<http://code.google.com/p/xnu-dev> / (A fork of the XNU kernel)


