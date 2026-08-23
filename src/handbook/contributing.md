# Contributing

Contributions are welcome. The project is on
[GitHub](https://github.com/PureDarwin/PureDarwin) and there is a
[Discord](https://discord.gg/9kz8XXRRcT) where most discussion happens.

`CONTRIBUTING.md` in the repository is the authoritative policy, and it explains the
reasoning behind everything here. This page is the summary, plus the practical detail
that is specific to working in the tree.

Three categories of change are closed without review:
[kernel and system-library changes from first-time contributors](#what-new-contributors-may-work-on),
[code whose licensing is unknown or unassured](#provenance), and
[changes the submitter cannot explain in review](#ai-assisted-contributions).

## Branches

**Development happens on `next`. Each release is frozen onto `main`.**

Open pull requests against `next`. `main` holds the last frozen release, so it is what
you check out to get the state a release was cut from, not what you build on top of.
Cleanup and stabilisation for a release also land on `next`, which is then merged to
`main` and frozen.

## What new contributors may work on

If this is your first contribution, work on Nix packages: porting software, fixing a
build, adding an arm64 variant, getting something onto an image. See
[Adding a package](porting/adding-a-package.md).

**First-time contributors may not modify existing kernel or system-library
implementations, and such changes are closed without review.** This is about blast
radius. These components all depend on each other, and a one-line change in libSystem
can take out the whole system, producing eight bugs in eight places that look unrelated
to what you touched, often only visible on real hardware and weeks later. Reviewing that
properly costs more than writing it.

The exemption is additive libSystem integration work. Adding an existing library or
component to the libSystem build, its exports, or the integration machinery around it is
fine, as long as the change does not alter the underlying library's behaviour. Missing
exports are one of the project's most common recurring bugs, so this work is genuinely
wanted. Changing what a component does is an implementation change, and the restriction
applies.

The restriction lifts on maintainer judgement, not on a counter. There is no number of
merged pull requests that earns access to the kernel, and one merged package is not a
qualification for XNU surgery. It lifts when you have been around long enough for the
maintainers to know how you work, and it lifts by area rather than all at once.

If you think you are ready, or you have a change in a restricted area you believe is
worth making, raise it in an issue or in Discord first. Asking is not an approval
ceremony: restricted areas have high review costs and often contain constraints that are
not obvious from the code, so a short conversation establishes whether the approach is
viable before either of you spends real time on it.

## Provenance

Every contribution has to be yours to give, under a compatible licence.

**Code of unknown or unassured licensing cannot be accepted and cannot be looked at.**
Do not paste it into an issue, a pull request or a chat channel: once a maintainer has
seen it, whether the project's own implementation was influenced by it becomes a real
question, and nothing later fixes that. Leaked Apple source, decompiled Apple binaries,
or code derived from proprietary Apple implementation material falls squarely in this
category. Do not provide it to project maintainers.

Clean-room work is permitted, and much of the project depends on it: drivers written
from a manufacturer's datasheet, code written against a published standard, and work
based on observing real hardware.

The line is implementation material versus interface knowledge. Learning what a register
does, what a protocol looks like on the wire, or what a structure layout must be to
interoperate is interface knowledge, and you may write from it. Reading a proprietary
implementation and writing code from what you saw is derivation.

In practice: work from sources you can name, and cite them in the commit message or a
comment, the way the LAN78xx driver names its datasheet. Do not go looking at
proprietary implementations to check your work. If you cannot tell which side of the
line you are on, say so in the pull request description, naming your sources and the
parts you are unsure about.

## AI-assisted contributions

Assisted and model-generated code is allowed. The test is the one applied to every
contribution:

**Can you stand behind this as your own work, licensed appropriately, and have you
reviewed it yourself?**

For purposes of review there is no distinction between code you wrote unaided and code
produced with a model. You must understand it, defend it, and take responsibility for
what you submit, which means having read the output line by line and being confident it
is not reproducing licensed code from elsewhere.

One requirement is worth stating on its own, because it is the most common failure. For
non-trivial changes to existing code, inspect the history of the code you are changing
and understand why the current implementation exists. This applies both to you and to
any model assisting you. A lot of this tree looks wrong until you know why it is that
way, and most of the odd-looking code is a fix for a specific bug with a commit message
that says so. Read `git log` and `git blame` on what you are touching. A confident, tidy
change that quietly reverts one of those fixes is the classic assisted contribution.

How it is enforced: you will be asked questions about your patch, and if you cannot
answer them the pull request is closed as-is. Not trick questions, but the kind of thing
anyone who understands the change should be able to answer without preparation, and the
kind someone merely submitting generated or copied code usually cannot.

None of this is aimed at people who use models. It is the standard for everyone: a
person who hand-writes a patch they do not really understand, or copies one from a forum
post and files it, is in exactly the same position and gets the same answer.

## Style

`CODING_STYLE.md` covers formatting. Points that catch people out:

* CMake only, and no Xcode projects in the main branch. This means no second build
  system in the tree. It does not mean a hand-rolled CMake build is supported; see
  [The CMake tree](building/cmake.md).
* Kernel C++ is a restricted dialect. No STL, no libc++abi. Use `OSSharedPtr`, but keep
  it out of declarations, because it is not ABI-stable.
* Keep cleanup separate from functional change.

## Testing your change

```
nix build .#image-minimal
nix run .#vm
```

**Build and boot x86_64 after touching anything shared between architectures.** The
kernel and most kexts are shared, and ARM work leaking arm-only code into shared files
is the most common way the primary target breaks.

Testing under both KVM (`nix run .#kvm`) and plain QEMU with TCG (`nix run .#vm`) is
recommended but not required. They exercise different paths, and the lead maintainer
does not test TCG routinely, so a TCG regression can sit unnoticed for a while. If your
change is somewhere that difference plausibly matters, running both genuinely helps.

Remember that untracked files are invisible to the flake. Stage your work before you
build, or you will test the old tree.

## Reporting a bug

Include the target and how you were running it, the image, the boot-args, and the
console output as text where possible. For hardware, add the machine model and firmware
settings. A boot that stops with no output is very hard to act on;
[Debugging](debugging.md) covers getting a console up first.
