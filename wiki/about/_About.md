# About

This page describes some part of the PureDarwin project and the motivation behind it, as well as how it relates to other projects.

### Goals

The goal of the PureDarwin project is to make Darwin more usable for open source enthusiasts and developers by providing documentation and by enabling them to retrieve, understand, modify, build, and distribute Darwin.

### Organization

The PureDarwin project is organized very informally at this stage. There are no official boards and committees. We are not interested in politics and personal agendas, just in smart concepts and quality code. Our [team](Team) is loosely coupled by a common interest in Darwin and by upholding true Open Source spirit.

### Contributing

Like other open source projects, PureDarwin is looking for contributors for all aspects of the project.

The PureDarwin project is always looking for talented individuals to contribute to and join the project. To contribute to the PureDarwin project, you should first familiarize yourself with the contents of this wiki. You can also join the IRC discussion on the #puredarwin channel on irc.freenode.net or the [Discord server](https://discord.gg/9kz8XXRRcT) and help each other. Contributions to the project can take various forms, from adding documentation to sending in patches and constructive feedback in the [Issues](https://github.com/PureDarwin/PureDarwin/issues) section.

A non-exhaustive list of the fields where investigation has still not been done is available [here](TODO).

### Sponsors

Special thanks to MacStadium for sponsoring a hosted Mac mini. We would also like to thank GitHub for hosting this site and repository and, last but not least, Apple, Inc. for making Darwin available and especially for maintaining the DarwinBuild project.

### Frequently asked questions

#### Why spend time on Darwin?

For learning and fun.

#### How does PureDarwin relate to the former OpenDarwin project?

Although some people have been seeing PureDarwin as the informal successor to OpenDarwin, there is no official relationship other than the fact that OpenDarwin and PureDarwin are both downstream Darwin projects. Also, it is no secret that PureDarwin would not exist if OpenDarwin had not closed down. Coming later in time, PureDarwin is in the fortunate position to be able to benefit from the valuable contributions that were rooted in the OpenDarwin project.

#### How does PureDarwin relate to the DarwinBuild project? 

[DarwinBuild](/developers/Using%20DarwinBuild/DarwinBuild) is one of PureDarwin's main upstream projects. 

#### What does the "Pure" in PureDarwin stand for?

[Pure as in beer](http://en.wikipedia.org/wiki/Reinheitsgebot)! It means that we just use components specifically released by Apple for use with Darwin, as well as other Open Source components (collectively called "upstream code"). Specifically, it means that we do not use any components from Mac OS X. It also means that we try to stay as close as possible to the "outside world" as in Mac OS X (e.g., regarding the choice of compilers, options, etc.). It does *not* mean, however, that we do not modify and add to the upstream code, to the extent that the respective licenses allow.

#### Where can I find an ISO image?

A ready-made VMware virtual machine is available from the [LegacyDownloads](https://github.com/PureDarwin/LegacyDownloads/releases) page. This virtual machine contains an ISO that could be used on real hardware as well. It is a proof-of-concept of a minimal Darwin 9 system built from the DarwinBuild project. Please note that you need the latest VMware (Player 2.5, Fusion 2).

#### When do you plan to release a full ISO image?

Probably when the DarwinBuild project and the MacPorts project will be able to run on a mature PureDarwin release without any "[impurities](/developers/Using%20MacPorts/Purity)".

### PureDarwin Logo

![](/img/PureDarwin.png)
