gs_screen_order_init_memory(gx_ht_order * porder, const gs_state * pgs,
                            gs_screen_halftone * phsp, bool accurate,
                            gs_memory_t * mem)
{
    gs_matrix imat;
    ulong max_size = gx_ht_cache_default_bits_size();
    int code;
    gs_lib_ctx_t *ctx = gs_lib_ctx_get_interp_instance(mem);

    if (phsp->frequency < 0.1)
        return_error(gs_error_rangecheck);
    gs_deviceinitialmatrix(gs_currentdevice(pgs), &imat);
    code = pick_cell_size(phsp, &imat, max_size,
                          ctx->screen_min_screen_levels, accurate,
                          &porder->params);
    if (code < 0)
        return code;
    gx_compute_cell_values(&porder->params);
    porder->screen_params.matrix = imat;
    porder->screen_params.max_size = max_size;
    return gs_screen_order_alloc(porder, mem);
}
