RPM Package Manager
===================
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](http://rpm5.org/files/arc/artwork/rpm-logo-150x150.png)](http://rpm5.org/files/arc/artwork/rpm-logo-150x150.png)
The RPM Package Manager is a package manager and package format commonly used for Linux distributions. RPM also runs on Darwin. MacPorts is capable of producing RPMs including depencency information.
This page describes how to use RPM on a PureDarwin system.

### About RPM
![](http://archiv.tu-chemnitz.de/pub/2006/0178/data/rpm_logo.png)

RPM is the package manager and package format used by Red Hat, Novell/SUSE, Mandriva, and other Linux distributions.
It is located at <http://rpm.org/> 

<div style="display:inline;float:left;margin-top:5px;margin-right:10px;margin-bottom:0px;margin-left:0px">
[![](http://rpm5.org/files/arc/artwork/rpm-logo-150x150.png)](http://rpm5.org/files/arc/artwork/rpm-logo-150x150.png)

RPM5 is a branch of RPM located at rpm5.org.
Although both have common roots, it is not the branch of RPM that is used by Red Hat, for example.
It is located at <http://rpm5.org/> 
More about the differences can be found [here](http://trainofthoughts.org/blog/2008/01/06/rpm5-vs-rpm/), for example.


#### RPM in MacPorts
MacPorts provides ports for RPM. However, there is a chicken-and-egg problem because RPM and its dependencies need to be installed before RPM can be used itself.


`port search rpm`
`apt-rpm                        sysutils/apt-rpm 0.5.15lorg3.93 Automatic updater and package installer/remover for RPM`
`rpm                            sysutils/rpm   4.4.9        The RPM package management system.`
`[...]`

`rpm50                          sysutils/rpm50 5.0.3        The RPM package management system.`
`rpm51                          sysutils/rpm51 5.1.4        The RPM package management system.`



#### RPM from rpm5.org
The rpm package from rpm5.org is a self-contained bundle that comes with all the dependencies that are not part of Darwin itself.

However, even after it has been installed it says "package rpm is not installed". Bug?
### Installing RPM5 on PureDarwin
To install RPM5 on a PureDarwin system, do the following:

1.  Download the dmg from http://rpm5.org/files/rpm/rpm-5.1/BINARY/
2.  Mount the dmg on the Mac, copy RPM5.pkg to the root of the PureDarwin system
3.  On the target system, do: 
This installs RPM5 to /usr/local/bin/rpm. The RPM database is located at /var/local/lib/rpm/.

Make sure the following depenencies are met on the PureDarwin system:
-   /usr/lib/libbz2.1.0.dylib
-   /usr/lib/libxml2.2.dylib (DarwinBuild project libxml2)
-   /usr/lib/libSystem.B.dylib
-   /usr/lib/libz.1.dylib
-   /usr/lib/libiconv.2.dylib
-   /usr/lib/libssl.0.9.7.dylib (DarwinBuild project OpenSSL)
-   /usr/lib/libcrypto.0.9.7.dylib
-   /usr/lib/libgcc_s.1.dylib
### Building RPMs with MacPorts
Follow the instructions on the MacPorts page and use `/opt/local/bin/port rpm someproject`.
Should you get an error about missing parts, then do `/opt/local/bin/port unarchive someproject` before.
### Useful RPM commands
To run commands on RPMs that are not installed yet, add the `p` option as shown below.
-   Install a package rpm -ivh --noparentdirs somepackage.rpm
-   Show which packages are installed `rpm -qa`
-   Show information about an package `rpm -qi ``somepackage or rpm -q**p**i somepackage**.rpm**`
-   Show which files are in an package `rpm -ql somepackage or rpm -q**p**l somepackage**.rpm**`
-   **Show which dependencies a package requires `rpm -qR somepackage or rpm -qpR somepackage.rpm**
-   Remove an installed package rpm -e somepackage
-   Show help rpm --help
### Troubleshooting
#### org.macports.darwin9 is needed
**Problem: **Each package fails to install with the message "org.macports.darwin9 is needed".
**Solution: **Satisfy the dependency to org.macports.darwin9 by installing the RPM below. This is a dummy package that contains no actual software but tells the RPM database about the Darwin base system (specifically, the parts installed from DarwinBuild rather than MacPorts). It is based on <http://svn.macports.org/repository/macports/users/afb/macosx-base.spec> and was built with ``
#### Installation fails due to dependencies on itself
**Problem:** When trying to install a package, RPM complains that directories are missing that are either part of the base system or should be part of the package that is about to be installed.


`bash-3.2# ls /opt/local/`
bin/     etc/     include/ lib/     share/   src/     var/ 
`
`
bash-3.2# rpm -ivh /libiconv-1.12-0.i386.rpm error: Failed dependencies:
 /opt/local/bin is needed by libiconv-1.12-0.i386
 /opt/local/include is needed by libiconv-1.12-0.i386
 /opt/local/lib is needed by libiconv-1.12-0.i386
 /opt/local/share/doc/libiconv-1.12 is needed by libiconv-1.12-0.i386
 /opt/local/share/man/man1 is needed by libiconv-1.12-0.i386
 /opt/local/share/man/man3 is needed by libiconv-1.12-0.i386


**Solution: **
please let us know.
#### Disk fills up quickly
**Problem: **When using RPM a lot, the disk fills up quickly.
**Solution:** By default, RPM5 saves any RPM that you uninstall in /var/local/spool/repackage/.
This can be disabled by changing %repackage_all_erasures to 0 in /usr/local/lib/rpm/macros.
### To be investigated
OpenDarwin 6.2.2 had RPMs for the projects in DarwinBuild. How were these made?



sh-3.2# rpm -qip /Volumes/OpenDarwin6.6.2/System/Installation/RPMS/org.opendarwin.misc_cmds-6.6.2-4.fat.rpm
Name        : org.opendarwin.misc_cmds     Relocations: (not relocatable)
Version     : 6.6.2                             Vendor: OpenDarwin
Release     : 4                             Build Date: Sun Jul  6 10:15:26 2003
Install Date: (not installed)               Build Host: lamancha.opendarwin.org
Group       : System                        Source RPM: org.opendarwin.misc_cmds-6.6.2-4.src.rpm
Size        : 490564                           License: ?
Signature   : (none)
Summary     : misc_cmds
Description :
OpenDarwin project misc_cmds

According to #opendarwin, these were built before DarwinBuild was around. A Perl script was used to generate RPM spec files, and the contents od the DSTROOT was packaged up.

### A quick and dirty way to unpack a directory of RPMs
<span style="font-family:courier new,monospace"><span style="font-size:small">UNP=$(find i386/*.rpm)  && for UN in $UNP; do ./opt/local/bin/rpm2cpio  $UN | cpio -i -d -v ; done</span></span>


### Thanks
afb from #macports contributed knowledge to this page.
