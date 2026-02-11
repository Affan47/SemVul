properties_load (EyesApplet *eyes_applet)
{
        gchar *theme_path = NULL;

	theme_path = panel_applet_gconf_get_string (
		eyes_applet->applet, "theme_path", NULL);

	if (theme_path == NULL)
		theme_path = g_strdup (GEYES_THEMES_DIR "Default-tiny");

        if (load_theme (eyes_applet, theme_path) == FALSE) {
		g_free (theme_path);

		return FALSE;
	}

        g_free (theme_path);

	return TRUE;
}
