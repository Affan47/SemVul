COND *Item_func::build_equal_items(THD *thd, COND_EQUAL *inherited,
                                   bool link_item_fields,
                                   COND_EQUAL **cond_equal_ref)
{


  COND *cond= propagate_equal_fields(thd, Context_boolean(), inherited);
  cond->update_used_tables();
  DBUG_ASSERT(cond == this);
  DBUG_ASSERT(!cond_equal_ref || !cond_equal_ref[0]);
  return cond;
}
