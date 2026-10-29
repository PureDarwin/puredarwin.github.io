# The SDK

Every Darwin component is compiled against an SDK: the headers and stub libraries that
describe the system it will run on. Apple's macOS SDK is proprietary and cannot be
redistributed.

PureDarwin used to require a copy of Apple's `MacOSX11.3.sdk.tar.xz`, registered in the
Nix store by hand. **That requirement is gone.** The build now assembles its own SDK from
open source headers, and a clean machine needs nothing but the repository and Nix.

## How It Is Built

`nix/pkgs/toolchain/apple-sdk-pinned.nix` builds the SDK. It collects the public headers
from the in-tree sources (XNU's `bsd`, `osfmk`, `iokit` and `libkern` headers, libSystem,
the frameworks and so on) and lays them out the way an SDK is laid out:

```
$out/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
```

It is built in two stages. The first stage has the hand-written headers that `migcom`
needs. The second stage adds the `<mach/*.h>` headers that `migcom` generates from XNU's
`.defs` files, so nothing generated is checked into the tree.

The small amount of content that has no open source origin is written by the project
and lives in `nix/pkgs/toolchain/oss-sdk/`, laid out as the SDK tree. It is mostly a few
reconstructed headers and text stubs (`.tbd` files) for frameworks.

The flake wires this SDK in globally, so every target builds against it.

## When a Header Is Missing

Almost every gap found so far was a header that already existed somewhere in the tree
and was not yet copied into the SDK. Look for it in the tree first. Only write new
content in `oss-sdk/` when nothing in the tree provides it.

Never copy content out of Apple's proprietary SDK to fill a gap, even to look at it. The
whole point of this SDK is that every file in it has an open source origin.

## Other Licensing

The SDK is not the only licensing question in the tree. Security.framework still
compiles the old GPL corecrypto, some of Apple's published source carries no usable
license grant, and GPL extras such as fbDOOM are kept outside the tree as an opt-in. See
[Licensing](../licensing.md).
