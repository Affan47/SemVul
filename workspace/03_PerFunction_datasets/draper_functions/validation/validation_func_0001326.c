gx_provide_fm_pair_attributes(gs_font_dir * dir,
               gs_font *font, cached_fm_pair *pair,
               const gs_matrix * char_tm, const gs_log2_scale_point *log2_scale,
               bool design_grid)
{
    if (does_font_need_tt_interpreter(font)) {
        if (pair->ttf != NULL)
            return 0;
        return gx_attach_tt_interpreter(dir, (gs_font_type42 *)font, pair,
                        char_tm, log2_scale, design_grid);
    }
    return 0;
}
