eyegraph_trymove(int pos, int color, const char *message, int str)
{
  static Hash_data remembered_board_hashes[MAXSTACK];
  int k;
  int does_capture = does_capture_something(pos, color);

  remembered_board_hashes[stackp] = board_hash;

  if (!trymove(pos, color, message, str))
    return 0;

  if (does_capture)
    return 1;

  for (k = 0; k < stackp; k++)
    if (hashdata_is_equal(board_hash, remembered_board_hashes[k])) {
      popgo();
      return 0;
    }

  return 1;
}
