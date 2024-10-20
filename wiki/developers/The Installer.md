The Installer
=============
This page is a "request for comments" related to the general installation process. Please feel free to contribute and comment.
Through the general install process the installer should be able to also install itself.

The Installation Process
------------------------
Installing PureDarwin should be a two stage process, as illustrated here.


![](/img/developers/repository/the-installer/install.png)
### First stage

The first stage installer is run from either a PureDarwin CD image, or from another operating system on the target computer. The first stage should:

-   Partition the target disk, if desired.
-   Format the target partition.
-   Install the PureDarwin Core package. This will provide all of the utilities and services necessary to allow the second stage installer to complete successfully.
-   Install the appropriate bootloaders (*/usr/standalone/i386 -> install bootloader into MBR (beginning of disk), boot sector (beginning of partition), grub and HFS startup file (alternatively /boot)*), according to user choice and whether it will be a multi-boot system. The user will have the choice of MBR (Chameleon) or EFI. The question should be "Is this a Mac or VMware Fusion?" If they answer "yes", install the EFI bootloader; if they answer "no", install MBR.
-   Reboot the system when done.
![](/img/developers/repository/the-installer/firststage.png)

**
#### Pre-configuration and questions
The user will be asked a quick list of questions. The question must always have a default answer available and "compatible" with all others answers of previous and next questions.
-   **Interactive mode** (advanced)
    Questions, questions and questions...
-   **Semi interactive mode**
-   **Non interactive mode** (full)
    MODE=1
    
-   **Non interactive mode** (automatic)
    MODE=0
    When the second stage installer runs, it should check for the presence of a configuration file in a specific location.
    If it finds it, it should read all settings from here and complete the installation without asking the user any more question. If this file isn't found then it should continue with the standard interactive installation. If not all settings has been provided in the present file, it should continue filling with the default value or (alternatively jump into interactive mode. __Caution__ about this fact, because if "the user" explicitly has chosen "non interactive mode", it is not to fall into interactive mode because 1 settings is missing in the file).

> "Non-interactive mode" will require the user (eg. system admin) to do some extra work. The installer should always automatically attempt to copy non-interactive configuration files from a set location on the boot CD (eg. in /Library/Install/ ) to the target disk. In order to make use of this facility, a boot CD with files in this location should be specially prepared. We can make a root of the install CD, along with the pd_makedmg script, available for download for exactly this purpose.
> 


**
Grouping in categories and sub-categories the sequences of questions seems common. 

This leads us to another possibilities, we could also target a type of PureDarwin release installed (e.g., nano, dev, rescue, test/bench, etc..).




**
__Notes:__ We can't depend on what admin tools are loaded onto the target (having the core system ship without eg. the DSTools package), so user records should be created by generating the data files (a la pd_injectuser) rather than via tools (pd_adduser).
#### Preparation of destination media
Partitioning the destination disk, formatting, installing bootloader. This stage could also see the installation of the kernel(s) and a core system so that the rest of the install process could run from the destination, as outlined above.

__Notes:__ We need to know from where we can put and provide the installation materials and to where the PureDarwin project will be installed. e.g., disk, but we have also: iso and VMware, qemu and other democratised emulation/simulation/virtualisation solution.

#### First Stage Installer Script
An installer script will be needed to guide the user through the first stage installation. A rough idea of how this would work (using the Chameleon bootloader components replacing the standard Darwin ones in /usr/standalone/i386/) is:

Show the user a list of attached drives and ask them to choose one.
Show the user a list of partitions on the chosen drive, and ask them to choose one or enter the fdisk interactive partitioner.
If the user chose to partition the disk, restart the system so that the changes take effect.
Once the user has chosen a disk (number = `$disk`) and partition (number = `$part`) to install on, we can ask them for a volume name (`$name`) to give it, and then without further interaction:
-   `newfs_hfs -s -J -v [$name] /dev/rdisk[$disk]s[$part]`
-   `dd if=/usr/standalone/i386/boot1h of=/dev/rdisk[$disk]s[$part]`
-   `mount -t hfs /dev/disk[$disk]s[$part] /tmp`
-   `cp /usr/standalone/i386/boot /tmp/ `(for MBR)
-   `tar xfz /usr/standalone/PureDarwinCore.root.tar.gz -C /tmp/`
-   `umount /tmp`
-   `echo 'Remove CD-ROM...'`
-   `shutdown -r now`
And we're on to the second stage install.

__
__

Correctly setting up bootloaders is a tricky business, especially in a multi-boot environment. One of the advantages of this two stage approach is that the user will find out if the system can successfully boot into Darwin before spending time installing (potentially involving lengthy downloads) all the packages needed by a complete system. 

**Comment: ***See the *[*boot*](../booting/boot.html)* page for setting up the bootloader*
### Second stage
The second stage installer will be designed to run in a Darwin environment, meaning that it will be exactly the same no matter what the first stage installer was.

![](/img/developers/repository/the-installer/secondstage.png)

In this way we will be moving the environment-specific parts of setup into the first stage (of which there will be a few different platform-specific versions), consequently we only need to maintain a single version of the main installation code.
It will possibly need access to a network connection, although providing a local cache of packages will make this unnecessary.

"PureDarwin Core" is basically (in minimal PureDarwin installation which automatically runs a setup and install script at boot) allowing the user to add extra packages to.
It should be possible for the user to chose not to install anything an be left with a working, bare-bones system.

("PureDarwin Boot" above is a fictional version of Nano equipped with the extra packages needed to run `pd_setup`)
#### Copying across and installing packages
This is covered on the [Package management](../package-management.html) page.
#### Post-configuration
This will include adding users (a default one is provided if no user account has been created) to the system and some settings.

The choices (configuring details such as the system timezone, preferred language, keyboard layouts, etc...) made by the user at the "pre-configuration" phase let the installation to be finish without the user waiting around..
------------------------------------------------------------------------
*A final question could be (or not) to fall into a shell or to reboot (on timeout too).*

