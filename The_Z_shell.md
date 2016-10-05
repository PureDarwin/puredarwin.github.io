The Z shell
===========
<div style="margin:5px 10px;display:inline;float:right">
[![](../_/rsrc/1223242963057/users/zsh/wizard.gif)](zsh/wizard.gif%3Fattredirects=0)
This page is about using zsh on PureDarwin system.
Normally, PureDarwin comes with the bash shell which most users will be familiar with.
Some users might prefer to use zsh however. This page is a work in progress, please feel free to contribute.

<div class="sites-embed-align-left-wrapping-off">
<div class="sites-embed-border-off sites-embed" style="width:250px;">
<div class="sites-embed-content sites-embed-type-toc">
<div class="goog-toc sites-embed-toc-maxdepth-6">
Contents
1.  [**1** Availability](zsh.html#TOC-Availability)
    1.  [**1.1** In PureDarwin](zsh.html#TOC-In-PureDarwin)
    2.  [**1.2** In the DarwinBuild project](zsh.html#TOC-In-the-DarwinBuild-project)
    3.  [**1.3** In the MacPorts project](zsh.html#TOC-In-the-MacPorts-project)
2.  [**2** Changing an user's default shell](zsh.html#TOC-Changing-an-user-s-default-shell)
3.  [**3** zshrc](zsh.html#TOC-zshrc)
4.  [**4** Resources](zsh.html#TOC-Resources)

### Availability
#### In PureDarwin
Available.
#### In the DarwinBuild project
Available.
See the [DarwinBuild](../developers/darwinbuild.html) page on how to compile a project if needed.
#### In the MacPorts project
Available.
Take a look at [Using the MacPorts project](../developers/macports.1.html) page for more information about MacPorts if you don't know how to build it.


<span style="text-decoration:underline">Note:</span> You should also take a look in the available variants (you can use <span style="font-family:courier new,monospace"><span style="font-size:small">port info zsh</span></span> or <span style="font-family:courier new,monospace"><span style="font-size:small">port variants zsh</span></span> if you want to know the description associated to the respective variant).
The zsh port appears to be "[pure](../developers/macports/purity.html)" as shown below.

[![](../_/rsrc/1224017323026/users/zsh/pd_portviz%20zsh_directed.png%3Fheight=200&width=143)](zsh/pd_portviz%20zsh_directed.png%3Fattredirects=0)

### Changing an user's default shell
To use zsh as the default shell of the currently logged-in user, do

<span style="font-size:small">chsh -s /bin/zsh</span>

To revert back to bash, do 

<span style="font-size:small">chsh -s /bin/bash</span>
### zshrc
Populate your ~/.zshrc (or /etc/zshrc) with:


<span style="font-family:courier new,monospace"><span style="font-size:small">export PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/usr/libexec:/System/Library/CoreServices</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">export PATH=/opt/local/bin:/opt/local/sbin:$PATH</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">export PATH=/usr/X11R6/bin:$PATH</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">export EDITOR=/usr/bin/vi</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">alias ll='ls -lh'</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">PS1='%n@%m:%~%# '</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">TERM='vt100'</span></span>
<span style="font-family:courier new,monospace"><span style="font-size:small">bindkey -e</span></span>
<div style="font-family:arial,sans-serif">
-   Some <span style="font-size:small">PATH</span> could be optional, depending the flavor.
-   <span style="font-size:12px">PS1 </span>sets the prompt like <span style="font-size:small">user@PureDarwin:~%</span> in your home dir and <span style="font-size:12px">user@PureDarwin:/tmp% <span style="font-size:13px">in the well-known temporary folder.</span></span>
-   <span style="font-size:12px">TERM</span> variable could be 'ansi' or per example 'xterm-color'.
-   the <span style="font-size:12px">bindkey -e</span> command allows you to use emac style for ^A, ^E, and ^D shortcut (how paradoxal since the EDITOR is vi? ;)).
<div style="font-family:arial,sans-serif">
<span style="text-decoration:underline">Note</span>: zsh is the only shell we know that it is able to run in interactive mode without (or with a broken) standard input.
### Resources {style="font-family:arial,sans-serif"}
<div style="font-family:arial,sans-serif">
<http://www.zsh.org/>
<div style="font-family:arial,sans-serif">
<http://zsh.dotsrc.org/> (mirror: <http://zsh.sourceforge.net/> )
<div style="font-family:arial,sans-serif">

<div style="font-family:arial,sans-serif">
<http://en.wikipedia.org/wiki/Zsh> 
