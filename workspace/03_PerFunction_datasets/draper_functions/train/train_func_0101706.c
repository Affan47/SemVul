axis_transform_back_from_row_one (const Axis axis,
                                  const uint32_t bitrow)
{
  g_assert(axis >= HO && axis <= DU);

  uint32_t tmp;
  SquareSet bit_board;

  switch (axis) {
  case HO:
    return (SquareSet) bitrow;
  case VE:
    tmp = bitrow;
    tmp |= tmp << 7;
    tmp |= tmp << 14;
    bit_board = (SquareSet) tmp | ((SquareSet) tmp << 28);
    return bit_board & column_a;
  case DD:
    tmp = bitrow;
    tmp |= tmp << 8;
    bit_board = (SquareSet) tmp | ((SquareSet) tmp << 16);
    bit_board |= bit_board << 32;
    return bit_board & diagonal_a1_h8;
  case DU:
    tmp = bitrow;
    tmp |= tmp << 8;
    tmp |= (tmp & squares_b1_f1_a2_e2) << 16;
    bit_board = (SquareSet) tmp | ((SquareSet) tmp << 32);
    return bit_board & diagonal_h1_a8;
  default:
    abort();
    return EXIT_FAILURE;
  }
}
