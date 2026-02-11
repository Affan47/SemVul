cp_parser_save_default_args (cp_parser* parser, tree decl)
{
  tree probe;

  for (probe = TYPE_ARG_TYPES (TREE_TYPE (decl));
       probe;
       probe = TREE_CHAIN (probe))
    if (TREE_PURPOSE (probe))
      {
	TREE_PURPOSE (parser->unparsed_functions_queues)
	  = tree_cons (NULL_TREE, decl,
		       TREE_PURPOSE (parser->unparsed_functions_queues));
	break;
      }
  return;
}
