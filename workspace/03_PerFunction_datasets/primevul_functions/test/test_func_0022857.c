bool consume_comment(Lex_input_stream *lip, int remaining_recursions_permitted)
{

  DBUG_ASSERT(remaining_recursions_permitted == 0 ||
              remaining_recursions_permitted == 1);
  uchar c;
  while (! lip->eof())
  {
    c= lip->yyGet();

    if (remaining_recursions_permitted == 1)
    {
      if ((c == '/') && (lip->yyPeek() == '*'))
      {
        lip->yyUnput('(');
        lip->yySkip();

        lip->yySkip();
        if (consume_comment(lip, 0))
          return true;

        lip->yyUnput(')');
        lip->yySkip();
        continue;
      }
    }

    if (c == '*')
    {
      if (lip->yyPeek() == '/')
      {
        lip->yySkip();
        return FALSE;
      }
    }

    if (c == '\n')
      lip->yylineno++;
  }

  return TRUE;
}
