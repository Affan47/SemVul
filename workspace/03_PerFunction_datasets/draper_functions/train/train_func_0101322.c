close_wedge_median(patch_fill_state_t *pfs, wedge_vertex_list_t *l,
        const patch_color_t *c0, const patch_color_t *c1)
{
    int code;

    if (!l->last_side)
        return 0;
    code = fill_wedge_from_list(pfs, l, c1, c0);
    if (code < 0)
        return code;
    release_wedge_vertex_list_interval(pfs, l->beg, l->end);
    return 0;
}
