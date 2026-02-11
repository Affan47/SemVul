about_read_line(FILE *fp)
{
	static gchar tpn[MAX_CAR];
	char *pt;
	char c;

	pt = tpn;
	while( ((c=getc(fp))!='\n') && (c!=EOF) && ((pt-tpn)<MAX_CAR) )
		*(pt++)=c;
	*pt = '\0';
	if ( c!=EOF)
		return tpn;
	else
		return NULL;
}
