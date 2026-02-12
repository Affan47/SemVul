void Parser::advanceToNextToken() {
      lex < css_comments >(false);

      pstate += pstate.offset;
      pstate.offset.column = 0;
      pstate.offset.line = 0;
    }
