# The SDK

Every Darwin component is compiled against an SDK, the headers and stub libraries that
describe the system it'll run on. Apple's macOS SDK is proprietary, so we can't
redistribute it.

PureDarwin used to need a copy of Apple's `MacOSX11.3.sdk.tar.xz`, added to the Nix
store by hand. **We've dropped that requirement.** The build now assembles its own SDK
from open source headers, and a clean machine needs nothing but the repository and Nix.

## How It's Built

`nix/pkgs/toolchain/apple-sdk-pinned.nix` builds the SDK. It collects the public headers
from the in-tree sources (XNU's `bsd`, `osfmk`, `iokit` and `libkern` headers,
libSystem, the frameworks and so on) and lays them out the way an SDK is laid out:

```
$out/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
```

It's built in two stages. The first has the hand-written headers that `migcom` needs,
and the second adds the `<mach/*.h>` headers that `migcom` generates from XNU's `.defs`
files, so nothing generated is checked into the tree.

The little content that has no open source origin is ours. It lives in
`nix/pkgs/toolchain/oss-sdk/`, laid out like the SDK, and it's mostly a few
reconstructed headers and text stubs (`.tbd` files) for frameworks.

The flake wires this SDK in everywhere, so every target builds against it.

## When a Header Is Missing

Nearly every gap we've found so far was a header that already existed somewhere in the
tree and just hadn't been copied into the SDK yet. Look for it in the tree first, and
only write new content in `oss-sdk/` when nothing in the tree provides it.

Never copy anything out of Apple's proprietary SDK to fill a gap, even just to look at
it. The whole point of this SDK is that every file in it has an open source origin.

## Other Licensing

The SDK isn't the only licensing question in the tree. Some of Apple's published source
carries no usable licence, and GPL extras such as fbDOOM are kept outside the tree and
built only when asked for. See [Licensing](../licensing.md).
