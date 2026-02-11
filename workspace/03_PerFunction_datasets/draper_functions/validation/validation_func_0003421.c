cmor_set_table(int table) {
  extern int CMOR_TABLE;
  char msg[CMOR_MAX_STRING];
  cmor_add_traceback("cmor_set_table");
  cmor_is_setup();
  if (table>cmor_ntables) {
    snprintf(msg,CMOR_MAX_STRING,"Invalid table number: %i",table);
    cmor_handle_error(msg,CMOR_CRITICAL);
  }
  if (cmor_tables[table].table_id=='\0') {
    snprintf(msg,CMOR_MAX_STRING,"Invalid table: %i , not loaded yet!",table);
    cmor_handle_error(msg,CMOR_CRITICAL);
  }
  CMOR_TABLE = table;
  cmor_pop_traceback();
  return 0;
}
