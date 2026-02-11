cpl_polynomial_dump(const cpl_polynomial * p,
                                   FILE                 * stream)
{
    const cpl_error_code err = CPL_ERROR_FILE_IO;
    int i, dim;


    cpl_ensure_code(stream != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(p      != NULL, CPL_ERROR_NULL_INPUT);

    cpl_ensure_code( fprintf(stream,
        "#----- %" CPL_SIZE_FORMAT " dimensional polynomial -----\n", p->dim)
                     > 0, err);

    for (i=0; i < p->dim; i++)
        cpl_ensure_code(fprintf(stream, "%d.dim.power  ", i+1) > 0, err);

    cpl_ensure_code(fprintf(stream, "coefficient\n") > 0,  err);

    if (p->nc == 0) {
        for (dim=0; dim < p->dim; dim++)
            cpl_ensure_code(fprintf(stream, "  %5d      ", 0) > 0, err);

        cpl_ensure_code(fprintf(stream, "0\n") > 0,  err);
    }

    for (i=0; i < p->nc; i++) {
        if (p->dim == 1) {
            if (p->c[i] == 0.0) continue;
            cpl_ensure_code(fprintf(stream, "  %5d      ", i) > 0,  err);
        } else
            for (dim=0; dim < p->dim; dim++)
                cpl_ensure_code(fprintf(stream, "  %5" CPL_SIZE_FORMAT "      ",
                                        p->pow[p->dim * i + dim]) > 0, err);

        cpl_ensure_code(fprintf(stream, "%g\n", p->c[i]) > 0, err);

    }

    cpl_ensure_code(
        fprintf(stream, "#------------------------------------\n") > 0, err);

    return CPL_ERROR_NONE;
}
