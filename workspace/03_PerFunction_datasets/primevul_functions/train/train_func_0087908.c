determine_versionability (struct cgraph_node *node,
			  class ipa_node_params *info)
{
  const char *reason = NULL;


  if (node->alias || node->thunk.thunk_p)
    reason = "alias or thunk";
  else if (!node->versionable)
    reason = "not a tree_versionable_function";
  else if (node->get_availability () <= AVAIL_INTERPOSABLE)
    reason = "insufficient body availability";
  else if (!opt_for_fn (node->decl, optimize)
	   || !opt_for_fn (node->decl, flag_ipa_cp))
    reason = "non-optimized function";
  else if (lookup_attribute ("omp declare simd", DECL_ATTRIBUTES (node->decl)))
    {


      reason = "function has SIMD clones";
    }
  else if (lookup_attribute ("target_clones", DECL_ATTRIBUTES (node->decl)))
    {


      reason = "function target_clones attribute";
    }


  else if (node->comdat_local_p ())
    reason = "comdat-local function";
  else if (node->calls_comdat_local)
    {


      reason = "calls comdat-local function";
    }


  if (DECL_EXTERNAL (node->decl))
    for (cgraph_edge *edge = node->callees; !reason && edge;
	 edge = edge->next_callee)
      if (fndecl_built_in_p (edge->callee->decl, BUILT_IN_NORMAL))
        {
	  if (DECL_FUNCTION_CODE (edge->callee->decl) == BUILT_IN_VA_ARG_PACK)
	    reason = "external function which calls va_arg_pack";
	  if (DECL_FUNCTION_CODE (edge->callee->decl)
	      == BUILT_IN_VA_ARG_PACK_LEN)
	    reason = "external function which calls va_arg_pack_len";
        }

  if (reason && dump_file && !node->alias && !node->thunk.thunk_p)
    fprintf (dump_file, "Function %s is not versionable, reason: %s.\n",
	     node->dump_name (), reason);

  info->versionable = (reason == NULL);
}
