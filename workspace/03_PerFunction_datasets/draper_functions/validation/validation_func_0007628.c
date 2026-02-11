index_read_last_map(uchar *buf, const uchar *key,
                                      key_part_map keypart_map)
{
  DBUG_ASSERT(this->file->children_attached);
  MYSQL_INDEX_READ_ROW_START(table_share->db.str, table_share->table_name.str);
  ha_macro_statistic_inc(ha_read_key_count);
  int error=myrg_rkey(file,buf,active_index, key, keypart_map,
		      HA_READ_PREFIX_LAST);
  table->status=error ? STATUS_NOT_FOUND: 0;
  MYSQL_INDEX_READ_ROW_DONE(error);
  return error;
}
