nm_ip6_manager_cancel_addrconf (NMIP6Manager *manager, int ifindex)
{
	g_return_if_fail (NM_IS_IP6_MANAGER (manager));
	g_return_if_fail (ifindex > 0);

	g_hash_table_remove (NM_IP6_MANAGER_GET_PRIVATE (manager)->devices,
	                     GINT_TO_POINTER (ifindex));
}
