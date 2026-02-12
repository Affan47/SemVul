Ruleset_Obj Parser::parse_ruleset(Lookahead lookahead)
  {
    NESTING_GUARD(nestings);

    Block_Obj parent = block_stack.back();
    bool is_root = parent && parent->is_root();

    lex < optional_css_whitespace >(false, true);

    Ruleset_Obj ruleset = SASS_MEMORY_NEW(Ruleset, pstate);

    if (lookahead.parsable) ruleset->selector(parse_selector_list(false));
    else {
      Selector_List_Obj list = SASS_MEMORY_NEW(Selector_List, pstate);
      list->schema(parse_selector_schema(lookahead.position, false));
      ruleset->selector(list);
    }

    stack.push_back(Scope::Rules);
    ruleset->block(parse_block());
    stack.pop_back();

    ruleset->update_pstate(pstate);
    ruleset->block()->update_pstate(pstate);

    ruleset->is_root(is_root);

    return ruleset;
  }
