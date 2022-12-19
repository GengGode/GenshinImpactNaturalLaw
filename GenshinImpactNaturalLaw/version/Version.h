#pragma once
namespace tl::launcher::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 1;
static const int version_patch = 37;
static const int version_build = 54;
static const char* version = "0.1.37";
static const char* version_hash = "b2de168";
static const char* build_version = "0.1.37.54-debug-b2de168";
#else
static const int version_major = 3;
static const int version_minor = 1;
static const int version_patch = 37;
static const int version_build = 54;
static const char* version = "3.1.37";
static const char* version_hash = "b2de168";
static const char* build_version = "3.1.37.54-master-b2de168";
#endif
}
//该文件自动生成，无需更改 
