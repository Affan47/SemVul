Expression_Obj Parser::parse_comma_list(bool delayed)
  {
    NESTING_GUARD(nestings);


    if (peek_css< list_terminator >(position))
    {

      return SASS_MEMORY_NEW(List, pstate, 0);
    }


    Expression_Obj list = parse_space_list();

    if (!peek_css< exactly<','> >(position)) {


      if (!delayed) list->set_delayed(false);
      return list;
    }


    List_Obj comma_list = SASS_MEMORY_NEW(List, pstate, 2, SASS_COMMA);

    comma_list->append(list);

    while (lex_css< exactly<','> >())
    {

      if (peek_css< list_terminator >(position)
      ) { break; }

      comma_list->append(parse_space_list());
    }

    return comma_list;
  }
