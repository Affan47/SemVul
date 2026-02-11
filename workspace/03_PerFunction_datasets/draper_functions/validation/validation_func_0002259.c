get_default_selection()
{
  int sel=0;
  if (my_rule && type==DISJ)
    sel=my_rule->get_default_selection();
  return sel;
}
