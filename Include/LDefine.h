//
//  LDefine.h
//  
//
//  Created by LeafMaple on 2018/07/05.
//

#ifndef LDefine_h
#define LDefine_h

#ifdef __APPLE__
typedef unsigned int DWORD;
#endif
typedef unsigned char BYTE;

#define L3DCOLOR_ARGB(a,r,g,b) \
    ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define L3DCOLOR_RGBA(r,g,b,a) L3DCOLOR_ARGB(a,r,g,b)

#define L3DCOLOR_COLORVALUE(r,g,b,a) \
    L3DCOLOR_RGBA((DWORD)((r)*255.f), (DWORD)((g)*255.f), (DWORD)((b)*255.f), (DWORD)((a)*255.f))

#endif /* LDefine_h */
