# arm64 QEMU virt

The arm64 development target. Boots to a shell.

## Building

```
nix build .#kernel-arm64-virt      # or -debug
nix build .#kexts-arm64
nix build .#kc-arm64
nix build .#image-arm64-virt-minimal
nix run .#arm64-virt
```

`userland-arm64` and the ports with an `-arm64` suffix supply the guest software.
`image-arm64-virt-wayland` adds a Wayland session.

## State

Boots to a shell from an ext4 root, with the platform expert, the GIC, the virtio devices
and xHCI input working. FreeBSD's e1000 driver runs here too and gets a DHCP lease.

## Machine Notes

**Use `-cpu neoverse-n2` or `cortex-a710`.** With `-cpu max`, the EDK2 firmware crashes
before printing anything. That looks like a silent serial port and a loader problem, and
it is neither.

**Use `-M virt,gic-version=3`.** The platform expects a GICv3.

**16K page granule.** The virt target uses 16K pages. That touches L2 block congruence,
the trustcache, `segLOWEST` handling and the TSD layout, all of which had to be fixed to
get here.

**Display is ramfb.** The loader fills a 64-bit Video structure, and the kernel wants
`v_display == 0`. The virt machine also needs the xHCI keyboard for input.

**Timer interrupts.** The timer interrupt has to be routed as Group 0, delivered as an
FIQ. Routed any other way, the system stalls before reaching a shell.

## Root Filesystem Options

Two shapes are available. `image-arm64-virt` is a normal disk image.
`image-arm64-virt-minimal` uses a 512 MB RAM disk with `rd=md0`. It is faster to iterate
on, and it is the shape shared with the netboot and T8010 paths.

## Other Things Proven Here

JIT works. `MAP_JIT`, live code rewriting and cross-thread patching all pass, and asmjit
runs. Plain RWX mappings are refused by `vm_map_enter`, as they should be. Nothing on
the JIT side stands in the way of running an emulator on this target.
