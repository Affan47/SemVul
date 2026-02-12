int init_ftfuncs(THD *thd, SELECT_LEX *select_lex, bool no_order)
{
  if (select_lex->ftfunc_list->elements)
  {
    List_iterator<Item_func_match> li(*(select_lex->ftfunc_list));
    Item_func_match *ifm;

    while ((ifm=li++))
      if (unlikely(!ifm->is_fixed()))


        li.remove();
      else if (ifm->init_search(thd, no_order))
	return 1;
  }
  return 0;
}
