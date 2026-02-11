contacts_list_pane_filter_entry_changed (ContactsListPane* self, GtkEditable* editable) {
	guint _tmp0_ = 0U;
	guint _tmp2_ = 0U;
	GtkEntry* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (editable != NULL);
	_tmp0_ = self->priv->filter_entry_changed_id;
	if (_tmp0_ != ((guint) 0)) {
		guint _tmp1_ = 0U;
		_tmp1_ = self->priv->filter_entry_changed_id;
		g_source_remove (_tmp1_);
	}
	_tmp2_ = g_timeout_add_full (G_PRIORITY_DEFAULT, (guint) 300, _contacts_list_pane_filter_entry_changed_timeout_gsource_func, g_object_ref (self), g_object_unref);
	self->priv->filter_entry_changed_id = _tmp2_;
	_tmp3_ = self->filter_entry;
	_tmp4_ = gtk_entry_get_text (_tmp3_);
	if (g_strcmp0 (_tmp4_, "") == 0) {
		GtkEntry* _tmp5_ = NULL;
		_tmp5_ = self->filter_entry;
		gtk_entry_set_icon_from_icon_name (_tmp5_, GTK_ENTRY_ICON_SECONDARY, "edit-find-symbolic");
	} else {
		GtkEntry* _tmp6_ = NULL;
		_tmp6_ = self->filter_entry;
		gtk_entry_set_icon_from_icon_name (_tmp6_, GTK_ENTRY_ICON_SECONDARY, "edit-clear-symbolic");
	}
}
