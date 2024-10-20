The boot process
================
This page describes the boot process of a Darwin 9 system.
This is a first draft, please feel free to contribute.

### Single-user (-s/cmd-S)
This is a top-level overview about the Darwin 9 boot process in single-user mode.


[![](http://sites.google.com/a/puredarwin.org/puredarwin/developers/booting/Bild%207.png)](http://sites.google.com/a/puredarwin.org/puredarwin/developers/booting/Bild%207.png)
(Source: PureDarwin)

During single-user boot, the following things happen: (please add to the list)
The firmware (either BIOS or EFI) initializes the hardware
-   On BIOS machines, the screen is black and shows white text during this process
-   On EFI machines, the screen is gray and shows nothing during this process (this applies to Intel Macs, other EFI machines might have other implementations)
The boot loader is loaded by the firmware
-   On BIOS machines, [boot](booting/boot.html) is loaded and a boot-132 message is shown
-   On EFI machines, [efiboot](booting/efiboot.html) is loaded and an Apple logo but no spinner is shown (this applies to Intel Macs, other EFI machines might have other implementations)
The boot loader reads /Library/Preferences/SystemConfiguration/com.apple.Boot.plist
-   If the file is not present, the boot loader prints an error message
The boot loader loads XNU and the kernel extensions (kexts)
-   On BIOS machines, a spinning star or a list of kexts being loaded is shown
-   On EFI machines, an Apple logo but no spinner is shown (this applies to Intel Macs, other EFI machines might have other implementations)
XNU is loaded
-   If the essential KEXTs (especially the Platform Expert, which is in AppleACPIPlatform.kext) were loaded successfully as well, the kernel starts and prints a copyright message mentioning University of California at Berkeley
XNU loads KEXTs (for the first time; those with [OSBundleRequired](http://developer.apple.com/documentation/Darwin/Conceptual/KEXTConcept/KEXTConceptLoading/loading_kexts.html#//apple_ref/doc/uid/20002369-97632-BABIAICJ) set to "Root") and waits for the root device
-   If the root device can be accessed using the available kexts, the kernel prints the message "Got root device"; at some point thereafter the rest of the KEXTs are loaded (those without [OSBundleRequired](http://developer.apple.com/documentation/Darwin/Conceptual/KEXTConcept/KEXTConceptLoading/loading_kexts.html#//apple_ref/doc/uid/20002369-97632-BABIAICJ) set to "Root")
-   If the root device cannot be accessed using the available kexts, the message reads "Still waiting for root device..." instead
The kernel starts /sbin/launchd on the root device
launchd starts /bin/launchctl
launchctl starts /bin/bash
### Multi-user
Same procedure as described above for single-user boot, but instead of the last step ("launchctl starts /bin/bash") the following happens:
-   ...
(Please write text here)
### Netbooting (-n/cmd-N)
Same procedure as described above for single-user boot, but instead of the last step ("launchctl starts /bin/bash") the following happens:
-   ...
(Please write text here)

