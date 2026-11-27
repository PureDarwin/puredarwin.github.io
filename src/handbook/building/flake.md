# The Nix Flake

`flake.nix` is where every build starts. It's large and written by hand, so this page is a map and the file itself is the
reference.

## Inputs

A flake names the other repositories it builds from. These are PureDarwin's:

| Input | What it provides |
| --- | --- |
| `nixpkgs` | Build tools for the host, and the upstream sources most ports reuse |
| `iig-tools` | `iig`, the tool that turns IOKit interface files into C++, needed for newer kexts |
| `kc-tools` | The tools that link the kernel and its extensions into one file |
| `xnu-loader` | PureDarwin's bootloader |
| `pd-sb-key` | The key that signs Secure Boot images. By default it's a placeholder with no key, and builds that sign replace it |

`iig-tools`, `kc-tools` and `xnu-loader` are PureDarwin repositories. If you change one
of them together with the main tree, point the build at your copy with
`--override-input`.

## How the Outputs Are Grouped

**Packages are disk images.** `nix build .#image-minimal`, `.#image-wayland` and the
others in [Image Flavours](../images/flavours.md) are the flake's packages, because
images are what most people build.

Everything else is under a group name:

| Group | Contents | Example |
| --- | --- | --- |
| `pd.<arch>` | Libraries, programs and ported software for one architecture: `x86_64`, `arm64`, `armv6`, `riscv64`, `arm32` or `wasm32` | `.#pd.x86_64.libSystem`, `.#pd.arm64.zsh` |
| `kernel` | Kernels and kernel extensions | `.#kernel.kernel`, `.#kernel.kexts`, `.#kernel.kernel-debug` |
| `kernel.arm64.<board>` | An arm64 board's kernel, as `release` or `debug` | `.#kernel.arm64.virt.release` |
| `kc` | Kernel collections, the kernel and its extensions linked into one file | `.#kc.default`, `.#kc.gpu`, `.#kc.arm64.virt.release` |
| `firmware` | Device firmware, such as GPU firmware | |
| `toolchain` | The compilers, linker and SDK | `.#toolchain.native-ld` |
| `runners` | The QEMU scripts behind the apps below | |
| `tests` | Test images and checks | |

`nix flake show` prints the full list.

A name ending in `-debug` is built against the kernel's development configuration,
which has extra checks and logging.

## The Supporting Files

| File | Role |
| --- | --- |
| `build.nix` | The one derivation that builds the in-tree CMake sources |
| `image.nix` | Builds a partitioned, bootable disk image |
| `nix/outputs.nix` | Sorts every output into the groups above |
| `nix/image-contents.nix` | Decides what goes into each image, and defines the runners |
| `nix/release.nix` | Turns an image into a named, compressed release file |
| `nix/arm64.nix`, `nix/riscv64.nix` | The kernels and userland for the other architectures |
| `nix/boards.nix` | The arm64 boards |
| `nix/lib/` | Shared helpers, such as the kext list and target settings |
| `nix/pkgs/` | Every ported third-party package |

## Apps

Apps start QEMU with an image. `nix run .#vm`, `.#kvm`, `.#arm64-virt`, `.#arm64-uefi`
and `.#arm64-uboot` are the common ones. See [Running in QEMU](../images/running.md).

## The Development Shell

`nix develop` gives you the cross compiler, the linker, `migcom` and `unifdef`, and
points CMake at the toolchain file. It's for working on one component at a time and doesn't build a whole system. See [The CMake Tree](cmake.md).
