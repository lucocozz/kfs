#include "libc.h"

/// Copy N bytes of SRC to DEST.
///
/// ## Parameters
///
/// - `dest`: Pointer to the destination array where the content is to be copied, type-casted to a pointer of type void*.
/// - `src`: Pointer to the source of data to be copied, type-casted to a pointer of type void*.
/// - `n`: Number of bytes to copy.
///
/// ## Examples
///
/// ```
/// int array1[5] = { 1, 2, 3, 4, 5 };
/// int array2[5];
///
/// memcpy(array2, array1, 5 * sizeof(int));
/// for (size_t i = 0; i < 5; ++i)
/// 	printf("%d ", array2[i]); // 1 2 3 4 5
/// ```
///
/// ## Return
///
/// A pointer to the destination, which is `dest`.
///
/// ## Note
///
/// - The memory areas must not overlap.
/// - The memory areas must be already allocated.
/// - The size of `dest` and `src` must be at least `n` bytes.
void *memcpy(void *dest, const void *src, size_t n)
{
	int8_t			*d = dest;
	const int8_t	*s = src;

	while (n--)
		*d++ = *s++;
	return (dest);
}