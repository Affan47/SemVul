spice_convert_newlines(const gchar *str, gssize len,
                                     NewlineType from,
                                     NewlineType to,
                                     GError **error)
{
    GError *err = NULL;
    gssize length;
    gsize nl;
    GString *output;
    gboolean free_segment = FALSE;
    gint i;

    g_return_val_if_fail(str != NULL, NULL);
    g_return_val_if_fail(len >= -1, NULL);
    g_return_val_if_fail(error == NULL || *error == NULL, NULL);

    g_return_val_if_fail((from == NEWLINE_TYPE_LF &&
                          to == NEWLINE_TYPE_CR_LF) ||
                         (from == NEWLINE_TYPE_CR_LF &&
                          to == NEWLINE_TYPE_LF), NULL);

    if (len == -1)
        len = strlen(str);


    else if (len > 0 && str[len-1] == 0)
        len -= 1;


    output = g_string_sized_new(len * 2 + 1);

    for (i = 0; i < len; i += length + nl) {
        length = get_line(str + i, len - i, from, &nl, error);
        if (length < 0)
            break;

        g_string_append_len(output, str + i, length);

        if (nl) {

            if (to == NEWLINE_TYPE_CR_LF &&
                output->str[output->len - 1] != '\r')
                g_string_append_c(output, '\r');

            g_string_append_c(output, '\n');
        }
    }

    if (err) {
        g_propagate_error(error, err);
        free_segment = TRUE;
    }

    return g_string_free(output, free_segment);
}
