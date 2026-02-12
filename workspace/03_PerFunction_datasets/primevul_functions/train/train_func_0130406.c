void textcolor_bg(int bg)
{	char command[13];


	sprintf(command, "\033[%dm", bg + 40);
	fprintf(stderr, "%s", command);
	fflush(stderr);
}
