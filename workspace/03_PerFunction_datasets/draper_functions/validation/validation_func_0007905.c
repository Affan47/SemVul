c_print_identifier (FILE *file, tree node, int indent)
{
  print_node (file, "symbol", I_SYMBOL_DECL (node), indent + 4);
  print_node (file, "tag", I_TAG_DECL (node), indent + 4);
  print_node (file, "label", I_LABEL_DECL (node), indent + 4);
  if (C_IS_RESERVED_WORD (node) && C_RID_CODE (node) != RID_CXX_COMPAT_WARN)
    {
      tree rid = ridpointers[C_RID_CODE (node)];
      indent_to (file, indent + 4);
      fprintf (file, "rid " HOST_PTR_PRINTF " \"%s\"",
	       (void *) rid, IDENTIFIER_POINTER (rid));
    }
}
