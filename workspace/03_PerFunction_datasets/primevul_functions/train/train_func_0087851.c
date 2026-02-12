count_callers (cgraph_node *node, void *data)
{
  int *caller_count = (int *) data;

  for (cgraph_edge *cs = node->callers; cs; cs = cs->next_caller)


    if (!cs->caller->thunk.thunk_p || !cs->caller->local)
      ++*caller_count;
  return false;
}
