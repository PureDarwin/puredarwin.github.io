HFS+ partial raw approach
=========================
draft.


How did we get there? Needed to replace some [blocker](../../blockers.html) as `hdid' in [pd_setup](http://code.google.com/p/puredarwin/source/browse/setup/pd_setup) in order to be able to build PureDarwin images not only from Mac but also from PureDarwin.


Each piece is build and then "assembled" on this example:


<span style="font-size:small"> <span style="background-color:rgb(213,166,189)"> Partition map (with 512 byte blocks) on 'PureDarwin_nano.iso' </span></span>

<span style="font-size:small"> <span style="background-color:rgb(213,166,189)">  #:                type name       length   base   ( size )   </span></span>
<span style="font-size:small"> <span style="background-color:rgb(213,166,189)">  1: Apple_partition_map Apple          63 @ 1                 </span></span>
<span style="font-size:small"> <span style="background-color:rgb(213,166,189)"> </span><span style="background-color:rgb(246,178,107)"> 2:          Apple_Free Extra        2016 @ 64               </span><span style="background-color:rgb(213,166,189)"> </span></span>
<span style="font-size:small"> <span style="background-color:rgb(213,166,189)"> </span><span style="background-color:rgb(159,197,232)"> 3:           Apple_HFS PureDarwin 305056 @ 2080   (149.0M)  </span><span style="background-color:rgb(213,166,189)"> </span></span>
<span style="font-size:small"> <span style="background-color:rgb(213,166,189)">  4:          Apple_Free Extra          64 @ 307136            </span></span>
<span style="font-size:small">
</span>

1.  The raw target image file itself is created..
    <span style="font-family:courier new,monospace;font-size:small">dd if=/dev/zero of="$TARGET" bs=512k count=$(expr $SIZE '*' 2)
    <span style="font-family:Arial,Verdana,sans-serif;font-size:13px">
    ..and attached to a vndevice node (does not behave as a disk device node)
    <span style="font-family:courier new,monospace;font-size:small">/usr/libexec/vndevice attach /dev/vn0 "$TARGET"
    <span style="font-family:Arial,Verdana,sans-serif;font-size:13px"><span style="font-size:small">
    </span>Then the image/device is initialized and populated with a minimal partition map.
    <span style="font-family:courier new,monospace;font-size:small">pdisk $RDEVICE -initialize
    pdisk $RDEVICE -createPartition "$VOLNAME" Apple_HFS $sectors $(expr $blocks - $sectors) &gt; /dev/null
    
    </span></span></span></span></span>
2.  The El torito image will host the volume name, the cdboot bootloader and several bootloader files. 
    <span style="font-size:small">"$MKISOFS_BIN" -quiet -V "$VOLNAME" -no-emul-boot -boot-load-size 4 -c boot.cat -b $CDBOOT -o "$T_TARGET_P2" 
    </span>
    The result is then deployed via to the target image
    <span style="font-size:small">dd if="$T_TARGET_P2" of=$RDEVICE skip=64 seek=64 bs=512
    </span>
3.  The HFS partition image comes also originally from /dev/zero via `dd'.<span style="white-space:pre">
    </span><span style="font-size:small">dd if=/dev/zero of="$T_TARGET_P3" bs=1024k count=600
    </span><span style="white-space:pre"> `vndevice' is still involved but on another node.
    </span><span style="font-size:small">/usr/libexec/vndevice attach /dev/vn3 "$T_TARGET_P3"
    </span><span style="white-space:pre"> Construct a fresh HFS+ fs..
    </span><span style="font-size:small">newfs_hfs -s -J -v "$VOLNAME" ${RDEVICE}
    </span><span style="white-space:pre"> ..and mount it
    </span><span style="font-size:small">mount -t hfs -o perm ${DEVICE} "$MOUNT"
    </span>
    Finally, the HFS image is also deployed to the target image<span style="white-space:pre">
    </span><span style="font-size:small">echo "ddying $T_TARGET_P2 to $RDEVICE"</span><span style="white-space:pre"><span style="font-size:small">
    </span></span><span style="font-size:small">dd if="$T_TARGET_P3" of=$RDEVICE seek=$sectors bs=2048</span>


Notes: detach is not mentioned but should be used.:wq


etc..
fsck !!
etc..

### State
The HFS partition can be mounted in a running PureDarwin OS.
If the cdrom device is attached to the node /dev/disk1: <span style="font-size:small">mount -o ro -t hfs /dev/disk1s0s3 /mnt</span>

[![](../../_/rsrc/1263579413219/developers/hfsplus/hfs-partial-raw-approach/mount%20puredarwin%20iso%20from%20puredarwin.png)](hfs-partial-raw-approach/mount%20puredarwin%20iso%20from%20puredarwin.png%3Fattredirects=0)


The "<span style="font-size:small">phys_blksz 2048 does not match journal header size 512</span>" error message is not the first symptom of this problem, because after disabling the journalization (removing -J in `newfs_hfs'), the previous error message will not appear but the same kernel panic for same reason(s) will occur.

The `fsck' tool will complain about bad volume header, as Disk Utility (front-end of fsck for this part).

[![](../../_/rsrc/1263579479736/developers/hfsplus/hfs-partial-raw-approach/HFS%20and%20disk%20utility%20repair.png)](hfs-partial-raw-approach/HFS%20and%20disk%20utility%20repair.png%3Fattredirects=0)


It boots up to 'jnl' in case of a "bootstrap" or a "full" release, and without any problem if it is a "nano" release.

kernel panic if `fsck -fy' has not been run on this image before as show just below:


[![](../../_/rsrc/1263577921945/developers/hfsplus/hfs-partial-raw-approach/HFS%20bad%20volume%20header%20kernel%20panic.png)](hfs-partial-raw-approach/HFS%20bad%20volume%20header%20kernel%20panic.png%3Fattredirects=0)

Diffing the volume header
-------------------------
Diff a partition built with `dd' and `vndevice' against the same one but after `fsck -fy' on it reveals differences.

[![](../../_/rsrc/1263577672858/developers/hfsplus/hfs-partial-raw-approach/HFS%20diff%20part3.png)](hfs-partial-raw-approach/HFS%20diff%20part3.png%3Fattredirects=0)

This documentation has been really usefull in this process of problem resolution: http://developer.apple.com/mac/library/technotes/tn/tn1150.html

That has also confirmed that the partition is correctly copied via `dd' into the image, at least the problematic part we focus on.


OK The first 1024 bytes of volume (before the volume header), and the last 512 bytes of the volume (after the alternate volume header) are reserved.

OK The volume header is always located at 1024 bytes from the start of the volume.

NO A copy of the volume header, known as the alternate volume header, is stored starting at 1024 bytes before the end of the volume.


Note: All of the allocation blocks containing the volume header, alternate volume header,
or the reserved areas before the volume header or after the alternate volume header,
are marked as used in the allocation file. The actual number of allocation blocks marked this way depends on the allocation block size

From top to bottom, the address is growing:

<span style="font-size:small">0      reserved (Start of the volume)</span>
<span style="font-size:small">.      ...</span>
<span style="font-size:small">1023   reserved</span>
<span style="font-size:small">1024   Start of the volume header</span>
<span style="font-size:small">.      ...</span>
<span style="font-size:small">n-1024 Start of the alternate volume header (copy of the volume header)</span>
<span style="font-size:small">.</span>
<span style="font-size:small">n-512  reserved</span>
<span style="font-size:small">.      ...</span>
<span style="font-size:small">n      reserver (End of the volume)</span>


Technically, we inspect this structure in these first 1024+n bytes:

<span style="font-size:x-small">struct HFSPlusVolumeHeader {</span>
<span style="font-size:x-small">    UInt16              signature;</span>
<span style="font-size:x-small">    UInt16              version;</span>
<span style="font-size:x-small">    UInt32              attributes;</span>
<span style="font-size:x-small">    UInt32              lastMountedVersion;</span>
<span style="font-size:x-small">    UInt32              journalInfoBlock;</span>
<span style="font-size:x-small">    UInt32              createDate;</span>
<span style="font-size:x-small">    UInt32              modifyDate;</span>
<span style="font-size:x-small">    UInt32              backupDate;</span>
<span style="font-size:x-small">    UInt32              checkedDate;</span>
<span style="font-size:x-small">    UInt32              fileCount;</span>
<span style="font-size:x-small">    UInt32              folderCount;</span>
<span style="font-size:x-small">    UInt32              blockSize;</span>
<span style="font-size:x-small">    UInt32              totalBlocks;</span>
<span style="font-size:x-small">    UInt32              freeBlocks;</span>
<span style="font-size:x-small">    UInt32              nextAllocation;</span>
<span style="font-size:x-small">    UInt32              rsrcClumpSize;</span>
<span style="font-size:x-small">    UInt32              dataClumpSize;</span>
<span style="font-size:x-small">    HFSCatalogNodeID    nextCatalogID;</span>
<span style="font-size:x-small">    UInt32              writeCount;</span>
<span style="font-size:x-small">    UInt64              encodingsBitmap;</span>
<span style="font-size:x-small">    UInt32              finderInfo[8];</span>
<span style="font-size:x-small">    HFSPlusForkData     allocationFile;</span>
<span style="font-size:x-small">    HFSPlusForkData     extentsFile;</span>
<span style="font-size:x-small">    HFSPlusForkData     catalogFile;</span>
<span style="font-size:x-small">    HFSPlusForkData     attributesFile;</span>
<span style="font-size:x-small">    HFSPlusForkData     startupFile;</span>
<span style="font-size:x-small">};</span>
<span style="font-size:x-small">typedef struct HFSPlusVolumeHeader HFSPlusVolumeHeader;</span>

Back to the above diff of the beginning of the Volume header, take in account that not all fields, even if a difference occurs, appeard important "to patch" (e.g.: modifyDate). The main interesting diffs found are:


<span style="font-size:small">    UInt32              fileCount;          0000 2eec --- ( -0x3 ) ---&gt; 0000 2ee9  </span>
<span style="font-size:small">    UInt32              folderCount;        0000 052a --- ( -0x2 ) ---&gt; 0000 0528 </span>

<span style="font-size:small">    UInt32              freeBlocks;         0000 5090 --- (+0x1F3) ---&gt; 0000 5283 </span>

<span style="font-size:small">    UInt32              nextAllocation;     0001 d839 --- (-0x1F1) ---&gt; 0001 d648</span>

<span style="font-size:small">    HFSCatalogNodeID    nextCatalogID;      0000 356d --- ( -0x7 ) ---&gt; 0000 3566     </span>



### Details
Quick info related to fields where diffs have been found before and after fsck.
#### attributes
<span style="font-size:small">UInt32              attributes;</span>

Volume attributes (set of one bit-flags).

before fsck
8000 2100
<span style="font-size:small">binary: 0000 0000 0001 0010 0000 0000 0000 1000</span>
<span style="font-size:small">reserv: xxxx xxx         x  xxxx xxxx xxxx xxxx</span>
<span style="font-size:small">enable:              x                      </span>
kHFSBootVolumeInconsistentBit is set (bit 11).
Similar to kHFSVolumeUnmountedBit, but inverted in meaning.
Bit should be set when a volume for writing is mounted, and be clear at the end of unmount. 
If this bit is already set at mount, a consistency checking from the assumption that the volume is corrupt could be needed.

-0x100
after fsck
8000 2000

<span style="font-size:small">binary: 1000 0000 0000 0000 0010 0000 0000 0000</span>

<span style="font-size:small">reserv: xxxx xxx         x  xxxx xxxx xxxx xxxx</span>
<span style="font-size:small">
</span>

http://developer.apple.com/mac/library/technotes/tn/tn1150.html#VolumeAttributes
#### fileCount
<span style="font-size:small">UInt32              fileCount;</span>


The total number of files on the volume.
The fileCount field does not include the special files.
It should equal the number of file records found in the catalog file.


before fsck
0000 2ee9

-3

after fsck
0000 2eec
#### folderCount    
<span style="font-size:small">UInt32              folderCount;</span>

Total number of folders on the volume not including the root folder.
Should equal number of folder records in the catalog file minus one (the root folder in Catalog)


before fsck
0000 0528 


+2


after fsck
0000 052a

#### freeBlocks
<span style="font-size:small">UInt32              freeBlocks;</span>

Contains the total number of unused allocation blocks.

before fsck
0000 5283 


+0x1F3 (499)


after fsck
0000 5090
#### nextAllocation
<span style="font-size:small">UInt32              nextAllocation;</span>

Used to find where to start searching for free allocation blocks when allocation space for a file.
It contains the allocation block number where the search should start. 


before fsck
0001 d648


+0x1F1

after fsck

0001 d839


Can be threated as reserved

http://developer.apple.com/mac/library/technotes/tn/tn1150.html#AllocationFile
#### nextCatalogID
<span style="font-size:small">HFSCatalogNodeID    nextCatalogID;</span>

It appears to be an usual UInt32 which points to the next "unused" catalog ID.
A catalog ID is a B-Tree.


before fsck
0000 3566

+0x7


after fsck
0000 356d


See <span style="font-size:small">[Technical Note TN1150: HFS Plus Volume Format](http://developer.apple.com/mac/library/technotes/tn/tn1150.html#CatalogFile)</span> for more information.






