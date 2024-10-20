login
=====
Since multi-user support is available, managing logins (so that users run with only the permissions they have been granted) follows naturally.

### Console login
Console login can be achieved using the ``getty'` tool. There is a launchd plist (com.apple.getty.plist) available (but uninstalled by default - we need to add this to the next revision of Spring) as part of the *system_cmds* project. Installing this leads to a login prompt being displayed (as long as the startx script isn't also run).

(The prompt gets swamped by error messages, but we're working to eliminate them.)

Also note that `getty' takes care of creating user security sessions, so the *pam_sessioncreate.so* hack is no longer needed and can be removed from `/etc/pam.d/login`. It even creates the SECURITYSESSIONID environment variable, which is very nice.
### SSH login
SSH login is working if an sshd server is of course running. A security session is automatically created, but the SECURITYSESSIONID environment variable is not set (which is the same behaviour as on OS X).

### X login
Authorised X login is not currently supported, but should be easy enough to implement. The *org.puredarwin.x.plist* should invoke an "Xlogin" app instead of the default window manager, as it currently does. Since X and PAM are standards on Linux/BSD, finding the source code to such an app should not be a problem. One which doesn't rely on any particular widget set would be preferred. The source will then need to be (very slightly) modified to include the necessary security session creation code. This won't be very hard.

So if someone can recommend a simple X login app which we can modify, let us know.
(xdm is a basic one (and there is also gdm and kdm (probably more dependencies))))
(we could also provide a X CLI one tunneled in a SSH session: ssh user@::1 -X (or -Y..) + the command which launchs X (pros: ssh authentication is reliable, the session is encrypted, ::1 force to use IPv6 sockets to localhost | con: too slow in QEMU probably))
#### X Display manager list
__To investigate:__
> xdm
> [slim](http://slim.berlios.de/)
> [enter](http://enter.sourceforge.net/) (not maintained since last update: March 26, 2007)
> [orthos](http://exa.czweb.org/?view=orthos) (unsecure?)
> Entrance (from e17)
> [wdm](http://voins.program.ru/wdm/index.html.en) (not maitained)
__
__
__Ready to provide (+default choice (e.g., in bold)):__
> ..

### Smartcard login
Need to investigate: <http://smartcardservices.macosforge.org/>
### Disable login
Disabling possibility of login on the system is also part of the management.
(Remove getty and login stuff, remote_cmds, sshd, etc..)
(via dscl)
(removing shells)
Automatically create the /etc/nologin file.
### Auto login
Should we "enable" this kind of dangerous feature (it is technically possible), is it really needed?
