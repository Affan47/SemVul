static my_bool xarecover_handlerton(THD *unused, plugin_ref plugin,
                                    void *arg)
{
  handlerton *hton= plugin_hton(plugin);
  struct xarecover_st *info= (struct xarecover_st *) arg;
  int got;

  if (hton->state == SHOW_OPTION_YES && hton->recover)
  {
    while ((got= hton->recover(hton, info->list, info->len)) > 0 )
    {
      sql_print_information("Found %d prepared transaction(s) in %s",
                            got, hton_name(hton)->str);


      my_xid wsrep_limit __attribute__((unused))= 0;


      if (WSREP_ON)
        wsrep_limit= wsrep_order_and_check_continuity(info->list, got);

      for (int i=0; i < got; i ++)
      {
        my_xid x= IF_WSREP(wsrep_is_wsrep_xid(&info->list[i]) ?
                           wsrep_xid_seqno(&info->list[i]) :
                           info->list[i].get_my_xid(),
                           info->list[i].get_my_xid());
        if (!x)
        {
          DBUG_EXECUTE("info",{
            char buf[XIDDATASIZE*4+6];
            _db_doprnt_("ignore xid %s", xid_to_str(buf, info->list[i]));
            });
          xid_cache_insert(info->list + i);
          info->found_foreign_xids++;
          continue;
        }
        if (IF_WSREP(!(wsrep_emulate_bin_log &&
                       wsrep_is_wsrep_xid(info->list + i) &&
                       x <= wsrep_limit) && info->dry_run,
                     info->dry_run))
        {
          info->found_my_xids++;
          continue;
        }

        if (IF_WSREP((wsrep_emulate_bin_log &&
                      wsrep_is_wsrep_xid(info->list + i) &&
                      x <= wsrep_limit), false) ||
            (info->commit_list ?
             my_hash_search(info->commit_list, (uchar *)&x, sizeof(x)) != 0 :
             tc_heuristic_recover == TC_HEURISTIC_RECOVER_COMMIT))
        {
          int rc= hton->commit_by_xid(hton, info->list+i);
          if (rc == 0)
          {
            DBUG_EXECUTE("info",{
              char buf[XIDDATASIZE*4+6];
              _db_doprnt_("commit xid %s", xid_to_str(buf, info->list[i]));
              });
          }
        }
        else
        {
          int rc= hton->rollback_by_xid(hton, info->list+i);
          if (rc == 0)
          {
            DBUG_EXECUTE("info",{
              char buf[XIDDATASIZE*4+6];
              _db_doprnt_("rollback xid %s", xid_to_str(buf, info->list[i]));
              });
          }
        }
      }
      if (got < info->len)
        break;
    }
  }
  return FALSE;
}
