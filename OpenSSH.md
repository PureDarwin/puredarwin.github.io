OpenSSH
=======

This page describes how to use ssh (SSH client and OpenSSH daemon) on PureDarwin.

### Installing the SSH server
To install the SSH server, simply install OpenSSH.root.tar.gz (you can find a version compiled for Darwin 9 [here](http://src.macosforge.org/Roots/9A581/OpenSSH.root.tar.gz)).
### Activating the SSH server
<span style="font-size:small">To activate the SSH server (it will be automatically launched on every boot), issue</span>

<span style="font-size:small">sudo launchctl load -w /System/Library/LaunchDaemons/ssh.plist </span>


To stop the SSH server, issue

<span style="font-size:small">sudo launchctl unload -w /System/Library/LaunchDaemons/ssh.plist </span>
### Connecting to the SSH server
To connect, do
<span style="font-size:small">ssh localhost -l toor</span>
<span style="font-size:small">
</span>
<span style="font-size:small"><span style="font-family:Arial,Verdana,sans-serif;font-size:13px">if you have a user "toor". Don't forget to change the password with the "passwd" command.</span></span>
