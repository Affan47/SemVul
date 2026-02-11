expand_java_multianewarray (tree class_type, int ndim)
{
  int i;
  vec<tree, va_gc> *args = NULL;

  vec_safe_grow (args, 3 + ndim);

  (*args)[0] = build_class_ref (class_type);
  (*args)[1] = build_int_cst (NULL_TREE, ndim);

  for(i = ndim - 1; i >= 0; i-- )
    (*args)[(unsigned)(2 + i)] = pop_value (int_type_node);

  (*args)[2 + ndim] = null_pointer_node;

  push_value (build_call_vec (promote_type (class_type),
                              build_address_of (soft_multianewarray_node),
                              args));
}
