# Contributing

Contributions are welcome. The code is on
[GitHub](https://github.com/PureDarwin/PureDarwin), and most discussion happens on
[Discord](https://discord.gg/9kz8XXRRcT).

`CONTRIBUTING.md` in the repository is the full policy, with the reasons behind each
rule. This page is a summary, plus practical detail about working in the tree.

## Branches

Work happens on `main`, so open pull requests against `main`. Releases are built from
`main`, and each release image is named after the commit it was built from, so there's
no separate release branch.

## Where New Contributors Start

If this is your first contribution, work on Nix packages: porting software, fixing a
build, adding an arm64 build, or getting something onto an image. See
[Adding a Package](porting/adding-a-package.md). This is where new contributors help
most right away, and where a mistake is cheap and easy to review.

**If you're new to the tree, talk to us before you change the kernel or the core
system libraries.** Open an issue or ask on Discord first, and describe what you want to
change and why. A pull request in these areas that arrives without that conversation may
be closed and pointed to one, instead of being reviewed.

These parts all depend on each other. A one-line
change in libSystem can cause bugs in many places that look unrelated to what you
touched, often only on real hardware and weeks later. Reviewing such a change properly
costs more than writing it.

Adding to the libSystem build is the exception. Adding an existing library to the
build, or exporting a function that's already written, doesn't need a conversation
first, as long as it doesn't change what the library does. Missing exports are one of
the most common bugs, so this work is wanted.

The need to ask first goes away as the maintainers get to know how you work, one area
at a time. There's no count of merged pull requests that earns it.

## Provenance

Every contribution has to be yours to give, under a licence compatible with the project.

**Code whose licence is unknown or unclear can't be accepted, and can't be looked
at.** Don't paste it into an issue, a pull request or a chat. Once a maintainer has
seen it, whether the project's own code was influenced by it becomes a real question,
and nothing fixes that later. Leaked Apple source, decompiled Apple programs and code
derived from Apple's closed implementations all fall into this group.

When you bring in code from another project, say where it came from and include its
licence.

Clean-room work is allowed, and much of the project depends on it. That means drivers
written from a manufacturer's datasheet, code written against a published standard, and
work based on watching how real hardware behaves. The line is between interface
knowledge and implementation. Knowing what a register does, or what a protocol looks
like on the wire, is interface knowledge, and you may write from it. Reading someone's
closed implementation and writing code from what you saw is copying.

Name your sources in the commit message or a comment, the way the LAN78xx driver names
its datasheet. If you're unsure which side of the line you're on, say so in the pull
request.

## Forks and Credit

PureDarwin is open source, and forks are welcome. The same credit rule applies to
everyone who builds on someone else's work, PureDarwin included:

* **Keep the notices.** Keep every copyright notice, licence notice and SPDX line in the
  files you take, even where a licence would let you drop them.
* **Say what you inherited.** Wherever you describe your system, in READMEs, release
  notes, announcements and posts, say what it's based on. Say which of the features you
  show come from the projects you started from, and which are new in your work.
* **Name your starting point.** Name the project and the revision you started from.
* **Renaming doesn't change authorship.** Code with new names, bundle identifiers or
  paths is still the work of the people who wrote it.
* **Send fixes back** where you can.

The licences decide what you're legally required to do, and these points are what the
project asks on top of that. We follow them ourselves for the projects we build on, and
the [Credits](credits.md) page records what came from where. If you find
something there that's wrong or missing, tell us and we will fix it.

`NOTICE` in the repository has the full text of this request, and the summary of what the
licences require.

## Work Done With AI Tools

Code written with the help of a model is allowed. The test is the same one applied to
every contribution: **can you stand behind it as your own work, under the right
licence, and have you reviewed it yourself?**

You must understand the change, be able to explain it, and take responsibility for it.
For changes to existing code, read the history of what you're changing first. Much of
this tree looks wrong until you know why it's that way, and the commit that made it so
usually says. A tidy change that quietly undoes one of those fixes is the most common
failure.

Pull request descriptions, issues and review replies must be written by you, in your own
words. Translation tools are fine. `CONTRIBUTING.md` has the rules for pull requests
opened by automated tools.

You'll be asked questions about your patch, and if you can't answer them, the pull
request is closed. That applies the same way to someone who copied a patch from a forum
without understanding it.

## Style

`CODING_STYLE.md` covers formatting. Some points that catch people out:

* CMake is the only build system in the tree, with no Xcode projects. Building the tree
  by running CMake by hand is still not supported. See
  [The CMake Tree](building/cmake.md).
* C++ in the kernel is limited, with no standard library and no libc++abi.
* Keep cleanup separate from functional changes.

## Pull Requests

* One logical change per pull request.
* Commit messages are a subject line, with only trailers such as `Signed-off-by:` below
  it. Put anything longer in the pull request description.
* Say what you tested, on which target, and how. For hardware changes, say which
  machine.

## Testing Your Change

```
nix build .#image-minimal
nix run .#vm
```

**If you touched anything shared between architectures, build and boot x86_64.** Most
of the kernel and kext code is shared, and ARM work leaking into shared files is the
most common way the main target breaks.

Testing under both KVM (`nix run .#kvm`) and plain QEMU (`nix run .#vm`) is useful but
not required. They take different paths through the kernel, and the plain QEMU path is
tested less often.

Files you haven't added to git are invisible to the build, so add your work before you
build, or you'll test the old tree.

## Reporting a Bug

Write the report yourself. Include the target, the image, whether it ran in QEMU or on
real hardware, the boot arguments, and the console output as text where you can. For
hardware, add the machine model and firmware settings. A boot that stops with no output
is very hard to act on, so [Debugging](debugging.md) explains how to get a console first.
