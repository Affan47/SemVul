Item *Item_cond::propagate_equal_fields(THD *thd,
                                        const Context &ctx,
                                        COND_EQUAL *cond)
{
  DBUG_ASSERT(!thd->stmt_arena->is_stmt_prepare());
  DBUG_ASSERT(arg_count == 0);
  List_iterator<Item> li(list);
  while (li++)
  {


    propagate_and_change_item_tree(thd, li.ref(), cond, Context_boolean());
  }
  return this;
}
