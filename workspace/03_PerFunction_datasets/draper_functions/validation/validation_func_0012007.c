haifa_finish_h_i_d (void)
{
  int i;
  haifa_insn_data_t data;
  struct reg_use_data *use, *next;

  FOR_EACH_VEC_ELT (h_i_d, i, data)
    {
      free (data->max_reg_pressure);
      free (data->reg_pressure);
      for (use = data->reg_use_list; use != NULL; use = next)
	{
	  next = use->next_insn_use;
	  free (use);
	}
    }
  h_i_d.release ();
}
