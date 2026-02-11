want_early_inline_function_p (struct cgraph_edge *e)
{
  bool want_inline = true;
  struct cgraph_node *callee = cgraph_function_or_thunk_node (e->callee, NULL);

  if (DECL_DISREGARD_INLINE_LIMITS (callee->symbol.decl))
    ;
  else if (!DECL_DECLARED_INLINE_P (callee->symbol.decl)
	   && !flag_inline_small_functions)
    {
      e->inline_failed = CIF_FUNCTION_NOT_INLINE_CANDIDATE;
      report_inline_failed_reason (e);
      want_inline = false;
    }
  else
    {
      int growth = estimate_edge_growth (e);
      int n;

      if (growth <= 0)
	;
      else if (!cgraph_maybe_hot_edge_p (e)
	       && growth > 0)
	{
	  if (dump_file)
	    fprintf (dump_file, "  will not early inline: %s/%i->%s/%i, "
		     "call is cold and code would grow by %i\n",
		     xstrdup (cgraph_node_name (e->caller)), e->caller->uid,
		     xstrdup (cgraph_node_name (callee)), callee->uid,
		     growth);
	  want_inline = false;
	}
      else if (growth > PARAM_VALUE (PARAM_EARLY_INLINING_INSNS))
	{
	  if (dump_file)
	    fprintf (dump_file, "  will not early inline: %s/%i->%s/%i, "
		     "growth %i exceeds --param early-inlining-insns\n",
		     xstrdup (cgraph_node_name (e->caller)), e->caller->uid,
		     xstrdup (cgraph_node_name (callee)), callee->uid,
		     growth);
	  want_inline = false;
	}
      else if ((n = num_calls (callee)) != 0
	       && growth * (n + 1) > PARAM_VALUE (PARAM_EARLY_INLINING_INSNS))
	{
	  if (dump_file)
	    fprintf (dump_file, "  will not early inline: %s/%i->%s/%i, "
		     "growth %i exceeds --param early-inlining-insns "
		     "divided by number of calls\n",
		     xstrdup (cgraph_node_name (e->caller)), e->caller->uid,
		     xstrdup (cgraph_node_name (callee)), callee->uid,
		     growth);
	  want_inline = false;
	}
    }
  return want_inline;
}
