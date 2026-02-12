txt_char_widths_to_uts(gs_font *font ,
                       txt_glyph_widths_t *pwidths)
{
    if (font && (font->FontType == ft_user_defined ||
        font->FontType == ft_PCL_user_defined ||
        font->FontType == ft_GL2_stick_user_defined ||
        font->FontType == ft_GL2_531)) {
        gs_matrix *pmat = &font->orig_FontMatrix;

        pwidths->Width.xy.x *= pmat->xx;
        pwidths->Width.xy.y  = 0.0;
        gs_distance_transform(pwidths->real_width.xy.x, pwidths->real_width.xy.y, pmat, &pwidths->real_width.xy);
    } else {


        pwidths->Width.xy.x /= 1000.0;
        pwidths->Width.xy.y /= 1000.0;
        pwidths->real_width.xy.x /= 1000.0;
        pwidths->real_width.xy.y /= 1000.0;
    }
}
