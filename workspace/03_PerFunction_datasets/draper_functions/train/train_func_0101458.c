save_fixed_argument_area (int reg_parm_stack_space, rtx argblock, int *low_to_save, int *high_to_save)
{
  int low;
  int high;


  high = reg_parm_stack_space;
#ifdef ARGS_GROW_DOWNWARD
  high += 1;
#endif
  if (high > highest_outgoing_arg_in_use)
    high = highest_outgoing_arg_in_use;

  for (low = 0; low < high; low++)
    if (stack_usage_map[low] != 0)
      {
	int num_to_save;
	enum machine_mode save_mode;
	int delta;
	rtx stack_area;
	rtx save_area;

	while (stack_usage_map[--high] == 0)
	  ;

	*low_to_save = low;
	*high_to_save = high;

	num_to_save = high - low + 1;
	save_mode = mode_for_size (num_to_save * BITS_PER_UNIT, MODE_INT, 1);


	if ((low & (MIN (GET_MODE_SIZE (save_mode),
			 BIGGEST_ALIGNMENT / UNITS_PER_WORD) - 1)))
	  save_mode = BLKmode;

#ifdef ARGS_GROW_DOWNWARD
	delta = -high;
#else
	delta = low;
#endif
	stack_area = gen_rtx_MEM (save_mode,
				  memory_address (save_mode,
						  plus_constant (argblock,
								 delta)));

	set_mem_align (stack_area, PARM_BOUNDARY);
	if (save_mode == BLKmode)
	  {
	    save_area = assign_stack_temp (BLKmode, num_to_save, 0);
	    emit_block_move (validize_mem (save_area), stack_area,
			     GEN_INT (num_to_save), BLOCK_OP_CALL_PARM);
	  }
	else
	  {
	    save_area = gen_reg_rtx (save_mode);
	    emit_move_insn (save_area, stack_area);
	  }

	return save_area;
      }

  return NULL_RTX;
}
