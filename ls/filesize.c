/* filesizes.c - prints size of passwd file */

#include <stdio.h>
#include <sys/stat.h>

int main()
{
	struct stat infobuf;
	if (stat("/etc/passwd", &infobuf) == -1)
		perror("/etc/passwd");
	else
		printf("The size of /etc/passwd is %ld\n", infobuf.st_size);

	return 0;
}