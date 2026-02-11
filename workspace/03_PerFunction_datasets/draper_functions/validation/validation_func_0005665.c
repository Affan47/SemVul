pushdecl_with_scope_1 (tree x, cp_binding_level *level, bool is_friend)
{
  cp_binding_level *b;
  tree function_decl = current_function_decl;

  current_function_decl = NULL_TREE;
  if (level->kind == sk_class)
    {
      b = class_binding_level;
      class_binding_level = level;
      pushdecl_class_level (x);
      class_binding_level = b;
    }
  else
    {
      b = current_binding_level;
      current_binding_level = level;
      x = pushdecl_maybe_friend (x, is_friend);
      current_binding_level = b;
    }
  current_function_decl = function_decl;
  return x;
}
