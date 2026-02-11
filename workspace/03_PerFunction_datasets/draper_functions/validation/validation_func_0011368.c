main (int argc, char **argv)
{
  Jbig2Ctx *ctx;
  Jbig2WordStream ws;
  Jbig2ArithState *as;
  int i;
  Jbig2ArithCx cx = 0;

  ctx = jbig2_ctx_new(NULL, 0, NULL, NULL, NULL);

  ws.get_next_word = test_get_word;
  as = jbig2_arith_new (ctx, &ws);
#ifdef JBIG2_DEBUG_ARITH
  jbig2_arith_trace (as, cx);
#endif

  for (i = 0; i < 256; i++)
    {
      bool D;

      D = jbig2_arith_decode (as, &cx);
#ifdef JBIG2_DEBUG_ARITH
      fprintf(stderr, "%3d: D = %d, ", i, D);
      jbig2_arith_trace (as, cx);
#endif
    }

  jbig2_free(ctx->allocator, as);

  jbig2_ctx_free(ctx);

  return 0;
}
