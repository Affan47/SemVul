lto_register_builtin_type (tree type, const char *name)
{
  tree decl;

  if (!TYPE_NAME (type))
    {
      decl = build_decl (UNKNOWN_LOCATION, TYPE_DECL,
			 get_identifier (name), type);
      DECL_ARTIFICIAL (decl) = 1;
      TYPE_NAME (type) = decl;
    }

  registered_builtin_types = tree_cons (0, type, registered_builtin_types);
}
