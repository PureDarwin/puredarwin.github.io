# Porting Guide

Most of the software on a PureDarwin image is upstream code that was never built for
this system. Getting it to build is the bulk of the work, and there is a right way to go
about it.

* [Adding a package](porting/adding-a-package.md) - the mechanics.
* [Recurring traps](porting/traps.md) - the failures that cost days, and how to
  recognise them early.

**The goal is source compatibility with unmodified upstream code.** A port that requires
patches is a port that has to be re-done at every version bump, and a patch that works
around a PureDarwin quirk hides a bug that will bite the next port too.

So when a build fails, start with one question: **"what is PureDarwin claiming about
itself that is not true?"** In practice the answer is usually one of these:

* A symbol that is implemented but not exported from libSystem.
* A header that exists and promises a function the system does not have.
* A link flag that makes every feature test succeed.
* A configure check answered by the SDK headers, where the runtime would answer
  differently.

Every one of those makes the port look broken when the platform is the thing that is
lying. Fix the platform, and the unmodified upstream source usually just builds.

This is not an absolute rule. Some projects genuinely conflate Darwin with macOS and
Cocoa, WebKit being the standing example, and those need real patches. Reach for the
patch second.
