void textstyle(int attr)
{	char command[13];


	sprintf(command, "\033[%im", attr);
	fprintf(stderr, "%s", command);
	fflush(stderr);
}
