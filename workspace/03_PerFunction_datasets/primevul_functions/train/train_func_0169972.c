Item* Item_ref::compile(Item_analyzer analyzer, uchar **arg_p,
                        Item_transformer transformer, uchar *arg_t)
{

  if (!(this->*analyzer)(arg_p))
    return NULL;


  DBUG_ASSERT((*ref) != NULL);
  if (*arg_p)
  {
    uchar *arg_v= *arg_p;
    Item *new_item= (*ref)->compile(analyzer, &arg_v, transformer, arg_t);
    if (new_item && *ref != new_item)
      current_thd->change_item_tree(ref, new_item);
  }


  return (this->*transformer)(arg_t);
}
