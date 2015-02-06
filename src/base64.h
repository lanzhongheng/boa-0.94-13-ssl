/*
 *
 *
 */

#ifndef _BASE64_H
#define _BASE64_H

#ifdef __cplusplus
extern "C" {
#endif

int base64decode(void *dst, char *src, int maxlen);
void base64encode(unsigned char *from, char *to, int len);

#ifdef __cplusplus
}
#endif
#endif
