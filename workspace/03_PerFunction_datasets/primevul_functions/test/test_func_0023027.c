bool Item_func::setup_args_and_comparator(THD *thd, Arg_comparator *cmp)
{
  DBUG_ASSERT(arg_count >= 2);

  if (args[0]->cmp_type() == STRING_RESULT &&
      args[1]->cmp_type() == STRING_RESULT)
  {
    DTCollation tmp;
    if (agg_arg_charsets_for_comparison(tmp, args, 2))
      return true;
    cmp->m_compare_collation= tmp.collation;
  }

  DBUG_ASSERT(functype() != LIKE_FUNC);
  convert_const_compared_to_int_field(thd);

  return cmp->set_cmp_func(this, &args[0], &args[1], true);
}
