what
====

`what` is a tool showing what versions of object modules were used to construct a file.

Using `what`
------------

As example:

```shell
$ what /usr/lib/libSystem.B.dylib
/usr/lib/libSystem.B.dylib
  Libsyscall-1228.5.18~1 05/23/08 00:34:41 PDT
  Libc-498.1.1~5 04/15/08 22:44:26 PDT
  Libsystem-111.1.1~2 07/10/08 18:12:54 PDT
 PROGRAM:commonCrypto  PROJECT:CommonCrypto-32207
  libdyld-96.2~143 05/23/08 00:33:39 PDT
  Libinfo-278.0.3~2 04/07/08 12:29:06 PDT
  libdns_sd mDNSResponder-171.4 (Apr 20 2008 11:16:45)
  Libm-292.4 Mar 11 2008 23:06:24
 LIBRARY:libmacho  PROJECT:cctools_ofiles-667.3~138  DEVELOPER:root  BUILT:Mon Apr  7 16:19:07 PDT 2008
  Libnotify-35~3 09/23/07 14:39:00 PDT
  Libunc-21~150 09/23/07 14:39:04 PDT
  launchd_libs-258.12~1 04/03/08 17:35:26 PDT
  copyfile-42~24 03/04/08 21:17:45 PST
  Seatbelt_libs-107.1~456 05/23/08 00:33:32 PDT
  quarantine-22~35 09/23/07 14:38:59 PDT
  removefile-11~1 12/12/07 13:59:48 PST
```

Ressource
---------

`man what`