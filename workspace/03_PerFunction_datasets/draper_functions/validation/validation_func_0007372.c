genie_lengthen_int_to_long_mp (NODE_T * p)
{
  int digits = get_mp_digits (MODE (LONG_INT));
  MP_T *z;
  A68_INT k;
  POP_OBJECT (p, &k, A68_INT);
  STACK_MP (z, p, digits);
  (void) int_to_mp (p, z, VALUE (&k), digits);
  MP_STATUS (z) = (MP_T) INIT_MASK;
}
