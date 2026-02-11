gitg_config_accumulate (GitgShell   *shell,
                        gchar      **buffer,
                        GitgConfig *config)
{
	gchar **ptr = buffer;

	while (*ptr)
	{
		g_string_append (config->priv->accumulated, *ptr);
		++ptr;
	}
}
