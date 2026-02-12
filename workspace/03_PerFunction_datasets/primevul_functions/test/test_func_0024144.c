void multi_update::prepare_to_read_rows()
{


  for (TABLE_LIST *tl= update_tables; tl; tl= tl->next_local)
    tl->table->mark_columns_needed_for_update();
}
