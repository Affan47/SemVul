open_and_process_routine(THD *thd, Query_tables_list *prelocking_ctx,
                         Sroutine_hash_entry *rt,
                         Prelocking_strategy *prelocking_strategy,
                         bool has_prelocking_list,
                         Open_table_context *ot_ctx,
                         bool *need_prelocking, bool *routine_modifies_data)
{
  MDL_key::enum_mdl_namespace mdl_type= rt->mdl_request.key.mdl_namespace();
  DBUG_ENTER("open_and_process_routine");

  *routine_modifies_data= false;

  switch (mdl_type)
  {
  case MDL_key::FUNCTION:
  case MDL_key::PROCEDURE:
    {
      sp_head *sp;


      if (rt != (Sroutine_hash_entry*)prelocking_ctx->sroutines_list.first ||
          mdl_type != MDL_key::PROCEDURE)
      {


        DBUG_ASSERT(rt->mdl_request.type == MDL_SHARED);


        MDL_deadlock_handler mdl_deadlock_handler(ot_ctx);

        thd->push_internal_handler(&mdl_deadlock_handler);
        bool result= thd->mdl_context.acquire_lock(&rt->mdl_request,
                                                   ot_ctx->get_timeout());
        thd->pop_internal_handler();

        if (result)
          DBUG_RETURN(TRUE);

        DEBUG_SYNC(thd, "after_shared_lock_pname");


        if (sp_cache_routine(thd, rt, has_prelocking_list, &sp))
          DBUG_RETURN(TRUE);


        if (check_and_update_routine_version(thd, rt, sp))
          DBUG_RETURN(TRUE);


        if (sp)
        {
          *routine_modifies_data= sp->modifies_data();

          if (!has_prelocking_list)
            prelocking_strategy->handle_routine(thd, prelocking_ctx, rt, sp,
                                                need_prelocking);
        }
      }
      else
      {


        if (sp_cache_routine(thd, rt, FALSE, &sp))
          DBUG_RETURN(TRUE);
      }
    }
    break;
  case MDL_key::TRIGGER:


    break;
  default:

    DBUG_ASSERT(0);
  }
  DBUG_RETURN(FALSE);
}
