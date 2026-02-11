add()
{
  ulonglong value= (ulonglong) args[0]->val_int();
  if (!args[0]->null_value)
    bits|=value;
  return 0;
}
