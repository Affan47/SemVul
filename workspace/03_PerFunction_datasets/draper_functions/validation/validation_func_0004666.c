df_to_s(DocField *df)
{
    int i;
    int len = strlen(df->name) + 10;
    char *str, *s;
    for (i = 0; i < df->size; i++) {
        len += df->lengths[i] + 5;
    }
    s = str = ALLOC_N(char, len);
    sprintf(str, "%s: ", df->name);
    s += strlen(str);
    if (df->size == 1) {
        *(s++) = '"';
        strncpy(s, df->data[0], df->lengths[0]);
        s += df->lengths[0];
        *(s++) = '"';
        *(s++) = '\0';
    }
    else {
        *(s++) = '[';
        *(s++) = '"';
        strncpy(s, df->data[0], df->lengths[0]);
        s += df->lengths[0];
        *(s++) = '"';
        for (i = 1; i < df->size; i++) {
            *(s++) = ',';
            *(s++) = ' ';
            *(s++) = '"';
            strncpy(s, df->data[i], df->lengths[i]);
            s += df->lengths[i];
            *(s++) = '"';
        }
        sprintf(s, "]");
    }
    return str;
}
