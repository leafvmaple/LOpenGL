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

#pragma pack(push, 1)
struct MeshDataBlocks
{
    unsigned int PositionBlock;
    unsigned int NormalBlock;
    unsigned int DiffuseBlock;
    unsigned int TextureUVW1Block;
    unsigned int TextureUVW2Block;
    unsigned int TextureUVW3Block;
    unsigned int FacesIndexBlock;
    unsigned int SubsetIndexBlock;
    unsigned int SkinInfoBlock;
    unsigned int LODInfoBlock;
    unsigned int FlexibleBodyBlock;
    unsigned int BBoxBlock;
    unsigned int BlendMeshBlock;
    unsigned int ExtendBlock[17];
};

struct _MeshHead
{
    unsigned int dwNumVertices;
    unsigned int dwNumFaces;
    unsigned int dwNumSubset;
    union
    {
        MeshDataBlocks Blocks;
        unsigned int dwBlocks[30];
    };
};

struct _MeshFileHead
{
    TFileHeader KSFileHeader_NotUse;
    unsigned int dwFileMask;
    unsigned int dwBlockLength;
    unsigned int dwVersion;
    unsigned int AnimationBlock_NotUse;
    unsigned int ExtendBlock_NotUse[10];
    unsigned int MeshCount_NotUse;
    const static unsigned int s_dwFileMask = 0x4d455348;
    const static unsigned int s_dwCurrentVersion = 0;
};
#pragma pack(pop)

struct LMESH_DATA
{
    unsigned int    dwID;
    std::string     strFileName;
    unsigned int    dwOption;
    unsigned int    dwOptionEx;
    
    unsigned int    dwNumVertices;
    unsigned int    dwNumFaces;
    unsigned int    dwNumSubset;
    unsigned int    dwMeshFVF;
    
    GLVec3          *pPos;
    GLVec3          *pNormals;
    GLCOLOR         *pDiffuse;
    GLVec3          *pUV1;
    GLVec3          *pUV2;
    GLVec3          *pUV3;
    
    unsigned int    *pFaceIndices;
    unsigned int    *pSubsetIndices;
    
    BYTE*           pbyFileBuffer;
};

#endif // !_LFILESTUCT_H_
