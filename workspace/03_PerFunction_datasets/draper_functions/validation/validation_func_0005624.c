java_add_local_var (tree decl)
{
  tree *vars = &current_binding_level->names;
  tree next = *vars;
  DECL_CHAIN (decl) = next;
  *vars = decl;
  DECL_CONTEXT (decl) = current_function_decl;
  MAYBE_CREATE_VAR_LANG_DECL_SPECIFIC (decl);
  return decl;
}
