ipcp_print_call_profile_counts (FILE * f)
{
  struct cgraph_node *node;
  struct cgraph_edge *cs;

  for (node = cgraph_nodes; node; node = node->next)
    {
      for (cs = node->callees; cs; cs = cs->next_callee)
	{
	  fprintf (f, "%s -> %s ", cgraph_node_name (cs->caller),
		   cgraph_node_name (cs->callee));
	  fprintf (f, "count is  " HOST_WIDE_INT_PRINT_DEC "  \n",
		   (HOST_WIDE_INT) cs->count);
	}
    }
}
