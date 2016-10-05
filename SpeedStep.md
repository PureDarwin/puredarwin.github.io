SpeedStep
=========
SpeedStep is a technology from Intel to throttle the CPU's clock speed when it is not fully utilized in order to save power. This is especially useful for mobile devices and servers.

On a PureDarwin system, you can use the [VoodooPower](http://code.google.com/p/voodoo-power/) kernel extension in order to use SpeedStep.

On Intel Atom systems, PureDarwin 9 is known to work well with the VoodooPowerMini.kext (Leopard version) that. (On PureDarwin 10, you'll use the Snow Leopard version instead.)

You can download it from <http://www.superhai.com/darwin.html>

After downloading VoodooPowerMini.kext, you can install it on your PureDarwin 9 system:

<span style="font-size:small">sudo chown root:wheel 755 VoodooPowerMini.kext</span>
<span style="font-size:small">sudo chmod -R 755 VoodooPowerMini.kext</span>
<span style="font-size:small">mv VoodooPowerMini.kext /System/Library/Extensions/</span>
<span style="font-size:small">kextload /System/Library/Extensions/VoodooPowerMini.kext</span>
<span style="font-size:small"># Rebuild kext cache with kextload</span>

Now, you can verify that it is working:


<span style="font-size:small">toor@PureDarwin:~% sysctl -a | grep cpufrequency</span>
<span style="font-size:small">hw.cpufrequency = </span>**<span style="font-size:small">800015400</span>**
<span style="font-size:small">hw.cpufrequency_max: </span>**<span style="font-size:small">1600030800</span>**
<span style="font-size:small">hw.cpufrequency_min: 800015400</span>


If hw.cpufrequency is lower than hw.cpufrequency_max in low-CPU usage situations, then SpeedStep is working correctly.
