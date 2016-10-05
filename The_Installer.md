The Installer
=============
This page is a "request for comments" related to the general installation process. Please feel free to contribute and comment.
Through the general install process the installer should be able to also install itself.


<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:456px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** The Installation Process](the-installer.html#TOC-The-Installation-Process)
    1.  [**1.1** First stage](the-installer.html#TOC-First-stage)
        1.  [**1.1.1** Pre-configuration and questions](the-installer.html#TOC-Pre-configuration-and-questions)
        2.  [**1.1.2** Preparation of destination media](the-installer.html#TOC-Preparation-of-destination-media)
        3.  [**1.1.3** First Stage Installer Script](the-installer.html#TOC-First-Stage-Installer-Script)
    2.  [**1.2** Second stage](the-installer.html#TOC-Second-stage)
        1.  [**1.2.1** Copying across and installing packages](the-installer.html#TOC-Copying-across-and-installing-packages)
        2.  [**1.2.2** Post-configuration](the-installer.html#TOC-Post-configuration)

The Installation Process
------------------------
Installing PureDarwin should be a two stage process, as illustrated here.

<div style="text-align:left;display:block;margin-right:auto;margin-left:auto">
[![](../../_/rsrc/1263242453465/developers/repository/the-installer/install.png%3Fheight=221&width=420)](the-installer/install.png%3Fattredirects=0)
### First stage
<div style="text-align:left;display:block;margin-right:auto;margin-left:auto">
The first stage installer is run from either a PureDarwin CD image, or from another operating system on the target computer. The first stage should:
<div style="text-align:left;display:block;margin-right:auto;margin-left:auto">
-   Partition the target disk, if desired.
-   Format the target partition.
-   Install the PureDarwin Core package. This will provide all of the utilities and services necessary to allow the second stage installer to complete successfully.
-   Install the appropriate bootloaders (<span style="font-style:italic">/usr/standalone/i386 -&gt; install bootloader into MBR (beginning of disk), boot sector (beginning of partition), grub and HFS startup file (alternatively /boot)</span>), according to user choice and whether it will be a multi-boot system. The user will have the choice of MBR (Chameleon) or EFI. The question should be "Is this a Mac or VMware Fusion?" If they answer "yes", install the EFI bootloader; if they answer "no", install MBR.
-   Reboot the system when done.
[![](../../_/rsrc/1263242453465/developers/repository/the-installer/firststage.png)](the-installer/firststage.png%3Fattredirects=0)
<div style="text-align:left;display:block;margin-right:auto;margin-left:auto">
<span style="font-style:italic"><span style="font-style:normal"></span></span>
#### Pre-configuration and questions
The user will be asked a quick list of questions. The question must always have a default answer available and "compatible" with all others answers of previous and next questions.
-   <span style="font-weight:bold">Interactive mode</span> (advanced)
    Questions, questions and questions...<span style="border-collapse:separate;font-family:arial"> settings in details can be set.
    <span style="border-collapse:collapse;color:rgb(39,78,19);font-family:Arial">MODE=3</span> </span>
-   <span style="border-collapse:separate;font-weight:bold">Semi interactive mode</span><span style="border-collapse:separate"> (standard)
    Questions and questions.
    <span style="border-collapse:collapse;color:rgb(39,78,19)">MODE=2</span></span>
-   <span style="border-collapse:separate"><span style="font-weight:bold">Non interactive mode</span> (full)
    <span style="border-collapse:collapse;color:rgb(39,78,19)">MODE=1</span>
    <span style="border-collapse:collapse">Provide a<span style="border-collapse:separate;color:rgb(51,51,51)"><span style="font-family:arial,sans-serif"><span style="font-size:small"><span style="color:rgb(0,0,0)"> fast and rough</span></span></span><span style="font-family:arial,sans-serif"><span style="font-size:small"><span style="color:rgb(0,0,0)"> default setup with everything</span></span></span></span></span></span>
-   <span style="font-weight:bold">Non interactive mode</span> (automatic)
    <span style="color:rgb(39,78,19)">MODE=0</span>
    When the second stage installer runs, it should check for the presence of a configuration file in a specific location.
    If it finds it, it should read all settings from here and complete the installation without asking the user any more question. If this file isn't found then it should continue with the standard interactive installation. If not all settings has been provided in the present file, it should continue filling with the default value or (alternatively jump into interactive mode. <span style="text-decoration:underline">Caution</span> about this fact, because if "the user" explicitly has chosen "non interactive mode", it is not to fall into interactive mode because 1 settings is missing in the file).

> "Non-interactive mode" will require the user (eg. system admin) to do some extra work. The installer should always automatically attempt to copy non-interactive configuration files from a set location on the boot CD (eg. in /Library/Install/ ) to the target disk. In order to make use of this facility, a boot CD with files in this location should be specially prepared. We can make a root of the install CD, along with the pd_makedmg script, available for download for exactly this purpose.
> 

<div style="text-align:left;display:block;margin-right:auto;margin-left:auto">
<span style="font-style:italic"><span style="font-style:normal"></span></span>
Grouping in categories and sub-categories the sequences of questions seems common. 

<span style="border-collapse:separate">This leads us to another possibilities, we could also target a type of PureDarwin release installed (e.g., nano, dev, rescue, test/bench, etc..).</span>



<div style="text-align:left;display:block;margin-right:auto;margin-left:auto">
<span style="font-style:italic"><span style="font-style:normal"></span></span>
<span style="text-decoration:underline">Notes:</span> We can't depend on what admin tools are loaded onto the target (having the core system ship without eg. the DSTools package), so user records should be created by generating the data files (a la pd_injectuser) rather than via tools (pd_adduser).
#### Preparation of destination media
Partitioning the destination disk, formatting, installing bootloader. This stage could also see the installation of the kernel(s) and a core system so that the rest of the install process could run from the destination, as outlined above.

<span style="text-decoration:underline">Notes:</span> We need to know from where we can put and provide the installation materials and to where the PureDarwin project will be installed. e.g., disk, but we have also: iso and VMware, qemu and other democratised emulation/simulation/virtualisation solution.

#### First Stage Installer Script
An installer script will be needed to guide the user through the first stage installation. A rough idea of how this would work (using the Chameleon bootloader components replacing the standard Darwin ones in /usr/standalone/i386/) is:

Show the user a list of attached drives and ask them to choose one.
Show the user a list of partitions on the chosen drive, and ask them to choose one or enter the fdisk interactive partitioner.
If the user chose to partition the disk, restart the system so that the changes take effect.
Once the user has chosen a disk (number = <span style="font-family:courier new,monospace">$disk</span>) and partition (number = <span style="font-family:courier new,monospace">$part</span>) to install on, we can ask them for a volume name (<span style="font-family:courier new,monospace">$name</span>) to give it, and then without further interaction:
-   <span style="font-family:courier new,monospace"><span style="font-size:small">newfs_hfs -s -J -v [$name] /dev/rdisk[$disk]s[$part]</span></span>
-   <span style="font-family:courier new,monospace"><span style="font-size:small">dd if=/usr/standalone/i386/boot1h of=/dev/rdisk[$disk]s[$part]</span></span>
-   <span style="font-family:courier new,monospace"><span style="font-size:small">mount -t hfs /dev/disk[$disk]s[$part] /tmp</span></span>
-   <span style="font-family:courier new,monospace"><span style="font-size:small">cp /usr/standalone/i386/boot /tmp/ </span></span><span><span style="font-family:arial,sans-serif"><span style="font-size:small">(for MBR)</span></span></span>
-   <span style="font-family:courier new,monospace"><span style="font-size:small">tar xfz /usr/standalone/PureDarwinCore.root.tar.gz -C /tmp/</span></span>
-   <span style="font-family:courier new,monospace"><span style="font-size:small">umount /tmp</span></span>
-   <span style="font-family:courier new,monospace"><span style="font-size:small">echo 'Remove CD-ROM...'</span></span>
-   <span style="font-family:courier new,monospace"><span style="font-size:small">shutdown -r now</span></span>
And we're on to the second stage install.

<span style="color:rgb(85,26,139);text-decoration:underline">
</span>

Correctly setting up bootloaders is a tricky business, especially in a multi-boot environment. One of the advantages of this two stage approach is that the user will find out if the system can successfully boot into Darwin before spending time installing (potentially involving lengthy downloads) all the packages needed by a complete system. 

<span style="font-weight:bold"><span style="font-style:italic">Comment: </span></span><span style="font-style:italic">See the </span>[<span style="font-style:italic">boot</span>](../booting/boot.html)<span style="font-style:italic"> page for setting up the bootloader</span>
### Second stage
The second stage installer will be designed to run in a Darwin environment, meaning that it will be exactly the same no matter what the first stage installer was.

[![](../../_/rsrc/1263242453465/developers/repository/the-installer/secondstage.png)](the-installer/secondstage.png%3Fattredirects=0)

In this way we will be moving the environment-specific parts of setup into the first stage (of which there will be a few different platform-specific versions), consequently we only need to maintain a single version of the main installation code.
It will possibly need access to a network connection, although providing a local cache of packages will make this unnecessary.

"PureDarwin Core" is basically (in minimal PureDarwin installation which automatically runs a setup and install script at boot) allowing the user to add extra packages to.
It should be possible for the user to chose not to install anything an be left with a working, bare-bones system.

("PureDarwin Boot" above is a fictional version of Nano equipped with the extra packages needed to run <span style="font-family:courier new,monospace"><span style="font-size:small">pd_setup</span></span>)
#### Copying across and installing packages
This is covered on the [Package management](../package-management.html) page.
#### Post-configuration
This will include adding users (a default one is provided if no user account has been created) to the system and some settings.

The choices (configuring details such as the system timezone, preferred language, keyboard layouts, etc...) made by the user at the "pre-configuration" phase let the installation to be finish without the user waiting around..
------------------------------------------------------------------------
<span style="font-style:italic">A final question could be (or not) to fall into a shell or to reboot (on timeout too).</span>

