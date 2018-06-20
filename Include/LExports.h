#pragma once

#ifdef __APPLE__
#ifdef LENGINE_EXPORTS
#define L3DENGINE_API extern "C" __attribute__((visibility("default")))
#define L3DENGINE_CLASS __attribute__((visibility("default")))
#endif
#else
#ifdef LENGINE_EXPORTS
#define L3DENGINE_API extern "C" __declspec(dllexport)
#define L3DENGINE_CLASS __declspec(dllexport)
#else
#define L3DENGINE_API extern "C" __declspec(dllimport)
#define L3DENGINE_CLASS __declspec(dllimport)
#endif
#endif
