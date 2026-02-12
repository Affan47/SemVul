bool DML_prelocking_strategy::
handle_view(THD *thd, Query_tables_list *prelocking_ctx,
            TABLE_LIST *table_list, bool *need_prelocking)
{
  if (table_list->view->uses_stored_routines())
  {
    *need_prelocking= TRUE;

    sp_update_stmt_used_routines(thd, prelocking_ctx,
                                 &table_list->view->sroutines_list,
                                 table_list->top_table());
  }


  if (table_list->trg_event_map && table_list->next_global)
    table_list->next_global->trg_event_map= table_list->trg_event_map;
  return FALSE;
}
