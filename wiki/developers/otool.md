otool
=====
otool is a tool that, among other things, can show which shared libraries an application needs to run (similar to "ldd" on Linux).

### When to use otool

otool is useful when you want to run an application on PureDarwin, but are not sure what libraries it needs.

### How to use otool

Assume we want to know which libraries are needed to run bash.
Simply run:

```
otool -L /Volumes/PureDarwin/bin/bash
```

It will give us

```
/usr/lib/libncurses.5.4.dylib (compatibility version 5.4.0, current version 5.4.0)
/usr/lib/libiconv.2.dylib (compatibility version 7.0.0, current version 7.0.0)
/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.0.0)
/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)
```

So, we need to have these libaries installed in our PureDarwin system in order to be able to run bash.

### Use chroot

In order to further test, you can use chroot. (To be described)