handle_visibility_attribute (node, name, args, flags, no_add_attrs)
     tree *node;
     tree name;
     tree args;
     int flags ATTRIBUTE_UNUSED;
     bool *no_add_attrs;
{
  tree decl = *node;

  if (decl_function_context (decl) != 0 || ! TREE_PUBLIC (decl))
    {
      warning ("`%s' attribute ignored", IDENTIFIER_POINTER (name));
      *no_add_attrs = true;
    }
  else
    {
      tree id;

      id = TREE_VALUE (args);
      if (TREE_CODE (id) != STRING_CST)
	{
	  error ("visibility arg not a string");
	  *no_add_attrs = true;
	  return NULL_TREE;
	}
      if (strcmp (TREE_STRING_POINTER (id), "hidden")
	  && strcmp (TREE_STRING_POINTER (id), "protected")
	  && strcmp (TREE_STRING_POINTER (id), "internal")
	  && strcmp (TREE_STRING_POINTER (id), "default"))
	{
	  error ("visibility arg must be one of \"default\", \"hidden\", \"protected\" or \"internal\"");
	  *no_add_attrs = true;
	  return NULL_TREE;
	}
    }

  return NULL_TREE;
}
