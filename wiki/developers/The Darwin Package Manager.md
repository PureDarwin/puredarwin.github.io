The Darwin Package Manager
==========================

This is Stuart and Aladin's proposal for "dm", a Darwin Package Manager. It is based on the discussion on the [Package management](../package-management.html) page.

Feel free to rip it apart.

### Scope

"dm" will be a command line tool used to manage the darwinbuild components of a Darwin system, namely:

-   Binary roots available from src.macosforge.org/Roots
-   Patched binaries from code.google.com/p/puredarwin (inc. PureDarwin pd_* scripts and PureFoundation)

These locations would be checked in turn for binaries, in the same way that darwinbuild currently checks for patch files and tarballs.
#### Supersets

darwinup

darwinxref


(patched MacPorts?)
#### Subsets

"dm" would also be used to install other package managers (e.g., MacPorts), which would then be used to install other packages.

 (is a tweaked DarwinBuild where the pseudo-chroot is in fact the root (/) plausible?)



#### Mandatory files involved at run-time

The Darwin Package Manager should take a filename (if possible) which does not exist in any UNIX distribution and/or GNU/Linux distro.

Some propositions for the filename crossed with other involved filenames (if possible too) described later:

-   dm (*Darwin package Database*)
    pdpd or pd2 (
-   
-   dtpm (Darwin's Trivial Package Manager)
-   dtbi (Darwin's Trivial Binary Installer)






Where the "dm" tool should be installed has to be discussed, it could be in:


-   `/usr/local/sbin`
    According to *hier* it could also be in /usr/local/sbin and by default "dm" is not included in the basic operating system (Darwin)..
         /usr/         contains the majority of user utilities and applications
                       local/    executables, libraries, etc. not included by the basic operating system
-   <span style="font-family:courier new,monospace"><span style="font-size:small">/usr/sbin/
    <span style="font-family:Arial;font-size:13px">According to *hier..*
    <span style="font-family:courier new;font-size:12px">     /usr/         contains the majority of user utilities and applications
                       sbin/     system daemons & system utilities (executed by users)</span></span></span></span>

-   `/usr/libexec/`
    <span style="font-family:courier new;font-size:12px">     /usr/         contains the majority of user utilities and applications
                       libexec/  system daemons & system utilities (executed by other programs)</span>
-   <span style="font-family:courier new;font-size:12px">/opt/local/bin/port
    <span style="font-family:arial,sans-serif">__Note:__ If we pach `port' from the MacPorts project, then the default location is obvious.</span></span>


  ----------------------------------------------------- --------------------------------------------------------------------------------
  **Filename**        *To be determined*...
  **Permissions**     Admin privileges, executable, read..
                                                        (-r-xr-xr-x root  admin ?)
                                                        Admin users can then use it to add and remove packages as needed.
  **Path**            *To be determined...*
  **Miscellaneous**   The Darwin Package Manager
  ----------------------------------------------------- --------------------------------------------------------------------------------
------------------------------------------------------------------------
The PureDarwin Package Database ("pdpd" or "pd2") is still abstract at this time.
For the potential filename:
-   "pdpd" or "pd2" for PureDarwin Package Database
-   "dpd(b)" for Darwin Package Data(b)ase
__Note:__ If we choose to patch `port' from the MacPorts project, this repository will be useless except if we want to log and/or record in parallel the events.

  ----------------------------------------------------- -------------------------------------------------------------------------
  **Filename**        *To be determined...*
  **Permissions**     *To be determined...*
  **Path**            *To be determined...*
  **Miscellaneous**   The (Pure)Darwin Package Database
                                                        
                                                        
  ----------------------------------------------------- -------------------------------------------------------------------------
------------------------------------------------------------------------
A launchd plist file (`org.puredarwin.xyzt.plist`?) in `/System/Library/LaunchDaemons/`

  ----------------------------------------------------- --------------------------------------------------------------------------------
  **Filename**        org.puredarwin.[*tobedetermined*].plist
  **Permissions**     (-rw-r--r--  root  wheel)
                                                        
  **Path**            /System/Library/LaunchDaemons/
  **Miscellaneous**   Launchd plist (scheduling, update..)
  ----------------------------------------------------- --------------------------------------------------------------------------------

### darwinup

"dm" will use darwinup for the lowest-level installation and un-installation. darwinup works much like a version control system, keeping track of which files are altered during an install so that it can then "roll back" the file system at un-install time. It does not, however, have any idea of dependencies or the ability to fetch files from repositories. These are the features which "dm" will provide.



If we use `darwinup', we could need to list *all* features/possibilities provided by `darwinup', list what we clearly need for a plausible start, and make a diff between both lists.
### The PureDarwin Package Database
Central to "dm" will be the PureDarwin Package Database ("pdpd" or "pd2"). This will be based on a complete package list and dependency information extracted from the darwinxref database, augmented with information about packages provided by PureDarwin and others. The tools described below can help compile this information, but the amount of work involved should not be under estimated. Package management systems simplify matters for the user by shifting the task of tracking and resolving package inter-dependencies to those who administer the packaging system.

-   For simplicity I'm not planning on keeping darwinxref's detailed file list information (the contents of each package). Will this be a problem? Will users want to search for individual files? And if they do, could we just use a wrapper around xref.puredarwin.org to retrieve this info? **Answer:** Each package produced and packages by darwinbuild has a receipt (/usr/local/darwinbuild/receipts/&lt;package&gt;) which lists all of the files added. This will solve the problem for installed packages.

To the data from darwinxref we will add:

-   Localised descriptions of each package
-   "groups" and "systems" information (explained below)

One of the first things "dm" should do when it's run is to check for an updated version of the pd2 database and download it.
### Groups and Systems

Groups and Systems provide a way of grouping collections of packages together to make it easier for the user to choose and install the packages they need.

-   Groups are collections of packages, assembled by theme eg. "web_services" or "perl_and_libraries"
-   Systems are collections of packages, forming complete special-purpose Darwin distributions eg. "full_desktop", "rescue_tools", "office_server", "web_server"

Group and Systems names should never be the same as package names.
### The "core" group

There should be a special "core" group which contains all of the components every PureDarwin installation needs (eg. the kernel(s), launchd, general .KEXTs, the main frameworks). This should always be installed, and cannot be un-installed, but can be updated.



The "core" group could include all of the packages needed to create a network connection and run "dm". We could then make the first stage of the installation process preparing the destination disk and installing the "core" group, with the second part being running "dm" from the destination disk. (This would allow us to provide multiple first stages -- eg. install from LiveCD, Linux, Windows -- with a single common second stage).



The "core" group would probably be written directly to the destination disk and not installed via darwinup.
### Updates

"dm" will have an `--update` mode (possibly scheduled via launchd) which will check for updated versions of the installed packages.

Now, here we have a problem, since by default the binary roots we will be using don't include any version information in their files names. That said, it is very rare for the MacOSForge roots to be updated, and if need be we could add version information to the roots held by PureDarwin.



Update information will have to be dated. "dm" will keep track of when it last checked for updates. It will collect a list of all packages updated since that time, check which of those it has installed, and download these updates.



"dm" should also be also be able to update itself, via several ways (itself, macports, darwinbuild, etc.. at least it should be symetric to the installation ways and perhaps more).
### Security

Different "security" mechanisms could/should be provided, feel free to add and/or strike them:

-   Checksuming (md5, sha-1, sha-2 family, etc..) itself and packages for from integrity to security purposes.
-   If something is remotely retrieved, we should have the possibility (by default that would be nice) to establish a "secure" (many possible ways too..) connection.
-   If "dm" is aware of the resident binaries deployed in the system, checksum could also be possible against them (but it could take some resource, and this kind of process could be moved into a "spotlight-like" daemon).
### Language

"dm" will need to be written in a language which allows the invocation of external commands (darwinup, curl), the processing (regex) and storage of text (the output from darwinup) and database access (pd2). If "dm" is going to be included in the "core" group then so will its support libraries/interpretter. A scripting language seems like the best option.



Mini poll:

-   Stuart suggests Perl: "*but I'm fairly flexible on this point. (Unlike Python and indentations.)*"
-   Aladin suggests to not reinvent the wheel and enhance the MacPorts project in patching `port' and creating special portfile for our needs. Stuart will look into this.
-   Alternatively,  `#!/bin/sh` or Lua (this one is not in the "core" group).
### Usage



So, could it be also possible that "dm" is a patch of `port' command (from the MacPorts project) which extends its functionalities to our needs because a lot of things and good features are already inside. We will provide some specific ports too. We could ask exactly the same for a tweaked darwinbuild which points to root. Also in the installation process, a lot of packages are for "user-land" and comes from darwinbuild (and/or macports) at this time.




 ```--info { package | group | system }`

     `--list { installed | available }`

`--get [config_setting]`

`--set config_setting value`

`--add [options] package_list`

`--remove [options] package_list`

`--update`

 

`--info` displays information about the given package, group or system -- whether it is currently installed, where it can be found, version, dependencies, and in the case of groups and systems, which packages they contain.




`--list` without an argument lists all installed packages. With "available" option, list all packages in the package database.




`--get` without an argument lists the current values of all all `config_settings` (which will have default built-in values, values stored in /etc/dm.config, and can be over-ridden by the `[options]` flags to `--add` and `--remove`). If `config_setting` is provided, the settings for just that setting are displayed.




`--set` sets the value of a particular `config_setting` (after checking that it's valid) and stores it in /etc/dm.config.




`--add` adds the packages in `package_list` to the current Darwin install.




`--remove` removes the packages in `package_list` from the current Darwin install.



 `package_list` 
> is a list of space-separated package, group and system names. If an entry contains a "." or a "/" it is treated as a path to a file, which is read. It is expected to contain a list of package, group or system names, which are then added to the package_list. This will allow custom configurations to be built and used time and again. eg.


> perl python ruby <span style="font-size:small">will add the curl, perl, python and ruby packages
> </span>
> --add recovery_tools file_servers emacs    will add the emacs package, all packages from the file_servers group, and all packages from the recovery_tools system
> --add Chess packages.txt will add the Chess package, and any packages, groups or systems listed in packages.txt




 `options`
> over-ride the defaults stored in /etc/dm.config for the duration of the single command. (This is not a complete list.)



-   --dependencies { YES | NO } -- The dependencies `config_setting`. By default this is YES, meaning that for every package added its dependencies are found and added at the same time. (I'm not really sure about how we handle removing dependencies. Either we store some form of reference count for packages, or we re-check dependencies at the time. Either way, we should stop the user from removing a package which other packages depend on.)
-   --cache directory_path -- The cache `config_setting`. This is checked for packages before remote repositories. This will allow installation from CD images without needing networking.
-   --temp directory_path -- The temp `config_setting`. This is where packages are downloaded to. It is also checked for packages before remote repositories.



`--update` fetches a list of package changes since the last update and compares it to the list of installed packages. It then downloads those packages which have changed and installs them.


### At Installation Time

An interactive installer will present the user with lists of systems, groups or packages for them to choose from. Their choices will then be passed to "dm", which will resolve dependencies, download the packages, and install them.

### Package Database Admin Toold
dbtool.zip below contains a couple of simple Perl scripts, described below. These are a first attempt at producing some tools for creating and managing the package database. These are intended to be used by the packaging system admins, not by the end user. They mostly work on plain text files, so it should be possible to keep all of the associated resources (package lists, language files, core, group and system lists) under revision control and automate the process of producing the package database.
Please also note that at this point I see the "dm" tool more as a binary installer than a fully-fledged package manager.
#### dbaudit
`dbaudit` does a brute-force audit of a darwinbuild environment, finding which packages have binary roots and attempting to calculate dependencies for those that do.
<div style="display:block;margin-right:auto;margin-left:auto;text-align:center">
![](/img/developers/package-management/the-darwin-package-manager/dbaudit.png)
The output package list is a simple text file with one line per package found. Each line has the format:
    PackageName Y build version { dependency1 dependency2 ... dependencyN }
Where "Y" could also be "N" and signals that a binary root was found. If no root was found, no version or dependency information will be provided.
Dependencies are listed as package names, if resolved, or the full path of linked library paths otherwise.
#### dbstats
`dbstats` produces a simple summary of the `dbaudit` output file. The information in this file may go towards providing the dependency information needed by a Darwin package manager.
package_list.zip contains the package list which `dbaudit` produced for a 9G55pd1 install of darwinbuild. It shows:
    `423 packages, 79 missing binary roots, 79 unresolved dependencies`
(The two 79s are purely coincidental and unrelated, I think.)

#### pdpdmake
`pdpdmake` takes a number of input files and either creates or updates a SQLite database file according to their contents.
<div style="display:block;margin-right:auto;margin-left:auto;text-align:center">
![](/img/developers/package-management/the-darwin-package-manager/pdpdmake.png)

As a minimum, at least one package list must be provided.
#### dtbi

`dtbi` (Darwin Trivial Binary Installer) is a Perl prototype of a basic installer for Darwin. It's main purpose is to generate discussion. Currently it will query a pdpd database (there's one produced from the packages_list.txt file below provided as an example) for information about packages. If `darwinup` is installed, `dtbi` will query it for a list of installed packages. It will add a new package, plus any uninstalled packages which that package depends upon, downloading the binary from MacOSForge.



To try `dtbi` in PureDarwinXmas:

1.  Install the CPAN package (Perl modules, needed for database access).
2.  Install `curl` (if you want to try installing packages).
3.  Install `darwinup` (from `darwinbuild`) into /usr/sbin/ (we can argue about where it *should* go later).
4.  Copy `dtbi` and the db database file into the same directory (/Users/Shared/ is nice).

Currently, only the `--info`,` --list` and `--add` options have been implemented. Again, this is just a quick Perl prototype to get people talking and to see if this solves a problem for us. The fact that this version requires 10+Mb of Perl modules suggests we'll actually be using a different language for the production version.



Your comments below or in #puredarwin, please.


