LookupTune(const char *name)
{
	int ix;

	for(ix=0; ix<n_tunes; ix++)
	{
		if(strcmp(name, tunes[ix].name) == 0)
			return(ix);
	}
	return(-1);
}
