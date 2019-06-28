# Microsoft Developer Studio Generated NMAKE File, Based on Saver.dsp
!IF "$(CFG)" == ""
CFG=Saver - Win32 Release
!MESSAGE No configuration specified. Defaulting to Saver - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Saver - Win32 Release" && "$(CFG)" != "Saver - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Saver.mak" CFG="Saver - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Saver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Saver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Saver - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SwarmSaver.scr"

!ELSE 

ALL : "$(OUTDIR)\SwarmSaver.scr"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Drawwnd.obj"
	-@erase "$(INTDIR)\Saver.obj"
	-@erase "$(INTDIR)\Saver.pch"
	-@erase "$(INTDIR)\Saver.res"
	-@erase "$(INTDIR)\Saverdlg.obj"
	-@erase "$(INTDIR)\Saverwnd.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SwarmSaver.scr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)\Saver.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Saver.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Saver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\SwarmSaver.pdb" /machine:I386 /out:"$(OUTDIR)\SwarmSaver.scr" 
LINK32_OBJS= \
	"$(INTDIR)\Drawwnd.obj" \
	"$(INTDIR)\Saver.obj" \
	"$(INTDIR)\Saver.res" \
	"$(INTDIR)\Saverdlg.obj" \
	"$(INTDIR)\Saverwnd.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\SwarmSaver.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Saver - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SwarmSaver.scr" "$(OUTDIR)\Saver.bsc"

!ELSE 

ALL : "$(OUTDIR)\SwarmSaver.scr" "$(OUTDIR)\Saver.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Drawwnd.obj"
	-@erase "$(INTDIR)\Drawwnd.sbr"
	-@erase "$(INTDIR)\Saver.obj"
	-@erase "$(INTDIR)\Saver.pch"
	-@erase "$(INTDIR)\Saver.res"
	-@erase "$(INTDIR)\Saver.sbr"
	-@erase "$(INTDIR)\Saverdlg.obj"
	-@erase "$(INTDIR)\Saverdlg.sbr"
	-@erase "$(INTDIR)\Saverwnd.obj"
	-@erase "$(INTDIR)\Saverwnd.sbr"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\Stdafx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Saver.bsc"
	-@erase "$(OUTDIR)\SwarmSaver.ilk"
	-@erase "$(OUTDIR)\SwarmSaver.pdb"
	-@erase "$(OUTDIR)\SwarmSaver.scr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Saver.pch" /Yu"Stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Saver.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Saver.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Drawwnd.sbr" \
	"$(INTDIR)\Saver.sbr" \
	"$(INTDIR)\Saverdlg.sbr" \
	"$(INTDIR)\Saverwnd.sbr" \
	"$(INTDIR)\Stdafx.sbr"

"$(OUTDIR)\Saver.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\SwarmSaver.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\SwarmSaver.scr" 
LINK32_OBJS= \
	"$(INTDIR)\Drawwnd.obj" \
	"$(INTDIR)\Saver.obj" \
	"$(INTDIR)\Saver.res" \
	"$(INTDIR)\Saverdlg.obj" \
	"$(INTDIR)\Saverwnd.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\SwarmSaver.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "Saver - Win32 Release" || "$(CFG)" == "Saver - Win32 Debug"
SOURCE=.\Drawwnd.cpp

!IF  "$(CFG)" == "Saver - Win32 Release"

DEP_CPP_DRAWW=\
	".\drawwnd.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Drawwnd.obj" : $(SOURCE) $(DEP_CPP_DRAWW) "$(INTDIR)"\
 "$(INTDIR)\Saver.pch"


!ELSEIF  "$(CFG)" == "Saver - Win32 Debug"

DEP_CPP_DRAWW=\
	".\drawwnd.h"\
	

"$(INTDIR)\Drawwnd.obj"	"$(INTDIR)\Drawwnd.sbr" : $(SOURCE) $(DEP_CPP_DRAWW)\
 "$(INTDIR)" "$(INTDIR)\Saver.pch"


!ENDIF 

SOURCE=.\Saver.cpp

!IF  "$(CFG)" == "Saver - Win32 Release"

DEP_CPP_SAVER=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\Saverdlg.h"\
	".\saverwnd.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Saver.obj" : $(SOURCE) $(DEP_CPP_SAVER) "$(INTDIR)"\
 "$(INTDIR)\Saver.pch"


!ELSEIF  "$(CFG)" == "Saver - Win32 Debug"

DEP_CPP_SAVER=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\Saverdlg.h"\
	".\saverwnd.h"\
	

"$(INTDIR)\Saver.obj"	"$(INTDIR)\Saver.sbr" : $(SOURCE) $(DEP_CPP_SAVER)\
 "$(INTDIR)" "$(INTDIR)\Saver.pch"


!ENDIF 

SOURCE=.\Saver.rc
DEP_RSC_SAVER_=\
	".\res\cursor1.cur"\
	".\res\Saver.ico"\
	".\res\Saver.rc2"\
	

"$(INTDIR)\Saver.res" : $(SOURCE) $(DEP_RSC_SAVER_) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Saverdlg.cpp

!IF  "$(CFG)" == "Saver - Win32 Release"

DEP_CPP_SAVERD=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\Saverdlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Saverdlg.obj" : $(SOURCE) $(DEP_CPP_SAVERD) "$(INTDIR)"\
 "$(INTDIR)\Saver.pch"


!ELSEIF  "$(CFG)" == "Saver - Win32 Debug"

DEP_CPP_SAVERD=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\Saverdlg.h"\
	

"$(INTDIR)\Saverdlg.obj"	"$(INTDIR)\Saverdlg.sbr" : $(SOURCE) $(DEP_CPP_SAVERD)\
 "$(INTDIR)" "$(INTDIR)\Saver.pch"


!ENDIF 

SOURCE=.\Saverwnd.cpp

!IF  "$(CFG)" == "Saver - Win32 Release"

DEP_CPP_SAVERW=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\saverwnd.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Saverwnd.obj" : $(SOURCE) $(DEP_CPP_SAVERW) "$(INTDIR)"\
 "$(INTDIR)\Saver.pch"


!ELSEIF  "$(CFG)" == "Saver - Win32 Debug"

DEP_CPP_SAVERW=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\saverwnd.h"\
	

"$(INTDIR)\Saverwnd.obj"	"$(INTDIR)\Saverwnd.sbr" : $(SOURCE) $(DEP_CPP_SAVERW)\
 "$(INTDIR)" "$(INTDIR)\Saver.pch"


!ENDIF 

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Saver - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)\Saver.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\Saver.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Saver - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Saver.pch" /Yc"Stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\Stdafx.sbr"	"$(INTDIR)\Saver.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

