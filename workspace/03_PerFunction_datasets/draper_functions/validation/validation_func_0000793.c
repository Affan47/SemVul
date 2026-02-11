exact_solution_new (void)
{
  ExactSolution * es;
  static const size_t size_of_exact_solution = sizeof(ExactSolution);

  es = (ExactSolution*) malloc(size_of_exact_solution);
  g_assert(es);

  es->solved_game_position = NULL;
  es->outcome = invalid_outcome;
  for (int i = 0; i < PV_MAX_LENGTH; i++) {
    es->pv[i] = invalid_move;
  }
  es->pv_length = 0;
  es->final_board = NULL;
  es->node_count = 0;
  es->leaf_count = 0;

  return es;
}
