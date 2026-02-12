open_table_get_mdl_lock(THD *thd, Open_table_context *ot_ctx,
                        MDL_request *mdl_request,
                        uint flags,
                        MDL_ticket **mdl_ticket)
{
  MDL_request mdl_request_shared;

  if (flags & (MYSQL_OPEN_FORCE_SHARED_MDL |
               MYSQL_OPEN_FORCE_SHARED_HIGH_PRIO_MDL))
  {


    DBUG_ASSERT(!(flags & MYSQL_OPEN_FORCE_SHARED_MDL) ||
                !(flags & MYSQL_OPEN_FORCE_SHARED_HIGH_PRIO_MDL));

    mdl_request_shared.init(&mdl_request->key,
                            (flags & MYSQL_OPEN_FORCE_SHARED_MDL) ?
                            MDL_SHARED : MDL_SHARED_HIGH_PRIO,
                            MDL_TRANSACTION);
    mdl_request= &mdl_request_shared;
  }

  if (flags & MYSQL_OPEN_FAIL_ON_MDL_CONFLICT)
  {


    if (thd->mdl_context.try_acquire_lock(mdl_request))
      return TRUE;
    if (mdl_request->ticket == NULL)
    {
      my_error(ER_WARN_I_S_SKIPPED_TABLE, MYF(0),
               mdl_request->key.db_name(), mdl_request->key.name());
      return TRUE;
    }
  }
  else
  {


    MDL_deadlock_handler mdl_deadlock_handler(ot_ctx);

    thd->push_internal_handler(&mdl_deadlock_handler);
    bool result= thd->mdl_context.acquire_lock(mdl_request,
                                               ot_ctx->get_timeout());
    thd->pop_internal_handler();

    if (result && !ot_ctx->can_recover_from_failed_open())
      return TRUE;
  }
  *mdl_ticket= mdl_request->ticket;
  return FALSE;
}
