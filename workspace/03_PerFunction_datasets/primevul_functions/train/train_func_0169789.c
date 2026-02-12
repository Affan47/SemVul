Item::Type Item_name_const::type() const
{


  if (!valid_args)
    return NULL_ITEM;
  Item::Type value_type= value_item->type();
  if (value_type == FUNC_ITEM)
  {


    DBUG_ASSERT(((Item_func *) value_item)->functype() ==
                Item_func::NEG_FUNC ||
                ((Item_func *) value_item)->functype() ==
                Item_func::COLLATE_FUNC);
    return ((Item_func *) value_item)->key_item()->type();
  }
  return value_type;
}
