next_runtime_01_initialize (void)
{
  tree type;

#ifdef OBJCPLUS


  if (!global_options_set.x_flag_objc_call_cxx_cdtors)
    global_options.x_flag_objc_call_cxx_cdtors = 1;
#endif


  next_runtime_abi_01_init_metadata_attributes ();

  if (flag_objc_abi >= 1)
    objc_prop_list_ptr = build_pointer_type (xref_tag (RECORD_TYPE,
					     get_identifier ("_prop_list_t")));


  objc_selector_type = build_pointer_type (xref_tag (RECORD_TYPE,
					   get_identifier (TAG_SELECTOR)));

  build_v1_class_template ();
  build_super_template ();
  build_v1_protocol_template ();
  build_v1_category_template ();


  type = build_varargs_function_type_list (objc_object_type,
					   objc_object_type,
					   objc_selector_type,
					   NULL_TREE);

  umsg_decl = add_builtin_function (TAG_MSGSEND,
				    type, 0, NOT_BUILT_IN,
				    NULL, NULL_TREE);

  umsg_nonnil_decl = add_builtin_function (TAG_MSGSEND_NONNIL,
					   type, 0, NOT_BUILT_IN,
					    NULL, NULL_TREE);

  umsg_stret_decl = add_builtin_function (TAG_MSGSEND_STRET,
					  type, 0, NOT_BUILT_IN,
					  NULL, NULL_TREE);

  umsg_nonnil_stret_decl = add_builtin_function (TAG_MSGSEND_NONNIL_STRET,
						 type, 0, NOT_BUILT_IN,
						 NULL, NULL_TREE);


  TREE_NOTHROW (umsg_decl) = 0;
  TREE_NOTHROW (umsg_nonnil_decl) = 0;
  TREE_NOTHROW (umsg_stret_decl) = 0;
  TREE_NOTHROW (umsg_nonnil_stret_decl) = 0;


#ifdef OFFS_MSGSEND_FAST
  umsg_fast_decl = add_builtin_function (TAG_MSGSEND_FAST,
					     type, 0, NOT_BUILT_IN,
					     NULL, NULL_TREE);
  TREE_NOTHROW (umsg_fast_decl) = 0;
  DECL_ATTRIBUTES (umsg_fast_decl)
	= tree_cons (get_identifier ("hard_coded_address"),
		     build_int_cst (NULL_TREE, OFFS_MSGSEND_FAST),
		     NULL_TREE);
#else

  umsg_fast_decl = umsg_decl;
#endif


  type = build_varargs_function_type_list (objc_object_type,
                                            objc_super_type,
                                            objc_selector_type,
                                            NULL_TREE);
  umsg_super_decl = add_builtin_function (TAG_MSGSENDSUPER,
					      type, 0, NOT_BUILT_IN,
					      NULL, NULL_TREE);
  umsg_super_stret_decl = add_builtin_function (TAG_MSGSENDSUPER_STRET,
						    type, 0, NOT_BUILT_IN, 0,
						    NULL_TREE);
  TREE_NOTHROW (umsg_super_decl) = 0;
  TREE_NOTHROW (umsg_super_stret_decl) = 0;

  type = build_function_type_list (objc_object_type,
                                   const_string_type_node,
                                   NULL_TREE);


  objc_get_class_decl
    = add_builtin_function (TAG_GETCLASS, type, 0, NOT_BUILT_IN,
			    NULL, NULL_TREE);


  objc_get_meta_class_decl
    = add_builtin_function (TAG_GETMETACLASS, type, 0, NOT_BUILT_IN, NULL, NULL_TREE);


  type = build_function_type_list (void_type_node,
				   ptr_type_node,
				   const_ptr_type_node,
				   ptrdiff_type_node,
				   boolean_type_node,
				   boolean_type_node,
				   NULL_TREE);


  objc_copyStruct_decl = add_builtin_function ("objc_copyStruct",
						   type, 0, NOT_BUILT_IN,
						   NULL, NULL_TREE);
  TREE_NOTHROW (objc_copyStruct_decl) = 0;
  objc_getPropertyStruct_decl = NULL_TREE;
  objc_setPropertyStruct_decl = NULL_TREE;

  build_next_objc_exception_stuff ();
  if (flag_objc_exceptions && !flag_objc_sjlj_exceptions)
    using_eh_for_cleanups ();
  lang_hooks.eh_runtime_type = objc_eh_runtime_type;
  lang_hooks.eh_personality = objc_eh_personality;
}
