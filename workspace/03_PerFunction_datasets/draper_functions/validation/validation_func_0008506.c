ply_get_other_properties(
  PlyFile *plyfile,
  char *elem_name,
  int offset
)
{
  int i;
  PlyElement *elem;
  PlyOtherProp *other;
  PlyProperty *prop;
  int nprops;


  elem = find_element (plyfile, elem_name);
  if (elem == NULL) {
    fprintf (stderr, "ply_get_other_properties: Can't find element '%s'\n",
             elem_name);
    return (NULL);
  }


  plyfile->which_elem = elem;


  elem->other_offset = offset;


  setup_other_props (elem);


  other = (PlyOtherProp *) myalloc (sizeof (PlyOtherProp));
  other->name = strdup (elem_name);
#if 0
  if (elem->other_offset == NO_OTHER_PROPS) {
    other->size = 0;
    other->props = NULL;
    other->nprops = 0;
    return (other);
  }
#endif
  other->size = elem->other_size;
  other->props = (PlyProperty **) myalloc (sizeof(PlyProperty) * elem->nprops);


  nprops = 0;
  for (i = 0; i < elem->nprops; i++) {
    if (elem->store_prop[i])
      continue;
    prop = (PlyProperty *) myalloc (sizeof (PlyProperty));
    copy_property (prop, elem->props[i]);
    other->props[nprops] = prop;
    nprops++;
  }
  other->nprops = nprops;

#if 1

  if (other->nprops == 0) {
    elem->other_offset = NO_OTHER_PROPS;
  }
#endif


  return (other);
}
