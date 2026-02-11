hdrl_imagelist_get_iter_row_slices(const hdrl_imagelist * hlist,
                                                 cpl_size nrows,
                                                 int flags)
{
    cpl_ensure(hlist, CPL_ERROR_NULL_INPUT, NULL);
    cpl_ensure(hdrl_imagelist_get_size(hlist) > 0,
               CPL_ERROR_ILLEGAL_INPUT, NULL);

    hdrl_imagelist_row_slices_iter * state = cpl_malloc(sizeof(*state));
    state->hlist = hlist;
    state->ny = hdrl_image_get_size_y(hdrl_imagelist_get_const(hlist, 0));
    state->pos = 1;
    state->nrows = CX_MAX(nrows, 1);

    return hdrl_iter_init(hdrl_imagelist_row_slices_next, NULL, NULL,
                          HDRL_ITER_INPUT | HDRL_ITER_IMAGELIST, state);
}
