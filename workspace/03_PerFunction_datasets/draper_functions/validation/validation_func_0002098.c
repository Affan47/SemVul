ast_rtp_engine_unregister(struct ast_rtp_engine *engine)
{
	struct ast_rtp_engine *current_engine = NULL;

	AST_RWLIST_WRLOCK(&engines);

	if ((current_engine = AST_RWLIST_REMOVE(&engines, engine, entry))) {
		ast_verb(2, "Unregistered RTP engine '%s'\n", engine->name);
	}

	AST_RWLIST_UNLOCK(&engines);

	return current_engine ? 0 : -1;
}
