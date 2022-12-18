#pragma once
namespace tl::launcher::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 0;
static const int version_patch = 18;
static const int version_build = 18;
static const char* version = "0.0.18";
static const char* version_hash = "cc9f86c";
static const char* build_version = "0.0.18.18-debug-cc9f86c";
#else
static const int version_major = 3;
static const int version_minor = 0;
static const int version_patch = 18;
static const int version_build = 18;
static const char* version = "3.0.18";
static const char* version_hash = "cc9f86c";
static const char* build_version = "3.0.18.18-master-cc9f86c";
#endif
}
//该文件自动生成，无需更改 
