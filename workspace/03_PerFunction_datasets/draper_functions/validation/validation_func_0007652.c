handle_a2dp_open(struct unix_client *client, struct bt_open_req *req)
{
	if (!client->interface)

		client->interface = g_strdup(AUDIO_SINK_INTERFACE);
	else if (!g_str_equal(client->interface, AUDIO_SINK_INTERFACE) &&
			!g_str_equal(client->interface, AUDIO_SOURCE_INTERFACE))
		return -EIO;

	DBG("open a2dp - object=%s source=%s destination=%s lock=%s%s",
			strcmp(req->object, "") ? req->object : "ANY",
			strcmp(req->source, "") ? req->source : "ANY",
			strcmp(req->destination, "") ? req->destination : "ANY",
			req->lock & BT_READ_LOCK ? "read" : "",
			req->lock & BT_WRITE_LOCK ? "write" : "");

	return 0;
}
