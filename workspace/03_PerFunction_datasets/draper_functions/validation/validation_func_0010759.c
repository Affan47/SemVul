aes_get_wcs(struct aes *aes)
{
    wchar_t *w;
    int r;


    if (aes->aes_set & AES_SET_WCS)
        return (aes->aes_wcs);

    if (aes->aes_set & AES_SET_MBS) {


        size_t wcs_length = aes->aes_mbs.length;

        w = (wchar_t *)malloc((wcs_length + 1) * sizeof(wchar_t));
        if (w == NULL)
            __archive_errx(1, "No memory for aes_get_wcs()");
        r = mbstowcs(w, aes->aes_mbs.s, wcs_length);
        if (r > 0) {
            w[r] = 0;
            aes->aes_set |= AES_SET_WCS;
            return (aes->aes_wcs = w);
        }
        free(w);
    }

    if (aes->aes_set & AES_SET_UTF8) {

        aes->aes_wcs = __archive_string_utf8_w(&(aes->aes_utf8));
        if (aes->aes_wcs != NULL)
            aes->aes_set |= AES_SET_WCS;
        return (aes->aes_wcs);
    }
    return (NULL);
}
