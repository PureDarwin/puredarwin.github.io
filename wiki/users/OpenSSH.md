OpenSSH
=======

This page describes how to use ssh (SSH client and OpenSSH daemon) on PureDarwin.

### Installing the SSH server
To install the SSH server, simply install OpenSSH.root.tar.gz (you can find a version compiled for Darwin 9 [here](http://src.macosforge.org/Roots/9A581/OpenSSH.root.tar.gz)).
### Activating the SSH server
To activate the SSH server (it will be automatically launched on every boot), issue

sudo launchctl load -w /System/Library/LaunchDaemons/ssh.plist 


To stop the SSH server, issue

sudo launchctl unload -w /System/Library/LaunchDaemons/ssh.plist 
### Connecting to the SSH server
To connect, do
ssh localhost -l toor


if you have a user "toor". Don't forget to change the password with the "passwd" command.
