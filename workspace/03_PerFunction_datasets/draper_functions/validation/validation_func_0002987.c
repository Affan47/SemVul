evt_rec_init(EVTCONTEXT *ctx, int syslog_pri, const char *desc)
{
  EVTREC *e;

  e = (EVTREC *) malloc(sizeof(EVTREC));
  if (e)
    {
      e->ev_ctx = evt_ctx_ref(ctx);
      e->ev_desc = strdup(desc);
      e->ev_pairs = NULL;
      e->ev_last_pair = NULL;
      e->ev_ref = 1;
      e->ev_syslog_pri = syslog_pri;
      if (!evt_rec_call_hooks(e))
        {
          free(e);
          e = NULL;
        }
    }
  return e;
}
