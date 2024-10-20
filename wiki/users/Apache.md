Apache
======

Apache is the most popular HTTP server software in use. It can be installed on PureDarwin, e.g., from the MacPorts project.

Installing apache
-----------------
Apache can be installed as `apache2` port from MacPorts.

Configuring apache
------------------
The configuration files can be found in `/opt/local/apache2/conf` if you have installed the apache2 package from MacPorts.

To load apache2 on every boot, run `sudo launchctl load -w /Library/LaunchDaemons/org.macports.apache2.plist`.

Announcing apache in the local network
--------------------------------------
Running
`dns-sd -R . _http._tcp. . 80` should announce the web server in the local network via [Bonjour](https://github.com/PureDarwin/PureDarwin/wiki/Bonjour).
The service then appears in the Safari Bonjour bookmarks folder. Using a '.' as the service name is equivalent to no service name, telling mDNS to use the computer name. However, this appears not to work properly, since the announced domain name has the ".local." suffix which Apache apparently does not recognize?

To be continued.