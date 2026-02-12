bool Item_float::eq(const Item *arg, bool binary_cmp) const
{
  if (arg->basic_const_item() && arg->type() == type())
  {


    Item *item= (Item*) arg;
    return item->val_real() == value;
  }
  return FALSE;
}
