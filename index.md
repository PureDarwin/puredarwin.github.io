# Welcome to PureDarwin
![](/puredarwin.png)

[Darwin](http://en.wikipedia.org/wiki/Darwin_%28operating_system%29) is the open source operating system from Apple that forms the base for macOS. PureDarwin is a community project that aims to make Darwin more usable (some people think of it as the informal successor to OpenDarwin).

One current goal of this project is to provide useful bootable media of Darwin 10.x.
Another goal of this project is to provide additional documentation. [More](https://github.com/PureDarwin/PureDarwin/wiki/About)...

## For the Darwin community!

### Here's our Beta build!

[PD-17.4-Beta Build](https://github.com/PureDarwin/PD-17.4-Beta)

### Here's a screenshot and a video of our latest build!
![](Screenshots/2018-03-02.png)
<iframe width="560" height="315" src="https://www.youtube.com/embed/oCYpCOq0RJg?rel=0&amp;start=30" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

Documentation and quick hints
-----------------------------
Please see the [PureDarwin Wiki](https://github.com/PureDarwin/PureDarwin/wiki/), it would be very kind if anyone could contribute and fix the wiki as we have links and formatting there that are broken.

See the [changelog](https://github.com/PureDarwin/PureDarwin/wiki/_history) for recent updates to the Wiki.

Getting the code
-------------------------
We have a [GitHub repo](https://github.com/PureDarwin/), and encourage visitors to use it for both contribution, and for checking out the latest build sources.

Additionally, as an interim measure, we have a [version of PureDarwin Xmas](https://github.com/PureDarwin/LegacyDownloads/releases/download/PDXMASNBE01/NewBootEnvironment-XMas-1.7z) with a fixed boot sector, which is compatible with QEMU.

#### **Here's a [guide](https://github.com/PureDarwin/Building-XNU-16.7-Kernel-Guide/) on building XNU of the 16.7 (10.12.6) kernel!** 

Status
------

PureDarwin is currently working on AHCI/NVMe and eMMC family/drivers for Darwin, only they will not support/work on Apple's macOS. We have a PoC (Proof of Concept) of a PureDarwin 17.6 QEMU image that's based on Apple's open source code of [macOS 10.13.3](https://opensource.apple.com/release/macos-10133.html) that's only currently available to devs who join our IRC channel (#puredarwin on Freenode). 

**Update:** Hey, guys, we're still moving along. We'll be providing an SDK that is native of an Apple release on opensource.apple.com and a modified version that is PureDarwin targeted, as we are working on a modified XNU kernel with some other BSD/POSIX features that don't require us to rely on Apple's closed sources that they'll never release.

We are looking for supporters/coders that can help bring about faster development of PureDarwin while showing Apple that there is still a community of open source Darwin supporters that would like to see more open-ness from them, whether it be from them releasing binary drivers for our use as they once did, or open source projects like libxpc/launchd again.

[PureDarwin's Current Build Status](Status.md)

#### PureDarwin IRC Channel!
Please join us on freenode.net #puredarwin for our info we have USA/Europe Devs who can receive hardware.
Due to spam on IRC, please contact bart- or InSaneDarwin on IRC for an invite to the channel.

FAQ
-------

#### What is Darwin?

Darwin is an open-source *Unix-like* 
operating system released by Apple Inc.
that forms the base for macOS.

#### What is PureDarwin?

The goal of PureDarwin is to make
Darwin more usable by providing an
installation ISO, documentation, and
add-on software. You are welcome to
join #puredarwin on irc.freenode.net
if you would like to join PureDarwin
development and to add to
www.puredarwin.org

#### How usable is PureDarwin?

PureDarwin can run on VMware as well
as on real Intel-based hardware. We are
successfully running a web server, have
built hundreds of software packages
with MacPorts running on PureDarwin,
including ssh, apache2, tightvnc, Xfce,
and others.

#### Why spend time on Darwin?

For learning BSD stuff and for fun.

#### How does PureDarwin relate to the former OpenDarwin project?

Although some people have been
seeing PureDarwin as the informal
successor to OpenDarwin, there is no
official relationship other than the fact
that OpenDarwin and PureDarwin are
both downstream Darwin projects.
It is, of course, no secret that PureDarwin
would not exist if OpenDarwin had not
closed down. Coming later in time,
PureDarwin is in the fortunate position
to be able to benefit from the valuable
contributions that were rooted in the
OpenDarwin project.

#### How does PureDarwin relate to the DarwinBuild project?

DarwinBuild is one of PureDarwin‘s
main upstream projects.

#### What does the "Pure" in PureDarwin stand for?

Pure as in beer! It means that we just use components specifically released
by Apple for use with Darwin, as well as other Open Source components (coll
ectively called "upstream code"). Specifically, it means that we do not
use any components from macOS. It also means that we try to stay as close
as possible to the "outside world" as in macOS (e.g., regarding the choice
of compilers, options, etc.). It does not
mean, however, that we do not modify
and add to the upstream code, to
the extent that the respective licenses
allow.

#### How can I help PureDarwin?

Pretty much on all fronts. Especially if
you are skilled in C, C++, ObjC, Mac OS
X, BSD, etc. you should consider joining
#puredarwin on irc.freenode.net

Follow Us!
-------
Twitter: [PureDarwin Twitter](https://www.twitter.com/puredarwin)

Facebook: [PureDarwin Facebook](https://www.facebook.com/groups/puredarwin/)

Reddit: [PureDarwin Reddit](https://www.reddit.com/r/PureDarwin/)

Discord: [PureDarwin Discord](https://discord.gg/9kz8XXRRcT)

Credits
-------

We would like to thank
-   Apple, Inc. for releasing Darwin as open source 
-   kvv and _wms for their continuing help
-   David Elliott for his work on boot-132
-   The Chameleon team for their work on boot-132
-   The xnu-dev team for their work on the XNU kernel
-   Stuart Crook for his work on PureFoundation
-   Guillaume Verdeau for his work on X.Org
-   [Rafirafi](https://github.com/rafirafi) for his work on Generic Platform and PDCrypto kexts
-   [InSaneDarwin](https://github.com/csekel/) for his work on AHCI and eMMC Family/Drivers(still in active private development)
-   Mac OS Forge 
-   The DarwinBuild project 
-   The MacPorts project
-   The folks at #macosforge, #macports, #macdev, #opendarwin, #puredarwin, 
-   Everyone else contributing to Darwin 

{% include footer.html %}

© 2024 PureDarwin / PD-Devs
