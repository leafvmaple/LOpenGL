#pragma once

#include <cstdio>
#include <cstring>

#ifdef _WIN32
#define lfopen(_stream,_file_name,_mode) (fopen_s(&_stream,_file_name,_mode))
#elif __APPLE__
#define lfopen(_stream,_file_name,_mode) (_stream=fopen(_file_name,_mode))
#endif