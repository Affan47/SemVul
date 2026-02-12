define_gs_font(i_ctx_t *i_ctx_p, gs_font * pfont)
{
    return (pfont->base == pfont && pfont->dir == 0 ?

            gs_definefont(ifont_dir, pfont) :
            0);
}
