/** cp.c
 *  uses read and write with tunable buffer size
 * 
 *  usage: cp src dest
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFERSIZE 4096
#define OUTFDCHOMD 0775

void oops(char *, char *);

int main(int ac, char * av[])
{
	int  in_fd, out_fd, n_chars;
	char buf[BUFFERSIZE];

	if (ac != 3) {
		fprintf(stderr, "usage: %s source destination\n", * av);
		exit(1);
	}

	if ((in_fd = open(av[1], O_RDONLY)) == -1)
		oops("Cannot open ", av[1]);
	if ((out_fd = open(av[2], O_CREAT | O_WRONLY, OUTFDCHOMD)) == -1)
		oops("Cannot creat ", av[2]);

	while((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
	{
		int res = write(out_fd, buf, n_chars);
		printf("%d\t%d\n", n_chars, res);
		if (res != n_chars)
			oops("Write error to ", av[2]);
	}
	if (n_chars == -1)
		oops("Read error from ", av[1]);

	if (close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files", "");

	return 0;
}

void oops(char * s1, char * s2)
{
	fprintf(stderr, "Error: %s ", s1);
	perror(s2);
	exit(1);
}

