print_mem_expr (outfile, expr)
     FILE *outfile;
     tree expr;
{
  if (TREE_CODE (expr) == COMPONENT_REF)
    {
      if (TREE_OPERAND (expr, 0))
	print_mem_expr (outfile, TREE_OPERAND (expr, 0));
      else
	fputs (" <variable>", outfile);
      if (DECL_NAME (TREE_OPERAND (expr, 1)))
	fprintf (outfile, ".%s",
		 IDENTIFIER_POINTER (DECL_NAME (TREE_OPERAND (expr, 1))));
    }
  else if (TREE_CODE (expr) == INDIRECT_REF)
    {
      fputs (" (*", outfile);
      print_mem_expr (outfile, TREE_OPERAND (expr, 0));
      fputs (")", outfile);
    }
  else if (DECL_NAME (expr))
    fprintf (outfile, " %s", IDENTIFIER_POINTER (DECL_NAME (expr)));
  else if (TREE_CODE (expr) == RESULT_DECL)
    fputs (" <result>", outfile);
  else
    fputs (" <anonymous>", outfile);
}
