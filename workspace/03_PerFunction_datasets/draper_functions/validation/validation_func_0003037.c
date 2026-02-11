make_alias_for (tree target, tree newid)
{
  tree alias = build_decl (DECL_SOURCE_LOCATION (target),
			   TREE_CODE (target), newid, TREE_TYPE (target));
  DECL_LANG_SPECIFIC (alias) = DECL_LANG_SPECIFIC (target);
  cxx_dup_lang_specific_decl (alias);
  DECL_CONTEXT (alias) = NULL;
  TREE_READONLY (alias) = TREE_READONLY (target);
  TREE_THIS_VOLATILE (alias) = TREE_THIS_VOLATILE (target);
  TREE_PUBLIC (alias) = 0;
  DECL_INTERFACE_KNOWN (alias) = 1;
  if (DECL_LANG_SPECIFIC (alias))
    {
      DECL_NOT_REALLY_EXTERN (alias) = 1;
      DECL_USE_TEMPLATE (alias) = 0;
      DECL_TEMPLATE_INFO (alias) = NULL;
    }
  DECL_EXTERNAL (alias) = 0;
  DECL_ARTIFICIAL (alias) = 1;
  DECL_TEMPLATE_INSTANTIATED (alias) = 0;
  if (TREE_CODE (alias) == FUNCTION_DECL)
    {
      DECL_SAVED_FUNCTION_DATA (alias) = NULL;
      DECL_DESTRUCTOR_P (alias) = 0;
      DECL_CONSTRUCTOR_P (alias) = 0;
      DECL_PENDING_INLINE_P (alias) = 0;
      DECL_DECLARED_INLINE_P (alias) = 0;
      DECL_INITIAL (alias) = error_mark_node;
      DECL_ARGUMENTS (alias) = copy_list (DECL_ARGUMENTS (target));
    }
  else
    TREE_STATIC (alias) = 1;
  TREE_ADDRESSABLE (alias) = 1;
  TREE_USED (alias) = 1;
  SET_DECL_ASSEMBLER_NAME (alias, DECL_NAME (alias));
  return alias;
}
