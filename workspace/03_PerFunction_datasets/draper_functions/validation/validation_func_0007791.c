select_g_select_nodeinfo_alloc(void)
{
	dynamic_plugin_data_t *nodeinfo_ptr = NULL;
	uint32_t plugin_id;

	if (slurm_select_init(0) < 0)
		return NULL;

	plugin_id = working_cluster_rec ?
		working_cluster_rec->plugin_id_select : select_context_default;

	nodeinfo_ptr = xmalloc(sizeof(dynamic_plugin_data_t));
	nodeinfo_ptr->plugin_id = plugin_id;
	nodeinfo_ptr->data = (*(ops[plugin_id].
				nodeinfo_alloc))();
	return nodeinfo_ptr;
}
