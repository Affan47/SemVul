mcap_release_instance(struct mcap_instance *mi)
{
	GSList *l;

	if (!mi)
		return;

	if (mi->ccio) {
		g_io_channel_shutdown(mi->ccio, TRUE, NULL);
		g_io_channel_unref(mi->ccio);
		mi->ccio = NULL;
	}

	if (mi->dcio) {
		g_io_channel_shutdown(mi->dcio, TRUE, NULL);
		g_io_channel_unref(mi->dcio);
		mi->dcio = NULL;
	}

	for (l = mi->mcls; l; l = l->next) {
		mcap_mcl_release(l->data);
		mcap_mcl_unref(l->data);
	}

	g_slist_free(mi->mcls);
	mi->mcls = NULL;

	for (l = mi->cached; l; l = l->next) {
		mcap_mcl_release(l->data);
		mcap_mcl_unref(l->data);
	}

	g_slist_free(mi->cached);
	mi->cached = NULL;
}
