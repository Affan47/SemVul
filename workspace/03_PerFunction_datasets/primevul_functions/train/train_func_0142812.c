Value_Obj Parser::parse_static_value()
  {
    lex< static_value >();
    Token str(lexed);


    --pstate.offset.column;
    --after_token.column;
    --str.end;
    --position;

    return color_or_string(str.time_wspace());;
  }
