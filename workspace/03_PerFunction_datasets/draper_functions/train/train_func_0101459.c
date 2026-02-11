finalize (GObject *obj)
{
	AnjutaClassGenPlugin *cg_plugin;
	cg_plugin = ANJUTA_PLUGIN_CLASS_GEN (obj);
	g_free (cg_plugin->top_dir);

	if(cg_plugin->window != NULL)
		g_object_unref(G_OBJECT(cg_plugin->window));
	if(cg_plugin->generator != NULL)
		g_object_unref(G_OBJECT(cg_plugin->generator));

	G_OBJECT_CLASS (parent_class)->finalize (obj);
}
