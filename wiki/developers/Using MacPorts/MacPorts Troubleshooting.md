MacPorts Troubleshooting
========================

This page contains some of the issues you might run into when using MacPorts on a PureDarwin system (or in a PureDarwin chroot). We also list pragmatic workarounds where possible. This page is mainly for reference via search engines, so we should always cite specific error messages here.

### gcc42
**Issue**
****
No suitable m4
**Workaround**
ln -s gm4 m4
**Issue**
In file included from ../../gcc-4.2.4/gcc/tsystem.h:104,
                 from ../../gcc-4.2.4/gcc/config/darwin-crt3.c:38:
/usr/include/stdlib.h:283: error: expected ',' or ';' before '__OSX_AVAILABLE_BUT_DEPRECATED

**Workaround**

 
### gtk2
**Issue**
"needs" Xcode
**Workaround**
`port edit gtk2`, delete the whole section regarding Xcode
**Issue**
configure: error: no acceptable Java compiler found in $PATH
**Workaround**
Need to port edit db46, delete the line about java, port install db46
Now we can continue to build the rest of gtk2
### python26
**Issue**
In file included from Python/mactoolboxglue.c:27:
Include/pymactoolbox.h:10:27: error: Carbon/Carbon.h: No such file or directory
Include/pymactoolbox.h:13:33: error: QuickTime/QuickTime.h: No such file or directory
**Workaround**
Use patch provided by afb in MacPorts ticket [#23122](http://trac.macports.org/ticket/23122)
Then you need to to the following so that subsequently installed Python modules are correctly found:
mkdir -p /opt/local/Library/Frameworks/Python.framework/Versions/2.6/lib
ln -s /opt/local//include/python2.6 /opt/local/Library/Frameworks/Python.framework/Versions/2.6/Headers
mkdir -p /opt/local/Library/Frameworks/Python.framework/Versions/2.6/bin/
ln -s /opt/local/bin/python2.6 /opt/local/Library/Frameworks/Python.framework/Versions/2.6/bin/
ln -s /opt/local/lib/python2.6/site-packages /opt/local/Library/Frameworks/Python.framework/Versions/2.6/lib/python2.6/
**tiff**
**
**
**Issue**
tiff "needs" Xcode
**Workaround**
`port edit tiff`, delete the line regarding Xcode
The following might also be necessary:
ln -s /usr/bin/true /usr/bin/defaults
### dnsmasq
**Issue**
make: yacc: Command not found
**Workaround**
Need to
port install byacc
ln -s /opt/local/bin/byacc /opt/local/bin/yacc
But then, the dependency nawk fails to build due to missing dsymutil, hence we need to do:
ln -s /usr/bin/true /usr/bin/dsymutil
### ~~subversion~~
**~~Issue~~**
~~subversion wants to use Keychain, which is not available in PureDarwin~~
~~
~~
**~~Workaround~~**
port install subversion +disable_keychain
~~
~~
~~Suggested puredarwin variant, see MacPorts ~~[~~#23304~~](https://trac.macports.org/ticket/23304)
### dbus
**Issue**
fails with "configure: error: launchd support explicitly enabled but not available"
**Workaround**
Install launch.h from the launchd binary root 
### xorg-libxcb
**Issue**
ImportError: No module named xcbgen.state
**Workaround**
Solved in python symlinking of site-packages above (see python26)
### mesa
**Issue**

 directory


**Workaround**

We should write a puredarwin variant
### xinit
**Issue**

<span style="font-size:small">DEBUG: Assembled command: 'cd "/opt/local/var/macports/build/_opt_local_var_macports_sources_rsync.macports.org_release_ports_x11_xinit/work/xinit-1.2.0" && /usr/bin/make -j2 all'</span>
/usr/bin/make  all-recursive
Making all in privileged_startx
/usr/bin/make  all-am
  CC     server.o
  CC     client.o
server.c:35:31: error: servers/bootstrap.h: No such file or directory

**Workaround**
Install headers from launchd.root.tar.gz 
### xorg-server
**Issue**
IOKit portion (needed for Darwin) is missing


**Workaround**

### glitz
**Issue**


**Workaround**
`port edit glitz`, delete all lines regarding Xcode
### db47
**Issue**
checking if jikes works... configure: error: The Java compiler jikes failed


**Workaround**
Edit the portfile so that it includes

variant puredarwin { 
 configure.args-delete   --enable-java 
} 
### curlftpfs
**Issue**
Can't be built since MacFUSE doesn't build on PureDarwin due to being an Xcode project


**Workaround**
Install MacFUSE from project's pkg, edit portfile to remove dependency on MacFUSE


To be continued

