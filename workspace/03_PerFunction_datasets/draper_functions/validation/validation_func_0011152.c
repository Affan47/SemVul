sstate_disconnect(upstype_t *ups)
{
	if ((!ups) || (ups->sock_fd < 0)) {
		return;
	}

	sstate_infofree(ups);
	sstate_cmdfree(ups);

	pconf_finish(&ups->sock_ctx);

	close(ups->sock_fd);
	ups->sock_fd = -1;
}
