scratchbox_plugin_dispose (GObject *obj)
{
	ScratchboxPlugin *plugin = ANJUTA_PLUGIN_SCRATCHBOX (obj);


	if (plugin->user_dir)
	{
		g_free (plugin->user_dir);
		plugin->user_dir = NULL;
	}

	g_object_unref (plugin->settings);

	G_OBJECT_CLASS (parent_class)->dispose (obj);
}
