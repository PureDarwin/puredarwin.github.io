Upgrading a port
================
![](../../_/rsrc/1222694606788/developers/macports/macports-logo-top.png)[MacPorts](http://www.macports.org/), formerly known as DarwinPorts, is a variant of the BSD ports system for Darwin and Mac OS X.
This page describes how to upgrade a port in MacPorts to a later version of the respective software.

### Case example
In this example, we update the portfile for gnustep-base. This is just an example.
#### Downloading latest upstream source
To find out the URL where the upstream source is located, do:



`port cat gnustep-base `

Check whether a newer version is available at that download location and download it, in this case gnustep-base-1.16.3.tar.gz
#### Calculating md5
Calculate the md5 checksum of the upstream source with

`md5 gnustep-base-1.16.3.tar.gz `
`MD5 (gnustep-base-1.16.3.tar.gz) = 32ae302922a0a6e14c7008a105014bba`
#### Editing the portfile
Copy the portfile first so that we can create a patch later:

`cp $(port file gnustep-base) $(port file gnustep-base).orig`
`port edit gnustep-base`

Change version to 1.16.3
Change md5 to the value calculated before
#### Creating the patch
`diff -u $(port file gnustep-base).orig $(port file gnustep-base) > gnustep-base.patch`
#### Testing the patched portfile
Now build it with

`port rpm gnustep-base`
#### Activating the new version
In order to activate the new version so that it is used when builting additional software, you need to do in addition:

`port archive gnustep-base`
`port upgrade -n gnustep-base`

Finally, check that your activated version is really the new one with

`port installed gnustep-base`
#### Submitting the patch to MacPorts
Search whether a ticket already exists, if not submit a new one with the patch attached.
