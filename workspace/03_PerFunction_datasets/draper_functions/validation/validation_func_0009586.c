std_handler_cancel (assuan_context_t ctx, char *line)
{
  if (ctx->cancel_notify_fnc)

    ctx->cancel_notify_fnc (ctx, line);
  return PROCESS_DONE (ctx, set_error (ctx, GPG_ERR_NOT_IMPLEMENTED, NULL));
}
