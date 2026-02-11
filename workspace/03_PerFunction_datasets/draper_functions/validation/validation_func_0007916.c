_cpp_warn_if_unused_macro (pfile, node, v)
     cpp_reader *pfile;
     cpp_hashnode *node;
     void *v ATTRIBUTE_UNUSED;
{
  if (node->type == NT_MACRO && !(node->flags & NODE_BUILTIN))
    {
      cpp_macro *macro = node->value.macro;

      if (!macro->used

	  && macro->line >= pfile->first_unused_line
	  && MAIN_FILE_P (lookup_line (&pfile->line_maps, macro->line)))
	cpp_error_with_line (pfile, DL_WARNING, macro->line, 0,
			     "macro \"%s\" is not used", NODE_NAME (node));
    }

  return 1;
}
