load(char *name)
{
	FILE *in, *oldin;

	if ((in = Fopen(name, "r")) == NULL)
		return;
	oldin = input;
	input = in;
	loading = 1;
	sourcing = 1;
	commands();
	loading = 0;
	sourcing = 0;
	input = oldin;
	Fclose(in);
}
