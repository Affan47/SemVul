autohelperowl_defendpat445(int trans, int move, int color, int action)
{
  int a, b, c, d, A, B, C;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(722, trans, move);
  b = AFFINE_TRANSFORM(721, trans, move);
  c = AFFINE_TRANSFORM(758, trans, move);
  d = AFFINE_TRANSFORM(757, trans, move);
  A = AFFINE_TRANSFORM(648, trans, move);
  B = AFFINE_TRANSFORM(685, trans, move);
  C = AFFINE_TRANSFORM(794, trans, move);

  return  owl_escape_value(d) > 0 && play_attack_defend2_n(color, 1, 5, move, a, b, c, d, B, c) && play_connect_n(color, 1, 6, move, a, b, c, d, NO_MOVE, A, C);
}
