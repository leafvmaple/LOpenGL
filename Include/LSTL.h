
#ifndef _LSTL_H_
#define _LSTL_H_

#include <list>
#include <vector>

#ifdef WIN32
#include <map>

#elif __APPLE__
#include <unordered_map>

#endif // !__APPLE__
#endif // !_LSTL_H_
