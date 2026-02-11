cmd_insert_internal(dbcallback_i& cb, const prep_stmt& pst,
  const string_ref *fvals, size_t fvalslen)
{
  if (!for_write_flag) {
    return cb.dbcb_resp_short(2, "readonly");
  }
  lock_tables_if();
  if (lock == 0) {
    return cb.dbcb_resp_short(1, "lock_tables");
  }
  if (pst.get_table_id() >= table_vec.size()) {
    return cb.dbcb_resp_short(2, "tblnum");
  }
  TABLE *const table = table_vec[pst.get_table_id()].table;
  handler *const hnd = table->file;
  uchar *const buf = table->record[0];
  empty_record(table);
  memset(buf, 0, table->s->null_bytes);
  const prep_stmt::fields_type& rf = pst.get_ret_fields();
  const size_t n = std::min(rf.size(), fvalslen);
  for (size_t i = 0; i < n; ++i) {
    uint32_t fn = rf[i];
    Field *const fld = table->field[fn];
    if (fvals[i].begin() == 0) {
      fld->set_null();
    } else {
      fld->store(fvals[i].begin(), fvals[i].size(), &my_charset_bin);
    }
  }
  table->next_number_field = table->found_next_number_field;

  const int r = hnd->ha_write_row(buf);
  const ulonglong insert_id = table->file->insert_id_for_cur_row;
  table->next_number_field = 0;
  table_vec[pst.get_table_id()].modified = true;
  if (r == 0 && table->found_next_number_field != 0) {
    return cb.dbcb_resp_short_num64(0, insert_id);
  }
  if (r != 0) {
    return cb.dbcb_resp_short_num(1, r);
  }
  return cb.dbcb_resp_short(0, "");
}
