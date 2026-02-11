RmAPILPlugin
(	gpointer piname
,	gpointer plugin
,	gpointer notused
)
{
	PILPlugin*	Plugin = plugin;
	PILPluginType*	Pitype = Plugin->plugintype;

	PILValidatePlugin(piname, plugin, NULL);
	PILValidatePluginType(NULL, Pitype, NULL);
	g_assert(IS_PILPLUGIN(Plugin));

	if (DEBUGPLUGIN) {
		PILLog(PIL_DEBUG, "RmAPILPlugin(%s/%s)", Pitype->plugintype
		,	Plugin->plugin_name);
	}


	DelPILPlugin(plugin);
	DELETE(piname);
	return TRUE;
}
