dsc_parse_document_media(CDSC *dsc)
{
    unsigned int i, n;
    CDSCMEDIA lmedia;
    GSBOOL blank_line;

    if (IS_DSC(dsc->line, "%%DocumentMedia:"))
        n = 16;
    else if (IS_DSC(dsc->line, "%%+"))
        n = 3;
    else
        return CDSC_ERROR;


    blank_line = TRUE;
    for (i=n; i<dsc->line_length; i++) {
        if (!IS_WHITE_OR_EOL(dsc->line[i])) {
            blank_line = FALSE;
            break;
        }
    }

    if (!blank_line) {
        char name[MAXSTR];
        char colour[MAXSTR];
        char type[MAXSTR];
        lmedia.name = lmedia.colour = lmedia.type = (char *)NULL;
        lmedia.width = lmedia.height = lmedia.weight = 0;
        lmedia.mediabox = (CDSCBBOX *)NULL;
        lmedia.name = dsc_copy_string(name, sizeof(name),
                dsc->line+n, dsc->line_length-n, &i);
        n+=i;
        if (i)
            lmedia.width = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
        n+=i;
        if (i)
            lmedia.height = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
        n+=i;
        if (i)
            lmedia.weight = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
        n+=i;
        if (i)
            lmedia.colour = dsc_copy_string(colour, sizeof(colour),
                dsc->line+n, dsc->line_length-n, &i);
        n+=i;
        if (i)
            lmedia.type = dsc_copy_string(type, sizeof(type),
                dsc->line+n, dsc->line_length-n, &i);

        if (i==0)
            dsc_unknown(dsc);
        else {
            if (dsc_add_media(dsc, &lmedia))
                return CDSC_ERROR;
        }
    }
    return CDSC_OK;
}
