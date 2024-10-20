# TODO

Would you like to help out with PureDarwin?
Don't know where to start? 

This page lists (from higher to lower layers, but non exhaustively) some of the areas where work is needed to make Darwin the truly world-class OS it should be.

## Feedback

Feedback is crucial, in whatever form it takes; from the container to the content including the way of sending it.

### Catalogue compatible hardware

If you've got PureDarwin to run somewhere - either in a VM we don't know about, or on a real piece of hardware - then please let us know so that we can add it to our compatible hardware page.

### Test other applications

With the X window system up and running, PureDarwin becomes a very compatible BSD clone, meaning that it should run any of the wide range of software available for that platform. As an example, most of the [pure](/developers/Using%20MacPorts/Purity) binaries compiled through [the MacPorts project](/developers/Using%20MacPorts/Using-MacPorts) can easily be copied into and used in a PureDarwin release. Let us know what you got running.

### Complaints

It would be much appreciated if criticism is constructive.

### Legal aspects

Help us to improve several legal aspects, including, non-exhaustively, how to handle intellectual property, trademarks, patents, copyright and licenses. What to provide? Where? How?

## Packages and binary roots

### Test available packages

The basic Darwin system as provided by Apple is made up of over 400 different packages. Many of these have been included in releases of PureDarwin ([Xmas](/users/Xmas) and [Nano](/users/PureDarwin-Nano)). Many more are available from http://src.macosforge.org. **And they all need testing.** We know this method is empiric but we simply need to know what works, and (more importantly) what doesn't, so that we can focus our efforts there.

A particular interest at the moment is per example the high level web application stack: Apache, MySQL, and PHP (or lighttpd, rrdtool and postgresql, etc..). That also could be the other scripting languages as Python, Perl, Ruby... or also some more low level behavior via the use of DTrace per example.
We haven't had a chance to put them through their paces yet, so maybe you could try them and let us know.

### Build missing packages

Not every Darwin project is available as a pre-built binary root. There's a list of these 'missing' packages (about 80 in all) in the git repository (under [projects/PureDarwinPackageDatabase/PackageLists](https://github.com/PureDarwin/PureDarwin/tree/master/projects/PureDarwinPackageDatabase/PackageLists/) in the file [missing.txt](https://github.com/PureDarwin/PureDarwin/tree/master/projects/PureDarwinPackageDatabase/PackageLists/missing.txt)). Some of these are known not to build.

Others are untested. If you succeed in building them, let us know so we can host a copy of the binary root for others and make them available for testing.

## Device drivers

### Locate and list available device drivers

Like all operating systems, Darwin will live or die by its hardware support.

There are a great many IOKit device drivers created by Apple and 3rd parties available. We first need to collect a list together, so that they can be tested and then bundled with future versions of PureDarwin. 

__Notes:__ See the [Network](/developers/Network) page, the [KEXTs](/developers/KEXTs/kexts) page, the [Graphics](/developers/Graphics) page, the [Binary drivers](BinaryDrivers) page, the [ZFS](/developers/ZFS) page, etc...

### Write device drivers

This is a crucial mission. Even pulling together all of the 3rd party drivers available, there will still be plenty of unsupported hardware. And we also have the problem of device drivers which are available in OS X but which haven't been made available for free redistribution in any form by Apple (e.g., the e1000 support via *AppleIntel82454XEthernet* driver springs instantly to mind).

So if you have the skills in this area, why not roll up your sleeves and get stuck in?
