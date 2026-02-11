array_get_preedit_string(GString *preedit) {
    GString *result = g_string_new("");

    int i;
    for (i = 0; i < preedit->len; i++) {
        gchar c = preedit->str[i];
        int index = -1;

        if (c >= 'a' && c <= 'z') {
            index = c - 'a';
        }
        else if (c == ',') {
            index = 26;
        }
        else if (c == '.') {
            index = 27;
        }
        else if (c == '/') {
            index = 28;
        }
        else if (c == ';') {
            index = 29;
        }

        if (index >= 0) {
            g_string_append(result, valid_key_map[index]);
        }
    }

    return result;
}
