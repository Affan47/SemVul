void clear_globals(void)
{
	extern int ntp_optind;
	showhostnames = 0;
	ntp_optind = 0;
	server_entry = NULL;
	havehost = 0;
	numassoc = 0;
	numcmds = 0;
	numhosts = 0;
}
