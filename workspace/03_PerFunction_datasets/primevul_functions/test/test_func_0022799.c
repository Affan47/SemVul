TABLE_LIST *LEX::unlink_first_table(bool *link_to_local)
{
  TABLE_LIST *first;
  if ((first= query_tables))
  {


    if ((query_tables= query_tables->next_global))
      query_tables->prev_global= &query_tables;
    else
      query_tables_last= &query_tables;
    first->next_global= 0;


    if ((*link_to_local= MY_TEST(select_lex.table_list.first)))
    {
      select_lex.context.table_list=
        select_lex.context.first_name_resolution_table= first->next_local;
      select_lex.table_list.first= first->next_local;
      select_lex.table_list.elements--;
      first->next_local= 0;


      first_lists_tables_same();
    }
  }
  return first;
}
