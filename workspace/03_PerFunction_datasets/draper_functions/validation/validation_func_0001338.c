bluetooth_plugin_dir_process (const char *plugindir)
{
	GDir *dir;
	const char *item;
	GbtPlugin *p = NULL;
	GError *err = NULL;
	gboolean (*gbt_init_plugin)(GbtPlugin *p);

	dir = g_dir_open (plugindir, 0, &err);

	if (dir == NULL) {
		g_warning ("Can't open the plugins dir: %s", err ? err->message : "No reason");
		if (err)
			g_error_free (err);
	} else {
		while ((item = g_dir_read_name(dir))) {
			if (g_str_has_suffix (item, "." G_MODULE_SUFFIX)) {
				char *module_path;

				p = g_new0(GbtPlugin, 1);
				module_path = g_module_build_path (plugindir, item);
				p->module = g_module_open (module_path, G_MODULE_BIND_LAZY);
				if (!p->module) {
					g_warning ("error opening %s: %s", module_path, g_module_error ());
					g_free (module_path);
					continue;
				}
				g_free (module_path);

				if (!g_module_symbol (p->module, "gbt_init_plugin", (gpointer *) &gbt_init_plugin)) {
					g_warning ("error: %s", g_module_error ());
					g_module_close (p->module);
					continue;
				}

				gbt_init_plugin (p);

				plugin_list = g_list_append (plugin_list, p);
			}
		}
		g_dir_close (dir);
	}
}
