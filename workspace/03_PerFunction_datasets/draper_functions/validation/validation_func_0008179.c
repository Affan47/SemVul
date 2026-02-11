languages_variant_init (const char *variant)
{
        GError  *error;
        gboolean res;
        char    *buf;
        gsize    buf_len;
        char    *filename;

        bindtextdomain (variant, ISO_CODES_LOCALESDIR);
        bind_textdomain_codeset (variant, "UTF-8");

        error = NULL;
        filename = g_strdup_printf (ISO_CODES_DATADIR "/%s.xml", variant);
        res = g_file_get_contents (filename,
                                   &buf,
                                   &buf_len,
                                   &error);
        if (res) {
                GMarkupParseContext *ctx;
                GMarkupParser        parser = { languages_parse_start_tag, NULL, NULL, NULL, NULL };

                ctx = g_markup_parse_context_new (&parser, 0, NULL, NULL);

                error = NULL;
                res = g_markup_parse_context_parse (ctx, buf, buf_len, &error);

                if (! res) {
                        g_warning ("Failed to parse '%s': %s\n",
                                   filename,
                                   error->message);
                        g_error_free (error);
                }

                g_markup_parse_context_free (ctx);
                g_free (buf);
        } else {
                g_warning ("Failed to load '%s': %s\n",
                           filename,
                           error->message);
                g_error_free (error);
        }

        g_free (filename);
}
