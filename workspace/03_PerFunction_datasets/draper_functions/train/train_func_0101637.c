ncp_put_super(struct super_block *sb)
{
	struct ncp_server *server = NCP_SBP(sb);

	ncp_lock_server(server);
	ncp_disconnect(server);
	ncp_unlock_server(server);

	ncp_stop_tasks(server);

	mutex_destroy(&server->rcv.creq_mutex);
	mutex_destroy(&server->root_setup_lock);
	mutex_destroy(&server->mutex);

	if (server->info_sock)
		sockfd_put(server->info_sock);
	sockfd_put(server->ncp_sock);
	kill_pid(server->m.wdog_pid, SIGTERM, 1);
	put_pid(server->m.wdog_pid);

	bdi_destroy(&server->bdi);
	kfree(server->priv.data);
	kfree(server->auth.object_name);
	vfree(server->rxbuf);
	vfree(server->txbuf);
	vfree(server->packet);
	call_rcu(&server->rcu, delayed_free);
}
