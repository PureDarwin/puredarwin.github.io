Development environments
========================
draft.
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Status](development-environments.html#TOC-Status)
    1.  [**1.1** gcc](development-environments.html#TOC-gcc)
    2.  [**1.2** llvm](development-environments.html#TOC-llvm)

Status
------
Most of libraries, headers and developer tools (e.g. a compiler) comes from the Darwinbuild project and/or the MacPorts project.
### gcc
<span style="font-size:small">gcc -v</span>
<span style="font-size:small">Using built-in specs.</span>
<span style="font-size:small">Target: i686-apple-darwin9</span>
<span style="font-size:small">Configured with: /Volumes/One/darwin-build-testing/9A581/BuildRoot/private/var/tmp/gcc/gcc-5465.obj/src/configure --disable-checking -enable-werror --prefix=/usr --mandir=/share/man --enable-languages=c,objc,c++,obj-c++ --program-transform-name=/^[cg][^.-]*$/s/$/-4.0/ --with-gxx-include-dir=/include/c++/4.0.0 --with-slibdir=/usr/lib --build=i686-apple-darwin9 --with-arch=apple --with-tune=generic --host=i686-apple-darwin9 --target=i686-apple-darwin9</span>
<span style="font-size:small">Thread model: posix</span>
<span style="font-size:small">gcc version 4.0.1 (Apple Inc. build 5465)</span>
### llvm

<span style="font-size:small">llvmc --version</span>
<span style="font-size:small">Low Level Virtual Machine (http://llvm.org/):</span>
<span style="font-size:small">  llvm version 2.5</span>
<span style="font-size:small">  Optimized build with assertions.</span>
<span style="font-size:small">  Built Jul 30 2009(19:01:55).</span>


llvm (Low Level Virtual Machine) from <http://llvm.org/> can be built and installed in a chroot at this time:

<span style="font-size:small">[...]</span>
<span style="font-size:small">llvm[4]: ======= Finished Linking Release Executable Sample (without symbols)</span>
<span style="font-size:small">make[1]: Nothing to be done for `all'.</span>
<span style="font-size:small">llvm[0]: ***** Completed Release Build</span>


