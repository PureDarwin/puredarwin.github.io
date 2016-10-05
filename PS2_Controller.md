PS2 Controller
==============
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](../../_/rsrc/1247875684014/developers/xnu/ps2-controller/voodoolabs_500.png%3Fheight=71&width=96)](ps2-controller/voodoolabs_500.png%3Fattredirects=0)
Draft.
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Voodoo PS2 Controller](ps2-controller.html#TOC-Voodoo-PS2-Controller)


Voodoo PS2 Controller
---------------------
VoodooPS2Controller 0.98 has been released and seems to work.
All KEXTs below are loaded at boot:
-   VoodooPS2Controller (tested in tty)
-   VoodooPS2Keyboard (tested in tty)
-   VoodooPS2Mouse
-   VoodooPS2Trackpad

 kextstat reports:
<span style="font-size:small">   23    2 0xb007000  0x6000     0x5000     org.voodoo.driver.PS2Controller (1.1.0) &lt;12&gt;</span>
<span style="font-size:small">   26    0 0xb10d000  0x3000     0x2000     org.voodoo.driver.PS2Keyboard (1.1.0) &lt;23 22 12&gt;</span>
<span style="font-size:small">   51    0 0xd25f000  0x8000     0x7000     org.voodoo.driver.PS2Trackpad (1.1.0) &lt;23 22 12&gt;</span>

<span style="text-decoration:underline">Notes:</span> The KEXTs above are conflicting with ACPIPS2Nub from D. Elliott (e.g., needed for ApplePS2Controller) so be sure choose one or the other solution exclusively. ACPIPS2Nub will be autoloaded, but not necessarly ApplePS2Controller KEXTs.

<span style="font-family:Helvetica,Verdana,sans-serif;font-size:12px"></span>
<span style="font-size:13px"></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span>kextload /System/Library/Extensions/ApplePS2Controller.kext/Contents/PlugIns/ApplePS2Keyboard.kext</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">kextload /System/Library/Extensions/ApplePS2Controller.kext/Contents/PlugIns/ApplePS2Mouse.kext</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">kextload /System/Library/Extensions/ApplePS2Controller.kext/Contents/PlugIns/ApplePS2Trackpad.kext</span></span>
<span style="font-size:small">
</span>

