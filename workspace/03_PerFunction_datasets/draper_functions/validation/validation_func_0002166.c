end_board ()
{
  if (currentUiMode == UIMODE_SOUND) {
    gc_sound_policy_set(sound_policy);
    gc_sound_bg_resume();
  }

  if(gcomprisBoard!=NULL)
    {
      pause_board(TRUE);

      memory_destroy_all_items();
      if (currentMode == MODE_TUX){
	if (tux_memory)
	  g_queue_free(tux_memory);
	tux_memory = NULL;
      }
    }
  g_free(op_add);
  op_add = NULL;
  g_free(op_minus);
  op_minus = NULL;
  g_free(op_mult);
  op_mult = NULL;
  g_free(op_div);
  op_div = NULL;

  gcomprisBoard = NULL;
}
