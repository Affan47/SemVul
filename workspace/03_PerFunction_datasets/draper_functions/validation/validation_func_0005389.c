syncevo_source_statuses_foreach (SyncevoSourceStatuses *source_statuses,
                                 SourceStatusFunc func,
                                 gpointer data)
{
    GHashTableIter iter;
    GValueArray *source_status;

    char *name;

    g_return_if_fail (source_statuses);

    g_hash_table_iter_init (&iter, source_statuses);
    while (g_hash_table_iter_next (&iter, (gpointer)&name, (gpointer)&source_status)) {
        const char *mode_str;
        const char *status_str;
        SyncevoSyncMode mode;
        SyncevoSessionStatus status;
        guint error_code;

        mode_str = g_value_get_string (g_value_array_get_nth (source_status, 0));
        mode = syncevo_sync_mode_from_string (mode_str);

        status_str = g_value_get_string (g_value_array_get_nth (source_status, 1));
        status = syncevo_source_status_from_string (status_str);
        error_code = g_value_get_uint (g_value_array_get_nth (source_status, 2));

        func (name, mode, status, error_code, data);
    }
}
