# pdnews

A small C tool for the news section of this site. It reads the existing
entries as JSON and creates new ones, wiring them into the news index and
`src/SUMMARY.md`.

Everything it writes is plain ASCII. Typographic punctuation pasted in from a
word processor (curly quotes, em and en dashes, ellipsis, bullet, no-break
space) is folded to its ASCII equivalent; any other non-ASCII byte is an error
unless you pass `--allow-utf8`.

## Build

With Nix, from the repository root:

    nix run .#pdnews -- list --json
    nix build .#pdnews          # result/bin/pdnews
    nix develop                 # puts pdnews, mdbook and cmake on PATH

Without Nix:

    cmake -S tools/pdnews -B build/pdnews
    cmake --build build/pdnews

## Usage

Run it from the repository root, or point it at one with `--root DIR` (or the
`PDNEWS_ROOT` environment variable).

    pdnews list
    pdnews list --json
    pdnews new --title "Release: PureDarwin 0.4.0 Alpha" \
               --date 2026-08-22 \
               --author "PD-Team" \
               --summary "ext4 root, Wine on X11 and a virgl desktop." \
               --image /img/news/2026/news-cover-0-4-0.jpg \
               --body-file draft.md

`new` writes `src/news/<slug>.md`, adds the entry at the top of
`src/news/_News.md`, and adds it as the first item under News in
`src/SUMMARY.md`. The slug comes from the title unless `--slug` is given, and
the date defaults to today. Without `--body-file` the article body is a
placeholder line for you to fill in.

The three news highlights on `src/index.html` are hand-maintained; `new`
prints a reminder rather than editing the HTML.

## JSON shape

`list --json` prints an array, newest first:

    {
      "slug": "Remembering-Cliff-Sekel",
      "title": "Remembering Cliff Sekel (InsaneDarwin)",
      "date": "January 3, 2026",
      "iso_date": "2026-01-03",
      "author": "PD-Team",
      "summary": "The PureDarwin project has lost its leader.",
      "image": "/img/news/2026/news-cover-remembering-cliff.jpg",
      "path": "src/news/Remembering-Cliff-Sekel.md"
    }

Titles, dates, authors and cover images come from the article itself; the
summary comes from the quoted line in `src/news/_News.md`.
