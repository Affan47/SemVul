void Item_trigger_field::setup_field(THD *thd, TABLE *table,
                                     GRANT_INFO *table_grant_info)
{


  enum_mark_columns save_mark_used_columns= thd->mark_used_columns;
  thd->mark_used_columns= MARK_COLUMNS_NONE;


  (void)find_field_in_table(thd, table, field_name, (uint) strlen(field_name),
                            0, &field_idx);
  thd->mark_used_columns= save_mark_used_columns;
  triggers= table->triggers;
  table_grants= table_grant_info;
}
