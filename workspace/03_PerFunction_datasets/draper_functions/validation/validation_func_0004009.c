_remove_comments(conffile_t cf, char *linebuf, int linebuflen)
{
    int i, newlen, previous_is_escape = 0, comment_remaining_buf = 0;


    i = 0;
    newlen = linebuflen;
    while (i < linebuflen) {
        if (comment_remaining_buf) {
            linebuf[i] = '\0';
            newlen--;
        }
        else if (linebuf[i] == '\\' && previous_is_escape == 0)
            previous_is_escape++;
        else if (linebuf[i] == '#' && previous_is_escape == 0) {
            linebuf[i] = '\0';
            comment_remaining_buf++;
            newlen--;
        }
        else if (previous_is_escape > 0)
            previous_is_escape = 0;
        i++;
    }

    return newlen;
}
