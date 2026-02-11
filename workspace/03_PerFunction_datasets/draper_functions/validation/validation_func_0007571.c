ecore_imf_context_input_panel_imdata_get(Ecore_IMF_Context *ctx, void *data, int *len)
{
   if (!ECORE_MAGIC_CHECK(ctx, ECORE_MAGIC_CONTEXT))
     {
        ECORE_MAGIC_FAIL(ctx, ECORE_MAGIC_CONTEXT,
                         "ecore_imf_context_input_panel_imdata_get");
        return;
     }

   if (!data) return;

   if (ctx->klass->input_panel_imdata_get)
     ctx->klass->input_panel_imdata_get(ctx, data, len);
}
