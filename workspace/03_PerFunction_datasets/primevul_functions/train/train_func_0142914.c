Expression_Obj Parser::lex_interp_uri()
  {

    return lex_interp< re_string_uri_open, re_string_uri_close >();
  }
