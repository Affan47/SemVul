locate_old_decl (tree decl)
{
  if (TREE_CODE (decl) == FUNCTION_DECL && DECL_BUILT_IN (decl))
    ;
  else if (DECL_INITIAL (decl))
    inform (input_location, "previous definition of %q+D was here", decl);
  else if (C_DECL_IMPLICIT (decl))
    inform (input_location, "previous implicit declaration of %q+D was here", decl);
  else
    inform (input_location, "previous declaration of %q+D was here", decl);
}
