nsm_lookup_addr(const struct list_head *nsm_handles,
					const struct sockaddr *sap)
{
	struct nsm_handle *nsm;

	list_for_each_entry(nsm, nsm_handles, sm_link)
		if (rpc_cmp_addr(nsm_addr(nsm), sap))
			return nsm;
	return NULL;
}
