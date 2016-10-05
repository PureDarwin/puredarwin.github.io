Using the Smart Package Manager
===============================
Smart manages RPM packages on PureDarwin. This page describes how to use it.
<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** What is smart](smart.html#TOC-What-is-smart)
2.  [**2** Installing smart](smart.html#TOC-Installing-smart)
3.  [**3** Setting up smart](smart.html#TOC-Setting-up-smart)
4.  [**4** Using smart](smart.html#TOC-Using-smart)
    1.  [**4.1** Installing a package](smart.html#TOC-Installing-a-package)
    2.  [**4.2** Removing a package](smart.html#TOC-Removing-a-package)
5.  [**5** References](smart.html#TOC-References)

### What is smart
Smart is the tool you use to manage add-on software packages on PureDarwin. It can install, upgrade, and uninstall software packages and their dependencies using software repositories in the Internet.
### Installing smart
Future versions of PureDarwin might come with smart preinstalled.
Until that is true, you have to install smart and its dependencies from [smart.mpkg.dmg](http://puredarwin.darkhatter.net/macports/smart-0.52.dmg) to the PureDarwin volume using a Mac.
Alternatively, mount the (uncompressed) smart.dmg on the PureDarwin system and install it with

<span style="font-family:courier new;font-size:12px">
</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">cd / ; find /Volumes/smart*/smart-*.mpkg/Contents/Packages/*.pkg/Contents/Archive.pax.gz </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">-print -exec pax -z -f {} ;</span></span>
<span style="font-family:courier new;font-size:12px">
</span>
(not recommended for end users).

Smart and its dependencies need both Python 2.4 (comes with smart.mpkg) and Python 2.5 (is expected to come with the base system, but is missing from Darwin and hence needs to be installed from MacPorts). <span style="font-weight:bold"><span style="color:rgb(255,0,0)">To be fixed</span></span>
### Setting up smart
Future versions of PureDarwin might come with smart preconfigured.
Until that is true, do the following to set up the PureDarwin repository:


<span style="font-family:courier new;font-size:12px"></span>
PYTHONPATH=/opt/local/lib/python2.5/site-packages/smart/backends/:
/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH 
/opt/local/bin/python2.4 /opt/local/bin/smart 
channel --add  PureDarwin type=rpm-md baseurl=http://xref.puredarwin.org/macports/RPMS/i386/

<span style="font-family:courier new;font-size:12px">
</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">PYTHONPATH=/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH /opt/local/bin/python2.4 /opt/local/bin/smart update</span></span>
<span style="font-family:courier new;font-size:12px">
</span>
<span style="font-family:courier new;font-size:12px"><span style="color:rgb(255,0,0)">(...)</span></span>
<span style="font-family:courier new;font-size:12px"></span>
<span style="color:rgb(255,0,0)">Alias: PureDarwin</span>
<span style="color:rgb(255,0,0)">Type: rpm-md</span>
<span style="color:rgb(255,0,0)">Base URL: http://xref.puredarwin.org/macports/RPMS/i386/</span>
<span style="color:rgb(255,0,0)">
</span>
<span style="color:rgb(255,0,0)">Include this channel? (y/N): y</span>
<span style="color:rgb(255,0,0)">
</span>
<span style="color:rgb(255,0,0)">/opt/local/lib/python2.5/site-packages/smart/backends/rpm/rpmver.py:114: RuntimeWarning: Python C API version mismatch for module crpmver: <span style="font-weight:bold">This Python has API version 1012, module crpmver has version 1013.</span></span>
<span style="color:rgb(255,0,0)">  from crpmver import *</span>
<span style="color:rgb(255,0,0)"><span style="font-weight:bold">error: Unable to create channel of type 'rpm_md'  </span>  </span>

<span style="color:rgb(255,0,0)">
</span>
<span><span style="color:rgb(255,0,0)">When we use Python 2.5 it's the other way around:</span></span>
<span style="color:rgb(255,0,0)">
</span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)">/opt/local/lib/python2.5/site-packages/smart/backends/rpm/base.py:25: RuntimeWarning: Python C API version mismatch for module zlib: <span style="font-weight:bold">This Python has API version 1013, module zlib has version 1012.</span></span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)">  import zlib</span></span></span>
<span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="font-weight:bold"><span style="color:rgb(255,0,0)">error: Unable to create channel of type 'rpm_md'    </span></span><span style="color:rgb(255,0,0)"> </span></span></span></span>
<span style="color:rgb(255,0,0)">
</span>
<span><span style="color:rgb(255,0,0)">Note that this needs a working network, which is not yet in PureDarwin. Hence this should work in a chroot only, but even there it doesn't...</span></span><span style="color:rgb(255,0,0)"> How to fix this?</span>
### Using smart
What follows are the most commonly used operations in smart. See <span style="font-family:courier new,monospace"><span style="font-size:small">smart --help</span></span> for more information.
Currently smart must be invoked with

<span style="font-family:courier new,monospace"><span style="font-size:small">PYTHONPATH=/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH /opt/local/bin/python2.4 /opt/local/bin/smart</span></span>
<span style="color:rgb(255,0,0)">
</span>
<span style="color:rgb(255,0,0)">This needs to be fixed.</span>
#### Installing a package
To install vim:

<span style="font-family:courier new,monospace"><span style="font-size:small">PYTHONPATH=/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH /opt/local/bin/python2.4 /opt/local/bin/smart install vim</span></span>

vim should now be installed in /opt/local/bin/vim.
#### Removing a package
To remove vim:

<span style="font-family:courier new,monospace"><span style="font-size:small">PYTHONPATH=/opt/local/lib/python2.4/site-packages/:/opt/local/lib/python2.5/site-packages/:$PYTHONPATH /opt/local/bin/python2.4 /opt/local/bin/smart remove vim</span></span>
### References
[Smart homepage](http://labix.org/smart)
