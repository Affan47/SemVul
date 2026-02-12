void JOIN::cleanup(bool full)
{
  DBUG_ENTER("JOIN::cleanup");
  DBUG_PRINT("enter", ("full %u", (uint) full));

  if (full)
    have_query_plan= QEP_DELETED;

  if (original_join_tab)
  {

    join_tab= original_join_tab;
    original_join_tab= 0;
    table_count= original_table_count;
  }

  if (join_tab)
  {
    JOIN_TAB *tab;

    if (full)
    {


      if (top_join_tab_count && tables_list)
      {
        for (tab= first_breadth_first_tab(); tab;
             tab= next_breadth_first_tab(first_breadth_first_tab(),
                                         top_join_tab_count, tab))
        {
          tab->cleanup();
          delete tab->filesort_result;
          tab->filesort_result= NULL;
        }
      }
      cleaned= true;

      {
        JOIN_TAB *curr_tab= join_tab + exec_join_tab_cnt();
        for (uint i= 0; i < aggr_tables; i++, curr_tab++)
        {
          if (curr_tab->aggr)
          {
            free_tmp_table(thd, curr_tab->table);
            curr_tab->table= NULL;
            delete curr_tab->tmp_table_param;
            curr_tab->tmp_table_param= NULL;
            curr_tab->aggr= NULL;

            delete curr_tab->filesort_result;
            curr_tab->filesort_result= NULL;
          }
        }
        aggr_tables= 0;
      }
    }
    else
    {
      for (tab= first_linear_tab(this, WITH_BUSH_ROOTS, WITH_CONST_TABLES); tab;
           tab= next_linear_tab(this, tab, WITH_BUSH_ROOTS))
      {
        tab->partial_cleanup();
      }
    }
  }
  if (full)
  {
    cleanup_empty_jtbm_semi_joins(this, join_list);


    group_fields.delete_elements();


    tmp_table_param.copy_funcs.empty();


    tmp_table_param.cleanup();

    delete pushdown_query;
    pushdown_query= 0;

    if (!join_tab)
    {
      List_iterator<TABLE_LIST> li(*join_list);
      TABLE_LIST *table_ref;
      while ((table_ref= li++))
      {
        if (table_ref->table &&
            table_ref->jtbm_subselect &&
            table_ref->jtbm_subselect->is_jtbm_const_tab)
        {
          free_tmp_table(thd, table_ref->table);
          table_ref->table= NULL;
        }
      }
    }
  }

  if (current_ref_ptrs != items0)
  {
    set_items_ref_array(items0);
    set_group_rpa= false;
  }
  DBUG_VOID_RETURN;
}
