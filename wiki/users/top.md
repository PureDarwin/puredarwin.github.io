top
===
This page is about the well-known UNIX tool 'top', which display and update sorted information about processes, but differs a little bit from the 'top' on other BSDs and/or GNU/Linux.

**Problem:** logged as a user, `top' fails in "Bus error" as illustrated below:

![](/img/users/top/top%20fails%20as%20user.png)

**
Solution:** Unknown. Please contact us if you know a solution.

'otool' says:

`/usr/bin/top:`
 `/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.13.0)`
 `/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit (compatibility version 1.0.0, current version 275.0.0)`
 `/usr/lib/libpanel.5.4.dylib (compatibility version 5.4.0, current version 5.4.0)`
 `/usr/lib/libncurses.5.4.dylib (compatibility version 5.4.0, current version 5.4.0)`
 `/usr/lib/libutil.dylib (compatibility version 1.0.0, current version 1.0.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)`


As root, there is no problem:

![](/img/users/top/top%20classic.png)

