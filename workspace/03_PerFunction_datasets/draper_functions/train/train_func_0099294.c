entry_insert_numeric(GtkWidget *entry, gchar *text, gint length)
{
        gint count;

        if (length == -1)
                length = strlen(text);
        count = 0;
        while (count < length) {
                if (!isdigit(*(text + count)) && !(*(text + count) == '.')) {
                        g_signal_stop_emission_by_name(entry, "insert-text");
                        return;
                }
                count++;
        }
}
