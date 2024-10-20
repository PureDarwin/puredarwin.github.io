# Generic platform kext for PureDarwin

Reader Rafirafi sent us source code for a new kext, `ClockRTC`, and patches that make it possible to use `Apple8259PIC-6`, `AppleI386GenericPlatform-5`, `AppleI386PCI-6` with PureDarwin on generic hardware (only tested on QEMU). He thinks this will be useful for people who are interested in running Darwin without proprietary kexts. Note, however, that this is not a full ACPI platform kext and it will likely only work on QEMU.

`GenericPlatform-10` is available at https://github.com/PureDarwin/LegacyDownloads/releases/tag/GPKE10
