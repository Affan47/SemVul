__ca_file_zeropad (sqlite3_context *context, int argc, sqlite3_value **argv)
{
        gchar * result = NULL;
        const gchar *value;
        int pad_size;
        gchar *aux = NULL;

        value = (const gchar *) sqlite3_value_text(argv[0]);
        pad_size = sqlite3_value_int (argv[1]);
        if (strlen(value) < pad_size) {
                aux = g_strnfill (pad_size - strlen(value),'0');
                result = g_strconcat (aux, value, NULL);
                g_free (aux);
        } else {
                result = g_strdup (value);
        }

        sqlite3_result_text (context, result, -1, g_free);
}
