Patching MacPorts to produce binaries for PureDarwin
====================================================
<div style="margin-top:5px;margin-right:10px;margin-bottom:5px;margin-left:10px;display:inline;float:right">
[![](../../_/rsrc/1222694606788/developers/macports/macports-logo-top.png)](http://sites.google.com/a/puredarwin.org/puredarwin/developers/goog_1222698405894)
[MacPorts](http://www.macports.org/), formerly known as DarwinPorts, is a variant of the BSD ports system for Darwin and Mac OS X.

Since the focus of the MacPorts project has shifted away from Darwin toward Mac OS X lately, it may be necessary create some patches in order to be able to use MacPorts-built software on PureDarwin.

You can check [here](https://trac.macports.org/query?status=assigned&status=closed&status=new&status=reopened&order=priority&col=id&col=summary&col=status&col=type&col=priority&col=milestone&col=component&keywords=%7Epuredarwin) which ports already have (or should have) puredarwin variants.
 This page describes how to create such patches.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:430px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Making a +puredarwin variant](patching.html#TOC-Making-a-puredarwin-variant)
2.  [**2** Case study: vim](patching.html#TOC-Case-study:-vim)
    1.  [**2.1** Problem statement](patching.html#TOC-Problem-statement)
    2.  [**2.2** Finding out how to disable the proprietary libraries and frameworks](patching.html#TOC-Finding-out-how-to-disable-the-proprietary-libraries-and-frameworks)
    3.  [**2.3** Editing the portfile](patching.html#TOC-Editing-the-portfile)
    4.  [**2.4** Testing the modifications](patching.html#TOC-Testing-the-modifications)
    5.  [**2.5** Creating and submitting a patch to MacPorts](patching.html#TOC-Creating-and-submitting-a-patch-to-MacPorts)
3.  [**3** Case study: freetype](patching.html#TOC-Case-study:-freetype)
4.  [**4** Case study: glib2](patching.html#TOC-Case-study:-glib2)
5.  [**5** To do](patching.html#TOC-To-do)


### Making a +puredarwin variant
Some software in MacPorts compiles in a way that makes the binaries depend on proprietary, closed-source libraries and frameworks, such as Carbon.framework, CoreServices.framework, and others. Strangely, this sometimes is even the case for open source software that originally comes from other operating systems where these frameworks and libraries don't even exist, such as FreeBSD.

Since the proprietary, closed-source libraries and frameworks are not part of Darwin, it is necessary to patch the portfiles for such projects, as will be shown on this page.
### Case study: vim
#### Problem statement
<span style="font-weight:bold">Note that the following is example somewhat theoretical since a +puredarwin variant has been committed to the vim portfile after this article was written.</span>

If as usual, you compile vim in MacPorts, the resulting binary will look like this:


<span style="font-family:courier new,monospace"><span style="font-size:small">otool -L /opt/local/bin/vim</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/opt/local/bin/vim:</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/opt/local/lib/libncurses.5.dylib (compatibility version 5.0.0, current version 5.0.0)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/opt/local/lib/libiconv.2.dylib (compatibility version 7.0.0, current version 7.0.0)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)">/System/Library/Frameworks/Carbon.framework/Versions/A/Carbon (compatibility version 2.0.0, current version 136.0.0)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)">/System/Library/Frameworks/CoreServices.framework/Versions/A/CoreServices (compatibility version 1.0.0, current version 32.0.0)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(255,0,0)">/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.15.0)</span></span></span>


The dependencies marked red are not part of Darwin and should not really be necessary for vim. So we need to change the portfile in a way that MacPorts can compile vim without these dependencies. It has been said, "<span style="font-style:italic">in a way</span>", implicitly meaning that there are many ways depending the case.
#### Finding out how to disable the proprietary libraries and frameworks
Execute these commands:

<span style="font-family:courier new,monospace"><span style="font-size:small">port info vim # look at the description, variants and dependencies</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">port cat vim # look at the portfile raw content</span></span>
<span style="font-family:courier new;font-size:12px">port extract vim # extract the original source</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">port patch vim # appply MacPorts patches</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small">cd $(port work vim) # go to working directory</span></span>
<span style="font-family:courier new;font-size:12px"><span style="font-family:Arial;font-size:13px"> </span></span>

Let's search the configure files there for mentions of Carbon (which is the first of the proprietary frameworks in the otool output above):

<span style="font-family:courier new,monospace"><span style="font-size:small">grep -r Carbon . | grep configure</span></span>
<span style="font-family:courier new;font-size:12px">
 </span>
There we have it, lots of Carbon mentions.
In the same way, you can grep <span style="font-style:italic">config.log</span> if it exists.

In <span style="font-style:italic">vim72/src/auto/configure</span>, we see:
<span style="font-family:courier new;font-size:12px">
 </span>
<span style="font-family:courier new;font-size:12px">enable_carbon_check</span>
<span style="font-family:courier new;font-size:12px">
 </span>
In order to find what should be disable, we're looking configuration options manually (old dead-listing method, line by line).

<span style="font-family:courier new,monospace"><span style="font-size:small">./configure --help</span></span>

This option seems interesting:


<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> --disable-darwin Disable Darwin (Mac OS X) support.</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">[...]</span></span>


Now, before editing the portfile, we first compile manually to see if the next result of otool will be clean, or not.
You can also add more options, reflecting variants you will use too.

<span style="font-family:courier new,monospace"><span style="font-size:small">./configure --prefix=/opt/local --disable-darwin ...</span></span>

Then...

<span style="font-family:courier new,monospace"><span style="font-size:small">make</span></span>

The result is clean:


<span style="font-family:courier new,monospace"><span style="font-size:small">./src/vim:</span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/opt/local/lib/libncurses.5.dylib (compatibility version 5.0.0, current version 5.0.0)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/opt/local/lib/libiconv.2.dylib (compatibility version 7.0.0, current version 7.0.0)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)</span></span></span>

#### Editing the portfile
Now we can edit the portfile and add +puredarwin platform (a variant alias) with relevant options.
First, copy the portfile:

<span style="font-family:courier new,monospace"><span style="font-size:small">cp $(port file vim) $(port file vim).orig</span></span>

Second, remember to backup your alternate portfile, cause a <span style="font-family:courier new,monospace"><span style="font-size:small">port selfupdate</span></span> will make you lose your modifications.

<span style="font-family:courier new,monospace"><span style="font-size:small">port edit vim</span></span>

Then just above the first variant declaration, add:


<span style="font-family:courier new,monospace"><span style="font-size:small">platform puredarwin {</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> configure.args-append --disable-darwin</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">}</span></span>


This case is really simple, it just needs a missing option. Sometimes you will have to use <span style="font-family:courier new,monospace"><span style="font-size:small">configure.args-delete</span></span> in order to also remove options.

The modifications are automatically reflected in description:


<span style="font-family:courier new,monospace"><span style="font-size:small">port info vim</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">vim 7.2.021, editors/vim (Variants: universal, <span style="font-weight:bold">puredarwin</span>, athena, gtk1, gtk2, motif, tiny, small, big, huge, xim, perl, python, ruby, tcl, cscope, nls)</span></span>

The modifications are also reflected in the final binary:


<span style="font-family:courier new,monospace"><span style="font-size:small">port install vim <span style="font-weight:bold">-macosx </span><span><span style="font-weight:bold">+</span></span><span style="font-weight:bold">puredarwin</span> +tiny</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">Portfile changed since last build; discarding previous state.</span></span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">---&gt; Fetching vim</span></span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">[...]</span></span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">---&gt; Cleaning vim</span></span></span>

<span style="text-decoration:underline">Note:</span> You have probably noticed that <span style="font-family:courier new,monospace"><span style="font-size:small">-macosx</span></span> has been added, it's because of MacPorts nature which autodetects the host and adds corresponding platform/variant implicitly. Since we tend to avoid link to proprietary frameworks and other problematic dependencies.
#### Testing the modifications
Paranoid behavior makes we look again to the installed vim, it's a success.


<span style="font-family:courier new,monospace"><span style="font-size:small">otool -L /opt/local/bin/vim</span></span>

<span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/opt/local/bin/vim:</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/opt/local/lib/libncurses.5.dylib (compatibility version 5.0.0, current version 5.0.0)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/opt/local/lib/libiconv.2.dylib (compatibility version 7.0.0, current version 7.0.0)</span></span></span>
<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)"> </span></span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(68,68,68)">/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)</span></span></span>

The goal has been reached.
#### Creating and submitting a patch to MacPorts
Create a patch to be submitted to MacPorts:

<span style="font-family:courier new,monospace"><span style="font-size:small">export P=vim ; diff -u $(port file $P).orig $(port file $P) &gt; Portfile-$P.diff</span></span>


Check at

https://trac.macports.org/query?status=assigned&status=closed&status=new&status=reopened&order=priority&col=id&col=summary&col=status&col=type&col=priority&col=milestone&col=component&port=<span style="font-weight:bold">vim</span>

whether a ticket for that port already exists that matches the topic of your patch. If not, create a new ticket at <https://trac.macports.org/newticket> - suggested values (copy and paste, but replace "packagename" and "version" with the real values):
<span style="font-weight:bold">Short Summary:</span> <span style="color:rgb(153,0,0)">packagename-version</span> puredarwin variant
<span style="font-weight:bold">Full Description:</span> Patch to include a +puredarwin variant so that the resulting binary can run on [http://www.puredarwin.org/ PureDarwin], where proprietary frameworks and libraries are not available
<span style="font-weight:bold">Type:</span> enhancement
<span style="font-weight:bold">Milestone:</span> Port Enhancements
<span style="font-weight:bold">Version: </span>(leave as is)
-   <span style="font-weight:bold">Cc:</span><span> <span style="color:rgb(153,0,0)">(the port maintainer)</span>,</span> probono(puredarwin.org), aladin(puredarwin.org) <span style="color:rgb(153,0,0)">(do not cc yourself)</span>
<span style="font-weight:bold">Priority:</span> Normal
<span style="font-weight:bold">Component:</span> ports
<span style="font-weight:bold">Keywords:</span> <span style="color:rgb(153,0,0)">packagename</span>, puredarwin, haspatch
<span style="font-weight:bold">Port:</span> <span style="color:rgb(153,0,0)">packagename</span>


### Case study: freetype
<span style="font-family:courier new,monospace"><span style="font-size:small">cp $(port file freetype) $(port file freetype).orig</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">port edit freetype</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">platform puredarwin {</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> configure.args-delete --with-old-mac-fonts</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> configure.args-append --without-ats</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">}</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">port info freetype</span></span>
<span style="font-family:courier new;font-size:12px">
 </span>
<span style="font-family:courier new;font-size:12px">port clean --all freetype</span>
<span style="font-family:courier new;font-size:12px">port -f destroot freetype +puredarwin</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">port rpm freetype +puredarwin</span></span>

<span style="font-family:courier new;font-size:12px"> </span>
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
<span style="font-family:courier new;font-size:12px">diff -u $(port file freetype).orig $(port file freetype) &gt; Portfile-freetype.diff</span>
### Case study: glib2 {style="background-color:transparent;color:rgb(0,0,0);font-family:Arial,Verdana,sans-serif;font-size:18px;margin-top:10px;margin-bottom:10px;margin-left:10px;margin-right:0px"}
This case is a bit more complicated, since we need to patch configure.in if the +puredarwin variant is selected.

<span style="font-family:courier new,monospace"><span style="font-size:small">cd $(port work glib2)/glib-*/</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">cp configure.in configure.in.orig</span></span>
<span style="font-family:courier new;font-size:12px">
 </span>
<span style="font-family:courier new,monospace"><span style="font-size:small">nano configure.in</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"># delete Carbon-related portions</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">diff -u configure.in.orig configure.in &gt; $(port dir glib2)/files/patch-configure.in.diff</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">cd -</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">cp $(port file glib2) $(port file glib2).orig</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">port edit glib2</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new;font-size:12px"># add</span>
<span style="font-family:courier new,monospace"><span style="font-size:small">platform puredarwin {</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small"> patchfiles-append patch-configure.in.diff </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">}</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
 </span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">diff -u $(port file glib2).orig $(port file glib2) &gt; Portfile-glib2.diff</span></span>
<span style="font-family:courier new;font-size:12px">
</span>

<span style="text-decoration:underline">Note:</span> Carbon has been explicitly added in 2007 to <span style="font-style:italic">configure.in</span> file as we can read in the <span style="font-style:italic">Changelog</span> file.

<span style="white-space:pre"><span style="font-family:courier new,monospace"><span style="font-size:small"> </span></span></span><span style="font-family:courier new,monospace"><span style="font-size:small">* configure.in: Add Carbon checks.</span></span>

Another way is to directly edit <span style="font-style:italic">configure</span> file.
At lines 4290 and 4291, comment or remove the problematic header includes:


<span style="font-family:courier new,monospace"><span style="font-size:small">#include &lt;Carbon/Carbon.h&gt;</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">#include &lt;CoreServices/CoreServices.h&gt;</span></span>

From line 4722 to 4729, you can comment all the block, or alternatively define HAVE_CARBON to 0 and remove -framework Carbon.


<span style="font-family:courier new,monospace"><span style="font-size:small">if test "x$glib_have_carbon" = "xyes"; then</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">cat &gt;&gt;confdefs.h &lt;&lt;_ACEOF</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">#define HAVE_CARBON 1</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">_ACEOF</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">
</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  LDFLAGS="$LDFLAGS -framework Carbon"</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">fi</span></span>


<span style="text-decoration:underline">Note:</span> It hasn't been tested and doesn't appear to be needed for "purity" purpose (since it's worked with instructions just above), but other occurrences has been found:
Line 4311:


<span style="font-family:courier new,monospace"><span style="font-size:small">  glib_have_carbon=yes</span></span>
<span style="font-family:courier new;font-size:12px">
</span>
From line 4356:


<span style="font-family:courier new,monospace"><span style="font-size:small"> if test "$glib_have_carbon" = "yes"; then</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  OS_CARBON_TRUE=</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  OS_CARBON_FALSE='#'</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">else</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  OS_CARBON_TRUE='#'</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">  OS_CARBON_FALSE=</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">fi</span></span>
### To do
Expand the otool check so that it can be included in MacPorts as a "purity tester" (i.e., check that anything that comes out of MacPorts is free from links to proprietary, closed-source libraries and frameworks).

<span style="font-size:18px;font-weight:bold">References</span>

[MacPorts Guide](http://guide.macports.org/)

