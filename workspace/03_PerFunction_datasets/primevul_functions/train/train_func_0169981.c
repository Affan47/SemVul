void Item::rename(char *new_name)
{


  if (!orig_name && new_name != name)
    orig_name= name;
  name= new_name;
}
