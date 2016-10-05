login
=====
Since multi-user support is available, managing logins (so that users run with only the permissions they have been granted) follows naturally.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:301px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Console login](login.html#TOC-Console-login)
2.  [**2** SSH login](login.html#TOC-SSH-login)
3.  [**3** X login](login.html#TOC-X-login)
    1.  [**3.1** X Display manager list](login.html#TOC-X-Display-manager-list)
4.  [**4** Smartcard login](login.html#TOC-Smartcard-login)
5.  [**5** Disable login](login.html#TOC-Disable-login)
6.  [**6** Auto login](login.html#TOC-Auto-login)


### Console login
Console login can be achieved using the <span style="font-family:courier new,monospace"><span style="font-size:small">`getty'</span></span> tool. There is a launchd plist (com.apple.getty.plist) available (but uninstalled by default - we need to add this to the next revision of Spring) as part of the <span style="font-style:italic">system_cmds</span> project. Installing this leads to a login prompt being displayed (as long as the startx script isn't also run).

(The prompt gets swamped by error messages, but we're working to eliminate them.)

Also note that <span style="font-family:courier new;font-size:12px">`getty'</span> takes care of creating user security sessions, so the <span style="font-style:italic">pam_sessioncreate.so</span> hack is no longer needed and can be removed from <span style="font-family:courier new,monospace"><span style="font-size:small">/etc/pam.d/login</span></span>. It even creates the SECURITYSESSIONID environment variable, which is very nice.
### SSH login
SSH login is working if an sshd server is of course running. A security session is automatically created, but the SECURITYSESSIONID environment variable is not set (which is the same behaviour as on OS X).

### X login
Authorised X login is not currently supported, but should be easy enough to implement. The <span style="font-style:italic">org.puredarwin.x.plist</span> should invoke an "Xlogin" app instead of the default window manager, as it currently does. Since X and PAM are standards on Linux/BSD, finding the source code to such an app should not be a problem. One which doesn't rely on any particular widget set would be preferred. The source will then need to be (very slightly) modified to include the necessary security session creation code. This won't be very hard.

So if someone can recommend a simple X login app which we can modify, let us know.
(xdm is a basic one (and there is also gdm and kdm (probably more dependencies))))
(we could also provide a X CLI one tunneled in a SSH session: ssh user@::1 -X (or -Y..) + the command which launchs X (pros: ssh authentication is reliable, the session is encrypted, ::1 force to use IPv6 sockets to localhost | con: too slow in QEMU probably))
#### X Display manager list
<span style="text-decoration:underline">To investigate:</span>
> xdm
> [slim](http://slim.berlios.de/)
> [enter](http://enter.sourceforge.net/) (not maintained since last updat<span style="font-family:arial,sans-serif"><span style="font-size:small">e: </span></span><span style="line-height:14px"><span style="font-family:arial,sans-serif"><span style="font-size:small">March 26, 2007)</span></span></span>
> <span style="line-height:14px">[orthos](http://exa.czweb.org/?view=orthos) (unsecure?)</span>
> <span style="line-height:14px">Entrance (from e17)</span>
> <span style="line-height:14px">[wdm](http://voins.program.ru/wdm/index.html.en) (not maitained)</span>
<span style="text-decoration:underline">
</span>
<span style="text-decoration:underline">Ready to provide (+default choice (e.g., in bold)):</span>
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
