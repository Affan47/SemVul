cdffile_free(NetCDF *cdffile)
{
    gint i, j;


    for (i = 0; i < cdffile->ndims; i++)
        g_free(cdffile->dims[i].name);
    g_free(cdffile->dims);

    cdffile->ndims = 0;
    cdffile->dims = 0;


    for (i = 0; i < cdffile->nattrs; i++)
        g_free(cdffile->attrs[i].name);
    g_free(cdffile->attrs);

    cdffile->nattrs = 0;
    cdffile->attrs = 0;


    for (i = 0; i < cdffile->nvars; i++) {
        g_free(cdffile->vars[i].name);
        g_free(cdffile->vars[i].dimids);
        for (j = 0; j < cdffile->vars[i].nattrs; j++)
            g_free(cdffile->vars[i].attrs[j].name);
        g_free(cdffile->vars[i].attrs);

        cdffile->vars[i].nattrs = 0;
        cdffile->vars[i].attrs = 0;
    }
    g_free(cdffile->vars);

    cdffile->nvars = 0;
    cdffile->vars = 0;
}
