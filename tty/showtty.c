/* showtty.c
 * displays some current tty settings
 * TODO: support the display of special keys such as Backspace(ascii 127)
 */

#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include "showtty.h"

int main()
{
	struct termios ttyinfo;							//this struct holds tty info
	if (tcgetattr(0, &ttyinfo) == -1) {				//get info
		perror("cannot get params about stdin");
		exit(1);
	}
													//show info
	showbaud(cfgetospeed(&ttyinfo));				//get + show baud rate
	printf("The erase character is ascii %d, Ctrl - %c\n", ttyinfo.c_cc[VERASE], ttyinfo.c_cc[VERASE] - 1 + 'A');
	printf("The line kill character is ascii %d, Ctrl - %c\n", ttyinfo.c_cc[VKILL], ttyinfo.c_cc[VKILL] - 1 + 'A');
	show_some_flags(&ttyinfo);						//show misc. flags
	exit(0);
}

void showbaud(int thespeed)
/*
 * prints the speed in english
 */
{
	printf("the baud rate is ");
	switch (thespeed) {
		case B300:  printf("300\n"); break;
		case B600:  printf("600\n"); break;
		case B1200: printf("1200\n"); break;
		case B1800: printf("1800\n"); break;
		case B2400: printf("2400\n"); break;
		case B4800: printf("4800\n"); break;
		case B9600: printf("9600\n"); break;
		default:    printf("Fast\n"); break;
	}
}

void show_some_flags(struct termios * ttyp)
/*
 * show the values of two of the flag sets_: c_iflag and c_lflag
 * adding c_oflag and c_cflag is pretty routine - just add new
 * tables above and a bit more code below.
 */
{
	show_flagset(ttyp->c_iflag, input_flags);
	show_flagset(ttyp->c_lflag, local_flags);
}

void show_flagset(int thevalue, struct flaginfo thebitnames[])
/*
 * check each bit pattern and display descriptive title
 */
{
	int i;
	for (i = 0; thebitnames[i].fl_value; i++) {
		printf("%s is ", thebitnames[i].fl_name);
		if (thevalue & thebitnames[i].fl_value)
			printf("ON\n");
		else
			printf("OFF\n");
	}
}