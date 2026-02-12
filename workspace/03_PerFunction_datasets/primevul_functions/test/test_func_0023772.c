void cmp_item_decimal::store_value(Item *item)
{
  my_decimal *val= item->val_decimal(&value);

  if (val && val != &value)
    my_decimal2decimal(val, &value);
  m_null_value= item->null_value;
}
