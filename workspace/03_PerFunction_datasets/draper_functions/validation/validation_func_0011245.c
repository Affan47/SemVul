copy_settings (GtkButton *button, GtkBuilder *dialog)
{
        const gchar *language;
        const gchar *region;
        const gchar *layout;
        const gchar *variants;
        GtkWidget *label;
        GVariantBuilder *b;
        gchar *s;
        gchar *command;
        gchar *lang;
        GError *error = NULL;
        gint i;

        label = WID ("user_display_language");
        language = g_object_get_data (G_OBJECT (label), "language");
        label = WID ("user_format");
        region = g_object_get_data (G_OBJECT (label), "region");


        command = g_strconcat ("/usr/share/language-tools/language2locale ", language, NULL);
        if (!g_spawn_command_line_sync (command, &lang, NULL, NULL, &error)) {
                g_warning ("Couldn't get LANG locale: %s", error->message);
                g_error_free (error);
                g_free (command);
                return;
        }
        g_free (command);
        g_strchomp (lang);
        if (strlen (lang) == 0) {
                g_warning ("Couldn't get LANG locale -- Copying interrupted");
                return;
        }

        b = g_variant_builder_new (G_VARIANT_TYPE ("as"));
        s = g_strconcat ("LANG=", lang, NULL);
        g_variant_builder_add (b, "s", s);
        g_free (lang);
        g_free (s);
        s = g_strconcat ("LANGUAGE=", language, NULL);
        g_variant_builder_add (b, "s", s);
        g_free (s);
        const gchar *format_categories[] = { "LC_NUMERIC", "LC_TIME",
           "LC_MONETARY", "LC_PAPER", "LC_IDENTIFICATION", "LC_NAME",
           "LC_ADDRESS", "LC_TELEPHONE", "LC_MEASUREMENT", NULL };
        for (i = 0; format_categories[i] != NULL; i++) {
                s = g_strconcat (format_categories[i], "=", region, NULL);
                g_variant_builder_add (b, "s", s);
                g_free (s);
        }

        g_dbus_proxy_call (localed_proxy,
                           "SetLocale",
                           g_variant_new ("(asb)", b, TRUE),
                           G_DBUS_CALL_FLAGS_NONE,
                           -1, NULL, NULL, NULL);
        g_variant_builder_unref (b);

        label = WID ("user_input_source");
        layout = g_object_get_data (G_OBJECT (label), "input_source");
        variants = g_object_get_data (G_OBJECT (label), "input_variants");

        if (layout == NULL || layout[0] == '\0') {
                g_debug ("Not calling SetX11Keyboard, as there are no XKB input sources in the user's settings");
                return;
        }

        g_dbus_proxy_call (localed_proxy,
                           "SetX11Keyboard",
                           g_variant_new ("(ssssbb)", layout, "", variants ? variants : "", "", TRUE, TRUE),
                           G_DBUS_CALL_FLAGS_NONE,
                           -1, NULL, NULL, NULL);
}
