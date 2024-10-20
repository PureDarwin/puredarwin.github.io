SpeedStep
=========
SpeedStep is a technology from Intel to throttle the CPU's clock speed when it is not fully utilized in order to save power. This is especially useful for mobile devices and servers.

On a PureDarwin system, you can use the [VoodooPower](http://code.google.com/p/voodoo-power/) kernel extension in order to use SpeedStep.

On Intel Atom systems, PureDarwin 9 is known to work well with the VoodooPowerMini.kext (Leopard version) that. (On PureDarwin 10, you'll use the Snow Leopard version instead.)

You can download it from <http://www.superhai.com/darwin.html>

After downloading VoodooPowerMini.kext, you can install it on your PureDarwin 9 system:

sudo chown root:wheel 755 VoodooPowerMini.kext
sudo chmod -R 755 VoodooPowerMini.kext
mv VoodooPowerMini.kext /System/Library/Extensions/
kextload /System/Library/Extensions/VoodooPowerMini.kext
# Rebuild kext cache with kextload

Now, you can verify that it is working:


toor@PureDarwin:~% sysctl -a | grep cpufrequency
hw.cpufrequency = **800015400**
hw.cpufrequency_max: **1600030800**
hw.cpufrequency_min: 800015400


If hw.cpufrequency is lower than hw.cpufrequency_max in low-CPU usage situations, then SpeedStep is working correctly.
