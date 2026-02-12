String *Item_copy_string::val_str(String *str)
{

  if (null_value)
    return (String*) 0;
  return &str_value;
}
