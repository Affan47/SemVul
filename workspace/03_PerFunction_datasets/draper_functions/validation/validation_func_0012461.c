_libnm_glib_dbus_watcher (gpointer user_data)
{
	libnm_glib_ctx	*ctx = (libnm_glib_ctx *)user_data;

	g_return_val_if_fail (ctx != NULL, FALSE);

	ctx->dbus_watcher = 0;

	if (!ctx->dbus_con)
		ctx->dbus_con = _libnm_glib_dbus_init ((gpointer)ctx, ctx->g_main_ctx);

	if (ctx->dbus_con)
	{

		_libnm_glib_get_nm_state (ctx);
		ctx->dbus_watch_interval = 1000;
	}
	else
	{


		ctx->dbus_watch_interval = MIN(ctx->dbus_watch_interval + 3000, 60000);


		_libnm_glib_schedule_dbus_watcher (ctx);
	}

	return FALSE;
}
