assign_temp (type_or_decl, keep, memory_required, dont_promote)
     tree type_or_decl;
     int keep;
     int memory_required;
     int dont_promote ATTRIBUTE_UNUSED;
{
  tree type, decl;
  enum machine_mode mode;
#ifndef PROMOTE_FOR_CALL_ONLY
  int unsignedp;
#endif

  if (DECL_P (type_or_decl))
    decl = type_or_decl, type = TREE_TYPE (decl);
  else
    decl = NULL, type = type_or_decl;

  mode = TYPE_MODE (type);
#ifndef PROMOTE_FOR_CALL_ONLY
  unsignedp = TREE_UNSIGNED (type);
#endif

  if (mode == BLKmode || memory_required)
    {
      HOST_WIDE_INT size = int_size_in_bytes (type);
      rtx tmp;


      if (size == 0)
	size = 1;


      if (size == -1 && TREE_CODE (type) == ARRAY_TYPE
	  && TYPE_ARRAY_MAX_SIZE (type) != NULL_TREE
	  && host_integerp (TYPE_ARRAY_MAX_SIZE (type), 1))
	size = tree_low_cst (TYPE_ARRAY_MAX_SIZE (type), 1);


      if (decl && size == -1
	  && TREE_CODE (TYPE_SIZE_UNIT (type)) == INTEGER_CST)
	{
	  error_with_decl (decl, "size of variable `%s' is too large");
	  size = 1;
	}

      tmp = assign_stack_temp_for_type (mode, size, keep, type);
      return tmp;
    }

#ifndef PROMOTE_FOR_CALL_ONLY
  if (! dont_promote)
    mode = promote_mode (type, mode, &unsignedp, 0);
#endif

  return gen_reg_rtx (mode);
}
