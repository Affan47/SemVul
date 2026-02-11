strrstr(char *main, char *sub)
{
	char *p;
	int sublen;

	if(!main) return NULL;
	if(!sub) return NULL;

	sublen = strlen(sub);

	p = main + strlen(main);
	while(p!=main)
	{
		if(strncmp(p, sub, sublen) == 0) return p;
		p--;
	}
	if(strncmp(p, sub, sublen) == 0) return p;
	return NULL;
}
