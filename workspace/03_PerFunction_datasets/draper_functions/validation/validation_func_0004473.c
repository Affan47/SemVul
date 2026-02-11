hwloc_pci_add_child_before(struct hwloc_obj *root, struct hwloc_obj *child, struct hwloc_obj *new)
{
  if (child) {
    new->prev_sibling = child->prev_sibling;
    child->prev_sibling = new;
  } else {
    new->prev_sibling = root->last_child;
    root->last_child = new;
  }

  if (new->prev_sibling)
    new->prev_sibling->next_sibling = new;
  else
    root->first_child = new;
  new->next_sibling = child;
}
