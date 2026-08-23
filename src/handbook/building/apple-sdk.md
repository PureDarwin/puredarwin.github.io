# The Apple SDK requirement

Building PureDarwin currently requires `MacOSX11.3.sdk.tar.xz`, a copy of Apple's macOS
11.3 SDK. It is proprietary, it cannot be fetched automatically, and it cannot be
redistributed, so you have to supply it.

**This is a known problem and removing it is on the [roadmap](../roadmap.md).** It is
not a blocker for the 20.5.0 release, but it is the reason a build is not a single
command on a clean machine.

## Registering it

```
nix-store --add-fixed sha256 /path/to/MacOSX11.3.sdk.tar.xz
```

Expected sha256:

```
9adc1373d3879e1973d28ad9f17c9051b02931674a3ec2a2498128989ece2cb1
```

If it is missing, the build stops with:

```
MacOSX11.3.sdk.tar.xz (Apple SDK, proprietary - not fetchable/redistributable)
is not yet in your Nix store. Register your local copy with:
  nix-store --add-fixed sha256 /path/to/MacOSX11.3.sdk.tar.xz
```

## How it is wired in

The mechanism is `requireFile`: Nix knows the hash and the message, but has no way to
obtain the file. The flake also carries an `allowUnfreePredicate` narrowly scoped to
this one name, so nothing else unfree slips in.

The canonical definition lives in `nix/pkgs/toolchain/apple-sdk-pinned.nix`, which
unpacks it to:

```
$out/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
```

with a `MacOSX11.3.sdk` symlink beside it. Every port that needs a sysroot repeats the
same `requireFile` block; there is no shared helper for it yet.

Never hardcode a path to your own copy into a Nix file. The `requireFile` pattern is
deliberate: it fails with instructions rather than with a path that only works on one
machine.

## The same pattern for external sources

fbDOOM is handled the same way for a different reason. The project avoids adding GPL
components where it can, so fbDOOM is kept as an external checkout rather than a flake
input, pointed at by `PUREDARWIN_FBDOOM_SOURCE_ENV` and built with `--impure`.

This is not an objection to the GPL. It is that a GPL component in the tree
brings obligations along with it, and those obligations then apply to anyone
packaging or redistributing PureDarwin. Keeping it opt-in and external
means the default build has one less licence to reason about, and people
who want fbDOOM can still have it. `corecrypto` is the counterexample:
it is GPL and it is in the tree, because there was no alternative, and
[replacing it](../roadmap.md#replace-corecrypto---blocked-on-an-alternative) is on the
roadmap for exactly this reason.

If you need to add something that must remain external to the tree, copy the fbDOOM
shape. The principle is not specific to the GPL: avoid folding another independently
licensed substantial component into the default distribution when keeping it external
works just as well. ZFS, under the CDDL, is the other obvious candidate.

## Why it is still needed

The SDK supplies headers and stub libraries that the project has not yet replaced with
its own. Every component that stops needing it is one step closer to a fully open build;
several already have their own headers, and the guest headers under `pd-guest-headers/`
exist precisely so in-guest compilers never see Apple's.

The work to finish this is tracked on the [Roadmap](../roadmap.md) alongside the related
item of completing the Nix-on-macOS host path.
