genie_odd_int (NODE_T * p)
{
  A68_INT j;
  POP_OBJECT (p, &j, A68_INT);
  PUSH_PRIMITIVE (p, (BOOL_T) ((VALUE (&j) >= 0 ? VALUE (&j) : -VALUE (&j)) % 2 == 1), A68_BOOL);
}
