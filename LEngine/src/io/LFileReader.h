#pragma once
#include <wtypes.h>
#include <atlconv.h>

class LFileReader
{
	LFileReader();
	~LFileReader();

public:
	static bool Reader(const char* pszFileName, unsigned char** ppBuffer, size_t* puLen);

	template<typename Model>
	static BYTE* Convert(BYTE* pBuffer, Model*& pModel, size_t nCount = 1)
	{
		size_t nLen = sizeof(Model) * nCount;
		pModel = (Model*) pBuffer;
		return pBuffer + nLen;
	}

	template<typename Model>
	static BYTE* Convert(BYTE* pBuffer, Model& pModel)
	{
		pModel = *((Model*) pBuffer);
		return pBuffer + sizeof(Model);
	}

	template<typename Model, int nSize>
	static BYTE* Copy(BYTE* pBuffer, Model pModel[nSize])
	{
		size_t nLen = sizeof(Model) * nSize;
		memcpy_s(&pModel, nLen, pBuffer, nLen);
		return pBuffer + nLen;
	}

	static BYTE* Copy(BYTE* pBuffer, TCHAR pModel[], size_t nLen = 0)
	{
		if (!nLen)
			nLen = strlen((LPCSTR)pBuffer);
		{
			USES_CONVERSION;
			strcpy_s(pModel, nLen, (LPCSTR)pBuffer);
		}
		return pBuffer + nLen;
	}

	template<typename Model>
	static BYTE* Copy(BYTE* pBuffer, Model* pModel, size_t nCount = 1)
	{
		size_t nLen = sizeof(Model) * nCount;
		memcpy_s(pModel, nLen, pBuffer, nLen);
		return pBuffer + nLen;
	}
};