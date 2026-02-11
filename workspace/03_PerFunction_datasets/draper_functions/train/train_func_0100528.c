dvcman_register_plugin(IDRDYNVC_ENTRY_POINTS* pEntryPoints,
	const char* name, IWTSPlugin* pPlugin)
{
	DVCMAN* dvcman = ((DVCMAN_ENTRY_POINTS*)pEntryPoints)->dvcman;

	if (dvcman->num_plugins < MAX_PLUGINS)
	{
		DEBUG_DVC("num_plugins %d", dvcman->num_plugins);
		dvcman->plugin_names[dvcman->num_plugins] = name;
		dvcman->plugins[dvcman->num_plugins++] = pPlugin;
		return 0;
	}
	else
	{
		DEBUG_WARN("Maximum DVC plugin number reached.");
		return 1;
	}
}
