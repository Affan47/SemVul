export_object (GDBusConnection *connection,
	       UnityWebappsIndicatorContext *indicator_context)
{
  GError *error;

  indicator_context->indicator_service_interface = unity_webapps_gen_indicator_skeleton_new ();

  g_signal_connect (indicator_context->indicator_service_interface,
		    "handle-show-indicator",
		    G_CALLBACK (on_handle_show_indicator),
		    indicator_context);
  g_signal_connect (indicator_context->indicator_service_interface,
		    "handle-clear-indicator",
		    G_CALLBACK (on_handle_clear_indicator),
		    indicator_context);
  g_signal_connect (indicator_context->indicator_service_interface,
		    "handle-clear-indicators",
		    G_CALLBACK (on_handle_clear_indicators),
		    indicator_context);
  g_signal_connect (indicator_context->indicator_service_interface,
		    "handle-set-property",
		    G_CALLBACK (on_handle_set_property),
		    indicator_context);
  g_signal_connect (indicator_context->indicator_service_interface,
		    "handle-set-property-icon",
		    G_CALLBACK (on_handle_set_property_icon),
		    indicator_context);
  g_signal_connect (indicator_context->indicator_service_interface,
		    "handle-add-action",
		    G_CALLBACK (on_handle_add_action),
		    indicator_context);
  g_signal_connect (indicator_context->indicator_service_interface,
		    "handle-remove-action",
		    G_CALLBACK (on_handle_remove_action),
		    indicator_context);
  g_signal_connect (indicator_context->indicator_service_interface,
		    "handle-remove-actions",
		    G_CALLBACK (on_handle_remove_actions),
		    indicator_context);

  error = NULL;

  g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (indicator_context->indicator_service_interface),
				    connection,
				    UNITY_WEBAPPS_INDICATOR_PATH,
				    &error);

  if (error != NULL)
    {
      g_error ("Error exporting Unity Webapps Indicator object: %s", error->message);

      g_error_free (error);

      return;
    }

  UNITY_WEBAPPS_NOTE (INDICATOR, "Exported Indicator object");

}
