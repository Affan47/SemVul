add_reloption_kind(void)
{

	if (last_assigned_kind >= RELOPT_KIND_MAX)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
			errmsg("user-defined relation parameter types limit exceeded")));
	last_assigned_kind <<= 1;
	return (relopt_kind) last_assigned_kind;
}
