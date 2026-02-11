next_runtime_abi_02_build_const_string_constructor (location_t loc, tree string,
						   int length)
{
  tree constructor, fields, var;
  VEC(constructor_elt,gc) *v = NULL;


  fields = TYPE_FIELDS (internal_const_str_type);
  CONSTRUCTOR_APPEND_ELT (v, fields,
			  build_unary_op (loc, ADDR_EXPR, string_class_decl, 0));

  fields = DECL_CHAIN (fields);
  CONSTRUCTOR_APPEND_ELT (v, fields,
			  build_unary_op (loc, ADDR_EXPR, string, 1));


  fields = DECL_CHAIN (fields);
  CONSTRUCTOR_APPEND_ELT (v, fields, build_int_cst (NULL_TREE, length));
  constructor = objc_build_constructor (internal_const_str_type, v);

  var = build_decl (input_location, CONST_DECL, NULL, TREE_TYPE (constructor));
  DECL_INITIAL (var) = constructor;
  TREE_STATIC (var) = 1;
  DECL_CONTEXT (var) = NULL;
  OBJCMETA (var, objc_meta, meta_const_str);
  return var;
}
