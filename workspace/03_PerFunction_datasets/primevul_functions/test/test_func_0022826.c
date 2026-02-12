int MYSQLlex(YYSTYPE *yylval, THD *thd)
{
  Lex_input_stream *lip= & thd->m_parser_state->m_lip;
  int token;

  if (lip->lookahead_token >= 0)
  {


    token= lip->lookahead_token;
    lip->lookahead_token= -1;
    *yylval= *(lip->lookahead_yylval);
    lip->lookahead_yylval= NULL;
    return token;
  }

  token= lex_one_token(yylval, thd);
  lip->add_digest_token(token, yylval);

  switch(token) {
  case WITH:


    token= lex_one_token(yylval, thd);
    lip->add_digest_token(token, yylval);
    switch(token) {
    case CUBE_SYM:
      return WITH_CUBE_SYM;
    case ROLLUP_SYM:
      return WITH_ROLLUP_SYM;
    default:


      lip->lookahead_yylval= lip->yylval;
      lip->yylval= NULL;
      lip->lookahead_token= token;
      return WITH;
    }
    break;
  default:
    break;
  }
  return token;
}
