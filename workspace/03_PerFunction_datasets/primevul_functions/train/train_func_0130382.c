void textcolor_fg(int fg)
{	char command[13];


	sprintf(command, "\033[%dm", fg + 30);
	fprintf(stderr, "%s", command);
	fflush(stderr);
}
