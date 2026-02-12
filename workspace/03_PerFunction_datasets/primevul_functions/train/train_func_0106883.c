void comm_handle(const struct iface_port *ifp)
{
	static struct msg_digest *md;

#if defined(IP_RECVERR) && defined(MSG_ERRQUEUE)


	if (!check_msg_errqueue(ifp, POLLIN))
		return;

#endif

	md = alloc_md();
	md->iface = ifp;

	if (read_packet(md))
		process_packet(&md);

	if (md != NULL)
		release_md(md);

	cur_state = NULL;
	reset_cur_connection();
	cur_from = NULL;
}
