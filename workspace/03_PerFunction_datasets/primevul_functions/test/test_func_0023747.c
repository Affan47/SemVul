bool Item_func_case_simple::aggregate_switch_and_when_arguments(THD *thd,
                                                                bool nulls_eq)
{
  uint ncases= when_count();
  m_found_types= 0;
  if (prepare_predicant_and_values(thd, &m_found_types, nulls_eq))
  {


    DBUG_ASSERT(thd->is_error());
    return true;
  }

  if (!(m_found_types= collect_cmp_types(args, ncases + 1)))
    return true;

  if (m_found_types & (1U << STRING_RESULT))
  {


    if (agg_arg_charsets_for_comparison(cmp_collation, args, ncases + 1))
      return true;
  }

  if (make_unique_cmp_items(thd, cmp_collation.collation))
    return true;

  return false;
}
