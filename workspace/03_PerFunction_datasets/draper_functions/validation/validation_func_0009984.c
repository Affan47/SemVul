on_gdl_style_changed(GSettings* settings, const gchar* key, gpointer user_data) {
    AnjutaWindow* win = ANJUTA_WINDOW (user_data);
    GdlSwitcherStyle style = GDL_SWITCHER_STYLE_BOTH;

    gchar* pr_style = g_settings_get_string(settings, key);

    if (g_strcmp0(pr_style, "Text") == 0)
        style = GDL_SWITCHER_STYLE_TEXT;
    else if (g_strcmp0(pr_style, "Icon") == 0)
        style = GDL_SWITCHER_STYLE_ICON;
    else if (g_strcmp0(pr_style, "Both") == 0)
        style = GDL_SWITCHER_STYLE_BOTH;
    else if (g_strcmp0(pr_style, "Toolbar") == 0)
        style = GDL_SWITCHER_STYLE_TOOLBAR;
    else if (g_strcmp0(pr_style, "Tabs") == 0)
        style = GDL_SWITCHER_STYLE_TABS;

#if (ANJUTA_CHECK_VERSION(3, 6, 2))
    g_object_set (gdl_dock_layout_get_master (win->layout_manager), "switcher-style",
                      style, NULL);
#else
    g_object_set(G_OBJECT(win->layout_manager->master), "switcher-style", style, NULL);
#endif

    g_free(pr_style);
}
