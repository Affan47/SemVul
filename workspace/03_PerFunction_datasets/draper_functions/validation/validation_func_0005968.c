leave_ctx_new (GSimpleAsyncResult *result,
    const gchar *message,
    TpChannelGroupChangeReason reason)
{
  LeaveCtx *ctx = g_slice_new (LeaveCtx);

  ctx->result = result;
  ctx->message = message != NULL ? g_strdup (message) : g_strdup ("");
  ctx->reason = reason;

  return ctx;
}
