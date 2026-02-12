static void set_sock_ids(struct mdesc_handle *hp)
{
	u64 mp;


	if (!set_max_cache_ids_by_cache(hp, 3))
		set_max_cache_ids_by_cache(hp, 2);


	mp = mdesc_node_by_name(hp, MDESC_NODE_NULL, "sockets");
	if (mp != MDESC_NODE_NULL)
		set_sock_ids_by_socket(hp, mp);
}
