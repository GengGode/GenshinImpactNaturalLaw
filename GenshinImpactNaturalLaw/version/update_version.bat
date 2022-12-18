for /f %%x in (version\version.ver) do (
	set version=%%x
)
for /f  "tokens=1,2,3,4 delims=.-" %%a  in  ("%version%")  do (
	set v1=%%a
	set v2=%%b
	set /a v3=%%c+1
    set /a v4=%%d+1
)

if exist version\version.branch (
	del version\version.branch
)
if exist version\version_hash.hash (
	del version\version_hash.hash
)

git rev-parse --abbrev-ref HEAD>>  version\version.branch
git log -n1 --format=format:"%%h">> version\version_hash.hash

for /f %%x in (version\version.branch) do (
	set v5=%%x
)
for /f %%x in (version\version_hash.hash) do (
	set v6=%%x
)



set newVersionP1=0
set newVersionP2=0
if exist version\version.ver (
	for /f "tokens=1,2 delims=.-" %%a in (version\version.ver) do (
		set newVersionP1=%%a
		set newVersionP2=%%b
	)
)

if not "!newVersionP1!"=="" (
	if %newVersionP1% GTR %v1% (
		set /a v1=%newVersionP1%
		set /a v2=0
		set /a v3=0
	)
)
if not "%newVersionP2%"=="" (
	if %newVersionP2% GTR %v2% (
		set /a v2=%newVersionP2%
		set /a v3=0
	)
)

if exist version\Version.h (
    del version\Version.h
)

echo #pragma once>>version\Version.h
echo namespace tl::launcher::version>>version\Version.h
echo {>>version\Version.h
echo %#ifdef _DEBUG>>version\Version.h
echo static const int version_major = 0;>>version\Version.h
echo static const int version_minor = %v2%;>>version\Version.h
echo static const int version_patch = %v3%;>>version\Version.h
echo static const int version_build = %v4%;>>version\Version.h
echo static const char* version = "0.%v2%.%v3%";>>version\Version.h
echo static const char* version_hash = "%v6%";>>version\Version.h
echo static const char* build_version = "0.%v2%.%v3%.%v4%-debug-%v6%";>>version\Version.h
echo %#else>>version\Version.h
echo static const int version_major = %v1%;>>version\Version.h
echo static const int version_minor = %v2%;>>version\Version.h
echo static const int version_patch = %v3%;>>version\Version.h
echo static const int version_build = %v4%;>>version\Version.h
echo static const char* version = "%v1%.%v2%.%v3%";>>version\Version.h
echo static const char* version_hash = "%v6%";>>version\Version.h
echo static const char* build_version = "%v1%.%v2%.%v3%.%v4%-%v5%-%v6%";>>version\Version.h
echo %#endif>>version\Version.h
echo }>>version\Version.h
echo //该文件自动生成，无需更改 >>version\Version.h

if exist version\version.ver (
    del version\version.ver
)

echo %v1%.%v2%.%v3%.%v4%>>version\version.ver

echo build version : %v1%.%v2%.%v3%.%v4%-%v5%-%v6% 
