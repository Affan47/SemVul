detect_type_change_1 (tree arg, tree base, tree comp_type, gimple call,
		      struct ipa_jump_func *jfunc, HOST_WIDE_INT offset)
{
  struct type_change_info tci;
  ao_ref ao;

  gcc_checking_assert (DECL_P (arg)
		       || TREE_CODE (arg) == MEM_REF
		       || handled_component_p (arg));


  if (!flag_devirtualize || !gimple_vuse (call))
    return false;

  ao_ref_init (&ao, arg);
  ao.base = base;
  ao.offset = offset;
  ao.size = POINTER_SIZE;
  ao.max_size = ao.size;

  tci.offset = offset;
  tci.object = get_base_address (arg);
  tci.known_current_type = NULL_TREE;
  tci.type_maybe_changed = false;
  tci.multiple_types_encountered = false;

  walk_aliased_vdefs (&ao, gimple_vuse (call), check_stmt_for_type_change,
		      &tci, NULL);
  if (!tci.type_maybe_changed)
    return false;

  if (!tci.known_current_type
      || tci.multiple_types_encountered
      || offset != 0)
    jfunc->type = IPA_JF_UNKNOWN;
  else
    ipa_set_jf_known_type (jfunc, 0, tci.known_current_type, comp_type);

  return true;
}
