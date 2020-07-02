struct flaginfo { int fl_value; char * fl_name; };

struct flaginfo input_flags[] = {
	IGNBRK, "Ignore break condition",
	BRKINT, "Singnal interrupt on break",
	IGNPAR, "Ignore chars with parity errors",
	PARMRK, "Mark parity errors",
	INPCK,  "Enable input parity check",
	ISTRIP, "Strip character",
	INLCR,  "Map NL to CR on input",
	IGNCR,  "Ignore CR",
	ICRNL,  "Map CR to NL on input",
	IXON,   "Enable start/stop output control",
	// _IXANY, "Enable any char to restart output",
	IXOFF,  "Enable start/stop input control",
	0,      NULL
};

struct flaginfo local_flags[] = {
	ISIG,   "Enable signals",
	ICANON, "Canonical input (erase and kill)",
	//_XCASE, "Canonical upper/lower appearance",
	ECHO,   "Enable echo",
	ECHOE,  "Echo ERASE as BS-SPACE-BS",
	ECHOK,  "Echo KILL by starting new line",
	0,      NULL
};

void showbaud(int);
void show_some_flags(struct termios *);
void show_flagset(int, struct flaginfo thebitnames[]);