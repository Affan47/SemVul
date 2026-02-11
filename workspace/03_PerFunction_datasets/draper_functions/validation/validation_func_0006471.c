initialize_sanitizer_builtins (void)
{
  tree decl;

  if (builtin_decl_implicit_p (BUILT_IN_ASAN_INIT))
    return;

  tree BT_FN_VOID = build_function_type_list (void_type_node, NULL_TREE);
  tree BT_FN_VOID_PTR
    = build_function_type_list (void_type_node, ptr_type_node, NULL_TREE);
  tree BT_FN_VOID_PTR_PTRMODE
    = build_function_type_list (void_type_node, ptr_type_node,
				build_nonstandard_integer_type (POINTER_SIZE,
								1), NULL_TREE);
  tree BT_FN_VOID_INT
    = build_function_type_list (void_type_node, integer_type_node, NULL_TREE);
  tree BT_FN_BOOL_VPTR_PTR_IX_INT_INT[5];
  tree BT_FN_IX_CONST_VPTR_INT[5];
  tree BT_FN_IX_VPTR_IX_INT[5];
  tree BT_FN_VOID_VPTR_IX_INT[5];
  tree vptr
    = build_pointer_type (build_qualified_type (void_type_node,
						TYPE_QUAL_VOLATILE));
  tree cvptr
    = build_pointer_type (build_qualified_type (void_type_node,
						TYPE_QUAL_VOLATILE
						|TYPE_QUAL_CONST));
  tree boolt
    = lang_hooks.types.type_for_size (BOOL_TYPE_SIZE, 1);
  int i;
  for (i = 0; i < 5; i++)
    {
      tree ix = build_nonstandard_integer_type (BITS_PER_UNIT * (1 << i), 1);
      BT_FN_BOOL_VPTR_PTR_IX_INT_INT[i]
	= build_function_type_list (boolt, vptr, ptr_type_node, ix,
				    integer_type_node, integer_type_node,
				    NULL_TREE);
      BT_FN_IX_CONST_VPTR_INT[i]
	= build_function_type_list (ix, cvptr, integer_type_node, NULL_TREE);
      BT_FN_IX_VPTR_IX_INT[i]
	= build_function_type_list (ix, vptr, ix, integer_type_node,
				    NULL_TREE);
      BT_FN_VOID_VPTR_IX_INT[i]
	= build_function_type_list (void_type_node, vptr, ix,
				    integer_type_node, NULL_TREE);
    }
#define BT_FN_BOOL_VPTR_PTR_I1_INT_INT BT_FN_BOOL_VPTR_PTR_IX_INT_INT[0]
#define BT_FN_I1_CONST_VPTR_INT BT_FN_IX_CONST_VPTR_INT[0]
#define BT_FN_I1_VPTR_I1_INT BT_FN_IX_VPTR_IX_INT[0]
#define BT_FN_VOID_VPTR_I1_INT BT_FN_VOID_VPTR_IX_INT[0]
#define BT_FN_BOOL_VPTR_PTR_I2_INT_INT BT_FN_BOOL_VPTR_PTR_IX_INT_INT[1]
#define BT_FN_I2_CONST_VPTR_INT BT_FN_IX_CONST_VPTR_INT[1]
#define BT_FN_I2_VPTR_I2_INT BT_FN_IX_VPTR_IX_INT[1]
#define BT_FN_VOID_VPTR_I2_INT BT_FN_VOID_VPTR_IX_INT[1]
#define BT_FN_BOOL_VPTR_PTR_I4_INT_INT BT_FN_BOOL_VPTR_PTR_IX_INT_INT[2]
#define BT_FN_I4_CONST_VPTR_INT BT_FN_IX_CONST_VPTR_INT[2]
#define BT_FN_I4_VPTR_I4_INT BT_FN_IX_VPTR_IX_INT[2]
#define BT_FN_VOID_VPTR_I4_INT BT_FN_VOID_VPTR_IX_INT[2]
#define BT_FN_BOOL_VPTR_PTR_I8_INT_INT BT_FN_BOOL_VPTR_PTR_IX_INT_INT[3]
#define BT_FN_I8_CONST_VPTR_INT BT_FN_IX_CONST_VPTR_INT[3]
#define BT_FN_I8_VPTR_I8_INT BT_FN_IX_VPTR_IX_INT[3]
#define BT_FN_VOID_VPTR_I8_INT BT_FN_VOID_VPTR_IX_INT[3]
#define BT_FN_BOOL_VPTR_PTR_I16_INT_INT BT_FN_BOOL_VPTR_PTR_IX_INT_INT[4]
#define BT_FN_I16_CONST_VPTR_INT BT_FN_IX_CONST_VPTR_INT[4]
#define BT_FN_I16_VPTR_I16_INT BT_FN_IX_VPTR_IX_INT[4]
#define BT_FN_VOID_VPTR_I16_INT BT_FN_VOID_VPTR_IX_INT[4]
#undef ATTR_NOTHROW_LEAF_LIST
#define ATTR_NOTHROW_LEAF_LIST ECF_NOTHROW | ECF_LEAF
#undef ATTR_TMPURE_NOTHROW_LEAF_LIST
#define ATTR_TMPURE_NOTHROW_LEAF_LIST ECF_TM_PURE | ATTR_NOTHROW_LEAF_LIST
#undef ATTR_NORETURN_NOTHROW_LEAF_LIST
#define ATTR_NORETURN_NOTHROW_LEAF_LIST ECF_NORETURN | ATTR_NOTHROW_LEAF_LIST
#undef ATTR_TMPURE_NORETURN_NOTHROW_LEAF_LIST
#define ATTR_TMPURE_NORETURN_NOTHROW_LEAF_LIST \
  ECF_TM_PURE | ATTR_NORETURN_NOTHROW_LEAF_LIST
#undef DEF_SANITIZER_BUILTIN
#define DEF_SANITIZER_BUILTIN(ENUM, NAME, TYPE, ATTRS) \
  decl = add_builtin_function ("__builtin_" NAME, TYPE, ENUM,		\
			       BUILT_IN_NORMAL, NAME, NULL_TREE);	\
  set_call_expr_flags (decl, ATTRS);					\
  set_builtin_decl (ENUM, decl, true);

#include "sanitizer.def"

#undef DEF_SANITIZER_BUILTIN
}
