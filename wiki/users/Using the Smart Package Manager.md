Using the Smart Package Manager
===============================
Smart manages RPM packages on PureDarwin. This page describes how to use it.

### What is smart
Smart is the tool you use to manage add-on software packages on PureDarwin. It can install, upgrade, and uninstall software packages and their dependencies using software repositories in the Internet.
### Installing smart
Future versions of PureDarwin might come with smart preinstalled.
Until that is true, you have to install smart and its dependencies from [smart.mpkg.dmg](http://puredarwin.darkhatter.net/macports/smart-0.52.dmg) to the PureDarwin volume using a Mac.
Alternatively, mount the (uncompressed) smart.dmg on the PureDarwin system and install it with



`cd / ; find /Volumes/smart*/smart-*.mpkg/Contents/Packages/*.pkg/Contents/Archive.pax.gz `
`-print -exec pax -z -f {} ;`


(not recommended for end users).

Smart and its dependencies need both Python 2.4 (comes with smart.mpkg) and Python 2.5 (is expected to come with the base system, but is missing from Darwin and hence needs to be installed from MacPorts). **To be fixed**
### Setting up smart
Future versions of PureDarwin might come with smart preconfigured.
Until that is true, do the following to set up the PureDarwin repository:



PYTHONPATH=/opt/local/lib/python2.5/site-packages/smart/backends/:
/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH 
/opt/local/bin/python2.4 /opt/local/bin/smart 
channel --add  PureDarwin type=rpm-md baseurl=http://xref.puredarwin.org/macports/RPMS/i386/



`PYTHONPATH=/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH /opt/local/bin/python2.4 /opt/local/bin/smart update`


(...)

Alias: PureDarwin
Type: rpm-md
Base URL: http://xref.puredarwin.org/macports/RPMS/i386/


Include this channel? (y/N): y



  from crpmver import *




When we use Python 2.5 it's the other way around:


``
`  import zlib`



Note that this needs a working network, which is not yet in PureDarwin. Hence this should work in a chroot only, but even there it doesn't... How to fix this?
### Using smart
What follows are the most commonly used operations in smart. See `smart --help` for more information.
Currently smart must be invoked with

`PYTHONPATH=/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH /opt/local/bin/python2.4 /opt/local/bin/smart`


This needs to be fixed.
#### Installing a package
To install vim:

`PYTHONPATH=/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH /opt/local/bin/python2.4 /opt/local/bin/smart install vim`

vim should now be installed in /opt/local/bin/vim.
#### Removing a package
To remove vim:

`PYTHONPATH=/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH /opt/local/bin/python2.4 /opt/local/bin/smart remove vim`
### References
[Smart homepage](http://labix.org/smart)
