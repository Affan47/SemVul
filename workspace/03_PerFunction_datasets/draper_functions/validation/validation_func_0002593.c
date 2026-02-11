gwy_app_recent_file_list_filter_apply(GtkEntry *entry,
                                      Controls *controls)
{
    GPatternSpec *oldpattern;
    GwyContainer *settings;
    gchar *s, *t;

    settings = gwy_app_settings_get();
    g_string_assign(controls->glob, gtk_entry_get_text(entry));
    gwy_container_set_string_by_name(settings, "/app/file/recent/glob",
                                     g_strdup(controls->glob->str));

    oldpattern = controls->pattern;

    if (controls->casesens) {
        if (!strchr(controls->glob->str, '*')
            && !strchr(controls->glob->str, '?'))
            s = g_strconcat("*", controls->glob->str, "*", NULL);
        else
            s = g_strdup(controls->glob->str);
    }
    else {

        s = g_utf8_strdown(controls->glob->str, controls->glob->len);
        if (!strchr(s, '*') && !strchr(s, '?')) {
            t = s;
            s = g_strconcat("*", t, "*", NULL);
            g_free(t);
        }
    }
    controls->pattern = g_pattern_spec_new(s);
    g_free(s);

    if (oldpattern)
        g_pattern_spec_free(oldpattern);

    if (GTK_WIDGET_REALIZED(controls->window))
        gwy_app_wait_cursor_start(GTK_WINDOW(controls->window));
    gtk_tree_model_filter_refilter(GTK_TREE_MODEL_FILTER(controls->filter));
    if (GTK_WIDGET_REALIZED(controls->window))
        gwy_app_wait_cursor_finish(GTK_WINDOW(controls->window));
}
