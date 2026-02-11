gmpc_test_plugin_real_tool_menu_integration (GmpcPluginToolMenuIface* base, GtkMenu* menu) {
	GmpcTestPlugin * self;
	gint result = 0;
	const gchar* _tmp0_ = NULL;
	GtkMenuItem* _tmp1_;
	GtkMenuItem* _tmp2_;
	GtkMenuItem* item;
	GtkMenu* _tmp3_;
	self = (GmpcTestPlugin*) base;
	g_return_val_if_fail (menu != NULL, 0);
	_tmp0_ = _ ("Edit metadata current song");
	_tmp1_ = (GtkMenuItem*) gtk_menu_item_new_with_label (_tmp0_);
	_tmp2_ = g_object_ref_sink (_tmp1_);
	item = _tmp2_;
	_tmp3_ = menu;
	gtk_menu_shell_append ((GtkMenuShell*) _tmp3_, (GtkWidget*) item);
	g_signal_connect_object (item, "activate", (GCallback) _gmpc_test_plugin_menu_activated_album_gtk_menu_item_activate, self, 0);
	result = 2;
	_g_object_unref0 (item);
	return result;
}
