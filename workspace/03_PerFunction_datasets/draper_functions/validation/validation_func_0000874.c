yy_AtxInline(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "AtxInline"));
  {  int yypos1449= ctx->pos, yythunkpos1449= ctx->thunkpos;  if (!yy_Newline(ctx)) goto l1449;  goto l1448;
  l1449:;	  ctx->pos= yypos1449; ctx->thunkpos= yythunkpos1449;
  }
  {  int yypos1450= ctx->pos, yythunkpos1450= ctx->thunkpos;  if (!yy_Sp(ctx)) goto l1450;
  l1451:;
  {  int yypos1452= ctx->pos, yythunkpos1452= ctx->thunkpos;  if (!yymatchChar(ctx, '#')) goto l1452;  goto l1451;
  l1452:;	  ctx->pos= yypos1452; ctx->thunkpos= yythunkpos1452;
  }  if (!yy_Sp(ctx)) goto l1450;  if (!yy_Newline(ctx)) goto l1450;  goto l1448;
  l1450:;	  ctx->pos= yypos1450; ctx->thunkpos= yythunkpos1450;
  }  if (!yy_Inline(ctx)) goto l1448;
  yyprintf((stderr, "  ok   %s @ %s\n", "AtxInline", ctx->buf+ctx->pos));
  return 1;
  l1448:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "AtxInline", ctx->buf+ctx->pos));
  return 0;
}
