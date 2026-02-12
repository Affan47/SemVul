Expression_Obj Parser::parse_disjunction()
  {
    NESTING_GUARD(nestings);
    advanceToNextToken();
    ParserState state(pstate);

    Expression_Obj conj = parse_conjunction();

    std::vector<Expression_Obj> operands;
    while (lex_css< kwd_or >())
      operands.push_back(parse_conjunction());

    if (operands.size() == 0) return conj;

    Expression_Obj ex = fold_operands(conj, operands, { Sass_OP::OR });
    state.offset = pstate - state + pstate.offset;
    ex->pstate(state);
    return ex;
  }
