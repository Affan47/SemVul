Expression_Obj Parser::parse_conjunction()
  {
    NESTING_GUARD(nestings);
    advanceToNextToken();
    ParserState state(pstate);

    Expression_Obj rel = parse_relation();

    std::vector<Expression_Obj> operands;
    while (lex_css< kwd_and >()) {
      operands.push_back(parse_relation());
    }

    if (operands.size() == 0) return rel;

    Expression_Obj ex = fold_operands(rel, operands, { Sass_OP::AND });
    state.offset = pstate - state + pstate.offset;
    ex->pstate(state);
    return ex;
  }
