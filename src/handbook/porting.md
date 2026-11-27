# Porting Guide

Most of the software on a PureDarwin image is open source software that was never built
for this system. Porting it, which means getting it to build and run here, is a large
part of the work.

* [Adding a Package](porting/adding-a-package.md) explains the mechanics.
* [Recurring Traps](porting/traps.md) lists the failures that have cost days, and how to
  spot them early.

**The goal is that unchanged upstream code builds.** A port that needs patches has to be
redone at every new version. A patch that works around a PureDarwin quirk also hides a
bug that will hit the next port too.

So when a build fails, start with one question: **what's PureDarwin claiming about
itself that's not true?** The answer is usually one of these:

* A function that exists but isn't exported from libSystem.
* A header that promises a function the system doesn't have.
* A link flag that makes every feature test succeed.
* A configure check answered by the SDK headers, where the running system would answer
  differently.

In each case the port looks broken, but the platform is giving wrong answers. Fix the
platform, and the unchanged upstream source usually builds.

Some projects, WebKit among them, treat Darwin and macOS as the same thing, and those do
need real patches.
