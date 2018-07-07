#include <cstdio>
#include <iostream>
#include "LAssert.h"
#include "io/LFileReader.h"

#ifdef WIN32
#include <io.h>
#endif

bool LFileReader::Reader(const char* pszFileName, BYTE** ppBuffer, size_t* puLen)
{
	bool bResult = false;
	FILE* pFile = NULL;
	BYTE* pBuffer = NULL;
	size_t uFileLen;
	
	do 
	{
		BOOL_ERROR_BREAK(ppBuffer);
        
#ifdef WIN32
		fopen_s(&pFile, pszFileName, "rb");
		BOOL_ERROR_BREAK(pFile);
#else
        pFile = fopen(pszFileName, "rb");
        BOOL_ERROR_BREAK(pFile);
#endif

		fseek(pFile, 0, SEEK_END);
		uFileLen = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		pBuffer = new unsigned char[uFileLen];
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
