is_aligning_offset (const_tree offset, const_tree exp)
{

  while (CONVERT_EXPR_P (offset))
    offset = TREE_OPERAND (offset, 0);


  if (TREE_CODE (offset) != BIT_AND_EXPR
      || !host_integerp (TREE_OPERAND (offset, 1), 1)
      || compare_tree_int (TREE_OPERAND (offset, 1),
			   BIGGEST_ALIGNMENT / BITS_PER_UNIT) <= 0
      || exact_log2 (tree_low_cst (TREE_OPERAND (offset, 1), 1) + 1) < 0)
    return 0;


  offset = TREE_OPERAND (offset, 0);
  while (CONVERT_EXPR_P (offset))
    offset = TREE_OPERAND (offset, 0);

  if (TREE_CODE (offset) != NEGATE_EXPR)
    return 0;

  offset = TREE_OPERAND (offset, 0);
  while (CONVERT_EXPR_P (offset))
    offset = TREE_OPERAND (offset, 0);


  return TREE_CODE (offset) == ADDR_EXPR && TREE_OPERAND (offset, 0) == exp;
}
