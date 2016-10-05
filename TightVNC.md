TightVNC
========
TightVNC is a way to use X11 applications over the network. ![](http://www.tightvnc.com/logo/tightvnc-logo-90x90.png)
<div style="display:block;margin-left:auto;text-align:right">

Right now, support for native graphics is limited on PureDarwin. Also, you might want to use X11 over the network. TightVNC, a VNC server that runs on PureDarwin, can offer a graphical desktop for the network that you can access from any Mac OS X, Unix, Linux and Windows machine.

To use TightVNC, install it on a PureDarwin system with MacPorts. 
Launch it with

<span style="font-size:small">vncserver</span>

To connect from a Mac OS X computer running Leopard or later, open Safari and enter the URL <span style="font-size:small">vnc://hostname:5901</span> in the address bar and press enter. You will be connected to the TightVNC server on the PureDarwin host with the name hostname. To connect from other machines, you can use any VNC client.

Note that you should not run the TightVNC server as root. 

Also, it might be necessary to 

<span style="font-size:small">export DISPLAY=:1</span>

in order to launch graphical applications.

To announce the server on the network with [Bonjour](bonjour.html), you can use

<span style="font-size:small">dns-sd -R . _rfb._tcp . 5901 &</span>

 
Probably a clean launchd LaunchDaemon or LaunchAgent plist file should be written that listens to the port, announces the rfb service with Bonjour and launches TightVNC on demand. 
### Launching a VNC server for remote screen sharing (working jointly on same session)
The following launches a VNC server that multiple persons can connect to.
Using the <span style="font-size:small">vncpasswd</span> command, you can set a read-write and a read-only password, making this ideal to do screen sharing.

<span style="font-size:small">Xvnc :0 -desktop X  -alwaysshared -httpd /opt/local/share/vnc/classes -auth /var/root/.Xauthority </span>
<span style="font-size:small">    -geometry 800x600 -depth 24 -rfbwait 120000 </span>
<span style="font-size:small">    -rfbauth /var/root/.vnc/passwd -rfbport 5900 &</span>
<span style="font-size:small">twm &</span>
<span style="font-size:small">xterm &</span>
<span style="font-size:small">xsetroot -gray</span>
Now users can connect to **http://the.url:5800** (a page with an embedded VNC viewer served by Xvnc) or can use a native VNC client such as the one built into Mac OS X by entering **vnc://the.url**
