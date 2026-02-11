ast_check_hangup(struct ast_channel *chan)
{
	if (ast_channel_softhangup_internal_flag(chan))
		return 1;
	if (ast_tvzero(*ast_channel_whentohangup(chan)))
		return 0;
	if (ast_tvdiff_ms(*ast_channel_whentohangup(chan), ast_tvnow()) > 0)
		return 0;
	ast_debug(4, "Hangup time has come: %" PRIi64 "\n", ast_tvdiff_ms(*ast_channel_whentohangup(chan), ast_tvnow()));
	ast_test_suite_event_notify("HANGUP_TIME", "Channel: %s", ast_channel_name(chan));
	ast_channel_softhangup_internal_flag_add(chan, AST_SOFTHANGUP_TIMEOUT);
	return 1;
}
