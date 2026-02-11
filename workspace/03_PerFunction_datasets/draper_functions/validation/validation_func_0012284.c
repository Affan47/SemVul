onedigit_goto(struct ast_channel *chan, const char *context, char exten, int pri)
{
	char rexten[2] = { exten, '\0' };

	if (context) {
		if (!ast_goto_if_exists(chan, context, rexten, pri))
			return 1;
	} else {
		if (!ast_goto_if_exists(chan, ast_channel_context(chan), rexten, pri))
			return 1;
		else if (!ast_strlen_zero(ast_channel_macrocontext(chan))) {
			if (!ast_goto_if_exists(chan, ast_channel_macrocontext(chan), rexten, pri))
				return 1;
		}
	}
	return 0;
}
