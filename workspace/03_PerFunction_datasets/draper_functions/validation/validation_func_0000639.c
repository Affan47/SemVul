ssa_fix_duplicate_block_edges (struct redirection_data *rd,
			       ssa_local_info_t *local_info)
{


  if (THREAD_TARGET2 (rd->incoming_edges->e))
    {
      edge victim;
      edge e2;
      edge e = rd->incoming_edges->e;


      update_destination_phis (local_info->bb, rd->dup_block);


      victim = find_edge (rd->dup_block, THREAD_TARGET (e)->dest);
      e2 = redirect_edge_and_branch (victim, THREAD_TARGET2 (e)->dest);


      if (e2 == victim)
	copy_phi_args (e2->dest, THREAD_TARGET2 (e), e2);
    }
  else
    {
      remove_ctrl_stmt_and_useless_edges (rd->dup_block, NULL);
      create_edge_and_update_destination_phis (rd, rd->dup_block);
    }
}
