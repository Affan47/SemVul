void decoder_context::calc_tid_and_framerate_ratio()
{
  int highestTID = get_highest_TID();


  if (framedrop_tab[100].tid != highestTID) {
    compute_framedrop_table();
  }

  goal_HighestTid       = framedrop_tab[framerate_ratio].tid;
  layer_framerate_ratio = framedrop_tab[framerate_ratio].ratio;


  current_HighestTid = goal_HighestTid;
}
