# X.Org for PureDarwin

When we started PureDarwin, it was not possible to run X.Org on it since support for native IOKit mode had been removed from its sources. This situation is changing now.

Guillaume Verdeau has released patches to get X.Org running on PureDarwin.
He writes: "Hope it can help you and others. It's now hard for me to find time to improve XDarwin so I give it to you!"
Guillaume notes that there are some things that still need to be worked on, such as acceleration and the keyboard. To be able to build on PureDarwin you will need the old XDarwin keyboard routines that use NXKeymappings.

Sources are available on the [PureDarwin download page](/about/Downloads) (still waiting to be integrated into the build scripts in the repository - volunteers?).
