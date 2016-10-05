MacPorts Troubleshooting
========================

This page contains some of the issues you might run into when using MacPorts on a PureDarwin system (or in a PureDarwin chroot). We also list pragmatic workarounds where possible. This page is mainly for reference via search engines, so we should always cite specific error messages here.
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** gcc42](troubleshooting.html#TOC-gcc42)
2.  [**2** gtk2](troubleshooting.html#TOC-gtk2)
3.  [**3** python26](troubleshooting.html#TOC-python26)
4.  [**4** dnsmasq](troubleshooting.html#TOC-dnsmasq)
5.  [**5** subversion](troubleshooting.html#TOC-subversion)
6.  [**6** dbus](troubleshooting.html#TOC-dbus)
7.  [**7** xorg-libxcb](troubleshooting.html#TOC-xorg-libxcb)
8.  [**8** mesa](troubleshooting.html#TOC-mesa)
9.  [**9** xinit](troubleshooting.html#TOC-xinit)
10. [**10** xorg-server](troubleshooting.html#TOC-xorg-server)
11. [**11** glitz](troubleshooting.html#TOC-glitz)
12. [**12** db47](troubleshooting.html#TOC-db47)
13. [**13** curlftpfs](troubleshooting.html#TOC-curlftpfs)

### gcc42
**Issue**
**<span style="font-size:12px;font-weight:normal"></span>**
No suitable m4
**Workaround**
ln -s gm4 m4
**Issue**
<span style="font-size:small">In file included from ../../gcc-4.2.4/gcc/tsystem.h:104,</span>
<span style="font-size:small">                 from ../../gcc-4.2.4/gcc/config/darwin-crt3.c:38:</span>
<span style="font-size:small">/usr/include/stdlib.h:283: error: expected ',' or ';' before '__OSX_AVAILABLE_BUT_DEPRECATED</span>

**Workaround**
<span style="font-size:12px">Unknown<span style="color:rgb(0,0,0);font-family:Helvetica,Verdana,sans-serif">, see MacPorts [#23200](https://trac.macports.org/ticket/23200)</span></span>
<span style="font-size:12px"> </span>
### gtk2
**Issue**
"needs" Xcode
**Workaround**
<span style="font-family:courier new,monospace;font-size:small">port edit gtk2</span>, delete the whole section regarding Xcode
**Issue**
configure: error: no acceptable Java compiler found in $PATH
**Workaround**
Need to <span style="font-size:small">port edit db46</span>, delete the line about java, <span style="font-size:small">port install db46</span>
Now we can continue to build the rest of gtk2
### python26
**Issue**
In file included from Python/mactoolboxglue.c:27:
Include/pymactoolbox.h:10:27: error: Carbon/Carbon.h: No such file or directory
Include/pymactoolbox.h:13:33: error: QuickTime/QuickTime.h: No such file or directory
**Workaround**
Use patch provided by afb in MacPorts ticket [#23122](http://trac.macports.org/ticket/23122)
Then you need to to the following so that subsequently installed Python modules are correctly found:
<span style="font-size:small">mkdir -p /opt/local/Library/Frameworks/Python.framework/Versions/2.6/lib</span>
<span style="font-size:small">ln -s /opt/local//include/python2.6 /opt/local/Library/Frameworks/Python.framework/Versions/2.6/Headers</span>
<span style="font-size:small">mkdir -p /opt/local/Library/Frameworks/Python.framework/Versions/2.6/bin/</span>
<span style="font-size:small">ln -s /opt/local/bin/python2.6 /opt/local/Library/Frameworks/Python.framework/Versions/2.6/bin/</span>
<span style="font-size:small">ln -s /opt/local/lib/python2.6/site-packages /opt/local/Library/Frameworks/Python.framework/Versions/2.6/lib/python2.6/</span>
<span style="font-family:Arial,Verdana,sans-serif;font-size:14px;font-weight:bold">tiff</span>
<span style="font-size:14px">**
**</span>
**Issue**
tiff "needs" Xcode
**Workaround**
<span style="font-family:courier new,monospace;font-size:small">port edit tiff</span>, delete the line regarding Xcode
The following might also be necessary:
<span style="font-size:small">ln -s /usr/bin/true /usr/bin/defaults</span>
### dnsmasq
**Issue**
make: yacc: Command not found
**Workaround**
Need to
<span style="font-size:small">port install byacc</span>
<span style="font-size:small">ln -s /opt/local/bin/byacc /opt/local/bin/yacc</span>
But then, the dependency nawk fails to build due to missing dsymutil, hence we need to do:
ln -s /usr/bin/true /usr/bin/dsymutil
### <span style="text-decoration:line-through">subversion</span>
**<span style="text-decoration:line-through">Issue</span>**
<span style="text-decoration:line-through">subversion wants to use Keychain, which is not available in PureDarwin</span>
<span style="text-decoration:line-through">
</span>
**<span style="text-decoration:line-through">Workaround</span>**
<span style="font-size:small"><span style="text-decoration:line-through">port install subversion +disable_keychain</span></span>
<span style="text-decoration:line-through">
</span>
<span style="text-decoration:line-through">Suggested puredarwin variant, see MacPorts </span>[<span style="text-decoration:line-through">#23304</span>](https://trac.macports.org/ticket/23304)
### dbus
**Issue**
fails with <span style="font-size:small">"configure: error: launchd support explicitly enabled but not available"</span>
**Workaround**
Install launch.h from the launchd binary root 
### xorg-libxcb
**Issue**
ImportError: No module named xcbgen.state
**Workaround**
Solved in python symlinking of site-packages above (see python26)
### mesa
<span style="font-size:12px"><span style="font-family:arial,sans-serif;font-size:13px;border-collapse:collapse">**Issue**</span></span>
<span style="border-collapse:collapse"><span style="font-size:small">include/GL/gl.h:53:68: error:
 /System/Library/Frameworks/</span><span style="font-size:small">OpenGL.framework/Headers/gl.h: No such file or
</span></span>
<span style="border-collapse:collapse"><span style="font-size:small"> directory</span></span>
<span style="border-collapse:collapse">
</span>
<span style="font-size:12px"><span style="font-family:arial,sans-serif;font-size:13px;border-collapse:collapse">**Workaround**</span></span>
<span style="border-collapse:collapse"><span style="font-size:small">sudo port -v install mesa -hw_render <span style="font-family:arial,sans-serif;font-size:13px">(see MacPorts [#23210](http://trac.macports.org/ticket/23210))</span></span></span>
<span style="border-collapse:collapse">We should write a puredarwin variant</span>
### xinit
<span style="border-collapse:collapse">**Issue**</span>
<span style="border-collapse:collapse"></span>
<span style="font-size:small">DEBUG: Assembled command: 'cd "/opt/local/var/macports/build/_opt_local_var_macports_sources_rsync.macports.org_release_ports_x11_xinit/work/xinit-1.2.0" && /usr/bin/make -j2 all'</span>
<span style="font-size:small">/usr/bin/make  all-recursive</span>
<span style="font-size:small">Making all in privileged_startx</span>
<span style="font-size:small">/usr/bin/make  all-am</span>
<span style="font-size:small">  CC     server.o</span>
<span style="font-size:small">  CC     client.o</span>
<span style="font-size:small">server.c:35:31: error: servers/bootstrap.h: No such file or directory</span>

**Workaround**
Install headers from launchd.root.tar.gz 
### xorg-server
<span style="border-collapse:collapse">**Issue**</span>
<span style="border-collapse:collapse">IOKit portion (needed for Darwin) is missing</span>
<span style="border-collapse:collapse">
</span>
<span style="border-collapse:collapse">**Workaround**</span>
<span style="border-collapse:collapse">Need to find and integrate <span style="font-size:small">hw/darwin/iokit/Makefile.am</span> </span>
### glitz
<span style="font-size:12px">**Issue**</span>
<span style="font-size:12px">**<span style="font-family:Helvetica,Verdana,sans-serif;font-weight:normal">glitz "needs" Xcode</span>**</span>
<span style="font-size:12px"></span>
**Workaround**
<span style="font-family:courier new,monospace;font-size:small">port edit glitz</span>, delete all lines regarding Xcode
### db47
<span style="font-size:12px">**Issue**</span>
<span style="font-size:12px">checking if jikes works... configure: error: The Java compiler jikes failed</span>
<span style="font-size:12px">
</span>
<span style="font-size:12px">**Workaround**</span>
<span style="font-size:12px">Edit the portfile so that it includes</span>
<span style="font-size:12px"></span>
<span style="font-size:small">variant puredarwin { </span>
<span style="white-space:pre"><span style="font-size:small"> </span></span><span style="font-size:small">configure.args-delete   --enable-java </span>
<span style="font-size:small">} </span>
### curlftpfs
<span style="font-size:12px">**Issue**</span>
<span style="font-size:12px">Can't be built since MacFUSE doesn't build on PureDarwin due to being an Xcode project</span>
<span style="font-size:12px">
</span>
<span style="font-size:12px">**Workaround**</span>
<span style="font-size:12px">Install MacFUSE from project's pkg, edit portfile to remove dependency on MacFUSE</span>
<span style="font-size:12px">
</span>
<span style="font-size:12px">To be continued</span>

