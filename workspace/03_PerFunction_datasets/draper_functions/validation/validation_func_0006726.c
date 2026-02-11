cp_parser_template_declaration (cp_parser* parser, bool member_p)
{

  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_EXPORT))
    {

      cp_lexer_consume_token (parser->lexer);

      warning (0, "keyword %<export%> not implemented, and will be ignored");
    }

  cp_parser_template_declaration_after_export (parser, member_p);
}
