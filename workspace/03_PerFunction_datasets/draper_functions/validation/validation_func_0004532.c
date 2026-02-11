yy_StartList()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "StartList"));
  {  int yypos1323= yypos, yythunkpos1323= yythunkpos;  if (!yymatchDot()) goto l1322;  yypos= yypos1323; yythunkpos= yythunkpos1323;
  }  yyDo(yy_1_StartList, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "StartList", yybuf+yypos));
  return 1;
  l1322:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "StartList", yybuf+yypos));
  return 0;
}
