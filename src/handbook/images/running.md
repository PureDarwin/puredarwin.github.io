# Running in QEMU

The flake ships runners so you do not have to remember QEMU invocations. Each is a `nix
run` app.

## nix run .#vm

The default. Portable, no KVM required.

```
qemu-system-x86_64 -M q35 -m 4096 -smp 4 -vga std \
  -cpu IvyBridge,vendor=GenuineIntel \
  -fw_cfg name=opt/ovmf/X-PciMmio64Mb,string=2048 \
  OVMF code and vars as pflash \
  -drive id=root,format=raw,file=<image> \
  qemu-xhci with USB keyboard and mouse \
  intel-hda with hda-duplex \
  -serial mon:stdio -no-reboot -no-shutdown
```

Notes on the choices: `IvyBridge` because TCG works on some CPU models and dies on
others, and this is a confirmed good one (see [Running on real hardware](hardware.md));
`-vga std` because virtio-gpu in Blt-only mode gives no early framebuffer; the extra PCI
MMIO window because the default is too small for what the firmware wants to map; and
`-no-reboot -no-shutdown` so a panic leaves the machine sitting there for you to read.

## nix run .#kvm

Same system, accelerated, and set up for day-to-day use.

```
-machine q35,accel=kvm -cpu host -vga std
virtio-net with hostfwd tcp::2222-:22
```

The disk controller is selectable with `PUREDARWIN_VM_DISK`: the default is AHCI
(ich9-ahci with an ide-hd), or `virtio-blk-pci`. Being able to switch matters, because
the two exercise completely different driver paths.

With the network forward in place you can `ssh -p 2222 root@localhost` into the guest
once sshd is running.

## nix run .#arm64-virt

```
qemu-system-aarch64 -machine virt,gic-version=3 -cpu neoverse-n2 \
  -smp 4 -m 4096 -boot order=c,strict=on \
  AAVMF code and vars as pflash \
  -device virtio-blk-pci,bootindex=1 \
  -device ramfb \
  virtio-net-pci with hostfwd tcp::2223-:22 \
  qemu-xhci keyboard and mouse \
  -display none
```

`neoverse-n2` rather than `max` is deliberate. `-cpu max` crashes the EDK2 firmware
before it produces any output at all, which looks exactly like a dead serial port and
wasted a lot of time once. `ramfb` is the display that works; the virt machine also
needs the xHCI keyboard for input.

## nix run .#arm64-uefi and .#arm64-uboot

Two alternative arm64 paths kept for bringup work: a `virtio-gpu-pci` and GTK display
variant, and a U-Boot boot rather than UEFI.

## Environment variables

| Variable | Effect |
| --- | --- |
| `PUREDARWIN_IMAGE` | Image to boot. Otherwise the runner looks for `./puredarwin.img` then `./result/puredarwin.img` |
| `PUREDARWIN_VM_MEMORY` | Guest RAM in MB |
| `PUREDARWIN_VM_SMP` | CPU count |
| `PUREDARWIN_VM_VGA` | VGA device |
| `PUREDARWIN_VM_DISK` | `ahci` or `virtio` (kvm runner) |
| `PUREDARWIN_VM_STATE_DIR` | Where OVMF variables are kept, default `./.puredarwin-vm` |
| `PUREDARWIN_OVMF_CODE`, `PUREDARWIN_OVMF_VARS`, `PUREDARWIN_OVMF_VARS_TEMPLATE` | Override the firmware |

A read-only image (a `result` symlink into the Nix store) is opened with `snapshot=on`
automatically, so you can boot a store path without copying it first.

## Working with a writable image

For anything that needs to persist, copy the image out of the store, or drive a qcow2
overlay on top of it. An overlay is the better default when you are iterating: it keeps
the pristine image intact and throwing away the overlay is a clean reset.
