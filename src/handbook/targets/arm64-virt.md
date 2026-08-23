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

`userland-arm64` and the `-arm64` suffixed ports supply the guest software.

## State

Boots to a shell from an ext4 root, with the platform expert, GIC, virtio devices and
xHCI input working. Xorg can be started. **GL on virt is currently broken on the
reference machine**; treat that as an open bug rather than a general statement about the
target.

## Machine notes

**Use `-cpu neoverse-n2` or `cortex-a710`, not `-cpu max`.** With `max`, the EDK2
firmware crashes before printing anything, which presents as a completely silent serial
port and looks like a loader problem. It is not.

**16K page granule.** The virt target uses 16K pages. That interacts with L2 block
congruence, the trustcache and `segLOWEST` handling, and the TSD layout, all of which
had to be fixed to get here.

**Display is ramfb.** The loader fills a 64-bit Video structure and the kernel wants
`v_display == 0`. The virt machine also needs the xHCI keyboard for input.

**Interrupts.** `PDArmGIC` routes the virtual timer (CNTV) as Group 1.

## Root filesystem options

Two shapes are available. `image-arm64-virt` is a conventional disk image;
`image-arm64-virt-minimal` uses a 512 MB RAM disk with `rd=md0`, which is faster to
iterate on and is the shape shared with the netboot and T8010 paths.

## Other things proven here

JIT works: `MAP_JIT`, live code rewriting and cross-thread patching all pass, and asmjit
runs. Plain RWX mappings are refused by `vm_map_enter`, as they should be. There is no
JIT-side blocker for running an emulator on this target.
