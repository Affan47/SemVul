can_change_cond_ref_to_const(Item_bool_func2 *target,
                             Item *target_expr, Item *target_value,
                             Item_bool_func2 *source,
                             Item *source_expr, Item *source_const)
{
  if (!target_expr->eq(source_expr,0) ||
       target_value == source_const ||
       target->compare_type() != source->compare_type())
    return false;
  if (target->compare_type() == STRING_RESULT)
  {


    return
      target->compare_collation() == source->compare_collation() &&
      target_value->collation.collation == source_const->collation.collation;
  }
  if (target->compare_type() == TIME_RESULT)
  {
    if (target_value->cmp_type() != TIME_RESULT)
    {


      return false;
    }
  }
  return true;
}
