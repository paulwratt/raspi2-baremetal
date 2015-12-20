#include	<type.h>


void *memset(void *buf, int ch, size_t n)
{
	uint8_t *s = (uint8_t *) buf;
	uint8_t *e = s + n - 1;

	while (s != e) *s++ = ch;

	return buf;
}

size_t strlen(const char *s)
{
	const char* p = s;

	while (*s++) ;

	return s - p;
}
