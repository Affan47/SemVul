server_config_update_from_entry (server_config *server, GtkEntry *entry)
{
    char **str;
    const char *new_str;


    str = g_object_get_data (G_OBJECT (entry), "value");
    g_assert (str);
    new_str = gtk_entry_get_text (entry);

    if ((*str == NULL && strlen (new_str) != 0) ||
        (*str != NULL && strcmp (*str, new_str) != 0)) {

        server->changed = TRUE;

        g_free (*str);
        *str = g_strdup (new_str);
    }
}
