cp_parser_compound_statement (cp_parser *parser, bool in_statement_expr_p)
{
  tree compound_stmt;


  if (!cp_parser_require (parser, CPP_OPEN_BRACE, "`{'"))
    return error_mark_node;

  compound_stmt = begin_compound_stmt (false);

  cp_parser_statement_seq_opt (parser, in_statement_expr_p);

  finish_compound_stmt (compound_stmt);

  cp_parser_require (parser, CPP_CLOSE_BRACE, "`}'");

  return compound_stmt;
}
