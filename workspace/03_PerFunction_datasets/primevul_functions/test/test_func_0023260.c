bool Item_func_truth::val_bool()
{
  bool val= args[0]->val_bool();
  if (args[0]->null_value)
  {


    return (! affirmative);
  }

  if (affirmative)
  {

    return (val == value);
  }


  return (val != value);
}
