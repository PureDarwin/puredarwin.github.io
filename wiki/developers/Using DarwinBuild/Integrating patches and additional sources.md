Integrating patches and additional sources
==========================================
This page describes how to create a custom plist that inherits from another plist, but adds some new sources and patches.

```
# Create the patch
cd BuildRoot/SourceCache/launchd
cp launchd-258.1/ launchd-258.1.pd1/
# do the editing...
diff -ru launchd-258.1/ launchd-258.1.pd1/ > ../../../Sources/launchd-258.1.p1.patch
cd -
# Apply the patch
cd Sources/
tar xfvz launchd-258.1.tar.gz
cd launchd-258.1/
patch -p1 -r . < ../launchd-258.1.p1.patch 
# can then add this patch to the plist as described below, so that it gets applied automatically by DarwinBuild
```

### Why use a custom plist?

By default, DarwinBuild uses the sources that are specified in the .plist ([property list](http://en.wikipedia.org/wiki/Property_list)) files that describe each build version. It is, however, possible to define a new build version that incorporates certain changes, such as entirely new/different source files or even patches.

This is useful for downstream projects like PureDarwin, since we can take most of the upstream's codebase and customize (or "subclass") it. By doing so, we inherit a working build system as well.

#### Editing plists

Property list files can be edited using any text editor. On Mac OS X, they can also be comfortably edited with the Property List Editor that comes with Xcode Tools. Mac OS X also comes with `plutil`, a command line tool that can be used to verify that the syntax of a plist file is correct.

### Sample custom plist

Below is an example that shows how to specify patchfiles or entirely new source tarballs. 
    In .build/, you would have to create a new file called 9C31pd1.plist in addition to the 9C31.plist that is already there, with the following content (this is just an example):
```
    // !$*UTF8*$!
    {
            build = 9C31pd1;
            inherits = 9C31;
            projects = {
                    xnu = {
                            patchfiles = (
                    "xnu-1228.3.13_pd1.p1.patch",
                );
                    };
            boot = {
                version = "132_dfe_r122";
                source_sites = (
                    "http://tgwbd.org/darwin/downloads/",
                );
            };
            };
            source_sites = (
            "http://src.macosforge.org/Projects/", 
                    "http://src.puredarwin.org/",
            );
    }
```

To make DarwinBuild use the new plist, you have to

```
darwinbuild -init 9C31pd1
```

Now DarwinBuild will use the modifications specified in the file above. Specifically:
-   Everything is inherited from 9C31.plist, except for the PureDarwin-specific changes defined in this file, 9C31pd1.plist
-   When you do "darwinbuild xnu", then DarwinBuild will attempt to download a patch from http://src.macosforge.org/Projects/xnu-1228.3.13-pd1.p1.patch and (if it does not exist there) from http://src.puredarwin.org/xnu-1228.3.13-pd1.p1.patch (in that order), and apply that patch to xnu prior to building xnu
-   When you do "darwinbuild build", then DarwinBuild will attempt to download the sources from http://tgwbd.org/darwin/downloads/boot-132_dfe_r122.tar.gz instead of the usual source location.

### File name conventions

DarwinBuild assumes certain conventions are met with regard to filenames.
-   If you have a **source tarball**, it should be named projectname-version.tar.gz
     Note that a version must always be specified, added to the project name (upper/lowercase matters) with a dash, and followed by `.tar.gz`
     Example: `ACPIPS2Nub-1.tar.gz`
-   If you have a **patch**, it should be named with the name, a dash, version, followed by `.p0.patch`
     Example: `boot-132_dfe_r122.p0.patch`
-   If you have a **set of patches** for a given project, make a tarball named `project-version-patches.tar.gz`, which extracts to project-version-patches.  DarwinBuild will then apply each of the patches in that directory.
     Example: `boot-132-patches.tar.gz`
Otherwise DarwinBuild will be unable to download, unpack, patch, and build the sources as intended.