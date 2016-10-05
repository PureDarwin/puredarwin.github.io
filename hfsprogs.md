hfsprogs
========
debian and Ubuntu have a package called "hfsprogs", which can be used to create HFS+ disk images:
<span style="font-family:courier new,monospace">apt-get install hfsprogs</span>
<span style="font-family:courier new,monospace">mkfs.hfsplus disk.hfsplus </span>
<span style="font-family:courier new,monospace">Initialized disk.hfsplus as a 100 MB HFS Plus volume</span>
<span style="font-family:courier new,monospace">file disk.hfsplus </span>
<span style="font-family:courier new,monospace">disk.hfsplus: Macintosh HFS Extended version 4 data last mounted by: '10.0', created: Mon Mar 23 18:32:16 2009, last modified: Mon Mar 23 18:32:16 2009, last checked: Mon Mar 23 18:32:16 2009, block size: 4096, number of blocks: 25600, free blocks: 25197</span>
<span style="font-family:courier new,monospace">sudo mkdir /media/hfsplus</span>
<span style="font-family:courier new,monospace">sudo mount disk.hfsplus /media/hfsplus/ -o loop</span>
Now we can copy something there
(How) can we use this disk image with qemu?
If we want to make this bootable with a boot loader, we need to have a partition table inside the disk image!
Probably we need to do this along these lines:
http://wiki.eeeuser.com/howtocustomrestoreimage:pt2mkcustomimage
