PureDarwin bootstrap
====================
draft.



TODO: ramdisk (compressed) really begins to lack.

`launchd' via [/System/Library/LaunchDaemons/org.puredarwin.installer.plist](http://code.google.com/p/puredarwin/source/browse/projects/PureDarwinSettings/System/Library/LaunchDaemons/org.puredarwin.installer.plist) launches `[pd_installer](http://code.google.com/p/puredarwin/source/browse/scripts/pd_installer)' (probably in /usr/local/share/puredarwin/scripts).


### Generating a "bootstrap" release
PUREDARWIN_RELEASE="bootstrap" ./pd_setup ../../vm/bootstrap.vmwarevm PureDarwin



pd_installer

Example on VMware
...
Host OS: MacOS X running VMware fusion
Guest OS running inside VMware: PureDarwin "bootstrap"



Short count-down for the BIOS stage, where IDE devices are reported:
-   A cd device (bootstrap.iso)
-   An hd device (2 GB, non formated)

![](/img/developers/repository/puredarwin-bootstrap/boostrap%20vmware%20bios.png)

The screen can sometimes been entirely filled by the error below:

EBIOS read error: Error 0x31

    Block 0 Sectors 4


![](/img/developers/repository/puredarwin-bootstrap/bootstrap%20vmware%20bootloader%20seek%20errors.png)

This is not really problematic and should lead to the next screen.



The bootloader does not come from the media (bootstrap.iso) but from VMware (as displayed version shows).

See the [VMware](../vmware.html#TOC-darwin.iso) page for more information.

![](/img/developers/repository/puredarwin-bootstrap/boostrap%20vmware%20bootloader%20countdown.png)
If [F8] is pressed, additional boot arguments can be passed to the kernel.

![](/img/developers/repository/puredarwin-bootstrap/bootstrap%20vmware%20bootloader%20f8.png)

A Kernel EXTens decompression might occur.

![](/img/developers/repository/puredarwin-bootstrap/bootstrap%20vmware%20kext%20decompression.png)

Notice the cd-rom icon blinking while reading.

![](/img/developers/repository/puredarwin-bootstrap/vmware%20cd%20blink.png)

etc..




---





disk device detection (iofindwholemedia)


![](/img/developers/repository/puredarwin-bootstrap/pd_installer%20intro.png)


PureDarwin release

[x]


Boot on cd, deploy to hd (no ramdisk).

cd to hd


![](/img/developers/repository/puredarwin-bootstrap/vmware%20cd%20blink.png)

![](/img/developers/repository/puredarwin-bootstrap/vmware%20hd%20blink.png)



