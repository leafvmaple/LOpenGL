#ifndef LFILEREADER_H_
#define LFILEREADER_H_

#include "LDefine.h"
#include <cstring>

class LFileReader
{
	LFileReader();
	~LFileReader();

public:
	static bool Reader(const char* pszFileName, unsigned char** ppBuffer, size_t* puLen);
    static bool IsExist(const char* cszFileName);

	template<typename Model>
	static GLubyte* Convert(GLubyte* pBuffer, Model*& pModel, size_t nCount = 1)
	{
		size_t nLen = sizeof(Model) * nCount;
		pModel = (Model*) pBuffer;
		return pBuffer + nLen;
	}

	template<typename Model>
	static GLubyte* Convert(GLubyte* pBuffer, Model& pModel)
	{
		pModel = *((Model*) pBuffer);
		return pBuffer + sizeof(Model);
	}

	template<typename Model, int nSize>
	static GLubyte* Copy(GLubyte* pBuffer, Model pModel[nSize])
	{
		size_t nLen = sizeof(Model) * nSize;
		memcpy(&pModel, pBuffer, nLen);
		return pBuffer + nLen;
	}

	static GLubyte* Copy(GLubyte* pBuffer, char pModel[], size_t nLen = 0)
	{
		if (!nLen)
        {
			nLen = strlen((const char*)pBuffer);
#ifdef WIN32
			strcpy_s(pModel, nLen, (const char*)pBuffer);
#else
            strcpy(pModel, (const char*)pBuffer);
#endif
        }
		return pBuffer + nLen;
	}

	template<typename Model>
	static GLubyte* Copy(GLubyte* pBuffer, Model* pModel, size_t nCount = 1)
	{
		size_t nLen = sizeof(Model) * nCount;
		memcpy(pModel, pBuffer, nLen);
		return pBuffer + nLen;
	}
};

#endif
