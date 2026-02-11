genrtl_asm_stmt (tree cv_qualifier, tree string, tree output_operands,
		 tree input_operands, tree clobbers, int asm_input_p)
{
  if (cv_qualifier != NULL_TREE
      && cv_qualifier != ridpointers[(int) RID_VOLATILE])
    {
      warning ("%s qualifier ignored on asm",
	       IDENTIFIER_POINTER (cv_qualifier));
      cv_qualifier = NULL_TREE;
    }

  emit_line_note (input_location);
  if (asm_input_p)
    expand_asm (string, cv_qualifier != NULL_TREE);
  else
    c_expand_asm_operands (string, output_operands, input_operands,
			   clobbers, cv_qualifier != NULL_TREE,
			   input_location);
}
