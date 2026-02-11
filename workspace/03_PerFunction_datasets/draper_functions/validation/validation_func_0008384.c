pref_update()
{
char	buf[1000];
char	*p;
char	*q;

	sprintf(buf, SORTORDER "=%c " PAGESIZE "=%d " AUTOPURGE_V "=%d "
		FLOWEDTEXT "=%d " NOARCHIVE "=%d " NOAUTORENAMESENT "=%d "
		STARTOFWEEK "=%d",
		pref_flagsortorder, pref_flagpagesize, pref_autopurge,
		pref_noflowedtext, pref_noarchive, pref_noautorenamesent,
		pref_startofweek);

	if (pref_flagisoldest1st)
		strcat(buf, " " OLDEST1ST);

	if (pref_flagfullheaders)
		strcat(buf, " " FULLHEADERS);

	if (!pref_showhtml)
		strcat(buf, " " NOHTML);

	if (pref_wikifmt)
		strcat(buf, " " WIKITEXT);

	p=append_str(buf, FROM, pref_from);
	q=append_str(p, LDAP, pref_ldap);
	write_sqconfig(".", CONFIGFILE, q);
	free(q);
	free(p);
}
