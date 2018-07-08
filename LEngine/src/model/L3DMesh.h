//
//  L3DMesh.h
//  LEngine
//
//  Created by LeafMaple on 2018/07/05.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef L3DMesh_h
#define L3DMesh_h

#include <string>
#include "LInterface.h"
#include "io/LFileDef.h"
#include "io/LFileStruct.h"

class L3DMaterial;

struct VertexFromatOffsetItem
{
    const static unsigned int s_dwMaxVertexElement = 8;
    unsigned int dwFVF;
    unsigned int dwNumElement;
    unsigned int dwSrcOffset[s_dwMaxVertexElement];
    unsigned int dwSrcStride[s_dwMaxVertexElement];
    unsigned int dwDestOffset[s_dwMaxVertexElement];
    unsigned int dwDestStride[s_dwMaxVertexElement];
    unsigned int dwElementFVF[s_dwMaxVertexElement];
};

static VertexFromatOffsetItem s_VertexFormat[] = {
    {L3DFVF_XYZ | L3DFVF_NORMAL | L3DFVF_TEX1, 3,   
    0,   1,  3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 12, 12, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0,  12, 24, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 12,  8, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
    L3DFVF_XYZ, L3DFVF_NORMAL, L3DFVF_TEX1, ELEMENT_FVF_END},//PosNorTex1

    {L3DFVF_XYZ | L3DFVF_NORMAL | L3DFVF_TEX2, 4,
    0,   1,  3,  4, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 12, 12, 12, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
    0,  12, 24, 32, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 12,  8,  8, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    L3DFVF_XYZ, L3DFVF_NORMAL, L3DFVF_TEX1, L3DFVF_TEX2, ELEMENT_FVF_END,},//PosNorTex2

    {L3DFVF_XYZ | L3DFVF_NORMAL | L3DFVF_TEX3, 5,
    0,   1,  3,  4,  5, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 12, 12, 12, 12, 0xffffffff, 0xffffffff, 0xffffffff, 
    0,  12, 24, 32, 40, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 12,  8,  8,  8, 0xffffffff, 0xffffffff, 0xffffffff, 
    L3DFVF_XYZ, L3DFVF_NORMAL, L3DFVF_TEX1, L3DFVF_TEX2, L3DFVF_TEX3, ELEMENT_FVF_END},//PosNorTex3 有问题

    {L3DFVF_XYZ | L3DFVF_DIFFUSE | L3DFVF_TEX1, 3,
    0,   2,  3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    12,  4, 12, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0,  12, 28, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 16,  8, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    L3DFVF_XYZ, L3DFVF_DIFFUSE, L3DFVF_TEX1, ELEMENT_FVF_END, },//PosDiffuseTex1

    {L3DFVF_XYZ | L3DFVF_DIFFUSE | L3DFVF_TEX2, 4,
    0,   2,  3,  4, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    12,  4, 12, 12, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0,  12, 28, 36, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 16,  8,  8, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    L3DFVF_XYZ, L3DFVF_DIFFUSE, L3DFVF_TEX1, L3DFVF_TEX2, ELEMENT_FVF_END},//PosDiffuseTex2

    {L3DFVF_XYZ | L3DFVF_DIFFUSE | L3DFVF_TEX3, 5, 
    0,   2,  3,  4,  5, 0xffffffff, 0xffffffff, 0xffffffff,
    12,  4, 12, 12, 12, 0xffffffff, 0xffffffff, 0xffffffff, 
    0,  12, 28, 36, 44, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 16,  8,  8,  8, 0xffffffff, 0xffffffff, 0xffffffff,
    L3DFVF_XYZ, L3DFVF_DIFFUSE, L3DFVF_TEX1, L3DFVF_TEX2, L3DFVF_TEX3, ELEMENT_FVF_END},//PosDiffuseTex2

    {L3DFVF_XYZ | L3DFVF_DIFFUSE | L3DFVF_NORMAL | L3DFVF_TEX1, 4,
    0,   1,  2,  3, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0,  12,  4, 12, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0,  12, 28, 40, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 16, 12,  8, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    L3DFVF_XYZ, L3DFVF_DIFFUSE, L3DFVF_NORMAL, L3DFVF_TEX1, ELEMENT_FVF_END,},//PosNormalDiffuseTex1 ?????bug

    {L3DFVF_XYZ | L3DFVF_DIFFUSE | L3DFVF_NORMAL | L3DFVF_TEX2, 5,
    0,   1,  2,  3,  4, 0xffffffff, 0xffffffff, 0xffffffff,
    0,  12,  4, 12, 12, 0xffffffff, 0xffffffff, 0xffffffff,
    0,  12, 28, 36, 44, 0xffffffff, 0xffffffff, 0xffffffff,
    12, 16,  8,  8,  8, 0xffffffff, 0xffffffff, 0xffffffff,
    L3DFVF_XYZ, L3DFVF_DIFFUSE, L3DFVF_NORMAL, L3DFVF_TEX1, L3DFVF_TEX2, ELEMENT_FVF_END},//PosNormalDiffuseTex2

    {L3DFVF_XYZ | L3DFVF_DIFFUSE | L3DFVF_NORMAL | L3DFVF_TEX3, 6,
    0,   1,  2,  3,  4,  5, 0xffffffff, 0xffffffff,
    0,  12,  4,  8,  8,  8, 0xffffffff, 0xffffffff,
    0,  12, 28, 40, 48, 56, 0xffffffff, 0xffffffff,
    12, 16, 12,  8,  8,  8, 0xffffffff, 0xffffffff,
    L3DFVF_XYZ, L3DFVF_DIFFUSE, L3DFVF_NORMAL, L3DFVF_TEX1, L3DFVF_TEX2, L3DFVF_TEX3, ELEMENT_FVF_END}//PosNormalDiffuseTex3
};

class L3DMesh
{
public:
    friend class LMeshCreator;

    L3DMesh();
    ~L3DMesh();

private:
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

    L3DMaterial* m_pLMaterial;
    
    unsigned int m_nVertexArrObj;
    unsigned int m_dwNumFaces;
    
    static const VertexFromatOffsetItem* GetVertexFormat(unsigned int dwFVF);
    static unsigned int GetVertexStride(unsigned int dwFVF);
    
public:
    bool LoadMesh(const char* cszFileName);
    bool UpdateMesh(unsigned int dwSubMesh);
    
private:
    bool LoadMeshData(const char* cszFileName, LMESH_DATA* pLMeshData);
    bool CreateMesh(const LMESH_DATA* pLMeshData);
};

#endif /* L3DMesh_h */
