Package management
==================
Historically, Darwin did not have package management. However, DarwinBuild has many elements already in place to make one.
 This page is for discussion what needs to be there, what is already there, and what hence needs to be done.
<span style="font-weight:bold">This page is currently in brainstorming mode. Please join the discussion!</span>

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** What needs to be there](package-management.html#TOC-What-needs-to-be-there)
2.  [**2** What is already there](package-management.html#TOC-What-is-already-there)
3.  [**3** darwinup](package-management.html#TOC-darwinup)
4.  [**4** What needs to be done](package-management.html#TOC-What-needs-to-be-done)
    1.  [**4.1** "Glue" language to use: python? ](package-management.html#TOC-Glue-language-to-use:-python-)
    2.  [**4.2** Questions](package-management.html#TOC-Questions)
5.  [**5** Mac OS X](package-management.html#TOC-Mac-OS-X)
6.  [**6** Security](package-management.html#TOC-Security)

### What needs to be there
1.  Find out the version of a (installed/uninstalled) binary root ("package")
2.  Install a binary root, including its run-time dependencies
3.  Uninstall a binary root
4.  Check whether a given binary root is needed by any other binary roots that are currently installed
5.  Find out which files belong to a given binary root
6.  Find out which binary root a given file belongs to
7.  Upgrade a binary root (taking into consideration its dependencies)
8.  Prevent different binary roots from overwriting each other's files
9.  Repair permissions
10. Download binary roots from repositories (like apt-get or yum)
11. Get package descriptions into the metadata
### What is already there
-   The [xref database](darwinbuild/xref.html), which is populated at build time, and which includes information about versions and build- and run-time dependencies (but <span style="color:rgb(255,0,0)">no versions thereof? However, DarwinBuild is monolithic in the sense that every 9C31 project depends on other 9C31 projects ONLY</span>)
-   A mechanism to package binary roots into archives (tar.gz, xar)
-   Darwin manifests, which contain information about which installed file belongs to which installed binary root, checksums, and permissions
-   [darwinup](http://darwinbuild.macosforge.org/trac/browser/trunk/darwinup/NOTES), the Darwin Update utility, which according to its description, "provides a transaction-based mechanism to install software on the base system that modifies or supersedes existing system components.  Darwin Update is not a "package manager," and does not specify any package format.  Updates can be installed from a directory, a tar archive, or other formats."
### darwinup
darwinup looks like a useful tool, and it appears to be under currently development (check the timeline on the Darwinbuild MacOSForge page). It is provided as part of the darwinbuild source code, and is built and installed along with the other darwinbuild tools. We would recommend that you then install it in /usr/sbin on your Darwin installation.
darwinup will provide the final leg of the installation/deinstallation process: installing packages from the local disk and tracking which files are affected by each operation.
darwinbuild requires that the bzip2 package is installed. This is not currently provided by PureDarwinXmas, and there is no binary root available for it, but it seems to build without problems.
darwinup can install from a .tar, .tar.gz, .tar.bz or even .pkg. (It can also install a directory, in the style of uncompressed binary roots).
<span>    <span style="font-family:courier new,monospace">darwinup install /Users/Shared/curl-42.tar.gz</span></span>
<span>    <span style="font-family:courier new,monospace">-- lots of output showing stuff is happening --</span></span><span style="font-family:courier new">
</span>
<span>    <span style="font-family:courier new,monospace">5DAF8472-468B-409B-A037-E8A7DD0F6E4E</span></span><span style="font-family:courier new">
</span>
<span style="font-family:arial,sans-serif">The final line is the UUID under which the package was installed. The UUIDs of all installed packages can be shown using the list command, and can be used to un-install packages:</span>
<span>    <span style="font-family:courier new,monospace">darwinup uninstall </span></span><span style="font-family:courier new">5DAF8472-468B-409B-A037-E8A7DD0F6E4E</span>
These UUIDs are a very good example of why a user-friendly package management system is needed.
### What needs to be done
-   The metadata contained in the xref database must go into the binary root packages ([initial progress](http://lists.macosforge.org/pipermail/darwinbuild-dev/2005-September/000168.html))
-   An installer must be written which interprets this metadata and stores it in the target machine's xref database, and that makes use of darwinup
-   An uninstaller must be written which interprets the metadata from the xref db and the darwin receipts and/or darwinup. [It is possible that darwinup keeps a "reference count" for all packages, only removing them when all packages needing them are gone. This will have to be looked into. If it is correct, this simplifies this part of uninstallation: we can tell darwinup to remove a package and all of its dependencies, and darwinup can then decide what needs to actually be deleted.]
-   A higher-level tool must be written which resolves run-time dependencies and downloads the appropriate binary root packages from the repositories (although current DarwinBuild is designed as "monolithic", i.e. "the OS" = 1 unit)
#### "Glue" language to use: python? 
-   Available on Darwin, Mac OS X, and (almost) anywhere alse
-   Can talk to sqlite3 (xref) easily
-   Can parse plists with [python-plist](http://odz.sakura.ne.jp/toys/wiki/python-plist)
-   Can use tgz, tbz2 files with [tarfile](http://aspn.activestate.com/ASPN/Cookbook/Python/Recipe/299412) and xar files with [pyxar](http://code.google.com/p/xar/wiki/pyxar)
-   Needs no compilation, supports rapid prototyping and changing
-   Easy to learn and understand
#### Questions
-   darwinxref exportProject -xml nano
     seems not to include versions of the dependencies (this apparently comes from the fact that the DarwinBuild database was conceived as monolithic and "completely filled" once an OS release is made.) <span style="font-weight:bold">The key information here is that packages from one build version always depend on packages of the same build version (e.g., 9C31) ONLY.</span>
-   Integrate <span>[<span style="font-size:large">smartpm</span>](http://labix.org/smart)</span>? Integrate <span style="font-size:large">[rpm](http://lists.macosforge.org/pipermail/macports-dev/2007-July/002087.html)</span> which MacPorts apparently uses? Integrate <span style="font-size:large">[dpkg](http://www.finkproject.org/faq/index.php?phpLang=en)</span> which Fink uses?
### Mac OS X
Let's, for a minute, look at how Mac OS X does things.
It comes with an utility called pkgutil which comes closest to a package manager (but at the same time lacks important functionality):
    sh-3.2# pkgutil --file-info $(which pkgutil)
    volume: /
    path: usr/sbin/pkgutil
    pkgid: com.apple.pkg.BaseSystem
    pkg-version: 10.5.0.1.1.1192168948
    install-time: 1193314189
    uid: 0
    gid: 0
    mode: 100555
    pkgid: com.apple.pkg.update.os.10.5.1
    pkg-version: 1.0.1.1191932192
    install-time: 1195808274
    uid: 0
    gid: 0
    mode: 100555
    pkgid: com.apple.pkg.update.os.10.5.3.combo
    pkg-version: 1.0.1.1191932192
    install-time: 1212138511
    uid: 0
    gid: 0
    mode: 100555
Its man page states that "Package dependency analysis and reference counting are not yet available, hence there is no --uninstall command yet". See the [installer-dev](http://lists.apple.com/mailman/listinfo/installer-dev) mailing list for more information.
### Security
RPM depends/relies on gnupg backend in order to check integrity.
The default keyring can be spoofed with a bad keyring which can lead to validate compromised binary if somebody change the <span style="font-style:italic">$GPGPATH</span> variable or the macro <span style="font-style:italic">$_gpg_path</span>.
Also md5sum can be hooked too, take care.


