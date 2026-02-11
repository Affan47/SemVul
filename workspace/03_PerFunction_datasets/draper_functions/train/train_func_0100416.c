nextfile(void)
{
	if (infile != stdin)
		fclose(infile);
	infile = NULL;
	argno++;
}
