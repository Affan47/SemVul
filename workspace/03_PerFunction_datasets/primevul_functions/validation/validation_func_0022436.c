static Item **get_sargable_cond(JOIN *join, TABLE *table)
{
  Item **retval;
  if (table->pos_in_table_list->on_expr)
  {


    retval= &table->pos_in_table_list->on_expr;
  }
  else if (table->pos_in_table_list->embedding &&
           !table->pos_in_table_list->embedding->sj_on_expr)
  {


    retval= &(table->pos_in_table_list->embedding->on_expr);
  }
  else
  {

    retval= &join->conds;
  }
  return retval;
}
