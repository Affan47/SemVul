pk_control_can_authorize_async (PkControl *control,
				const gchar *action_id,
				GCancellable *cancellable,
				GAsyncReadyCallback callback,
				gpointer user_data)
{
	GSimpleAsyncResult *res;
	PkControlState *state;
	GError *error = NULL;

	g_return_if_fail (PK_IS_CONTROL (control));
	g_return_if_fail (callback != NULL);
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

	res = g_simple_async_result_new (G_OBJECT (control),
					 callback,
					 user_data,
					 pk_control_can_authorize_async);


	state = g_slice_new0 (PkControlState);
	state->res = g_object_ref (res);
	state->control = g_object_ref (control);
	state->parameters = g_variant_new ("(s)", action_id);
	g_variant_ref_sink (state->parameters);
	if (cancellable != NULL)
		state->cancellable = g_object_ref (cancellable);


	if (cancellable != NULL &&
	    g_cancellable_set_error_if_cancelled (cancellable, &error)) {
		pk_control_can_authorize_state_finish (state, error);
		g_error_free (error);
		goto out;
	}
	state->authorize = PK_AUTHORIZE_ENUM_UNKNOWN;


	if (control->priv->proxy != NULL) {
		pk_control_can_authorize_internal (state);
	} else {
		g_dbus_proxy_new_for_bus (G_BUS_TYPE_SYSTEM,
					  G_DBUS_PROXY_FLAGS_NONE,
					  NULL,
					  PK_DBUS_SERVICE,
					  PK_DBUS_PATH,
					  PK_DBUS_INTERFACE,
					  control->priv->cancellable,
					  pk_control_can_authorize_proxy_cb,
					  state);
	}


	g_ptr_array_add (control->priv->calls, state);
out:
	g_object_unref (res);
}
