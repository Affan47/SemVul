register_attribute(char *name, Attribute_type type)
{
  int id = -1;
  if (Next_attribute_name == MAX_ATTRIBUTE_NAMES)
    fatal_error("register_attribute: too many attribute names");
  else {
    id = str_to_sn(name, 1);
    id = Next_attribute_name++;
    Attribute_names[id].name = new_str_copy(name);
    Attribute_names[id].type = type;
  }
  return id;
}
