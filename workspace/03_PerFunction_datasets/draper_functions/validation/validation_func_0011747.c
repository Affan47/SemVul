cli_js_destroy(struct parser_state *state)
{
	size_t i;
	if(!state)
		return;
	scope_free_all(state->list);
	for(i=0;i<state->tokens.cnt;i++) {
		free_token(&state->tokens.data[i]);
	}
	free(state->tokens.data);

	if(state->scanner)
		yylex_destroy(state->scanner);
	memset(state, 0x55, sizeof(*state));
	free(state);
	cli_dbgmsg(MODULE "cli_js_destroy() done\n");
}
