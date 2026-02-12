make_str_kind(const char *raw) {

    char *ch, s_kind[3] = {0, 0, 0};
    ch = s_kind;
    while (*raw && *raw != '\'' && *raw != '"') {
        *ch++ = *raw++;
    }
    return PyUnicode_FromString(s_kind);
}
