start_protocol (enum tree_code code, tree name, tree list, tree attributes)
{
  tree protocol;
  bool deprecated = false;

#ifdef OBJCPLUS
  if (current_namespace != global_namespace) {
    error ("Objective-C declarations may only appear in global scope");
  }
#endif


  if (attributes)
    {
      tree attribute;
      for (attribute = attributes; attribute; attribute = TREE_CHAIN (attribute))
	{
	  tree name = TREE_PURPOSE (attribute);

	  if (is_attribute_p  ("deprecated", name))
	    deprecated = true;
	  else
	    warning (OPT_Wattributes, "%qE attribute directive ignored", name);
	}
    }

  protocol = lookup_protocol (name,  false,
			       false);

  if (!protocol)
    {
      protocol = make_node (code);
      TYPE_LANG_SLOT_1 (protocol) = make_tree_vec (PROTOCOL_LANG_SLOT_ELTS);

      PROTOCOL_NAME (protocol) = name;
      PROTOCOL_LIST (protocol) = lookup_and_install_protocols (list,  false);
      add_protocol (protocol);
      PROTOCOL_DEFINED (protocol) = 1;
      PROTOCOL_FORWARD_DECL (protocol) = NULL_TREE;

      check_protocol_recursively (protocol, list);
    }
  else if (! PROTOCOL_DEFINED (protocol))
    {
      PROTOCOL_DEFINED (protocol) = 1;
      PROTOCOL_LIST (protocol) = lookup_and_install_protocols (list,  false);

      check_protocol_recursively (protocol, list);
    }
  else
    {
      warning (0, "duplicate declaration for protocol %qE",
	       name);
    }

  if (attributes)
    {
      TYPE_ATTRIBUTES (protocol) = attributes;
      if (deprecated)
	TREE_DEPRECATED (protocol) = 1;
    }

  return protocol;
}
