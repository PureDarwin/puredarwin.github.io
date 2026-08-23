# Boot chain

What happens between power-on and a shell prompt.

## 1. Firmware to loader

UEFI firmware (OVMF on x86_64, AAVMF on arm64) finds `\EFI\BOOT\BOOTX64.EFI` on the EFI
system partition. That is `xnu-loader`, PureDarwin's bootloader. Apple's `boot.efi` is
not open source, so this is project code.

On the Raspberry Pi and on T8010 the entry point differs: the Pi boots through its own
firmware chain, and T8010 is reached through checkm8 and a modified PongoOS, which
chainloads the kernel with the `pdload`/`pdboot` module.

## 2. Loader work

The loader:

* reads `\EFI\BOOT\boot-args.txt` and parses it into the kernel's boot arguments;
* scans the GPT to find the root volume and derive `boot-uuid`. For an HFS+ root it
  reads the UUID out of the volume header's FinderInfo; for ext4 it uses the partition;
* loads the kernel collection;
* fills in the boot arguments structure, including the framebuffer description the
  firmware handed it, and jumps to the kernel.

The framebuffer handoff is a common source of trouble. On x86 with no serial port, the
loader setting `v_display` to a graphics mode disables the kernel's framebuffer text
console, so you get no output at all; `disable_serial_output` needs `debug=0x8`. On
arm64 the loader fills a 64-bit Video structure and the kernel wants `v_display == 0`.

## 3. Kernel and kexts

The kernel starts, brings up the platform expert for the machine, and loads the kexts
that were linked into the kernel collection. `AppleFileSystemDriver` matches the volume
whose UUID equals `boot-uuid` and publishes `boot-uuid-media`; the filesystem driver
(`ext4.kext` on every current target, or `hfs.kext` on `image-hfs`) mounts it as root.

If the root is a RAM disk, `rd=md0` in the boot-args points the kernel at the md device
the loader populated instead.

## 4. launchd

The kernel execs launchd as PID 1. PureDarwin's launchd and XPC implementation lives in
`src/Libraries/XPC`. Apple's last open source drop was 10.9 Mavericks, which is a long
way behind the Darwin 20 we target, so this is a reimplementation rather than a build of
Apple's sources.

launchd starts the LaunchDaemons in `/System/Library/LaunchDaemons`, which for a
standard image are:

| Daemon | Job |
| --- | --- |
| `com.apple.notifyd` | The notification server, needed by CoreFoundation and much else |
| `org.puredarwin.hostname` | Sets the hostname to `puredarwin` |
| `org.puredarwin.root-remount` | Remounts the root filesystem read-write, the job classic Darwin gave to `/etc/rc` |
| `org.puredarwin.dbus` | The system D-Bus, for the desktop images |

## 5. Console login

`/etc/ttys` contains a single line:

```
/dev/console /bin/zsh -l
```

That gives you a root shell on the console. There is no getty and no login prompt; on a
system with one user and no passwords, a login prompt would only be theatre.

The environment comes from `/etc/zshenv` and `/etc/profile`, which set `PATH`, `TERM`,
`FONTCONFIG_FILE`, the XDG directories, the X locale and cursor paths, and the
gdk-pixbuf loader cache location.

## The generated /etc

All of this is written by `image.nix`, not stored in the repository as files:

* `passwd` and `master.passwd`. Both are needed. Darwin's libinfo reads `master.passwd`
  when euid is 0 and does **not** fall back to `passwd`, so without it every `getpwnam`
  for root fails and D-Bus, login and anything resolving a user break.
* `group`, `hosts`, `fstab` (deliberately empty of a root entry, since the kernel mounts
  root from `boot-uuid`), `services` and `protocols` from iana-etc, `resolv.conf`,
  `shells`, `ttys`.
* `profile`, `zshenv`, `zprofile`, `zshrc`, and `/var/root/.zprofile`.
* Compatibility symlinks in `/usr/lib`: `libc`, `libm`, `libpthread`, `libdl` and
  `libinfo` all point at `libSystem.B.dylib`, as they do on macOS.
* The guest C headers, staged by the libSystem build as `pd-guest-headers/` and moved to
  `/usr/include` here, so cross-built ports never see them but an in-guest compiler
  does.
