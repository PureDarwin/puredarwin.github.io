GNOME
=====
<div style="display:inline;float:right;margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px">
[![](../_/rsrc/1264268603393/users/gnome/gnome-logo.jpg)](gnome/gnome-logo.jpg%3Fattredirects=0)
GNOME is a graphical desktop environment and development platform. For more information, see <http://www.gnome.org/>.
This page is about running GNOME components on a PureDarwin system.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** GNOME components running in PureDarwin 9](gnome.html#TOC-GNOME-components-running-in-PureDarwin-9)
    1.  [**1.1** metacity](gnome.html#TOC-metacity)
    2.  [**1.2** zenity](gnome.html#TOC-zenity)


### GNOME components running in PureDarwin 9
Right now, we have the following components running on PureDarwin 9.
#### metacity
Metacity is the window manager most commonly used with GNOME. 
Once you have installed it (e.g., from MacPorts) and try to launch it, you will get


<span style="font-size:small">Window manager warning: Failed to contact configuration server; some possible causes are that you need to enable TCP/IP networking for ORBit, or you have stale NFS locks due to a system crash. See http://projects.gnome.org/gconf/ for information. (Details -  1: Failed to get connection to session: Not enough memory)</span>
<span style="font-size:small">Dynamic session lookup supported but failed: launchd did not provide a socket path, verify that org.freedesktop.dbus-session.plist is loaded!</span>
<span style="font-size:small">Window manager warning: Failed to contact configuration server; some possible causes are that you need to enable TCP/IP networking for ORBit, or you have stale NFS locks due to a system crash. See http://projects.gnome.org/gconf/ for information. (Details -  1: Failed to get connection to session: Not enough memory)</span>


Then simply 


<span style="font-size:small">launchctl load -w /Library/LaunchAgents/org.freedesktop.dbus-session.plist </span>
<span style="font-size:small">metacity</span>


and it will run.
#### zenity
Zenity is a little tool that can be used (e.g., in bash scripts) to create simple GTK dialogs.
