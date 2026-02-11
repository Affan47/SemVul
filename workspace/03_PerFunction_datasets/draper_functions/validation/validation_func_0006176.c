owl_does_defend(int move, int target, int *kworm)
{
  int color = board[target];
  int result = 0;
  struct local_owl_data *owl;
  int reading_nodes_when_called = get_reading_node_counter();
  int tactical_nodes;
  int origin;
  int acode;
  int wpos = NO_MOVE;
  int wid = MAX_GOAL_WORMS;
  double start = 0.0;

  if (debug & DEBUG_OWL_PERFORMANCE)
    start = gg_cputime();

  if (worm[target].unconditional_status == DEAD)
    return 0;

  origin = dragon[target].origin;
  TRACE("owl_does_defend %1m %1m(%1m)\n", move, target, origin);

  if (search_persistent_owl_cache(OWL_DOES_DEFEND, move, target, 0,
				  &result, kworm, NULL, NULL))
    return result;

  if (trymove(move, color, "owl_does_defend", target)) {

    if (search_persistent_owl_cache(OWL_ATTACK, origin, 0, 0,
				    &result, NULL, kworm, NULL)) {
      popgo();
      return REVERSE_RESULT(result);
    }


    init_owl(&owl, target, NO_MOVE, move, 1, NULL);
    prepare_goal_list(target, owl, owl_goal_worm, &goal_worms_computed,
		      kworm, 0);
    acode = do_owl_attack(target, NULL, &wid, owl, 0);
    finish_goal_list(&goal_worms_computed, &wpos, owl_goal_worm, wid);
    result = REVERSE_RESULT(acode);
    popgo();
  }
  else
    return 0;

  tactical_nodes = get_reading_node_counter() - reading_nodes_when_called;

  DEBUG(DEBUG_OWL_PERFORMANCE,
	"owl_does_defend %1m %1m(%1m), result %d (%d, %d nodes, %f seconds)\n",
	move, target, origin, result, local_owl_node_counter,
	tactical_nodes, gg_cputime() - start);

  store_persistent_owl_cache(OWL_DOES_DEFEND, move, target, 0,
			     result, wpos, 0, 0,
			     tactical_nodes, owl->goal, board[target]);

  if (kworm)
    *kworm = wpos;
  return result;
}
