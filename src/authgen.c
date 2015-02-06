/*
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "md5.h"
#include "base64.h"

#define AUTH_LEN	1024
#define PASSWD_LEN	256

void usage();
char* create_auth(char *user, char *passwd);
void release_auth(char *item);

int main(int argc, char **argv)
{
	int fd;
	char *auth_item;
	
	if (argc > 1 && (!strcmp(argv[1], "--help") || 
			 !strcmp(argv[1], "-h"))) {
		usage();
		return 0;
	}

	if (4 != argc) {
		fprintf(stderr, "Error: invalid parameter.\n");
		usage();
		return -1;
	}

	fd = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, 00600);
	if (fd < 0) {
		fprintf(stderr, "Failure: open file \"%s\" failed.\n", argv[3]);
		return -1;
	}

	auth_item = create_auth(argv[1], argv[2]);
	if (!auth_item) {
		fprintf(stderr, "Failure: create_auth return NULL.\n");
		close(fd);
		return -1;
	}

	if (write(fd, auth_item, strlen(auth_item)) <= 0) {
		fprintf(stderr, "Failure: write \"%s\" to file \"%s\" failed.\n", 
				auth_item, argv[3]);
		close(fd);
		release_auth(auth_item);
		return -1;
	}
	
	close(fd);
	release_auth(auth_item);
	return 0;	
}


void usage()
{
	printf("\tusage:\tusergen username password file_path\n"
		   "\te.g. :\tusergen John Jonh123 /etc/mypasswd\n\n");
	return;
}

char* create_auth(char *user, char *passwd)
{
	struct MD5Context mc;
	unsigned char final[16];
	char encoded_passwd[PASSWD_LEN];
	char *auth;
		
	auth = (char *) malloc(AUTH_LEN);
	if (!auth)
		return auth;	

	MD5Init(&mc);
	MD5Update(&mc, (unsigned char *) passwd, strlen(passwd));
	MD5Final(final, &mc);
	strcpy(encoded_passwd, "$1$");
	base64encode(final, encoded_passwd + 3, 16);
	
	snprintf(auth, AUTH_LEN, "%s:%s\n", user, encoded_passwd);

	return auth;
}

void release_auth(char *item)
{
	if (item)
		free(item);
}
