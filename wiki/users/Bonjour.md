Bonjour
=======

![](http://upload.wikimedia.org/wikipedia/en/9/91/Apple_Bonjour_Icon.png)

Bonjour is Apple's implementation of the [Zeroconf](http://en.wikipedia.org/wiki/Zeroconf) service discovery protocol. mDNSResponder is the open source software from Apple that implements Bonjour in both Mac OS X and Darwin.

### Announcing services

#### Manually

To manually announce services on the local network, you can use the mDNS command.

```
# Announce HTTP server
mDNS -R . _http._tcp . 80

# Announce AFP server
mDNS -R . _afpovertcp._tcp. 548
```

More service types are defined at http://www.dns-sd.org/ServiceTypes.html

#### Automatically

Servers on Darwin systems are usually launched through launchd. You can use the `Bonjour` key in LaunchDaemons plist files to have launchd automatically announce services.

### Browsing services

To browse announced services on the Mac, you can use [Bonjour Browser](http://www.tildesoft.com/Programs.html#BonjourBrowser).

### References

-   <https://developer.apple.com/bonjour/>
-   [DNS SRV (RFC 2782) Service Types](http://www.dns-sd.org/ServiceTypes.html)