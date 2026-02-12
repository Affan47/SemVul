status_put_id(stream * s, const char *title, const char *id)
{
    if (*s->cursor.w.ptr == '\n') {
        stprintf(s, "%s=\"%s", title, id);
    } else {
        stprintf(s, ",%s", id);
    }
}
