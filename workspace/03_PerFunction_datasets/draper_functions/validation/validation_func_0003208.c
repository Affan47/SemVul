gs_setmatrix(gs_state * pgs, const gs_matrix * pmat)
{
    update_ctm(pgs, pmat->tx, pmat->ty);
    set_ctm_only(pgs, *pmat);
#ifdef DEBUG
    if (gs_debug_c('x'))
        dmlprintf(pgs->memory, "[x]setmatrix:\n"), trace_ctm(pgs);
#endif
    return 0;
}
