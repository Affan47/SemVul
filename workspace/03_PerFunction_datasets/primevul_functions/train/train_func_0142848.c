Token Parser::lex_variable()
  {

    if (!peek< exactly <'$'> >()) {
      css_error("Invalid CSS", " after ", ": expected \"$\", was ");
    }

    if (!lex< sequence < exactly <'$'>, identifier > >()) {
      lex< exactly <'$'> >();
      css_error("Invalid CSS", " after ", ": expected identifier, was ");
    }

    return token;
  }
