#ifndef STDDEF_H
#define STDDEF_H

// Size type
typedef unsigned int size_t;

// Null pointer
#ifndef NULL
#define NULL ((void*)0)
#endif

// Offset of macro
#define offsetof(type, member) __builtin_offsetof(type, member)

#endif
