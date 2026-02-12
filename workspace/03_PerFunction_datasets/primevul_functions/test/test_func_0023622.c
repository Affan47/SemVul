void in_decimal::set(uint pos, Item *item)
{

  my_decimal *dec= ((my_decimal *)base) + pos;
  dec->len= DECIMAL_BUFF_LENGTH;
  dec->fix_buffer_pointer();
  my_decimal *res= item->val_decimal(dec);

  if (!item->null_value && res != dec)
    my_decimal2decimal(res, dec);
}
