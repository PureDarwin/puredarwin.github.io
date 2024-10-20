Using MacPorts
==============

![](/img/developers/macports/macports-logo-top.png)
[MacPorts](http://www.macports.org/), formerly known as DarwinPorts, is a variant of the BSD ports system for Darwin and Mac OS X.
This page describes how to use MacPorts to create binary packages that can be deployed to PureDarwin. We now have [MacPorts running on PureDarwin](macports/macportsonpuredarwin.html) itself. Deploying MacPorts on a PureDarwin system and building binaries there is preferable, since you will save a lot of hassle.

### Prerequisites
For MacPorts, you need
-   An Intel-based Macintosh with Mac OS X 10.5 Leopard (latest version)
-   Xcode Tools
-   X11 (optional?)

The actual requirements might be less than that, but this is the configuration currently tested and used by us.
At a later time, we might attempt to use MacPorts on the PureDarwin system itself, but at this time our approach is to build binaries using MacPorts on the Mac and deploy these to PureDarwin.

### Installation
On the Mac, simply download and install the latest MacPorts DMG from the [MacPorts download page](http://www.macports.org/install.php).
It will install the MacPorts system under */opt/local/*.
Instead of using binary, you can also compile tarball or svn source.
See the [MacPorts download page](http://www.macports.org/install.php) for more information about how to get more information around installing MacPorts.

### Configuration
Since we would like MacPorts to create binary packages of the software that we build with it that can then be deployed to PureDarwin systems, we must enable the archive mode.
For that, edit the file */opt/local/etc/macports/macports.conf* so that it contains:

    # Create and use binary archive packages for installation/reinstallation ease
    portarchivemode         yes

Since we are using .tbz2 files as thinned DarwinBuild binary roots, we'd like to create the same type of packages with MacPorts too:

    # Supported types: tgz (default), tar, tbz, tbz2, tlz, xar, zip, cpgz, cpio
    portarchivetype         tbz2

MacPorts is now configured to create binary archives in the tbz2 format.

**Important:** Since Snow Leopard/Darwin 10, you need to explicitly set the architecture to i386 or you will get binaries that don't run on 32-bit only CPUs. The PureDarwin project is about building i386 binaries, so please make sure that you have the following in your */opt/local/etc/macports/macports.conf*:

    # The machine architecture to build for in normal use.
    build_arch i386

Otherwise, you'll get 64-bit binaries that are incompatible with 32-bit only CPUs, such as Intel Core Solo, Core Duo and Atom CPUs.

### Use

#### Searching for a port
`sudo port search xfree86`

#### Getting information about a port found
Remember you must match the exact port name (no sensitive case).
This is usefull to know which variants are available and which wants you would like in case

    sudo port info xfree86
    XFree86 @4.7.0 (x11)
    Variants:    darwin, macosx, puredarwin

    The XFree86 project's X window system implementation
    Homepage:    http://www.xfree86.org/

    Platforms:            darwin, freebsd
    Maintainers:          nomaintainer@macports.org

    Maintainers: nomaintainer@macports.org

#### Building a port
To build XFree86, for example, use:

`sudo port -d archive xfree86 +puredarwin`

This is just an example. If you really want to build XFree86, see the [XFree86](xfree86.html) page for additional information.
This should download, compile, and after a while return
 

--->  Archive XFree86-4.7.0_0+macosx+puredarwin.i386.tbz2 packaged


The resulting package should be located at */opt/local/var/macports/packages/darwin/i386/XFree86-4.7.0_0+macosx+puredarwin.i386.tbz2* and should be ready for deployment to a PureDarwin system.

#### +puredarwin variant
MacPorts includes various build targets or "variants". Here is a quick, approximate overview:


![](/img/developers/macports/Bild%208.png)


Maybe you noticed the "+puredarwin" build target in the command above. Note that "+darwin" is a superset of both "+puredarwin" and "+macosx", so binaries made using the "+darwin" variant will in many cases **not** run on PureDarwin. 

It is probably fair to say that the "+puredarwin" variant in MacPorts is the most appropriate variant if you are targeting the PureDarwin distribution. 
This build target may be defined in the portfile of the respective project that you are building.

Talking about variants, use `sudo port variants XFree86` in order to list them and their respective description.
The raw content of a portfile can be displayed via `sudo port cat XFree86` command.
The portfile of XFree86, */opt/local/var/macports/sources/rsync.macports.org/release/ports/x11/XFree86/Portfile*, defines:


    platform puredarwin {
        post-patch {
            set hostfd [open "${worksrcpath}/config/cf/host.def" a+]
            puts $hostfd "#define DarwinQuartzSupport NO"
            puts $hostfd "#define BuildGlxExt         YES"
            puts $hostfd "#define BuildGLXLibrary     YES"
            close $hostfd
        }
    }

Other projects might or might not need and/or have a "+puredarwin" variant.
If they need but lack one, please consider submitting patches for the respective portfiles.
To see which projects already have a puredarwin variant, click [here](http://www.macports.org/ports.php?by=variant&substr=puredarwin).

Probably you want to set MacPorts to always use the +puredarwin variant, if possible.
Do that by adding "+puredarwin" to variants.conf:

    echo "+puredarwin" >> /opt/local/etc/macports/variants.conf
    echo "-macosx" >> /opt/local/etc/macports/variants.conf

#### Purity checking
It is crucial that you [check the build results for "purity"](macports/purity.html).

#### Updating MacPorts
Do not hesitate to "cron" it.
Also run it after your first installation of MacPorts.
`sudo port selfupdate`
After a "selfupdate", you can also list outdated port(s) (in version) with:
`sudo port outdated`

#### Upgrading deprecated port(s)
In order to upgrade a specific port, use:
`sudo port upgrade XFree86`
If you want to upgrade all deprecated ports found since the latest selfupdate:
`sudo port upgrade outdated`

#### Cleaning MacPorts
In order to clean a specific port, use:
`sudo port clean XFree86`
If you want to clean all ports:
`port clean all`

#### Removing inactive port(s)
`port -f uninstall inactive`

### Troubleshooting
**Problem (1.6.0):** port rpm cairo +puredarwin -macosx returns
Error: Unable to execute port: invalid command name "univers...

**Solution:** Apply the patch below

### Credits
Thanks afb for lots of help with MacPorts and for the portmain.tcl patch below.

### Resources
[MacPorts.org](http://www.macports.org/)
[man port](macports/port.html)
