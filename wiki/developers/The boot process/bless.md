bless
=====
bless is the command used on Mac OS X to make volumes bootable.
This page discusses the bless command and its applicability in a PureDarwin system.

It is a work in progress; please contribute.

### What is bless

bless is a command line tool on Mac OS X and Darwin to make volumes bootable.
It also includes libbless, a library which is used by other applications (such as installers) to make volumes bootable.
The bless project is available as Open Source from Apple.

### "Worlds" supported by bless

#### efiboot

The bless command is used to set up the "efiboot" boot loader on Intel-based Macintosh systems which use EFI as their firmware.

(to be written)

#### boot

The bless command was used to set up the "boot" boot loader on generic BIOS-based systems in older versions of Darwin.

bless-24 was known to work with BIOS-based machines.
It appears that bless-37.1.4 from 2006 was the latest version that contained BIOS code.
Later versions of bless are no longer capable of blessing a volume so that it works on BIOS-based machines.

``` 
 *  Revision 1.21  2006/01/02 22:27:28  ssen
 *  <rdar://problem/4395370> bless should not support BIOS systems
 *  For RC_RELEASE=Leopard, keep BIOS support, but preprocess it out
 *  for Herbie and the open source build
```

(Maybe the BIOS-related portions of the code should be patched back in by PureDarwin.)

(to be written)

#### BootX

Was used to set up the "BootX" boot loader on "New World" and "Old World" PowerPC computers which used OpenFirmware as their firmware. Not relevant for PureDarwin.

### Using bless

The usage of the bless command varies depending on which "world" you are targeting. Please refer to the bless manpage that comes with the bless command.

### bless alternatives

A method to make a disk bootable on BIOS and EFI machines without using the bless command is described on the [boot](https://github.com/PureDarwin/PureDarwin/wiki/boot) page.

### References

-   http://src.gnu-darwin.org/DarwinSourceArchive/expanded/bless/bless-37.1.4/libbless/BIOS/