bitmap_remove_from_set (bitmap_set_t set, pre_expr expr)
{
  unsigned int val  = get_expr_value_id (expr);
  if (!value_id_constant_p (val))
    {
      bitmap_clear_bit (&set->values, val);
      bitmap_clear_bit (&set->expressions, get_expression_id (expr));
    }
}
