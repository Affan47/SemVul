Supports_Condition_Obj Parser::parse_supports_operator(bool top_level)
  {
    Supports_Condition_Obj cond = parse_supports_condition_in_parens(top_level);
    if (cond.isNull()) return {};

    while (true) {
      Supports_Operator::Operand op = Supports_Operator::OR;
      if (lex < kwd_and >()) { op = Supports_Operator::AND; }
      else if(!lex < kwd_or >()) { break; }

      lex < css_whitespace >();
      Supports_Condition_Obj right = parse_supports_condition_in_parens(true);


      cond = SASS_MEMORY_NEW(Supports_Operator, pstate, cond, right, op);
    }
    return cond;
  }
