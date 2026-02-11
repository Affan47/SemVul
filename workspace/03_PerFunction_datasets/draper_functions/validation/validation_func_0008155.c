isc_base64_tobuffer(isc_lex_t *lexer, isc_buffer_t *target, int length) {
	base64_decode_ctx_t ctx;
	isc_textregion_t *tr;
	isc_token_t token;
	isc_boolean_t eol;

	base64_decode_init(&ctx, length, target);

	while (!ctx.seen_end && (ctx.length != 0)) {
		unsigned int i;

		if (length > 0)
			eol = ISC_FALSE;
		else
			eol = ISC_TRUE;
		RETERR(isc_lex_getmastertoken(lexer, &token,
					      isc_tokentype_string, eol));
		if (token.type != isc_tokentype_string)
			break;
		tr = &token.value.as_textregion;
		for (i = 0; i < tr->length; i++)
			RETERR(base64_decode_char(&ctx, tr->base[i]));
	}
	if (ctx.length < 0 && !ctx.seen_end)
		isc_lex_ungettoken(lexer, &token);
	RETERR(base64_decode_finish(&ctx));
	return (ISC_R_SUCCESS);
}
