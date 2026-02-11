c_parser_next_tokens_start_typename (c_parser *parser, enum c_lookahead_kind la)
{
  c_token *token = c_parser_peek_token (parser);
  if (c_token_starts_typename (token))
    return true;


  if (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID


      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  || c_parser_peek_2nd_token (parser)->type == CPP_MULT)


      && !lookup_name (token->value))
    return true;

  return false;
}
