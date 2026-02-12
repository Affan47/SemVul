bool Item_int::eq(const Item *arg, bool binary_cmp) const
{

  if (arg->basic_const_item() && arg->type() == type())
  {


    Item *item= (Item*) arg;
    return (item->val_int() == value &&
            ((longlong) value >= 0 ||
             (item->unsigned_flag == unsigned_flag)));
  }
  return FALSE;
}
