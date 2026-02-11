find_method_in_superclasses (tree searched_class, int flags,
                             tree method_name, tree signature,
                             tree (*signature_builder) (tree))
{
  tree klass;
  for (klass = CLASSTYPE_SUPER (searched_class); klass != NULL_TREE;
       klass = CLASSTYPE_SUPER (klass))
    {
      tree method;
      method = shallow_find_method (klass, flags, method_name,
				    signature, signature_builder);
      if (method != NULL_TREE)
	return method;
    }

  return NULL_TREE;
}
