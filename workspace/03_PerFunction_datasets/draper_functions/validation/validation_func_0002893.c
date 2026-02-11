parse_env(void)
{
    const gchar *id;


    g_unsetenv("DESKTOP_STARTUP_ID");


    id = g_getenv("DESKTOP_AUTOSTART_ID");
    if (id) {
        g_unsetenv("DESKTOP_AUTOSTART_ID");
        if (ob_sm_id) g_free(ob_sm_id);
        ob_sm_id = g_strdup(id);
        ob_debug_type(OB_DEBUG_SM,
                      "DESKTOP_AUTOSTART_ID %s supercedes --sm-client-id\n",
                      ob_sm_id);
    }
}
