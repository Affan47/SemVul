yy_EmptyTitle()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "EmptyTitle"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l110;  if (!yymatchString("")) goto l110;  yyText(yybegin, yyend);  if (!(YY_END)) goto l110;
  yyprintf((stderr, "  ok   %s @ %s\n", "EmptyTitle", yybuf+yypos));
  return 1;
  l110:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "EmptyTitle", yybuf+yypos));
  return 0;
}
