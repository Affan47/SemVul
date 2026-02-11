_mesa_DepthRange(GLclampd nearval, GLclampd farval)
{
   unsigned i;
   GET_CURRENT_CONTEXT(ctx);

   FLUSH_VERTICES(ctx, 0);

   if (MESA_VERBOSE&VERBOSE_API)
      _mesa_debug(ctx, "glDepthRange %f %f\n", nearval, farval);


   for (i = 0; i < ctx->Const.MaxViewports; i++)
      set_depth_range_no_notify(ctx, i, nearval, farval);

   if (ctx->Driver.DepthRange) {
      ctx->Driver.DepthRange(ctx);
   }
}
