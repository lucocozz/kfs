#ifndef KERNEL_ASSERT_H
#define KERNEL_ASSERT_H

#include "system/utils.h"

#define assert(x)	\
	do {	\
		if (!(x))	\
			panic("ASSERT %s:%d: %s\n", __FILE__, __LINE__, #x);	\
	} while (0)

#define assert_eq(x, y)	\
	do {	\
		if ((x) != (y))	\
			panic("ASSERT %s:%d: %s != %s\n", __FILE__, __LINE__, #x, #y);	\
	} while (0)

#define assert_ne(x, y)	\
	do {	\
		if ((x) == (y))	\
			panic("ASSERT %s:%d: %s == %s\n", __FILE__, __LINE__, #x, #y);	\
	} while (0)

#define assert_null(x)	\
	do {	\
		if ((x) != NULL)	\
			panic("ASSERT %s:%d: %s != NULL\n", __FILE__, __LINE__, #x);	\
	} while (0)

#define assert_not_null(x)	\
	do {	\
		if ((x) == NULL)	\
			panic("ASSERT %s:%d: %s == NULL\n", __FILE__, __LINE__, #x);	\
	} while (0)

#define assert_true(x)	\
	do {	\
		if (!(x))	\
			panic("ASSERT %s:%d: %s is false\n", __FILE__, __LINE__, #x);	\
	} while (0)

#define assert_false(x)	\
	do {	\
		if (x)	\
			panic("ASSERT %s:%d: %s is true\n", __FILE__, __LINE__, #x);	\
	} while (0)

#endif