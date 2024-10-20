Darwin 9
========
...
9L30 status
-----------
not tested.
9J61 status
-----------
### Principle
#### 1-pass
After running the so-called brutus command ``for X in $(darwinxref version '*' | cut -f 1 -d '-'); do darwinbuild $X; done`' the following projects have been successfully built, taking in account that some projects has been excluded as e.g., *xnu* (because it was already built and packaged as a test case at the beginning), but also *MySQL*, *gcc_42*, *gcc*, *BerkeleyDB*, *bind9* and *apache1* which can be built successfully at first or second pass depending the project but definitively takes too much time and space at compilation process (*gcc_42* could be soon needed too).


Let's load the projects freshly built with the following script, even if we don't need most of them.




`for Y in `ls Packages | awk -F "." '{print $1}'`; do`

`done`


#### 2-pass
Then a second pass will be made, excluding the previous built and load projects, with:

`for X in $(darwinxref version '*' | cut -f 1 -d '-'); do`
``
`  for Y in `ls Packages | awk -F "."  '{print $1}'`; do`
`  if [ "$Y" = "$X" ]; then`
`  SAME="true"`
`  break`
`  fi`
`  done`


`  if [ "$SAME" = "false" ]; then`
`                darwinbuild  $X`
`  fi`
done


What does that mean if we found a "diff" between the two passes? What can we do?
1- Some dependencies (headers and/or binaries part of one or more project) are missing. Consequently, we can at least identify the dependent(s) where at least one dependency is missing (since this dependent failed to build at 1st-pass and success at 2nd-pass).  Of course, a 3rd-pass, a 4th-path, etc.. an n-path applies to the same rules.
2- We should run a 3rd-pass on the projects which still fail if between the previous passes, some noticable differences were found. And at the end, we should still obtain more binary roots and less compilation time.
3- A quick electromagnetic solar tempest has just disappeard?

__Notes:__ from scratch, the "~&lt;build attempts&gt;" appended to the project and its version (found in "*Logs/<project>/<project>-<version>.log~<build attempts>*", but not only/necessarly here in fact) could be used in the "n-passes" process in order to know if and when the project has been successfully built previously or not. (TODO)
#### n-pass
At a certain point, projects which cannot be built "by default" will be listed if between a *pass n *and a *pass n-1* no difference has been established. Moreover, knowing that a project failed to build at the first pass or fail to build near the other extremum will help in the fixing process.
### Results (excerpt)
#### Current status
The approximative current status (not including the chaos) looks like the following:
Some projects have no sources, consequently cannot be built.
Some projects have no binaryroots but source and can easily be built.
Some projects are hard to build.

The bin column refers to the availability of an "official" binaryroot (e.g., from MacOSforge or Apple).
The src column points to the availability of an "official" source.
The logs column list (and locally points to the project logs) each build attempt (pass) and its state.

> green for exit status 0 (build succeed)
> orange for exit status 1 (fail)
> red for exit status 2 (fail)
> black when "it seems" that no src is available, so nothing can be built.
> 


  ------------------ ------------------ ------------------ ------------------
  **PROJECT**        **BIN**            **SRC**            **LOGS**
  Apple16X50Serial                                       [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") **[13](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  Apple3Com3C90x                                         **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleACPIPlatform                                      [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  AppleADBButtons                                        **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleADBKeyboard                                       **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleADBMouse                                          [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") **[2](j
                                                           avascript:void(0);
                                                            "** BUILD SUCCEED
                                                           ED **")** ^**[3](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**^
  AppleAPIC                                              [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  AppleCore99NVRAM                                       **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleDisplays                                          [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  AppleFan                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleFileSystemDri                                     [1](javascript:voi
  ver                                                      d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  AppleFlashNVRAM                                        **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleGMACEthernet                                      **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleGPIO                                              **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleHWSensor                                          [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  AppleI2C                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleI2S                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleIntel8255x                                        [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  AppleIntelPIIXATA                                      **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleK2SATA                                            **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleK2SATARoot                                        **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleKauaiATA                                          **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleKeyLargo                                          [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  AppleKeyswitch                                         [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") **[2](j
                                                           avascript:void(0);
                                                            "** BUILD SUCCEED
                                                           ED **")** ^**[3](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**^
  AppleKiwiATA                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleKiwiRoot                                          **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleMPIC                                              **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleMacRISC2PE                                        **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleMacRISC4PE                                        [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  AppleMacRiscPCI                                        **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleMediaBay                                          **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleOnboardAudio                                      [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  ApplePCCard16ATA                                       **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  ApplePCCardATA                                         **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleRAID                                              [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") ^**[7]
                                                           (javascript:void(0
                                                           ); "** BUILD SUCCE
                                                           EDED **")**^ [8](
                                                           javascript:void(0)
                                                           ; "** BUILD FAILED
                                                            **")
  AppleRS232Serial                                       [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  AppleRTC                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  AppleRTL8139Ethern                                     **[1](javascript:v
  et                                                       oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleSCCSerial                                         [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  AppleSMBIOS                                            [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  AppleSym8xx                                            **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleTalk                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[12](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**
  AppleThermal                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  AppleUSBAudio                                          [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  AppleUSBCDCDriver                                      [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  AppleUSBIrDA                                           [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  AppleVIA                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  BerkeleyDB                                             **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")**
  BootCache                                              [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") **[13](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  BootX                                                  [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  CF                                                     [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  CFNetwork                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2")
  CFOpenDirectory                                        [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  CPAN                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  CPANInternal                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  CarbonHeaders                                          **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  ChatServer                                             [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  Chess                                                  [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           )
  CommonCrypto                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  CoreOSMakefiles                                        [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  CrackLib                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  Csu                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  CyrusIMAP                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") **[14](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  DSPasswordServerFr                                     [1](javascript:voi
  amework                                                  d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  DSPasswordServerPl                                     [1](javascript:voi
  ugin                                                     d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  DSTools                                                [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  DirectoryService                                       [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           )
  DirectoryServiceDa                                     [1](javascript:voi
  emon                                                     d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **")
  DirectoryServiceMI                                     [1](javascript:voi
  G                                                        d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  DiskArbitration                                        [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  DynamicPowerStep                                       [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") **[8](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  FastCGI                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  FirewallTool                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  ICU                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  ICU_debug                                             **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  ICU_profile                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  IOACPIFamily                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  IOADBFamily                                            **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  IOATABlockStorage                                      [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  IOATAFamily                                            [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOATAPIProtocolTra                                     [1](javascript:voi
  nsport                                                   d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  IOAudioFamily                                          [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOBDStorageFamily                                      [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  IOCDStorageFamily                                      [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IODVDStorageFamily                                     [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOFWDVComponents                                       [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  IOFireWireAVC                                          [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") **[8](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  IOFireWireFamily                                       [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOFireWireIP                                           [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOFireWireSBP2                                         [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOFireWireSerialBu                                     [1](javascript:voi
  sProtocolTransport                                       d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  IOGraphics                                             [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOHIDFamily                                            [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  IOI2CFamily                                            [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOKitTools                                             [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOKitUser                                              [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") ^[
                                                           9](javascript:void
                                                           (0); "** BUILD FAI
                                                           LED **")^ [10](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [11](javascri
                                                           pt:void(0); "** BU
                                                           ILD FAILED **")
  IONetworkingFamily                                     [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  IOPCCardFamily                                         [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOPCIFamily                                            [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOSCSIArchitecture                                     [1](javascript:voi
  ModelFamily                                              d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  IOSCSIParallelFami                                     [1](javascript:voi
  ly                                                       d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  IOSerialFamily                                         [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  IOStorageFamily                                        [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  IOUSBFamily                                            [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  IOUSBMassStorageCl                                     [1](javascript:voi
  ass                                                      d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  JavaScriptCore                                         [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [15
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [16](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [17](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [18
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [19](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [20](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: ?") [21](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [22](javascri
                                                           pt:void(0); "** BU
                                                           ILD FAILED **") [
                                                           23](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [24](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *")
  JavaScriptGlue                                         [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  Kerberos                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  KerberosHelper                                         [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  KeyLargoATA                                            **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  LDAPFramework                                          [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") **[
                                                           13](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  Libc                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") [14](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [15](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [16](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: 2") [17](ja
                                                           vascript:void(0); 
                                                           "EXIT STATUS: 2")
                                                            **[18](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  Libc_debug                                            [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") **[
                                                           13](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  Libc_headers                                          [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") **[5](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  Libc_man                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") **[5](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  Libc_profile                                          [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") **[
                                                           13](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  Libcpp_kext                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  Libinfo                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  Libm                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  Libmx                                                  **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  Libnotify                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  Librpcsvc                                              **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  Libstreams                                             **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  Libsyscall                                             [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  Libsystem                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2")
  Liby                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  MacPorts                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           **[2](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")**
  MySQL                                                  
  NFS                                                    [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") **[8]
                                                           (javascript:void(0
                                                           ); "** BUILD SUCCE
                                                           EDED **")**
  NullCPUPowerManage                                     **[1](javascript:v
  ment                                                     oid(0); "** BUILD 
                                                           SUCCEEDED **")**
  OpenAL                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  OpenDirectory                                          [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  OpenLDAP                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") [14](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2")
  OpenSSH                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            **[9](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  OpenSSL                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  OpenSSL096                                             [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  PowerManagement                                        [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  PyRSS2Gen                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  RubyCocoa                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  RubyGems                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  RubyOnRails                                            [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  SCSIHeaderInstalle                                     **[1](javascript:v
  r                                                        oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  SQLite                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  Security                                               [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  SecurityTokend                                         [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  SecurityTool                                           [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  SmartCardServices                                      [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  SpamAssassin                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  SquirrelMail                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  SystemStubs                                            **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
                                                            **[3](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
                                                            **[4](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  TargetConfig                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  TargetConfig_host                                     [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  TimeZoneData                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  Tokend                                                 **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  Twisted                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  TwistedWords                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  TwistedXish                                            [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  UserNotification                                       [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  VirtualAudioDriver                                     [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  WebCore                                                [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  X11apps                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  X11fonts                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  X11libs                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  X11misc                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  X11proto                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  X11server                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  adv_cmds                                              **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  amavisd                                                **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  apache                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2")
  apache1                                                
  apache_mod_bonjo                                     [1](javascript:voi
  ur                                                       d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  apache_mod_fastc                                     [1](javascript:voi
  gi                                                       d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  apache_mod_hfs_                                     [1](javascript:voi
  apple                                                    d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  apache_mod_perl                                      [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  apache_mod_perl1                                     [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  apache_mod_php                                       [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  apache_mod_php4                                      [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  apache_mod_ssl                                       [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  apr                                                    [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  architecture                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  at_cmds                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") [14](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [15](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [16](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: 2") [17](ja
                                                           vascript:void(0); 
                                                           "EXIT STATUS: 2")
                                                            [18](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [19](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") *
                                                           *[20](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")**
  autoconf                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  autofs                                                 [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [15
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [16](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [17](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [18
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [19](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [20](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [21
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [22](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [23](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [24
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [25](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [26](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [27
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [28](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [29](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [30
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [31](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [32](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **")
  automake                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  autozone                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  awk                                                    [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  bash                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  basic_cmds                                            [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  bc                                                     [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  bind9                                                  
  bison                                                  [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  bison1                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  bless                                                  [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  bootp                                                  [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [15
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [16](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [17](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [18
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  bootstrap_cmds                                        [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  bsdmake                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  bsm                                                    [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  bzip2                                                  [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[2](javas
                                                           cript:void(0); "**
                                                            BUILD SUCCEEDED *
                                                           *")** ^**[3](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**^
  cctools                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            **[9](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  cctools_ofiles                                        [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            **[9](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  cddafs                                                 [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") **[8](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  clamav                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  configd                                                [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  configd_executabl                                     [1](javascript:voi
  es                                                       d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  configd_plugins                                       [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [14](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           15](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : ?") [16](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [17](javascript:v
                                                           oid(0); "** BUILD 
                                                           FAILED **") [18](
                                                           javascript:void(0)
                                                           ; "** BUILD FAILED
                                                            **") [19](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [20](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [21](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           )
  copyfile                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2")
  cron                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  crontabs                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  cscope                                                 **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  cups                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  curl                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  cvs                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  cvs_wrapped                                           **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  cxxfilt                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") **[5](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  developer_cmds                                        **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  diffstat                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  diskdev_cmds                                          [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  disklabel                                              [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  distcc                                                 [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  doc_cmds                                              **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  drvAppleCMD646Root                                     **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  dtrace                                                 [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [15
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [16](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[17](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  dyld                                                   [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [15
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [16](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [17](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [18
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  eap8021x                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2")
  efax                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") **[14](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  efiboot                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2")
  emacs                                                  [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") **[14](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  enscript                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  expat                                                  **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  extenTools                                             **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  fetchmail                                              **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  file                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  file_cmds                                             **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  files                                                  **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  flex                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  freeradius                                             [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           )
  gcc                                                    [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2")
  gcc_42                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2")
  gcc_os                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  gcc_select                                            **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  gccfast                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  gdb                                                    [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  gdbforcw                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") **[5](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  glibtool                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  gm4                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  gnudiff                                                **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  gnumake                                                **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  gnuserv                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") **[
                                                           13](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  gnutar                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") **[
                                                           13](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  gnuzip                                                 **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  gperf                                                  **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  gpt                                                    [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  graphviz                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  grep                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  groff                                                  **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  gssd                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            **[9](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  gutenprint                                             [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  headerdoc                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  hfs                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  iodbc                                                  [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") [14](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [15](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [16](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: 2") [17](ja
                                                           vascript:void(0); 
                                                           "EXIT STATUS: 2")
                                                            [18](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2")
  ipsec                                                  [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") **[8](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  ipv6configuration                                      [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **")
  isoutil                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") *
                                                           *[11](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")**
  jam                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  kext_tools                                            [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") **[13](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  keymaps                                                **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")**
  keymgr                                                 **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  ksh                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  launchd                                                [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **")
  launchd_libs                                          [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")** **[8](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  ld64                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  less                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  libdwarf                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: ?") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            ?") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: ?") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: ?") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: ?") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : ?") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") [14](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2")
  libdyld                                                [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") **
                                                           [9](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  libedit                                                **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  libelf                                                 **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")**
  libffi                                                 **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  libfs                                                  **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  libgcc                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  libiconv                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  libmd                                                  **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  libpcap                                                **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  libresolv                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  libsecurity_agent                                     [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") **
                                                           [9](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  libsecurity_apple                                     [1](javascript:voi
  _csp                                                    d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: ?") [12](ja
                                                           vascript:void(0); 
                                                           "EXIT STATUS: ?")
                                                            [13](javascript:v
                                                           oid(0); "** BUILD 
                                                           FAILED **") [14](
                                                           javascript:void(0)
                                                           ; "** BUILD FAILED
                                                            **") [15](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: ?") **[
                                                           16](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  libsecurity_apple                                     [1](javascript:voi
  _cspdl                                                  d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: ?") [12](ja
                                                           vascript:void(0); 
                                                           "EXIT STATUS: ?")
                                                            [13](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: ?") [14](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [15](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **")
  libsecurity_apple                                     [1](javascript:voi
  _file_dl                                               d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") **[
                                                           12](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  libsecurity_apple                                     [1](javascript:voi
  _x509_cl                                               d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libsecurity_apple                                     [1](javascript:voi
  _x509_tp                                               d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           ** **[12](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  libsecurity_asn1                                      [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           ** **[12](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  libsecurity_autho                                     [1](javascript:voi
  rization                                                 d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  libsecurity_cdsa                                     [1](javascript:voi
  _client                                                  d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libsecurity_cdsa                                     [1](javascript:voi
  _plugin                                                  d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           ** **[12](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  libsecurity_cdsa                                     [1](javascript:voi
  _utilities                                               d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           )
  libsecurity_cdsa                                     [1](javascript:voi
  _utils                                                   d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") **[8](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  libsecurity_check                                     [1](javascript:voi
  pw                                                       d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  libsecurity_cms                                       [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           ** **[12](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  libsecurity_codes                                     [1](javascript:voi
  igning                                                   d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [15
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [16](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [17](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [18
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [19](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [20](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [21
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [22](java
                                                           script:void(0); "E
                                                           XIT STATUS: ?") [
                                                           23](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : ?") [24](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [25](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: ?")
  libsecurity_cssm                                      [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libsecurity_dotma                                     [1](javascript:voi
  cdl                                                      d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  libsecurity_filed                                     [1](javascript:voi
  b                                                        d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libsecurity_filev                                     [1](javascript:voi
  ault                                                     d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: ?") [15](ja
                                                           vascript:void(0); 
                                                           "EXIT STATUS: ?")
                                                            [16](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: ?") [17](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [18](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: ?") **[19](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  libsecurity_keych                                     [1](javascript:voi
  ain                                                      d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: ?") [12](ja
                                                           vascript:void(0); 
                                                           "EXIT STATUS: ?")
                                                            [13](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: ?") [14](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [15](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [16
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           ?") **[17](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  libsecurity_ldap                                     [1](javascript:voi
  _dl                                                      d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[14](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libsecurity_manif                                     [1](javascript:voi
  est                                                      d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libsecurity_mds                                       [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") **[
                                                           12](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  libsecurity_ocspd                                     [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") **
                                                           [9](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  libsecurity_pkcs1                                     [1](javascript:voi
  2                                                        d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: ?") [12](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [13](javascri
                                                           pt:void(0); "** BU
                                                           ILD FAILED **") *
                                                           *[14](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")**
  libsecurity_sd_c                                     [1](javascript:voi
  spdl                                                     d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libsecurity_smime                                     [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libsecurity_ssl                                       [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libsecurity_utili                                     [1](javascript:voi
  ties                                                     d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: ?") [12](ja
                                                           vascript:void(0); 
                                                           "EXIT STATUS: ?")
                                                            [13](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: ?") [14](java
                                                           script:void(0); "E
                                                           XIT STATUS: ?") [
                                                           15](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : ?") **[16](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**
  libsecurityd                                           [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) **[11](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  libstdcxx                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") **[5](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  libstdcxx_SUPanWh                                     [1](javascript:voi
  eat                                                      d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  libtelnet                                              **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  libutil                                                **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  libxml2                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") **[8]
                                                           (javascript:void(0
                                                           ); "** BUILD SUCCE
                                                           EDED **")**
  libxslt                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  lsof                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  lukemftp                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  lukemftpd                                              **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  mDNSResponder                                          [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  mDNSResponderSyste                                     [1](javascript:voi
  mLibraries                                               d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            **[9](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  mail_cmds                                             **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  mailman                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  man                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  misc_cmds                                             **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  modemccl                                               [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  msdosfs                                                [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") **[8](javascr
                                                           ipt:void(0); "** B
                                                           UILD SUCCEEDED **"
                                                           )**
  nano                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  nasm                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  ncurses                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") **[3
                                                           ](javascript:void(
                                                           0); "** BUILD SUCC
                                                           EEDED **")** ^**[
                                                           4](javascript:void
                                                           (0); "** BUILD SUC
                                                           CEEDED **")**^
  neon                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") **[3
                                                           ](javascript:void(
                                                           0); "** BUILD SUCC
                                                           EEDED **")** ^**[
                                                           4](javascript:void
                                                           (0); "** BUILD SUC
                                                           CEEDED **")**^
  net_snmp                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  netcat                                                 **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  netinfo                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: ?") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") *
                                                           *[11](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")**
  network_cmds                                          [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            **[9](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  notify                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            **[9](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  ntfs                                                   [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  ntp                                                    [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") [14](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") **[15
                                                           ](javascript:void(
                                                           0); "** BUILD SUCC
                                                           EEDED **")** **[1
                                                           6](javascript:void
                                                           (0); "** BUILD SUC
                                                           CEEDED **")**
  objc4                                                  **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  openmpi                                                **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  pam                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  pam_modules                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") [14](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2")
  passwordserver_sa                                     [1](javascript:voi
  sl                                                       d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") **[13](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  passwordserver_sa                                     **[1](javascript:v
  slextra                                                  oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  passwordserver_sa                                     [1](javascript:voi
  slkerberos                                               d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") **[
                                                           15](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  patch_cmds                                            **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  pb_makefiles                                          **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  pbx_jamfiles                                          **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  pcsc                                                   
  pdisk                                                  [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  perl                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  portmap                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  postfix                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") **[
                                                           13](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  ppp                                                    [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  procmail                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  project_makefiles                                     [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") **[5](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  pyOpenSSL                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  pyobjc                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  python                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  python23                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  python_dateutil                                       [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  python_modules                                        [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  rcs                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  remote_cmds                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            **[9](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  removefile                                             **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  rsync                                                  **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  ruby                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  ruby_dnssd                                            [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  ruby_libxml                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  samba                                                  [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  screen                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            **[9](javascript
                                                           :void(0); "** BUIL
                                                           D SUCCEEDED **")**
  security_authtram                                     **[1](javascript:v
  poline                                                   oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  security_certific                                     **[1](javascript:v
  ates                                                     oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  security_certtool                                     [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") **
                                                           [9](javascript:voi
                                                           d(0); "** BUILD SU
                                                           CCEEDED **")**
  security_crlrefre                                     [1](javascript:voi
  sh                                                       d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") **[10](ja
                                                           vascript:void(0); 
                                                           "** BUILD SUCCEEDE
                                                           D **")**
  security_dotmac_                                     [1](javascript:voi
  tp                                                       d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [14](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [15
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           ?") [16](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: ?") [17](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: ?"
                                                           ) [18](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [19
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [20](java
                                                           script:void(0); "E
                                                           XIT STATUS: ?") [
                                                           21](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : ?") [22](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [23](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: ?") [24](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [25](javascript
                                                           :void(0); "EXIT ST
                                                           ATUS: ?") [26](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [27](javascri
                                                           pt:void(0); "** BU
                                                           ILD FAILED **") [
                                                           28](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") **[29](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  security_ocspd                                        [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  security_privport                                     [1](javascript:voi
  server                                                   d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  security_systemke                                     [1](javascript:voi
  ychain                                                   d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           )
  securityd                                              [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [13](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           )
  shell_cmds                                            [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  smb                                                    [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  srm                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  stmalloc                                               **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  subversion                                             [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  sudo                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  svk                                                    
  swig                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  syslog                                                 [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2") [13
                                                           ](javascript:void(
                                                           0); "EXIT STATUS: 
                                                           2") [14](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2")
  system_cmds                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  system_config                                         **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  tcl                                                    [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  tcl_ext                                               [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  tcl_tk                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  tcp_wrappers                                          **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  tcpdump                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") **[3
                                                           ](javascript:void(
                                                           0); "** BUILD SUCC
                                                           EEDED **")** ^**[
                                                           4](javascript:void
                                                           (0); "** BUILD SUC
                                                           CEEDED **")**^
  tcsh                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  texi2html                                              **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  texinfo                                                [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") **[3
                                                           ](javascript:void(
                                                           0); "** BUILD SUCC
                                                           EEDED **")** ^**[
                                                           4](javascript:void
                                                           (0); "** BUILD SUC
                                                           CEEDED **")**^
  text_cmds                                             **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  tidy                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") **[12](java
                                                           script:void(0); "*
                                                           * BUILD SUCCEEDED 
                                                           **")**
  top                                                    [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") **[7](javasc
                                                           ript:void(0); "** 
                                                           BUILD SUCCEEDED **
                                                           ")**
  usertemplate                                           [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") **[8]
                                                           (javascript:void(0
                                                           ); "** BUILD SUCCE
                                                           EDED **")**
  uucp                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  vim                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  webdavfs                                               [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") [7](ja
                                                           vascript:void(0); 
                                                           "** BUILD FAILED *
                                                           *") [8](javascrip
                                                           t:void(0); "** BUI
                                                           LD FAILED **") [9
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **") [10](java
                                                           script:void(0); "*
                                                           * BUILD FAILED **"
                                                           ) [11](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [12
                                                           ](javascript:void(
                                                           0); "** BUILD FAIL
                                                           ED **")
  wxWidgets                                              [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") [3](
                                                           javascript:void(0)
                                                           ; "EXIT STATUS: 2"
                                                           ) [4](javascript:
                                                           void(0); "EXIT STA
                                                           TUS: 2") [5](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           6](javascript:void
                                                           (0); "EXIT STATUS:
                                                            2") [7](javascri
                                                           pt:void(0); "EXIT 
                                                           STATUS: 2") [8](j
                                                           avascript:void(0);
                                                            "EXIT STATUS: 2")
                                                            [9](javascript:v
                                                           oid(0); "EXIT STAT
                                                           US: 2") [10](java
                                                           script:void(0); "E
                                                           XIT STATUS: 2") [
                                                           11](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [12](javasc
                                                           ript:void(0); "EXI
                                                           T STATUS: 2")
  xar                                                    [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") [3](javascript
                                                           :void(0); "** BUIL
                                                           D FAILED **") [4]
                                                           (javascript:void(0
                                                           ); "** BUILD FAILE
                                                           D **") [5](javasc
                                                           ript:void(0); "** 
                                                           BUILD FAILED **")
                                                            [6](javascript:vo
                                                           id(0); "** BUILD F
                                                           AILED **") **[7](
                                                           javascript:void(0)
                                                           ; "** BUILD SUCCEE
                                                           DED **")**
  xelf                                                   **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  xnu                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  zfs                                                    [1](javascript:voi
                                                           d(0); "** BUILD FA
                                                           ILED **") [2](jav
                                                           ascript:void(0); "
                                                           ** BUILD FAILED **
                                                           ") **[3](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           ** **[4](javascri
                                                           pt:void(0); "** BU
                                                           ILD SUCCEEDED **")
                                                           **
  zip                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  zlib                                                   [1](javascript:voi
                                                           d(0); "EXIT STATUS
                                                           : 2") [2](javascr
                                                           ipt:void(0); "EXIT
                                                            STATUS: 2") **[3
                                                           ](javascript:void(
                                                           0); "** BUILD SUCC
                                                           EEDED **")** ^**[
                                                           4](javascript:void
                                                           (0); "** BUILD SUC
                                                           CEEDED **")**^
  zsh                                                    **[1](javascript:v
                                                           oid(0); "** BUILD 
                                                           SUCCEEDED **")** 
                                                           ^**[2](javascript:
                                                           void(0); "** BUILD
                                                            SUCCEEDED **")**^
  ------------------ ------------------ ------------------ ------------------
------------------------------------------------------------------------
289 / 417 successfully built.
121 / 417 failed to build.


------------------------------------------------------------------------
#### 1..3-pass
After the first pass and using `/opt/local/share/darwinbuild/packageRoots', many projects have been built and packaged successfully.

On the other side, there is the list of packages which have not been built successfully for any reasons.

Just before running into the second pass, we will load all these freshly built projects. Then we will see if more projects are built after the second pass.

These binary roots will be also loaded.
Another step which could have been done at the beginning or each pass is to load headers (-headers):

`for Y in `ls Packages | awk -F "." '{print $1}'`; do`
`        darwinbuild -headers $Y`
`done`


Build succeeded:



+--------------------+--------------------+--------------------+--------------------+
| <span              |  **2-pass**       |  **3-pass**       |  **3-pass'        |
| style="font-weight |                    |                    | (-headers)**       |
| :bold">1-pass</spa |                    |                    |                    |
| n>                 |                    |                    |                    |
+--------------------+--------------------+--------------------+--------------------+
| <span              | <span              | <span              | <span              |
| style="border-coll | style="border-coll | style="border-coll | style="border-coll |
| apse:separate"></s | apse:separate"></s | apse:separate"></s | apse:separate;font |
| pan>               | pan>               | pan>               | -family:courier ne |
| <div               | <div>              | <div>              | w,Verdana,sans-ser |
| style="text-align: |                    |                    | if"></span>        |
| left">             | <span              | <span              | <div>              |
|                    | style="font-family | style="font-size:x |                    |
| <span              | :arial,sans-serif" | -small">ncurses-21 | <span              |
| style="font-family | ><span             | ~3</span>         | style="font-family |
| :arial,sans-serif" | style="font-size:x |                    | :arial,sans-serif" |
| ><span             | -small">AppleADBMo | </div>             | ><span             |
| style="font-size:x | use-212~2</span>< |                    | style="font-size:x |
| -small">Apple3Com3 | /span>             | <div>              | -small">Apple3Com3 |
| C90x-10~1</span>< |                    |                    | C<span             |
| /span>             | </div>             | <span              | style="font-family |
|                    |                    | style="font-size:x | :courier new;font- |
| </div>             | <div>              | -small">neon-8~3< | size:12px"><span   |
|                    |                    | /span>             | style="font-family |
| <div>              | <span              |                    | :arial;font-size:1 |
|                    | style="font-family | </div>             | 0px">90x-10~2    |
| <span              | :arial,sans-serif" |                    | <span              |
| style="font-family | ><span             | <div>              | style="font-family |
| :arial,sans-serif" | style="font-size:x |                    | :Arial">AppleADBBu |
| ><span             | -small">AppleKeysw | <span              | tt</span>ons-300~ |
| style="font-size:x | itch-104.0.1~2</s | style="font-size:x | 2</span></span></s |
| -small">AppleADBBu | pan></span>        | -small">tcpdump-23 | pan></span>        |
| ttons-300~1</span |                    | ~3</span>         |                    |
| ></span>           | </div>             |                    | </div>             |
|                    |                    | </div>             |                    |
| </div>             | <div>              |                    | <div>              |
|                    |                    | <div>              |                    |
| <div>              | <span              |                    | <span              |
|                    | style="font-family | <span              | style="font-family |
| <span              | :arial,sans-serif" | style="font-size:x | :arial,sans-serif" |
| style="font-family | ><span             | -small">texinfo-17 | ><span             |
| :arial,sans-serif" | style="font-size:x | ~3</span>         | style="font-size:x |
| ><span             | -small">CoreOSMake |                    | -small">AppleADBKe |
| style="font-size:x | files-52~2</span> | </div>             | yboard-239.1~2</s |
| -small">AppleADBKe | </span>            |                    | pan></span>        |
| yboard-239.1~1</s |                    | <div>              |                    |
| pan></span>        | </div>             |                    | </div>             |
|                    |                    | <span              |                    |
| </div>             | <div>              | style="font-size:x | <div>              |
|                    |                    | -small">zlib-18~3 |                    |
| <div>              | <span              | </span>            | <span              |
|                    | style="font-family |                    | style="font-family |
| <span              | :arial,sans-serif" | </div>             | :arial,sans-serif" |
| style="font-family | ><span             |                    | ><span             |
| :arial,sans-serif" | style="font-size:x |                    | style="font-size:x |
| ><span             | -small">OpenSSL096 |                    | -small">AppleADBMo |
| style="font-size:x | -6.2~2</span></sp |                    | use-212~3</span>< |
| -small">AppleCore9 | an>                |                    | /span>             |
| 9NVRAM-111.3.1~1< |                    |                    |                    |
| /span></span>      | </div>             |                    | </div>             |
|                    |                    |                    |                    |
| </div>             | <div>              |                    | <div>              |
|                    |                    |                    |                    |
| <div>              | <span              |                    | <span              |
|                    | style="font-family |                    | style="font-family |
| <span              | :arial,sans-serif" |                    | :arial,sans-serif" |
| style="font-family | ><span             |                    | ><span             |
| :arial,sans-serif" | style="font-size:x |                    | style="font-size:x |
| ><span             | -small">TargetConf |                    | -small">AppleCore9 |
| style="font-size:x | ig-6~2</span></sp |                    | 9NVRAM-111.3.1~2< |
| -small">AppleFan-1 | an>                |                    | /span></span>      |
| 10.3.1~1</span></ |                    |                    |                    |
| span>              | </div>             |                    | </div>             |
|                    |                    |                    |                    |
| </div>             | <div>              |                    | <div>              |
|                    |                    |                    |                    |
| <div>              | <span              |                    | <span              |
|                    | style="font-family |                    | style="font-family |
| <span              | :arial,sans-serif" |                    | :arial,sans-serif" |
| style="font-family | ><span             |                    | ><span             |
| :arial,sans-serif" | style="font-size:x |                    | style="font-size:x |
| ><span             | -small">TargetConf |                    | -small">AppleFan-1 |
| style="font-size:x | ig_host-6~2</spa |                    | 10.3.1~2</span></ |
| -small">AppleFlash | n></span>          |                    | span>              |
| NVRAM-105.4.0~1</ |                    |                    |                    |
| span></span>       | </div>             |                    | </div>             |
|                    |                    |                    |                    |
| </div>             | <div>              |                    | <div>              |
|                    |                    |                    |                    |
| <div>              | <span              |                    | <span              |
|                    | style="font-family |                    | style="font-family |
| <span              | :arial,sans-serif" |                    | :arial,sans-serif" |
| style="font-family | ><span             |                    | ><span             |
| :arial,sans-serif" | style="font-size:x |                    | style="font-size:x |
| ><span             | -small">apache_mo |                    | -small">AppleFlash |
| style="font-size:x | d_perl1-16~2</sp |                    | NVRAM-105.4.0~2</ |
| -small">AppleGMACE | an></span>         |                    | span></span>       |
| thernet-157.3.1~1 |                    |                    |                    |
| </span></span>     | </div>             |                    | </div>             |
|                    |                    |                    |                    |
| </div>             | <div>              |                    | <div>              |
|                    |                    |                    |                    |
| <div>              | <span              |                    | <span              |
|                    | style="font-family |                    | style="font-family |
| <span              | :arial,sans-serif" |                    | :arial,sans-serif" |
| style="font-family | ><span             |                    | ><span             |
| :arial,sans-serif" | style="font-size:x |                    | style="font-size:x |
| ><span             | -small">apache_mo |                    | -small">AppleGMACE |
| style="font-size:x | d_ssl-690~2</spa |                    | thernet-157.3.1~2 |
| -small">AppleGPIO- | n></span>          |                    | </span></span>     |
| 131.0.0~1</span>< |                    |                    |                    |
| /span>             | </div>             |                    | </div>             |
|                    |                    |                    |                    |
| </div>             | <div>              |                    | <div>              |
|                    |                    |                    |                    |
| <div>              | <span              |                    | <span              |
|                    | style="font-family |                    | style="font-family |
| <span              | :arial,sans-serif" |                    | :arial,sans-serif" |
| style="font-family | ><span             |                    | ><span             |
| :arial,sans-serif" | style="font-size:x |                    | style="font-size:x |
| ><span             | -small">apr-12~2< |                    | -small">AppleGPIO- |
| style="font-size:x | /span></span>      |                    | 131.0.0~2</span>< |
| -small">AppleI2C-4 |                    |                    | /span>             |
| 00.0.3~1</span></ | </div>             |                    |                    |
| span>              |                    |                    | </div>             |
|                    | <div>              |                    |                    |
| </div>             |                    |                    | <div>              |
|                    | <span              |                    |                    |
| <div>              | style="font-family |                    | <span              |
|                    | :arial,sans-serif" |                    | style="font-family |
| <span              | ><span             |                    | :arial,sans-serif" |
| style="font-family | style="font-size:x |                    | ><span             |
| :arial,sans-serif" | -small">autoconf-1 |                    | style="font-size:x |
| ><span             | 4~2</span></span> |                    | -small">AppleI2C-4 |
| style="font-size:x |                    |                    | 00.0.3~2</span></ |
| -small">AppleI2S-1 | </div>             |                    | span>              |
| 01.3.1~1</span></ |                    |                    |                    |
| span>              | <div>              |                    | </div>             |
|                    |                    |                    |                    |
| </div>             | <span              |                    | <div>              |
|                    | style="font-family |                    |                    |
| <div>              | :arial,sans-serif" |                    | <span              |
|                    | ><span             |                    | style="font-family |
| <span              | style="font-size:x |                    | :arial,sans-serif" |
| style="font-family | -small">automake-7 |                    | ><span             |
| :arial,sans-serif" | ~2</span></span>  |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleI2S-1 |
| style="font-size:x | </div>             |                    | 01.3.1~2</span></ |
| -small">AppleIntel |                    |                    | span>              |
| PIIXATA-200.0.1~1 | <div>              |                    |                    |
| </span></span>     |                    |                    | </div>             |
|                    | <span              |                    |                    |
| </div>             | style="font-family |                    | <div>              |
|                    | :arial,sans-serif" |                    |                    |
| <div>              | ><span             |                    | <span              |
|                    | style="font-size:x |                    | style="font-family |
| <span              | -small">awk-11~2< |                    | :arial,sans-serif" |
| style="font-family | /span></span>      |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             | </div>             |                    | -small">AppleIntel |
| style="font-size:x |                    |                    | PIIXATA-200.0.1~2 |
| -small">AppleK2SAT | <div>              |                    | </span></span>     |
| A-104.3.2~1</span |                    |                    |                    |
| ></span>           | <span              |                    | </div>             |
|                    | style="font-family |                    |                    |
| </div>             | :arial,sans-serif" |                    | <div>              |
|                    | ><span             |                    |                    |
| <div>              | style="font-size:x |                    | <span              |
|                    | -small">bash-76.2 |                    | style="font-family |
| <span              | ~2</span></span>   |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" | </div>             |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleK2SAT |
| style="font-size:x | <div>              |                    | A-104.3.2~2</span |
| -small">AppleK2SAT |                    |                    | ></span>           |
| ARoot-105.2.2~1</ | <span              |                    |                    |
| span></span>       | style="font-family |                    | </div>             |
|                    | :arial,sans-serif" |                    |                    |
| </div>             | ><span             |                    | <div>              |
|                    | style="font-size:x |                    |                    |
| <div>              | -small">basic_cmd |                    | <span              |
|                    | s-48~2</span></sp |                    | style="font-family |
| <span              | an>                |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" | </div>             |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleK2SAT |
| style="font-size:x | <div>              |                    | ARoot-105.2.2~2</ |
| -small">AppleKauai |                    |                    | span></span>       |
| ATA-121.3.4~1</sp | <span              |                    |                    |
| an></span>         | style="font-family |                    | </div>             |
|                    | :arial,sans-serif" |                    |                    |
| </div>             | ><span             |                    | <div>              |
|                    | style="font-size:x |                    |                    |
| <div>              | -small">bc-21~2</ |                    | <span              |
|                    | span></span>       |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family | </div>             |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             | <div>              |                    | -small">AppleKauai |
| style="font-size:x |                    |                    | ATA-121.3.4~2</sp |
| -small">AppleKiwiA | <span              |                    | an></span>         |
| TA-102.3.2~1</spa | style="font-family |                    |                    |
| n></span>          | :arial,sans-serif" |                    | </div>             |
|                    | ><span             |                    |                    |
| </div>             | style="font-size:x |                    | <div>              |
|                    | -small">bison-13~ |                    |                    |
| <div>              | 2</span></span>    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              | </div>             |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" | <div>              |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleKeysw |
| style="font-size:x | <span              |                    | itch-104.0.1~3</s |
| -small">AppleKiwiR | style="font-family |                    | pan></span>        |
| oot-105.3.1~1</sp | :arial,sans-serif" |                    |                    |
| an></span>         | ><span             |                    | </div>             |
|                    | style="font-size:x |                    |                    |
| </div>             | -small">bison1-1~ |                    | <div>              |
|                    | 2</span></span>    |                    |                    |
| <div>              |                    |                    | <span              |
|                    | </div>             |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family | <div>              |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             | <span              |                    | -small">AppleKiwiA |
| style="font-size:x | style="font-family |                    | TA-102.3.2~2</spa |
| -small">AppleMPIC- | :arial,sans-serif" |                    | n></span>          |
| 1.5.3~1</span></s | ><span             |                    |                    |
| pan>               | style="font-size:x |                    | </div>             |
|                    | -small">bootstrap |                    |                    |
| </div>             | _cmds-60.1~2</spa |                    | <div>              |
|                    | n></span>          |                    |                    |
| <div>              |                    |                    | <span              |
|                    | </div>             |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family | <div>              |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             | <span              |                    | -small">AppleKiwiR |
| style="font-size:x | style="font-family |                    | oot-105.3.1~2</sp |
| -small">AppleMacRI | :arial,sans-serif" |                    | an></span>         |
| SC2PE-187.0.5~1</ | ><span             |                    |                    |
| span></span>       | style="font-size:x |                    | </div>             |
|                    | -small">bsdmake-23 |                    |                    |
| </div>             | ~2</span></span>  |                    | <div>              |
|                    |                    |                    |                    |
| <div>              | </div>             |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              | <div>              |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" | <span              |                    | style="font-size:x |
| ><span             | style="font-family |                    | -small">AppleMPIC- |
| style="font-size:x | :arial,sans-serif" |                    | 1.5.3~2</span></s |
| -small">AppleMacRi | ><span             |                    | pan>               |
| scPCI-3.4~1</span | style="font-size:x |                    |                    |
| ></span>           | -small">bsm-13~2< |                    | </div>             |
|                    | /span></span>      |                    |                    |
| </div>             |                    |                    | <div>              |
|                    | </div>             |                    |                    |
| <div>              |                    |                    | <span              |
|                    | <div>              |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family | <span              |                    | ><span             |
| :arial,sans-serif" | style="font-family |                    | style="font-size:x |
| ><span             | :arial,sans-serif" |                    | -small">AppleMacRI |
| style="font-size:x | ><span             |                    | SC2PE-187.0.5~2</ |
| -small">AppleMedia | style="font-size:x |                    | span></span>       |
| Bay-102.3.1~1</sp | -small">bzip2-16~ |                    |                    |
| an></span>         | 2</span></span>    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             | </div>             |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleMacRi |
| style="font-size:x |                    |                    | scPCI-3.4~2</span |
| -small">ApplePCCar |                    |                    | ></span>           |
| d16ATA-113~1</spa |                    |                    |                    |
| n></span>          |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleMedia |
| style="font-size:x |                    |                    | Bay-102.3.1~2</sp |
| -small">ApplePCCar |                    |                    | an></span>         |
| dATA-103.3.2~1</s |                    |                    |                    |
| pan></span>        |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">ApplePCCar |
| style="font-size:x |                    |                    | d16ATA-113~2</spa |
| -small">AppleRTL81 |                    |                    | n></span>          |
| 39Ethernet-141~1< |                    |                    |                    |
| /span></span>      |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">ApplePCCar |
| style="font-size:x |                    |                    | dATA-103.3.2~2</s |
| -small">AppleSym8x |                    |                    | pan></span>        |
| x-122.3.1~1</span |                    |                    |                    |
| ></span>           |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleRTL81 |
| style="font-size:x |                    |                    | 39Ethernet-141~2< |
| -small">AppleTherm |                    |                    | /span></span>      |
| al-101.3.2~1</spa |                    |                    |                    |
| n></span>          |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleSym8x |
| style="font-size:x |                    |                    | x-122.3.1~2</span |
| -small">AppleVIA-1 |                    |                    | ></span>           |
| 51.0.1~1</span></ |                    |                    |                    |
| span>              |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleTherm |
| style="font-size:x |                    |                    | al-101.3.2~2</spa |
| -small">CarbonHead |                    |                    | n></span>          |
| ers-9G55~1</span> |                    |                    |                    |
| </span>            |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">AppleVIA-1 |
| style="font-size:x |                    |                    | 51.0.1~2</span></ |
| -small">CommonCryp |                    |                    | span>              |
| to-32207~1</span> |                    |                    |                    |
| </span>            |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">CarbonHead |
| style="font-size:x |                    |                    | ers-9G55~2</span> |
| -small">CrackLib-3 |                    |                    | </span>            |
| 0889~1</span></sp |                    |                    |                    |
| an>                |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">CommonCryp |
| style="font-size:x |                    |                    | to-32207~2</span> |
| -small">Csu-75~1< |                    |                    | </span>            |
| /span></span>      |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">CoreOSMake |
| -small">ICU-8.11.4 |                    |                    | files-52~3</span> |
| ~1</span></span>  |                    |                    | </span>            |
|                    |                    |                    |                    |
| </div>             |                    |                    | </div>             |
|                    |                    |                    |                    |
| <div>              |                    |                    | <div>              |
|                    |                    |                    |                    |
| <span              |                    |                    | <span              |
| style="font-family |                    |                    | style="font-family |
| :arial,sans-serif" |                    |                    | :arial,sans-serif" |
| ><span             |                    |                    | ><span             |
| style="font-size:x |                    |                    | style="font-size:x |
| -small">ICU_debug |                    |                    | -small">ICU-8.11.4 |
| -8.11.4~1</span>< |                    |                    | ~2</span></span>  |
| /span>             |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">ICU_debug |
| -small">ICU_profi |                    |                    | -8.11.4~2</span>< |
| le-8.11.4~1</span |                    |                    | /span>             |
| ></span>           |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">ICU_profi |
| -small">IOACPIFami |                    |                    | le-8.11.4~2</span |
| ly-5~1</span></sp |                    |                    | ></span>           |
| an>                |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">IOACPIFami |
| -small">IOADBFamil |                    |                    | ly-5~2</span></sp |
| y-6~1</span></spa |                    |                    | an>                |
| n>                 |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">IOADBFamil |
| -small">KeyLargoAT |                    |                    | y-6~2</span></spa |
| A-111.3.1~1</span |                    |                    | n>                 |
| ></span>           |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">KeyLargoAT |
| -small">Libcpp_ke |                    |                    | A-111.3.1~2</span |
| xt-5~1</span></sp |                    |                    | ></span>           |
| an>                |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">Librpcsvc- |
| -small">Libm-292.4 |                    |                    | 15~2</span></span |
| ~1</span></span>  |                    |                    | >                  |
|                    |                    |                    |                    |
| </div>             |                    |                    | </div>             |
|                    |                    |                    |                    |
| <div>              |                    |                    | <div>              |
|                    |                    |                    |                    |
| <span              |                    |                    | <span              |
| style="font-family |                    |                    | style="font-family |
| :arial,sans-serif" |                    |                    | :arial,sans-serif" |
| ><span             |                    |                    | ><span             |
| style="font-size:x |                    |                    | style="font-size:x |
| -small">Libmx-292. |                    |                    | -small">Libstreams |
| 4~1</span></span> |                    |                    | -25~2</span></spa |
|                    |                    |                    | n>                 |
| </div>             |                    |                    |                    |
|                    |                    |                    | </div>             |
| <div>              |                    |                    |                    |
|                    |                    |                    | <div>              |
| <span              |                    |                    |                    |
| style="font-family |                    |                    | <span              |
| :arial,sans-serif" |                    |                    | style="font-family |
| ><span             |                    |                    | :arial,sans-serif" |
| style="font-size:x |                    |                    | ><span             |
| -small">Librpcsvc- |                    |                    | style="font-size:x |
| 15~1</span></span |                    |                    | -small">SCSIHeader |
| >                  |                    |                    | Installer-100.0.2 |
|                    |                    |                    | ~2</span></span>   |
| </div>             |                    |                    |                    |
|                    |                    |                    | </div>             |
| <div>              |                    |                    |                    |
|                    |                    |                    | <div>              |
| <span              |                    |                    |                    |
| style="font-family |                    |                    | <span              |
| :arial,sans-serif" |                    |                    | style="font-family |
| ><span             |                    |                    | :arial,sans-serif" |
| style="font-size:x |                    |                    | ><span             |
| -small">Libstreams |                    |                    | style="font-size:x |
| -25~1</span></spa |                    |                    | -small">TargetConf |
| n>                 |                    |                    | ig-6~3</span></sp |
|                    |                    |                    | an>                |
| </div>             |                    |                    |                    |
|                    |                    |                    | </div>             |
| <div>              |                    |                    |                    |
|                    |                    |                    | <div>              |
| <span              |                    |                    |                    |
| style="font-family |                    |                    | <span              |
| :arial,sans-serif" |                    |                    | style="font-family |
| ><span             |                    |                    | :arial,sans-serif" |
| style="font-size:x |                    |                    | ><span             |
| -small">Liby-15~1 |                    |                    | style="font-size:x |
| </span></span>     |                    |                    | -small">TargetConf |
|                    |                    |                    | ig_host-6~3</spa |
| </div>             |                    |                    | n></span>          |
|                    |                    |                    |                    |
| <div>              |                    |                    | </div>             |
|                    |                    |                    |                    |
| <span              |                    |                    | <div>              |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    | <span              |
| ><span             |                    |                    | style="font-family |
| style="font-size:x |                    |                    | :arial,sans-serif" |
| -small">SCSIHeader |                    |                    | ><span             |
| Installer-100.0.2 |                    |                    | style="font-size:x |
| ~1</span></span>   |                    |                    | -small">Tokend-352 |
|                    |                    |                    | 09~2</span></span |
| </div>             |                    |                    | >                  |
|                    |                    |                    |                    |
| <div>              |                    |                    | </div>             |
|                    |                    |                    |                    |
| <span              |                    |                    | <div>              |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    | <span              |
| ><span             |                    |                    | style="font-family |
| style="font-size:x |                    |                    | :arial,sans-serif" |
| -small">SquirrelMa |                    |                    | ><span             |
| il-29~1</span></s |                    |                    | style="font-size:x |
| pan>               |                    |                    | -small">architectu |
|                    |                    |                    | re-254.0.5~2</spa |
| </div>             |                    |                    | n></span>          |
|                    |                    |                    |                    |
| <div>              |                    |                    | </div>             |
|                    |                    |                    |                    |
| <span              |                    |                    | <div>              |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    | <span              |
| ><span             |                    |                    | style="font-family |
| style="font-size:x |                    |                    | :arial,sans-serif" |
| -small">SystemStub |                    |                    | ><span             |
| s-6~1</span></spa |                    |                    | style="font-size:x |
| n>                 |                    |                    | -small">autozone-7 |
|                    |                    |                    | 7.1~2</span></spa |
| </div>             |                    |                    | n>                 |
|                    |                    |                    |                    |
| <div>              |                    |                    | </div>             |
|                    |                    |                    |                    |
| <span              |                    |                    | <div>              |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    | <span              |
| ><span             |                    |                    | style="font-family |
| style="font-size:x |                    |                    | :arial,sans-serif" |
| -small">TimeZoneDa |                    |                    | ><span             |
| ta-16~1</span></s |                    |                    | style="font-size:x |
| pan>               |                    |                    | -small">bsdmake-23 |
|                    |                    |                    | ~3</span></span>  |
| </div>             |                    |                    |                    |
|                    |                    |                    | </div>             |
| <div>              |                    |                    |                    |
|                    |                    |                    | <div>              |
| <span              |                    |                    |                    |
| style="font-family |                    |                    | <span              |
| :arial,sans-serif" |                    |                    | style="font-family |
| ><span             |                    |                    | :arial,sans-serif" |
| style="font-size:x |                    |                    | ><span             |
| -small">Tokend-352 |                    |                    | style="font-size:x |
| 09~1</span></span |                    |                    | -small">bsm-13~3< |
| >                  |                    |                    | /span></span>      |
|                    |                    |                    |                    |
| </div>             |                    |                    | </div>             |
|                    |                    |                    |                    |
| <div>              |                    |                    | <div>              |
|                    |                    |                    |                    |
| <span              |                    |                    | <span              |
| style="font-family |                    |                    | style="font-family |
| :arial,sans-serif" |                    |                    | :arial,sans-serif" |
| ><span             |                    |                    | ><span             |
| style="font-size:x |                    |                    | style="font-size:x |
| -small">adv_cmds- |                    |                    | -small">drvAppleCM |
| 119~1</span></spa |                    |                    | D646Root-104.2.2~ |
| n>                 |                    |                    | 2</span></span>    |
|                    |                    |                    |                    |
| </div>             |                    |                    | </div>             |
|                    |                    |                    |                    |
| <div>              |                    |                    | <div>              |
|                    |                    |                    |                    |
| <span              |                    |                    | <span              |
| style="font-family |                    |                    | style="font-family |
| :arial,sans-serif" |                    |                    | :arial,sans-serif" |
| ><span             |                    |                    | ><span             |
| style="font-size:x |                    |                    | style="font-size:x |
| -small">amavisd-11 |                    |                    | -small">extenTools |
| 0.2~1</span></spa |                    |                    | -17.3~2</span></s |
| n>                 |                    |                    | pan>               |
|                    |                    |                    |                    |
| </div>             |                    |                    | </div>             |
|                    |                    |                    |                    |
| <div>              |                    |                    | <div>              |
|                    |                    |                    |                    |
| <span              |                    |                    | <span              |
| style="font-family |                    |                    | style="font-family |
| :arial,sans-serif" |                    |                    | :arial,sans-serif" |
| ><span             |                    |                    | ><span             |
| style="font-size:x |                    |                    | style="font-size:x |
| -small">architectu |                    |                    | -small">gcc_selec |
| re-254.0.5~1</spa |                    |                    | t-66~2</span></sp |
| n></span>          |                    |                    | an>                |
|                    |                    |                    |                    |
| </div>             |                    |                    | </div>             |
|                    |                    |                    |                    |
| <div>              |                    |                    | <div>              |
|                    |                    |                    |                    |
| <span              |                    |                    | <span              |
| style="font-family |                    |                    | style="font-family |
| :arial,sans-serif" |                    |                    | :arial,sans-serif" |
| ><span             |                    |                    | ><span             |
| style="font-size:x |                    |                    | style="font-size:x |
| -small">autozone-7 |                    |                    | -small">libedit-11 |
| 7.1~1</span></spa |                    |                    | ~2</span></span>  |
| n>                 |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">libffi-10 |
| -small">crontabs-3 |                    |                    | ~2</span></span>   |
| 4~1</span></span> |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">libfs-7~2 |
| -small">cscope-14 |                    |                    | </span></span>     |
| ~1</span></span>   |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">libpcap-18 |
| -small">curl-42~1 |                    |                    | ~2</span></span>  |
| </span></span>     |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">libtelnet- |
| -small">cvs-39~1< |                    |                    | 7~2</span></span> |
| /span></span>      |                    |                    |                    |
|                    |                    |                    | </div>             |
| </div>             |                    |                    |                    |
|                    |                    |                    | <div>              |
| <div>              |                    |                    |                    |
|                    |                    |                    | <span              |
| <span              |                    |                    | style="font-family |
| style="font-family |                    |                    | :arial,sans-serif" |
| :arial,sans-serif" |                    |                    | ><span             |
| ><span             |                    |                    | style="font-size:x |
| style="font-size:x |                    |                    | -small">libutil-11 |
| -small">cvs_wrapp |                    |                    | ~2</span></span>  |
| ed-13~1</span></s |                    |                    |                    |
| pan>               |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    | <div>              |
|                    |                    |                    |                    |
| <div>              |                    |                    | <span              |
|                    |                    |                    | style="font-family |
| <span              |                    |                    | :arial,sans-serif" |
| style="font-family |                    |                    | ><span             |
| :arial,sans-serif" |                    |                    | style="font-size:x |
| ><span             |                    |                    | -small">objc4-371. |
| style="font-size:x |                    |                    | 2~2</span></span> |
| -small">developer |                    |                    |                    |
| _cmds-49~1</span> |                    |                    | </div>             |
| </span>            |                    |                    |                    |
|                    |                    |                    | <div>              |
| </div>             |                    |                    |                    |
|                    |                    |                    | <span              |
| <div>              |                    |                    | style="font-family |
|                    |                    |                    | :arial,sans-serif" |
| <span              |                    |                    | ><span             |
| style="font-family |                    |                    | style="font-size:x |
| :arial,sans-serif" |                    |                    | -small">pam-32.1~ |
| ><span             |                    |                    | 2</span></span>    |
| style="font-size:x |                    |                    |                    |
| -small">diffstat-5 |                    |                    | </div>             |
| ~1</span></span>  |                    |                    |                    |
|                    |                    |                    | <div>              |
| </div>             |                    |                    |                    |
|                    |                    |                    | <span              |
| <div>              |                    |                    | style="font-family |
|                    |                    |                    | :arial,sans-serif" |
| <span              |                    |                    | ><span             |
| style="font-family |                    |                    | style="font-size:x |
| :arial,sans-serif" |                    |                    | -small">pbx_jamfi |
| ><span             |                    |                    | les-874~2</span>< |
| style="font-size:x |                    |                    | /span>             |
| -small">doc_cmds- |                    |                    |                    |
| 47~1</span></span |                    |                    | </div>             |
| >                  |                    |                    |                    |
|                    |                    |                    | <div>              |
| </div>             |                    |                    |                    |
|                    |                    |                    | <span              |
| <div>              |                    |                    | style="font-family |
|                    |                    |                    | :arial,sans-serif" |
| <span              |                    |                    | ><span             |
| style="font-family |                    |                    | style="font-size:x |
| :arial,sans-serif" |                    |                    | -small">removefile |
| ><span             |                    |                    | -11~2</span></spa |
| style="font-size:x |                    |                    | n>                 |
| -small">drvAppleCM |                    |                    |                    |
| D646Root-104.2.2~ |                    |                    | </div>             |
| 1</span></span>    |                    |                    |                    |
|                    |                    |                    | <div>              |
| </div>             |                    |                    |                    |
|                    |                    |                    | <span              |
| <div>              |                    |                    | style="font-family |
|                    |                    |                    | :arial,sans-serif" |
| <span              |                    |                    | ><span             |
| style="font-family |                    |                    | style="font-size:x |
| :arial,sans-serif" |                    |                    | -small">xnu-1228.1 |
| ><span             |                    |                    | 2.14~2</span></sp |
| style="font-size:x |                    |                    | an>                |
| -small">enscript-1 |                    |                    |                    |
| 5~1</span></span> |                    |                    | </div>             |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">expat-6~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">extenTools |                    |                    |                    |
| -17.3~1</span></s |                    |                    |                    |
| pan>               |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">fetchmail- |                    |                    |                    |
| 30~1</span></span |                    |                    |                    |
| >                  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">file-23~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">file_cmds |                    |                    |                    |
| -188~1</span></sp |                    |                    |                    |
| an>                |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">files-530. |                    |                    |                    |
| 1.5~1</span></spa |                    |                    |                    |
| n>                 |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">flex-20.3 |                    |                    |                    |
| ~1</span></span>   |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">gcc_selec |                    |                    |                    |
| t-66~1</span></sp |                    |                    |                    |
| an>                |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">glibtool-1 |                    |                    |                    |
| 2~1</span></span> |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">gm4-12~1< |                    |                    |                    |
| /span></span>      |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">gnudiff-14 |                    |                    |                    |
| ~1</span></span>  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">gnumake-11 |                    |                    |                    |
| 9~1</span></span> |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">gnuzip-25 |                    |                    |                    |
| ~1</span></span>   |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">gperf-4~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">graphviz-6 |                    |                    |                    |
| 22~1</span></span |                    |                    |                    |
| >                  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">grep-24~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">groff-31~ |                    |                    |                    |
| 1</span></span>    |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">hfs-165.1 |                    |                    |                    |
| ~1</span></span>   |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">jam-851~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">keymgr-18 |                    |                    |                    |
| ~1</span></span>   |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">ksh-13~1< |                    |                    |                    |
| /span></span>      |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">ld64-77.1 |                    |                    |                    |
| ~1</span></span>   |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">less-20~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">libedit-11 |                    |                    |                    |
| ~1</span></span>  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">libffi-10 |                    |                    |                    |
| ~1</span></span>   |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">libfs-7~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">libiconv-2 |                    |                    |                    |
| 4~1</span></span> |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">libmd-2~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">libpcap-18 |                    |                    |                    |
| ~1</span></span>  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">libtelnet- |                    |                    |                    |
| 7~1</span></span> |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">libutil-11 |                    |                    |                    |
| ~1</span></span>  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">lsof-33~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">lukemftp-1 |                    |                    |                    |
| 1~1</span></span> |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">lukemftpd- |                    |                    |                    |
| 33~1</span></span |                    |                    |                    |
| >                  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">mail_cmds |                    |                    |                    |
| -22~1</span></spa |                    |                    |                    |
| n>                 |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">man-12~1< |                    |                    |                    |
| /span></span>      |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">misc_cmds |                    |                    |                    |
| -23~1</span></spa |                    |                    |                    |
| n>                 |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">nano-4~1< |                    |                    |                    |
| /span></span>      |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">nasm-13~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">netcat-7~ |                    |                    |                    |
| 1</span></span>    |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">objc4-371. |                    |                    |                    |
| 2~1</span></span> |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">openmpi-5 |                    |                    |                    |
| ~1</span></span>   |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">pam-32.1~ |                    |                    |                    |
| 1</span></span>    |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">passwordse |                    |                    |                    |
| rver_saslextra-11 |                    |                    |                    |
| 8.1~1</span></spa |                    |                    |                    |
| n>                 |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">patch_cmd |                    |                    |                    |
| s-11~1</span></sp |                    |                    |                    |
| an>                |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">pb_makefi |                    |                    |                    |
| les-128~1</span>< |                    |                    |                    |
| /span>             |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">pbx_jamfi |                    |                    |                    |
| les-874~1</span>< |                    |                    |                    |
| /span>             |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">procmail-1 |                    |                    |                    |
| 1~1</span></span> |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">rcs-13~1< |                    |                    |                    |
| /span></span>      |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">removefile |                    |                    |                    |
| -11~1</span></spa |                    |                    |                    |
| n>                 |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">rsync-35.2 |                    |                    |                    |
| ~1</span></span>  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">security_ |                    |                    |                    |
| authtrampoline-325 |                    |                    |                    |
| 34~1</span></span |                    |                    |                    |
| >                  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">security_ |                    |                    |                    |
| certificates-36075 |                    |                    |                    |
| ~1</span></span>  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">srm-6~1</ |                    |                    |                    |
| span></span>       |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">stmalloc-4 |                    |                    |                    |
| ~1</span></span>  |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">sudo-28~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">swig-4~1< |                    |                    |                    |
| /span></span>      |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">system_co |                    |                    |                    |
| nfig-49~1</span>< |                    |                    |                    |
| /span>             |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">tcp_wrapp |                    |                    |                    |
| ers-18~1</span></ |                    |                    |                    |
| span>              |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">tcsh-60~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">texi2html- |                    |                    |                    |
| 5~1</span></span> |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">text_cmds |                    |                    |                    |
| -69~1</span></spa |                    |                    |                    |
| n>                 |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">uucp-10~1 |                    |                    |                    |
| </span></span>     |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">vim-39~1< |                    |                    |                    |
| /span></span>      |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">xelf-1~1< |                    |                    |                    |
| /span></span>      |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">zip-9~1</ |                    |                    |                    |
| span></span>       |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
|                    |                    |                    |                    |
| <div>              |                    |                    |                    |
|                    |                    |                    |                    |
| <span              |                    |                    |                    |
| style="font-family |                    |                    |                    |
| :arial,sans-serif" |                    |                    |                    |
| ><span             |                    |                    |                    |
| style="font-size:x |                    |                    |                    |
| -small">zsh-48~1< |                    |                    |                    |
| /span></span>      |                    |                    |                    |
|                    |                    |                    |                    |
| </div>             |                    |                    |                    |
+--------------------+--------------------+--------------------+--------------------+


**4-pass**

Again, all the projects will be built (or not). As a result, nothing will be built successfully according to packageRoots:

`/opt/local/share/darwinbuild/packageRoots           `
`Archive tool: tar (GNU tar) 1.15.1`
`*** Packaging Headers`
`*** Packaging Roots`

Finally, we reach the point where no buildable (without alteration, patch, etc..) dependency is missing.


Let's also now add [PureFoundation](../../../purefoundation.html) in *[...]/9J61/BuildRoot* folder with: `tar xzf ../../../hg/Roots/pd/PureFoundation.root.tar.gz`.
And go for a 5 round..
#### 5-pass
After trying again to build all projects, it appears that 6 additional projects have been successfully built:




Let's load them, and be prepare for pass six.
It is also plausible that many solutions and pseudo-solutions below will be needed for the next passes. Everything has been logged since the beginning, some useful `grep' sequences based on the available solutions against the log files could also be done in order to make them build.
#### 6-pass
Indeed, nothing more succeed at this stage.





Enjoy the number of error to fix..

`grep -i error Logs/*/*6 | wc -l`
`  196493`



`grep -i warning Logs/*/*6 | wc -l`
`   38007`


**Errata:**
it should be loaded with -load -headers:

for Y in `ls Packages/*hdrs*.tar.gz | awk -F "." '{print $1}' | sed 's/Packages///g'`; do
    darwinbuild -load -headers $Y
done


Let's first look the projects which do not have any binaryroot and cannot be built.
-   In green are the projects which have enough solution(s) available in order to built successfully the project (on 9J61)
-   
-   In red are the projects where source not available or impossible to build (e.g., CFNetwork on darwin 9).
-   



-AppleMacRISC4PE
-AppleOnboardAudio
-AppleUSBAudio
-AppleUSBCDCDriver
-AppleUSBIrDA
-BootCache
-BootX
-CFNetwork
-CPAN
-CPANInternal
-ChatServer

-CyrusIMAP
-DSPasswordServerPlugin
-DynamicPowerStep
-FastCGI
-FirewallTool
-IOATABlockStorage
-IOATAPIProtocolTransport
-IOBDStorageFamily
-IOFWDVComponents
-IOFireWireIP
-IOFireWireSerialBusProtocolTransport


-IOSCSIArchitectureModelFamily
-JavaScriptCore
-JavaScriptGlue
-Libc_debug
-Libc_profile

-OpenAL
-OpenDirectory
-OpenLDAP
-OpenSSH
-PyRSS2Gen
-RubyOnRails
-SecurityTool
-SpamAssassin
-Twisted
-TwistedWords
-TwistedXish
-VirtualAudioDriver
-WebCore
-X11fonts
-X11libs
-X11proto
-apache
-apache_mod_bonjour
-apache_mod_fastcgi
-apache_mod_hfs_apple
-apache_mod_perl
-apache_mod_php
-apache_mod_php4
-autofs
-cddafs
-clamav
-configd_executables
-configd_plugins

-cups
-disklabel
-efax
-efiboot
-gdb
-gnuserv
-gpt
-gssd
-gutenprint

-iodbc
-ipsec
-ipv6configuration
-isoutil

-libsecurity_agent
-libsecurity_apple_csp
-libsecurity_apple_cspdl
-libsecurity_apple_file_dl
-libsecurity_apple_x509_cl
-libsecurity_apple_x509_tp
-libsecurity_asn1
-libsecurity_authorization
-libsecurity_cdsa_plugin
-libsecurity_cdsa_utils
-libsecurity_checkpw
-libsecurity_cms
-libsecurity_codesigning
-libsecurity_dotmacdl
-libsecurity_filedb
-libsecurity_filevault
-libsecurity_keychain
-libsecurity_ldap_dl
-libsecurity_manifest
-libsecurity_mds
-libsecurity_ocspd
-libsecurity_pkcs12
-libsecurity_sd_cspdl
-libsecurity_smime
-libsecurity_ssl
-libsecurityd
-libstdcxx_SUPanWheat


-mDNSResponderSystemLibraries
-mailman
-msdosfs
-net_snmp

-notify

-ntp
-pam_modules
-passwordserver_saslkerberos

-portmap
-postfix
-pyOpenSSL
-pyobjc
-python
-python23
-python_dateutil
-python_modules
-ruby
-ruby_dnssd
-ruby_libxml

-security_certtool
-security_crlrefresh
-security_dotmac_tp
-security_ocspd
-security_privportserver
-security_systemkeychain
-securityd
-smb
-subversion
-svk
-syslog
-tcl
-tcl_ext
-tcl_tk




Let's make another pass (7th) again after loading all these built projects.
At this stage, the state of the buildroot is not "clean" anymore, some headers have been copied or linked manually from a location to another (and even from outside the buildroot sometimes), etc..
#### 7 pass
The results are really great, more and more projects are built again (see results of packageRoots):

AppleAPIC-13~7 AppleDisplays-1140.0.5~7 AppleFileSystemDriver-12~7 AppleHWSensor-190~7 AppleIntel8255x-19~7 AppleKeyLargo-172.3.1~7 AppleSMBIOS-38~7 AppleUSBAudio-264.2.10~7 BootCache-43.12~13 BootX-81~7 CF-476.18~7 DirectoryServiceMIG-514.25~7 IOATAFamily-201.0.1~7 IOAudioFamily-169.4.3~7 IOCDStorageFamily-39~7 IODVDStorageFamily-26~7 IOFireWireFamily-347.4.0~7 IOFireWireIP-177.4.0~7 IOFireWireSBP2-198.4.0~7 IOGraphics-305.14~7 IOI2CFamily-111.0.2~7 IOPCCardFamily-48~7 IOPCIFamily-110~7 IOStorageFamily-92.9~7 Libinfo-278.0.3~7 Libnotify-36~7 Libsyscall-1228.12.14~7 UserNotification-21~7 VirtualAudioDriver-258.3.1~7 diskdev_cmds-421.8~7 distcc-881~7 gpt-7~7 libresolv-25.0.2~7 libsecurity_checkpw-29159~7 portmap-26~7 shell_cmds-118~7 top-39~7

__
__
__Random notes:__ In fact we have a workaround since 9F33pd1 which will soon be used as many projects are related to the following problem(s) [...].
****

`/System/Library/Frameworks/Security.framework/Headers/SecBase.h:74: error: syntax error before 'SecKeychainAttrType'`
`/System/Library/Frameworks/Security.framework/Headers/SecBase.h:77: error: syntax error before '}' token`

`/System/Library/Frameworks/Security.framework/Headers/SecKeychain.h:78: error: syntax error before 'SecAuthenticationType'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychain.h:117: error: syntax error before 'SecProtocolType'`
**Projects impacted:**

DynamicPowerStep KerberosHelper OpenSSH SecurityTool apache_mod_bonjour bootp cddafs configd_executables ipsec ipv6configuration libsecurity_apple_x509_tp libsecurity_asn1 libsecurity_cdsa_utilities libsecurity_cdsa_utils libsecurity_cms libsecurity_dotmacdl libsecurity_filevault libsecurity_ldap_dl libsecurity_manifest libsecurity_pkcs12 libsecurity_smime libsecurity_ssl modemccl ppp samba security_certtool security_ocspd security_systemkeychain securityd


So let's use the workaround which consists of simply adding. This is a dirty workaround because nobody should alter any header files.
Let's go for the 8th round, we're not tired at all.
#### 8 pass
build build!


### 9 pass

o/
OpenSSH-95.1.5~9 cctools-667.3~9 cctools_ofiles-667.3~9 gssd-23~9 libdyld-97.1~9 libsecurity_agent-32091.1~9 libsecurity_ocspd-29518~9 mDNSResponderSystemLibraries-176.3~9 network_cmds-307.1.1~9 notify-16~9 remote_cmds-13.0.2~9 security_certtool-31828~9
..[...]

#### 10 pass
security_crlrefresh-31832~10

+--------------------------------------+--------------------------------------+
| <div style="text-align:center">      | <span                                |
|                                      | style="font-weight:bold">Security(d) |
| <span                                | and other related projects which not |
| style="font-weight:bold">Remaining   | yet build</span>                     |
| projects</span>                      |                                      |
|                                      |                                      |
| </div>                               |                                      |
|                                      |                                      |
| <span                                |                                      |
| style="font-weight:bold"></span>     |                                      |
| <div style="text-align:center">      |                                      |
|                                      |                                      |
| (estimation)                         |                                      |
|                                      |                                      |
| </div>                               |                                      |
+--------------------------------------+--------------------------------------+
| Image 9J6111pass.png                 | Image securitystuff.png              |
+--------------------------------------+--------------------------------------+

Below are errors related to the project described just above.

According to the map, we should probably begin to fix first :

libsecurity_cdsa_utilities
 which unblocks libsecurity_apple_x509_tp, libsecurity_apple_x509_cl, SecurityTool, libsecurity_cms,  libsecurity_ssl, libsecurity_smime,


Problematic point is all the project linked (depending) on a non available project.
#### 11-pass

After running another pass (11 iirc..), more projects are built:

AppleRS232Serial-130.2.7~11

AppleSCCSerial-132.4.2~11

AppleUSBCDCDriver-3212.4.1~11

AppleUSBIrDA-144.4.0~11

IOSerialFamily-32.2~11

SecurityTokend-32363~11

SmartCardServices-34733~11

disklabel-2~11

libsecurity_cdsa_client-32432~11

libsecurity_cssm-32993~11

libsecurity_filedb-32868~11

libsecurity_utilities-36433~16

Which satisfy dependency for:
libsecurity_mds
libsecurity_apple_file_dl
...
let's fix more and more..

After applying some patches and rebuild some dependents where their dependencies just have been patched, the picture looks like:
![](/img/developers/darwinbuild/troubleshooting/9J61pd1-n.png)


The state is beyond the 12th pass now..








------------------------------------------------------------------------

**Problem:** The Mac OS X platform is missing...

**Solution: **It is more than recommended to avoid using HFS+ as the filesystem of your BuildRoot volume with DarwinBuild (precisely Xcode in this case). An UFS disk image works, alternatively you can also *fool* Xcode using NFS as described [there](../../darwinbuild.html#TOC-Work-around-DarwinBuild-ticket-1). Also note that on Mac OS X 10.5, there is a bug in `hdiutil' which prevents to create large UFS disk image (around 12g max). The trick is to use a Tiger machine to create a larger image.
Example with an UFS disk image:

hdiutil create -size 30g -type UDIF -fs UFS -volname Builds -attach Builds.dmg

 The cause is Xcode 3.1 running in a chroot on not-UFS.
**Fixed: **This workaround is **no longer needed** since on the [Darwinbuild website](http://darwinbuild.macosforge.org/), we can read (news from 2009/04/17): "*The latest revision of trunk has support for sparsebundles and NFS Loopback in order to avoid the problems with xcodebuild inside of chroots. If you do not change the way you use darwinbuild, you will start seeing the sparsebundle storage. Nothing else is needed and Xcode-based projects will build on whatever filesyste**m you have.*"



**Solution:** `darwinbuild -load TargetConfig` (this will download a binary root)

------------------------------------------------------------------------
### AppleDisplay
darwinbuild AppleDisplay
#### 9J61 (ok)
****

`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:25:26: error: IOKit/system.h: No such file or directory`
`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:26:25: error: IOKit/IOLib.h: No such file or directory`
`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:27:38: error: IOKit/graphics/IODisplay.h: No such file or directory`
`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:28:39: error: IOKit/IODeviceTreeSupport.h: No such file or directory`
`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:29:36: error: IOKit/IOPlatformExpert.h: No such file or directory`
`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:30:49: error: IOKit/ndrvsupport/IONDRVFramebuffer.h: No such file or directory`
`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:31:29: error: IOKit/IOMessage.h: No such file or directory`
`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:32:38: error: IOKit/pwr_mgt/RootDomain.h: No such file or directory`
`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:33:26: error: IOKit/assert.h: No such file or directory`
`/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/AppleOnboardDisplay.cpp:36:20: error: stddef.h: No such file or directory`
**Solution:? **(resolved near pass 7)

**Problem:**` /SourceCache/AppleDisplays/AppleDisplays-1140.0.5/AppleOnboardDisplay/IVAD.h:27:29: error: libkern/OSTypes.h: No such file or directory`
**Solution:** ? (resolved near pass 7)
------------------------------------------------------------------------
### AppleMacRISC4PE
#### 9J61
**Problem:**

`MacRISC4PE.cpp:183: error: 'kUniNRevision3_2_1' was not declared in this scope`

`MacRISC4CPU.cpp:488: error: 'kUniNNormal' was not declared in this scope`

`MacRISC4CPU.cpp:551: error: 'kUniNSave' was not declared in this scope`
`MacRISC4CPU.cpp:557: error: 'kUniNSleep' was not declared in this scope`

`U3.cpp:91: error: 'kUniNVersion' was not declared in this scope`
`U3.cpp:93: error: 'kUniNVersion3' was not declared in this scope`
`U3.cpp:136: error: 'kU3ToggleRegister' was not declared in this scope`
`[...]`

`U3.cpp:1268: error: 'kU3API_DARTExcp' was not declared in this scope`
**Solution:** ?

**Problem:** `IOPlatformPlugins/IOPlatformPlugin.cpp:356: error: 'kIOPPluginForceUpdateKey' was not declared in this scope`
`IOPlatformPlugins/IOPlatformPlugin.cpp:357: error: 'kIOPPluginForceUpdateAllKey' was not declared in this scope`
`IOPlatformPlugins/IOPlatformPlugin.cpp:358: error: 'kIOPPluginForceSensorCurValKey' was not declared in this scope`
`IOPlatformPlugins/IOPlatformPlugin.cpp:359: error: 'kIOPPluginReleaseForcedSensorKey' was not declared in this scope`
`IOPlatformPlugins/IOPlatformPlugin.cpp:360: error: 'kIOPPluginForceCtrlTargetValKey' was not declared in this scope`
`IOPlatformPlugins/IOPlatformPlugin.cpp:361: error: 'kIOPPluginReleaseForcedControlKey' was not declared in this scope`
`IOPlatformPlugins/IOPlatformPlugin.cpp:362: error: 'kIOPPluginForceCtrlLoopMetaStateKey' was not declared in this scope`
`IOPlatformPlugins/IOPlatformPlugin.cpp:363: error: 'kIOPPluginReleaseForcedCtrlLoopKey' was not declared in this scope`
**Solution:** ?
------------------------------------------------------------------------
### AppleOnboardAudio
#### 9J61
**Problem:** `HALPlugin/AOAHALPlugin.h:44:41: error: CoreAudio/AudioDriverPlugIn.h: No such file or directory`
**Solution: ** ?
See <http://darwinbuild.macosforge.org/trac/ticket/82>
------------------------------------------------------------------------
### AppleRAID
#### 9J61
**Problem:** /SourceCache/AppleRAID/AppleRAID-3.0.19/AppleRAID.h:60:27: error: IOKit/IOTypes.h: No such file or directory/SourceCache/AppleRAID/AppleRAID-3.0.19/AppleRAID.h:61:29: error: IOKit/IOService.h: No such file or directory /SourceCache/AppleRAID/AppleRAID-3.0.19/AppleRAID.h:62:30: error: IOKit/IOWorkLoop.h: No such file or directory /SourceCache/AppleRAID/AppleRAID-3.0.19/AppleRAID.h:63:33: error: IOKit/IOEventSource.h: No such file or directory... etc
**Solution:** related to kernel headers and iokituser headers

**Problem:** /SourceCache/AppleRAID/AppleRAID-3.0.19/artest.c:38:30: error: MediaKit/MKMedia.h: No such file or directory
/SourceCache/AppleRAID/AppleRAID-3.0.19/artest.c:39:36: error: MediaKit/MKMediaAccess.h: No such file or directory
**Solution:** ???
------------------------------------------------------------------------
### AppleRS232Serial
#### 9J61
**Problem:** `AppleRS232Serial.cpp:31:39: error: IOKit/serial/IOSerialKeys.h: No such file or directory`

`AppleRS232Serial.h:86:45: error: IOKit/serial/IOSerialDriverSync.h: No such file or directory`
`AppleRS232Serial.h:87:50: error: IOKit/serial/IORS232SerialStreamSync.h: No such file or directory`
**Solution:** Fixed at between pass 10 and pass 11 with Apple16X50Serial fix

------------------------------------------------------------------------
### AppleUSBCDCDriver
#### 9J61 (ok)
**Problem:** /SourceCache/AppleUSBCDCDriver/AppleUSBCDCDriver-3212.4.1/AppleUSBCDC/Classes/AppleUSBCDC.cpp:47:39: error: IOKit/serial/IOSerialKeys.h: No such file or directory
/SourceCache/AppleUSBCDCDriver/AppleUSBCDCDriver-3212.4.1/AppleUSBCDC/Classes/AppleUSBCDC.cpp:48:45: error: IOKit/serial/IOSerialDriverSync.h: No such file or directory
/SourceCache/AppleUSBCDCDriver/AppleUSBCDCDriver-3212.4.1/AppleUSBCDC/Classes/AppleUSBCDC.cpp:49:50: error: IOKit/serial/IOModemSerialStreamSync.h: No such file or directory
/SourceCache/AppleUSBCDCDriver/AppleUSBCDCDriver-3212.4.1/AppleUSBCDC/Classes/AppleUSBCDC.cpp:50:50: error: IOKit/serial/IORS232SerialStreamSync.h: No such file or directory

**Solution:** Fixed at between pass 10 and pass 11 with Apple16X50Serial fix
------------------------------------------------------------------------
### AppleUSBIrDA
#### 9J61 (ok)
AppleUSBIrDA/AppleUSBIrDA.cpp:40:39: error: IOKit/serial/IOSerialKeys.h: No such file or directory
AppleUSBIrDA/AppleUSBIrDA.cpp:41:50: error: IOKit/serial/IOModemSerialStreamSync.h: No such file or directory
AppleUSBIrDA/AppleUSBIrDA.cpp:42:50: error: IOKit/serial/IORS232SerialStreamSync.h: No such file or directory
In file included from AppleUSBIrDA/AppleUSBIrDA.cpp:46:
AppleUSBIrDA/AppleUSBIrDA.h:27:45: error: IOKit/serial/IOSerialDriverSync.h: No such file or directory

**Solution:** Fixed at between pass 10 and pass 11 with Apple16X50Serial fix


------------------------------------------------------------------------
### Apple16X50Serial
#### 9J61 (ok)
**Problem:** `/SourceCache/Apple16X50Serial/Apple16X50Serial-19.3/Apple16X50UARTSync.h:31:64: error: IOKit/serial/IORS232SerialStreamSync.h: No such file or directory`

`/SourceCache/Apple16X50Serial/Apple16X50Serial-19.3/Apple16X50Queue.h:23:45: error: IOKit/serial/IOSerialStreamSync.h: No such file or directory`

`/SourceCache/Apple16X50Serial/Apple16X50Serial-19.3/Apple16X50PCCard.cpp:26:39: error: IOKit/serial/IOSerialKeys.h: No such file or directory`
**Solution:**

`chroot BuildRoot`
`mkdir /XCD/SY/Library/Frameworks/Kernel.framework/Versions/A/PrivateHeaders/IOKit/serial`
`cp SourceCache/IOSerialFamily/IOSerialFamily-32.2/IOSerialFamily.kmodproj/*h /XCD/SY/Library/Frameworks/Kernel.framework/Versions/A/PrivateHeaders/IOKit/serial `
then 

`** BUILD SUCCEEDED **`
`[...]`

`Apple16X50Serial - 6 files registered.`


------------------------------------------------------------------------
### BootCache
#### 9J61
**Problem:** `error: couldn't exec /XCD/loper/Library/Xcode/Plug-ins/CoreBuildTasks.xcplugin/Contents/Resources/copystrings: No such file or directory`
`This is related to the availability of ruby (copystrings is a ruby script)`.
**Solution: **to have ruby. **Please let us know if you have a solution.**
------------------------------------------------------------------------


### CF 

`darwinbuild CF`
#### 9J61
**Problem:** `CFMessagePort.c:38:28: error: bootstrap_priv.h: No such file or directory`
**Solution:** <span style="font-family:courier new"><span style="color:rgb(153,153,153)">darwinbuild launchd && darwinbuild -load launchd</span></span>
#### 9G55
**** `/usr/include/sys/stat.h:75:26: In file included from CFBundle.c:40error: Availability.h: No such file or directory`

/usr/include/sys/stat.h:75:26: error: Availability.h: No such file or directory

****
#### 9F33 (ok)
****

![](/img/developers/darwinbuild/troubleshooting/CF.png)

**Problem: **In fact, CF-lite appears to missing many functions. Although the CF-lite built just above is enough for [PureDarwin nano](../../../downloads/puredarwin-nano.html), it won't be sufficient in a full PureDarwin release since many vital daemons may use these missing functions. Some have been already patched or can be short-circuited with an empty body, but others clearly need some code inside their body.


For more information about the differences between the CF from Mac OS X and the CF-lite from DarwinBuild (the one we use) which explain why some expected symbols are missing, please take a look at [CF-lite](../../cf-lite.html) page.

This is a non exhaustive list of missing symbols found, from darwinbuild compilation or at runtime.

``
`com.apple.configd[28]: Referenced from: /System/Library/SystemConfiguration/PowerManagement.bundle/Contents/MacOS/PowerManagement `
`com.apple.configd[28]: Expected in: /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation
`
``


``
`  Referenced from: /System/Library/Frameworks/Security.framework/Versions/A/Security`
`  Expected in: /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation`



**
**
**Solution: **Build using the PureDarwin .plist (see [Integrating patches and additional sources](../patchfiles.html) for instructions), which includes patches to resolve most of these problems.
------------------------------------------------------------------------
### CFNetwork
#### 9J61
CFNetwork is not opensource in darwin 9 but in darwin 8. See <http://darwinbuild.macosforge.org/trac/ticket/16>

**problem:** `*** Fetching Sources ...`
`Downloading http://src.macosforge.org/Projects//CFNetwork-219.tar.gz ...`
`Downloading http://src.macosforge.org/Patches//CFNetwork-219.tar.gz ...`
`*** Copying Sources ...`
`tar (child): /Users/aladin/PureDarwin/darwinbuild/9J61/Sources/CFNetwork-219.tar.gz: Cannot open: No such file or directory`
`tar (child): Error is not recoverable: exiting now`
`tar: Child returned status 2`
`tar: Error exit delayed from previous errors`
`make: *** No rule to make target `install'.  Stop.`
**solution:** The version in the original *9J61.plist* seems to not match the available sources.
CFNetwork-129.20 &lt;- is the latest available at this time, 9J61pd1 is not yet out, but the version could be downgraded in any plist which inherits from 9J61.

**Problem:** cc1: error: unrecognized command line option "-Wno-precomp"
**Solution:** Patch baby patch!
****
------------------------------------------------------------------------

### CFOpenDirectory
`darwinbuild CFOpenDirectory`

__Notes:__ CFOpenDirectory is needed by `passwd'
#### 9J61 ??
#### 9G55
**`error: couldn't exec /XCD/loper/Library/Xcode/Plug-ins/CoreBuildTasks.xcplugin/Contents/Resources/copystrings: No such file or directory`**

**Solution: **related implicitly (but mandatory) to ruby as explained later below.
#### 9F33
**Problem:` `dyld: Library not loaded: /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation**
**Referenced from: /System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/OpenDirectory**
**Reason: image not found**
**Solution: **

------------------------------------------------------------------------

### CPAN
#### 9J61pd1
/usr/bin/perl ../xsubpps/xsubpp-5.8.0 -noprototypes -typemap /System/Library/Perl/5.8.8/ExtUtils/typemap  AppleEvents.xs &gt; AppleEvents.xsc && mv AppleEvents.xsc AppleEvents.c
cc -c -pipe -no-cpp-precomp -arch ppc -arch i386 -I/Developer/Headers/FlatCarbon/ -arch ppc -arch i386 -g -pipe -fno-common -DPERL_DARWIN -no-cpp-precomp -fno-strict-aliasing -Wdeclaration-after-statement -I/usr/local/include -fpascal-strings -O3   -DVERSION="1.32" -DXS_VERSION="1.32"  "-I/System/Library/Perl/5.8.8/darwin-thread-multi-2level/CORE"   AppleEvents.c

In file included from AppleEvents.xs:63:
../Carbon.h:67:20: error: In file included from AppleEvents.xs:63:
../Carbon.h:67:20: error: Events.h: No such file or directory
Events.h: No such file or directory
../Carbon.h:68:21: ../Carbon.h:68:21: error: error: Dialogs.h: No such file or directory
Dialogs.h: No such file or directory
../Carbon.h:69:19: ../Carbon.h:69:19:error:  Files.h: No such file or directoryerror: 
Files.h: No such file or directory
../Carbon.h:70:19: ../Carbon.h:70:19:error:  Types.h: No such file or directoryerror: 
Types.h: No such file or directory
../Carbon.h:71:31: ../Carbon.h:71:31:error:  ConditionalMacros.h: No such file or directoryerror: 
ConditionalMacros.h: No such file or directory

------------------------------------------------------------------------
### CPANInternal
9J61

Problem: WARNING: YAML: Prerequisite YAML isn't installed
WARNING: ExtUtils::ParseXS: Prerequisite ExtUtils::ParseXS isn't installed
WARNING: Archive::Tar: Prerequisite Archive::Tar isn't installed
ERRORS/WARNINGS FOUND IN PREREQUISITES.  You may wish to install the versions
 of the modules indicated above before proceeding with this installation.


------------------------------------------------------------------------
### DSPasswordServerPlugin
#### 9J61
**Problem:** `/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.h:56:24: error: sasl/sasl.h: No such file or directory`

/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.h:57:28: error: sasl/saslutil.h: No such file or directory


/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.h:65:40: error: DirectoryServiceCore/CBuff.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.h:66:44: error: DirectoryServiceCore/CDataBuff.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.h:67:49: error: DirectoryServiceCore/CAttributeList.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.h:68:47: error: DirectoryServiceCore/SharedConsts.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.h:69:45: error: DirectoryServiceCore/PluginData.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.h:70:50: error: DirectoryServiceCore/CDSServerModule.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.h:71:46: error: DirectoryServiceCore/CSharedData.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.mm:43:50: error: DirectoryServiceCore/ServerModuleLib.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.mm:45:42: error: DirectoryServiceCore/CRCCalc.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.mm:47:45: error: DirectoryServiceCore/CPlugInRef.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.mm:48:44: error: DirectoryServiceCore/DSCThread.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.mm:49:44: error: DirectoryServiceCore/CContinue.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.mm:50:51: error: DirectoryServiceCore/DSEventSemaphore.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.mm:51:51: error: DirectoryServiceCore/DSMutexSemaphore.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.mm:53:42: error: DirectoryServiceCore/DSUtils.h: No such file or directory
/SourceCache/DSPasswordServerPlugin/DSPasswordServerPlugin-208.5/CPSPlugIn.mm:54:47: error: DirectoryServiceCore/PrivateTypes.h: No such file or directory
**Solution:** See patch.

------------------------------------------------------------------------
### CyrusIMAP
#### 9J61pd1 (ok)

**Solution: **echo '
#!/bin/sh
echo "ProductName: PureDarwin"
echo "ProductVersion: 10.5.7"
echo "BuildVersion: 9J61"' &gt; BuildRoot/usr/bin/sw_vers
**Problem: **missing *sasl.h
**Solution:** mkdir -p BuildRoot/usr/include/sasl
cp BuildRoot/SourceCache/passwordserver_sasl/passwordserver_sasl-118.1/cyrus_sasl/include/*h BuildRoot/usr/include/sasl 


------------------------------------------------------------------------
### DirectoryService
darwinbuild DirectoryService
#### 9J61 ??
#### 9F33
**Problem:** `error: couldn't exec /usr/sbin/dtrace: No such file or directory`
**Solution:** Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then build dtrace first:
<span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild dtrace && darwinbuild -load dtrace && </span></span>`darwinbuild DirectoryService`

**Problem:** `/usr/sbin/dtrace -h -s Threads/dslockstat.d -o "/private/var/tmp/DirectoryService/DirectoryService-514.23.obj/DirectoryService.build/API Framework.build/DerivedSources/dslockstat.h"`
`dtrace(13670) malloc: *** error for object 0x116310: Non-aligned pointer being freed (2)`
`*** set a breakpoint in malloc_error_break to debug`
`dtrace(13670) malloc: *** error for object 0x116310: Non-aligned pointer being freed (2)`
`*** set a breakpoint in malloc_error_break to debug`
`dtrace(13670) malloc: *** error for object 0x116310: Non-aligned pointer being freed (2)`
`*** set a breakpoint in malloc_error_break to debug`
**Solution:** **Please, let us know if you have one.**

**Problem:** `/private/var/tmp/DirectoryService/DirectoryService-514.23.obj/DirectoryService.build/API Framework.build/DerivedSources/dslockstat.h:36: error: expected unqualified-id before 'long'`
`/private/var/tmp/DirectoryService/DirectoryService-514.23.obj/DirectoryService.build/API Framework.build/DerivedSources/dslockstat.h:36: error: expected `)' before 'long'`
`/private/var/tmp/DirectoryService/DirectoryService-514.23.obj/DirectoryService.build/API Framework.build/DerivedSources/dslockstat.h:38: error: expected unqualified-id before 'long'`
`/private/var/tmp/DirectoryService/DirectoryService-514.23.obj/DirectoryService.build/API Framework.build/DerivedSources/dslockstat.h:38: error: expected `)' before 'long'`
**Solution:** ...



------------------------------------------------------------------------
### DirectoryServiceDaemon
`darwinbuild ``DirectoryServiceDaemon`
#### 9J61
#### 9F33
**Problem:** `/SourceCache/DirectoryServiceDaemon/DirectoryService-514.23/PlugIns/Common/CDSAuthParams.h:28:37: error: PasswordServer/AuthFile.h: No such file or directory`

`/SourceCache/DirectoryServiceDaemon/DirectoryService-514.23/PlugIns/Common/CDSAuthParams.h:92: error: 'PWGlobalAccessFeatures' does not name a type`

`/SourceCache/DirectoryServiceDaemon/DirectoryService-514.23/PlugIns/Common/CDSAuthParams.h:93: error: 'PWGlobalMoreAccessFeatures' does not name a type`
**Solution:** `cp -R BuildRoot/System/Library/PrivateFrameworks/PasswordServer.framework BuildRoot/XCD/SY/Library/PrivateFrameworks`

**Problem:** `/SourceCache/DirectoryServiceDaemon/DirectoryService-514.23/Server/DirServiceMain.cpp:61:25: error: XSEventPort.h: No such file or directory`

****


------------------------------------------------------------------------



### FastCGI
#### 9J61
(cd gems && /usr/bin/gem install --install-dir /private/var/tmp/FastCGI/FastCGI-4.root/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/gems/1.8 --local --include-dependencies --rdoc fcgi -- with-fcgi-dir=/private/var/tmp/FastCGI/FastCGI-4.root/usr)
/bin/sh: /usr/bin/gem: /System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/bin/ruby: bad interpreter: No such file or directory
make[1]: *** [install-ruby-binding] Error 126


------------------------------------------------------------------------
### ICU (ok)
#### 9J61 (ok)
see n-pass.
#### 9F33pd1 (ok)
Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then:

darwinbuild -init 9F33pd1

<span style="font-family:courier new;font-size:12px"><span style="font-family:Arial;font-size:13px">The plist file above contains a workaround that tend to avoid an error related to <http://darwinbuild.macosforge.org/trac/ticket/38> .</span></span>

------------------------------------------------------------------------

### IOATAPIProtocolTransport
#### 9J61
Problem: IOATAPIProtocolTransport.cpp:33:50: error: IOKit/scsi/SCSICommandOperationCodes.h: No such file or directory

IOATAPIProtocolTransport.cpp:34:33: error: IOKit/scsi/SCSITask.h: No such file or directory
IOATAPIProtocolTransport.cpp:35:107: error: IOKit/scsi/SCSITaskDefinition.h: No such file or directory

IOATAPIProtocolTransport.h:50:51: error: IOKit/storage/ata/IOATAStorageDefines.h: No such file or directory
IOATAPIProtocolTransport.h:53:47: error: IOKit/scsi/IOSCSIProtocolServices.h: No such file or directory

------------------------------------------------------------------------
### IOBDBlockStorageDevice
#### 9J61
**Problem:** /SourceCache/IOBDStorageFamily/IOBDStorageFamily-6/IOBDBlockStorageDevice.cpp:24:50: error: IOKit/storage/IOBDBlockStorageDevice.h: No such file or directory

/SourceCache/IOBDStorageFamily/IOBDStorageFamily-6/IOBDBlockStorageDriver.cpp:24:50: error: IOKit/storage/IOBDBlockStorageDriver.h: No such file or directory
/SourceCache/IOBDStorageFamily/IOBDStorageFamily-6/IOBDBlockStorageDriver.cpp:25:37: error: IOKit/storage/IOBDMedia.h: No such file or directory
------------------------------------------------------------------------
### IOFireWireSerialBusProtocolTransport
9J61

**Problem:** /SourceCache/IOFireWireSerialBusProtocolTransport/IOFireWireSerialBusProtocolTransport-152.0.2/IOFireWireSerialBusProtocolTransport.h:42:47: error: IOKit/scsi/IOSCSIProtocolServices.h: No such file or directory
Where can we found it? except in the sdk.

------------------------------------------------------------------------
### IOHIDFamily
#### 9J61
?
#### 9F33pd1


Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then:
darwinbuild -init 9F33pd1

The plist file above contains some patches that tend to avoid most of the errors just below.



darwinbuild IOHIDFamily


**Problem:** `/System/Library/Frameworks/IOKit.framework/PrivateHeaders/hid/IOHIDLibPrivate.h:30:42: error: IOKit/hid/IOHIDLibUserClient.h: No such file or directory`

**Pseudo-solution:** Headers from IOKitUser appear to be needed:

`cp BuildRoot/XCD/SY/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/hid/IOHIDLibUserClient.h BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/hid/`


**Problem: **`/SourceCache/IOHIDFamily/IOHIDFamily-258.3/IOHIDLib/IOHIDDeviceClass.cpp:455: error: 'nil' was not declared in this scope`

**Problem: **`/SourceCache/IOHIDFamily/IOHIDFamily-258.3/IOHIDLib/IOHIDQueueClass.cpp:447: error: 'nil' was not declared in this scope`


**Solution:** `#include <objc/objc.h>`


**Problem:**`/SourceCache/IOHIDFamily/IOHIDFamily-258.3/hidd/hidd.c:28: error: 'IOHIDEventSystemRef' undeclared (first use in this function)`
**Solution:** **?**



``
**Solution:** **?**



------------------------------------------------------------------------

****
### IOKitUser
`darwinbuild IOKitUser`



**Problem:** The framework is registered in /XCD/SY:
`40755 0 0 0 ./XCD/SY/Library/Frameworks/IOKit.framework`
****
and replace XCD/SY in the binary with /System for all occurences.
Then:


mv Roots/IOKitUser/IOKitUser-388.2.1.root~28/XCD/SY/Library/ 
mkdir Roots/IOKitUser/IOKitUser-388.2.1.root~28/System 
mv Roots/IOKitUser/IOKitUser-388.2.1.root~28/XCD/SY/Library/ Roots/IOKitUser/IOKitUser-388.2.1.root~28/System 
rm -R Roots/IOKitUser/IOKitUser-388.2.1.root~28/XCD/

After in the chrooted buildroot:
file /System/Library/Frameworks/IOKit.framework/Versions/A/IOKit
/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit: Mach-O universal binary with 4 architectures
/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit (for architecture i386): Mach-O dynamically linked shared library i386
/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit (for architecture x86_64): Mach-O 64-bit dynamically linked shared library x86_64
/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit (for architecture ppc7400): Mach-O dynamically linked shared library ppc
/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit (for architecture ppc64): Mach-O 64-bit dynamically linked shared library ppc64
and 

otool -L /System/Library/Frameworks/IOKit.framework/Versions/A/IOKit
/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit:
 /System/Library/Frameworks/IOKit.framework/Versions/A/IOKit (compatibility version 1.0.0, current version 275.0.0)
 /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)
 /usr/lib/libz.1.dylib (compatibility version 1.0.0, current version 1.2.3)
 /usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)
 /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.4)
Instead of 
otool -L /XCD/SY/Library/Frameworks/IOKit.framework/Versions/A/IOKit 
/XCD/SY/Library/Frameworks/IOKit.framework/Versions/A/IOKit:
 /XCD/SY/Library/Frameworks/IOKit.framework/Versions/A/IOKit (compatibility version 1.0.0, current version 275.0.0)
 /XCD/SY/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.18.0)
 /XCD/lib/libz.1.dylib (compatibility version 1.0.0, current version 1.2.3)
 /XCD/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)
 /XCD/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.4)

****


#### 9J61
PureFoundation need to be added (for `arch' dep).
**Problem:** `pbxcp: IOAccelSurfaceControl.h: No such file or directory`

`pbxcp: IOGraphicsLibPrivate.h: No such file or directory`

**Solution:** `cp -R BuildRoot/SourceCache/IOKitUser/IOKitUser-388.53.11/graphics.subproj/*h BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/graphics`
`cp -R BuildRoot/private/var/tmp/IOKitUser/IOKitUser-388.53.11.sym/BuiltProducts/include/IOKit/graphics/IO* BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/graphics`


**Problem:** 
**Solution:** `darwinbuild AppleDisplay` (it could fail to build, but anyway we need the header file)
then `cp ./BuildRoot/private/var/tmp/AppleDisplays/AppleDisplays-1140.0.5.root/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/graphics/IODisplayProductIDs.h BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/graphics`


**Problem:**


`#ifndef kNilOptions 
`    `#define kNilOptions 0
#endif`


... follow solutions and pseudo-solutions as below. 
#### 9F33pd1 (+ppc +ppc64 +x86 +x86_64)


To build isoutil on 9J61, iokituser for i386+ppc in 9F33pd1 need to be build.. + some regular solutions available below needs to be applied..
Also i386 specific arch has been removed from 9F33pd1 of IOKitUser project.


Problems:
cp -R BuildRoot/SourceCache/IOGraphics/IOGraphics-305.14/IOGraphicsFamily/IOKit/graphics/* BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/graphics/


cp BuildRoot/XCD/SY/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/storage/RAID/AppleRAIDUserLib.h BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/storage/RAID


cp /Users/aladin/PureDarwin/darwinbuild/9J61/.build/buildroot.nfs/SourceCache/AppleDisplays/AppleDisplays-1140.0.5/*h BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/graphics 


cp -R /Users/aladin/PureDarwin/darwinbuild/9J61/.build/buildroot.nfs/SourceCache/IOGraphics/IOGraphics-305.14/IOGraphicsFamily/IOKit/i2c BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/ 


**Problem: **/SourceCache/IOKitUser/IOKitUser-388.2.1/pwr_mgt.subproj/IOPMEnergyPrefs.c:36:31: error: servers/bootstrap.h: No such file or directory
According to DTrace:
  1  17720                       open:entry cc1 /private/var/tmp/IOKitUser/IOKitUser-388.2.1.sym/BuiltProducts/include/servers/bootstrap.h
  1  17720                       open:entry cc1 /private/var/tmp/IOKitUser/IOKitUser-388.2.1.obj/IOKitUser.build/DerivedSources/servers/bootstrap.h
  1  17720                       open:entry cc1 /System/Library/Frameworks/System.framework/PrivateHeaders/servers/bootstrap.h
  1  17720                       open:entry cc1 /private/var/tmp/IOKitUser/IOKitUser-388.2.1.obj/IOKitUser.build/IOKit.build/DerivedSources/servers/bootstrap.h
  1  17720                       open:entry cc1 /usr/local/include/servers/bootstrap.h
  1  17720                       open:entry cc1 /usr/lib/gcc/powerpc-apple-darwin9/4.0.1/include/servers/bootstrap.h
  1  17720                       open:entry cc1 /usr/include/servers/bootstrap.h

**Solution:** cp -R /Developer/SDKs/MacOSX10.5.sdk/usr/include/servers/ BuildRoot/usr/include

cp /Developer/SDKs/MacOSX10.5.sdk/usr/include/servers/* BuildRoot/usr/include/servers/



At the end: `** BUILD SUCCEEDED **`
o// 
That helps to satisfy isoutil on 9J61 per example.
`file':

`XCD/SY/Library/Frameworks/IOKit.framework/IOKit (for architecture ppc7400):` `Mach-O dynamically linked shared library ppc`
`XCD/SY/Library/Frameworks/IOKit.framework/IOKit (for architecture ppc64):` `Mach-O 64-bit dynamically linked shared library ppc64`
`XCD/SY/Library/Frameworks/IOKit.framework/IOKit (for architecture i386):` `Mach-O dynamically linked shared library i386`
`XCD/SY/Library/Frameworks/IOKit.framework/IOKit (for architecture x86_64):` `Mach-O 64-bit dynamically linked shared library x86_64`



#### 9F33pd1 (ok)

Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then:
darwinbuild -init 9F33pd1

The plist file above contains some patches that tend to avoid most of the errors just below.
In order to build IOKitUser, you also need to alter your *BuildRoot* directory, a minimalist script and some patches are available [here](http://code.google.com/p/puredarwin/source/browse/#svn/trunk/scripts).

./pd_injectbuildroot /Volumes/Builds/9F33/BuildRoot/


Not sure if it is needed or not:

darwinbuild -headers IOKitUser


Now, prepare coffee.

darwinbuild IOKitUser




dyld: Library not loaded: /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation
  Referenced from: /usr/bin/arch
  Reason: image not found
gcc-4.0: Invalid arch name : -D__MACH30__
`mig: fatal: "<no name yet>", line -1: no SubSystem declaration`
****
**mv /usr/bin/arch /usr/bin/arch.origin**
**echo 'uname -p' > /usr/bin/arch**
**chmod +x /usr/bin/arch**

**Alternative solution:** [PureFoundation](../../../purefoundation.html) can be added manually in the buildroot to satisfy dependency referenced to Foundation.framework.
`root@europa:/Volumes/Builds/``9G55/BuildRoot# mv PureFoundation/Foundation.``framework System/Library/Frameworks`
`root@europa:/Volumes/Builds/``9G55/BuildRoot# chroot .
europa# arch
NSObject +load
i386`




****

**Also:** The latest builds of the patched CFLite which accompanies PureFoundation include an implementation of CFNotificationCenter.


**Problem:** ``
`pbxcp: IOAccelSurfaceControl.h: No such file or directory`
**Problem:** ``
pbxcp: IOGraphicsLibPrivate.h: No such file or directory
**Solution:** `mkdir -p `**BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/graphics**
Then copy to the directory created just above from:
-   `BuildRoot/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/*.h`
-   BuildRoot/private/var/tmp/IOKitUser/IOKitUser-388.2.1.root/XCD/SY/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/graphics/*.h
-   `BuildRoot/private/var/tmp/IOKitUser/IOKitUser-388.2.1.sym/BuiltProducts/include/IOKit/graphics/*.h`

**TODO: **clean location please..


**** /XCD/loper/usr/bin/mig: line 147: : command not found

darwinbuild -load bootstrap_cmds
cp BuildRoot/usr/bin/arch BuildRoot/usr/bin/mig BuildRoot/XCD/loper/usr/bin/
mkdir BuildRoot/XCD/loper/usr/libexec/
cp BuildRoot/usr/libexec/migcom BuildRoot/XCD/loper/usr/libexec



**Problem**
`/System/Library/Frameworks/Security.framework/Headers/SecBase.h:63: error: syntax error before 'SecKeychainAttrType'`
`/System/Library/Frameworks/Security.framework/Headers/SecBase.h:74: error: syntax error before 'SecKeychainAttrType'`
`/System/Library/Frameworks/Security.framework/Headers/SecBase.h:77: error: syntax error before '}' token`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychain.h:78: error: syntax error before 'SecAuthenticationType'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychain.h:117: error: syntax error before 'SecProtocolType'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychain.h:526: error: syntax error before 'SecProtocolType'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychain.h:549: error: syntax error before 'SecProtocolType'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychainItem.h:45: error: syntax error before 'SecItemClass'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychainItem.h:75: error: syntax error before 'SecItemAttr'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychainItem.h:186: error: syntax error before 'itemClass'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychainItem.h:211: error: syntax error before 'SecItemClass'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychainItem.h:232: error: syntax error before 'SecItemClass'`
`/System/Library/Frameworks/Security.framework/Headers/SecKeychainSearch.h:55: error: syntax error before 'SecItemClass'`
****Comment all the problematic lines in `/System/Library/Frameworks/Security.framework/Headers/*h`
**Solution:** Add in SecBase.h `#include <CarbonCore/MacTypes.h>`


**Problem: /SourceCache/IOKitUser/IOKitUser-388.2.1/IOKitLib.c:347: error: 'kNilOptions' undeclared (first use in this function)**

Psuedo-Solution: Patch *BuildRoot/SourceCache/IOKitUser/IOKitUser-388.2.1/IOKitLib.h* with

`#ifndef kNilOptions 
`    `#define kNilOptions 0
#endif`

**Solution:** Add in SecBase.h #include <CarbonCore/MacTypes.h>



**Problem:** It seems related to [FourCC](http://en.wikipedia.org/wiki/FourCC) (and Carbon?)
**/private/var/tmp/IOKitUser/IOKitUser-388.2.1.sym/BuiltProducts/include/IOKit/graphics/IOGraphicsInterface.h:92: error: syntax error before 'FourCharCode'**
**Pseudo-Solution: **Comment line 91 and line 92 in BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/Headers/graphics/IOGraphicsInterface.h as 

`//    IOReturn (*CopyCapabilities)`
`//        (void *thisPointer, FourCharCode select, CFTypeRef * capabilities);`
**TODO:** FourCharCode needs to be included instead of disabled, there is a definition somewhere to include in the proper way at the right place


**Problem: /SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/GetSymbolFromPEF.h:65: error: syntax error before 'LogicalAddress'**
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/GetSymbolFromPEF.h:65: warning: no semicolon at end of struct or union`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/GetSymbolFromPEF.h:183: error: syntax error before 'LogicalAddress'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/GetSymbolFromPEF.h:193: error: syntax error before 'thePEFPtr'`
****Replace the unknown types with "`void *`", recreate missing variable declaration.


****

`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:136: error: 'sectionHeaderPtr' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:136: error: (Each undeclared identifier is reported only once`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:136: error: for each function it appears in.)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:142: error: 'nil' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:148: error: 'thePEFPtr' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:294: error: 'theData' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:296: error: 'noErr' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:300: error: 'Ptr' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:300: error: syntax error before 'originalUnpackBuffer'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:315: error: syntax error before 'thePEFPtr'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:318: error: invalid storage class for function 'GetSymbolFromPEF'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:319: error: 'inSymbolName' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:331: error: 'LogicalAddress' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:331: error: syntax error before 'expandedDataPtr'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:338: error: dereferencing pointer to incomplete type`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:342: error: dereferencing pointer to incomplete type`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:347: error: 'theSymbolPtr' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:354: error: dereferencing pointer to incomplete type`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:358: error: invalid application of 'sizeof' to incomplete type 'ContainerHeader' `
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:410: error: invalid application of 'sizeof' to incomplete type 'ContainerHeader' `
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:413: error: 'expandedDataPtr' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:437: error: 'theSymbolSize' undeclared (first use in this function)`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:444: error: syntax error before 'expandedDataPtr'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:454: error: syntax error before 'thePEFPtr'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:455: error: invalid storage class for function 'GetPEFLen'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:465: error: dereferencing pointer to incomplete type`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:470: error: dereferencing pointer to incomplete type`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:475: error: invalid use of undefined type 'struct ContainerHeader'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:477: error: dereferencing pointer to incomplete type`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:496: error: invalid storage class for function 'SymbolCompare'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:548: error: invalid storage class for function 'ExaminePEF'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:645: error: syntax error before 'LogicalAddress'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:727: error: invalid storage class for function 'PEFExamineFile'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:793: error: invalid storage class for function '_PEFExamineFile'`
`/SourceCache/IOKitUser/IOKitUser-388.2.1/graphics.subproj/PEFSupport.c:810: error: invalid storage class for function 'PEFExamineBundle'`
**Pseudo-Solution: **Replace the unknown types with "`void *`", recreate missing variable declaration.




****
**Pseudo-Solution: **Comment at line 352 in MacTypes.h

`//enum {`
`//  kNilOptions                   = 0`
`//};`

**TODO:** This looks like what we need just above.. what a paradox.



****
**Pseudo-Solution: **Feed the empty file with a subsystem declaration as:

`subsystem IOHIDEventSystem 71000;`

**TODO:** What should we really do?



****
**Solution: `chroot BuildRoot`**
**mkdir -p /AppleInternal/XCD/loper**
`ln -s /usr/local/bin/seg_addr_table /AppleInternal/XCD/loper/`


**Problem:** Ruby is (implicitly) missing:
`error: couldn't exec /XCD/loper/Library/Xcode/Plug-ins/CoreBuildTasks.xcplugin/Contents/Resources/copyplist: No such file or directory`

`error: couldn't exec /XCD/loper/Library/Xcode/Plug-ins/CoreBuildTasks.xcplugin/Contents/Resources/copystrings: No such file or directory`
****
`cp /System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/libruby.1.dylib BuildRoot/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/libruby.1.dylib`
**
**
**Problem:` `/XCD/loper/Library/Xcode/Plug-ins/CoreBuildTasks.xcplugin/Contents/Resources/copyplist:15:in `require': no such file to load -- optparse (LoadError)**
`/XCD/loper/Library/Xcode/Plug-ins/CoreBuildTasks.xcplugin/Contents/Resources/copystrings:16:in `require': no such file to load -- optparse (LoadError)`
****

Here, compilation pseudo-success for the first time after 94 attempts... o/

Copying IOKitUser from /Volumes/Builds/9F33/Roots/IOKitUser/IOKitUser-388.2.1.root~95 ...


`IOKitUser - 70 files registered.`



__Notes:__ Do not alter the prototype of functions, or you will end with undefined symbols at linking as:
Undefined symbols:
`  "_GetSymbolFromPEF", referenced from:`
`      __PEFExamineFile in PEFSupport.o`
`      __PEFExamineFile in PEFSupport.o`
`  "_GetPEFLen", referenced from:`
`      __PEFExamineFile in PEFSupport.o`


**Problem: **
`/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit:`
 `/XCD/SY/Library/Frameworks/IOKit.framework/Versions/A/IOKit (compatibility version 1.0.0, current version 275.0.0)`
 ``
 `/usr/lib/libz.1.dylib (compatibility version 1.0.0, current version 1.2.3)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)`

****

/System/Library/Frameworks/CoreFoundation/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)

Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then rebuild CF:

<span style="font-family:courier new"><span style="font-size:12px">darwinbuild -init 9F33pd1 && darwinbuild CF && darwinbuild -load CF</span></span>
The plist file above contains some patches that tend to avoid most of the errors just below.
After recompilation of CF, dependency is fixed:

`/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)`
**Next solution: **See <http://darwinbuild.macosforge.org/trac/ticket/41#comment:1> / [rdar://problem/6488974](http://rdar://problem/6488974)
![](/img/developers/darwinbuild/troubleshooting/IOKitUser.png)







<span style="font-family:Helvetica;font-size:12px"><span style="font-size:13px"><http://darwinbuild.macosforge.org/trac/ticket/9></span></span>

<span style="font-family:Helvetica;font-size:12px"><span style="font-size:13px"><http://darwinbuild.macosforge.org/trac/ticket/17></span></span>

<span style="font-family:Helvetica"><span style="font-family:Arial"><http://darwinbuild.macosforge.org/trac/ticket/41#comment:1></span></span>

[rdar://problem/6488974](http://rdar://problem/6488974)

------------------------------------------------------------------------
### IOKitTools
#### 9J61 (ok)
See the n-pass + IOKitUser stories..


**Problem: **`/SourceCache/IOKitTools/IOKitTools-76/ioreg.tproj/ioreg.c:25:78: error: IOKit/IOCFSerialize.h: No such file or directory`

`/SourceCache/IOKitTools/IOKitTools-76/ioreg.tproj/ioreg.c:26:77: error: IOKit/IOKitLib.h: No such file or directory`

`/SourceCache/IOKitTools/IOKitTools-76/ioreg.tproj/ioreg.c:27:82: error: IOKit/IOKitLibPrivate.h: No such file or directory`

**Solution:** `cp -R BuildRoot/XCD/SY/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders/* BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/PrivateHeaders`

`cp -R BuildRoot /XCD/SY/Library/Frameworks/IOKit.framework/Versions/A/Headers/* BuildRoot/System/Library/Frameworks/IOKit.framework/Versions/A/Headers`
------------------------------------------------------------------------

### Libc
#### 9J61pd1

**Problem:** /private/var/tmp/Libc/Libc-498.1.7.sym/include/plockstat.h:116: error: syntax error before '*' token
**Solution:** patch plockstat.h "on the fly" (comments error lines). It is generated via DTrace it seems at compilation time, and all error are some prototypes without name, only the parameters (e.g., (int a, int b..) instead of fctname(int a, int b..)).

+ see patch


------------------------------------------------------------------------
### Libc_debug


#### 9J61pd1
**Problem: sh: line 2: 58568 Trace/BPT trap          dtrace -o /private/var/tmp/Libc_debug/Libc_debug-498.1.7.sym/include/plockstat.h -C -h -s /SourceCache/Libc_debug/Libc-498.1.7/pthreads/plockstat.d**

*** Error code 133
1 error

------------------------------------------------------------------------
### Libc_profile

#### 9J61pd1
**Problem:** sh: line 2: 60868 Trace/BPT trap          dtrace -o /private/var/tmp/Libc_profile/Libc_profile-498.1.7.sym/include/plockstat.h -C -h -s /SourceCache/Libc_profile/Libc-498.1.7/pthreads/plockstat.d

*** Error code 133
1 error
*** Error code 2
1 error
*** Error code 2
------------------------------------------------------------------------

### Libsystem
****
darwinbuild Libsystem
#### 9J61 ?
#### 9F33
**Problem:** `ar: libc-partial_debug.a is a fat file (use libtool(1) or lipo(1) and ar(1) on it)`

`ar: libc-partial_debug.a: Inappropriate file type or format`

**Solution:** `lipo BuildRoot/usr/local/lib/system/libc-partial_debug.a -thin i386 -output libc-partial_debug.a`

`mv libc-partial_debug.a BuildRoot/usr/local/lib/system/libc-partial_debug.a`





**Problem:** ar: libsyscall_debug.a is a fat file (use libtool(1) or lipo(1) and ar(1) on it)

ar: libsyscall_debug.a: Inappropriate file type or format

**Solution:** lipo BuildRoot/usr/local/lib/system/libsyscall_debug.a -thin i386 -output libsyscall_debug.a

mv libsyscall_debug.a BuildRoot/usr/local/lib/system/libsyscall_debug.a


**Problem:** ar: libc-partial.a is a fat file (use libtool(1) or lipo(1) and ar(1) on it)

ar: libc-partial.a: Inappropriate file type or format

**Solution:** lipo BuildRoot/usr/local/lib/system/libc-partial.a -thin i386 -output libc-partial.a

mv libc-partial.a BuildRoot/usr/local/lib/system/libc-partial.a


**Problem:** ar: libsyscall.a is a fat file (use libtool(1) or lipo(1) and ar(1) on it)

ar: libsyscall.a: Inappropriate file type or format

**Solution:** lipo BuildRoot/usr/local/lib/system/libsyscall.a -thin i386 -output libsyscall.a

mv libsyscall.a BuildRoot/usr/local/lib/system/libsyscall.a


**Problem:** ar: libc-partial_profile.a is a fat file (use libtool(1) or lipo(1) and ar(1) on it)

ar: libc-partial_profile.a: Inappropriate file type or format

**Solution:** lipo BuildRoot/usr/local/lib/system/libc-partial_profile.a -thin i386 -output libc-partial_profile.a

mv libc-partial_profile.a BuildRoot/usr/local/lib/system/libc-partial_profile.a


**Problem:** ar: libsyscall_profile.a is a fat file (use libtool(1) or lipo(1) and ar(1) on it)

ar: libsyscall_profile.a: Inappropriate file type or format

**Solution:** lipo BuildRoot/usr/local/lib/system/libsyscall_profile.a -thin i386 -output libsyscall_profile.a

mv libsyscall_profile.a BuildRoot/usr/local/lib/system/libsyscall_profile.a


**Problem:** `ld: library not found for -llaunch`
****
See <http://darwinbuild.macosforge.org/trac/ticket/10>
------------------------------------------------------------------------
### NFS
#### 9J61 (ok)
**Problems:**` /SourceCache/NFS/NFS-25.2/showmount/mshow.c:31:20: error: dns_sd.h: No such file or directory`
`/SourceCache/NFS/NFS-25.2/showmount/mshow.c:31:20: error: dns_sd.h: No such file or directory`
**Solution:** `cp -R /Developer/SDKs/MacOSX10.5.sdk/usr/include/dns* BuildRoot/usr/include`

**Problem:** `/SourceCache/NFS/NFS-25.2/nfsd/main.c:86:20:/SourceCache/NFS/NFS-25.2/nfsd/main.c:86:20:  error: error: launch.h: No such file or directorylaunch.h: No such file or directory`
**Solution: **`cp /Users/aladin/PureDarwin/darwinbuild/9J61/.build/buildroot.nfs/private/var/tmp/launchd_libs/launchd_libs-258.22.root/usr/include/* BuildRoot/usr/include`

Then !


`BUILD TIME: 0h 0m 14s`
`EXIT STATUS: 0`
`NFS - 25 files registered.`




------------------------------------------------------------------------


### PowerManagement
#### 9J61
Problem: 
/SourceCache/PowerManagement/PowerManagement-158.10/AppleSmartBatteryManager/AppleSmartBatteryManager.h:28:43: error: IOKit/smbus/IOSMBusController.h: No such file or directory
Solution: ? Headers seems not available on macosx too.
See <http://darwinbuild.macosforge.org/trac/ticket/80>



------------------------------------------------------------------------



### Security
`darwinbuild Security`
#### 9J61?
#### 9F33
****
**[...]**
**2008-10-20 06:32:44.589 xcodebuild[65272:713] [MT] ASSERTION FAILURE in /SourceCache/DevToolsBase/DevToolsBase-1114/pbxcore/SpecificationTypes/XCPlatformSpecification.m:421**
**Details:  The Mac OS X platform is missing - cannot set a default platform.**
****
****





**** generateErrStrings.mm:5:35: error: Foundation/Foundation.h: No such file or directory
**** **Please, let us know if you have one. **Since Foundation is not part of Darwin, we need to patch the source so that it doesn't need Foundation any more (Sometimes older versions of the same source can give a hint).



![](/img/developers/darwinbuild/troubleshooting/Security.png)

------------------------------------------------------------------------



### SecurityTool
#### 9J61
/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h: In static member function 'static void Security::MacOSError::check(OSStatus)':
/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h:103: error: 'noErr' was not declared in this scope
/usr/local/SecurityPieces/Frameworks/security_cdsa_utilities.framework/Headers/cssmdbname.h: In member function 'bool Security::DbName::operator&lt;(const Security::DbName&) const':
/usr/local/SecurityPieces/Frameworks/security_cdsa_utilities.framework/Headers/cssmdbname.h:90: error: 'nil' was not declared in this scope


security.c:62:34: error: security_asn1/secerr.h: No such file or directory



------------------------------------------------------------------------
### SystemStubs
#### 9J61 (ok)
#### 9F33 (ok)

**Problem: **`Error: couldn't exec /XCD/loper/usr/bin/libtool: No such file or directory`

**Solution: **`cp BuildRoot/usr/bin/libtool BuildRoot/XCD/loper/usr/bin/`



------------------------------------------------------------------------

### TargetConfig
`darwinbuild TargetConfig`
#### 9J61 (ok)
#### 9F33pd1 (ok)
**Problem:** *CoreFoundation* has no *.framework* extension.

**dyld: Library not loaded: /System/Library/Frameworks/CoreFoundation/Versions/A/CoreFoundation**



****

/System/Library/Frameworks/CoreFoundation/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)

Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then rebuild CF:

<span style="font-family:courier new"><span style="font-size:12px">darwinbuild -init 9F33pd1 && darwinbuild CF && darwinbuild -load CF</span></span>
The plist file above contains some patches that tend to avoid most of the errors just below.
After recompilation of CF, dependency is fixed:

/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)




Since *TargetConfig* is available and can be built, we will fix `tconf' with the right framework pathname instead of using a symbolic link or copying the framework.
`darwinbuild TargetConfig`
`darwinbuild -load TargetConfig`

Now tconf is linked to the correct framework:
otool -L BuildRoot/usr/local/bin/tconf 
BuildRoot/usr/local/bin/tconf:

 /usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)
 /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)
So we can remove the previous temporary CoreFoundation directory:
rm -fR BuildRoot/System/Library/Frameworks/CoreFoundation

------------------------------------------------------------------------

### WebCore
#### 9J61
make: *** No rule to make target `JSEventTargetBase.lut.h', needed by `all'.  Stop.


------------------------------------------------------------------------
### at_cmds 
#### 9J61pd1 (ok)
**Problem:** appletalk.c:44:29: error: SystemIntegrity.h: No such file or directory 
**Solution:** **excellent project option**, which helps us to easily make a patch, it is almost like we do not have the need(s) to bother about some side effects (consequences of the patch) because the developers have the big picture of their project. It's a real thank you.
 cf the src: 


------------------------------------------------------------------------
### autofs
#### 9J61
**Problem: **/SourceCache/autofs/autofs-109.8/autofsd/autofsd.c:36:43: error: CoreFoundation/CoreFoundation.h: No such file or directory
**Solution:** 

------------------------------------------------------------------------




### bootp

#### 9J61
**Problem:** /XCD/loper/usr/bin/gcc-4.0 -x c -arch ppc -fmessage-length=0 -pipe -Wno-trigraphs -fpascal-strings -fasm-blocks -Os -mdynamic-no-pic -mtune=G4 -fvisibility=hidden -mmacosx-version-min=10.5 -gdwarf-2 -I/private/var/tmp/bootp/bootp-170.1.obj/bootp.build/bootpd.build/bootpd.hmap -Wall -Wno-four-char-constants -Wno-unknown-pragmas -F/private/var/tmp/bootp/bootp-170.1.sym/BuiltProducts -F/XCD/SY/Library/PrivateFrameworks -I/private/var/tmp/bootp/bootp-170.1.sym/BuiltProducts/include -I/private/var/tmp/bootp/bootp-170.1.obj/bootp.build/bootpd.build/DerivedSources -c /SourceCache/bootp/bootp-170.1/bootpd.tproj/bsdpd.c -o /private/var/tmp/bootp/bootp-170.1.obj/bootp.build/bootpd.build/Objects-normal/ppc/bsdpd.o In file included from /SourceCache/bootp/bootp-170.1/bootpd.tproj/bsdpd.c:89: /SourceCache/bootp/bootp-170.1/bootpd.tproj/AFPUsers.h:32:41: error: OpenDirectory/OpenDirectory.h: No such file or directory
**Solution:** chroot BuildRoot
ln -s /System/Library/PrivateFrameworks/OpenDirectory.framework /XCD/SY/Library/PrivateFrameworks/

then



**Problem:** /XCD/SY/Library/PrivateFrameworks/OpenDirectory.framework/Headers/OpenDirectory.h:27:51: error: CFOpenDirectory/CFOpenDirectoryConsts.h: No such file or directory
/XCD/SY/Library/PrivateFrameworks/OpenDirectory.framework/Headers/OpenDirectory.h:28:45: error: CFOpenDirectory/CFOpenDirectory.h: No such file or directory

**Solution:** mkdir -p BuildRoot/usr/include/CFOpenDirectoryroot

cp BuildRoot/private/var/tmp/CFOpenDirectory/CFOpenDirectory-39.root/XCD/SY/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/Frameworks/CFOpenDirectory.framework/Versions/A/Headers/CFOpenDirectory* BuildRoot/usr/include/CFOpenDirectory
then
**Problem:** ld: file not found: /System/Library/PrivateFrameworks/OpenDirectory.framework/Versions/A/Frameworks/CFOpenDirectory.framework/Versions/A/CFOpenDirectory





------------------------------------------------------------------------


### bootstrap_cmds
`darwinbuild bootstrap_cmds`
#### 9J61 (ok)
#### 9G55 (ok)
#### 9F33 (ok)

****
<span style="font-weight:bold">Solution: <span style="font-weight:normal"><span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild flex && darwinbuild -load flex</span></span></span></span>
![](/img/developers/darwinbuild/troubleshooting/bootstrap_cmds.png)
------------------------------------------------------------------------
### configd
darwinbuild configd
#### 9J61
**Problem:** CompileC /private/var/tmp/configd_plugins/configd_plugins-91.obj/configd_plugins.build/InterfaceNamer.build/Objects-normal/ppc/ifnamer.o 
InterfaceNamer.bproj/ifnamer.c:72:58: error: SystemConfiguration/VLANConfigurationPrivate.h: No such file or directory

#### 9F33 (ok)

Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then:


darwinbuild -init 9F33pd1

The plist file above contains some patches that tend to avoid most of the errors just below.


`darwinbuild configd`

****
**Solution:** `cp -R BuildRoot/System/Library/Frameworks/System.framework BuildRoot/XCD/SY/Library/Frameworks/`

**Problem:** `/SourceCache/configd/configd-212.2/SystemConfiguration.fproj/SCNetworkInterface.c:47:42: error: EAP8021X/EAPClientProperties.h: No such file or directory`
consequently..
`/SourceCache/configd/configd-212.2/SystemConfiguration.fproj/SCNetworkInterface.c: In function 'SCNetworkInterfaceCheckPassword':`
`/SourceCache/configd/configd-212.2/SystemConfiguration.fproj/SCNetworkInterface.c:3825: error: 'kEAPClientPropUserPasswordKeychainItemID' undeclared (first use in this function)`
`/SourceCache/configd/configd-212.2/SystemConfiguration.fproj/SCNetworkInterface.c: In function 'SCNetworkInterfaceCopyPassword':`
`/SourceCache/configd/configd-212.2/SystemConfiguration.fproj/SCNetworkInterface.c:3911: error: 'kEAPClientPropUserPasswordKeychainItemID' undeclared (first use in this function)`
`/SourceCache/configd/configd-212.2/SystemConfiguration.fproj/SCNetworkInterface.c: In function 'SCNetworkInterfaceRemovePassword':`
`/SourceCache/configd/configd-212.2/SystemConfiguration.fproj/SCNetworkInterface.c:4010: error: 'kEAPClientPropUserPasswordKeychainItemID' undeclared (first use in this function)`
`/SourceCache/configd/configd-212.2/SystemConfiguration.fproj/SCNetworkInterface.c: In function 'SCNetworkInterfaceSetPassword':`
`/SourceCache/configd/configd-212.2/SystemConfiguration.fproj/SCNetworkInterface.c:4208: error: 'kEAPClientPropUserPasswordKeychainItemID' undeclared (first use in this function)`
****
**Problem: **`Undefined symbols:`
`  "_CFPreferencesAppValueIsForced", referenced from:`
`      _processPreferences in SCNetworkConnectionPrivate.o`
`      _SCUserPreferencesIsForced in SCNetworkConnectionPrivate.o`
`  "_CFStringTransform", referenced from:`
`      __SC_dos_copy_string in SCDPrivate.o`
Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then rebuild configd:

<span><span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild -init 9F33pd1 && darwinbuild configd</span></span></span>
The plist file above contains some patches that tend to avoid the undefined symbols.


**Problem:** The framework is registered in /XCD/SY:
**40555 0 0 0 ./XCD/SY/Library/Frameworks/SystemConfiguration.framework**
**Solution:** **Please, let us know if you have one.**

------------------------------------------------------------------------
### configd_executables
`darwinbuild configd_executables`

****

****
****
------------------------------------------------------------------------

****
### copyfile
9J61

Problem: /SourceCache/copyfile/copyfile-42/copyfile.c:48:24: error: quarantine.h: No such file or directory


------------------------------------------------------------------------
### cron
#### 9J61 (ok)
****

`/SourceCache/cron/cron-30/cron/do_command.c:39:35: error: IOKit/pwr_mgt/IOPMLib.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:40:32: error: IOKit/pwr_mgt/IOPM.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:41:28: error: IOKit/IOReturn.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:38:28: error: IOKit/IOKitLib.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:39:35: error: IOKit/pwr_mgt/IOPMLib.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:40:32: error: IOKit/pwr_mgt/IOPM.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:41:28: error: IOKit/IOReturn.h: No such file or directory`
**Solution:** <span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild IOKitUser && darwinbuild -load IOKitUser</span></span> (note: plan to keep some effort and coffee probably involved in building IOKitUser.
------------------------------------------------------------------------

### cups
9J61
Problem: make: *** No rule to make target `installfat'.  Stop.


Problem: dyld

    /XCD/loper/usr/bin/g++-4.0 -arch ppc -L/private/var/tmp/dyld/dyld-97.1.sym/BuiltProducts -F/private/var/tmp/dyld/dyld-97.1.sym/BuiltProducts -filelist /private/var/tmp/dyld/dyld-97.1.obj/dyld.build/dyld.build/Objects-normal/ppc/dyld.LinkFileList -exported_symbols_list /SourceCache/dyld/dyld-97.1/src/dyld.exp -mmacosx-version-min=10.5 -Wl,-dead_strip -seg1addr 0x8fe00000 -lstdc++-static -nostdlib /usr/local/lib/system/libc.a -lgcc_eh -lgcc -Wl,-e,__dyld_start -Wl,-dylinker -Wl,-dylinker_install_name,/usr/lib/dyld -Wl,-non_global_symbols_strip_list,/SourceCache/dyld/dyld-97.1/src/strip.exp -o /private/var/tmp/dyld/dyld-97.1.obj/dyld.build/dyld.build/Objects-normal/ppc/dyld
ld: couldn't dlopen() /usr/lib/libdtrace.dylib: dlopen(/usr/lib/libdtrace.dylib, 1): Library not loaded: /System/Library/PrivateFrameworks/Symbolication.framework/Versions/A/Symbolication
**Solution:** rebuild dtrace patched instead of using the default binaryroot available at apple/macosforge to avoid the symbolication link.

Or use the binaryroot from 9F33pd1 already patched (tar xzvf ../../../hg/Roots/9F33pd1/dtrace.root.tar.gz in BuildRoot)

But... more pb:     /XCD/loper/usr/bin/g++-4.0 -arch ppc -L/private/var/tmp/dyld/dyld-97.1.sym/BuiltProducts -F/private/var/tmp/dyld/dyld-97.1.sym/BuiltProducts -filelist /private/var/tmp/dyld/dyld-97.1.obj/dyld.build/dyld.build/Objects-normal/ppc/dyld.LinkFileList -exported_symbols_list /SourceCache/dyld/dyld-97.1/src/dyld.exp -mmacosx-version-min=10.5 -Wl,-dead_strip -seg1addr 0x8fe00000 -lstdc++-static -nostdlib /usr/local/lib/system/libc.a -lgcc_eh -lgcc -Wl,-e,__dyld_start -Wl,-dylinker -Wl,-dylinker_install_name,/usr/lib/dyld -Wl,-non_global_symbols_strip_list,/SourceCache/dyld/dyld-97.1/src/strip.exp -o /private/var/tmp/dyld/dyld-97.1.obj/dyld.build/dyld.build/Objects-normal/ppc/dyld
error: provider plockstat doesn't exist
error: Could not register probes
ld: error creating dtrace DOF section
collect2: ld returned 1 exit status

------------------------------------------------------------------------
### dtrace
### 

Run-time problem: dtrace: failed to compile script [...] "/usr/lib/dtrace/darwin.d", line 26: syntax error near "uthread_t"
Solution: related mach_kernel.ctfsys? some probe not available?

9J61




****





Problem: /SourceCache/dtrace/dtrace-48.1/libproc/libproc.m:10:40: error: Symbolication/Symbolication.h: No such file or directory
/SourceCache/dtrace/dtrace-48.1/libproc/libproc.m:11:47: error: Symbolication/SymbolicationPrivate.h: No such file or directory
In file included from /SourceCache/dtrace/dtrace-48.1/libproc/libproc.m:29:
Solution: 
#### 9G55
DTrace compilation fails.


****` In file included from /SourceCache/dtrace/dtrace-48/libctf/ctf_lib.c:30:`
`/usr/include/sys/stat.h:75:26: error: Availability.h: No such file or directory`
`In file included from /SourceCache/dtrace/dtrace-48/libctf/ctf_lib.c:30:`
`/usr/include/sys/stat.h:460: error: syntax error before '__OSX_AVAILABLE_BUT_DEPRECATED'`
**Solution: ... **Found in two locations into the host system:

`/Developer/SDKs/MacOSX10.5.sdk/usr/include/Availability.h`
`/usr/include/Availability.h`
<span style="font-weight:bold">Availability.h should be soon available: <span style="font-weight:normal"><http://darwinbuild.macosforge.org/trac/changeset/459> </span></span>

### 9F33 (ok)
Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then:


darwinbuild -init 9F33pd1

The plist file above contains some patches that tend to avoid most of the errors just below.




__Note:__ dtrace compilation needs *libdwarf* to be installed in the BuildRoot, and *libdwarf* depends on *libelf*. Both *libdwarf* and *libelf* projects aren't available in darwinbuild, so they have been added in the custom plist to satisfy dtrace requirements.

So before building dtrace.

<span style="font-size:12px">darwinbuild libelf && darwinbuild -load libelf</span>

<span style="font-size:12px">darwinbuild libdwarf && darwinbuild -load libdwarf</span>

This should be done automatically with dtrace dependencies, **but how**?


darwinbuild dtrace

**** error: couldn't exec /XCD/loper/usr/bin/yacc: No such file or directory
**Old-Solution: darwinbuild bison**
**darwinbuild -load bison**
**cp BuildRoot/usr/bin/yacc BuildRoot/XCD/loper/usr/bin/ **

**Problem: **`error: couldn't exec /XCD/loper/usr/bin/lex: No such file or directory`
<span style="font-weight:bold">Old-Solution: <span style="font-weight:normal"><span style="font-family:courier new,monospace"><span style="font-size:small"><span style="color:rgb(204,204,204)">darwinbuild flex && darwinbuild -load flex</span></span></span></span></span>
cp BuildRoot/usr/bin/lex BuildRoot/XCD/loper/usr/bin
**Solution: **[http://darwinbuild.macosforge.org/trac/ticket/43](http://darwinbuild.macosforge.org/trac/ticket/43) 

**** /XCD/loper/usr/bin/mig: line 147: : command not found
**Solution:  darwinbuild bootstrap_cmds**
darwinbuild -load bootstrap_cmds
cp BuildRoot/usr/bin/arch BuildRoot/usr/bin/mig BuildRoot/XCD/loper/usr/bin/
mkdir BuildRoot/XCD/loper/usr/libexec/
cp BuildRoot/usr/libexec/migcom BuildRoot/XCD/loper/usr/libexec

__Note:__ we used `dtrace' to dtrace dtrace, e.g.:
`  0  18390             write_nocancel:entry sh /XCD/loper/usr/bin/mig: line 60: pushd: /XCD/loper/usr/bin/../libexec: No such file or directory`
`  0  18390             write_nocancel:entry grep migcomPath=$(realpath "${scriptRoot}/../libexec/migcom")`
**Problem:** `dyld: Library not loaded: /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation`
  Referenced from: /usr/bin/arch
  Reason: image not found
****
mv /usr/bin/arch /usr/bin/arch.origin
echo 'uname -p' > /usr/bin/arch
chmod +x /usr/bin/arch

**Alternative solution:** PureFoundation can be used (from <http://www.hereapi.com/pf/index.html>), it really seems interesting as showed just below, it works for `arch':
`root@europa:/Volumes/Builds/``9G55/BuildRoot# mv PureFoundation/Foundation.``framework System/Library/Frameworks
root@europa:/Volumes/Builds/``9G55/BuildRoot# chroot .
europa# arch
NSObject +load
i386
`

**** /SourceCache/dtrace/dtrace-48/libproc/libproc.m:10:40: error: Symbolication/Symbolication.h: No such file or directory
/SourceCache/dtrace/dtrace-48/libproc/libproc.m:11:47: error: Symbolication/SymbolicationPrivate.h: No such file or directory
**Solution**: Since Symbolication is not part of Darwin, all references to it need to be patched out of the source.
__Notes:__ <http://darwinbuild.macosforge.org/trac/ticket/23> / <http://darwinbuild.macosforge.org/trac/ticket/24>

On PureDarwin, the patched `dtrace' built from darwinbuild looks like:

/usr/sbin/dtrace:
 `/usr/lib/libdtrace.dylib (compatibility version 1.0.0, current version 48.0.0)`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)`
 `/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`

![](/img/developers/darwinbuild/troubleshooting/dtrace%20patched.png)


On Mac OS X, `dtrace' looks like:

/usr/sbin/dtrace:
 `/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 674.0.0)`
 `/System/Library/PrivateFrameworks/Symbolication.framework/Versions/A/Symbolication (compatibility version 1.0.0, current version 35.0.0)`
 `/usr/lib/libdtrace.dylib (compatibility version 1.0.0, current version 48.0.0)`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.0.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
 `/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 474.0.0)`


![](/img/developers/darwinbuild/troubleshooting/dtrace.png)

------------------------------------------------------------------------


### eap8021x
#### 9J61pd1
**Problem:** ld64: warning, -seg_addr_table file cannot be read: /AppleInternal/Developer/seg_addr_table
ld64: warning, -seg_addr_table file cannot be read: /AppleInternal/Developer/seg_addr_table
ld64ld64: warning, :- seg_addr_tablewarning, -seg_addr_table file cannot be read: /AppleInternal/Developer/seg_addr_table
ld: warning in /System/Library/Frameworks//Security.framework/Security, missing required architecture ppc64 in file
ld: warning in /usr/lib/libSystemStubs.a, missing required architecture ppc64 in  file cannot be read:file
Undefined symbols:
  "_SecIdentityCreateWithCertificate" /AppleInternal/Developer/, referenced from:
**Solution:**

**Problem:** /usr/bin/cc -arch i386 -Os -pipe -no-cpp-precomp -Wmost  -g  -fno-common -I/private/var/tmp/eap8021x/eap8021x-49.8.sym/eapol.build/ProjectHeaders -I -I -I/private/var/tmp/eap8021x/eap8021x-49.8.sym/eapol.build/derived_src/eapolclient.tproj -I. -pipe        -I/private/var/tmp/eap8021x/eap8021x-49.8.sym/eapol.build/Headers -I/private/var/tmp/eap8021x/eap8021x-49.8.sym/eapol.build/PrivateHeaders -F/private/var/tmp/eap8021x/eap8021x-49.8.sym  -F/System/Library/PrivateFrameworks -F/System/Library/PrivateFrameworks -mdynamic-no-pic -fconstant-cfstrings   -c -o /private/var/tmp/eap8021x/eap8021x-49.8.obj/objects-optimized/eapolclient.tproj/wireless.i386.o wireless.c
wireless.c:37:38: error: Apple80211/Apple80211API.h: No such file or directory
wireless.c:38:37: error: Apple80211/Apple80211IE.h: No such file or directory
wireless.c:47:54: error: Kernel/IOKit/apple80211/apple80211_ioctl.h: No such file or directory
Solution:

------------------------------------------------------------------------
### efax
#### 9J61
Problem: /SourceCache/efax/efax-28/efax/efaxos.c:144: error: 'kCFNotificationDeliverImmediately' undeclared (first use in this function)

/SourceCache/efax/efax-28/efax/efaxos.c:144: error: 'kCFNotificationPostToAllSessions' undeclared (first use in this function)

------------------------------------------------------------------------
### efiboot 
**Problem:** make: *** No rule to make target `install'.  Stop.
**<- no source available, only binary form.**
****
------------------------------------------------------------------------
****
### gcc_os
checking if mkdir takes one argument... yes
/SourceCache/gcc_os/gcc_os-1823/gcc/config.gcc: line 2971: out_file: command not found
/SourceCache/gcc_os/gcc_os-1823/gcc/config.gcc: line 2971: out_file: command not found
Using `/SourceCache/gcc_os/gcc_os-1823/gcc/config/rs6000/rs6000.c' for machine-specific logic.
Using `/SourceCache/gcc_os/gcc_os-1823/gcc/config/rs6000/rs6000.md' as machine description file.
Using the following target machine macro files:
 /SourceCache/gcc_os/gcc_os-1823/gcc/config/rs6000/rs6000.h
 /SourceCache/gcc_os/gcc_os-1823/gcc/config/darwin.h
 /SourceCache/gcc_os/gcc_os-1823/gcc/config/rs6000/darwin.h
Using host-darwin.o for host machine hooks.
/APPLE_LICENSE: line 1: APPLE: command not found
/APPLE_LICENSE: line 2: Version: command not found
/APPLE_LICENSE: line 4: Please: command not found
..
------------------------------------------------------------------------
### gccfast
checking if mkdir takes one argument... yes
/SourceCache/gccfast/gccfast-1626/gcc/config.gcc: line 2971: out_file: command not found
Using `/SourceCache/gccfast/gccfast-1626/gcc/config/i386/i386.c' for machine-specific logic.
Using `/SourceCache/gccfast/gccfast-1626/gcc/config/i386/i386.md' as machine description file.
Using the following target machine macro files:
 /SourceCache/gccfast/gccfast-1626/gcc/config/i386/i386.h
 /SourceCache/gccfast/gccfast-1626/gcc/config/darwin.h
 /SourceCache/gccfast/gccfast-1626/gcc/config/i386/darwin.h
Using host-darwin.o for host machine hooks.
/APPLE_LICENSE: line 1: APPLE: command not found
/APPLE_LICENSE: line 2: Version: command not found
/APPLE_LICENSE: line 4: Please: command not found
/APPLE_LICENSE: line 5: By: command not found
------------------------------------------------------------------------
### gnuserv
#### 9J61
/usr/bin/emacs-undumped -batch -l loadup 
 --eval "(add-to-list 'load-path ".")" 
 -l gnuserv-compat  -f batch-byte-compile gnuserv-compat.el
dyld: Library not loaded: /System/Library/Frameworks/Carbon.framework/Versions/A/Carbon
  Referenced from: /usr/bin/emacs-undumped
  Reason: image not found

DiskImage available??

lib/FVDIHLInterface.h:27:38: error: DiskImages/DIHLInterface.h: No such file or directory


------------------------------------------------------------------------
### ipv6configuration
#### 9J61
libraries/service.c:817: error: 'userNotification' undeclared (first use in this function)

libraries/service.c:834: error: 'CFUserNotificationRef' undeclared (first use in this function)

libraries/service.c:850: error: 'kCFUserNotificationAlertHeaderKey' undeclared (first use in this function)
libraries/service.c:852: error: 'kCFUserNotificationAlertMessageKey' undeclared (first use in this function)
libraries/service.c:854: error: 'kCFUserNotificationLocalizationURLKey' undeclared (first use in this function)


****
------------------------------------------------------------------------

**isoutil**
#### 9J61 (ok)
**problem:** `cd9660.util_main.m:52:28: error: IOKit/IOKitLib.h: No such file or directory`

****
**cp -R /Developer/SDKs/MacOSX10.5.sdk/System/Library/Frameworks/IOKit.framework/Versions/A/Headers/* BuildRoot/usr/include/IOKit**

Consequently, next error will be..



**Problem: **c`d9660.util_main.m:757: error: 'kNilOptions' undeclared (first use in this function)`
`cd9660.util_main.m:757: error: (Each undeclared identifier is reported only once`
`cd9660.util_main.m:757: error: for each function it appears in.)`
**Pseudo-solution:** Add in BuildRoot/usr/include/IOKit/IOKitLib.h #include &lt;CarbonCore/MacTypes.h&gt;


Then,


**Problem:** `ld: framework not found IOKit`

`ld: framework not found IOKit`
**PseudoSolution:** install *IOKitUser* from *9F33pd1* using a custom plist:

`darwinbuild -load IOKitUser   `
`Downloading http://src.macosforge.org/Roots/9J61//IOKitUser.root.tar.gz ...`
`Downloading http://puredarwin.googlecode.com/svn/Roots/9G55pd1//IOKitUser.root.tar.gz ...`
`Downloading http://puredarwin.googlecode.com/svn/Roots/9F33pd1//IOKitUser.root.tar.gz ...`
`Download complete`
`IOKitUser - 137 files registered.`

**Solution:** `darwinbuild -load IOKitUser` &lt;- unfortunately, it doesn't built without patch

But another problem will come if the default IOKitUser binaryroot from 9F33pd1 is used, because it as been built only for the arch i386. So either building isoutil only for i386 (not tested) or removing the arch restriction on IOKItUser in 9F33pd1 to ppc could work (test).


------------------------------------------------------------------------
### kext_tools

`darwinbuild kext_tools`
#### 9J61 ??


#### 9F33pd1 (ok)
Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then init:



darwinbuild -init 9F33pd1

The plist file above contains some patches that tend to avoid most of the errors just below.
__Note:__ No BuildRoot alteration, hopefully.



`darwinbuild kext_tools`


**Problem: **`/SourceCache/kext_tools/kext_tools-117/prelink.c:800: error: 'kNilOptions' undeclared (first use in this function)`


**Problem: **/SourceCache/kext_tools/kext_tools-117/bootcaches.c:925: error: 'kNilOptions' undeclared (first use in this function)

****
#ifndef kNilOptions 
    `#define kNilOptions 0
#endif`
<span style="font-family:courier new;font-size:12px"><span style="font-family:Arial;font-size:13px;font-weight:bold"><span style="font-weight:normal">**Solution:** Add <span>`#include <CarbonCore/MacTypes.h>`</span></span></span></span>



**Problem: **/SourceCache/kext_tools/kext_tools-117/bootcaches.c:143: error: 'nil' undeclared (first use in this function)

/SourceCache/kext_tools/kext_tools-117/bootcaches.c:403: error: 'nil' undeclared (first use in this function)

/SourceCache/kext_tools/kext_tools-117/bootcaches.c:774: error: 'nil' undeclared (first use in this function)

**Solution: **Add #include <objc/objc.h>


Compilation success, let's look the patched `kextcache' binary for "purity" purpose:

`/usr/sbin/kextcache:`
 ``
 `/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)`
 `/System/Library/Frameworks/DiskArbitration.framework/Versions/A/DiskArbitration (compatibility version 1.0.0, current version 1.0.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)`

And the Mac OS X `kextcache' binary:

`/usr/sbin/kextcache:`
 `/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit (compatibility version 1.0.0, current version 275.0.0)`
 `/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)`
 `/System/Library/Frameworks/DiskArbitration.framework/Versions/A/DiskArbitration (compatibility version 1.0.0, current version 1.0.0)`
 `/System/Library/Frameworks/ApplicationServices.framework/Versions/A/ApplicationServices (compatibility version 1.0.0, current version 34.0.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.0.0)`

**Problem:** /XCD/SY should not be.
**Solution:**





------------------------------------------------------------------------


### launchd
``
#### 9J61 ?
Problem: ERROR: could not find root: IOKitUser
Solution:<span style="font-size:12px;font-weight:normal"> darwinbuild IOKitUser && darwinbuild -load IOKitUser
</span>
#### 9G55
### ?

#### 9F33pd1 (ok)
Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then:


darwinbuild -init 9F33pd1

The plist file above contains some patches that tend to avoid most of the errors just below.


darwinbuild launchd



**Problem:** `ERROR: could not find root: IOKitUser`
**Pseudo-solution:** <span style="font-family:courier new;font-size:12px">darwinbuild IOKitUser && darwinbuild -load IOKitUser</span>

**Problem:** `dyld: Library not loaded: /usr/lib/libauto.dylib`
`  Referenced from: /usr/lib/libobjc.A.dylib`
`  Reason: image not found`
**Old-Solution: ******
**Solution:** Good [news](../../../news/autozone.html) on 11/12/2008, the AutoZone project sources have been released by Apple: <span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild autozone && darwinbuild -load autozone</span></span>

**Problem:** `/SourceCache/launchd/launchd-258.18/launchd/src/launchctl.c:37:28: error: IOKit/IOKitLib.h: No such file or directory`
****
**cp -R /Developer/SDKs/MacOSX10.5.sdk/System/Library/Frameworks/IOKit.framework/Versions/A/Headers/* BuildRoot/usr/include/IOKit**


**Problem:** `/SourceCache/launchd/launchd-258.18/launchd/src/launchctl.c:73:23: error: bootfiles.h: No such file or directory`
****
__Note:__ See <http://darwinbuild.macosforge.org/trac/ticket/9> 


****
/SourceCache/launchd/launchd-258.18/launchd/src/launchctl.c:69:30: error: readline/history.h: No such file or directory

**Solution:** darwinbuild libedit
darwinbuild -load libedit



**Problem: **gcc -no-cpp-precomp -isysroot / -F//System/Library/PrivateFrameworks -Wall -Wextra -Waggregate-return -Wshadow -Wmissing-prototypes -Wmissing-declarations -Werror -D__MigTypeCheck=1 -fvisibility=hidden -Dmig_external=__private_extern__ -I//System/Library/Frameworks/System.framework/PrivateHeaders -arch ppc -arch i386 -g -Os -pipe -pipe -no-cpp-precomp -arch ppc -arch i386 -Wl,-syslibroot,/ -framework CoreFoundation -framework IOKit -framework Security -weak_library /usr/lib/libedit.dylib -arch ppc -arch i386             -o launchctl launchctl-launchctl.o  
ld: framework not found IOKit
**Solution:** See above for *IOKitUser* project.


**Problem:**` ``/SourceCache/launchd/launchd-258.1/launchd/src/launchd_core_logic.c:76:21: error: sandbox.h: No such file or directory`
**Solution:**` ``cp /usr/include/sandbox.h BuildRoot/usr/include/`



**Problem:** `/SourceCache/launchd/launchd-258.1/launchd/src/SystemStarter.c:159: error: 'kCFNotificationDeliverImmediately' undeclared (first use in this function)`
**Pseudo-Solution:** cp /Developer/SDKs/MacOSX10.5.sdk/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers/CFNotificationCenter.h BuildRoot/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers/

`#include <CoreFoundation/CFNotificationCenter.h>`
Also comment in  from line 156 to line 161 in order to avoid missing symbols

`/*` `CFNotificationCenterPostNotificationWithOptions(`
 `CFNotificationCenterGetDistributedCenter(),`
 `CFSTR("com.apple.startupitems.completed"),`
 `NULL, NULL,`
 `kCFNotificationDeliverImmediately | kCFNotificationPostToAllSessions);`
`*/`
__Note:__ This is what is happening about missing symbols:
`Undefined symbols for architecture i386:`
`  "_CFNotificationCenterGetDistributedCenter", referenced from:`
`      _main in SystemStarter-SystemStarter.o`
`  "_CFNotificationCenterPostNotificationWithOptions", referenced from:`
`      _main in SystemStarter-SystemStarter.o`
**
**

Compilation pseudo-success: `launchd - 27 files registered.`
`darwinbuild -load launchd`
launchd also works:

`launchd `
`launchd: This program is not meant to be run directly.`


**Problem:** *launchctl* is linked to *CoreFoundation*
**launchctl **
`dyld: Library not loaded: /System/Library/Frameworks/CoreFoundation/Versions/A/CoreFoundation`
`  Referenced from: /System/Library/Frameworks/IOKit.framework/Versions/A/IOKit`
`  Reason: image not found`

****

/System/Library/Frameworks/CoreFoundation/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)

Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then rebuild CF:

<span style="font-family:courier new"><span style="font-size:12px">darwinbuild -init 9F33pd1 && darwinbuild CF && darwinbuild -load CF</span></span>
The plist file above contains some patches that tend to avoid most of the related errors.
After recompilation of CF, dependency is fixed:

/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)



**Problem:** `launchctl help`
`dyld: Symbol not found: __kCFBundleResourceSpecificationKey`
`  Referenced from: /System/Library/Frameworks/Security.framework/Versions/A/Security`
`  Expected in: /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation`
**Solution: **Same problem as investigation below. So we recreate the expected method (empty foobar) in CF to satisfy Security.

![](/img/developers/darwinbuild/troubleshooting/launchd_9F33pd1.png)
__
__

**Comparison with launchd from Darwin 8:**

**
**

****

`/sbin/launchd:`
`        /usr/lib/libbsm.dylib (compatibility version 1.0.0, current version 1.0.0)`
`        /usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
`        /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 88.3.3)`


Leopard's launchd binary still links to the same three libraries only.
However, there's quite a difference in launchctl between Darwin 8 and 9, as shown below.
Mac OS X 10.4 (Darwin 8):


/bin/launchctl:
        /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 368.27.0)
        /usr/lib/libedit.2.dylib (compatibility version 2.0.0, current version 2.0.0)
`        /usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
`        /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 88.3.3)`



Mac OS X 10.5 (Darwin 9):


/bin/launchctl:
` `/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.14.0)
` ``/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit (compatibility version 1.0.0, current version 275.0.0)`
` `/System/Library/Frameworks/Security.framework/Versions/A/Security (compatibility version 1.0.0, current version 34102.0.0)
` `/usr/lib/libedit.2.dylib (compatibility version 2.0.0, current version 2.9.0)
` ``/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`

 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.0.0)`


PureDarwin (Darwin 9):


 `/System/Library/Frameworks/CoreFoundation/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)`

 ``
 `/System/Library/Frameworks/Security.framework/Versions/A/Security (compatibility version 1.0.0, current version 33532.0.0)`
 `/usr/lib/libedit.2.dylib (compatibility version 2.0.0, current version 2.9.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)`







**Problem:** /XCD/SY should not be.
**Solution:** **Please, let us know if you have one.**
------------------------------------------------------------------------
### launchd_libs
#### 9J61 (ok)
**Problem:** mig in XCD related error.
**Solution:** cf above/below.


****
------------------------------------------------------------------------
### libdwarf
`darwinbuild libdwarf`
#### 9J61
?
#### 9G55
**Problem:** `lipo: /SourceCache/libdwarf/libdwarf-8/dwarf/dwarfdump/dwarfdump.i386 and /SourceCache/libdwarf/libdwarf-8/dwarf/dwarfdump/dwarfdump.ppc have the same architectures (i386) and can't be in the same fat output file`
**Solution:** ?
#### 9F33 (ok)
------------------------------------------------------------------------
### libgcc
#### 9J61pd1
/usr/include/stdlib.h:283: error: expected ',' or ';' before '__OSX_AVAILABLE_BUT_DEPRECATED'
&gt;&gt; int  daemon(int, int) __DARWIN_1050(daemon) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_2_0,__IPHONE_2_0);
&gt;&gt;&gt;
//int  daemon(int, int) __DARWIN_1050(daemon) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_2_0,__IPHONE_2_0);
int  daemon(int, int) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_2_0,__IPHONE_2_0);
------------------------------------------------------------------------

### libsecurity_apple_csp
#### 9J61
not present in macosx too:

`lib/FEEKeys.h:34:40: error: security_cryptkit/feeTypes.h: No such file or directory`
`lib/FEEKeys.h:43: error: expected `)' before 'feeKey'`
`lib/FEEKeys.h:53: error: 'feePubKey' does not name a type`
`lib/FEEKeys.h:55: error: 'feePubKey' does not name a type`

patch + <http://lists.apple.com/archives/apple-cdsa/2003/Feb/msg00017.html>
and
__Notes:__ *The current use of FEE by the CSP enables CryptKit routines which need pseudorandom numbers (e.g., signature generation) to obtain pseudorandom data via callbacks specified when calling the relevant function. The callback is defined (as a feeRandFcn) in feeTypes.h. The CSP provides a function in such cases which obtain data from the kernelâ€™s Yarrow implementation, which is believed to be cryptographically secure on the MacOS X platform. All of the CryptKit functions which provide for this callback treat the callback parameter as optional; when not present, CryptKit uses its own FEE-based PRNG.* 
then

`/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h:103: error: 'noErr' was not declared in this scope`

`/usr/local/SecurityPieces/Frameworks/security_cdsa_utilities.framework/Headers/cssmdbname.h:90: error: 'nil' was not declared in this scope`

**Solution:** Add `#include <CarbonCore/MacTypes.h>` in *BuildRoot/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers/CFBase.h*
__Notes:__ See <http://darwinbuild.macosforge.org/trac/ticket/85>


------------------------------------------------------------------------
### libsecurity_cdsa_plugin
#### 9J61 (ok)
**Problem:** `/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h: In static member function 'static void Security::MacOSError::check(OSStatus)':`

`/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h:103: error: 'noErr' was not declared in this scope`
<span style="font-family:courier new,monospace"><span style="font-size:small">/usr/local/SecurityPieces/Frameworks/security_cdsa_utilities.framework/Headers/cssmdbname.h: In member function 'bool Security::DbName::operator&lt;(const Security::DbName&) const':</span></span>
`/usr/local/SecurityPieces/Frameworks/security_cdsa_utilities.framework/Headers/cssmdbname.h:90: error: 'nil' was not declared in this scope`
**Solution:** Apply the libsecurityd fix and build libsecurity_utilities
------------------------------------------------------------------------

### libsecurity_cdsa_utilities
#### 9J61
`lib/osxverifier.cpp:27:46: error: security_codesigning/requirement.h: No such file or directory`
`lib/osxverifier.cpp:30:44: error: security_codesigning/reqdumper.h: No such file or directory`
depend on security_codesigning


------------------------------------------------------------------------
### libsecurity_codesigning

#### 9J61
**Problem:** `/bin/sh -c ""/private/var/tmp/libsecurity_codesigning/libsecurity_codesigning-36591.obj/libsecurity_codesigning.build/Requirements Language.build/Script-C2D383B70A23A8C4005C63A2.sh""`

`/private/var/tmp/libsecurity_codesigning/libsecurity_codesigning-36591.obj/libsecurity_codesigning.build/Requirements Language.build/Script-C2D383B70A23A8C4005C63A2.sh: line 6: java: command not found`
**Solution:** `chroot BuildRoot`
??? cf java
But..

Error occurred during initialization of VM
Unable to load native library: libjava.jnilib

+ JavaVM blocker, because linked to Foundation with symbols not provided by PureFoundation.
Consequently codesigning stuff cannot be built. Since a long time.. <http://lists.apple.com/archives/darwin-development/2003/Jan/msg00227.html>
the script in cause:

#!/bin/bash
antlr=/usr/local/bin/antlr.jar
DEBUG=""
mkdir -p $TEMPDIR
rm -f $TEMPDIR/Requirement{Parser,Lexer}*
java -cp "$antlr" antlr.Tool -o $TEMPDIR $DEBUG requirements.grammar

and more, no antlr found.. MacPorts says about:

Description:          ANTLR, ANother Tool for Language Recognition, is a language tool that provides a framework for constructing recognizers, compilers, and translators from grammatical descriptions
                      containing Java, C#, or C++ actions.
Homepage:             http://www.antlr2.org/

Then trying to build it (libsecurity_codesigning) outside the chroot leads to:

    /bin/sh -c ""/Users/aladin/PureDarwin/darwinbuild/9J61/BuildRoot/private/var/tmp/libsecurity_codesigning/libsecurity_codesigning-36591.obj/libsecurity_codesigning.build/Requirements Language.build/Script-C2D383B70A23A8C4005C63A2.sh""
Exception in thread "main" java.lang.NoClassDefFoundError: antlr/Tool
** BUILD FAILED **

So, let's see what can we do we the previous discovered port.
 port install antlr

ln -fs /opt/local/lib/antlr.jar /usr/local/bin 


lib/cserror.h:30:44: error: security_utilities/cfutilities.h: No such file or directory
lib/cserror.h:31:42: error: security_utilities/debugging.h: No such file or directory

lib/cs.h:33:34: error: Security/SecBasePriv.h: No such file or directory
lib/cs.h:35:43: error: security_utilities/globalizer.h: No such file or directory
lib/cs.h:36:44: error: security_utilities/seccfobject.h: No such file or directory
lib/cs.h:37:40: error: security_utilities/cfclass.h: No such file or directory
lib/cs.h:38:39: error: security_utilities/errors.h: No such file or directory

lib/codedirectory.h:36:39: error: security_utilities/unix++.h: No such file or directory
lib/codedirectory.h:37:37: error: security_utilities/blob.h: No such file or directory
lib/codedirectory.h:39:40: error: security_utilities/hashing.h: No such file or directory

lib/requirement.h:31:42: error: security_utilities/superblob.h: No such file or directory
etc..



lib/bundlediskrep.cpp:25:41: error: CoreFoundation/CFBundlePriv.h: No such file or directory
Remarquable! For the first time, "it's" the contrary:

cp -R BuildRoot/usr/local/SecurityPieces /usr/local/
something from the buildroot finally goes outside!

then
lib/cs.h:33:34: error: Security/SecBasePriv.h: No such file or directory
/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/seccfobject.h:29:38: error: CoreFoundation/CFRuntime.h: No such file or directory


To be continued..
------------------------------------------------------------------------
### libsecurity_dotmacdl
#### 9J61
**Problem:** /SourceCache/libsecurity_dotmacdl/libsecurity_dotmacdl-29745/lib/DotMacRelation.cpp:30:39: error: CoreServices/CoreServices.h: No such file or directory


------------------------------------------------------------------------
### libsecurity_filevault
#### 9J61
**Problem:** /usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h: In static member function 'static void Security::MacOSError::check(OSStatus)':
/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h:103: error: 'noErr' was not declared in this scope
------------------------------------------------------------------------
### libsecurity_keychain
#### 9J61
**Problem:** /private/var/tmp/libsecurity_keychain/libsecurity_keychain-36620.sym/BuiltProducts/SecurityPieces/Headers/Security/SecBase.h:63: error: 'OSType' does not name a type

`/private/var/tmp/libsecurity_keychain/libsecurity_keychain-36620.sym/BuiltProducts/SecurityPieces/Headers/Security/SecBase.h:74: error: 'SecKeychainAttrType' does not name a type`
`/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h: In static member function 'static void Security::MacOSError::check(OSStatus)':`
`/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h:103: error: 'noErr' was not declared in this scope`
`/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/cfutilities.h: At global scope:`
`/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/cfutilities.h:443: error: 'noErr' was not declared in this scope`
`/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/cfutilities.h:450: error: 'noErr' was not declared in this scope`
`/private/var/tmp/libsecurity_keychain/libsecurity_keychain-36620.sym/BuiltProducts/SecurityPieces/Headers/Security/SecKeychain.h:78: error: 'FourCharCode' does not name a type`
`/private/var/tmp/libsecurity_keychain/libsecurity_keychain-36620.sym/BuiltProducts/SecurityPieces/Headers/Security/SecKeychain.h:117: error: 'FourCharCode' does not name a type`
`/private/var/tmp/libsecurity_keychain/libsecurity_keychain-36620.sym/BuiltProducts/SecurityPieces/Headers/Security/SecKeychain.h:526: error: 'SecProtocolType' has not been declared`
`/private/var/tmp/libsecurity_keychain/libsecurity_keychain-36620.sym/BuiltProducts/SecurityPieces/Headers/Security/SecKeychain.h:526: error: 'SecAuthenticationType' has not been declared`
**Solution:** Add `#include <CarbonCore/MacTypes.h>` in *BuildRoot/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers/CFBase.h*

**Problem:** `lib/KCEventNotifier.h:31:49: error: CoreFoundation/CFNotificationCenter.h: No such file or directory`

**Pseudosolution: cp /Developer/SDKs/MacOSX10.5.sdk/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers/CFNotificationCenter.h BuildRoot/System/Library/Frameworks/CoreFoundation.framework/Versions/A/Headers/**

**Problem: **lib/CertificateRequest.cpp:34:41: error: security_dotmac_tp/dotMacTp.h: No such file or directory

**Solution: ...**
**Problem: ...**
**Solution:**
mkdir -p BuildRoot/usr/local/include/security_pkcs12            
root@europa:/Users/aladin/PureDarwin/darwinbuild/9J61# cp BuildRoot/private/var/tmp/libsecurity_pkcs12/libsecurity_pkcs12-32085.root/usr/local/SecurityPieces/Frameworks/security_pkcs12.framework/Versions/A/*/* BuildRoot/usr/local/include/security_pkcs12 

------------------------------------------------------------------------
### libsecurity_ldap_dl
#### 9J61
**Problem:** /SourceCache/libsecurity_ldap_dl/libsecurity_ldap_dl-30174/lib/DirectoryServices.cpp:266: error: cannot convert 'long unsigned int*' to 'UInt32*' for argument '8' to 'tDirStatus dsGetRecordList(tDirNodeReference, tDataBuffer*, tDataList*, tDirPatternMatch, tDataList*, tDataList*, int, UInt32*, tContextData*)'

<span style="font-size:small">/SourceCache/libsecurity_ldap_dl/libsecurity_ldap_dl-30174/lib/DirectoryServices.cpp: In member function 'void DSNode::Search(DSRecordList&, DSDataList&, DSDataNode&, tDirPatternMatch, DSDataNode&, long unsigned int&, DSContext&)':</span>
/SourceCache/libsecurity_ldap_dl/libsecurity_ldap_dl-30174/lib/DirectoryServices.cpp:279: error: cannot convert 'long unsigned int*' to 'UInt32*' for argument '7' to 'tDirStatus dsDoAttributeValueSearch(tDirNodeReference, tDataBuffer*, tDataList*, tDataNode*, tDirPatternMatch, tDataNode*, UInt32*, tContextData*)'
/SourceCache/libsecurity_ldap_dl/libsecurity_ldap_dl-30174/lib/DirectoryServices.cpp: In member function 'void DirectoryService::CreateNodeList(const char*)':
/SourceCache/libsecurity_ldap_dl/libsecurity_ldap_dl-30174/lib/DirectoryServices.cpp:347: error: cannot convert 'long unsigned int*' to 'UInt32*' for argument '2' to 'tDirStatus dsGetDirNodeCount(tDirReference, UInt32*)'
/SourceCache/libsecurity_ldap_dl/libsecurity_ldap_dl-30174/lib/DirectoryServices.cpp:363: error: cannot convert 'long unsigned int*' to 'UInt32*' for argument '3' to 'tDirStatus dsGetDirNodeList(tDirReference, tDataBuffer*, UInt32*, tContextData*)'
/SourceCache/libsecurity_ldap_dl/libsecurity_ldap_dl-30174/lib/DirectoryServices.cpp:393: error: cannot convert 'long unsigned int*' to 'UInt32*' for argument '3' to 'tDirStatus dsGetDirNodeList(tDirReference, tDataBuffer*, UInt32*, tContextData*)'
**Solution:** Cast & Patch.

------------------------------------------------------------------------
### libsecurity_manifest
#### 9J61
**Problem:** /usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h: In static member function 'static void Security::MacOSError::check(OSStatus)':

/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h:103: error: 'noErr' was not declared in this scope

Solution: 
------------------------------------------------------------------------

### libsecurityd
#### 9J61 (ok)
**Problem:**` /usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h: In static member function 'static void Security::MacOSError::check(OSStatus)':`
`/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h:103: error: 'noErr' was not declared in this scope`

<span style="font-family:courier new,monospace"><span style="font-size:small">/usr/local/SecurityPieces/Frameworks/security_cdsa_utilities.framework/Headers/cssmdbname.h: In member function 'bool Security::DbName::operator&lt;(const Security::DbName&) const':</span></span>
`/usr/local/SecurityPieces/Frameworks/security_cdsa_utilities.framework/Headers/cssmdbname.h:90: error: 'nil' was not declared in this scope`
****

`#include <CarbonCore/MacTypes.h>`


Then you should see `** BUILD SUCCEEDED **`

------------------------------------------------------------------------


libstdcxx_

9J61

checking how to run the C preprocessor... /lib/cpp
configure: error: C preprocessor "/lib/cpp" fails sanity check



------------------------------------------------------------------------
### libxml2
libxml2 is a dependency of *xar* and *headerdoc.*
*
*

`darwinbuild libxml2`
#### 9J61 (ok)
**Problem:** `ld: can't open order file: /usr/local/lib/OrderFiles/libxml2.order`
**Solution:** ?? no OrderFiles nor libxml2.order exists on my mac.
`mkdir BuildRoot/usr/local/lib/OrderFiles`
`touch BuildRoot/usr/local/lib/OrderFiles/libxml2.order `
See <http://darwinbuild.macosforge.org/trac/ticket/72>.
------------------------------------------------------------------------
### libxslt
darwinbuild libxslt
#### 9J61 (ok)
could need <span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild libxml2 && darwinbuild -load xml2</span></span>





------------------------------------------------------------------------
### mDNSResponder
#### 9J61?
.
#### 9F33pd1 (ok)
``
Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then:


darwinbuild -init 9F33pd1

The plist file above contains some patches that tend to avoid most of the errors just below.

darwinbuild mDNSResponder
**Problem:** `/SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/mDNSMacOSX.c:913: error: 'kCFUserNotificationStopAlertLevel' undeclared (first use in this function)`
**Solution:** The patch which includes `<CarbonCore/MacTypes.h>` and `<CoreFoundation/CFUserNotification.h>`


**Problem:** /SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/../mDNSCore/mDNSEmbeddedAPI.h:2785: error: size of array 'sizecheck_DNSQuestion' is negative

`/SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/../mDNSCore/mDNSEmbeddedAPI.h:2786: error: size of array 'sizecheck_ZoneData' is negative`
`/SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/../mDNSCore/mDNSEmbeddedAPI.h:2793: error: size of array 'sizecheck_ServiceInfoQuery' is negative`
`/SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/../mDNSCore/mDNSEmbeddedAPI.h:2795: error: size of array 'sizecheck_ClientTunnel' is negative`

**Problem:** /SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/../mDNSCore/uDNS.c:4990: error: size of array 'sizecheck_SearchListElem' is negative

**Problem: **`/SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/../mDNSShared/uds_daemon.c:3958: error: size of array 'sizecheck_registered_record_entry' is negative`
`/SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/../mDNSShared/uds_daemon.c:3959: error: size of array 'sizecheck_service_instance' is negative`
`/SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/../mDNSShared/uds_daemon.c:3962: error: size of array 'sizecheck_reply_state' is negative`

**Solution:** We can comment the problematic lines. **Please, let us know if you have an alternative way.**


**Problem:** `ld: warning in /usr/local/lib/libdnsinfo.a, file is not of required architecture`
`Undefined symbols:`
`  "_dns_configuration_copy", referenced from:`
`      _mDNSPlatformSetDNSConfig in mDNSMacOSX.o`
`  "_dns_configuration_free", referenced from:`
`      _mDNSPlatformSetDNSConfig in mDNSMacOSX.o`
`ld: symbol(s) not found`
**Solution:** Rebuild and load *configd* with all the required archs (cf plist).
**Problem:** `/SourceCache/mDNSResponder/mDNSResponder-176.2/mDNSMacOSX/helper.c:303: error: syntax error before 'gNotification'`
**Solution: ?** add `#include <CoreFoundation/CFUserNotification.h>` 
------------------------------------------------------------------------
### mDNSResponderSystemLibraries (ok)
`darwinbuild ``mDNSResponderSystemLibraries`

------------------------------------------------------------------------
### msdosfs
#### 9J61 (ok)

`/SourceCache/msdosfs/msdosfs-136.5/msdosfs.kextproj/msdosfs.kmodproj/msdosfs_conv.c:79:22: error: sys/time.h: No such file or directory`
`/SourceCache/msdosfs/msdosfs-136.5/msdosfs.kextproj/msdosfs.kmodproj/msdosfs_conv.c:80:23: error: sys/systm.h: No such file or directory`
`/SourceCache/msdosfs/msdosfs-136.5/msdosfs.kextproj/msdosfs.kmodproj/msdosfs_conv.c:81:24: error: sys/dirent.h: No such file or directory`
`It seems it looks like in XCD ([...]cts/include -I/XCD/SY/Library/Frameworks/Kernel.framework/PrivateHeaders -I/XCD/SY/Library/Frameworks/Kernel.framework/Headers -I/priva[...]) but there is no Kernel.framework originally.`
**Solution:** `chroot BuildRoot `
`ln -s /System/Library/Frameworks/Kernel.framework /XCD/SY/Library/Frameworks/Kernel.framework`
`exit`

then

**Problem:** `/SourceCache/msdosfs/msdosfs-136.5/newfs_msdos.tproj/newfs_msdos.c:55:27: error: sys/disklabel.h: No such file or directory`
Now it looks in XCD again ([...]ude -I/XCD/SY/Library/Frameworks/System.framework/PrivateHeaders -I/priva[...]...)
**Solution:** chroot BuildRoot 
`ln -s /System/Library/Frameworks/System.framework XCD/SY/Library/Frameworks/System.framework/`
exit

Though it has been succesfully built, the project remains in XCD (because of inheritance from the compilation which inherits that probably from another project built before).
**Problem:** XCD should not be here.

`** BUILD SUCCEEDED **`
`++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++`
` BUILD TIME: 0h 0m 10s`
`EXIT STATUS: 0`
`msdosfs - 12 files registered.`
`                                         40755 0 0 0 ./XCD`
`                                         40755 0 0 0 ./XCD/SY`
`                                         40755 0 0 0 ./XCD/SY/Library`
`                                         40755 0 0 0 ./XCD/SY/Library/Extensions`
`                                         40755 0 0 0 ./XCD/SY/Library/Extensions/msdosfs.kext`
`                                         40755 0 0 0 ./XCD/SY/Library/Extensions/msdosfs.kext/Contents`
`5b9a6e0ff3b5cc110a4411d1befd26e7f1e95042 100644 0 0 1050 ./XCD/SY/Library/Extensions/msdosfs.kext/Contents/Info.plist`
`                                         40755 0 0 0 ./XCD/SY/Library/Extensions/msdosfs.kext/Contents/MacOS`
`da39a3ee5e6b4b0d3255bfef95601890afd80709 100644 0 0 172844 ./XCD/SY/Library/Extensions/msdosfs.kext/Contents/MacOS/msdosfs`
`                                         40755 0 0 0 ./XCD/SY/Library/Filesystems`
`                                         40755 0 0 0 ./XCD/SY/Library/Filesystems/msdos.fs`
`                                         40755 0 0 0 ./XCD/SY/Library/Filesystems/msdos.fs/Contents`
`2260276cf80b31121312a84960b02313b5de152c 100644 0 0 7370 ./XCD/SY/Library/Filesystems/msdos.fs/Contents/Info.plist`
`                                         40755 0 0 0 ./XCD/SY/Library/Filesystems/msdos.fs/Contents/Resources`
`                                         40755 0 0 0 ./XCD/SY/Library/Filesystems/msdos.fs/Contents/Resources/English.lproj`
`7fba01433478b730cb5223e8020f73f238175537 100644 0 0 652 ./XCD/SY/Library/Filesystems/msdos.fs/Contents/Resources/English.lproj/InfoPlist.strings`
`a0d40033156fff78a4da42fc71d6610cbf8e4375 100755 0 0 45996 ./XCD/SY/Library/Filesystems/msdos.fs/msdos.util`
`                                         40755 0 0 0 ./sbin`
`91567a895ccaf37aefaf038859e349643d2304ae 100755 0 0 70668 ./sbin/fsck_msdos`
`d90105816c3bcca49c590d567b953d53517da82e 100755 0 0 38556 ./sbin/mount_msdos`
`9419c51c15a47d4d68942272f3dff58640f1457f 100755 0 0 54284 ./sbin/newfs_msdos`
`                                         40755 0 0 0 ./usr`
`                                         40755 0 0 0 ./usr/share`
`                                         40755 0 0 0 ./usr/share/man`
`                                         40755 0 0 0 ./usr/share/man/man8`
`9bf0b30b84ac2c58fdc021cb52d91bb6b65515f4 100644 0 0 3856 ./usr/share/man/man8/fsck_msdos.8`
`a8f9318a3d0558133ffc70bac75f013153cd8e70 100644 0 0 4080 ./usr/share/man/man8/mount_msdos.8`
`5ae5813033108e545cc0241ac25dda3935c2415e 100644 0 0 1864 ./usr/share/man/man8/msdos.util.8`
`b2ad8ef73fcc0f64b6ad4ed0852f336956d2ee3e 100644 0 0 5579 ./usr/share/man/man8/newfs_msdos.8`
**Solution:** **let us now if you have one**

------------------------------------------------------------------------

### netinfo
#### 9J61 (ok)
**Problem:** `nibind_prot.x:1: error: netinfo/nibind_prot.x: No such file or directory`

`ni_prot.x:1: error: netinfo/ni_prot.x: No such file or directory`
**Solution:** ..According to DTrace, nibind_prot.x is searched in many locations:

`  0  17720                       open:entry cc1 nibind_prot.x`
`  0  17720                       open:entry cc1 /usr/local/include/netinfo/nibind_prot.x`
`  0  17720                       open:entry cc1 /usr/lib/gcc/i686-apple-darwin9/4.0.1/include/netinfo/nibind_prot.x`
`  0  17720                       open:entry cc1 /usr/include/netinfo/nibind_prot.x`
So the trick would be to `touch BuildRoot/usr/local/include/netinfo/ni_prot.x BuildRoot/usr/local/include/netinfo/nibind_prot.x`
Do not use the real .x and its content, it will lead to a too deep nested include error.
**Problem:** `ld: can't open order file: /AppleInternal/OrderFiles/NetInfo.order`

`ld: can't open order file: /AppleInternal/OrderFiles/NetInfo.order`
**Solution:** `mkdir -p BuildRoot/AppleInternal/OrderFiles`
`touch BuildRoot/AppleInternal/OrderFiles/NetInfo.order`

------------------------------------------------------------------------

net_snmp
9J61

gcc -dynamiclib -single_module ${wl}-undefined ${wl}dynamic_lookup -o .libs/libnetsnmpagent.15.1.2.dylib  .libs/snmp_agent.o .libs/snmp_vars.o .libs/agent_read_config.o .libs/agent_registry.o .libs/agent_index.o .libs/agent_trap.o .libs/kernel.o .libs/agent_handler.o mibgroup/snmpv3/.libs/usmConf.o mibgroup/agentx/.libs/master.o mibgroup/agentx/.libs/subagent.o mibgroup/utilities/.libs/execute.o mibgroup/utilities/.libs/iquery.o mibgroup/mibII/.libs/vacm_conf.o mibgroup/agentx/.libs/protocol.o mibgroup/agentx/.libs/client.o mibgroup/agentx/.libs/master_admin.o mibgroup/agentx/.libs/agentx_config.o  ../snmplib/.libs/libnetsnmp.dylib  -arch ppc -arch i386 -F/System/Library/PrivateFrameworks/ -F/System/Library/Frameworks/ -arch ppc -arch i386 -arch ppc -arch i386 -framework IOKit -framework CoreFoundation -framework CoreServices -framework ApplicationServices -framework DiskArbitration -install_name  /usr/lib/libnetsnmpagent.15.dylib -compatibility_version 17 -current_version 17.2 -Wl,-single_module
ldld:: framework not found CoreServices




------------------------------------------------------------------------

### ntfs
#### 9J61 (ok)
**Problem:**

`/SourceCache/ntfs/ntfs-52/kext/ntfs_vfsops.c:44:23: error: sys/cdefs.h: No such file or directory`
`/SourceCache/ntfs/ntfs-52/kext/ntfs_vfsops.c:45:22: error: sys/attr.h: No such file or directory`
`/SourceCache/ntfs/ntfs-52/kext/ntfs_vfsops.c:46:21: error: sys/buf.h: No such file or directory`
`/SourceCache/ntfs/ntfs-52/kext/ntfs_vfsops.c:47:22: error: sys/disk.h: No such file or directory`
`/SourceCache/ntfs/ntfs-52/kext/ntfs_vfsops.c:48:23: error: sys/errno.h: No such file or directory`
`/SourceCache/ntfs/ntfs-52/kext/ntfs_vfsops.c:49:23: error: sys/fcntl.h: No such file or directory`
It also seek into: [...]lude -I/XCD/SY/Library/Frameworks/Kernel.framework/PrivateHeaders -I/XCD/SY/Library/Frameworks/Kernel.framework/Headers -I/pri[...]
**Solution:** see below/above (copy/link required headers).
------------------------------------------------------------------------

### objc4
#### 9J61 (ok)
#### 9F33 (ok)
Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then:



darwinbuild -init 9F33pd1


The plist file above contains some patches that tend to avoid most of the errors just below.



`darwinbuild objc4`


**Problem:** `/SourceCache/objc4/objc4-371.2/runtime/objc-private.h:49:22: error: auto_zone.h: No such file or directory`
<span style="font-family:Helvetica;font-weight:bold">Solution: <span style="color:rgb(255,0,0);font-family:Arial"><span style="font-size:small"><span style="color:rgb(0,0,0);font-weight:normal">11/12/2008, the AutoZone project sources have been released by Apple: <span style="font-family:courier new"><span style="font-size:12px">darwinbuild autozone && darwinbuild -load autozone</span></span></span> </span></span></span>

**Problem:** `couldn't exec /XCD/loper/usr/bin/libtool: No such file or directory`
**Solution: `**cp' or `ln' -s from `usr/bin/libtool`

In fact, the patches remove the *libauto* dependency and *libobjc* is now "pure":

__
__

`otool -L /usr/lib/libobjc.A.dylib`
`/usr/lib/libobjc.A.dylib:`
 `/usr/lib/libobjc.A.dylib (compatibility version 1.0.0, current version 227.0.0)`
 `/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)`
 `/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.1.1)`


Of course, we still need and hope to have GC support a day.
11/12/2008, the AutoZone project sources have been released by Apple: <span style="font-family:courier new"><span style="font-size:12px"><span style="color:rgb(204,204,204)">darwinbuild autozone && darwinbuild -load autozone</span></span></span>
------------------------------------------------------------------------
### pam_modules
#### 9J61
**Problem: **`/private/var/tmp/pam_modules/pam_modules-36.2.obj/pam_serialnumber/pam_serialnumber.c:40:46: error: AppleSystemInfo/ASI_SerialNumber.h: No such file or directory/private/var/tmp/pam_modules/pam_modules-36.2.obj/pam_serialnumber/pam_serialnumber.c:40:46:`

` error: AppleSystemInfo/ASI_SerialNumber.h: No such file or directory`
****

`  0  17720                       open:entry cc1 /usr/include/pam/AppleSystemInfo/ASI_SerialNumber.h`
`  0  17720                       open:entry cc1 /usr/local/include/AppleSystemInfo/ASI_SerialNumber.h`
`  0  17720                       open:entry cc1 /usr/lib/gcc/i686-apple-darwin9/4.0.1/include/AppleSystemInfo/ASI_SerialNumber.h`
`  0  17720                       open:entry cc1 /usr/include/AppleSystemInfo/ASI_SerialNumber.h`
`  1  17720                       open:entry cc1 /usr/include/pam/AppleSystemInfo/ASI_SerialNumber.h`
`  1  17720                       open:entry cc1 /usr/local/include/AppleSystemInfo/ASI_SerialNumber.h`
`  1  17720                       open:entry cc1 /usr/lib/gcc/powerpc-apple-darwin9/4.0.1/include/AppleSystemInfo/ASI_SerialNumber.h`
`  1  17720                       open:entry cc1 /usr/include/AppleSystemInfo/ASI_SerialNumber.h`
Then

`mkdir -p BuildRoot/usr/include/pam/AppleSystemInfo`
`touch BuildRoot/usr/include/pam/AppleSystemInfo/ASI_SerialNumber.h`
This leads to:

`/usr/bin/cc   -lpam -pipe -no-cpp-precomp -arch ppc -arch i386          -L/usr/local/lib -lAppleSystemInfo -framework CoreFoundation -framework IOKit  -g -Os -pipe -Ddarwin -no-cpp-precomp -Wall -I/usr/include/pam -pipe -no-cpp-precomp -arch ppc -arch i386 -bundle -o /private/var/tmp/pam_modules/pam_modules-36.2.obj/pam_serialnumber/pam_serialnumber.so /private/var/tmp/pam_modules/pam_modules-36.2.obj/pam_serialnumber/pam_serialnumber.o`
`ld: library not found for -lAppleSystemInfo`
****
****
__Notes:__ no path with *AppleSystemInfo* as a directory exist on my mac (10.5.7).

See <http://darwinbuild.macosforge.org/trac/ticket/79>
------------------------------------------------------------------------
### passwordserver_saslkerberos
#### 9J61
ld: warning in /usr/lib/libkrb5.dylib, missing required architecture ppc64 in file
ld: warning in /usr/lib/libSystemStubs.a, missing required architecture ppc64 in file
Undefined symbols:
  "_gss_wrap", referenced from:
      _sasl_gss_encode in gssapi.o
------------------------------------------------------------------------
### postfix
#### 9J61
xsasl_cyrus_server.c:77:18: error: sasl.h: No such file or directoryxsasl_cyrus_server.c:77:18: error: sasl.h: No such file or directory

xsasl_cyrus_server.c:78:22: xsasl_cyrus_server.c:78:22:error: saslutil.h: No such file or directory



------------------------------------------------------------------------
### pdisk
#### 9J61 (ok)
**Problem:** `/SourceCache/cron/cron-30/cron/do_command.c:38:28: error: IOKit/IOKitLib.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:39:35: error: IOKit/pwr_mgt/IOPMLib.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:40:32: error: IOKit/pwr_mgt/IOPM.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:41:28: error: IOKit/IOReturn.h: No such file or directory`
`/SourceCache/cron/cron-30/cron/do_command.c:38:28: error: IOKit/IOKitLib.h: No such file or directory`
`need IOKitUser`
------------------------------------------------------------------------
### ruby
<span style="font-family:Helvetica;font-size:12px"><span style="font-size:13px"><span style="font-family:arial">(Implicitly needed for copystrings & copyplist in </span></span>**IOKitUser**) and explicitly needed for many projects using ruby scripts.</span>
#### 9J61
**Problem:** 
**Solution:** rebuild SystemStubs with a custom plist including all arch.
#### 9G55

**** `ld: couldn't dlopen() /usr/lib/libdtrace.dylib: dlopen(/usr/lib/libdtrace.dylib, 1): image not found`
**Solution:** <span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild dtrace && darwinbuild -load dtrace</span></span>


#### 9F33
**** `ld: couldn't dlopen() /usr/lib/libdtrace.dylib: dlopen(/usr/lib/libdtrace.dylib, 1): image not found`
**Solution:** <span style="font-family:courier new,monospace"><span style="font-size:small">darwinbuild dtrace && darwinbuild -load dtrace</span></span>




**Problem: **Symbolication error..
**Solution:** **Please, let us know if you have one!**

![](/img/developers/darwinbuild/troubleshooting/ruby.png)

------------------------------------------------------------------------

### security_ocspd
9J61

/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h: In static member function 'static void Security::MacOSError::check(OSStatus)':

/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h:103: error: 'noErr' was not declared in this scope


------------------------------------------------------------------------
### securityd
9J61

src/acls.h:40:39: error: securityd_server/sscommon.h: No such file or directory

src/dbcrypto.h:31:37: error: securityd_client/ssblob.h: No such file or directory

src/notifications.h:34:39: error: securityd_client/ssclient.h: No such file or directory

src/SharedMemoryServer.h:8:49: error: securityd_client/SharedMemoryCommon.h: No such file or directory

/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h: In static member function 'static void Security::MacOSError::check(OSStatus)':
/usr/local/SecurityPieces/Frameworks/security_utilities.framework/Headers/errors.h:103: error: 'noErr' was not declared in this scope.
------------------------------------------------------------------------

### screen
#### 9J61 (ok)
**Problem:**

`/SourceCache/screen/screen-12/screen/screen.c:105:19:/SourceCache/screen/screen-12/screen/screen.c:105:19:  error: error: vproc.h: No such file or directory`

`/SourceCache/screen/screen-12/screen/screen.c:106:24: error: vproc_priv.h: No such file or directory`
`/SourceCache/screen/screen-12/screen/screen.c:106:24: error: vproc_priv.h: No such file or directory`
**Solution:** `cp -R BuildRoot/private/var/tmp/launchd_libs/launchd_libs-258.22.root/usr/include/* BuildRoot/usr/include/ 
`
`cp -R BuildRoot/private/var/tmp/launchd_libs/launchd_libs-258.22.root/usr/local/include/* BuildRoot/usr/local/include/`
------------------------------------------------------------------------
### smb
#### 9J61
**Problem:** /SourceCache/smb/smb-348.7/lib/smb/ctx.c:45:31: error: URLMount/URLMount.h: No such file or directory

/SourceCache/smb/smb-348.7/lib/smb/ctx.c:49:39: error: CoreServices/CoreServices.h: No such file or directory
/SourceCache/smb/smb-348.7/lib/smb/ctx.c:50:37: error: CFNetwork/CFNetServices.h: No such file or directory
/SourceCache/smb/smb-348.7/lib/smb/ctx.c:51:87: error: CFNetwork/CFNetServicesPriv.h: No such file or directory
------------------------------------------------------------------------
### subversion
#### 9J61
**Problem:** checking for Apache module support via DSO through APXS... /SourceCache/subversion/subversion-16/subversion/configure: line 3130: apxs: command not found
configure: error: no - APXS refers to an old version of Apache
                     Unable to locate /mod_dav.h


------------------------------------------------------------------------
### syslog
#### 9J61
**Problem:** ===== Building aslmanager RELEASE =====

/usr/bin/cc -arch ppc -arch i386 -g -Os -pipe -Wall -mdynamic-no-pic -DINET6 -pipe -no-cpp-precomp -arch ppc -arch i386 -I/private/var/tmp/syslog/syslog-69.0.4.obj/aslmanager -c -o /private/var/tmp/syslog/syslog-69.0.4.obj/aslmanager/aslmanager.o aslmanager.c
===== Linking aslmanager RELEASE =====
/usr/bin/cc -arch ppc -arch i386            -dead_strip -o /private/var/tmp/syslog/syslog-69.0.4.sym/aslmanager 
  /private/var/tmp/syslog/syslog-69.0.4.obj/aslmanager/aslmanager.o
Undefined symbols for architecture ppc:
  "_asl_file_close", referenced from:
      _do_match in aslmanager.o
      _do_match in aslmanager.o
      _do_match in aslmanager.o
  "_asl_file_open_write", referenced from:
      _do_match in aslmanager.o
  "_asl_file_open_read", referenced from:
      _do_match in aslmanager.o
  "_asl_file_save", referenced from:
      _do_match in aslmanager.o
  "_asl_file_match", referenced from:
      _do_match in aslmanager.o
ld: symbol(s) not found for architecture ppc
collect2: ld returned 1 exit status
Undefined symbols for architecture i386:
  "_asl_file_close", referenced from:
      _do_match in aslmanager.o
      _do_match in aslmanager.o
      _do_match in aslmanager.o
      _do_match in aslmanager.o
  "_asl_file_open_write", referenced from:
      _do_match in aslmanager.o
  "_asl_file_open_read", referenced from:
      _do_match in aslmanager.o
  "_asl_file_save", referenced from:
      _do_match in aslmanager.o
  "_asl_file_match", referenced from:
      _do_match in aslmanager.o
ld: symbol(s) not found for architecture i386


------------------------------------------------------------------------




### system_cmds


#### 9J61
Problem:
Referenced from: /usr/bin/arch
Reason: image not found
gcc-4.0: Invalid arch name : -D__MACH30__
**Solution:** `darwinbuild  -load system_cmds` (also add manually [PureFoundation](../../../purefoundation.html).root.tar.bz2 in order to satisfy arch dependency to Foundation.framework)

dynamic_pager.c:35:42: error: IOKit/pwr_mgt/IOPMLibPrivate.h: No such file or directory
dynamic_pager.c:36:37: error: IOKit/ps/IOPowerSources.h: No such file or directory
dynamic_pager.c:37:44: error: IOKit/ps/IOPowerSourcesPrivate.h: No such file or directory
darwinbuild -headers IOKitUser

#### 9G55
#### 9F33
**Problem:** `dynamic_pager.c:35:42: error: IOKit/pwr_mgt/IOPMLibPrivate.h: No such file or directory`
`dynamic_pager.c:36:37: error: IOKit/ps/IOPowerSources.h: No such file or directory`
`dynamic_pager.c:37:44: error: IOKit/ps/IOPowerSourcesPrivate.h: No such file or directory`
`dynamic_pager.c:569: error: 'kIOMasterPortDefault' undeclared (first use in this function)`
`dynamic_pager.c:569: error: (Each undeclared identifier is reported only once`
`dynamic_pager.c:569: error: for each function it appears in.)`
`dynamic_pager.c:570: error: 'kIOReturnSuccess' undeclared (first use in this function)`
`dynamic_pager.c:582: error: syntax error before 'kIOPMBatteryPowerKey'`
``
`darwinbuild -headers IOKitUser`
darwinbuild IOKitUser 
darwinbuild -load IOKitUser
chroot BuildRoot
cp -R /XCD/SY/Library/Frameworks/IOKit.framework /System/Library/Frameworks
cp -R /System/Library/Frameworks/IOKit.framework.origin/* /System/Library/Frameworks/IOKit.framework/


``
``
Since Foundation is not part of Darwin, we need to patch the source so that it doesn't need Foundation any more (Sometimes older versions of the same source can give a hint).

Alternative Solution: [PureFoundation](../../../purefoundation.html) can be added manually to satisfy arch dependency to *Foundation.framework*.
root@europa:/Volumes/Builds/9G55/BuildRoot# mv PureFoundation/Foundation.framework System/Library/Frameworks
root@europa:/Volumes/Builds/9G55/BuildRoot# chroot .
europa# arch
NSObject +load
i386


**Problem: arch**
``
`  Referenced from: /System/Library/Frameworks/Security.framework/Versions/A/Security`
`  Expected in: /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation`

****
`mv /usr/bin/arch /usr/bin/arch.origin`
`echo 'uname -p' > /usr/bin/arch`
`chmod +x /usr/bin/arch`
**Alterative-solution:** Satisfy the expected dependency with a patched CF-lite.

**
**
Let's look the dependencies of `arch' with `otool'.

otool -L /usr/bin/arch
`              [...]`
 `/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation...`
 [...]
 `/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation...`


> > otool -L /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation
> >  [...]<span style="color:rgb(68,68,68)">
> > </span><span style="color:rgb(68,68,68)">
> > </span><span style="font-family:Helvetica;font-size:12px"> <span style="font-family:courier new"><span style="color:rgb(68,68,68)">[...]
> > </span></span></span>
> > > > otool -L /System/Library/Frameworks/Security.framework/Versions/A/Security
> > > > <span style="color:rgb(68,68,68)">
> > > > </span> /usr/lib/libstdc++.6.dylib...<span style="color:rgb(68,68,68)">
> > > > </span> /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation...<span style="color:rgb(68,68,68)">
> > > > </span> /usr/lib/libgcc_s.1.dylib...<span style="color:rgb(68,68,68)">
> > > > </span> /usr/lib/libSystem.B.dylib...




*
*
**
grep kCFBundleResourceSpecificationKey /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation
Binary file /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation matches



In the BuildRoot, CF-lite returns nothing.



grep kCFBundleResourceSpecificationKey /Volumes/Builds/9F33/BuildRoot/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation 


So we have mainly three choices:
-   
-   
-   to short-circuit `arch'
We use *CF-lite*, but this time it seems to light. 



A workaround in this case consists to recreate the missing prototype and method *_kCFBundleResourceSpecificationKey* expected in *CF-lite*, build and then deploy it.

The real state looks like:


![](/img/developers/darwinbuild/troubleshooting/system_cmds_9F33pd1.png)


In fact, there is also **Foundation.framework missing**.
**Solution: **See PureFoundation. e.g., with arch:

`root@europa:/Volumes/Builds/``9G55/BuildRoot# mv PureFoundation/Foundation.``framework System/Library/Frameworks`
`root@europa:/Volumes/Builds/``9G55/BuildRoot# chroot .
europa# arch
NSObject +load
i386`

------------------------------------------------------------------------
### tcl
`darwinbuild tcl`
****
#### 9J61
#### 9G55

Fetch [9G55pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9G55pd1.plist) into *.build* directory of your DarwinBuild repository, then:



darwinbuild -init 9G55pd1


The plist file above contains some patches that tend to avoid some errors.



`darwinbuild tcl`

****

`Compiler: /XCD/loper/Library/Xcode/Plug-ins/GCC 4.0.xcplugin/Contents/Resources/gcc`

`Reason:   sh: /XCD/loper/Library/Xcode/Plug-ins/GCC 4.0.xcplugin/Contents/Resources/gcc: No such file or directory`

****

**
**

****

****

**
**

**Problem: **`dyld: Library not loaded: /System/Library/Frameworks/CoreFoundation/Versions/A/CoreFoundation
Referenced from: /private/var/tmp/tcl/tcl-64.sym/tcl/tclsh8.4
Reason: image not found`

**Solution:** Fetch [9F33pd1.plist](http://code.google.com/p/puredarwin/source/browse/trunk/plists/9F33pd1.plist) into *.build* directory of your DarwinBuild repository, then rebuild CF:

<span style="font-family:courier new"><span style="font-size:12px">darwinbuild -init 9F33pd1 && darwinbuild CF && darwinbuild -load CF</span></span>

After recompilation of CF, dependency is fixed:

`/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)`
**Next solution: **See <http://darwinbuild.macosforge.org/trac/ticket/41#comment:1> / [rdar://problem/6488974](http://rdar://problem/6488974)
------------------------------------------------------------------------
### tcl_ext
9J61

/private/var/tmp/tcl_ext/tcl_ext-64.sym/SRC/tcl/tcl/macosx/../unix/../compat/strstr.c:67: error: 'NULL' undeclared (first use in this function)
------------------------------------------------------------------------
### tcl_tk
9J61

/private/var/tmp/tcl_tk/tcl_tk-64.sym/SRC/tcl/tcl/macosx/../unix/../compat/strstr.c:67: error: 'NULL' undeclared (first use in this function)

------------------------------------------------------------------------
### tidy
#### 9J61 (ok)
**Problem:** `ld: can't open order file: /usr/local/lib/OrderFiles/libtidy.order`
**Solution:** `touch BuildRoot/usr/local/lib/OrderFiles/libtidy.order`
then

`++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++`
` BUILD TIME: 0h 0m 43s`
`EXIT STATUS: 0`


------------------------------------------------------------------------
### usertemplate
#### 9J61 (ok)
**Problem:** `/bin/sh: /Developer/Tools/SetFile: No such file or directory`

**Solution: **SetFile appears to not be available.

`ln -fs /usr/bin/true /Developer/Tools/SetFile`



Then it builds.

------------------------------------------------------------------------


### webdavfs
#### 9J61
**Problem: **dependency on cocoa header

/SourceCache/webdavfs/webdavfs-252.8/webdav_cert_ui.tproj/webdav_cert_ui_Prefix.pch:29:28: error: Cocoa/Cocoa.h: No such file or directory

------------------------------------------------------------------------
### xnu

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#### 9J61 (ok)
.
#### 9G55 (ok)
.
#### 9F33
<span style="font-size:12px;font-weight:normal"><span style="color:rgb(153,153,153)"><span style="color:rgb(0,0,0)">**Problem (9F33): **/bin/sh: /usr/local/bin/ctfmerge: No such file or directory
**Solution:** It needs libdwarf and libelf
**Problem (9F33)****:**</span>/</span>usr/local/bin/ctfmerge -l xnu -o /private/var/tmp/xnu/xnu-1228.7.58.obj/RELEASE_I386/./mach_kernel.ctfsys........</span>
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
`[...]`
`install: /private/var/tmp/xnu/xnu-1228.7.58.obj/RELEASE_I386/./mach_kernel.sys.dSYM/./Contents/Resources/DWARF//mach_kernel.sys: No such file or directory`
`make[2]: *** [/private/var/tmp/xnu/xnu-1228.7.58.sym/mach_kernel] Error 71`
`make[2]: *** Waiting for unfinished jobs....`
`WARNING: ctfmerge: Can't read input file /private/var/tmp/xnu/xnu-1228.7.58.obj/RELEASE_I386/*/RELEASE/*.*o.ctf: No such file or directory`
`ERROR: ctfmerge: Some input files were inaccessible`
`Removing /private/var/tmp/xnu/xnu-1228.7.58.obj/RELEASE_I386/./mach_kernel.ctfsys`
`install: /private/var/tmp/xnu/xnu-1228.7.58.obj/RELEASE_I386/./mach_kernel.ctfsys: No such file or directory`
`make[2]: *** [/private/var/tmp/xnu/xnu-1228.7.58.root/mach_kernel] Error 71`
**Solution: ?**
------------------------------------------------------------------------
### xar
`darwinbuild xar`
#### 96J1 (ok)
darwinbuild -load libxml2 is needed
------------------------------------------------------------------------
### zsh
`darwinbuild zsh`
****
#### 96J1 (ok)

#### 9G55 (ok)

------------------------------------------------------------------------
To be continued...

