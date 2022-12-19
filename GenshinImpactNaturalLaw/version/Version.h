#pragma once
namespace tl::launcher::version
{
#ifdef _DEBUG
static const int version_major = 0;
static const int version_minor = 1;
static const int version_patch = 36;
static const int version_build = 53;
static const char* version = "0.1.36";
static const char* version_hash = "1530271";
static const char* build_version = "0.1.36.53-debug-1530271";
#else
static const int version_major = 3;
static const int version_minor = 1;
static const int version_patch = 36;
static const int version_build = 53;
static const char* version = "3.1.36";
static const char* version_hash = "1530271";
static const char* build_version = "3.1.36.53-master-1530271";
#endif
}
//该文件自动生成，无需更改 
