add_pubname (tree decl, dw_die_ref die)
{
  if (targetm.want_debug_pub_sections && TREE_PUBLIC (decl))
    {
      const char *name = dwarf2_name (decl, 1);
      if (name)
	add_pubname_string (name, die);
    }
}
