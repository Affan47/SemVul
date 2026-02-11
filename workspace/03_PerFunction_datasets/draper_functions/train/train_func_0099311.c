ecore_imf_context_client_window_set(Ecore_IMF_Context *ctx, void *window)
{
   if (!ECORE_MAGIC_CHECK(ctx, ECORE_MAGIC_CONTEXT))
     {
        ECORE_MAGIC_FAIL(ctx, ECORE_MAGIC_CONTEXT,
                         "ecore_imf_context_client_window_set");
        return;
     }
   if (ctx->klass->client_window_set) ctx->klass->client_window_set(ctx, window);
   ctx->window = window;
}
