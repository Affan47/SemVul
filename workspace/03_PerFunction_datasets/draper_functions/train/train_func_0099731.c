zbase_make_font(gs_font_dir * pdir, const gs_font * oldfont,
                const gs_matrix * pmat, gs_font ** ppfont)
{


    int code = gs_base_make_font(pdir, oldfont, pmat, ppfont);

    if (code < 0)
        return code;
    return zdefault_make_font(pdir, oldfont, pmat, ppfont);
}
