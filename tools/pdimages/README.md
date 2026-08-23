# pdimages

Keeps the checksums for the preview images on the landing page honest. It
hashes the files as they are served, so what appears on the page is what a
visitor actually downloads, not what a local build happened to produce.

## Usage

From the repository root:

    nix run .#pdimages -- hash    # print SHA256SUMS lines, change nothing
    nix run .#pdimages -- sync    # write src/SHA256SUMS and update index.html

`sync` rewrites everything between the `<!-- pdimages:list -->` markers in
`src/index.html`, so the download list, sizes and hashes there are generated
rather than hand-edited. Do not edit inside the markers; edit the manifest and
run `sync` again.

## The manifest

`images.list` is the list of files, in the order they appear on the page. One
record per line, tab separated:

    file<TAB>kind<TAB>description

`kind` is `disk` or `video`, which only picks the icon. Adding an image is a
line here plus a `sync`.

## Environment

* `PDIMAGES_BASE_URL` - where the files are served from. Defaults to the
  project's own host.
* `PDIMAGES_ROOT` - repository root, defaults to the current directory.
* `PDIMAGES_MANIFEST` - an alternative manifest path.

Every download is streamed straight into `sha256sum`, so nothing is written to
disk and the full set can be re-hashed after a rebuild without needing room for
a second copy of the images.
