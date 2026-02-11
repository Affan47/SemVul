check_methods (tree t)
{
  tree x;

  for (x = TYPE_METHODS (t); x; x = TREE_CHAIN (x))
    {

      if (DECL_ASSEMBLER_NAME_SET_P (x)
	  && IDENTIFIER_ERROR_LOCUS (DECL_ASSEMBLER_NAME (x)))
	continue;

      check_for_override (x, t);
      if (DECL_PURE_VIRTUAL_P (x) && ! DECL_VINDEX (x))
	cp_error_at ("initializer specified for non-virtual method `%D'", x);


      if (DECL_VINDEX (x))
	{
	  TYPE_POLYMORPHIC_P (t) = 1;
	  if (DECL_PURE_VIRTUAL_P (x))
	    CLASSTYPE_PURE_VIRTUALS (t)
	      = tree_cons (NULL_TREE, x, CLASSTYPE_PURE_VIRTUALS (t));
	}
    }
}
