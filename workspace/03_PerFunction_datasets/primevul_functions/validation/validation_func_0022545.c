JOIN_TAB *next_explain_order_tab(JOIN* join, JOIN_TAB* tab)
{

  if (tab->last_leaf_in_bush)
    return tab->bush_root_tab;


  tab++;

  if (tab == join->join_tab + join->top_join_tab_count)
    return NULL;

  if (tab->bush_children)
    return tab->bush_children->start;

  return tab;
}
