obt_prop_set_array_text(Window win, Atom prop, const gchar *const *strs)
{
    GString *str;
    gchar const *const *s;

    str = g_string_sized_new(0);
    for (s = strs; *s; ++s) {
        str = g_string_append(str, *s);
        str = g_string_append_c(str, '\0');
    }
    XChangeProperty(obt_display, win, prop, OBT_PROP_ATOM(UTF8_STRING), 8,
                    PropModeReplace, (guchar*)str->str, str->len);
    g_string_free(str, TRUE);
}
