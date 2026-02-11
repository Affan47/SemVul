ready_sort (struct ready_list *ready)
{
  int i;
  rtx *first = ready_lastpos (ready);

  if (sched_pressure == SCHED_PRESSURE_WEIGHTED)
    {
      for (i = 0; i < ready->n_ready; i++)
	if (!DEBUG_INSN_P (first[i]))
	  setup_insn_reg_pressure_info (first[i]);
    }
  if (sched_pressure == SCHED_PRESSURE_MODEL
      && model_curr_point < model_num_insns)
    model_set_excess_costs (first, ready->n_ready);
  SCHED_SORT (first, ready->n_ready);
}
