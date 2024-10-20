# Development environments

draft.

## Status
Most of libraries, headers and developer tools (e.g. a compiler) comes from the Darwinbuild project and/or the MacPorts project.

### gcc
gcc -v
Using built-in specs.
Target: i686-apple-darwin9
Configured with: /Volumes/One/darwin-build-testing/9A581/BuildRoot/private/var/tmp/gcc/gcc-5465.obj/src/configure --disable-checking -enable-werror --prefix=/usr --mandir=/share/man --enable-languages=c,objc,c++,obj-c++ --program-transform-name=/^[cg][^.-]*$/s/$/-4.0/ --with-gxx-include-dir=/include/c++/4.0.0 --with-slibdir=/usr/lib --build=i686-apple-darwin9 --with-arch=apple --with-tune=generic --host=i686-apple-darwin9 --target=i686-apple-darwin9
Thread model: posix
gcc version 4.0.1 (Apple Inc. build 5465)

### llvm
llvmc --version
Low Level Virtual Machine (http://llvm.org/):
  llvm version 2.5
  Optimized build with assertions.
  Built Jul 30 2009(19:01:55).

llvm (Low Level Virtual Machine) from <http://llvm.org/> can be built and installed in a chroot at this time:

[...]
llvm[4]: ======= Finished Linking Release Executable Sample (without symbols)
make[1]: Nothing to be done for `all'.
llvm[0]: ***** Completed Release Build