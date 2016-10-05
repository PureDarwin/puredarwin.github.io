Platform Expert
===============
The Platform Expert is a vital part of the Darwin kernel environment. It contains the hardware abstraction layer, that is hardware specific parts of the kernel space. The Platform Expert for Intel machines is contained in AppleACPIPlatform.kext, which is available under the Apple Binary Driver License.
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** What the Platform Expert does](pe.html#TOC-What-the-Platform-Expert-does)
2.  [**2** Known issues with AppleACPIPlatformExpert](pe.html#TOC-Known-issues-with-AppleACPIPlatformExpert)
3.  [**3** Other Platform Experts](pe.html#TOC-Other-Platform-Experts)
4.  [**4** Specify which Platform Expert to use](pe.html#TOC-Specify-which-Platform-Expert-to-use)
5.  [**5** Generic Platform](pe.html#TOC-Generic-Platform)

### What the Platform Expert does
You can basically think of the Platform Expert as a "driver for the logic board". As such, it can roughly be compared to the Hardware Abstraction Layer (HAL) of other operating systems. The Platform Expert initializes the data structures that the [I/O Kit](http://developer.apple.com/documentation/DeviceDrivers/Conceptual/IOKitFundamentals/Introduction/chapter_1_section_1.html) needs. Specifically, it creates the root node of the device tree in the [I/O Registry](http://developer.apple.com/documentation/DeviceDrivers/Conceptual/IOKitFundamentals/TheRegistry/chapter_4_section_2.html), which all other nodes attach to. As such, it is a fundamental part of the Darwin kernel environment. The Platform Expert also handles kernel flags (such as cpus=1), registers interrupt, scans the system for devices, and drives the text console. In the XNU source code, the Platform Expert is referred to as <span style="font-family:-webkit-monospace;white-space:pre">pexpert</span>. 
### Known issues with AppleACPIPlatformExpert
AppleACPIPlatform.kext, which is available for use with Darwin under the Apple Binary Driver License in binary-only form, has been written specifically with Intel-based Macs in mind. Apparently little to no testing has been done to ensure that it is compatible with other hardware. Over time, the AppleACPIPlatformExpert has become more and more strict about some hardware features it assumes to be present. For example, [ACPI tables](http://www.acpi.info/), such as DSDTs, are assumed to follow Apple's standards. If the machine does not follow Apple's standards in the ACPI tables, this can create undesired effects. For example, it results in some multi-core machines crashing whenever xnu is loaded without the cpus=1 kernel flag. It might also result in unforeseen behavior in the area of power management.
### Other Platform Experts
Various PowerPC Platform Experts are available. For the i386 architecture, only two Platform Experts are of interest: AppleACPIPlatformExpert (mentioned above) and AppleI386GenericPlatform, which is Open Source but only available and working up to Darwin 8. If one wanted to use it with Darwin 9, one would have to modify it.
### Specify which Platform Expert to use
The platform=ACPI kernel flag tells the kernel to load the Platform Expert which matches "ACPI", if available. This is AppleACPIPlatform.kext, since it's Info.plist looks like this:
    <key>IONameMatch</key>
    <string>ACPI</string>
### Generic Platform
    Update 7/2012: Reader Rafirafi sent us source code for a new kext, ClockRTC, and patches that make it possible to use Apple8259PIC-6, AppleI386GenericPlatform-5, AppleI386PCI-6 with PureDarwin on generic hardware (only tested on QEMU). He thinks this will be welcome for people who are interested in running Darwin without proprietary kexts. Note, however, that this is not a full ACPI platform kext and it will likely only work on QEMU.
    GenericPlatform-1 is available on the Downloads page.
