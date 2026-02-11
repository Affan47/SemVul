execute_sm (struct loop *loop, VEC (edge, heap) *exits, mem_ref_p ref)
{
  tree tmp_var;
  unsigned i;
  gimple load, store;
  struct fmt_data fmt_data;
  edge ex;
  struct lim_aux_data *lim_data;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Executing store motion of ");
      print_generic_expr (dump_file, ref->mem, 0);
      fprintf (dump_file, " from loop %d\n", loop->num);
    }

  tmp_var = make_rename_temp (TREE_TYPE (ref->mem),
			      get_lsm_tmp_name (ref->mem, ~0));

  fmt_data.loop = loop;
  fmt_data.orig_loop = loop;
  for_each_index (&ref->mem, force_move_till, &fmt_data);

  rewrite_mem_refs (loop, ref, tmp_var);


  load = gimple_build_assign (tmp_var, unshare_expr (ref->mem));
  lim_data = init_lim_data (load);
  lim_data->max_loop = loop;
  lim_data->tgt_loop = loop;


  gsi_insert_on_edge (loop_latch_edge (loop), load);

  FOR_EACH_VEC_ELT (edge, exits, i, ex)
    {
      store = gimple_build_assign (unshare_expr (ref->mem), tmp_var);
      gsi_insert_on_edge (ex, store);
    }
}
