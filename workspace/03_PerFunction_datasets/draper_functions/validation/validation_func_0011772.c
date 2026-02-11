panel_layout_append_group (GKeyFile    *keyfile,
                           const char  *group,
                           int          screen_for_toplevels,
                           gboolean     dry_run,
                           GError     **error)
{
        g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

        if (g_strcmp0 (group, "Toplevel") == 0 ||
            g_str_has_prefix (group, "Toplevel "))
                return panel_layout_append_group_helper (
                                        keyfile, group,
                                        screen_for_toplevels,
                                        "Toplevel",
                                        PANEL_LAYOUT_TOPLEVEL_ID_LIST_KEY,
                                        PANEL_TOPLEVEL_SCHEMA,
                                        PANEL_LAYOUT_TOPLEVEL_PATH,
                                        PANEL_LAYOUT_TOPLEVEL_DEFAULT_PREFIX,
                                        panel_layout_toplevel_keys,
                                        G_N_ELEMENTS (panel_layout_toplevel_keys),
                                        dry_run, error, "toplevel");
        else if (g_strcmp0 (group, "Object") == 0 ||
                 g_str_has_prefix (group, "Object "))
                return panel_layout_append_group_helper (
                                        keyfile, group,
                                        screen_for_toplevels,
                                        "Object",
                                        PANEL_LAYOUT_OBJECT_ID_LIST_KEY,
                                        PANEL_OBJECT_SCHEMA,
                                        PANEL_LAYOUT_OBJECT_PATH,
                                        PANEL_LAYOUT_OBJECT_DEFAULT_PREFIX,
                                        panel_layout_object_keys,
                                        G_N_ELEMENTS (panel_layout_object_keys),
                                        dry_run, error, "object");

        g_set_error (error, PANEL_LAYOUT_ERROR, 0,
                     "Unknown group '%s'", group);

        return FALSE;
}
