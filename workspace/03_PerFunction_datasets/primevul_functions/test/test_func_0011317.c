qf_parse_line_nomatch(char_u *linebuf, int linelen, qffields_T *fields)
{
    fields->namebuf[0] = NUL;
    fields->lnum = 0;
    fields->valid = FALSE;

    return copy_nonerror_line(linebuf, linelen, fields);
}
