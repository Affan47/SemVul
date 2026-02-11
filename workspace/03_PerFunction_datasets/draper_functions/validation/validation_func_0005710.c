align_next(FILE * file, gint value)
{
    gint length, pos, align;


    value += !value;

    length = (int) log10f(value) + 2;
    pos = (int) ftell(file) + length;
    align = (4 - pos % 4) % 4;

    while (align > 0) {
        if (putc('0', file) < 0)
            return FALSE;

        align--;
    }

    return TRUE;
}
