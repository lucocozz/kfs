#include "libc.h"

/// Copy N bytes of SRC to DEST, guaranteeing correct behavior for overlapping strings.
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
/// int array[5] = { 1, 2, 3, 4, 5 };
///
/// memmove(array + 2, array, 3 * sizeof(int));
/// for (size_t i = 0; i < 5; ++i)
/// 	printf("%d ", array[i]); // 1 2 1 2 3
/// ```
///
/// ## Return
///
/// A pointer to the destination, which is `dest`.
///
/// ## Note
///
/// - The memory areas can overlap.
/// - The memory areas must be already allocated.
/// - The size of `dest` and `src` must be at least `n` bytes.
void	*memmove(void *dest, const void *src, size_t n)
{
	int8_t			*d = dest;
	const int8_t	*s = src;

	if (d < s) {
		while (n--)
			*d++ = *s++;
	} else {
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}
