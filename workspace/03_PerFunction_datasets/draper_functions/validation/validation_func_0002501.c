nocdr_exec(struct ast_channel *chan, const char *data)
{
	if (ast_channel_cdr(chan))
		ast_set_flag(ast_channel_cdr(chan), AST_CDR_FLAG_POST_DISABLED);

	return 0;
}
