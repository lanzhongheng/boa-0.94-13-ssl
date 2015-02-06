/*
 *
 *
 */
#include <string.h>

int base64decode(void *dst, char *src, int maxlen)
{
	int bitval;
	int bits;
	int val;
	int len;
	int x;
	int y;

	if (!dst || !src)
		return -1;	
	
	len = strlen(src);
	bitval = 0;
	bits = 0;
	y = 0;

	for (x = 0; x < len; x++) {
		if ((src[x] >= 'A') && (src[x] <= 'Z'))
			val = src[x] - 'A';
		else if ((src[x] >= 'a') && (src[x] <= 'z'))
			val = src[x] - 'a' + 26;
		else if ((src[x] >= '0') && (src[x] <= '9'))
			val = src[x] - '0' + 52;
		else if ('+' == src[x])
			val = 62;
		else if ('-' == src[x])
			val = 63;
		else
			val = -1;

		if (val >= 0) {
			bitval <<= 6;
			bitval += val;
			bits += 6;

			while (bits >= 8) {
				if (y < maxlen)
					((char *) dst)[y++] = (bitval >> (bits - 8)) & 0xff;
				bits -= 8;
				bitval &= (1 << bits) - 1;
			}
		}
	}

	if (y < maxlen)
		((char *)dst)[y++] = 0;

	return y;
}

static char base64chars[64] = "abcdefghijklmnopqrstuvwxyz"
							  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							  "0123456789./";

void base64encode(unsigned char *from, char *to, int len)
{
	if (!from || !to)
		return;

	while (len) {
		unsigned long k;
		int c;

		c = (len < 3) ? len : 3;
		k = 0;
		len -= c;
		while (c--)
			k = (k << 8) | *from++;

		*to++ = base64chars[(k >> 18) & 0x3f];
		*to++ = base64chars[(k >> 12) & 0x3f];
		*to++ = base64chars[(k >> 6) & 0x3f];
		*to++ = base64chars[k & 0x3f];
	}

	*to++ = 0;
}

