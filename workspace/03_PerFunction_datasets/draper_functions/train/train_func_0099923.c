g_strjoinv (const gchar *separator, gchar **str_array)
{
        char *res;
        size_t slen, len, i;

        if (separator != NULL)
                slen = strlen (separator);
        else
                slen = 0;

        len = 0;
        for (i = 0; str_array [i] != NULL; i++){
                len += strlen (str_array [i]);
                len += slen;
        }
        if (len == 0)
                return g_strdup ("");
        if (slen > 0 && len > 0)
                len -= slen;
        len++;
        res = (char*)malloc (len);
        strcpy (res, str_array [0]);
        for (i = 1; str_array [i] != NULL; i++){
                if (separator != NULL)
                        strcat (res, separator);
                strcat (res, str_array [i]);
        }
        return res;
}
