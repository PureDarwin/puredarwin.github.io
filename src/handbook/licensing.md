# Licensing

PureDarwin is not under one licence. It is Apple's open source under the APSL, plus
BSD-licensed code from FreeBSD, plus MIT-licensed work from other projects, plus code
written here. That is normal for a system of this shape, but it means "what licence is
PureDarwin" has no single answer, and anyone packaging or redistributing it needs the
detail.

This page is an orientation, not a legal opinion. The authority is always the header on
the file in front of you.

## The broad shape

| Area | Usually |
| --- | --- |
| `src/Kernel/xnu`, most kexts | APSL 2.0, Apple's own sources |
| `src/Libraries/libSystem`, `objc4` | APSL 2.0 |
| `src/Libraries/libcxx`, `libcxxabi`, `libunwind` | Apache 2.0 with LLVM exception |
| `src/Libraries/mDNSResponder` | Apache 2.0 |
| `src/Userspace` BSD commands | BSD, from the FreeBSD and NetBSD trees |
| `src/Libraries/Foundation` | Contains MPL 2.0 code; treated as MPL by convention, see below |
| `src/Frameworks/CoreGraphics`, `Onyx2D` | MIT, descended from Cocotron |
| `src/Kernel/Extensions/ext4`, `src/Libraries/libDER` | PD 1.0, written for this project |
| Other project-written code | Varies per component; check the header |

Foundation is worth a note. It contains MPL 2.0 code, and the project treats the whole
component as MPL. That is a working convention rather than a strict consequence of the
mixture: handling it uniformly keeps merging straightforward, and contributors are
encouraged to do the same. It is a choice made here, not something the licence imposes.

## XPC, in detail

`src/Libraries/XPC` is the clearest example of why a single answer does not work. It is
one directory holding components under different terms:

| Component | Licence |
| --- | --- |
| `libinfo` | APSL 2.0 |
| `libnv` | BSD-2-Clause, from the FreeBSD Foundation |
| `libxpc` | BSD-2-Clause |
| `launchd` | APSL 2.0 |
| `launchctl` | APSL 2.0 |
| `logd` | PD-1.0, a BSD-2-Clause derivative |

There is no aggregate licence for the directory. Collecting differently licensed
components in one place does not give them shared terms, so each of the above keeps its
own, and the SPDX header on the file in front of you is what governs it.

PD 1.0 is the project's own licence, a BSD-2-Clause derivative; the text is in
`PUREDARWIN_LICENSE.txt` at the root of the repository.

## corecrypto is the exception

The `corecrypto` kext and the CommonCrypto pieces above it are GPL, and unlike the other
GPL software the project uses they are part of the default build. That is not a choice
made on the merits: Apple's own corecrypto is not usable here, and the code descends
from rafirafi's 2016 pdcrypto with tiny-AES128-C adapted into it, which is what existed
at the time.

If you are redistributing PureDarwin, this is the licence to know about. Replacing it is
on the [roadmap](roadmap.md#replace-corecrypto---blocked-on-an-alternative).

## Published by Apple is not the same as licensed

Some source Apple has published carries no usable licence grant. The pattern is a
repository where only some files have a per-file licence header and there is no
repository-wide `LICENSE`, which leaves everything unheaded with nothing attached to it.

CommonCrypto is the example that costs the project most: it is published, it is exactly
what we want, and the unheaded parts cannot be used. That is why `corecrypto` here is a
GPL descendant rather than Apple's own code.

Apple's libDER arrived with the same gap. That one had a better ending: rather than work
around it, the project's libDER was written here, and is PD 1.0 as a result.

Check licensing file by file before building a port around an Apple component. Finding
out late is expensive, because by then somebody has read the code.

## Code kept outside the tree

The project avoids folding another independently licensed substantial component into the
default distribution when keeping it external works just as well.

fbDOOM is the working example. It is GPL, so rather than living in the tree as a flake
input it is an external checkout, pointed at by `PUREDARWIN_FBDOOM_SOURCE_ENV` and built
with `--impure`. This is not an objection to the GPL: a GPL component in the tree brings
obligations that then apply to everyone packaging or redistributing PureDarwin, and
keeping it opt-in means the default build has one less licence to reason about while
people who want fbDOOM can still have it.

If you need to add something that must remain external, copy the fbDOOM shape. The
principle is not specific to the GPL; ZFS, under the CDDL, is the other obvious
candidate.

## Contributing

What the project can accept, and the clean-room rules for writing drivers from
datasheets, are in [Contributing](contributing.md#provenance) and in `CONTRIBUTING.md`.
The short version: every contribution has to be yours to give under a compatible
licence, and code whose licensing is unknown cannot be accepted or even looked at.
