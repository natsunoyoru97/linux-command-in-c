/* play_again2.c
 * purpose: ask if user wants another transaction
 * method: set tty into char-by-char mode and no-echo mode
 * read char, return result
 * returns: 0=>yes, 1=>no
 * better: timeout if user walks away
 */
#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction"

int get_response(char *);
void set_cr_noecho_mode();
int tty_mode(int);

int main()
{
	int response;
	tty_mode(0);						// save tty mode
	set_cr_noecho_mode();						// set chr-by-chr mode
	response = get_response(QUESTION);	// get some answer
	tty_mode(1);						// restore tty mode
	return response;
}

int get_response(char * question)
/*
 * purpose: ask a question and wait for a y/n answer
 * method: use getchar and complain about non y/n answers
 * returns: 0=>yes, 1=>no
 */
{
	int input;
	printf("%s(y/n)?", question);
	while (1) {
		switch(input = getchar()) {
			case 'Y':
			case 'y': return 0;
			case 'n':
			case 'N':
			case EOF: return 1;
			default:
				printf("\ncannot understand %c, ", input);
				printf("Please type y or n \n");
		}
	}
}

void set_cr_noecho_mode()
/*
 * purpose: put file descriptor 0 (i.e. stdin) into chr-by-chr mode and noecho mode
 * method: use bits in termios
 */
{
	struct termios ttystate;
	tcgetattr(0, &ttystate);				// read curr.setting
	ttystate.c_lflag &= ~ICANON;			// no buffering
	ttystate.c_lflag &= ~ECHO;				// no echo either
	ttystate.c_cc[VMIN] = 1;				// get 1 char at a time
	tcsetattr(0, TCSANOW, &ttystate);		// install settings
}

// how == 0 => save current mode, how == 1 => restore mode
int tty_mode(int how)
{
	static struct termios original_mode;
	if (how == 0)
		tcgetattr(0, &original_mode);
	else
		return tcsetattr(0, TCSANOW, &original_mode);
}