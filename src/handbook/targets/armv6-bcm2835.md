# armv6 Raspberry Pi Zero

The earliest target, and the only 32-bit one. It boots as far as userspace but does not
reach a shell yet.

## Building

```
nix build .#kernel-arm32-bcm2835          # also -debug and -dev
nix build .#kexts-arm32-bcm2835
nix build .#prelinked-arm32-bcm2835
nix build .#userland-arm32-bcm2835
```

There is no image target for this board in the flake yet. A custom disk image aimed at
USB booting is being put together, and it is work in progress rather than something you
can build today.

## Why it is different

Everything else PureDarwin targets is 64-bit. ARMv6 needs a genuinely 32-bit XNU, which
Apple last shipped a very long time ago, so this is a port rather than a configuration:

* Memory barriers are CP15 operations, not the modern instructions.
* No `movw`/`movt`, so address materialisation has to go through literal pools.
* The kernel uses the older prelinked-kernel format rather than a fileset collection,
  built with `prelink-builder`.

## State

The kernel boots, mounts root and gets into userspace: execution reaches `dyld`, which
then complains about pthreads. That is a long way past where this target was when the
port started, when the question was whether a 32-bit XNU would build at all and the
error count was around 700.

Getting there meant going through `pmap.c`, which was the wall for a long time. The
ARMv6 MMU model is different enough from the 64-bit one that the page table code needed
real work rather than adaptation.

## Kexts

Seven: `corecrypto`, `pthread`, `ext4`, `IOStorageFamily`, `Ext4FileSystemDriver`,
`PDBcm2835SD`, `PDArmPlatformExpert`. `corecrypto` is not optional even here, because
`read_random()` dereferences NULL without it.

## Related tooling

Bootloader work uses
[lk-overlay, `llvm-vc4-vce` branch](https://github.com/librerpi/lk-overlay/tree/llvm-vc4-vce),
which is still experimental and does not support this board properly. Build it from
its own `nix develop`, then `VC4_TOOLCHAIN=gcc ./build.sh <project>`. Be aware that
unreferenced modules link out silently, which makes a missing feature look like a broken
one.
