Chameleon
=========

![chameleon](http://chameleon.osx86.hu/images/28t.png)  
The [Chameleon](http://chameleon.osx86.hu/category/Chameleon/) bootloader is an APSL project based on David Elliott's fake EFI implementation added to Apple's boot-132 project.

The source code repository is available at
<http://forge.voodooprojects.org/p/chameleon/source/tree/HEAD/>

Chameleon brings some nice features from low to high layers as:  
*Preboot ramdisk image, EFI partition booting, hibernation/resume, DSDT and SMBIOS, GUI booting and custom themes supports.*

**draft.**  

Status
------

- Chameleon 2.0-RC4-r684 works with QEMU v0.10.6 and VMware (Fusion) 3.0.1 on a Mac.
- Chameleon 2.0-RC3-r658 works with QEMU (mac & win tested), VMware (Fusion), etc.. Prolematic points reached on windows with e.g. vmware ("*Mach-o has bad magic number*" error).
- Chameleon 2.0-RC1-r431 works with QEMU.
- Chameleon 2.0-RC1-r431 will not show up in VMware (observed in Fusion but not in Player), because VMware relies on darwin.iso (VMware Tools) which contains the DFE bootloader (Stage 2 boot file &lt; 128K) is ok.
- In case of real hardware target, cdboot, boot, boot0 and boot1h have been deployed but not yet tested.
- In Image disk, virtual or not, cdboot and the "*El Torito ISO trick*" is used.
- Note: The error "*Error parsing plist*" in *i386/libsaio/stringTable.c*, the function "*long ParseXMLFile( char * buffer, TagPtr * dict )*" is responsible of returning the error.
```
    if (length &lt; 0) {
        error ("Error parsing plist filen");
        return -1;
    }
```
Why is it failing? The plist is obviously well formated and there is no permission problem at this level.  
**Problem:** "Error parsing plist file"   
**Solution:** In fact, the error comes from the memory allocation, it seems that 256MB is not enough and make it fails in the contrary of e.g., 384M.

Some features
-------------
Please see "*Introducing new features added to next version of Chameleon*", [part 1](http://chameleon.osx86.hu/articles/introducing-new-features-added-to-next-version-of-chameleon-part-1) and [part 2](http://chameleon.osx86.hu/articles/more-new-features-added-to-next-chameleon-version-part-2).

### Default partition
A default partition to boot can be specified.
Add to *com.apple.Boot.plist*:  
&lt;key&gt;Default Partition&lt;/key&gt;  
&lt;string&gt;hd(**x**,**y**)&lt;/string&gt;  


### Customizable UI
``
<string>**theme_folder_name**</string>

#### Custom UI
![](/img/developers/booting/chameleon/Chameleon%20PureDarwin%20theme%200%20wait.png)

#### Default UI
![](/img/developers/booting/chameleon/chameleon%20v2.0-RC1-r431%20timeout.png)

![](/img/developers/booting/chameleon/chameleon%20v2.0-RC1-r431%20memory%20info.png)

![](/img/developers/booting/chameleon/chameleon%20v2.0-RC1-r431%20video%20info.png)

![](/img/developers/booting/chameleon/chameleon%20v2.0-RC1-r431%20%20boot%20devices.png)

### RAM speed
&lt;key&gt;SMmemspeed&lt;/key&gt;
&lt;string&gt;800&lt;/string&gt;


How to update PureDarwin running inside qemu to the latest Chameleon bootloader 11/2011
----------------------------------------------------------------------------------------
```
sudo apt-get install dmg2img
dmg2img /home/mint/Downloads/2120-Chameleon v2.1VS r1701.dmg
# Run qemu with 
-hdb /home/mint/Downloads/2120-Chameleon v2.1VS r1701.img
```

```
PureDarwin:~ root# mount
/dev/disk0s1 on / (hfs, local, journaled)
PureDarwin:~ root# fdisk -f "/Volumes/Chameleon 2 VS//Manual Install/boot0" -u -y /dev/rdisk0
PureDarwin:~ root# dd if="/Volumes/Chameleon 2 VS//Manual Install/boot1h" of=/dev/rdisk0s1
PureDarwin:~ root# cp "/Volumes/Chameleon 2 VS//Manual Install/boot" /
```

# Chameleon v2.1VS r1701 seems no longer to be able to boot PD9, crashes immediately when loading the kernel
Resources
---------
<http://chameleon.osx86.hu>
[Source code repository](http://forge.voodooprojects.org/p/chameleon/source/tree/HEAD/)