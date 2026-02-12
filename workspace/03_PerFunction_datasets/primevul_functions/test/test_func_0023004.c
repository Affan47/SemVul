int ha_maria::open(const char *name, int mode, uint test_if_locked)
{
  uint i;

#ifdef NOT_USED


  if (!(test_if_locked & HA_OPEN_TMP_TABLE) && opt_maria_use_mmap)
    test_if_locked|= HA_OPEN_MMAP;
#endif

  if (maria_recover_options & HA_RECOVER_ANY)
  {

    test_if_locked|= HA_OPEN_ABORT_IF_CRASHED;
  }

  if (aria_readonly)
    test_if_locked|= HA_OPEN_IGNORE_MOVED_STATE;

  if (!(file= maria_open(name, mode, test_if_locked | HA_OPEN_FROM_SQL_LAYER,
                         s3_open_args())))
  {
    if (my_errno == HA_ERR_OLD_FILE)
    {
      push_warning(current_thd, Sql_condition::WARN_LEVEL_NOTE,
                   ER_CRASHED_ON_USAGE,
                   zerofill_error_msg);
    }
    return (my_errno ? my_errno : -1);
  }
  if (aria_readonly)
    file->s->options|= HA_OPTION_READ_ONLY_DATA;

  file->s->chst_invalidator= query_cache_invalidate_by_MyISAM_filename_ref;

  file->external_ref= (void*) table;

  if (test_if_locked & (HA_OPEN_IGNORE_IF_LOCKED | HA_OPEN_TMP_TABLE))
    maria_extra(file, HA_EXTRA_NO_WAIT_LOCK, 0);

  info(HA_STATUS_NO_LOCK | HA_STATUS_VARIABLE | HA_STATUS_CONST);
  if (!(test_if_locked & HA_OPEN_WAIT_IF_LOCKED))
    maria_extra(file, HA_EXTRA_WAIT_LOCK, 0);
  if ((data_file_type= file->s->data_file_type) != STATIC_RECORD)
    int_table_flags |= HA_REC_NOT_IN_SEQ;
  if (!file->s->base.born_transactional)
  {


    int_table_flags|= HA_CAN_INSERT_DELAYED | HA_NO_TRANSACTIONS;
  }
  else
    int_table_flags|= HA_CRASH_SAFE;

  if (file->s->options & (HA_OPTION_CHECKSUM | HA_OPTION_COMPRESS_RECORD))
    int_table_flags |= HA_HAS_NEW_CHECKSUM;


  if (file->s->options & HA_OPTION_PAGE_CHECKSUM &&
      file->s->base.born_transactional)
    int_table_flags |= HA_CAN_ONLINE_BACKUPS;


  if (file->s->data_file_type == STATIC_RECORD &&
      (file->s->has_varchar_fields || file->s->has_null_fields))
    int_table_flags|= HA_RECORD_MUST_BE_CLEAN_ON_WRITE;

  for (i= 0; i < table->s->keys; i++)
  {
    plugin_ref parser= table->key_info[i].parser;
    if (table->key_info[i].flags & HA_USES_PARSER)
      file->s->keyinfo[i].parser=
        (struct st_mysql_ftparser *)plugin_decl(parser)->info;
    table->key_info[i].block_size= file->s->keyinfo[i].block_length;
  }
  my_errno= 0;


  if (file->s->reopen == 1 && ! (test_if_locked & HA_OPEN_TMP_TABLE))
  {
    if (file->s->delay_key_write)
      feature_files_opened_with_delayed_keys++;
  }

  return my_errno;
}
