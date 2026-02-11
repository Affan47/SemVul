scev_analysis (void)
{
  vec<gimple> exit_conditions;

  exit_conditions.create (37);
  select_loops_exit_conditions (&exit_conditions);

  if (dump_file && (dump_flags & TDF_STATS))
    analyze_scalar_evolution_for_all_loop_phi_nodes (&exit_conditions);

  number_of_iterations_for_all_loops (&exit_conditions);
  exit_conditions.release ();
}
