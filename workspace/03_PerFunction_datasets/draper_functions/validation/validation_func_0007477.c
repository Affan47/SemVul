get_arg(SgrepData *sgrep,char *(*argv[]),int *i,int *j)
{
	char *r;

	if ((*(*argv))[*j+1]==0)
	{
		if ( ((*argv)[1])==NULL )
		{
		    sgrep_error(sgrep,"Option -%c requires an argument\n",
				(**argv)[*j]);
		    return NULL;
		}
		r=*(++(*argv));
		(*i)++;
		*j=strlen(r)-1;
	}
	else {
		r=&(*(*argv))[(*j)+1];
		*j=strlen(*(*argv))-1;
	}
#ifdef DEBUG
	fprintf(stderr,"Got argument %s\n",r);
#endif
	return r;
}
