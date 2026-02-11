autohelperaa_attackpat24(int trans, int move, int color, int action)
{
  int A, B;
  UNUSED(color);
  UNUSED(action);

  A = AFFINE_TRANSFORM(649, trans, move);
  B = AFFINE_TRANSFORM(723, trans, move);

  return countlib(A) == 3 && countlib(B) > 1 && play_attack_defend_n(color, 1, 1, move, A);
}
