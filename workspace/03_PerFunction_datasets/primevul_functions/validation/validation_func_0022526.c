optimize_cond(JOIN *join, COND *conds,
              List<TABLE_LIST> *join_list, bool ignore_on_conds,
              Item::cond_result *cond_value, COND_EQUAL **cond_equal,
              int flags)
{
  THD *thd= join->thd;
  DBUG_ENTER("optimize_cond");

  if (!conds)
  {
    *cond_value= Item::COND_TRUE;
    if (!ignore_on_conds)
      build_equal_items(join, NULL, NULL, join_list, ignore_on_conds,
                        cond_equal);
  }
  else
  {


    DBUG_EXECUTE("where", print_where(conds, "original", QT_ORDINARY););
    conds= build_equal_items(join, conds, NULL, join_list,
                             ignore_on_conds, cond_equal,
                             MY_TEST(flags & OPT_LINK_EQUAL_FIELDS));
    DBUG_EXECUTE("where",print_where(conds,"after equal_items", QT_ORDINARY););


    propagate_cond_constants(thd, (I_List<COND_CMP> *) 0, conds, conds);


    DBUG_EXECUTE("where",print_where(conds,"after const change", QT_ORDINARY););
    conds= conds->remove_eq_conds(thd, cond_value, true);
    if (conds && conds->type() == Item::COND_ITEM &&
        ((Item_cond*) conds)->functype() == Item_func::COND_AND_FUNC)
      *cond_equal= &((Item_cond_and*) conds)->m_cond_equal;
    DBUG_EXECUTE("info",print_where(conds,"after remove", QT_ORDINARY););
  }
  DBUG_RETURN(conds);
}
