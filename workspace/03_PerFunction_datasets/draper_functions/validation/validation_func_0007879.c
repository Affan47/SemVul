yy_NoteReference(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;  yyDo(ctx, yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "NoteReference"));  yyText(ctx, ctx->begin, ctx->end);  if (!( extension(EXT_NOTES) )) goto l635;  if (!yy_RawNoteReference(ctx)) goto l635;  yyDo(ctx, yySet, -1, 0);  yyDo(ctx, yy_1_NoteReference, ctx->begin, ctx->end);
  yyprintf((stderr, "  ok   %s @ %s\n", "NoteReference", ctx->buf+ctx->pos));  yyDo(ctx, yyPop, 1, 0);
  return 1;
  l635:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "NoteReference", ctx->buf+ctx->pos));
  return 0;
}
