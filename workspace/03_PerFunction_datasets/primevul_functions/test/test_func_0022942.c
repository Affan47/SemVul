void ha_maria::start_bulk_insert(ha_rows rows, uint flags)
{
  DBUG_ENTER("ha_maria::start_bulk_insert");
  THD *thd= table->in_use;
  MARIA_SHARE *share= file->s;
  bool index_disabled= 0;
  DBUG_PRINT("info", ("start_bulk_insert: rows %lu", (ulong) rows));


  if ((!rows || rows > MARIA_MIN_ROWS_TO_USE_WRITE_CACHE) && !has_long_unique())
  {
    ulonglong size= thd->variables.read_buff_size, tmp;
    if (rows)
    {
      if (file->state->records)
      {
        MARIA_INFO maria_info;
        maria_status(file, &maria_info, HA_STATUS_NO_LOCK |HA_STATUS_VARIABLE);
        set_if_smaller(size, maria_info.mean_reclength * rows);
      }
      else if (table->s->avg_row_length)
        set_if_smaller(size, (size_t) (table->s->avg_row_length * rows));
    }
    tmp= (ulong) size;
    maria_extra(file, HA_EXTRA_WRITE_CACHE, (void*) &tmp);
  }

  can_enable_indexes= (maria_is_all_keys_active(share->state.key_map,
                                                share->base.keys));
  bulk_insert_single_undo= BULK_INSERT_NONE;

  if (!(specialflag & SPECIAL_SAFE_MODE))
  {


    if ((file->state->records == 0) &&
        (share->state.state.records == 0) && can_enable_indexes &&
        (!rows || rows >= MARIA_MIN_ROWS_TO_DISABLE_INDEXES) &&
        (file->lock.type == TL_WRITE || file->lock.type == TL_UNLOCK) &&
        (!share->have_versioning || !share->now_transactional ||
         file->used_tables->use_count == 1))
    {


      if (file->open_flags & HA_OPEN_INTERNAL_TABLE)
      {

        file->update|= HA_STATE_CHANGED;
        index_disabled= share->base.keys > 0;
        maria_clear_all_keys_active(file->s->state.key_map);
      }
      else
      {
        my_bool all_keys= MY_TEST(flags & HA_CREATE_UNIQUE_INDEX_BY_SORT);


        MARIA_SHARE *share= file->s;
        MARIA_KEYDEF    *key=share->keyinfo;
        uint          i;

        DBUG_ASSERT(share->state.state.records == 0 &&
                    (!rows || rows >= MARIA_MIN_ROWS_TO_DISABLE_INDEXES));
        for (i=0 ; i < share->base.keys ; i++,key++)
        {
          if (!(key->flag & (HA_SPATIAL | HA_AUTO_KEY | HA_RTREE_INDEX)) &&
              ! maria_too_big_key_for_sort(key,rows) && share->base.auto_key != i+1 &&
              (all_keys || !(key->flag & HA_NOSAME)) &&
              table->key_info[i].algorithm != HA_KEY_ALG_LONG_HASH)
          {
            maria_clear_key_active(share->state.key_map, i);
            index_disabled= 1;
            file->update|= HA_STATE_CHANGED;
            file->create_unique_index_by_sort= all_keys;
          }
        }
      }
      if (share->now_transactional)
      {
        bulk_insert_single_undo= BULK_INSERT_SINGLE_UNDO_AND_NO_REPAIR;
        write_log_record_for_bulk_insert(file);
        _ma_tmp_disable_logging_for_table(file, TRUE);


        maria_delete_all_rows(file);
      }
    }
    else if (!file->bulk_insert &&
             (!rows || rows >= MARIA_MIN_ROWS_TO_USE_BULK_INSERT))
    {
      maria_init_bulk_insert(file,
                             (size_t) thd->variables.bulk_insert_buff_size,
                             rows);
    }
  }
  can_enable_indexes= index_disabled;
  DBUG_VOID_RETURN;
}
