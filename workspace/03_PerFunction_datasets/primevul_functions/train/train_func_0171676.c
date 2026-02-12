static void select_describe(JOIN *join, bool need_tmp_table, bool need_order,
			    bool distinct,const char *message)
{
  THD *thd=join->thd;
  select_result *result=join->result;
  DBUG_ENTER("select_describe");

  if (join->select_lex->pushdown_select)
  {


    DBUG_VOID_RETURN;
  }


  for (SELECT_LEX_UNIT *unit= join->select_lex->first_inner_unit();
       unit;
       unit= unit->next_unit())
  {


    if (unit->item && !unit->item->is_fixed())
    {
      Item *ref= unit->item;
      if (unit->item->fix_fields(thd, &ref))
        DBUG_VOID_RETURN;
      DBUG_ASSERT(ref == unit->item);
    }


    if (!(unit->item && unit->item->eliminated) &&
        !(unit->derived && unit->derived->merged_for_insert) &&
        (!unit->with_element ||
          (unit->derived &&
           unit->derived->derived_result &&
           !unit->with_element->is_hanging_recursive())))
    {
      if (mysql_explain_union(thd, unit, result))
        DBUG_VOID_RETURN;
    }
  }
  DBUG_VOID_RETURN;
}
