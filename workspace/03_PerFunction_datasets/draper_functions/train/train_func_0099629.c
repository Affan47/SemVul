do_lo_export(const char *loid_arg, const char *filename_arg)
{
	int			status;
	bool		own_transaction;

	if (!start_lo_xact("\\lo_export", &own_transaction))
		return false;

	SetCancelConn();
	status = lo_export(pset.db, atooid(loid_arg), filename_arg);
	ResetCancelConn();


	if (status != 1)
	{
		fputs(PQerrorMessage(pset.db), stderr);
		return fail_lo_xact("\\lo_export", own_transaction);
	}

	if (!finish_lo_xact("\\lo_export", own_transaction))
		return false;

	print_lo_result("lo_export");

	return true;
}
