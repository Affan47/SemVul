h_remove (struct h_node **table, void *data)
{
  struct h_node *node = (struct h_node *) data - 1;
  unsigned int hv;
  struct h_node *p;

  assert (table != NULL && node != NULL);

  hv = hashi (node->name, strlen (node->name));
  if (table[hv] == node)
    table[hv] = node->next;
  else
    for (p = table[hv]; p != NULL; p = p->next)
      if (p->next == node)
        {
	  p->next = node->next;
	  node->next = NULL;
	  break;
	}
  free (node->name);
  free (node);
}
