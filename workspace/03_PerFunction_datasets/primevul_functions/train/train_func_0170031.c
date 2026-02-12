bool Item_cache_str::cache_value()
{
  if (!example)
    return FALSE;
  value_cached= TRUE;
  value_buff.set(buffer, sizeof(buffer), example->collation.collation);
  value= example->str_result(&value_buff);
  if ((null_value= example->null_value))
    value= 0;
  else if (value != &value_buff)
  {


    value_buff.copy(*value);
    value= &value_buff;
  }
  return TRUE;
}
