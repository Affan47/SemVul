select_best_block (basic_block early_bb,
		   basic_block late_bb,
		   gimple stmt)
{
  basic_block best_bb = late_bb;
  basic_block temp_bb = late_bb;
  int threshold;

  while (temp_bb != early_bb)
    {


      if (temp_bb->loop_depth < best_bb->loop_depth)
	best_bb = temp_bb;


      temp_bb = get_immediate_dominator (CDI_DOMINATORS, temp_bb);
    }


  if (best_bb->loop_depth < early_bb->loop_depth)
    return best_bb;


  threshold = PARAM_VALUE (PARAM_SINK_FREQUENCY_THRESHOLD);
  if (gimple_vuse (stmt) || gimple_vdef (stmt))
    {
      threshold += 7;
      if (threshold > 100)
	threshold = 100;
    }


  if (best_bb->loop_depth == early_bb->loop_depth
      && best_bb->frequency < (early_bb->frequency * threshold / 100.0))
    return best_bb;


  return early_bb;
}
