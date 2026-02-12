Item* Item_ref::transform(Item_transformer transformer, uchar *arg)
{
  DBUG_ASSERT(!current_thd->stmt_arena->is_stmt_prepare());
  DBUG_ASSERT((*ref) != NULL);


  Item *new_item= (*ref)->transform(transformer, arg);
  if (!new_item)
    return NULL;


  if (*ref != new_item)
    current_thd->change_item_tree(ref, new_item);


  return (this->*transformer)(arg);
}
