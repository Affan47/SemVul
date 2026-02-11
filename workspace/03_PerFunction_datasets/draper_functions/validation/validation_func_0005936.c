s_file_available(register stream * s, gs_offset_t *pl)
{
    gs_offset_t max_avail = s->file_limit - stell(s);
    gs_offset_t buf_avail = sbufavailable(s);

    *pl = min(max_avail, buf_avail);
    if (sseekable(s)) {
        gs_offset_t pos, end;

        pos = gp_ftell_64(s->file);
        if (gp_fseek_64(s->file, 0, SEEK_END))
            return ERRC;
        end = gp_ftell_64(s->file);
        if (gp_fseek_64(s->file, pos, SEEK_SET))
            return ERRC;
        buf_avail += end - pos;
        *pl = min(max_avail, buf_avail);
        if (*pl == 0)
            *pl = -1;
    } else {
        if (*pl == 0 && feof(s->file))
            *pl = -1;
    }
    return 0;
}
