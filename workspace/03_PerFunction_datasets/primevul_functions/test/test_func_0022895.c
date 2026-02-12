void st_select_lex::set_explain_type(bool on_the_fly)
{
  bool is_primary= FALSE;
  if (next_select())
    is_primary= TRUE;

  if (!is_primary && first_inner_unit())
  {


    for (SELECT_LEX_UNIT *un= first_inner_unit(); un; un= un->next_unit())
    {
      if ((!un->derived || un->derived->is_materialized_derived()))
      {
        is_primary= TRUE;
        break;
      }
    }
  }

  if (on_the_fly && !is_primary && have_merged_subqueries)
    is_primary= TRUE;

  SELECT_LEX *first= master_unit()->first_select();

  uint8 is_uncacheable= (uncacheable & ~UNCACHEABLE_EXPLAIN);

  bool using_materialization= FALSE;
  Item_subselect *parent_item;
  if ((parent_item= master_unit()->item) &&
      parent_item->substype() == Item_subselect::IN_SUBS)
  {
    Item_in_subselect *in_subs= (Item_in_subselect*)parent_item;


    if (in_subs->test_strategy(SUBS_MATERIALIZATION))
      using_materialization= TRUE;
  }

  if (&master_unit()->thd->lex->select_lex == this)
  {
     type= is_primary ? "PRIMARY" : "SIMPLE";
  }
  else
  {
    if (this == first)
    {

      if (linkage == DERIVED_TABLE_TYPE)
        type= "DERIVED";
      else if (using_materialization)
        type= "MATERIALIZED";
      else
      {
         if (is_uncacheable & UNCACHEABLE_DEPENDENT)
           type= "DEPENDENT SUBQUERY";
         else
         {
           type= is_uncacheable? "UNCACHEABLE SUBQUERY" :
                                 "SUBQUERY";
         }
      }
    }
    else
    {

      if (is_uncacheable & UNCACHEABLE_DEPENDENT)
        type= "DEPENDENT UNION";
      else if (using_materialization)
        type= "MATERIALIZED UNION";
      else
      {
        type= is_uncacheable ? "UNCACHEABLE UNION": "UNION";
        if (this == master_unit()->fake_select_lex)
          type= "UNION RESULT";


        if (join)
        {
          bool uses_cte= false;
          for (JOIN_TAB *tab= first_linear_tab(join, WITHOUT_BUSH_ROOTS,
                                                     WITH_CONST_TABLES);
               tab;
               tab= next_linear_tab(join, tab, WITHOUT_BUSH_ROOTS))
          {


            if (!(tab->table && tab->table->pos_in_table_list))
	      continue;
            TABLE_LIST *tbl= tab->table->pos_in_table_list;
            if (tbl->with && tbl->with->is_recursive &&
                tbl->is_with_table_recursive_reference())
            {
              uses_cte= true;
              break;
            }
          }
          if (uses_cte)
            type= "RECURSIVE UNION";
        }
      }
    }
  }

  if (!on_the_fly)
    options|= SELECT_DESCRIBE;
}
