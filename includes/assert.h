#ifndef KERNEL_ASSERT_H
#define KERNEL_ASSERT_H

#include "system/utils.h"

#define assert(x)	\
	do {	\
		if (!(x)) {	\
			printk("ASSERT %s:%d: %s\n", __FILE__, __LINE__, #x);	\
			PAUSE_RUNTIME;	\
		}	\
	} while (0)

#define assert_eq(x, y)	\
	do {	\
		if ((x) != (y)) {	\
			printk("ASSERT %s:%d: %s != %s\n", __FILE__, __LINE__, #x, #y);	\
			PAUSE_RUNTIME;	\
		}	\
	} while (0)

#define assert_ne(x, y)	\
	do {	\
		if ((x) == (y)) {	\
			printk("ASSERT %s:%d: %s == %s\n", __FILE__, __LINE__, #x, #y);	\
			PAUSE_RUNTIME;	\
		}	\
	} while (0)

#define assert_null(x)	\
	do {	\
		if ((x) != NULL) {	\
			printk("ASSERT %s:%d: %s != NULL\n", __FILE__, __LINE__, #x);	\
			PAUSE_RUNTIME;	\
		}	\
	} while (0)

#define assert_not_null(x)	\
	do {	\
		if ((x) == NULL) {	\
			printk("ASSERT %s:%d: %s == NULL\n", __FILE__, __LINE__, #x);	\
			PAUSE_RUNTIME;	\
		}	\
	} while (0)

#define assert_true(x)	\
	do {	\
		if (!(x)) {	\
			printk("ASSERT %s:%d: %s is false\n", __FILE__, __LINE__, #x);	\
			PAUSE_RUNTIME;	\
		}	\
	} while (0)

#define assert_false(x)	\
	do {	\
		if (x) {	\
			printk("ASSERT %s:%d: %s is true\n", __FILE__, __LINE__, #x);	\
			PAUSE_RUNTIME;	\
		}	\
	} while (0)

#endif