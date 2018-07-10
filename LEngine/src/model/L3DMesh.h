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
class L3DCamera;

struct VertexFromatOffsetItem
{
    const static GLuint s_dwMaxVertexElement = 8;
    GLuint dwFVF;
    GLuint dwNumElement;
    GLuint dwSrcOffset[s_dwMaxVertexElement];
    GLuint dwSrcStride[s_dwMaxVertexElement];
    GLuint dwDestOffset[s_dwMaxVertexElement];
    GLuint dwDestStride[s_dwMaxVertexElement];
    GLuint dwElementFVF[s_dwMaxVertexElement];
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
        GLuint PositionBlock;
        GLuint NormalBlock;
        GLuint DiffuseBlock;
        GLuint TextureUVW1Block;
        GLuint TextureUVW2Block;
        GLuint TextureUVW3Block;
        GLuint FacesIndexBlock;
        GLuint SubsetIndexBlock;
        GLuint SkinInfoBlock;
        GLuint LODInfoBlock;
        GLuint FlexibleBodyBlock;
        GLuint BBoxBlock;
        GLuint BlendMeshBlock;
        GLuint ExtendBlock[17];
    };

    struct _MeshHead
    {
        GLuint dwNumVertices;
        GLuint dwNumFaces;
        GLuint dwNumSubset;
        union
        {
            MeshDataBlocks Blocks;
            GLuint dwBlocks[30];
        };
    };

    struct _MeshFileHead
    {
        TFileHeader KSFileHeader_NotUse;
        GLuint dwFileMask;
        GLuint dwBlockLength;
        GLuint dwVersion;
        GLuint AnimationBlock_NotUse;
        GLuint ExtendBlock_NotUse[10];
        GLuint MeshCount_NotUse;
        const static GLuint s_dwFileMask = 0x4d455348;
        const static GLuint s_dwCurrentVersion = 0;
    };
#pragma pack(pop)

    struct LMESH_DATA
    {
        GLuint          dwID;
        std::string     strFileName;
        GLuint          dwOption;
        GLuint          dwOptionEx;

        GLuint          dwNumVertices;
        GLuint          dwNumFaces;
        GLuint          dwNumSubset;
        GLuint          dwMeshFVF;

        glm::vec3       *pPos;
        glm::vec3       *pNormals;
        GLCOLOR         *pDiffuse;
        glm::vec3       *pUV1;
        glm::vec3       *pUV2;
        glm::vec3       *pUV3;

        GLuint          *pFaceIndices;
        GLuint          *pSubsetIndices;

        GLubyte         *pbyFileBuffer;
    };

    L3DMaterial* m_pLMaterial;
    
    GLuint m_nVertexArrObj;
    GLuint m_dwNumFaces;
    
    static const VertexFromatOffsetItem* GetVertexFormat(GLuint dwFVF);
    static GLuint GetVertexStride(GLuint dwFVF);
    
public:
    bool LoadMesh(const char* cszFileName);
    bool UpdateMesh(GLuint dwSubMesh);
    bool UpdatePosition(L3DCamera* p3DCamera);
    
private:
    bool LoadMeshData(const char* cszFileName, LMESH_DATA* pLMeshData);
    bool CreateMesh(const LMESH_DATA* pLMeshData);
};

#endif /* L3DMesh_h */
