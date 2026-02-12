static void update_maria_group_commit(MYSQL_THD thd,
                                      struct st_mysql_sys_var *var,
                                      void *var_ptr, const void *save)
{
  ulong value= (ulong)*((long *)var_ptr);
  DBUG_ENTER("update_maria_group_commit");
  DBUG_PRINT("enter", ("old value: %lu  new value %lu  rate %lu",
                       value, (ulong)(*(long *)save),
                       maria_group_commit_interval));

  switch (value) {
  case TRANSLOG_GCOMMIT_NONE:
    break;
  case TRANSLOG_GCOMMIT_HARD:
    translog_hard_group_commit(FALSE);
    break;
  case TRANSLOG_GCOMMIT_SOFT:
    translog_soft_sync(FALSE);
    if (maria_group_commit_interval)
      translog_soft_sync_end();
    break;
  default:
    DBUG_ASSERT(0);
  }
  value= *(ulong *)var_ptr= (ulong)(*(long *)save);
  translog_sync();

  switch (value) {
  case TRANSLOG_GCOMMIT_NONE:
    break;
  case TRANSLOG_GCOMMIT_HARD:
    translog_hard_group_commit(TRUE);
    break;
  case TRANSLOG_GCOMMIT_SOFT:
    translog_soft_sync(TRUE);

    if (maria_group_commit_interval)
      translog_soft_sync_start();
    break;
  default:
    DBUG_ASSERT(0);
  }
  DBUG_VOID_RETURN;
}
