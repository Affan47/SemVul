status_end_id_list(stream * s)
{
    if (*s->cursor.w.ptr != '\n')
        stputs(s, "\"\r\n");
}
