yy_HexEntity(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "HexEntity"));  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_BEGIN)) goto l302;  if (!yymatchChar(ctx, '&')) goto l302;  if (!yymatchChar(ctx, '#')) goto l302;  if (!yymatchClass(ctx, (unsigned char *)"\000\000\000\000\000\000\000\000\000\000\000\001\000\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l302;  if (!yymatchClass(ctx, (unsigned char *)"\000\000\000\000\000\000\377\003\176\000\000\000\176\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l302;
  l303:;
  {  int yypos304= ctx->pos, yythunkpos304= ctx->thunkpos;  if (!yymatchClass(ctx, (unsigned char *)"\000\000\000\000\000\000\377\003\176\000\000\000\176\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l304;  goto l303;
  l304:;	  ctx->pos= yypos304; ctx->thunkpos= yythunkpos304;
  }  if (!yymatchChar(ctx, ';')) goto l302;  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_END)) goto l302;
  yyprintf((stderr, "  ok   %s @ %s\n", "HexEntity", ctx->buf+ctx->pos));
  return 1;
  l302:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "HexEntity", ctx->buf+ctx->pos));
  return 0;
}
