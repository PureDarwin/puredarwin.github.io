PS2 Controller
==============
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
![](/img/developers/xnu/ps2-controller/voodoolabs_500.png)
Draft.

Voodoo PS2 Controller
---------------------
VoodooPS2Controller 0.98 has been released and seems to work.
All KEXTs below are loaded at boot:
-   VoodooPS2Controller (tested in tty)
-   VoodooPS2Keyboard (tested in tty)
-   VoodooPS2Mouse
-   VoodooPS2Trackpad

 kextstat reports:
   23    2 0xb007000  0x6000     0x5000     org.voodoo.driver.PS2Controller (1.1.0) <12>
   26    0 0xb10d000  0x3000     0x2000     org.voodoo.driver.PS2Keyboard (1.1.0) <23 22 12>
   51    0 0xd25f000  0x8000     0x7000     org.voodoo.driver.PS2Trackpad (1.1.0) <23 22 12>

__Notes:__ The KEXTs above are conflicting with ACPIPS2Nub from D. Elliott (e.g., needed for ApplePS2Controller) so be sure choose one or the other solution exclusively. ACPIPS2Nub will be autoloaded, but not necessarly ApplePS2Controller KEXTs.



`kextload /System/Library/Extensions/ApplePS2Controller.kext/Contents/PlugIns/ApplePS2Keyboard.kext`
`kextload /System/Library/Extensions/ApplePS2Controller.kext/Contents/PlugIns/ApplePS2Mouse.kext`
`kextload /System/Library/Extensions/ApplePS2Controller.kext/Contents/PlugIns/ApplePS2Trackpad.kext`



