void LEX::cleanup_after_one_table_open()
{


  if (all_selects_list != &select_lex)
  {
    derived_tables= 0;
    select_lex.exclude_from_table_unique_test= false;

    for (SELECT_LEX_UNIT *un= select_lex.first_inner_unit();
         un;
         un= un->next_unit())
      un->cleanup();

    all_selects_list= &select_lex;

    select_lex.cut_subtree();
  }
}
