audit_log_ok (audit_ctx_t ctx, audit_event_t event, gpg_error_t err)
{
  log_item_t item;

  if (!ctx || ctx->failure)
    return;
  if (!event)
    {
      ctx->failure = "Invalid event passed to audit_log_ok";
      return;
    }
  if (!(item = create_log_item (ctx)))
    return;
  item->event = event;
  item->err = err;
  item->have_err = 1;
}
