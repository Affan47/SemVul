panel_applet_frame_dbus_load (const gchar                 *iid,
			      PanelAppletFrameActivating  *frame_act)
{
	PanelAppletFrameDBus *dbus_frame;
	PanelAppletFrame     *frame;
	GVariantBuilder       builder;
	GdkScreen            *screen;
	gchar                *settings_path;
	gchar                *conf_path;
	gchar                *background;
	guint                 orient;

	g_return_val_if_fail (iid != NULL, FALSE);
	g_return_val_if_fail (frame_act != NULL, FALSE);

	if (!panel_applets_manager_factory_activate (iid))
		return FALSE;

	dbus_frame = g_object_new (PANEL_TYPE_APPLET_FRAME_DBUS, NULL);
	frame = PANEL_APPLET_FRAME (dbus_frame);
	_panel_applet_frame_set_iid (frame, iid);

	screen = panel_applet_frame_activating_get_screen (frame_act);
	orient = get_panel_applet_orient (panel_applet_frame_activating_get_orientation (frame_act));
	settings_path = panel_applet_frame_activating_get_settings_path (frame_act);
	conf_path = panel_applet_frame_activating_get_conf_path (frame_act);


	background = NULL;

	g_variant_builder_init (&builder, G_VARIANT_TYPE ("a{sv}"));
	g_variant_builder_add (&builder, "{sv}",
			       "settings-path",
			       g_variant_new_string (settings_path));
	g_variant_builder_add (&builder, "{sv}",
			       "prefs-key",
			       g_variant_new_string (conf_path));
	g_variant_builder_add (&builder, "{sv}",
			       "orient",
			       g_variant_new_uint32 (orient));
	g_variant_builder_add (&builder, "{sv}",
			       "size",
			       g_variant_new_uint32 (panel_applet_frame_activating_get_size (frame_act)));
	g_variant_builder_add (&builder, "{sv}",
			       "locked-down",
			       g_variant_new_boolean (panel_applet_frame_activating_get_locked_down (frame_act)));
	if (background) {
		g_variant_builder_add (&builder, "{sv}",
				       "background",
				       g_variant_new_string (background));
	}

	g_object_set_data (G_OBJECT (frame), "panel-applet-frame-activating", frame_act);

	panel_applet_container_add (dbus_frame->priv->container,
				    screen, iid, NULL,
				    (GAsyncReadyCallback) panel_applet_frame_dbus_activated,
				    frame,
				    g_variant_builder_end (&builder));

	g_free (conf_path);
	g_free (settings_path);
	g_free (background);

	return TRUE;
}
