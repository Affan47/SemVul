le_conn_complete(int index, void *ptr)
{
	struct dev_info *dev = &devs[index];
	evt_le_connection_complete *evt = ptr;
	char filename[PATH_MAX];
	char local_addr[18], peer_addr[18], *str;
	struct bt_conn *conn;
	uint8_t bdaddr_type;

	if (evt->status) {
		btd_event_conn_failed(&dev->bdaddr, &evt->peer_bdaddr,
								evt->status);
		return;
	}

	conn = get_connection(dev, &evt->peer_bdaddr);
	conn->handle = btohs(evt->handle);

	bdaddr_type = le_addr_type(evt->peer_bdaddr_type);
	btd_event_conn_complete(&dev->bdaddr, &evt->peer_bdaddr, bdaddr_type,
								NULL, NULL);


	ba2str(&dev->bdaddr, local_addr);
	ba2str(&evt->peer_bdaddr, peer_addr);

	create_name(filename, sizeof(filename), STORAGEDIR, local_addr,
							"manufacturers");

	str = textfile_get(filename, peer_addr);
	if (!str)
		get_remote_version(index, btohs(evt->handle));
	else
		free(str);
}
