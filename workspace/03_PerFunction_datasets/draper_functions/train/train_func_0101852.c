sjlj_assign_call_site_values (void)
{
  htab_t ar_hash;
  int i, disp_index;
  eh_landing_pad lp;

  vec_alloc (crtl->eh.action_record_data, 64);
  ar_hash = htab_create (31, action_record_hash, action_record_eq, free);

  disp_index = 0;
  call_site_base = 1;
  for (i = 1; vec_safe_iterate (cfun->eh->lp_array, i, &lp); ++i)
    if (lp && lp->post_landing_pad)
      {
	int action, call_site;


	action = collect_one_action_chain (ar_hash, lp->region);


	if (action == -2)
	  call_site = 0;

	else if (action == -1)
	  call_site = -1;

	else
	  call_site = add_call_site (GEN_INT (disp_index), action, 0);
	sjlj_lp_call_site_index[i] = call_site;

	disp_index++;
      }

  htab_delete (ar_hash);

  return disp_index;
}
