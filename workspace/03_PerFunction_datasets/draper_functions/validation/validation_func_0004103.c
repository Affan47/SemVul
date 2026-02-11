JoinTypes(TRBinaryOpIC::TypeInfo x,
                                               TRBinaryOpIC::TypeInfo y) {
  if (x == UNINITIALIZED) return y;
  if (y == UNINITIALIZED) return x;
  if (x == STRING && y == STRING) return STRING;
  if (x == STRING || y == STRING) return GENERIC;
  if (x >= y) return x;
  return y;
}
