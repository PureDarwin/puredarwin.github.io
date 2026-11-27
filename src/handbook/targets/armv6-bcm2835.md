# armv6 Raspberry Pi Zero

This is our earliest target and the only 32-bit one. It boots as far as userspace but
doesn't reach a shell yet.

## Building

```
nix build .#kernel.kernel-arm32-bcm2835          # also -debug and -dev
nix build .#kernel.kexts-arm32-bcm2835
nix build .#kernel.prelinked-arm32-bcm2835
nix build .#pd.arm32.userland-arm32-bcm2835
```

There's no image target for this board in the flake yet. We're putting together a custom
disk image for USB booting, but it's still in progress and you can't build it today.

## Why It Is Different

Everything else PureDarwin targets is 64-bit. ARMv6 needs a genuinely 32-bit XNU, which
Apple last shipped a very long time ago. That makes this a real port:

* Memory barriers are CP15 operations, from before the modern barrier instructions.
* No `movw`/`movt`, so address materialisation has to go through literal pools.
* The kernel uses the older prelinked-kernel format, built with `prelink-builder`.

## State

The kernel boots, mounts root and gets into userspace, where execution reaches `dyld`
and then fails on pthreads. That's a long way past where this target was when the
port started, when the question was whether a 32-bit XNU would build at all and the
error count was around 700.

Getting there meant going through `pmap.c`, which was the wall for a long time. The
ARMv6 MMU model is different enough from the 64-bit one that the page table code needed
real work.

## Kexts

Seven: `corecrypto`, `pthread`, `ext4`, `IOStorageFamily`, `Ext4FileSystemDriver`,
`PDBcm2835SD`, `PDArmPlatformExpert`. `corecrypto` isn't optional even here, because
`read_random()` dereferences NULL without it.

## Related Tooling

Bootloader work uses
[lk-overlay, `llvm-vc4-vce` branch](https://github.com/librerpi/lk-overlay/tree/llvm-vc4-vce),
which is still experimental and doesn't support this board properly. Build it from
its own `nix develop`, then `VC4_TOOLCHAIN=gcc ./build.sh <project>`. Be aware that
unreferenced modules link out silently, which makes a missing feature look like a broken
one.
