PureDarwin bootstrap
====================
draft.



TODO: ramdisk (compressed) really begins to lack.

`launchd' via [/System/Library/LaunchDaemons/org.puredarwin.installer.plist](http://code.google.com/p/puredarwin/source/browse/projects/PureDarwinSettings/System/Library/LaunchDaemons/org.puredarwin.installer.plist) launches `[pd_installer](http://code.google.com/p/puredarwin/source/browse/scripts/pd_installer)' (probably in /usr/local/share/puredarwin/scripts).


### Generating a "bootstrap" release
<span style="font-size:small">PUREDARWIN_RELEASE="bootstrap" ./pd_setup ../../vm/bootstrap.vmwarevm PureDarwin</span>
<span style="font-size:small">
</span>

pd_installer

Example on VMware
...
Host OS: MacOS X running VMware fusion
Guest OS running inside VMware: PureDarwin "bootstrap"



Short count-down for the BIOS stage, where IDE devices are reported:
-   A cd device (bootstrap.iso)
-   An hd device (2 GB, non formated)

[![](../../_/rsrc/1263857828263/developers/repository/puredarwin-bootstrap/boostrap%20vmware%20bios.png%3Fheight=335&width=400)](puredarwin-bootstrap/boostrap%20vmware%20bios.png%3Fattredirects=0)

The screen can sometimes been entirely filled by the error below:

<span style="font-size:small">EBIOS read error: Error 0x31</span>

<span><span style="font-size:small">    Block 0 Sectors 4</span></span><span style="font-size:small">
</span>

[![](../../_/rsrc/1263857961350/developers/repository/puredarwin-bootstrap/bootstrap%20vmware%20bootloader%20seek%20errors.png%3Fheight=262&width=400)](puredarwin-bootstrap/bootstrap%20vmware%20bootloader%20seek%20errors.png%3Fattredirects=0)

This is not really problematic and should lead to the next screen.



The bootloader does not come from the media (bootstrap.iso) but from VMware (as displayed version shows).

See the [VMware](../vmware.html#TOC-darwin.iso) page for more information.

[![](../../_/rsrc/1263858200290/developers/repository/puredarwin-bootstrap/boostrap%20vmware%20bootloader%20countdown.png%3Fheight=262&width=400)](puredarwin-bootstrap/boostrap%20vmware%20bootloader%20countdown.png%3Fattredirects=0)
If [F8] is pressed, additional boot arguments can be passed to the kernel.

[![](../../_/rsrc/1263858485530/developers/repository/puredarwin-bootstrap/bootstrap%20vmware%20bootloader%20f8.png%3Fheight=262&width=400)](puredarwin-bootstrap/bootstrap%20vmware%20bootloader%20f8.png%3Fattredirects=0)

A Kernel EXTens decompression might occur.

[![](../../_/rsrc/1263858631045/developers/repository/puredarwin-bootstrap/bootstrap%20vmware%20kext%20decompression.png%3Fheight=262&width=400)](puredarwin-bootstrap/bootstrap%20vmware%20kext%20decompression.png%3Fattredirects=0)

Notice the cd-rom icon blinking while reading.

[![](../../_/rsrc/1263243391341/developers/repository/puredarwin-bootstrap/vmware%20cd%20blink.png)](puredarwin-bootstrap/vmware%20cd%20blink.png%3Fattredirects=0)

etc..




---





disk device detection (iofindwholemedia)


[![](../../_/rsrc/1263243397363/developers/repository/puredarwin-bootstrap/pd_installer%20intro.png)](puredarwin-bootstrap/pd_installer%20intro.png%3Fattredirects=0)


PureDarwin release

[x]


Boot on cd, deploy to hd (no ramdisk).

cd to hd


[![](../../_/rsrc/1263243391341/developers/repository/puredarwin-bootstrap/vmware%20cd%20blink.png)](puredarwin-bootstrap/vmware%20cd%20blink.png%3Fattredirects=0)

[![](../../_/rsrc/1263243384855/developers/repository/puredarwin-bootstrap/vmware%20hd%20blink.png)](puredarwin-bootstrap/vmware%20hd%20blink.png%3Fattredirects=0)



