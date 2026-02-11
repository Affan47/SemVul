pending_connect_finalize(struct audio_device *dev)
{
	struct headset *hs = dev->headset;
	struct pending_connect *p = hs->pending;

	if (p == NULL)
		return;

	if (p->svclass)
		bt_cancel_discovery(&dev->src, &dev->dst);

	g_slist_foreach(p->callbacks, (GFunc) pending_connect_complete, dev);

	g_slist_free_full(p->callbacks, g_free);

	if (p->io) {
		g_io_channel_shutdown(p->io, TRUE, NULL);
		g_io_channel_unref(p->io);
	}

	if (p->msg)
		dbus_message_unref(p->msg);

	if (p->call) {
		dbus_pending_call_cancel(p->call);
		dbus_pending_call_unref(p->call);
	}

	g_free(p);

	hs->pending = NULL;
}
