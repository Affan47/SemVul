exec_describe_portal_message(const char *portal_name)
{
	Portal		portal;


	start_xact_command();


	MemoryContextSwitchTo(MessageContext);

	portal = GetPortalByName(portal_name);
	if (!PortalIsValid(portal))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_CURSOR),
				 errmsg("portal \"%s\" does not exist", portal_name)));


	if (IsAbortedTransactionBlockState() &&
		portal->tupDesc)
		ereport(ERROR,
				(errcode(ERRCODE_IN_FAILED_SQL_TRANSACTION),
				 errmsg("current transaction is aborted, "
						"commands ignored until end of transaction block"),
				 errdetail_abort()));

	if (whereToSendOutput != DestRemote)
		return;

	if (portal->tupDesc)
		SendRowDescriptionMessage(portal->tupDesc,
								  FetchPortalTargetList(portal),
								  portal->formats);
	else
		pq_putemptymessage('n');
}
