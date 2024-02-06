#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include <stddef.h>

size_t	strlen(const char *str);
char	*strcpy(char *dest, const char *src);
char	*strncpy(char *dest, const char *src, size_t n);
char	*strcat(char *dest, const char *src);
char	*strncat(char *dest, const char *src, size_t n);
int		strcmp(const char *s1, const char *s2);
int		strncmp(const char *s1, const char *s2, size_t n);
char	*strchr(const char *s, int c);
char	*strrchr(const char *s, int c);
char	*strrev(char *str);
char	*strtolower(char *str);
char	*strtoupper(char *str);
void	*memcpy(void *dest, const void *src, size_t n);
void	*memset(void *s, int c, size_t n);
void	*memset16(void *s, int c, size_t n);
void	*memset32(void *s, int c, size_t n);
void	*memmove(void *dest, const void *src, size_t n);
int		memcmp(const void *s1, const void *s2, size_t n);
void	bzero(void *s, size_t n);
// void	*memchr(const void *s, int c, size_t n);

#endif
