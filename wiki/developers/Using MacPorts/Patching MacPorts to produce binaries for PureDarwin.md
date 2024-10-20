Patching MacPorts to produce binaries for PureDarwin
====================================================
<div style="margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px;display:inline;float:right">
![](/img/developers/macports/macports-logo-top.png)
[MacPorts](http://www.macports.org/), formerly known as DarwinPorts, is a variant of the BSD ports system for Darwin and Mac OS X.

Since the focus of the MacPorts project has shifted away from Darwin toward Mac OS X lately, it may be necessary create some patches in order to be able to use MacPorts-built software on PureDarwin.

You can check [here](https://trac.macports.org/query?status=assigned&status=closed&status=new&status=reopened&order=priority&col=id&col=summary&col=status&col=type&col=priority&col=milestone&col=component&keywords=%7Epuredarwin) which ports already have (or should have) puredarwin variants.
This page describes how to create such patches.


### Making a +puredarwin variant
Some software in MacPorts compiles in a way that makes the binaries depend on proprietary, closed-source libraries and frameworks, such as Carbon.framework, CoreServices.framework, and others. Strangely, this sometimes is even the case for open source software that originally comes from other operating systems where these frameworks and libraries don't even exist, such as FreeBSD.

Since the proprietary, closed-source libraries and frameworks are not part of Darwin, it is necessary to patch the portfiles for such projects, as will be shown on this page.
### Case study: vim
#### Problem statement
**Note that the following is example somewhat theoretical since a +puredarwin variant has been committed to the vim portfile after this article was written.**

If as usual, you compile vim in MacPorts, the resulting binary will look like this:


`otool -L /opt/local/bin/vim`
`/opt/local/bin/vim:`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)`
 `/opt/local/lib/libncurses.5.dylib (compatibility version 5.0.0, current version 5.0.0)`
 `/opt/local/lib/libiconv.2.dylib (compatibility version 7.0.0, current version 7.0.0)`
 `/System/Library/Frameworks/Carbon.framework/Versions/A/Carbon (compatibility version 2.0.0, current version 136.0.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
 `/System/Library/Frameworks/CoreServices.framework/Versions/A/CoreServices (compatibility version 1.0.0, current version 32.0.0)`
 `/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.15.0)`


The dependencies marked red are not part of Darwin and should not really be necessary for vim. So we need to change the portfile in a way that MacPorts can compile vim without these dependencies. It has been said, "*in a way*", implicitly meaning that there are many ways depending the case.
#### Finding out how to disable the proprietary libraries and frameworks
Execute these commands:

`port info vim # look at the description, variants and dependencies`
`port cat vim # look at the portfile raw content`
port extract vim # extract the original source
`port patch vim # appply MacPorts patches`

`cd $(port work vim) # go to working directory`
 

Let's search the configure files there for mentions of Carbon (which is the first of the proprietary frameworks in the otool output above):

`grep -r Carbon . | grep configure`
<span style="font-family:courier new;font-size:12px">
 </span>
There we have it, lots of Carbon mentions.
In the same way, you can grep *config.log* if it exists.

In *vim72/src/auto/configure*, we see:
<span style="font-family:courier new;font-size:12px">
 </span>
enable_carbon_check
<span style="font-family:courier new;font-size:12px">
 </span>
In order to find what should be disable, we're looking configuration options manually (old dead-listing method, line by line).

`./configure --help`

This option seems interesting:


`[...]`
` --disable-darwin Disable Darwin (Mac OS X) support.`
`[...]`


Now, before editing the portfile, we first compile manually to see if the next result of otool will be clean, or not.
You can also add more options, reflecting variants you will use too.

`./configure --prefix=/opt/local --disable-darwin ...`

Then...

`make`

The result is clean:


`./src/vim:`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)`
 `/opt/local/lib/libncurses.5.dylib (compatibility version 5.0.0, current version 5.0.0)`
 `/opt/local/lib/libiconv.2.dylib (compatibility version 7.0.0, current version 7.0.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`

#### Editing the portfile
Now we can edit the portfile and add +puredarwin platform (a variant alias) with relevant options.
First, copy the portfile:

`cp $(port file vim) $(port file vim).orig`

Second, remember to backup your alternate portfile, cause a `port selfupdate` will make you lose your modifications.

`port edit vim`

Then just above the first variant declaration, add:


`platform puredarwin {`
` configure.args-append --disable-darwin`
`}`


This case is really simple, it just needs a missing option. Sometimes you will have to use `configure.args-delete` in order to also remove options.

The modifications are automatically reflected in description:


`port info vim`
``

The modifications are also reflected in the final binary:


`port install vim **-macosx **+**puredarwin** +tiny`
`Portfile changed since last build; discarding previous state.`

`---> Fetching vim`
`[...]`

`---> Cleaning vim`

__Note:__ You have probably noticed that `-macosx` has been added, it's because of MacPorts nature which autodetects the host and adds corresponding platform/variant implicitly. Since we tend to avoid link to proprietary frameworks and other problematic dependencies.
#### Testing the modifications
Paranoid behavior makes we look again to the installed vim, it's a success.


`otool -L /opt/local/bin/vim`

`/opt/local/bin/vim:`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)`
 `/opt/local/lib/libncurses.5.dylib (compatibility version 5.0.0, current version 5.0.0)`
 `/opt/local/lib/libiconv.2.dylib (compatibility version 7.0.0, current version 7.0.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`

The goal has been reached.
#### Creating and submitting a patch to MacPorts
Create a patch to be submitted to MacPorts:

`export P=vim ; diff -u $(port file $P).orig $(port file $P) > Portfile-$P.diff`


Check at

https://trac.macports.org/query?status=assigned&status=closed&status=new&status=reopened&order=priority&col=id&col=summary&col=status&col=type&col=priority&col=milestone&col=component&port=**vim**

whether a ticket for that port already exists that matches the topic of your patch. If not, create a new ticket at <https://trac.macports.org/newticket> - suggested values (copy and paste, but replace "packagename" and "version" with the real values):
**Short Summary:** packagename-version puredarwin variant
**Full Description:** Patch to include a +puredarwin variant so that the resulting binary can run on [http://www.puredarwin.org/ PureDarwin], where proprietary frameworks and libraries are not available
**Type:** enhancement
**Milestone:** Port Enhancements
**Version: **(leave as is)
-   **Cc:** probono(puredarwin.org), aladin(puredarwin.org) (do not cc yourself)
**Priority:** Normal
**Component:** ports
**Keywords:** packagename, puredarwin, haspatch
**Port:** packagename


### Case study: freetype
`cp $(port file freetype) $(port file freetype).orig`
`port edit freetype`
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
`platform puredarwin {`
` configure.args-delete --with-old-mac-fonts`
` configure.args-append --without-ats`
`}`
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
`port info freetype`
<span style="font-family:courier new;font-size:12px">
 </span>
port clean --all freetype
port -f destroot freetype +puredarwin
`port rpm freetype +puredarwin`

 
sh-3.2# port deactivate freetype
---&gt; Deactivating freetype
sh-3.2# port activate freetype @2.3.7_1+puredarwin
---&gt; Activating freetype 2.3.7_1+puredarwin
sh-3.2# port installed freetype
The following ports are currently installed:
freetype @2.3.7_1
freetype @2.3.7_1+puredarwin (active)

<span style="font-family:courier new;font-size:12px">
 </span>
diff -u $(port file freetype).orig $(port file freetype) > Portfile-freetype.diff
### Case study: glib2 {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:18px;margin-top:10px;margin-bottom:10px;margin-left:10px;margin-right:0px"}
This case is a bit more complicated, since we need to patch configure.in if the +puredarwin variant is selected.

`cd $(port work glib2)/glib-*/`
`cp configure.in configure.in.orig`
<span style="font-family:courier new;font-size:12px">
 </span>
`nano configure.in`
`# delete Carbon-related portions`
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
`diff -u configure.in.orig configure.in > $(port dir glib2)/files/patch-configure.in.diff`
`cd -`
`cp $(port file glib2) $(port file glib2).orig`
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
`port edit glib2`
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
# add
`platform puredarwin {`
` patchfiles-append patch-configure.in.diff `
`}`
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
`diff -u $(port file glib2).orig $(port file glib2) > Portfile-glib2.diff`



__Note:__ Carbon has been explicitly added in 2007 to *configure.in* file as we can read in the *Changelog* file.

 `* configure.in: Add Carbon checks.`

Another way is to directly edit *configure* file.
At lines 4290 and 4291, comment or remove the problematic header includes:


`#include <Carbon/Carbon.h>`
`#include <CoreServices/CoreServices.h>`

From line 4722 to 4729, you can comment all the block, or alternatively define HAVE_CARBON to 0 and remove -framework Carbon.


`if test "x$glib_have_carbon" = "xyes"; then`
`
`
`cat >>confdefs.h <<_ACEOF`
`#define HAVE_CARBON 1`
`_ACEOF`
`
`
`  LDFLAGS="$LDFLAGS -framework Carbon"`
`fi`


__Note:__ It hasn't been tested and doesn't appear to be needed for "purity" purpose (since it's worked with instructions just above), but other occurrences has been found:
Line 4311:


`  glib_have_carbon=yes`


From line 4356:


` if test "$glib_have_carbon" = "yes"; then`
`  OS_CARBON_TRUE=`
`  OS_CARBON_FALSE='#'`
`else`
`  OS_CARBON_TRUE='#'`
`  OS_CARBON_FALSE=`
`fi`
### To do
Expand the otool check so that it can be included in MacPorts as a "purity tester" (i.e., check that anything that comes out of MacPorts is free from links to proprietary, closed-source libraries and frameworks).

**References**

[MacPorts Guide](http://guide.macports.org/)

