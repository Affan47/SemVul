cp_parser_require (cp_parser* parser,
                   enum cpp_ttype type,
                   const char* token_desc)
{
  if (cp_lexer_next_token_is (parser->lexer, type))
    return cp_lexer_consume_token (parser->lexer);
  else
    {

      if (!cp_parser_simulate_error (parser))
	{
	  char *message = concat ("expected ", token_desc, NULL);
	  cp_parser_error (parser, message);
	  free (message);
	}
      return NULL;
    }
}
