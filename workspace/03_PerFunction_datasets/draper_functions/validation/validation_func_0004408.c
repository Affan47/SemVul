find_property(PlyElement *elem, const std::string &prop_name, int *index)
{
  for (size_t i = 0; i < elem->props.size(); i++)
    if (string(prop_name)==elem->props[i].name ) {
      *index = i;
      return &elem->props[i];
    }
  *index = -1;
  return (NULL);
}
