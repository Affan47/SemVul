void handler::update_global_table_stats()
{
  TABLE_STATS * table_stats;

  status_var_add(table->in_use->status_var.rows_read, rows_read);
  DBUG_ASSERT(rows_tmp_read == 0);

  if (!table->in_use->userstat_running)
  {
    rows_read= rows_changed= 0;
    return;
  }

  if (rows_read + rows_changed == 0)
    return;

  DBUG_ASSERT(table->s);
  DBUG_ASSERT(table->s->table_cache_key.str);

  mysql_mutex_lock(&LOCK_global_table_stats);

  if (!(table_stats= (TABLE_STATS*)
        my_hash_search(&global_table_stats,
                    (uchar*) table->s->table_cache_key.str,
                    table->s->table_cache_key.length)))
  {
    if (!(table_stats = ((TABLE_STATS*)
                         my_malloc(sizeof(TABLE_STATS),
                                   MYF(MY_WME | MY_ZEROFILL)))))
    {

      goto end;
    }
    memcpy(table_stats->table, table->s->table_cache_key.str,
           table->s->table_cache_key.length);
    table_stats->table_name_length= (uint)table->s->table_cache_key.length;
    table_stats->engine_type= ht->db_type;


    if (my_hash_insert(&global_table_stats, (uchar*) table_stats))
    {

      my_free(table_stats);
      goto end;
    }
  }

  table_stats->rows_read+=    rows_read;
  table_stats->rows_changed+= rows_changed;
  table_stats->rows_changed_x_indexes+= (rows_changed *
                                         (table->s->keys ? table->s->keys :
                                          1));
  rows_read= rows_changed= 0;
end:
  mysql_mutex_unlock(&LOCK_global_table_stats);
}
