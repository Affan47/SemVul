build_vector_from_val (tree vectype, tree sc)
{
  int i, nunits = TYPE_VECTOR_SUBPARTS (vectype);
  VEC(constructor_elt, gc) *v = NULL;

  if (sc == error_mark_node)
    return sc;


  gcc_checking_assert (types_compatible_p (TYPE_MAIN_VARIANT (TREE_TYPE (sc)),
					   TREE_TYPE (vectype)));

  v = VEC_alloc (constructor_elt, gc, nunits);
  for (i = 0; i < nunits; ++i)
    CONSTRUCTOR_APPEND_ELT (v, NULL_TREE, sc);

  if (CONSTANT_CLASS_P (sc))
    return build_vector_from_ctor (vectype, v);
  else
    return build_constructor (vectype, v);
}
