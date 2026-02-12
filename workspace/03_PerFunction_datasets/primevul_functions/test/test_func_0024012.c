create_internal_tmp_table_from_heap(THD *thd, TABLE *table,
                                    TMP_ENGINE_COLUMNDEF *start_recinfo,
                                    TMP_ENGINE_COLUMNDEF **recinfo,
                                    int error,
                                    bool ignore_last_dupp_key_error,
                                    bool *is_duplicate)
{
  TABLE new_table;
  TABLE_SHARE share;
  const char *save_proc_info;
  int write_err= 0;
  DBUG_ENTER("create_internal_tmp_table_from_heap");
  if (is_duplicate)
    *is_duplicate= FALSE;

  if (table->s->db_type() != heap_hton ||
      error != HA_ERR_RECORD_FILE_FULL)
  {


    table->file->print_error(error, MYF(ME_FATALERROR));
    DBUG_RETURN(1);
  }
  new_table= *table;
  share= *table->s;
  new_table.s= &share;
  new_table.s->db_plugin= ha_lock_engine(thd, TMP_ENGINE_HTON);
  if (!(new_table.file= get_new_handler(&share, &new_table.mem_root,
                                        new_table.s->db_type())))
    DBUG_RETURN(1);

  if (new_table.file->set_ha_share_ref(&share.ha_share))
  {
    delete new_table.file;
    DBUG_RETURN(1);
  }

  save_proc_info=thd->proc_info;
  THD_STAGE_INFO(thd, stage_converting_heap_to_myisam);

  new_table.no_rows= table->no_rows;
  if (create_internal_tmp_table(&new_table, table->key_info, start_recinfo,
                                recinfo,
                                thd->lex->select_lex.options |
			        thd->variables.option_bits))
    goto err2;
  if (open_tmp_table(&new_table))
    goto err1;
  if (table->file->indexes_are_disabled())
    new_table.file->ha_disable_indexes(HA_KEY_SWITCH_ALL);
  table->file->ha_index_or_rnd_end();
  if (table->file->ha_rnd_init_with_error(1))
    DBUG_RETURN(1);
  if (new_table.no_rows)
    new_table.file->extra(HA_EXTRA_NO_ROWS);
  else
  {

    table->file->info(HA_STATUS_VARIABLE);
    new_table.file->ha_start_bulk_insert(table->file->stats.records);
  }


  while (!table->file->ha_rnd_next(new_table.record[1]))
  {
    write_err= new_table.file->ha_write_tmp_row(new_table.record[1]);
    DBUG_EXECUTE_IF("raise_error", write_err= HA_ERR_FOUND_DUPP_KEY ;);
    if (write_err)
      goto err;
    if (thd->check_killed())
    {
      thd->send_kill_message();
      goto err_killed;
    }
  }
  if (!new_table.no_rows && new_table.file->ha_end_bulk_insert())
    goto err;

  if ((write_err=new_table.file->ha_write_tmp_row(table->record[0])))
  {
    if (new_table.file->is_fatal_error(write_err, HA_CHECK_DUP) ||
	!ignore_last_dupp_key_error)
      goto err;
    if (is_duplicate)
      *is_duplicate= TRUE;
  }
  else
  {
    if (is_duplicate)
      *is_duplicate= FALSE;
  }


  (void) table->file->ha_rnd_end();
  (void) table->file->ha_close();
  delete table->file;
  table->file=0;
  plugin_unlock(0, table->s->db_plugin);
  share.db_plugin= my_plugin_lock(0, share.db_plugin);
  new_table.s= table->s;
  *table= new_table;
  *table->s= share;

  table->file->change_table_ptr(table, table->s);
  table->use_all_columns();
  if (save_proc_info)
    thd_proc_info(thd, (!strcmp(save_proc_info,"Copying to tmp table") ?
                  "Copying to tmp table on disk" : save_proc_info));
  DBUG_RETURN(0);

 err:
  DBUG_PRINT("error",("Got error: %d",write_err));
  table->file->print_error(write_err, MYF(0));
err_killed:
  (void) table->file->ha_rnd_end();
  (void) new_table.file->ha_close();
 err1:
  new_table.file->ha_delete_table(new_table.s->path.str);
 err2:
  delete new_table.file;
  thd_proc_info(thd, save_proc_info);
  table->mem_root= new_table.mem_root;
  DBUG_RETURN(1);
}
