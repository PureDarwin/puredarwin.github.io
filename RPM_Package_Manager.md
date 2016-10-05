RPM Package Manager
===================
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](http://rpm5.org/files/arc/artwork/rpm-logo-150x150.png)](http://rpm5.org/files/arc/artwork/rpm-logo-150x150.png)
The RPM Package Manager is a package manager and package format commonly used for Linux distributions. RPM also runs on Darwin. MacPorts is capable of producing RPMs including depencency information.
This page describes how to use RPM on a PureDarwin system.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** About RPM](rpm.html#TOC-About-RPM)
    1.  [**1.1** RPM in MacPorts](rpm.html#TOC-RPM-in-MacPorts)
    2.  [**1.2** RPM from rpm5.org](rpm.html#TOC-RPM-from-rpm5.org)
2.  [**2** Installing RPM5 on PureDarwin](rpm.html#TOC-Installing-RPM5-on-PureDarwin)
3.  [**3** Building RPMs with MacPorts](rpm.html#TOC-Building-RPMs-with-MacPorts)
4.  [**4** Useful RPM commands](rpm.html#TOC-Useful-RPM-commands)
5.  [**5** Troubleshooting](rpm.html#TOC-Troubleshooting)
    1.  [**5.1** org.macports.darwin9 is needed](rpm.html#TOC-org.macports.darwin9-is-needed)
    2.  [**5.2** Installation fails due to dependencies on itself](rpm.html#TOC-Installation-fails-due-to-dependencies-on-itself)
    3.  [**5.3** Disk fills up quickly](rpm.html#TOC-Disk-fills-up-quickly)
6.  [**6** To be investigated](rpm.html#TOC-To-be-investigated)
7.  [**7** A quick and dirty way to unpack a directory of RPMs](rpm.html#TOC-A-quick-and-dirty-way-to-unpack-a-directory-of-RPMs)
8.  [**8** Thanks](rpm.html#TOC-Thanks)

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


<span style="font-family:courier new,monospace"><span style="font-size:small">port search rpm</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">apt-rpm                        sysutils/apt-rpm 0.5.15lorg3.93 Automatic updater and package installer/remover for RPM</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">rpm                            sysutils/rpm   4.4.9        The RPM package management system.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">[...]</span></span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">rpm50                          sysutils/rpm50 5.0.3        The RPM package management system.</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">rpm51                          sysutils/rpm51 5.1.4        The RPM package management system.</span></span></span>
<span style="color:rgb(68,68,68);font-family:courier new;font-size:12px">
</span>

#### RPM from rpm5.org
The rpm package from rpm5.org is a self-contained bundle that comes with all the dependencies that are not part of Darwin itself.

However, even after it has been installed it says "package rpm is not installed". <span style="color:rgb(255,0,0)">Bug?</span>
### Installing RPM5 on PureDarwin
To install RPM5 on a PureDarwin system, do the following:

1.  Download the dmg from http://rpm5.org/files/rpm/rpm-5.1/BINARY/
2.  Mount the dmg on the Mac, copy RPM5.pkg to the root of the PureDarwin system
3.  On the target system, do: <span><span style="font-size:small"><span style="font-family:courier new,monospace">cd / ; </span></span><span style="border-collapse:separate;line-height:14px;white-space:pre"><span style="font-size:small"><span style="font-family:courier new,monospace">gunzip -c RPM5.pkg/Contents/Archive.pax.gz | pax -r</span></span></span></span>
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
Follow the instructions on the MacPorts page and use <span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/bin/port rpm someproject</span></span>.
Should you get an error about missing parts, then do <span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/bin/port unarchive someproject</span></span> before.
### Useful RPM commands
To run commands on RPMs that are not installed yet, add the <span style="font-family:courier new,monospace"><span style="font-size:small"><span style="font-weight:bold">p</span></span></span> option as shown below.
-   Install a package <span style="font-family:courier new"><span style="font-size:12px">rpm -ivh --noparentdirs somepackage.rpm</span></span>
-   Show which packages are installed <span style="font-family:courier new,monospace"><span style="font-size:small">rpm -qa</span></span>
-   Show information about an package <span style="font-family:courier new,monospace"><span style="font-size:small">rpm -qi </span></span><span style="font-family:courier new,monospace"><span style="font-size:small">somepackage<span style="font-family:Arial;font-size:13px"> or </span>rpm -q<span style="font-weight:bold">p</span>i somepackage<span style="font-weight:bold">.rpm</span></span></span>
-   Show which files are in an package <span style="font-family:courier new,monospace"><span style="font-size:small">rpm -ql somepackage<span style="font-family:Arial;font-size:13px"> or </span>rpm -q<span style="font-weight:bold">p</span>l somepackage<span style="font-weight:bold">.rpm</span></span></span>
-   <span style="font-family:courier new;font-size:12px;font-weight:bold"><span style="font-family:Arial;font-size:13px;font-weight:normal">Show which dependencies a package requires <span style="font-family:courier new,monospace"><span style="font-size:small">rpm -qR somepackage<span style="font-family:Arial;font-size:13px"> or </span>rpm -q<span style="font-weight:bold">p</span><span>R</span> somepackage<span style="font-weight:bold">.rpm</span></span></span></span></span>
-   Remove an installed package <span style="font-family:courier new"><span style="font-size:12px">rpm -e </span></span><span style="font-family:courier new"><span style="font-size:12px">somepackage</span></span>
-   Show help<span style="font-family:courier new;font-size:12px"> rpm --help</span>
### Troubleshooting
#### org.macports.darwin9 is needed
<span style="font-weight:bold">Problem: </span>Each package fails to install with the message "org.macports.darwin9 is needed".
<span style="font-weight:bold">Solution: </span>Satisfy the dependency to org.macports.darwin9 by installing the RPM below. This is a dummy package that contains no actual software but tells the RPM database about the Darwin base system (specifically, the parts installed from DarwinBuild rather than MacPorts). It is based on <http://svn.macports.org/repository/macports/users/afb/macosx-base.spec> and was built with <span style="font-family:courier new,monospace"><span style="font-size:small">rpmbuild -bb macosx-base.spec<span style="font-family:Arial;font-size:13px">. (Todo: Check what the OpenDarwin 7 CD did. Deleting that line from portrpm.tcl might also be an option.)</span></span></span>
#### Installation fails due to dependencies on itself
<span style="font-weight:bold">Problem:</span> When trying to install a package, RPM complains that directories are missing that are either part of the base system or should be part of the package that is about to be installed.


<span style="font-family:courier new,monospace"><span style="font-size:small">bash-3.2# ls /opt/local/</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">bin/     etc/     include/ lib/     share/   src/     var/ </span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small">bash-3.2# rpm -ivh /libiconv-1.12-0.i386.rpm error: Failed dependencies:</span></span></span>
<span style="white-space:pre"><span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/bin is needed by libiconv-1.12-0.i386</span></span></span>
<span style="white-space:pre"><span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/include is needed by libiconv-1.12-0.i386</span></span></span>
<span style="white-space:pre"><span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/lib is needed by libiconv-1.12-0.i386</span></span></span>
<span style="white-space:pre"><span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/share/doc/libiconv-1.12 is needed by libiconv-1.12-0.i386</span></span></span>
<span style="white-space:pre"><span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/share/man/man1 is needed by libiconv-1.12-0.i386</span></span></span>
<span style="white-space:pre"><span><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span></span><span><span style="font-family:courier new,monospace"><span style="font-size:small">/opt/local/share/man/man3 is needed by libiconv-1.12-0.i386</span></span></span>


<span style="font-weight:bold">Solution: </span><span>As a workaround, use <span style="font-family:courier new;font-size:12px">rpm -ivh <span style="font-weight:bold">--noparentdirs</span> somepackage.rpm</span></span>
<span>Sometimes, <span style="font-style:italic">if you really know what you are doing,<span style="font-family:courier new"><span style="font-size:12px"> </span></span><span style="font-style:normal"><span style="font-family:courier new"><span style="font-size:12px">--nodeps</span></span> might also be helpful.
</span></span>Final solution may be related to [this](http://rpm5.org/community/rpm-users/0051.html) - </span><span style="color:rgb(255,0,0)">please let us know.</span>
#### Disk fills up quickly
<span style="font-weight:bold">Problem: </span>When using RPM a lot, the disk fills up quickly.
<span style="font-weight:bold">Solution:</span> By default, RPM5 saves any RPM that you uninstall in /var/local/spool/repackage/.
This can be disabled by changing %repackage_all_erasures to 0 in <span style="border-collapse:separate;font-family:arial">/usr/local/lib/rpm/macros.</span>
### To be investigated
<span style="border-collapse:separate">OpenDarwin 6.2.2 had RPMs for the projects in DarwinBuild. How were these made?</span>
<span style="border-collapse:separate">
</span>
<span style="border-collapse:separate"></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">sh-3.2# rpm -qip /Volumes/OpenDarwin6.6.2/System/Installation/RPMS/org.opendarwin.misc_cmds-6.6.2-4.fat.rpm</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">Name        : org.opendarwin.misc_cmds     Relocations: (not relocatable)</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">Version     : 6.6.2                             Vendor: OpenDarwin</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">Release     : 4                             Build Date: Sun Jul  6 10:15:26 2003</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">Install Date: (not installed)               Build Host: lamancha.opendarwin.org</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">Group       : System                        Source RPM: org.opendarwin.misc_cmds-6.6.2-4.src.rpm</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">Size        : 490564                           License: ?</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">Signature   : (none)</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">Summary     : misc_cmds</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">Description :</span></span>
<span style="font-size:x-small"><span style="font-family:courier new,monospace">OpenDarwin project misc_cmds</span></span>

According to #opendarwin, these were built before DarwinBuild was around. A Perl script was used to generate RPM spec files, and the contents od the DSTROOT was packaged up.

### A quick and dirty way to unpack a directory of RPMs
<span style="font-family:courier new,monospace"><span style="font-size:small">UNP=$(find i386/*.rpm)  && for UN in $UNP; do ./opt/local/bin/rpm2cpio  $UN | cpio -i -d -v ; done</span></span>


### Thanks
afb from #macports contributed knowledge to this page.
