ay_irc_query_connected(eb_account *account)
{
	ay_irc_account *eia = NULL;

	if (!account)
		return FALSE;

	eia = (ay_irc_account *)account->protocol_account_data;

	return (eia->status != IRC_OFFLINE);
}
