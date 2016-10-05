Upgrading a port
================
![](../../_/rsrc/1222694606788/developers/macports/macports-logo-top.png)[MacPorts](http://www.macports.org/), formerly known as DarwinPorts, is a variant of the BSD ports system for Darwin and Mac OS X.
This page describes how to upgrade a port in MacPorts to a later version of the respective software.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Case example](upgrading-a-port.html#TOC-Case-example)
    1.  [**1.1** Downloading latest upstream source](upgrading-a-port.html#TOC-Downloading-latest-upstream-source)
    2.  [**1.2** Calculating md5](upgrading-a-port.html#TOC-Calculating-md5)
    3.  [**1.3** Editing the portfile](upgrading-a-port.html#TOC-Editing-the-portfile)
    4.  [**1.4** Creating the patch](upgrading-a-port.html#TOC-Creating-the-patch)
    5.  [**1.5** Testing the patched portfile](upgrading-a-port.html#TOC-Testing-the-patched-portfile)
    6.  [**1.6** Activating the new version](upgrading-a-port.html#TOC-Activating-the-new-version)
    7.  [**1.7** Submitting the patch to MacPorts](upgrading-a-port.html#TOC-Submitting-the-patch-to-MacPorts)


### Case example
In this example, we update the portfile for gnustep-base. This is just an example.
#### Downloading latest upstream source
To find out the URL where the upstream source is located, do:

<span style="font-family:courier new;font-size:12px">
</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">port cat gnustep-base </span></span>

Check whether a newer version is available at that download location and download it, in this case gnustep-base-1.16.3.tar.gz
#### Calculating md5
Calculate the md5 checksum of the upstream source with

<span style="font-family:courier new,monospace"><span style="font-size:small">md5 gnustep-base-1.16.3.tar.gz </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">MD5 (gnustep-base-1.16.3.tar.gz) = 32ae302922a0a6e14c7008a105014bba</span></span>
#### Editing the portfile
Copy the portfile first so that we can create a patch later:

<span style="font-family:courier new,monospace"><span style="font-size:small">cp $(port file gnustep-base) $(port file gnustep-base).orig</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">port edit gnustep-base</span></span>

Change version to 1.16.3
Change md5 to the value calculated before
#### Creating the patch
<span style="font-family:courier new,monospace"><span style="font-size:small">diff -u $(port file gnustep-base).orig $(port file gnustep-base) &gt; gnustep-base.patch</span></span>
#### Testing the patched portfile
Now build it with

<span style="font-family:courier new,monospace"><span style="font-size:small">port rpm gnustep-base</span></span>
#### Activating the new version
In order to activate the new version so that it is used when builting additional software, you need to do in addition:

<span style="font-family:courier new,monospace"><span style="font-size:small">port archive gnustep-base</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">port upgrade -n gnustep-base</span></span>

<span style="font-family:courier new;font-size:12px"><span style="font-family:Arial;font-size:13px">Finally, check that your activated version is really the new one with</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">port installed gnustep-base</span></span>
#### Submitting the patch to MacPorts
Search whether a ticket already exists, if not submit a new one with the patch attached.
