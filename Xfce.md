Xfce
====

<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](../_/rsrc/1264335424967/users/xfce/600px-xfce_logo.png%3Fheight=100&width=100)](xfce/600px-xfce_logo.png%3Fattredirects=0)
"Xfce is a lightweight desktop environment for various *NIX systems. Designed for productivity, it loads and executes applications fast, while conserving system resources." - Olivier Fourdan, creator of Xfce 


[![](../_/rsrc/1264331892311/screenshots/pd201001.jpg%3Fheight=300&width=400)](../screenshots/pd201001.jpg%3Fattredirects=0)

The screenshot above shows Xfce compiled on a PureDarwin 9 system from MacPorts, using xfce4_axiom_theme and a background from psdgraphics.com.

Xfce can be launched so that it can be accessed by VNC clients.

<span style="font-size:small">Note: currently this appears to work only as the root user, needs to be investigated.</span>
<span style="font-size:small">
 </span>

<span style="font-size:small">sudo Xvnc :0 -desktop X  -alwaysshared -httpd /opt/local/share/vnc/classes  </span>
<span style="font-size:small">    -geometry 800x600 -depth 24 -rfbwait 120000 </span>
<span style="font-size:small">    -rfbauth /var/root/.vnc/passwd -rfbport 5900 &</span>
<span style="font-size:small">xsetroot -gray</span>
<span style="font-size:small">export DISPLAY=:0</span>
<span style="font-size:small">sleep 1</span>
<span style="font-size:small">sudo launchctl load -w /Library/LaunchAgents/org.freedesktop.dbus-session.plist </span>
<span style="font-size:small">xfce4-session &</span>

To be continued.
### Credits
Thanks Anders F BjÃ¶rklund for his continuing support and bugfixes of Xfce in MacPorts.

