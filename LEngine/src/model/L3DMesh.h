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
#include "io/LFileStruct.h"

class L3DMesh
{
public:
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
    
public:
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
        
        BYTE*           pbyFileBuffer;
    };
    
public:
    bool LoadMesh(const char* cszFileName);
    bool UpdateMesh(unsigned int dwSubMesh);
    
    bool LoadMeshData(const char* cszFileName, LMESH_DATA* pLMeshData);
    bool CreateMesh(const LMESH_DATA* pLMeshData);
};

#endif /* L3DMesh_h */
