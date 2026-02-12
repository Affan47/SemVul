static JOIN_TAB *next_breadth_first_tab(JOIN_TAB *first_top_tab,
                                        uint n_top_tabs_count, JOIN_TAB *tab)
{
  n_top_tabs_count += tab->join->aggr_tables;
  if (!tab->bush_root_tab)
  {

    tab++;
    if (tab < first_top_tab + n_top_tabs_count)
      return tab;


    tab= first_top_tab;
  }
  else
  {

    if (!tab->last_leaf_in_bush)
    {

      return ++tab;
    }
    else
    {


      tab= tab->bush_root_tab + 1;
    }
  }


  for (; tab < first_top_tab + n_top_tabs_count; tab++)
  {
    if (tab->bush_children)
      return tab->bush_children->start;
  }
  return NULL;
}
