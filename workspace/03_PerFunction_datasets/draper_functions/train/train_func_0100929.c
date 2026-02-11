gigolo_backend_gvfs_browse_network(GigoloBackendGVFS *backend, GtkWindow *parent, GtkTreeStore *store)
{
	BrowseData *bd = g_new0(BrowseData, 1);
	GigoloBackendGVFSPrivate *priv;

	g_return_if_fail(backend != NULL);

	bd->mode = BROWSE_MODE_DOMAINS;
	bd->parent_path = NULL;
	bd->parent = parent;
	bd->store = store;
	bd->uri = g_strdup("smb://");
	bd->self = backend;
	bd->browse_func = browse_network_real;

	priv = GIGOLO_BACKEND_GVFS_GET_PRIVATE(backend);
	priv->browse_counter = 0;

	browse_network_real(bd);


	g_timeout_add(250, browse_network_ready_cb, backend);
}
