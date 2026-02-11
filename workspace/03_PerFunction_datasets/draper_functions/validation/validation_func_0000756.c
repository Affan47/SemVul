dump_gimple_mem_ops (pretty_printer *buffer, gimple gs, int spc, int flags)
{
  tree vdef = gimple_vdef (gs);
  tree vuse = gimple_vuse (gs);

  if (!ssa_operands_active () || !gimple_references_memory_p (gs))
    return;

  if (vdef != NULL_TREE)
    {
      pp_string (buffer, "# ");
      dump_generic_node (buffer, vdef, spc + 2, flags, false);
      pp_string (buffer, " = VDEF <");
      dump_generic_node (buffer, vuse, spc + 2, flags, false);
      pp_character (buffer, '>');
      newline_and_indent (buffer, spc);
    }
  else if (vuse != NULL_TREE)
    {
      pp_string (buffer, "# VUSE <");
      dump_generic_node (buffer, vuse, spc + 2, flags, false);
      pp_character (buffer, '>');
      newline_and_indent (buffer, spc);
    }
}
