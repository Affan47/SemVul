cs_adjust_counts_icc(gs_state *pgs, int delta)
{
    gs_color_space *pcs = gs_currentcolorspace_inline(pgs);

    if (pcs) {
        cs_adjust_counts(pgs, delta);
    }
}
