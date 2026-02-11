coll_parse_idseq (xmmsv_coll_token_t *tokens, xmmsv_coll_t **ret)
{
	xmmsv_coll_token_t *tk;

	tk = tokens;
	TOKEN_ASSERT (tk, XMMS_COLLECTION_TOKEN_SYMBOL_ID);

	tk = coll_next_token (tk);
	tk = coll_parse_sequence (tk, "id", ret);

	return (ret == NULL ? tokens : tk);
}
