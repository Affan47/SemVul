JOIN_TAB *next_linear_tab(JOIN* join, JOIN_TAB* tab,
                          enum enum_with_bush_roots include_bush_roots)
{
  if (include_bush_roots == WITH_BUSH_ROOTS && tab->bush_children)
  {

    return tab->bush_children->start;
  }

  DBUG_ASSERT(!tab->last_leaf_in_bush || tab->bush_root_tab);

  if (tab->bush_root_tab)
  {

    if (!tab->last_leaf_in_bush)
      return tab+1;

    tab= tab->bush_root_tab;
  }


  if (++tab >= join->join_tab + join->exec_join_tab_cnt() + join->aggr_tables)
    return NULL;

  if (include_bush_roots == WITHOUT_BUSH_ROOTS && tab->bush_children)
  {

    tab= tab->bush_children->start;
  }
  return tab;
}
