_validate_relative(resource_allocation_response_msg_t *resp)
{

	if (opt.relative_set &&
	    ((opt.relative + opt.min_nodes) > resp->node_cnt)) {
		if (opt.nodes_set_opt) {
			error("--relative and --nodes option incompatible "
			      "with count of allocated nodes (%d+%d>%d)",
			      opt.relative, opt.min_nodes, resp->node_cnt);
		} else {
			error("--relative and SLURM_NNODES option incompatible "
			      "with count of allocated nodes (%d+%d>%d)",
			      opt.relative, opt.min_nodes, resp->node_cnt);
		}
		return -1;
	}
	return 0;
}
