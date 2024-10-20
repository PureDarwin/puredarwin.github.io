Deploying DarwinBuild on PureDarwin
===================================
This page is about attempting to run DarwinBuild on a PureDarwin system (consequently, making PureDarwin a bit more self-hosted).

### Get Darwinbuild

#### Homebrew

As of 2015, Darwinbuild can be installed using Homebrew, however it fails.

```
brew install --HEAD homebrew/head-only/darwinbuild
(...)
==> Installing darwinbuild from homebrew/homebrew-head-only
==> Cloning http://svn.macosforge.org/repository/darwinbuild/trunk/
==> Patching
patching file common.mk
==> xcodebuild -configuration Release install DSTROOT=/ PREFIX=/usr/local/Cellar/darwinbuild/HEAD SYMROOT=build

The following build commands failed:
	CompileC build/darwinbuild.build/Release/darwinxref.build/Objects-normal/x86_64/cfutils.o darwinxref/cfutils.c normal x86_64 c com.apple.compilers.llvm.clang.1_0.compiler
(1 failure)

READ THIS: https://git.io/brew-troubleshooting
If reporting this issue please do so at (not Homebrew/homebrew):
  https://github.com/homebrew/homebrew-head-only/issues
```

This bug is disucssed on https://github.com/Homebrew/homebrew-head-only/issues/152

#### SVN

```
svn co http://svn.macosforge.org/repository/darwinbuild/trunk darwinbuild
```

#### MacPorts

```
port archive darwinbuild
```

#### DarwinBuild

Unfortunately, there is no `darwinbuild` project in darwinbuild:

```
darwinbuild darwinbuild
ERROR: project not found: darwinbuild
```

Somebody needs to fix that (**TODO:** add `darwinbuild`)

### Compiling Darwinbuild in a PureDarwin chroot

See [Deploying MacPorts on PureDarwin](../macports/macportsonpuredarwin.html) for some prerequisites (gcc stuff and some usefull dev tools).

```
cd /Volumes/PureDarwin
# These dependencies will be needed:
tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/libdyld.root.tar.gz                    
tar xzvf /Volumes/Builds/9G55/Roots/.DownloadCache/Libsyscall.root.tar.gz
```

We will temporary grab an old trick used by darwinbuild previously in order to avoid some project to raise this error: 

```
/bin/sh: dsymutil: command not found

chroot .
cp /usr/bin/true /usr/bin/dsymutil
LDFLAGS=-L/opt/local/lib make

make install

cd somewhere
darwinbuild -init <build version>
```

![](https://raw.github.com/wiki/PureDarwin/PureDarwin/images/osxpddbmp_interact.png)