Item_func_nullif::fix_length_and_dec()
{


  if (arg_count == 2)
    args[arg_count++]= m_arg0 ? m_arg0 : args[0];

  THD *thd= current_thd;


  DBUG_ASSERT(args[0] == args[2] || thd->stmt_arena->is_stmt_execute());
  if (args[0]->type() == SUM_FUNC_ITEM &&
      !thd->lex->is_ps_or_view_context_analysis())
  {


    m_cache= args[0]->cmp_type() == STRING_RESULT ?
             new (thd->mem_root) Item_cache_str_for_nullif(thd, args[0]) :
             args[0]->get_cache(thd);
    if (!m_cache)
      return TRUE;
    m_cache->setup(thd, args[0]);
    m_cache->store(args[0]);
    m_cache->set_used_tables(args[0]->used_tables());
    thd->change_item_tree(&args[0], m_cache);
    thd->change_item_tree(&args[2], m_cache);
  }
  set_handler(args[2]->type_handler());
  collation.set(args[2]->collation);
  decimals= args[2]->decimals;
  unsigned_flag= args[2]->unsigned_flag;
  fix_char_length(args[2]->max_char_length());
  maybe_null=1;
  m_arg0= args[0];
  if (setup_args_and_comparator(thd, &cmp))
    return TRUE;


  if (args[0] == m_arg0)
    m_arg0= NULL;
  return FALSE;
}
