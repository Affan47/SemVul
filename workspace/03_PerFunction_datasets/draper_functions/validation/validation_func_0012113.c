print_loop (FILE *file, struct loop *loop, int indent, int verbosity)
{
  char *s_indent;
  basic_block bb;

  if (loop == NULL)
    return;

  s_indent = (char *) alloca ((size_t) indent + 1);
  memset ((void *) s_indent, ' ', (size_t) indent);
  s_indent[indent] = '\0';


  fprintf (file, "%sloop_%d (", s_indent, loop->num);
  if (loop->header)
    fprintf (file, "header = %d", loop->header->index);
  else
    {
      fprintf (file, "deleted)\n");
      return;
    }
  if (loop->latch)
    fprintf (file, ", latch = %d", loop->latch->index);
  else
    fprintf (file, ", multiple latches");
  fprintf (file, ", niter = ");
  print_generic_expr (file, loop->nb_iterations, 0);

  if (loop->any_upper_bound)
    {
      fprintf (file, ", upper_bound = ");
      dump_double_int (file, loop->nb_iterations_upper_bound, true);
    }

  if (loop->any_estimate)
    {
      fprintf (file, ", estimate = ");
      dump_double_int (file, loop->nb_iterations_estimate, true);
    }
  fprintf (file, ")\n");


  if (verbosity >= 1)
    {
      fprintf (file, "%s{\n", s_indent);
      FOR_EACH_BB (bb)
	if (bb->loop_father == loop)
	  print_loops_bb (file, bb, indent, verbosity);

      print_loop_and_siblings (file, loop->inner, indent + 2, verbosity);
      fprintf (file, "%s}\n", s_indent);
    }
}
