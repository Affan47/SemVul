tcl_EnvSetMsgfile(interp, dbenv, ip, msgf)
	Tcl_Interp *interp;
	DB_ENV *dbenv;
	DBTCL_INFO *ip;
	char *msgf;
{
	COMPQUIET(interp, NULL);


	if (ip->i_msg != NULL && ip->i_msg != stdout &&
	    ip->i_msg != stderr)
		(void)fclose(ip->i_msg);
	if (strcmp(msgf, "/dev/stdout") == 0)
		ip->i_msg = stdout;
	else if (strcmp(msgf, "/dev/stderr") == 0)
		ip->i_msg = stderr;
	else
		ip->i_msg = fopen(msgf, "a");
	if (ip->i_msg != NULL)
		dbenv->set_msgfile(dbenv, ip->i_msg);
}
