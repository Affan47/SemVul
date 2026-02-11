handle_open_req(struct unix_client *client, struct bt_open_req *req)
{
	struct audio_device *dev;
	bdaddr_t src, dst;
	int err = 0;

	if (!check_nul(req->source) || !check_nul(req->destination) ||
			!check_nul(req->object)) {
		err = EINVAL;
		goto failed;
	}

	str2ba(req->source, &src);
	str2ba(req->destination, &dst);

	if (req->seid > BT_A2DP_SEID_RANGE) {
		err = handle_sco_open(client, req);
		if (err < 0) {
			err = -err;
			goto failed;
		}
	} else {
		err = handle_a2dp_open(client, req);
		if (err < 0) {
			err = -err;
			goto failed;
		}
	}

	if (!manager_find_device(req->object, &src, &dst, NULL, FALSE))
		goto failed;

	dev = manager_find_device(req->object, &src, &dst, client->interface,
				TRUE);
	if (!dev)
		dev = manager_find_device(req->object, &src, &dst,
					client->interface, FALSE);

	if (!dev)
		goto failed;

	client->seid = req->seid;
	client->lock = req->lock;

	start_open(dev, client);

	return;

failed:
	unix_ipc_error(client, BT_OPEN, err ? : EIO);
}
