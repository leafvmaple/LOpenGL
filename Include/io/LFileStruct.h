#ifndef _LFILESTUCT_H_
#define _LFILESTUCT_H_

#define defFILE_TAGLEN			8
#define defFILE_DESCLEN			64

#define MESH_SAVE_BONEBBOX  1
#define MAP_FILE_VERSION_PACKREGION 2

#include <string>
#include "LInterface.h"

struct TFileHeader
{
	char szCommonTag[defFILE_TAGLEN];
	char szModuleTag[defFILE_TAGLEN];
#ifdef __APPLE__
	__int32_t byVersion;
#elif _WIN32
    __int32 byVersion;
#endif
    char szDescription[defFILE_DESCLEN];
};

#endif // !_LFILESTUCT_H_
