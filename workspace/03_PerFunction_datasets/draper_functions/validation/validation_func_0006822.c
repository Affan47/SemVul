vn_nary_op_eq (const void *p1, const void *p2)
{
  const_vn_nary_op_t const vno1 = (const_vn_nary_op_t) p1;
  const_vn_nary_op_t const vno2 = (const_vn_nary_op_t) p2;
  unsigned i;

  if (vno1->hashcode != vno2->hashcode)
    return false;

  if (vno1->length != vno2->length)
    return false;

  if (vno1->opcode != vno2->opcode
      || !types_compatible_p (vno1->type, vno2->type))
    return false;

  for (i = 0; i < vno1->length; ++i)
    if (!expressions_equal_p (vno1->op[i], vno2->op[i]))
      return false;

  return true;
}
