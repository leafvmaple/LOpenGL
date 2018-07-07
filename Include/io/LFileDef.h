#ifndef _LFILEDEF_H_
#define _LFILEDEF_H_

#define L3DFVF_RESERVED0        0x001
#define L3DFVF_POSITION_MASK    0x400E
#define L3DFVF_XYZ              0x002
#define L3DFVF_XYZRHW           0x004
#define L3DFVF_XYZB1            0x006
#define L3DFVF_XYZB2            0x008
#define L3DFVF_XYZB3            0x00a
#define L3DFVF_XYZB4            0x00c
#define L3DFVF_XYZB5            0x00e
#define L3DFVF_XYZW             0x4002

#define L3DFVF_NORMAL           0x010
#define L3DFVF_PSIZE            0x020
#define L3DFVF_DIFFUSE          0x040
#define L3DFVF_SPECULAR         0x080

#define L3DFVF_TEXCOUNT_MASK    0xf00
#define L3DFVF_TEXCOUNT_SHIFT   8
#define L3DFVF_TEX0             0x000
#define L3DFVF_TEX1             0x100
#define L3DFVF_TEX2             0x200
#define L3DFVF_TEX3             0x300
#define L3DFVF_TEX4             0x400
#define L3DFVF_TEX5             0x500
#define L3DFVF_TEX6             0x600
#define L3DFVF_TEX7             0x700
#define L3DFVF_TEX8             0x800

#define L3DFVF_LASTBETA_UBYTE4   0x1000
#define L3DFVF_LASTBETA_D3DCOLOR 0x8000

#define L3DFVF_RESERVED2         0x6000  // 2 reserved bits

#define ELEMENT_FVF_END  0xffffffff

#endif
