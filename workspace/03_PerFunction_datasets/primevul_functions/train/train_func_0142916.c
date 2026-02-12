Token Parser::lex_identifier()
  {

    if (!lex< identifier >()) {
      css_error("Invalid CSS", " after ", ": expected identifier, was ");
    }

    return token;
  }
