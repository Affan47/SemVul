bool JOIN::build_explain()
{
  DBUG_ENTER("JOIN::build_explain");
  have_query_plan= QEP_AVAILABLE;


  MEM_ROOT *old_mem_root= thd->mem_root;
  Item *old_free_list __attribute__((unused))= thd->free_list;
  thd->mem_root= thd->lex->explain->mem_root;
  bool res= save_explain_data(thd->lex->explain, false ,
                        need_tmp,
                        !skip_sort_order && !no_order && (order || group_list),
                        select_distinct);
  thd->mem_root= old_mem_root;
  DBUG_ASSERT(thd->free_list == old_free_list);
  if (res)
    DBUG_RETURN(1);
  uint select_nr= select_lex->select_number;
  JOIN_TAB *curr_tab= join_tab + exec_join_tab_cnt();
  for (uint i= 0; i < aggr_tables; i++, curr_tab++)
  {
    if (select_nr == INT_MAX)
    {

      select_nr= select_lex->master_unit()->first_select()->select_number;
      curr_tab->tracker= thd->lex->explain->get_union(select_nr)->
                         get_tmptable_read_tracker();
    }
    else if (select_nr < INT_MAX)
    {
      Explain_select *tmp= thd->lex->explain->get_select(select_nr);
      if (tmp)
        curr_tab->tracker= tmp->get_using_temporary_read_tracker();
    }
  }
  DBUG_RETURN(0);
}
