/* who1.c - a first version of the who program
 *    		 open, read UTMP file, and show results
 */
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>       // To display the login info
#include <fcntl.h>      // To enable the open command
#include <unistd.h>     // To enable the read command
#include <time.h>

#define SHOWHOST		// Include remote machine on output

void show_info(struct utmp * utbufp);
void show_time(long timeval);

int main() 
{
	struct utmp current_record;
	int    utmpfd;
	int    reclen = sizeof(current_record);

	if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
		perror(UTMP_FILE);
		exit(1);
	}

	while (read(utmpfd, &current_record, reclen) == reclen)
		show_info(&current_record);
	close(utmpfd);

	return 0;
}

/* 
 *  show info()
 *  displays contents of the utmp struct in human readable form
 *  * note * these sizes should not be hardwired
 */
void show_info(struct utmp * utbufp)
{
	if (utbufp->ut_type != USER_PROCESS) return;

	printf("%-8.8s", utbufp->ut_name); //The logname
	printf(" ");
	printf("%-8.8s", utbufp->ut_line); //The tty
	printf(" ");
	show_time(utbufp->ut_time); //Login time
	printf(" ");

	#ifdef SHOWHOST
		printf("(%s)", utbufp->ut_host); //The host
	#endif
		printf("\n");
}

/*
 * displays time in a format fit for human consumption
 * uses ctime to build a string then picks parts out of it
 * Note: %12.12s prints a string 12 chars wide and LIMITS
 * it to 12 chars.
 */
void show_time(long timeval)
{
	char * cp;
	cp = ctime(&timeval); //String looks like: Mon Feb 4 00:46:40 EST 1991
	printf("%12.12s", cp + 4);
}