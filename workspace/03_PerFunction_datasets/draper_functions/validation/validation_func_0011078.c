autohelperaa_attackpat26(int trans, int move, int color, int action)
{
  int A, B;
  UNUSED(color);
  UNUSED(action);

  A = AFFINE_TRANSFORM(757, trans, move);
  B = AFFINE_TRANSFORM(722, trans, move);

  return countlib(A)<=3 && countlib(B)<=3 && (play_attack_defend_n(color, 1, 1, move, A) || play_attack_defend_n(color, 1, 1, move, B));
}
