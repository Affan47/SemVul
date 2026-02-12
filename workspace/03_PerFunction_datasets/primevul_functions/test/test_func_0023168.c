Item* Item_func_case_simple::propagate_equal_fields(THD *thd,
                                                    const Context &ctx,
                                                    COND_EQUAL *cond)
{
  const Type_handler *first_expr_cmp_handler;

  first_expr_cmp_handler= args[0]->type_handler_for_comparison();


  if (m_found_types == (1UL << first_expr_cmp_handler->cmp_type()))
    propagate_and_change_item_tree(thd, &args[0], cond,
      Context(ANY_SUBST, first_expr_cmp_handler, cmp_collation.collation));


  uint i, count= when_count();
  for (i= 1; i <= count; i++)
  {
    Type_handler_hybrid_field_type tmp(first_expr_cmp_handler);
    if (!tmp.aggregate_for_comparison(args[i]->type_handler_for_comparison()))
      propagate_and_change_item_tree(thd, &args[i], cond,
        Context(ANY_SUBST, tmp.type_handler(), cmp_collation.collation));
  }


  for (; i < arg_count; i++)
    propagate_and_change_item_tree(thd, &args[i], cond, Context_identity());

  return this;
}
