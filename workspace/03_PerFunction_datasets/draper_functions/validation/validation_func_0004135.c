write_data_header(IO_CACHE *file)
{
  uchar buf[ROWS_HEADER_LEN];


  assert(0);

  DBUG_ASSERT(m_table_id != ~0UL);
  DBUG_EXECUTE_IF("old_row_based_repl_4_byte_map_id_master",
                  {
                    int4store(buf + 0, m_table_id);
                    int2store(buf + 4, m_flags);
                    return (my_b_safe_write(file, buf, 6));
                  });
  int6store(buf + RW_MAPID_OFFSET, (ulonglong)m_table_id);
  int2store(buf + RW_FLAGS_OFFSET, m_flags);
  return (my_b_safe_write(file, buf, ROWS_HEADER_LEN));
}
