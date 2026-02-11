caribou_iscannable_group_base_init (CaribouIScannableGroupIface * iface) {
	static gboolean initialized = FALSE;
	if (!initialized) {
		initialized = TRUE;
		g_object_interface_install_property (iface, g_param_spec_enum ("scan-grouping", "scan-grouping", "scan-grouping", CARIBOU_TYPE_SCAN_GROUPING, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
		g_signal_new ("selected_item_changed", CARIBOU_TYPE_ISCANNABLE_GROUP, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__OBJECT, G_TYPE_NONE, 1, CARIBOU_TYPE_ISCANNABLE_ITEM);
		g_signal_new ("step_item_changed", CARIBOU_TYPE_ISCANNABLE_GROUP, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__OBJECT, G_TYPE_NONE, 1, CARIBOU_TYPE_ISCANNABLE_ITEM);
		g_signal_new ("scan_cleared", CARIBOU_TYPE_ISCANNABLE_GROUP, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	}
}
