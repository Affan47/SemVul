dump_affine_function (FILE *outf, affine_fn fn)
{
  unsigned i;
  tree coef;

  print_generic_expr (outf, VEC_index (tree, fn, 0), TDF_SLIM);
  for (i = 1; VEC_iterate (tree, fn, i, coef); i++)
    {
      fprintf (outf, " + ");
      print_generic_expr (outf, coef, TDF_SLIM);
      fprintf (outf, " * x_%u", i);
    }
}
