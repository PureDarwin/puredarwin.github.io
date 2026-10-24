# Boot Chain

What happens between power-on and the desktop.

## 1. Firmware to Loader

UEFI firmware (OVMF on x86_64, AAVMF on arm64) finds `\EFI\BOOT\BOOTX64.EFI` on the EFI
system partition. That is `xnu-loader`, PureDarwin's bootloader. Apple's `boot.efi` is
not open source, so this is project code.

Other paths lead to the same loader:

* Machines with 32-bit UEFI firmware load `\EFI\BOOT\BOOTIA32.EFI`, the 32-bit build of
  the loader, which the GPU images also carry.
* Secure Boot images put a Microsoft-signed shim at `BOOTX64.EFI`. The shim checks the
  loader's signature against the PureDarwin certificate you enrolled, then starts it.
* The `-legacy` images carry a BIOS boot stack in the MBR for machines without UEFI.
* The loader also boots as a Multiboot2 kernel from GRUB, or through QEMU's `-kernel`.
* The arm64 boards start the loader as a Linux kernel image from their own bootloader.
  The Raspberry Pi boots through its firmware chain. The iPad (T8010) is reached through
  checkm8 and a modified PongoOS, which chainloads the kernel with its `pdload` and
  `pdboot` module.

## 2. Loader Work

The loader:

* reads `\EFI\BOOT\boot-args.txt` and parses it into the kernel's boot arguments.
* scans the GPT to find the root volume and derive `boot-uuid`. For an HFS+ root it reads
  the UUID from the volume header's FinderInfo. For ext4 it uses the partition.
* loads the kernel collection.
* fills in the boot arguments structure, including the framebuffer the firmware handed
  it, and jumps to the kernel.

The loader reads `boot-args.txt` by its long file name. If you edit the file with
`mtools`, write it under the long name. A copy written under the short name
`BOOT-A~1.TXT` loses the long name, and the loader quietly falls back to its built-in
defaults.

The framebuffer handoff is a common source of trouble. On x86 with no serial port, a
loader that sets `v_display` to a graphics mode disables the kernel's framebuffer text
console, and you get no output at all. `disable_serial_output` needs `debug=0x8`. On
arm64 the loader fills a 64-bit Video structure, and the kernel wants `v_display == 0`.

## 3. Kernel and Kexts

The kernel starts, brings up the platform expert for the machine and starts the kexts
linked into the kernel collection. `AppleFileSystemDriver` matches the volume whose UUID
equals `boot-uuid` and publishes `boot-uuid-media`. The filesystem driver (`ext4.kext`
on most images, `hfs.kext` on `image-hfs`, `apfs.kext` on `image-apfs-minimal`) mounts it
as root.

If the root is a RAM disk, `rd=md0` in the boot arguments points the kernel at the md
device the loader filled.

Once root is mounted, the auxiliary kernel collection with the GPU and Wi-Fi drivers is
loaded. See [Kernel Collections](kernel-collections.md).

## 4. launchd

The kernel runs launchd as PID 1. PureDarwin's launchd and XPC live in
`src/Libraries/XPC`. Apple's last open source launchd was the one from Mac OS X 10.9,
far behind the Darwin version PureDarwin targets, so this is the project's own
implementation.

launchd starts the jobs in `/System/Library/LaunchDaemons`. On a standard image these
include:

| Daemon | Job |
| --- | --- |
| `com.apple.notifyd` | The notification server, needed by CoreFoundation and much else |
| `org.puredarwin.hostname` | Sets the hostname to `puredarwin` |
| `org.puredarwin.root-remount` | Remounts the root filesystem read-write, the job classic Darwin gave to `/etc/rc` |
| `org.puredarwin.dmesg-save` | Keeps a copy of the kernel log in `/var/log/dmesg-boot.*.txt` |
| `org.puredarwin.dbus` | The system D-Bus, for the desktop images |

configd, mDNSResponder and diskarbitrationd start the same way. On the desktop images,
the Argon session starts `neuswc`, the menu bar, the Dock and the other desktop
processes.

## 5. Console Login

`/etc/ttys` contains a single line:

```
/dev/console /bin/zsh -l
```

That gives you a root shell on the console, with no getty and no login prompt.

The environment comes from `/etc/zshenv` and `/etc/profile`. They set `PATH`, `TERM`,
`FONTCONFIG_FILE`, the XDG directories, the X locale and cursor paths, and the gdk-pixbuf
loader cache location.

## The Generated /etc

`image.nix` writes all of this. None of it is stored in the repository as files:

* `passwd` and `master.passwd`. Both are needed. Darwin's libinfo reads `master.passwd`
  when euid is 0 and does **not** fall back to `passwd`. Without it every `getpwnam` for
  root fails, and D-Bus, login and anything that resolves a user break.
* `group`, `hosts`, `fstab` (with no root entry, since the kernel mounts root from
  `boot-uuid`), `services` and `protocols` from iana-etc, `resolv.conf`, `shells` and
  `ttys`.
* `profile`, `zshenv`, `zprofile`, `zshrc` and `/var/root/.zprofile`.
* Compatibility symlinks in `/usr/lib`. `libc`, `libm`, `libpthread`, `libdl` and
  `libinfo` all point at `libSystem.B.dylib`, as they do on macOS.
* The guest C headers. The libSystem build stages them as `pd-guest-headers/`, and they
  move to `/usr/include` here. Cross-built ports never see them, and an in-guest
  compiler does.
