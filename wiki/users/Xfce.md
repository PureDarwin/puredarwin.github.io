Xfce
====
"Xfce is a lightweight desktop environment for various *NIX systems. Designed for productivity, it loads and executes applications fast, while conserving system resources." - Olivier Fourdan, creator of Xfce 

<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px"><a href="https://raw.github.com/wiki/PureDarwin/PureDarwin/images/600px-xfce_logo.png?attredirects=0" imageanchor="1"><img border="0" height="100" src="https://raw.github.com/wiki/PureDarwin/PureDarwin/images/600px-xfce_logo.png?height=100&amp;width=100" width="100"></a></div>

<img border="0" height="300" src="https://raw.github.com/wiki/PureDarwin/PureDarwin/images/pd201001.jpg?height=300&amp;width=400" width="400">

![](/img/screenshots/pd201001.jpg)

The screenshot above shows Xfce compiled on a PureDarwin 9 system from MacPorts, using xfce4_axiom_theme and a background from psdgraphics.com.

Xfce can be launched so that it can be accessed by VNC clients.

`Note: currently this appears to work only as the root user, needs to be investigated.`

```bash
sudo Xvnc :0 -desktop X  -alwaysshared -httpd /opt/local/share/vnc/classes  
    -geometry 800x600 -depth 24 -rfbwait 120000 
    -rfbauth /var/root/.vnc/passwd -rfbport 5900 &
xsetroot -gray
export DISPLAY=:0
sleep 1
sudo launchctl load -w /Library/LaunchAgents/org.freedesktop.dbus-session.plist
xfce4-session &
```

To be continued.
### Credits
Thanks Anders F Björklund for his continuing support and bugfixes of Xfce in MacPorts.

