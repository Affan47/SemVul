game_position_x_final_value (const GamePositionX *const gpx)
{
  const int b_count = bit_works_popcount(gpx->blacks);
  const int w_count = bit_works_popcount(gpx->whites);
  const int difference = b_count - w_count;
  if (difference == 0) return 0;
  const int empties = 64 - (b_count + w_count);
  const int delta = (difference > 0) ? difference + empties : difference - empties;
  return (gpx->player == BLACK_PLAYER) ? +delta : -delta;
}
