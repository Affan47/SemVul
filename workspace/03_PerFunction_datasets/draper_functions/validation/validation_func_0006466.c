device_browse_primary(struct btd_device *device, DBusConnection *conn,
				DBusMessage *msg, gboolean secure)
{
	struct btd_adapter *adapter = device->adapter;
	struct att_callbacks *attcb;
	struct browse_req *req;
	BtIOSecLevel sec_level;
	bdaddr_t src;

	if (device->browse)
		return -EBUSY;


	if (device->primaries) {
		error("Could not update GATT services");
		return -ENOSYS;
	}

	req = g_new0(struct browse_req, 1);
	req->device = btd_device_ref(device);
	adapter_get_address(adapter, &src);

	device->browse = req;

	if (device->attrib) {
		gatt_discover_primary(device->attrib, NULL, primary_cb, req);
		goto done;
	}

	sec_level = secure ? BT_IO_SEC_HIGH : BT_IO_SEC_LOW;

	attcb = g_new0(struct att_callbacks, 1);
	attcb->error = att_browse_error_cb;
	attcb->success = att_browse_cb;
	attcb->user_data = device;

	device->att_io = bt_io_connect(BT_IO_L2CAP, att_connect_cb,
				attcb, NULL, NULL,
				BT_IO_OPT_SOURCE_BDADDR, &src,
				BT_IO_OPT_DEST_BDADDR, &device->bdaddr,
				BT_IO_OPT_DEST_TYPE, device->bdaddr_type,
				BT_IO_OPT_CID, ATT_CID,
				BT_IO_OPT_SEC_LEVEL, sec_level,
				BT_IO_OPT_INVALID);

	if (device->att_io == NULL) {
		device->browse = NULL;
		browse_request_free(req);
		g_free(attcb);
		return -EIO;
	}

done:
	if (conn == NULL)
		conn = get_dbus_connection();

	req->conn = dbus_connection_ref(conn);

	if (msg) {
		const char *sender = dbus_message_get_sender(msg);

		req->msg = dbus_message_ref(msg);


		req->listener_id = g_dbus_add_disconnect_watch(conn,
						sender,
						discover_services_req_exit,
						req, NULL);
	}

	return 0;
}
