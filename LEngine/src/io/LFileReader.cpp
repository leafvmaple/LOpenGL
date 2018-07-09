#include <cstdio>
#include <iostream>
#include "LAssert.h"
#include "io/LFileReader.h"
#include "lstring.h"

#ifdef WIN32
#include <io.h>
#endif

bool LFileReader::Reader(const char* pszFileName, GLubyte** ppBuffer, size_t* puLen)
{
	bool bResult = false;
	FILE* pFile = nullptr;

	do 
	{
		BOOL_ERROR_BREAK(ppBuffer);
		
		lfopen(pFile, pszFileName, "rb");
		BOOL_ERROR_BREAK(pFile);

		fseek(pFile, 0, SEEK_END);
		size_t uFileLen = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		GLubyte* pBuffer = new GLubyte[uFileLen];
		BOOL_ERROR_BREAK(pBuffer);

		*puLen = fread(pBuffer, 1, uFileLen, pFile);
		BOOL_ERROR_BREAK(*puLen);

		*ppBuffer = pBuffer;

		bResult = true;
	} while (0);

	if (pFile)
		fclose(pFile);

	return bResult;
}

bool LFileReader::IsExist(const char* cszFileName)
{
	FILE* pFile = nullptr;
	lfopen(pFile, cszFileName, "rb");
    if (pFile)
    {
        fclose(pFile);
        return true;
    }
    return false;
}
