nm_urfkill_get_wwan_state (NMUrfkillManager *self)
{
	GVariant *state;
	gboolean enabled = TRUE;

	g_return_val_if_fail (self->wwan_proxy != NULL, enabled);

	state = g_dbus_proxy_get_cached_property (self->wwan_proxy, "state");

	if (state) {
		enabled = (g_variant_get_int32 (state) == 0);
		g_variant_unref (state);
	}

	return enabled;
}
