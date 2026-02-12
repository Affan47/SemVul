void Item_subselect::recalc_used_tables(st_select_lex *new_parent,
                                        bool after_pullout)
{
  List_iterator_fast<Ref_to_outside> it(upper_refs);
  Ref_to_outside *upper;
  DBUG_ENTER("recalc_used_tables");

  used_tables_cache= 0;
  while ((upper= it++))
  {
    bool found= FALSE;


    for (st_select_lex *sel= upper->select; sel; sel= sel->outer_select())
    {


      if (sel == new_parent)
      {
        found= TRUE;


        if (upper->item)
        {

          Field_fixer fixer;
          fixer.used_tables= 0;
          fixer.new_parent= new_parent;
          upper->item->walk(&Item::enumerate_field_refs_processor, 0, &fixer);
          used_tables_cache |= fixer.used_tables;
          upper->item->walk(&Item::update_table_bitmaps_processor, FALSE, NULL);


        }
      }
    }
    if (!found)
      used_tables_cache|= OUTER_REF_TABLE_BIT;
  }


  DBUG_PRINT("exit", ("used_tables_cache: %llx", used_tables_cache));
  DBUG_VOID_RETURN;
}
