Filesystem hierarchy
====================

Ever wondered what /etc, /usr, /opt, and so on mean?
Ever wondered what the differences between /lib, /usr/lib, /usr/local/lib are?
Ever wondered what libexec and standalone mean?

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:280px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** BSD man hier](hier.html#TOC-BSD-man-hier)
2.  [**2** Commonly used Darwin specialties](hier.html#TOC-Commonly-used-Darwin-specialties)
3.  [**3** $PATH](hier.html#TOC-PATH)
    1.  [**3.1** Darwin 9](hier.html#TOC-Darwin-9)
    2.  [**3.2** Mac OS X 10.5](hier.html#TOC-Mac-OS-X-10.5)
    3.  [**3.3** FreeBSD (example for "BSD world")](hier.html#TOC-FreeBSD-example-for-BSD-world-)
    4.  [**3.4** Ubuntu (example for "GNU world")](hier.html#TOC-Ubuntu-example-for-GNU-world-)
4.  [**4** Library path](hier.html#TOC-Library-path)


<span style="font-weight:bold">Commonly used Darwin specialties at the bottom of this page.</span>
### BSD man hier
<span style="border-collapse:separate;font-family:verdana;font-size:11px"> </span>
``` {style="font-family:monospace"}
HIER(7)       FreeBSD Miscellaneous Information Manual        HIER(7)
NAME
     hier -- layout of file systems
DESCRIPTION
     A sketch of the file system hierarchy.
     /      root directory of the file system
     /bin/ user utilities fundamental to both single-user and multi-user
       environments
     /boot/ programs and configuration files used during operating system
       bootstrap
       defaults/  default bootstrapping configuration files; see
              loader.conf(5)
        kernel/    pure kernel executable (the operating system loaded
             into memory at boot time).
       modules/   third-party loadable kernel modules; see kldstat(8)
     /cdrom/    default mount point for CD-ROM drives (created by
       sysinstall(8))
     /compat/    normally a link to /usr/compat.  If not, then the /usr/compat
        comments apply (created by sysinstall(8))
     /dev/    device special files managed by devfs(5)
        fd/   file descriptor files; see fd(4)
        net/  network devices
     /dist/    mount point used by sysinstall(8)
     /etc/  system configuration files and scripts
      defaults/   default system configuration files; see rc(8)
        bluetooth/  bluetooth configuration files
       gnats/      gnats configuration files; see send-pr(1)
        isdn/       isdn4bsd configuration files; see isdnd(8)
        localtime   local timezone information; see ctime(3)
        mail/       Sendmail control files
      mtree/      mtree configuration files; see mtree(8)
        namedb/     named configuration files; see named(8)
        pam.d/      configuration files for the Pluggable Authentica-
               tion Modules (PAM) library
      periodic/   scripts that are run daily, weekly, and monthly,
                via cron(8); see periodic(8)
        rc.d/       System and daemon startup/control scripts; see
              rc(8)
        security/   OpenBSM audit configuration files; see audit(8)
        ppp/        ppp configuration files; see ppp(8)
        ssh/        OpenSSH configuration files; see ssh(1)
        ssl/        OpenSSL configuration files
     /lib/   critical system libraries needed for binaries in /bin and
       /sbin
        geom/  class-specific libraries for the geom(8) utility
     /libexec/    critical system utilities needed for binaries in /bin and
       /sbin
     /media/    contains subdirectories to be used as mount points for remov-
       able media such as CDs, USB drives, and floppy disks
     /mnt/  empty directory commonly used by system administrators as a
     temporary mount point
     /proc/    process file system; see procfs(5)
     /rescue/   statically linked programs for emergency recovery; see
      rescue(8)
     /root/ root's HOME directory
     /sbin/    system programs and administration utilities fundamental to
     both single-user and multi-user environments
     /tmp/  temporary files that are not guaranteed to persist across sys-
      tem reboots
     /usr/   contains the majority of user utilities and applications
        bin/      common utilities, programming tools, and applica-
           tions
     compat/   files needed to support binary compatibility with
           other operating systems, such as Linux (created by
              sysinstall(8))
       games/    useful and semi-frivolous programs
        include/  standard C include files
            altq/       C include files for alternate queueing
              arpa/       C include files for Internet service
                    protocols
           bsnmp/      C include files for the SNMP daemon
             c++/        C++ include files
           cam/        C include files for the Common Access
                   Methods Layer
                   scsi/   The SCSI device on top of
                       CAM
             dev/        C include files for programming various
                     FreeBSD devices
                     ic/     Various header files
                        describing driver- and bus-
                         independent hardware cir-
                       cuits
                   ofw/    Open Firmware support
                   pbio/   8255 PPI cards; see pbio(4)
                      ppbus/      The parallel port bus; see
                          ppbus(4)
                      usb/    The USB subsystem
                   utopia/     Physical chip driver for ATM
                        interfaces; see utopia(4)
                      wi/     The wi(4) WaveLAN driver
           fs/
                      fdescfs/    per-process file descriptors
                        file system
                     fifofs/     IEEE Std 1003.1
                         (``POSIX.1'') FIFOs file
                        system
                      msdosfs/    MS-DOS file system
                      ntfs/   NTFS file system
                    nullfs/     loopback file system
                    nwfs/   NetWare file system
                     portalfs/   portal file system
                      procfs/     process file system
                     smbfs/      SMB/CIFS file system
                    udf/    UDF file system
                     unionfs     union file system
           geom/       GEOM framework
                      concat/     CONCAT GEOM class
                   gate/   GATE GEOM class
                     mirror/     MIRROR GEOM class
                   nop/    NOP GEOM class
                      raid3/      RAID3 GEOM class
                    stripe/     STRIPE GEOM class
           isc/        ISC utility library libisc include files
            isofs/
                      cd9660/     iso9660 file system
             libmilter/  C include files for libmilter, the
                      sendmail(8) mail filter API
              machine/    machine-specific C include files
            net/        miscellaneous network C include files
           netatalk/   Appletalk protocol
              netatm/     ATM include files; see atm(8)
              netinet/    C include files for Internet standard
                   protocols; see inet(4)
              netinet6/   C include files for Internet protocol
                   version 6; see inet6(4)
              netipsec/   kernel key-management service; see
                      ipsec(4)
              netipx/     IPX/SPX protocol stacks
             netnatm/    NATM include files; see natm(4)
                      api/    include files for the sig-
                          nalling API
                     msg/    include files that describe
                         signalling messages and
                         declare associated functions
                    saal/   include files for the sig-
                          nalling AAL layer
                   sig/    include files for the UNI
                       signalling protocol
             netsmb/     SMB/CIFS requester
              nfs/        C include files for NFS (Network File
                   System)
             objc/       Objective C include files
           openssl/    OpenSSL (Cryptography/SSL toolkit) head-
                    ers
             pccard/     PC-CARD controllers
             protocols/  C include files for Berkeley service
                    protocols
           readline/   get a line from a user, with editing;
                   see readline(3)
              rpc/        remote procedure calls; see rpc(3)
              rpcsvc/     definition of RPC service structures;
                   see rpc(3)
              security/   PAM; see pam(8)
              sys/        system C include files (kernel data
                     structures)
             ufs/        C include files for UFS (The U-word File
                    System)
                     ffs/    Fast file system
                    ufs/    UFS file system
             vm/         virtual memory; see vmstat(8)
        lib/      shared and archive ar(1)-type libraries
            aout/       a.out archive libraries
             compat/     shared libraries for compatibility
                      aout/   a.out backward compatibility
                        libraries
           dtrace/     DTrace library scripts
              engines/    OpenSSL (Cryptography/SSL toolkit)
                      dynamically loadable engines
      libdata/  miscellaneous utility data files
            gcc/        gcc(1) configuration data
             ldscripts/  linker scripts; see ld(1)
              lint/       various prebuilt lint libraries; see
                    lint(1)
        libexec/  system daemons & system utilities (executed by other
            programs)
           aout/       utilities to manipulate a.out executa-
                      bles
            elf/        utilities to manipulate ELF executables
             lpr/        utilities and filters for LP print sys-
                     tem; see lpr(1)
              sendmail/   the sendmail(8) binary; see
                      mailwrapper(8)
              sm.bin/     restricted shell for sendmail(8); see
                    smrsh(8)
        local/    local executables, libraries, etc.  Also used as the
            default destination for the FreeBSD ports framework.
            Within local/, the general layout sketched out by
           hier for /usr should be used.  Exceptions are the
            man directory (directly under local/ rather than
            under local/share/), ports documentation (in
            share/doc/<port>/), and /usr/local/etc (mimics
            /etc).
        obj/      architecture-specific target tree produced by build-
            ing the /usr/src tree
     ports/    The FreeBSD ports collection (optional).
      sbin/     system daemons & system utilities (executed by
              users)
        share/    architecture-independent files
              calendar/  a variety of pre-fab calendar files; see
                    calendar(1)
              dict/      word lists; see look(1)
                     freebsd     FreeBSD-specific terms,
                         proper names, and jargon
                    words   common words
                    web2    words from Webster's 2nd
                        International
                   papers/     reference databases; see
                        refer(1)
              doc/       miscellaneous documentation; source for
                     most of the printed BSD manuals (avail-
                     able from the USENIX association)
                   FAQ/    Frequently Asked Questions
                  IPv6/   implementation notes for IPv6
                   bind/   documents pertaining to BIND
                        (the Berkeley Internet Name
                         Domain)
                     es/     Spanish translations of docu-
                       ments in /usr/share/doc
                     handbook/   FreeBSD Handbook
                    ja/     Japanese translations of doc-
                       uments in /usr/share/doc
                    legal/  License files for vendor sup-
                       plied firmwares
                     ncurses/    HTML documents pertaining to
                        ncurses; see ncurses(3)
                     ntp/    HTML documents pertaining to
                        the Network Time Protocol
                   papers/     UNIX Papers
                     psd/    UNIX Programmer's Supplemen-
                        tary Documents
                  ru/     Russian translations of docu-
                       ments in /usr/share/doc
                     smm/    UNIX System Manager's Manual
                    tutorials/  FreeBSD tutorials
                   usd/    UNIX User's Supplementary
                       Documents
                   zh/     Chinese translations of docu-
                       ments in /usr/share/doc
              examples/  various examples for users and program-
                     mers
             games/     ASCII text files used by various games
           groff_font/
                     device description file for device name
              info/      GNU Info hypertext system
            isdn/      ISDN
             locale/    localization files; see setlocale(3)
              man/       manual pages
             me/        macros for use with the me macro package;
                   see me(7)
              misc/      miscellaneous system-wide ASCII text
                    files
                   fonts/  ???
                     termcap     terminal characteristics
                        database; see termcap(5)
              mk/        templates for make; see make(1)
              nls/       national language support files; see
                    mklocale(1)
              security/  data files for security policies such as
                    mac_lomac(4)
              sendmail/  sendmail(8) configuration files
           skel/      example . (dot) files for new accounts
           snmp/      MIBs, example files and tree definitions
                    for the SNMP daemon.
                    defs/   Tree definition files for use
                       with gensnmptree(1)
                     mibs/   MIB files
            syscons/   files used by syscons; see syscons(4)
                     fonts/ console fonts; see
                      vidcontrol(1) and vidfont(1)
                     keymaps/   console keyboard maps; see
                      kbdcontrol(1) and kbdmap(1)
                     scrnmaps/  console screen maps
           tabset/    tab description files for a variety of
                  terminals; used in the termcap file; see
                    termcap(5)
              tmac/      text processing macros; see nroff(1) and
                    troff(1)
              vi/        localization support and utilities for
                  vi(1)
              zoneinfo/  timezone configuration information; see
                     tzfile(5)
        src/      BSD, third-party, and/or local source files
             bin/        source code for files in /bin
           contrib/    source code for contributed software
            crypto/     source code for contributed cryptography
                    software
            etc/        source code for files in /etc
           games/      source code for files in /usr/games
             gnu/        Utilities covered by the GNU General
                    Public License
              include/    source code for files in /usr/include
           kerberos5/  build infrastructure for kerberos ver-
                      sion 5
              lib/        source code for files in /usr/lib
           libexec/    source code for files in /usr/libexec
           release/    files required to produce a FreeBSD
                     release
             sbin/       source code for files in /sbin
              secure/     build directory for files in
                    /usr/src/crypto
             share/      source for files in /usr/share
              sys/        kernel source code
              tools/      tools used for maintenance and testing
                      of FreeBSD
              usr.bin/    source code for files in /usr/bin
           usr.sbin/   source code for files in /usr/sbin
     /var/  multi-purpose log, temporary, transient, and spool files
        account/   system accounting files
             acct        execution accounting file; see acct(5)
        at/    timed command scheduling files; see at(1)
               jobs/      directory containing job files
               spool/     directory containing output spool files
       backups/   miscellaneous backup files
       crash/     default directory to store kernel crash dumps; see
              crash(8) and savecore(8)
        cron/      files used by cron; see cron(8)
               tabs/      crontab files; see crontab(5)
        db/    miscellaneous automatically generated system-spe-
               cific database files
     empty/     empty directory for use by programs that need a
             specifically empty directory.  Used for instance by
             sshd(8) for privilege separation.
     games/     miscellaneous game status and score files
        heimdal/   kerberos server databases; see kdc(8)
        log/       miscellaneous system log files
              wtmp        login/logout log; see wtmp(5)
        mail/      user mailbox files
       msgs/      system messages database; see msgs(1)
        preserve/  temporary home of files preserved after an acciden-
             tal death of an editor; see ex(1)
        quotas/    file system quota information files
      run/       system information files describing various info
            about system since it was booted
            named/      writable by the ``bind'' user; see
                      named(8)
               ppp/        writable by the ``network'' group for
                       command connection sockets; see ppp(8)
               utmp        database of current users; see utmp(5)
        rwho/      rwho data files; see rwhod(8), rwho(1), and
              ruptime(1)
        spool/     miscellaneous printer and mail system spooling
              directories
             clientmqueue/
                       undelivered submission mail queue; see
                       sendmail(8)
               ftp/        commonly ~ftp; the anonymous ftp root
                       directory
               mqueue/     undelivered mail queue; see sendmail(8)
               output/     line printer spooling directories
        tmp/       temporary files that are kept between system
            reboots
             vi.recover/
                       the directory where recovery files are
                       stored
        yp/    the NIS maps
NOTES
     This manual page documents the default FreeBSD file system layout, but
     the actual hierarchy on a given system is defined at the system adminis-
     trator's discretion.  A well-maintained installation will include a cus-
     tomized version of this document.
SEE ALSO
     apropos(1), find(1), finger(1), grep(1), ls(1), whatis(1), whereis(1),
     which(1), fd(4), devfs(5), fsck(8)
HISTORY
     A hier manual page appeared in Version 7 AT&T UNIX.
```
    FreeBSD 7.0            June 28, 2007             FreeBSD 7.0
### Commonly used Darwin specialties
-   <span style="font-weight:bold">/opt/local/</span> MacPorts-installed software
-   <span style="font-weight:bold">/sw/ </span>fink-installed software
-   <span style="font-weight:bold">/usr/local/</span> Some DarwinBuild-installed software
-   <span style="font-weight:bold">/usr/standalone/i386/ </span>Darwin bootloader
### $PATH
Note that in the BSD paths, /usr/local/bin comes after /usr/bin (unlike in GNU world, where /usr/local/bin might come before /usr/bin)
#### Darwin 9
PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/X11/bin
#### Mac OS X 10.5
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/libexec:/System/Library/CoreServices
#### FreeBSD (example for "BSD world")
to be posted
#### Ubuntu (example for "GNU world")
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
### Library path
Darwin world: $<span style="border-collapse:separate;font-size:12px">DYLD_LIBRARY_PATH</span>
GNU world: $LD_LIBRARY_PATH

