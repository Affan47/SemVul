_mpd_add_pad(mpd_mbstr_t *result, const mpd_spec_t *spec, uint32_t *status)
{
    if (result->nchars < spec->min_width) {
        mpd_ssize_t add_chars, add_bytes;
        size_t lpad = 0, rpad = 0;
        size_t n_fill, len, i, j;
        char align = spec->align;
        uint8_t err = 0;
        char *cp;

        n_fill = strlen(spec->fill);
        add_chars = (spec->min_width - result->nchars);

        add_bytes = add_chars * (mpd_ssize_t)n_fill;

        cp = result->data = mpd_realloc(result->data,
                                        result->nbytes+add_bytes+1,
                                        sizeof *result->data, &err);
        if (err) {
            *status |= MPD_Malloc_error;
            mpd_free(result->data);
            return 0;
        }

        if (align == 'z') {
            align = '=';
        }

        if (align == '<') {
            rpad = add_chars;
        }
        else if (align == '>' || align == '=') {
            lpad = add_chars;
        }
        else {
            lpad = add_chars/2;
            rpad = add_chars-lpad;
        }

        len = result->nbytes;
        if (align == '=' && (*cp == '-' || *cp == '+' || *cp == ' ')) {

            cp++; len--;
        }

        memmove(cp+n_fill*lpad, cp, len);
        for (i = 0; i < lpad; i++) {
            for (j = 0; j < n_fill; j++) {
                cp[i*n_fill+j] = spec->fill[j];
            }
        }
        cp += (n_fill*lpad + len);
        for (i = 0; i < rpad; i++) {
            for (j = 0; j < n_fill; j++) {
                cp[i*n_fill+j] = spec->fill[j];
            }
        }

        result->nbytes += add_bytes;
        result->nchars += add_chars;
        result->data[result->nbytes] = '\0';
    }

    return 1;
}
