int _ma_update_state_lsns_sub(MARIA_SHARE *share, LSN lsn, TrID create_trid,
                              my_bool do_sync,
                              my_bool update_create_rename_lsn)
{
  uchar buf[LSN_STORE_SIZE * 3], *ptr;
  uchar trid_buff[8];
  File file= share->kfile.file;
  DBUG_ASSERT(file >= 0);

  if (lsn == LSN_IMPOSSIBLE)
  {
    int res;
    LEX_CUSTRING log_array[TRANSLOG_INTERNAL_PARTS + 1];

    log_array[TRANSLOG_INTERNAL_PARTS + 0].str=
      (uchar *)(share->open_file_name.str);
    log_array[TRANSLOG_INTERNAL_PARTS + 0].length=
      share->open_file_name.length + 1;
    if ((res= translog_write_record(&lsn, LOGREC_IMPORTED_TABLE,
                                    &dummy_transaction_object, NULL,
                                    (translog_size_t)
                                    log_array[TRANSLOG_INTERNAL_PARTS +
                                              0].length,
                                    sizeof(log_array)/sizeof(log_array[0]),
                                    log_array, NULL, NULL)))
      return res;
  }

  for (ptr= buf; ptr < (buf + sizeof(buf)); ptr+= LSN_STORE_SIZE)
    lsn_store(ptr, lsn);
  share->state.skip_redo_lsn= share->state.is_of_horizon= lsn;
  share->state.create_trid= create_trid;
  mi_int8store(trid_buff, create_trid);


  if (update_create_rename_lsn ||
      (share->state.create_rename_lsn > lsn && lsn != LSN_IMPOSSIBLE))
  {
    share->state.create_rename_lsn= lsn;
    if (share->id != 0)
    {


      translog_deassign_id_from_share(share);
    }
  }
  else
    lsn_store(buf, share->state.create_rename_lsn);
  return (my_pwrite(file, buf, sizeof(buf),
                    sizeof(share->state.header) +
                    MARIA_FILE_CREATE_RENAME_LSN_OFFSET, MYF(MY_NABP)) ||
          my_pwrite(file, trid_buff, sizeof(trid_buff),
                    sizeof(share->state.header) +
                    MARIA_FILE_CREATE_TRID_OFFSET, MYF(MY_NABP)) ||
          (do_sync && mysql_file_sync(file, MYF(0))));
}
