propagate_constants_topo (class ipa_topo_info *topo)
{
  int i;

  for (i = topo->nnodes - 1; i >= 0; i--)
    {
      unsigned j;
      struct cgraph_node *v, *node = topo->order[i];
      vec<cgraph_node *> cycle_nodes = ipa_get_nodes_in_cycle (node);


      FOR_EACH_VEC_ELT (cycle_nodes, j, v)
	if (v->has_gimple_body_p ())
	  {
	    if (opt_for_fn (v->decl, flag_ipa_cp)
		&& opt_for_fn (v->decl, optimize))
	      push_node_to_stack (topo, v);


	    else
	      {
		for (cgraph_edge *cs = v->callees; cs; cs = cs->next_callee)
	           propagate_constants_across_call (cs);
	      }
	  }

      v = pop_node_from_stack (topo);
      while (v)
	{
	  struct cgraph_edge *cs;
	  class ipa_node_params *info = NULL;
	  bool self_scc = true;

	  for (cs = v->callees; cs; cs = cs->next_callee)
	    if (ipa_edge_within_scc (cs))
	      {
		cgraph_node *callee = cs->callee->function_symbol ();

		if (v != callee)
		  self_scc = false;

		if (!info)
		  {
		    info = IPA_NODE_REF (v);
		    info->node_within_scc = true;
		  }

		if (propagate_constants_across_call (cs))
		  push_node_to_stack (topo, callee);
	      }

	  if (info)
	    info->node_is_self_scc = self_scc;

	  v = pop_node_from_stack (topo);
	}


      FOR_EACH_VEC_ELT (cycle_nodes, j, v)
	if (v->has_gimple_body_p ()
	    && opt_for_fn (v->decl, flag_ipa_cp)
	    && opt_for_fn (v->decl, optimize))
	  {
	    struct cgraph_edge *cs;

	    estimate_local_effects (v);
	    add_all_node_vals_to_toposort (v, topo);
	    for (cs = v->callees; cs; cs = cs->next_callee)
	      if (!ipa_edge_within_scc (cs))
		propagate_constants_across_call (cs);
	  }
      cycle_nodes.release ();
    }
}
