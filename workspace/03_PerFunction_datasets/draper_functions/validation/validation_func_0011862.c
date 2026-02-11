assemble_alias (tree decl, tree target)
{
  tree target_decl;
  bool is_weakref = false;

  if (lookup_attribute ("weakref", DECL_ATTRIBUTES (decl)))
    {
      tree alias = DECL_ASSEMBLER_NAME (decl);

      is_weakref = true;

      ultimate_transparent_alias_target (&target);

      if (alias == target)
	error ("weakref %q+D ultimately targets itself", decl);
      else
	{
#ifndef ASM_OUTPUT_WEAKREF
	  IDENTIFIER_TRANSPARENT_ALIAS (alias) = 1;
	  TREE_CHAIN (alias) = target;
#endif
	}
      if (TREE_PUBLIC (decl))
	error ("weakref %q+D must have static linkage", decl);
    }
  else
    {
#if !defined (ASM_OUTPUT_DEF)
# if !defined(ASM_OUTPUT_WEAK_ALIAS) && !defined (ASM_WEAKEN_DECL)
      error_at (DECL_SOURCE_LOCATION (decl),
		"alias definitions not supported in this configuration");
      return;
# else
      if (!DECL_WEAK (decl))
	{
	  if (lookup_attribute ("ifunc", DECL_ATTRIBUTES (decl)))
	    error_at (DECL_SOURCE_LOCATION (decl),
		      "ifunc is not supported in this configuration");
	  else
	    error_at (DECL_SOURCE_LOCATION (decl),
		      "only weak aliases are supported in this configuration");
	  return;
	}
# endif
#endif
    }
  TREE_USED (decl) = 1;


  if (! is_weakref)
    DECL_EXTERNAL (decl) = 0;


  if (TREE_CODE (decl) == FUNCTION_DECL)
    cgraph_node (decl)->alias = true;
  else
    varpool_node (decl)->alias = true;


  if (cgraph_global_info_ready)
    target_decl = find_decl_and_mark_needed (decl, target);
  else
    target_decl= NULL;
  if (target_decl && TREE_ASM_WRITTEN (target_decl))
    do_assemble_alias (decl, target);
  else
    {
      alias_pair *p = VEC_safe_push (alias_pair, gc, alias_pairs, NULL);
      p->decl = decl;
      p->target = target;
      p->emitted_diags = ALIAS_DIAG_NONE;
    }
}
