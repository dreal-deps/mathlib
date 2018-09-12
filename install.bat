@echo off
set Clcomp=""
set GCCcomp=""
set STATIC=""
set DLL=""
set CHECK=""
set TRUE="true"

:Loop
    IF "%1"=="" GOTO Continue  
    IF "%1"=="--cl"  set  CLcomp=TRUE 
    IF "%1"=="--gcc" set GCCcomp=TRUE
	IF "%1"=="--dll" set DLL=TRUE
	IF "%1"=="--static" set STATIC=TRUE
	IF "%1"=="--test" set CHECK=TRUE
	IF "%1"=="--help"  GOTO help
   SHIFT
   GOTO Loop
:Continue
IF %Clcomp%==TRUE IF %GCCcomp%==TRUE  echo you  can't use -gcc and -cl together 
IF %Clcomp%==TRUE IF %GCCcomp%==TRUE GOTO END

IF %DLL%==TRUE IF %STATIC%==TRUE  echo you  can't use -static and -dll together 
IF %DLL%==TRUE IF %STATIC%==TRUE GOTO END

IF %Clcomp%=="" IF %GCCcomp%=="" set Clcomp=TRUE
IF %DLL%=="" IF %STATIC%=="" set DLL=TRUE


IF %Clcomp%==TRUE  GOTO cl
IF %GCCcomp%==TRUE GOTO gcc


:cl
  echo Copying  necessary files
  copy .\NT\CL\NT.bat .
  IF %STATIC%==TRUE call nt.bat -static
  IF %DLL%==TRUE call nt.bat -dll
  cd tst 
  echo Perform testing
  IF %CHECK%==TRUE call check.bat
  cd ..
  GOTO END

:gcc
  echo Copying  necessary files
  copy .\NT\GCC\cyg.bat .
  IF %STATIC%==TRUE call cyg.bat -static
  IF %DLL%==TRUE call cyg.bat -dll
  cd tst
  echo Perform testing
  IF %CHECK%==TRUE call checkcyg.bat
  cd ..
  GOTO END

:help
     echo   Usage: Install  [OPTION]...
	echo Options:
	echo     --help         Display this information
	echo     --static        Install as static library 
	echo     --dll           Install as dll (default option)
	echo     --cl            Compile with cl (default option)
	echo     --gcc           Compile with gcc 
	echo     --test          perform checking
  GOTO END
  
     

:END
