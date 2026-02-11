dump_expr_init_vec (VEC(constructor_elt,gc) *v, int flags)
{
  unsigned HOST_WIDE_INT idx;
  tree value;

  FOR_EACH_CONSTRUCTOR_VALUE (v, idx, value)
    {
      dump_expr (value, flags | TFF_EXPR_IN_PARENS);
      if (idx != VEC_length (constructor_elt, v) - 1)
	pp_separate_with_comma (cxx_pp);
    }
}
