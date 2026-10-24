# Secure Boot

The `-sb` images boot with Secure Boot turned on. They start through a shim signed by
Microsoft's third-party UEFI CA. The shim then checks the PureDarwin loader against the
PureDarwin certificate, which you enroll once per machine. After that, the machine boots
`-sb` images like any other operating system.

If you would rather turn Secure Boot off, the ordinary images work too. Nothing on this
page is needed in that case.

## What You Need

* An `-sb` image, for example `puredarwin-25.5-gpu-sb.img`.
* Firmware that trusts Microsoft's third-party UEFI CA. Most PCs do by default. Some
  laptops ship with it turned off. The setting is usually called "Allow Microsoft 3rd
  Party UEFI CA" or similar, under the Secure Boot menu. Turn it on.
* A USB keyboard or the built-in keyboard. MokManager runs before any PureDarwin driver.

## Enroll the PureDarwin Certificate

You do this once. The certificate stays in the firmware's MOK list across reboots and
across new images.

1. Write the `-sb` image to a USB stick, and run `sync` before you unplug it.
2. Boot from the stick with Secure Boot on.
3. The shim reports that it cannot verify the loader, usually as
   `Verification failed: (0x1A) Security Violation`. This is expected on the first boot.
   Press Enter. MokManager opens.
4. Choose **Enroll key from disk**.
5. Pick the stick's EFI partition, then `EFI`, then `BOOT`, then `PUREDARWIN.cer`.
6. Choose **Continue**, then **Yes** to enroll it.
7. Choose **Reboot**.

From the next boot on, the shim accepts the loader and PureDarwin starts without stopping
in MokManager.

## What Is on the EFI Partition

| File | Role |
| --- | --- |
| `EFI/BOOT/BOOTX64.EFI` | The shim, signed by Microsoft |
| `EFI/BOOT/grubx64.efi` | The PureDarwin loader, signed with the PureDarwin key. The shim loads it by this name |
| `EFI/BOOT/mmx64.efi` | MokManager |
| `EFI/BOOT/PUREDARWIN.cer` | The certificate you enroll |
| `EFI/BOOT/BOOTIA32.EFI`, `grubia32.efi`, `mmia32.efi` | The same chain for 32-bit UEFI firmware |

The 32-bit chain uses Debian's signed shim. It is new and has had less testing than the
64-bit one.

## Removing the Certificate

From MokManager, choose **Delete MOK** and select the PureDarwin certificate. From Linux,
`mokutil --list-enrolled` shows it, and `mokutil --delete` with the certificate file removes
it on the next reboot.

## When It Does Not Work

**The Security Violation screen comes back after enrolling.** The certificate was not
enrolled. Repeat the steps and make sure to confirm with **Yes**. Some firmware also clears
the MOK list when Secure Boot settings are reset.

**The firmware refuses the stick before the shim runs.** The firmware does not trust
Microsoft's third-party CA. Turn on the setting described above, or turn Secure Boot off.

**It boots, then stops early.** That is no longer a Secure Boot problem. See
[What a Healthy Boot Looks Like](hardware.md#what-a-healthy-boot-looks-like).
