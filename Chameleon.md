Chameleon
=========
<div style="margin:5px 10px;display:inline;float:right">
[![](../../_/rsrc/1247890313941/developers/booting/chameleon/logo.png)](chameleon/logo.png%3Fattredirects=0)
The [Chameleon](http://chameleon.osx86.hu/category/Chameleon/) bootloader is an APSL project based on David Elliott's fake EFI implementation added to Apple's boot-132 project.

The source code repository is available at
<http://forge.voodooprojects.org/p/chameleon/source/tree/HEAD/>

Chameleon brings some nice features from low to high layers as:
*Preboot ramdisk image, EFI partition booting, hibernation/resume, DSDT and SMBIOS, GUI booting and custom themes supports*.

**draft.**


<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Status](chameleon.html#TOC-Status)
2.  [**2** Some features](chameleon.html#TOC-Some-features)
    1.  [**2.1** Default partition](chameleon.html#TOC-Default-partition)
    2.  [**2.2** Customizable UI](chameleon.html#TOC-Customizable-UI)
        1.  [**2.2.1** Custom UI](chameleon.html#TOC-Custom-UI)
        2.  [**2.2.2** Default UI](chameleon.html#TOC-Default-UI)
    3.  [**2.3** RAM speed](chameleon.html#TOC-RAM-speed)
    4.  [**2.4** Extension folder](chameleon.html#TOC-Extension-folder)
3.  [**3** How to update PureDarwin running inside qemu to the latest Chameleon bootloader 11/2011](chameleon.html#TOC-How-to-update-PureDarwin-running-inside-qemu-to-the-latest-Chameleon-bootloader-11-2011)
4.  [**4** Resources](chameleon.html#TOC-Resources)

Status
------
Chameleon 2.0-RC4-r684 works with QEMU v0.10.6 and VMware (Fusion) 3.0.1 on a Mac.
Chameleon 2.0-RC3-r658 works with QEMU (mac & win tested), VMware (Fusion), etc.. Prolematic points reached on windows with e.g. vmware ("*Mach-o has bad magic number*" error).
Chameleon 2.0-RC1-r431 works with QEMU.
Chameleon 2.0-RC1-r431 will not show up in VMware (observed in Fusion but not in Player), because VMware relies on darwin.iso (VMware Tools) which contains the DFE bootloader (Stage 2 boot file &lt; 128K) is ok.
In case of real hardware target, cdboot, boot, boot0 and boot1h have been deployed but not yet tested.
In Image disk, virtual or not, cdboot and the "*El Torito ISO trick*" is used.
<span style="text-decoration:underline">Note:</span> The error "*Error parsing plist*"
in *i386/libsaio/stringTable.c*, the function "*long ParseXMLFile( char * buffer, TagPtr * dict )*" is responsible of returning the error.
<span style="font-size:small">    if (length &lt; 0) {</span>
<span style="font-size:small">        error ("Error parsing plist filen");</span>
<span style="font-size:small">        return -1;</span>
<span style="font-size:small">    }</span>
Why is it failing? The plist is obviously well formated and there is no permission problem at this level.
**Problem:** <span style="font-family:courier new,monospace;font-size:small">"Error parsing plist file"</span>
**Solution:** In fact, the error comes from the memory allocation, it seems that 256MB is not enough and make it fails in the contrary of e.g., 384M.
Some features
-------------
Please see "*Introducing new features added to next version of Chameleon*", [part 1](http://chameleon.osx86.hu/articles/introducing-new-features-added-to-next-version-of-chameleon-part-1) and [part 2](http://chameleon.osx86.hu/articles/more-new-features-added-to-next-chameleon-version-part-2).
### Default partition
<span style="font-family:Arial,Verdana,sans-serif;font-size:13px">A default partition to boot can be specified.
Add to *com.apple.Boot.plist*:</span>
<span style="font-size:13px"><span style="font-size:small">&lt;key&gt;Default Partition&lt;/key&gt;
&lt;string&gt;hd(**x**,**y**)&lt;/string&gt;
</span></span>
### Customizable UI
<span style="font-family:courier new,monospace;font-size:small"><span style="font-size:13px">It is be possible to customize the bootloader UI.</span><span style="font-size:13px">
</span><span style="font-size:13px">/Extra/Themes/ folder should contain some themes and /Extra/com.apple.Boot.plist should references one of them with:
</span>&lt;key&gt;Theme&lt;/key&gt;</span>
<span style="font-size:small">&lt;string&gt;**theme_folder_name**&lt;/string&gt;</span>
#### Custom UI
[![](../../_/rsrc/1247935767327/developers/booting/chameleon/Chameleon%20PureDarwin%20theme%200%20wait.png%3Fheight=327&width=420)](chameleon/Chameleon%20PureDarwin%20theme%200%20wait.png%3Fattredirects=0)
#### Default UI
[![](../../_/rsrc/1247890788671/developers/booting/chameleon/chameleon%20v2.0-RC1-r431%20timeout.png%3Fheight=327&width=420)](chameleon/chameleon%20v2.0-RC1-r431%20timeout.png%3Fattredirects=0)

[![](../../_/rsrc/1247890781208/developers/booting/chameleon/chameleon%20v2.0-RC1-r431%20memory%20info.png%3Fheight=330&width=420)](chameleon/chameleon%20v2.0-RC1-r431%20memory%20info.png%3Fattredirects=0)

[![](../../_/rsrc/1247890794899/developers/booting/chameleon/chameleon%20v2.0-RC1-r431%20video%20info.png%3Fheight=330&width=420)](chameleon/chameleon%20v2.0-RC1-r431%20video%20info.png%3Fattredirects=0)

[![](../../_/rsrc/1247890785709/developers/booting/chameleon/chameleon%20v2.0-RC1-r431%20%20boot%20devices.png%3Fheight=330&width=420)](chameleon/chameleon%20v2.0-RC1-r431%20%20boot%20devices.png%3Fattredirects=0)
<span style="font-size:16px;font-weight:bold"></span>
### RAM speed
<span style="font-size:small">&lt;key&gt;SMmemspeed&lt;/key&gt;
&lt;string&gt;800&lt;/string&gt;</span>
### Extension folder
.

How to update PureDarwin running inside qemu to the latest Chameleon bootloader 11/2011
----------------------------------------------------------------------------------------
sudo apt-get install dmg2img
dmg2img /home/mint/Downloads/2120-Chameleon v2.1VS r1701.dmg
# Run qemu with 
-hdb /home/mint/Downloads/2120-Chameleon v2.1VS r1701.img


PureDarwin:~ root# mount
/dev/disk0s1 on / (hfs, local, journaled)
PureDarwin:~ root# fdisk -f "/Volumes/Chameleon 2 VS//Manual Install/boot0" -u -y /dev/rdisk0
PureDarwin:~ root# dd if="/Volumes/Chameleon 2 VS//Manual Install/boot1h" of=/dev/rdisk0s1
PureDarwin:~ root# cp "/Volumes/Chameleon 2 VS//Manual Install/boot" /

# Chameleon v2.1VS r1701 seems no longer to be able to boot PD9, crashes immediately when loading the kernel
Resources
---------
<http://chameleon.osx86.hu>
[Source code repository](http://forge.voodooprojects.org/p/chameleon/source/tree/HEAD/)

