ario_conf_get_string_slist (const char *key,
                            const char *string_value)
{
        ARIO_LOG_FUNCTION_START;
        const gchar *value = ario_conf_get (key);
        gchar **values;
        GSList *ret = NULL;
        int i;

        if (!value)
                value = string_value;

        if (!value)
                return NULL;

        values = g_strsplit ((const gchar *) value, ",", 0);

        for (i=0; values[i]!=NULL && g_utf8_collate (values[i], ""); ++i)
                ret = g_slist_append (ret, values[i]);

        g_free (values);

        return ret;
}
