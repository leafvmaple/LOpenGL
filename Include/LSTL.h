
#ifndef _LSTL_H_
#define _LSTL_H_

#include <list>
#include <map>

#ifdef WIN32
#define LLIST std::list
#define LHASH std::map

#define LLIST_ITER(T) std::list<T*>::iterator
#endif

#endif // !_LSTL_H_
