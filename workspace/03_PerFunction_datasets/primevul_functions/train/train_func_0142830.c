Expression_Obj Parser::parse_bracket_list()
  {
    NESTING_GUARD(nestings);


    if (peek_css< list_terminator >(position))
    {

      return SASS_MEMORY_NEW(List, pstate, 0, SASS_SPACE, false, true);
    }

    bool has_paren = peek_css< exactly<'('> >() != NULL;


    Expression_Obj list = parse_space_list();

    if (!peek_css< exactly<','> >(position)) {
      List_Obj l = Cast<List>(list);
      if (!l || l->is_bracketed() || has_paren) {
        List_Obj bracketed_list = SASS_MEMORY_NEW(List, pstate, 1, SASS_SPACE, false, true);
        bracketed_list->append(list);
        return bracketed_list;
      }
      l->is_bracketed(true);
      return l;
    }


    List_Obj bracketed_list = SASS_MEMORY_NEW(List, pstate, 2, SASS_COMMA, false, true);

    bracketed_list->append(list);

    while (lex_css< exactly<','> >())
    {

      if (peek_css< list_terminator >(position)
      ) { break; }

      bracketed_list->append(parse_space_list());
    }

    return bracketed_list;
  }
