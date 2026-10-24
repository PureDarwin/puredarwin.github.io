# Licensing

PureDarwin has no single licence. It is Apple's open source under the APSL, plus
BSD-licensed code from FreeBSD, plus MIT-licensed work from Haiku and other projects,
plus code written here. That is normal for a system of this shape. It means "what licence
is PureDarwin" has no single answer, and anyone packaging or redistributing it needs the
detail.

This page is an orientation. It is not legal advice. The authority is always the header
on the file in front of you.

## The Broad Shape

| Area | Usually |
| --- | --- |
| `src/Kernel/xnu`, most kexts | APSL 2.0, Apple's own sources |
| `src/Libraries/libSystem`, `objc4` | APSL 2.0 |
| `src/Libraries/libcxx`, `libcxxabi`, `libunwind` | Apache 2.0 with LLVM exception |
| `src/Libraries/mDNSResponder` | Apache 2.0 |
| `src/Userspace` BSD commands | BSD, from the FreeBSD and NetBSD trees |
| `src/Frameworks/Foundation` | Contains MPL 2.0 code, treated as MPL by convention. See below |
| `src/Frameworks/CoreGraphics`, `Onyx2D` | MIT, descended from Cocotron |
| `src/Kernel/Extensions/ext4`, `src/Libraries/libDER` | PD 1.0, written for this project |
| `src/Kernel/fbsdkpi` and the `PDFBSD*` drivers | BSD from FreeBSD, MIT from Haiku |
| Other project-written code | Varies per component. Check the header |

Foundation is worth a note. It contains MPL 2.0 code, and the project treats the whole
component as MPL. That is a working convention. Handling it uniformly keeps merging
simple, and contributors are encouraged to do the same. The licence itself does not
require it.

## XPC in Detail

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

PD 1.0 is the project's own licence, a BSD-2-Clause derivative. The text is in
`PUREDARWIN_LICENSE.txt` at the root of the repository.

## corecrypto Is the Exception

The `corecrypto` kext and the CommonCrypto pieces above it are GPL. They are the only GPL
software in the default build. Nobody chose that on the merits. Apple's own corecrypto
cannot be used here, and the code descends from rafirafi's 2016 pdcrypto with
tiny-AES128-C adapted into it, which is what existed at the time.

If you are redistributing PureDarwin, this is the licence to know about. Replacing it is
on the [roadmap](roadmap.md#replace-corecrypto-blocked-on-an-alternative).

## Published Is Not the Same as Licensed

Some source Apple has published carries no usable licence grant. The pattern is a
repository where only some files have a per-file licence header and there is no
repository-wide `LICENSE`, which leaves everything unheaded with nothing attached to it.

CommonCrypto is the example that costs the project most. It is published, it is exactly
what we want, and the unheaded parts cannot be used. That is why `corecrypto` here is a
GPL descendant of other code.

Apple's libDER arrived with the same gap. That one had a better ending. The project
wrote its own libDER, and it is PD 1.0 as a result.

Check licensing file by file before building a port around an Apple component. Finding
out late is expensive, because by then somebody has read the code.

## Code Kept Outside the Tree

The project avoids folding another independently licensed substantial component into the
default distribution when keeping it external works just as well.

fbDOOM is the working example. It is GPL, so it lives in an external checkout, pointed at
by `PUREDARWIN_FBDOOM_SOURCE_ENV` and built with `--impure`. This is no objection to the
GPL. A GPL component in the tree brings obligations for everyone who packages or
redistributes PureDarwin. Keeping it opt-in means the default build has one less licence
to reason about, and people who want fbDOOM can still have it.

If you need to add something that must stay external, copy the fbDOOM shape. The
principle applies beyond the GPL. ZFS, under the CDDL, is the other obvious candidate.

## Contributing

What the project can accept, and the clean-room rules for writing drivers from
datasheets, are in [Contributing](contributing.md#provenance) and in `CONTRIBUTING.md`.
The short version is that every contribution has to be yours to give under a compatible
licence, and code whose licensing is unknown cannot be accepted or even looked at.
