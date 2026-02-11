file_plugin_proxy_export(GwyContainer *data,
                         const gchar *filename,
                         GwyRunType mode,
                         GError **error,
                         const gchar *name)
{
    FilePluginInfo *info;
    gchar *tmpname = NULL;
    GError *err = NULL;
    gint exit_status;
    FILE *fh;
    gchar *args[] = { NULL, NULL, NULL, NULL, NULL };
    GQuark dquark, mquark;
    gboolean ok;

    gwy_app_data_browser_get_current(GWY_APP_DATA_FIELD_KEY, &dquark,
                                     GWY_APP_MASK_FIELD_KEY, &mquark,
                                     0);

    gwy_debug("called as %s with file `%s'", name, filename);
    if (mode != GWY_RUN_INTERACTIVE) {
        g_set_error(error, GWY_MODULE_FILE_ERROR,
                    GWY_MODULE_FILE_ERROR_INTERACTIVE,
                    _("Plugin-proxy must be run as interactive."));
        return FALSE;
    }
    if (!(info = file_find_plugin(name, GWY_FILE_OPERATION_EXPORT))) {
        g_set_error(error, GWY_MODULE_FILE_ERROR,
                    GWY_MODULE_FILE_ERROR_UNIMPLEMENTED,
                    _("Plug-in `%s' does not implement file saving."), name);
        return FALSE;
    }

    fh = text_dump_export(data, dquark, mquark, &tmpname, error);
    if (!fh)
        return FALSE;

    args[0] = info->file;
    args[1] = g_strdup(gwy_enum_to_string(GWY_FILE_OPERATION_EXPORT,
                                          file_op_names, -1));
    args[2] = tmpname;
    args[3] = decode_glib_encoded_filename(filename);
    gwy_debug("%s %s %s %s", args[0], args[1], args[2], args[3]);
    ok = g_spawn_sync(NULL, args, NULL, 0, NULL, NULL,
                      NULL, NULL, &exit_status, &err);
    if (!ok) {
        g_set_error(error, GWY_MODULE_FILE_ERROR,
                    GWY_MODULE_FILE_ERROR_SPECIFIC,
                    _("Cannot execute plug-in `%s': %s."), name, err->message);
        g_clear_error(&err);
    }
    g_unlink(tmpname);
    fclose(fh);
    gwy_debug("ok = %d, exit_status = %d, err = %p", ok, exit_status, err);
    if (ok && exit_status) {
        g_set_error(error, GWY_MODULE_FILE_ERROR,
                    GWY_MODULE_FILE_ERROR_SPECIFIC,
                    _("Plug-in `%s' returned non-zero exit status: %d."),
                    name, exit_status);
        ok = FALSE;
    }
    g_free(args[1]);
    g_free(args[3]);
    g_free(tmpname);

    return ok;
}
