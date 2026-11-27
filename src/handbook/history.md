# Darwin's History

Darwin wasn't always source only. In its early years Apple put out installable Darwin
releases, as CD images you could boot and install. The old
PureDarwin wiki still lists the Apple binaries that came on two of them,
`darwinx86-602.iso` for Darwin 6 and `darwinx86-801.iso` for Darwin 8 (see
[Binary Drivers](../archive/about/BinaryDrivers.md)). Darwin 8 was the last release
Apple shipped that way. From Darwin 9 on, the binary parts that weren't open source,
such as the ACPI platform driver and the EFI boot loader, were only posted as separate
"roots" on Mac OS Forge. Today Apple publishes
Darwin as source code only.

## OpenDarwin

OpenDarwin was a community project that built and distributed Darwin outside Apple. It
closed down, and PureDarwin wouldn't exist if it hadn't. There's no formal link between
the two, but people have long called PureDarwin its informal successor, and we still
benefit from work that started there (see the old [About](../archive/about/_About.md)
page).

## The First PureDarwin

PureDarwin started out on Darwin 9 sources (see
[PureDarwin Core](../archive/developers/PureDarwin%20Core.md)), with
[DarwinBuild](../archive/developers/Using%20DarwinBuild/DarwinBuild.md) and
[MacPorts](../archive/developers/Using%20MacPorts/Using-MacPorts.md) as its main tools. In December 2008 we released PureDarwin Xmas, a developer preview that ran as a
virtual machine, and it got a warm welcome
([news](../archive/news/PureDarwin%20Xmas%20Developer%20Preview%20receives%20warm%20welcome.md)).
[PureDarwin Nano](../archive/users/PureDarwin-Nano.md), a minimal Darwin 9 system that
boots to a shell, followed in December
2009 ([news](../archive/news/PureDarwin%20Nano%2020091226%20available%20for%20download.md)).
Along the way contributors such as Rafirafi replaced the remaining closed binaries of
Darwin 9 with open ones, including a new
[generic platform expert](../archive/news/Generic%20platform%20kext%20for%20PureDarwin.md)
([news](../archive/news/New%20PureDarwin%201.3%20beta%20release.md)).

All of that work is kept in the [Archive](../archive/_Archive.md), along with the
[old news posts](../archive/news/_News.md).

## PureDarwin Today

The goal hasn't changed: make Darwin usable on its own. What has changed is how much is
missing. Today's PureDarwin is built from Apple's current Darwin source, with our own
bootloader and drivers in place of the binaries Apple used to ship, and a Nix build
instead of DarwinBuild. The [Credits](credits.md) page lists what we've built on along
the way.

## Further Reading

* The [Archive](../archive/_Archive.md), the old PureDarwin wiki as it was.
* Rob Braun's [history of Darwin and the projects around it](https://web.archive.org/web/20250526110943/http://www.synack.net/~bbraun/writing/oshistory.html).
