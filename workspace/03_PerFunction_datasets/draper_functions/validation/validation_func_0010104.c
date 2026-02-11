set_mm_enabled (NMModem *self, gboolean enabled)
{


	dbus_g_proxy_begin_call (nm_modem_generic_get_proxy (NM_MODEM_GENERIC (self),
	                                                     MM_OLD_DBUS_INTERFACE_MODEM),
	                         "Enable", set_mm_enabled_done,
	                         self, NULL,
	                         G_TYPE_BOOLEAN, enabled,
	                         G_TYPE_INVALID);

	if (!enabled)
		update_mm_enabled (self, enabled);
}
