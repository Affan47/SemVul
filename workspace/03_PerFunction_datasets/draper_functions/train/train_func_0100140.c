decl_to_string (tree decl, int verbose)
{
  int flags = 0;

  if (TREE_CODE (decl) == TYPE_DECL || TREE_CODE (decl) == RECORD_TYPE
      || TREE_CODE (decl) == UNION_TYPE || TREE_CODE (decl) == ENUMERAL_TYPE)
    flags = TFF_CLASS_KEY_OR_ENUM;
  if (verbose)
    flags |= TFF_DECL_SPECIFIERS;
  else if (TREE_CODE (decl) == FUNCTION_DECL)
    flags |= TFF_DECL_SPECIFIERS | TFF_RETURN_TYPE;
  flags |= TFF_TEMPLATE_HEADER;

  reinit_cxx_pp ();
  dump_decl (decl, flags);
  return pp_formatted_text (cxx_pp);
}
