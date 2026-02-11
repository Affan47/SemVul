conn_get_by_addrs(void *my_addr, int my_addr_len,
				     void *peer_addr, int peer_addr_len)
{
	struct drbd_resource *resource;
	struct drbd_connection *connection;

	rcu_read_lock();
	for_each_resource_rcu(resource, &drbd_resources) {
		for_each_connection_rcu(connection, resource) {
			if (connection->my_addr_len == my_addr_len &&
			    connection->peer_addr_len == peer_addr_len &&
			    !memcmp(&connection->my_addr, my_addr, my_addr_len) &&
			    !memcmp(&connection->peer_addr, peer_addr, peer_addr_len)) {
				kref_get(&connection->kref);
				goto found;
			}
		}
	}
	connection = NULL;
found:
	rcu_read_unlock();
	return connection;
}
