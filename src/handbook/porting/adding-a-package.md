# Adding a package

Ports live in `nix/pkgs/`, grouped by what they are: `base` for build tools and core
libraries, `x11`, `wayland`, `mesa`, `gtk`, `xfce`, `apps`, and `apple` for Apple
frameworks.

There is no shared `mkPort` helper. The pattern is copied per file, which is worth
knowing before you go looking for one. `nix/pkgs/base/yajl.nix` is a good short example
to copy from.

## The shape

```nix
{ stdenv
, lib
, requireFile
, darwinCrossToolchain
, nativeLd
, libSystem
, yajl                       # the nixpkgs package, reused for version and src
, targetTriple ? "x86_64-apple-darwin20.4"
}:

let
  sdkTarball = requireFile {
    name = "MacOSX11.3.sdk.tar.xz";
    sha256 = "9adc1373d3879e1973d28ad9f17c9051b02931674a3ec2a2498128989ece2cb1";
    message = ''...'';
  };
in
stdenv.mkDerivation {
  pname = "puredarwin-yajl";
  inherit (yajl) version src;

  configurePhase = ''
    # point the build at the cross toolchain, the SDK sysroot and libSystem
  '';
}
```

Points to note:

* **Reuse `version` and `src` from nixpkgs** rather than fetching your own. It keeps the
  port tracking upstream and avoids a second hash to maintain.
* **The `configurePhase` is explicit.** Autotools and meson both need to be told about
  the cross toolchain, the sysroot and the target triple; the standard nixpkgs cross
  machinery does not apply here.
* **The SDK block is repeated verbatim.** Never substitute a path to your own copy.

## arm64 variants

An arm64 build of the same port is the same file called with a different triple:

```nix
targetTriple = "arm64-apple-darwin20.4";
```

`nix/lib/target-info.nix` turns that into meson's `cpu_family`, `cpu` and `endian`, and
the clang target. Do not also set `-target` in the package's own flags: an explicit one
overrides the wrapper's and silently produces objects for the wrong architecture.

Register the variant in the arm64 package set so it appears as `<name>-arm64`.

## Getting it into an image

A built package is not on an image until `nix/image-contents.nix` puts it there. Add it
to `imageExtraPackageSet` for the general images, and check whether it belongs in the
narrower sets: `strippedExtraPackages` for the minimal and stripped images, and the
Wayland-only set, which drops the X11 client stack and swaps several packages for builds
made without X.

That Wayland set is easy to miss. A package added only to the main set will be absent
from `image-wayland` with no error.

## Before you start

Check whether the thing you need is already there. `nix flake show` lists several
hundred packages, and near-misses are common: a library may exist as a static build when
you need a shared one, or as an `-arm64` variant only.
