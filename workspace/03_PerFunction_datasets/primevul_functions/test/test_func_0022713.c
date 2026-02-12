bool tdc_open_view(THD *thd, TABLE_LIST *table_list, uint flags)
{
  TABLE not_used;
  TABLE_SHARE *share;
  bool err= TRUE;

  if (!(share= tdc_acquire_share(thd, table_list, GTS_VIEW)))
    return TRUE;

  DBUG_ASSERT(share->is_view);

  if (flags & CHECK_METADATA_VERSION)
  {


    if (check_and_update_table_version(thd, table_list, share))
      goto ret;
  }

  err= mysql_make_view(thd, share, table_list, (flags & OPEN_VIEW_NO_PARSE));
ret:
  tdc_release_share(share);

  return err;
}
