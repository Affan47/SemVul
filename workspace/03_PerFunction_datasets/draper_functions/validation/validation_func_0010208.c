sig_error(XMPP_SERVER_REC *server, const char *full_jid,
    const char *msg)
{
	g_return_if_fail(server != NULL);
	g_return_if_fail(full_jid != NULL);

	printformat_module(MODULE_NAME, server, full_jid, MSGLEVEL_CRAP,
	    XMPPTXT_MESSAGE_NOT_DELIVERED, full_jid, msg);
}
