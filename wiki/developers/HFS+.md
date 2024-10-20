HFS+
====
This page describes the HFS+ filesystem and how to interact with it.
This is a work in progress; please contribute to this page.

### What is HFS+
the HFS+ file system is an improved version of the historical Hierarchical File System (HFS).
The predecessor was introduced in Mac OS.
The successor is also known as Sequoia, the "new Mac OS Extended Format".
A tree data structure (B*-tree) is used in the HFS+ file system. 
### How to interact with HFS+
(Please write some text)
#### Using Mac OS X
Mac OS X can read, write, and boot from HFS+ partitions natively.
On the Mac, Disk Utility is the main tool to create and repair HFS+ partitions.
(Please write some text)
#### Using Darwin
Darwin can read, write, and boot from HFS+ partitions natively.
On Darwin, hfs_tools is the main tool to create and repair HFS+ partitions.
/sbin/fsck_hfs
/sbin/fstyp_hfs
/sbin/mount_hfs
/sbin/newfs_hfs
pdisk supports HFS volume names.
/usr/sbin/pdisk
(Please write some text)
#### Using Linux
Linux can, with the appropriate driver, read and write HFS+ partitions. However, it lacks tools to create HFS+ partitions.

There is a [patch](http://atv-bootloader.googlecode.com/files/hfs_support-1.0.tar.gz) to compile hfs_tools on Linux which overcomes this shortage.
(Please write some text)
#### Using Windows
Windows cannot, per default, read or write HFS+ partitions.
However, there are commercial third-party and opensource tools to do so.
Opensource:
http://hem.bredband.net/catacombae/hfsx.html
(Please write some text)

