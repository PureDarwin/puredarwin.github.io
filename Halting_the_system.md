Halting the system
==================
The command `halt' is used to shut down the system.

<span style="font-style:italic">kext_tools</span> needs to be installed for `halt' to work properly, because `halt' calls <span style="font-style:italic">com.apple.KernelExtensionServer</span> and locks `kextd'.
So (at the time of 9F33), we patched the kext_tools project for purity purpose, in order to avoid missing symbols expected elsewhere.
Surprisedly, now `halt' and `shutdown' <span style="font-weight:bold">work perfectly</span> (<span style="text-decoration:underline">note:</span> it has yet been tested with CF-lite though, and `kextcache' depends on):


[![](../_/rsrc/1225463972197/developers/halt/halt%20in%20puredarwin.png)](halt/halt%20in%20puredarwin.png%3Fattredirects=0)

In case, `halt' fails, this is what could happening:


<span style="font-family:courier new"><span style="font-size:12px">WARNING: couldn't lock kext manager for reboot: %s</span></span>

<span style="font-family:courier new;font-size:12px">couldn't lock for reboot</span>


At this time, `shutdown -s now' is failing because of <span style="font-style:italic">sleep</span>:


[![](../_/rsrc/1225466088081/developers/halt/shutdown%20failing.png)](halt/shutdown%20failing.png%3Fattredirects=0)


*kext_tools* and its dependencies are missing in PureDarwin nano releases because they will make PureDarwin nano not "nano" anymore, explaining why halt didn't work. halt involves IOKitUser, CF, DiskArbitration.framework and Security.framework...

[![](../_/rsrc/1247364785038/developers/halt/kextd.png%3Fheight=360&width=420)](halt/kextd.png%3Fattredirects=0)

