zscalefont(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    int code;
    double scale;
    gs_matrix mat;

    if ((code = real_param(op, &scale)) < 0)
        return code;
    if ((code = gs_make_scaling(scale, scale, &mat)) < 0)
        return code;
    return make_font(i_ctx_p, &mat);
}
