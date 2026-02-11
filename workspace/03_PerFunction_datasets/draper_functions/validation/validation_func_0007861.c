mud_tray_init (MudTray *tray)
{
	tray->priv = g_new0(MudTrayPrivate, 1);

	tray->priv->window = NULL;
	tray->priv->icon = NULL;
	tray->priv->window_invisible = FALSE;

        mud_tray_create(tray);
}
