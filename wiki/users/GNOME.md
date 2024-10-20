GNOME
=====
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
![](/img/users/gnome/gnome-logo.jpg)
GNOME is a graphical desktop environment and development platform. For more information, see <http://www.gnome.org/>.
This page is about running GNOME components on a PureDarwin system.

### GNOME components running in PureDarwin 9
Right now, we have the following components running on PureDarwin 9.
#### metacity
Metacity is the window manager most commonly used with GNOME. 
Once you have installed it (e.g., from MacPorts) and try to launch it, you will get


Window manager warning: Failed to contact configuration server; some possible causes are that you need to enable TCP/IP networking for ORBit, or you have stale NFS locks due to a system crash. See http://projects.gnome.org/gconf/ for information. (Details -  1: Failed to get connection to session: Not enough memory)
Dynamic session lookup supported but failed: launchd did not provide a socket path, verify that org.freedesktop.dbus-session.plist is loaded!
Window manager warning: Failed to contact configuration server; some possible causes are that you need to enable TCP/IP networking for ORBit, or you have stale NFS locks due to a system crash. See http://projects.gnome.org/gconf/ for information. (Details -  1: Failed to get connection to session: Not enough memory)


Then simply 


launchctl load -w /Library/LaunchAgents/org.freedesktop.dbus-session.plist 
metacity


and it will run.
#### zenity
Zenity is a little tool that can be used (e.g., in bash scripts) to create simple GTK dialogs.
