Audio
=====

<span style="font-size:small">This page is about a future audio support in PureDarwin.</span>
<span style="font-size:small">draft.</span>
Status
------
<span style="font-size:small">IOAudioFamily.kext (patched) and VoodooHDA.kext can be loaded.</span>
<span style="font-size:small">We heard great progress from Cooper [previously](http://lists.apple.com/archives/Darwin-dev/2009/Aug/msg00000.html), also extending our knowledge to the fact that "audio support" does not only rely on the kext side but also in the user-land.</span>
IOAudioFamily and VoodooHDA
---------------------------
<span style="font-family:arial,sans-serif;font-style:italic">[High Definition Audio (HDA) driver for Mac OS X](http://code.google.com/p/voodoohda/)</span>
*
*
<span style="font-family:arial,sans-serif">"*VoodooHDA is an open source audio driver for devices compliant with the *[*Intel High Definition Audio (HDA)*](http://www.intel.com/standards/hdaudio/)* specification, based primarily on code from the FreeBSD *[*hdac driver*](http://www.freebsd.org/cgi/cvsweb.cgi/src/sys/dev/sound/pci/hda/)*. It is intended as an Intel-only replacement for AppleHDA on Mac OS X with support for a wide range of audio controllers and codecs*." <span style="font-family:Arial,Verdana,sans-serif"><http://code.google.com/p/voodoohda></span></span>

VoodooHDA cannot be loaded, because one of its dependencies (IOAudioFamily.kext) is not satisifed.
<http://code.google.com/p/voodoohda/issues/detail?id=38>


[![](../_/rsrc/1248010590995/developers/audio/VoodooHDA%20blocked%20at%20load.png%3Fheight=354&width=420)](audio/VoodooHDA%20blocked%20at%20load.png%3Fattredirects=0)

Since IOAudioFamily has been patched for [purity](macports/purity.html) purpose, IOAudioFamily.kext can now be loaded without OSvKernDSPLib.kext. See <http://darwinbuild.macosforge.org/trac/ticket/89>.
Consequently, VoodooHDA can also be loaded, its Info.plist has been modified in order to match the virtual devices of VMware but the "start" method doesn't seem to succeed.

[![](../_/rsrc/1248376065719/developers/audio/voodooHDA.png)](audio/voodooHDA.png%3Fattredirects=0)

No sound nor good symptoms.



<span style="font-size:small">**Blockers:**</span>
<span style="font-size:small">**OSvKernDSPLib.kext**</span>
<span style="white-space:pre"><span style="font-size:small">**AppleAC97Audio.kext**</span></span>
<span style="font-size:small;white-space:pre">Please let us know if you have more information and/or solutions
</span>


**Cooper sent us the following information in March 2010:**<span style="border-collapse:separate;color:rgb(0,0,0);font-family:Times New Roman;font-style:normal;font-variant:normal;font-weight:normal;letter-spacing:normal;line-height:normal;text-indent:0px;text-transform:none;white-space:normal;word-spacing:0px;font-size:medium"><span style="border-collapse:collapse;font-family:arial,sans-serif;font-size:13px">
**OSvKernDSPLib.kext:**
We don't have the source but the functions that we need are all well documented in the ADC and simple (each perform a single mathematical operation).  It would be easy for someone to implement these and patch them directly into whatever needs them or, better still, create a kext which exports them called OSvKernDSPLib.kext.
**Usermode access:**
If you use shark to do a trace (on OSX) of a program recording audio you'll find LOTS of references to HP_ funcs, in particular HP_IOThread.  Now if you search over a full XCode install you'll find you actually have that code.
Turns out that a huge amount of the usermode Coreaudio code is shipped with XCode to allow the development/testing of CoreAudioPlugins; go look in the folders called HPBase, PublicUtility etc.  These classes etc call down to the lower level audio interface functions, header files: AudioHardware.h etc (we don't have the source) and these then communicate with the audio drivers IOUserClient in the kernel.
So, where does that leave us.  Thankfully by trawling over the HP_ code you can find out whats important for the user code (the key thing it realtime priority), and by trawling through the kernel source (IOKit) you can find out what interface the code in AudioHardware.h uses (<http://lists.apple.com/archives/Darwin-dev/2009/Aug/msg00000.html>).
What I posted back in August on the Darwin-dev list is basically correct and the answers to my questions are:
**Q.** Is there a mechanism to tell me when its safe to use this data, or is it, as I suspect, volatile and you use it "as it".
**A.** Sort of.  You basically need a realtime usermode thread which polls the kernel for the correct data.  The generic, kernel, audio stuff then gives you a copy of the samples your expecting.
**Q.** My key question is how do I get intelligible audio from the driver? I've tried putting a sleep in, but to no avail.
**A.** IIRC, I did do this over 6 months ago; it all starts working once you get your io thread working correctly.
To help illustrate all this I thought I'd attach my test program.  I know its a mess, but it does (or did last time I used it) read audio directly from the kernel on OSX and save it into a file.  What I did was pull out all the key things from the HP_IOThread func, combine that which what I'd learnt about the raw IOKIt interface and put it all together.  You should be able to load the output audio into something like Audacity and then play it.  Simples, see :)
</span></span>
### <span style="border-collapse:separate;color:rgb(0,0,0);font-family:Times New Roman;font-style:normal;font-variant:normal;font-weight:normal;letter-spacing:normal;line-height:normal;text-indent:0px;text-transform:none;white-space:normal;word-spacing:0px;font-size:medium"><span style="border-collapse:collapse;font-family:arial,sans-serif;font-size:13px">Credits</span></span>
-   <span style="border-collapse:separate;color:rgb(0,0,0);font-family:Times New Roman;font-style:normal;font-variant:normal;font-weight:normal;letter-spacing:normal;line-height:normal;text-indent:0px;text-transform:none;white-space:normal;word-spacing:0px;font-size:medium"><span style="border-collapse:collapse;font-family:arial,sans-serif;font-size:13px">Cooper</span></span>
