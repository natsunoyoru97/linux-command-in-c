/* fileinfo.c - use stat() to obtain and print file properties
 *			  - some members are just members...
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * File type macros
 */
#define S_ISFIFO(m) (((m) & (0170000)) == (0010000))
#define S_ISDIR(m)  (((m) & (0170000)) == (0040000))
#define S_ISBLK(m)  (((m) & (0170000)) == (0060000))
#define S_ISREG(m)  (((m) & (0170000)) == (0100000))

void show_stat_info(char * fname, struct stat * buf);

int main(int ac, char *av[])
{
	struct stat info;		//buffer for file info

	if (ac > 1)
		if (stat(av[1], &info) != -1) {
			show_stat_info(av[1], &info);
			return 0;
		}
		else
			perror(av[1]);		//report stat() errors
	return 1;
}

void show_stat_info(char * fname, struct stat * buf)
/*
 * displays some info from stat in a name = value format
 */
{
	printf("    mode: %o\n", buf->st_mode);		//type + mode
	printf("   links: %ld\n", buf->st_nlink);    //links
	printf("    user: %d\n", buf->st_uid);		//user id
	printf("   group: %d\n", buf->st_gid);		//group id
	printf("    size: %ld\n", buf->st_size);		//file size
	printf(" modtime: %ld\n", buf->st_mtime);	//modified
	printf("    name: %s\n", fname);			//filename
}