autohelperowl_attackpat89(int trans, int move, int color, int action)
{
  int a, b, c, d, e;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(610, trans, move);
  b = AFFINE_TRANSFORM(609, trans, move);
  c = AFFINE_TRANSFORM(573, trans, move);
  d = AFFINE_TRANSFORM(572, trans, move);
  e = AFFINE_TRANSFORM(685, trans, move);

  return somewhere(color, 0, 4, a, b, c, d) && owl_escape_value(e) > 0;
}
