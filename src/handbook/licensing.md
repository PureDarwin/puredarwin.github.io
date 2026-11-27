# Licensing

PureDarwin doesn't have a single licence. It's Apple's open source, mostly under the
Apple Public Source License, mixed with code from FreeBSD, Haiku, Cocotron, NeoDarwin,
LLVM and other projects, plus the code we've written ourselves. That's normal for a
system built this way, but it means there's no one answer to "what licence is PureDarwin
under", and anyone who packages or shares it needs the detail.

This page is a guide and isn't legal advice. The licence of a file is the one stated in that
file, in its SPDX line and copyright notice. `NOTICE` in the repository describes the whole tree, and nothing on this page changes the licence of any file.

## PureDarwin's Own Code

New code written for PureDarwin is, as a rule, under "MPL-2.0 OR BSD-2-Clause". You may
use it under either licence. Code added inside a component that has its own licence
takes that component's licence. The project's BSD-style licence text is
`PUREDARWIN_LICENSE.txt` in the repository.

This describes the project's practice, and the notice in each file still decides its
licence.

## The Broad Shape

| Area | Usually |
| --- | --- |
| `src/Kernel/xnu`, Apple's kexts | APSL 2.0, Apple's sources |
| `src/Libraries/libSystem`, `objc4` | APSL 2.0 |
| `src/Libraries/libcxx`, `libcxxabi`, `libunwind`, `llvm-libc` | Apache 2.0 with the LLVM exception |
| `src/Libraries/mDNSResponder` | Mostly Apache 2.0 |
| `src/Frameworks/CoreFoundation` | Apache 2.0, from Apple's Swift releases |
| `src/Frameworks/Foundation` | MPL 2.0 |
| `src/Frameworks/AppKit`, `CoreGraphics`, `Onyx2D`, `CoreData` | MIT, from Cocotron, with PureDarwin's additions under PureDarwin's licence |
| `src/Userspace` BSD commands | BSD licences, from FreeBSD and NetBSD |
| `src/Kernel/fbsdkpi` and the FreeBSD drivers | BSD from FreeBSD, MIT from Haiku |
| `external/corecrypto` | MPL 2.0 |
| ext4, libDER and other PureDarwin code | MPL-2.0 OR BSD-2-Clause |

## XPC as an Example

`src/Libraries/XPC` shows why one answer doesn't work, because it's one directory with
parts under different licences:

| Part | Licence |
| --- | --- |
| `libinfo`, `notify` | APSL 2.0, from Apple |
| `launchd`, `launchctl` | APSL 2.0 |
| `libnv` | BSD-2-Clause, from FreeBSD |
| `libxpc` | BSD-2-Clause, from NextBSD |

Putting code with different licences in one directory doesn't give it a shared
licence. Each part keeps its own.

## GPL Code

Some kernel files are offered by their authors under a choice of licences, such as
"GPL-2.0 OR BSD-3-Clause". We use them under the permissive choice.

The Linux GPU drivers in drm-kmod are GPL only. The build fetches them and builds them
as optional kernel extensions, which keeps GPL code out of PureDarwin's sources. Anyone
who distributes those extensions, or an image that includes them, has to decide for
themselves whether that's compatible with the GPL and the other licences.

The same idea applies elsewhere. fbDOOM is GPL, so it's kept outside the tree and built
only when asked for. Keeping it optional means the default build has one less licence to
think about.

## Published Is Not the Same as Licensed

Some source Apple has published carries no usable licence. The pattern is a repository
where only some files have a licence header and there's no licence for the repository
as a whole. The files without a header then have no licence at all.

CommonCrypto is one example. Nearly all of Apple's published CommonCrypto carries the
APSL, but a few files had no licence. We rewrote those from their public interfaces. Apple's libDER had the same gap, so we wrote our own libDER.

Check licences file by file before you build a port around an Apple component. Finding
out late is expensive, because by then somebody has read the code.

## Credit

Licences decide what you must do. Credit is a separate question, and we hold
ourselves to the same rule we ask of anyone who builds on our work:

* Keep every copyright notice, licence notice and SPDX line in the files you take.
* Say plainly, wherever you describe your work, what you took from other projects and
  what you wrote yourself.
* Don't describe someone else's work as your own, in code or in announcements.

The [Credits](credits.md) page is how we do this for our own sources. The rule
for forks is in [Contributing](contributing.md#forks-and-credit).

## Contributing Code

What the project can accept, and the rules for writing drivers from datasheets, are in
[Contributing](contributing.md#provenance) and in `CONTRIBUTING.md`. Every contribution has to be yours to give under a compatible licence, and code whose licence is
unknown can't be accepted or even looked at.
