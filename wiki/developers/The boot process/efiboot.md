efiboot
=======
The efiboot project contains boot.efi, the bootloader that is used in Intel Macs to boot the system. 

### What is boot.efi 
boot.efi is a Universal EFI binary with 2 architectures, i386 and x86_64.
It can be used to boot Intel-based Macintosh computers with both 32-bit (e.g., first-generation MacBook Pro) and 64-bit firmwares (e.g., Santa Rosa MacBook Pro).  

### Requirements
efiboot requires EFI to work.  
Computers that do not have EFI need to use other bootloaders, such as boot.  
To use efiboot, you need:
-   An Intel-based Macintosh (or another computer with EFI that can read HFS+; no such computer is known)
-   A HFS+ volume containing a Darwin system
-   efiboot
-   `bless`

### Installation
To make a volume bootable through EFI, efiboot needs to be installed.  
Simply copying boot.efi, however, is not sufficient.  
To make it work, there are basically two options: 
  - Blessing the volume
  - moving boot.efi to a special, UEFI-specified location (to be verified)

#### Blessing the volume
Assuming your Darwin volume is mounted to $MOUNT, do:  
`"$MOUNT/usr/sbin/bless" -verbose -folder "$MOUNT/System/Library/CoreServices" -bootinfo -bootefi`  
The above command implements an Xinfo cache for PowerPC processors which is not needed in the case of an Intel-based Macintosh.

For PureDarwin a simplified command can be used that will bless for only EFI based Macintosh computers:  
`"$MOUNT/usr/sbin/bless" --folder "$MOUNT/System/Library/CoreServices" -bootefi --verbose`

The volume should now be bootable.

#### Moving boot.efi to UEFI-specified location
The firmware of Intel-based Macintosh computers implement sections 3.1 and 3.2 of the UEFI 2.0 specification.
UEFI 2.0 defines that the firmware looks for an EFI bootloader at the following locations:
-   /EFI/BOOT/BOOTX64.EFI
-   /EFI/BOOT/...
of FAT16-formatted volumes. Whether this can also be used to boot a Darwin system from a HFS+ volume needs to be verified.

### Using boot.efi in VirtualBox
EFI emulation in [VirtualBox](../virtualbox.html) 4 is capable of loading and executing boot.efi as the bootloader. Hence boot-132 or its derivatives are no longer needed in VirtualBox. We were able to boot PureDarwinNano.iso this way.

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/boot.efi.png)