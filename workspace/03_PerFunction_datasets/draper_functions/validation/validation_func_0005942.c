dump_ada_import (pretty_printer *buffer, tree t)
{
  const char *name = IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (t));
  int is_stdcall = TREE_CODE (t) == FUNCTION_DECL &&
    lookup_attribute ("stdcall", TYPE_ATTRIBUTES (TREE_TYPE (t)));

  if (is_stdcall)
    pp_string (buffer, "pragma Import (Stdcall, ");
  else if (name[0] == '_' && name[1] == 'Z')
    pp_string (buffer, "pragma Import (CPP, ");
  else
    pp_string (buffer, "pragma Import (C, ");

  dump_ada_decl_name (buffer, t, false);
  pp_string (buffer, ", \"");

  if (is_stdcall)
    pp_string (buffer, IDENTIFIER_POINTER (DECL_NAME (t)));
  else
    pp_asm_name (buffer, t);

  pp_string (buffer, "\");");
}
