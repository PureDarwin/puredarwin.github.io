Halting the system
==================
The command `halt' is used to shut down the system.

*kext_tools* needs to be installed for \`halt' to work properly, because \`halt' calls *com.apple.KernelExtensionServer* and locks \`kextd'.
So (at the time of 9F33), we patched the kext_tools project for purity purpose, in order to avoid missing symbols expected elsewhere.
Surprisedly, now \`halt' and \`shutdown' **work perfectly** (note: it has yet been tested with CF-lite though, and \`kextcache' depends on):


![](/img/developers/halt/halt%20in%20puredarwin.png)

In case, \`halt' fails, this is what could happening:


`WARNING: couldn't lock kext manager for reboot: %s`

`couldn't lock for reboot`


At this time, `shutdown -s now' is failing because of *sleep*:


![](/img/developers/halt/shutdown%20failing.png)


*kext_tools* and its dependencies are missing in PureDarwin nano releases because they will make PureDarwin nano not "nano" anymore, explaining why halt didn't work. halt involves IOKitUser, CF, DiskArbitration.framework and Security.framework...

![](/img/developers/halt/kextd.png)

