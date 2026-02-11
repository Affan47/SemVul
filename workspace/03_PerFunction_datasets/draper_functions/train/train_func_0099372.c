merge_useless_child(hwloc_topology_t topology, hwloc_obj_t *pparent)
{
  hwloc_obj_t parent = *pparent, child, *pchild, ios;
  int replacechild = 0, replaceparent = 0;

  for_each_child_safe(child, parent, pchild)
    merge_useless_child(topology, pchild);

  child = parent->first_child;
  if (!child)

    return;

  if (child->next_sibling && !hwloc_obj_type_is_io(child->next_sibling->type))

    return;


  ios = child->next_sibling;
  child->next_sibling = NULL;


  if (topology->ignored_types[parent->type] == HWLOC_IGNORE_TYPE_KEEP_STRUCTURE) {
    if (parent->type != HWLOC_OBJ_GROUP || can_merge_group(topology, parent))

      replaceparent = 1;
  }
  if (topology->ignored_types[child->type] == HWLOC_IGNORE_TYPE_KEEP_STRUCTURE) {
    if (child->type != HWLOC_OBJ_GROUP || can_merge_group(topology, child))

      replacechild = 1;
  }


  if (replaceparent && replacechild) {

    if (obj_type_priority[parent->type] > obj_type_priority[child->type])
      replaceparent = 0;
    else
      replacechild = 0;
  }

  if (replaceparent) {

    hwloc_debug("%s", "\nIgnoring parent ");
    print_object(topology, 0, parent);
    if (parent == topology->levels[0][0]) {
      child->parent = NULL;
      child->depth = 0;
    }
    *pparent = child;
    child->next_sibling = parent->next_sibling;
    hwloc_free_unlinked_object(parent);

  } else if (replacechild) {

    hwloc_debug("%s", "\nIgnoring child ");
    print_object(topology, 0, child);
    parent->first_child = child->first_child;
    hwloc_free_unlinked_object(child);
  }

  if (ios) {

    pchild = &((*pparent)->first_child);
    while (*pchild)
      pchild = &((*pchild)->next_sibling);
    *pchild = ios;
  }
}
