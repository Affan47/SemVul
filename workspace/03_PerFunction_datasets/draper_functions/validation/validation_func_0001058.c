_mesa_flush(struct gl_context *ctx)
{
   FLUSH_VERTICES( ctx, 0 );
   FLUSH_CURRENT( ctx, 0 );
   if (ctx->Driver.Flush) {
      ctx->Driver.Flush(ctx);
   }
}
