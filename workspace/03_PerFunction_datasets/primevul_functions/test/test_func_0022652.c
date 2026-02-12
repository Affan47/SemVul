check_and_update_routine_version(THD *thd, Sroutine_hash_entry *rt,
                                 sp_head *sp)
{
  ulong spc_version= sp_cache_version();

  ulong version= sp ? sp->sp_cache_version() : spc_version;


  if (rt->m_sp_cache_version != version ||
      (version != spc_version && !sp->is_invoked()))
  {
    if (thd->m_reprepare_observer &&
        thd->m_reprepare_observer->report_error(thd))
    {


      DBUG_ASSERT(thd->is_error());
      return TRUE;
    }

    rt->m_sp_cache_version= version;
  }
  return FALSE;
}
