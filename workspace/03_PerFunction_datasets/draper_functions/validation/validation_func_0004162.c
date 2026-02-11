closefile(Node **a, int n)
{
	Cell *x;
	int i, stat;

	n = n;
	x = execute(a[0]);
	getsval(x);
	for (i = 0; i < FOPEN_MAX; i++)
		if (files[i].fname && strcmp(x->sval, files[i].fname) == 0) {
			if (ferror(files[i].fp))
				WARNING( "i/o error occurred on %s", files[i].fname );
			if (files[i].mode == '|' || files[i].mode == LE)
				stat = pclose(files[i].fp);
			else
				stat = fclose(files[i].fp);
			if (stat == EOF)
				WARNING( "i/o error occurred closing %s", files[i].fname );
			if (i > 2)
				xfree(files[i].fname);
			files[i].fname = NULL;
			files[i].fp = NULL;
		}
	tempfree(x);
	return(True);
}
