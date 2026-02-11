osinfo_install_script_generate_output_async(OsinfoInstallScript *script,
                                                 OsinfoOs *os,
                                                 OsinfoInstallConfig *config,
                                                 GFile *output_dir,
                                                 GCancellable *cancellable,
                                                 GAsyncReadyCallback callback,
                                                 gpointer user_data)
{
    const gchar *filename;
    const gchar *prefix;
    OsinfoInstallScriptGenerateOutputData *data =
        g_new0(OsinfoInstallScriptGenerateOutputData, 1);

    OsinfoInstallScriptGenerateSyncData *data_sync = user_data;

    data->res = g_simple_async_result_new(G_OBJECT(script),
                                          callback,
                                          user_data,
                                          osinfo_install_script_generate_output_async);

    data->cancellable = cancellable;
    data->error = data_sync->error;
    data->output = osinfo_install_script_generate(script,
                                                  os,
                                                  config,
                                                  cancellable,
                                                  &data->error);
    data->output_pos = 0;
    data->output_len = strlen(data->output);

    prefix =
        osinfo_install_script_get_output_prefix(script);
    filename =
        osinfo_install_script_get_output_filename(script);

    if (prefix) {
        gchar *output_filename  = g_strdup_printf("%s-%s", prefix, filename);
        data->file = g_file_get_child(output_dir, output_filename);
        g_free(output_filename);
    } else {
        data->file = g_file_get_child(output_dir, filename);
    }

    g_file_replace_async(data->file,
                         NULL,
                         TRUE,
                         G_FILE_CREATE_NONE,
                         G_PRIORITY_DEFAULT,
                         cancellable,
                         osinfo_install_script_generate_output_write_file,
                         data);
}
