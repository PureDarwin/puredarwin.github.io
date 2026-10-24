# Recurring Traps

These have each cost days at least once. They are listed roughly in order of how often
they come up.

## The libSystem Export List

A symbol can be implemented, compiled and present in the archive, and still be missing
from `libSystem.exports`. Nothing links against it, and the failure appears as an
undefined symbol in something apparently unrelated, or as a `dlopen` that fails at
runtime with `RTLD_NOW`.

This has blocked whole subsystems: OpenGL was unavailable because five symbols were
missing from the export list, and dyld aborted at startup over a missing
`__dyld_is_memory_immutable`.

When a symbol "does not exist", grep the export lists before grepping the source.
`DYLD_PRINT_SEGMENTS` helps symbolicate what actually got loaded.

## dynamic_lookup Poisons Feature Detection

`-undefined dynamic_lookup` in `LDFLAGS` makes **every** link test succeed, because any
undefined symbol is deferred to runtime. Configure scripts then conclude the system has
functions it does not have.

Mesa detecting `memfd_create` and Wine taking the ELF path in ntdll were both this. If a
port has decided the system supports something surprising, check the link flags first.

## The SDK Answers Questions About the Guest

Feature detection compiled against SDK headers describes macOS, and PureDarwin can differ.
The build succeeds and the binary fails on the guest.

This is why the guest headers are staged separately as `pd-guest-headers/` and only
installed into the image at `/usr/include`, so cross-built ports never see them.

## Header Shadowing

An `osfmk` header on the include path ahead of the system one produced an identity
`htonl`, which is exactly the kind of bug that survives review because the code is
correct. Missing `_XSERVER64` made meson compute `sizeof` as -1. Check what is actually
being included before trusting a strange result.

## Static Archive Shadowing

A compatibility stub in an archive can alias onto itself and recurse infinitely, and at
the same time prevent the real libc implementation from being pulled in. The tell is a
self-referential `bl` in the disassembly of the function.

Related: an exported bootstrap `posix_memalign` that failed for alignments over 16
silently poisoned libOSMesa and libc++abi. The result was a blank render with no
error. Hidden visibility fixed it.

## Untracked Files Are Invisible to the Flake

The build reads the tree through `git+file://`. A file you have not staged does not
exist. Symptom: your change appears to do nothing at all.

### The `result` Gitignore Pattern

`.gitignore` carries `*result` and `*result-*`, and those patterns are unanchored, so
they match in every directory of the tree, including the repository root.

This is deliberate. `nix build` drops a `result` symlink in whatever directory you run
it from, and people run it from all over the tree, so `src/Kernel/xnu/result` and
friends turn up routinely and none of them should ever be committed.

The cost is that any real file or directory called `result` is invisible too. There is
already one in the tree, `src/Libraries/libSystem/libc/gen/FreeBSD/result`, which
survives only because it was committed before the rule existed. Git does not ignore
files it already tracks. Add a new one and it silently will not exist, which
combines with the untracked-files problem above into a genuinely confusing afternoon.

A better rule is wanted here and nobody has written one yet. Anchoring to the root
misses the subdirectory builds that motivated the pattern, and gitignore cannot match
"symlink into the Nix store", which is the thing actually being excluded. Until then, if
a file named `result` refuses to be added, this is why, and `git add -f` is the escape
hatch.

## Published by Apple Is Not the Same as Licensed

Some source Apple has published carries no usable licence grant, so check it file by
file before building a port around an Apple component. Finding out late is expensive,
because by then somebody has read the code. See [Licensing](../licensing.md).

## Never Hardcode CFTypeIDs

PureDarwin's CoreFoundation type IDs alias `_kCFRuntimeIDCF*` and depend on registration
order. Code that hardcodes a numeric ID, or counts registrations, will break in ways
that look like memory corruption.

## Do Not Guess at Include Guards

When adding to a vendored header, read the guard. Do not assume the conventional name
for it. Getting it wrong produces a header that is included twice or not at all.

## dlerror Can Lie

Under the pthread variant of dyld there is no `pthread_key_create`, so `dlerror()`
always returns NULL. glib read that as "the lookup succeeded" and carried on with a NULL
function pointer.

## Kernel-Specific Ones

* Kexts have no STL and no libc++abi. C++ in a kext is a restricted dialect. See
  `CODING_STYLE.md`.
* `kc-tools` truncates a kext's Info.plist `<dict>` after an XML comment, so the kext
  loses `IOProviderClass` and never matches.

## Early Boot Logging Is Not What You Think

A trace that never appears has not necessarily failed to run. In early userspace, which
means launchd and the first daemons, the logging helpers buffer, and nothing you emit
that way reaches a console you can see. Write straight to the console file descriptor
instead. In kernel code the equivalent question is `IOLog` against `kprintf`: they do
not reach the same places at the same times.
