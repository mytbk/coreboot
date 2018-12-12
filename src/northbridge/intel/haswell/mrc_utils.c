#include <string.h>

void __attribute((regparm(3))) mrc_setmem(void *s, size_t n, int c);
void __attribute((regparm(3))) mrc_memcpy(void *dst, const void *src, size_t n);
void __attribute((regparm(3))) mrc_fillword(int *s, int c, size_t n);
void __attribute((regparm(3))) mrc_zeromem(void *s, size_t n);
char __attribute((regparm(3))) mrc_highest_bit(int a);

void __attribute((regparm(3))) mrc_setmem(void *s, size_t n, int c)
{
	memset(s, c, n);
}

void __attribute((regparm(3))) mrc_fillword(int *s, int c, size_t n)
{
	for (size_t i = 0; i < n; i++)
		s[i] = c;
}

void __attribute((regparm(3))) mrc_memcpy(void *dst, const void *src, size_t n)
{
	memcpy(dst, src, n);
}

void __attribute((regparm(3))) mrc_zeromem(void *s, size_t n)
{
	memset(s, 0, n);
}

char __attribute((regparm(3))) mrc_highest_bit(int a)
{
	int result = 0;

	if (a == -1)
		return 0;

	for (int i = 0; i < 32; i++) {
		if (a & (1 << i))
			result = i + 1;
	}

	return result;
}
