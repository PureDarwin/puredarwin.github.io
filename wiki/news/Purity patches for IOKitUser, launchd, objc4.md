# "Purity" patches for IOKitUser, launchd, objc4

Darwin community, as you might have experienced, the current published sources of some Darwin 9 projects, including such essential ones as IOKitUser, launchd, objc4 currently have build- or runtime dependencies on projects that are not part of Darwin. 

It looks like patching the respective sources to remove the non-Darwin dependencies is the most pragmatic approach at this time. Hence, Aladin from the PureDarwin project has made available a series of patches.

Read the full post on the **darwin-dev** mailing list at http://lists.apple.com/archives/darwin-dev//2008/Oct/msg00132.html
