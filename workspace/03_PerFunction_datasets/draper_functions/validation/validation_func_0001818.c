gmpc_browsers_nowplaying_finalize (GObject* obj) {
	GmpcBrowsersNowplaying * self;
	self = GMPC_BROWSERS_NOWPLAYING (obj);
	_g_free0 (self->priv->title_color);
	_g_free0 (self->priv->item_color);
	_g_object_unref0 (self->priv->bitrate_label);
	_gtk_tree_row_reference_free0 (self->priv->np_ref);
	_g_object_unref0 (self->priv->paned);
	_g_object_unref0 (self->priv->container);
	_g_free0 (self->priv->song_checksum);
	G_OBJECT_CLASS (gmpc_browsers_nowplaying_parent_class)->finalize (obj);
}
