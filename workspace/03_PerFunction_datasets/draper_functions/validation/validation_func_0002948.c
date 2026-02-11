aa_add_move(struct aa_move attacks[AA_MAX_MOVES], int move, int target)
{
  int k;
  int r;

  for (k = 0; k < AA_MAX_MOVES; k++)
    if (attacks[k].move == move || attacks[k].move == NO_MOVE)
      break;


  if (k == AA_MAX_MOVES)
    return;

  target = find_origin(target);


  if (attacks[k].move == NO_MOVE) {
    attacks[k].move = move;
    attacks[k].target[0] = target;
    if (AA_MAX_TARGETS_PER_MOVE > 0)
      attacks[k].target[1] = NO_MOVE;

    if (k < AA_MAX_MOVES - 1)
      attacks[k+1].move = NO_MOVE;

    return;
  }


  for (r = 0; r < AA_MAX_TARGETS_PER_MOVE; r++)
    if (attacks[k].target[r] == target || attacks[k].target[r] == NO_MOVE)
      break;


  if (r == AA_MAX_TARGETS_PER_MOVE)
    return;


  if (attacks[k].target[r] == target)
    return;


  attacks[k].target[r] = target;
  if (r < AA_MAX_TARGETS_PER_MOVE - 1)
    attacks[k].target[r + 1] = NO_MOVE;
}
