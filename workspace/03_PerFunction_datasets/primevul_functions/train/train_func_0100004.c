txtwrite_font_orig_matrix(const gs_font *font, gs_glyph cid, gs_matrix *pmat)
{
    int code;

    switch (font->FontType) {
    case ft_composite:
    case ft_TrueType:
    case ft_CID_TrueType:

        gs_make_identity(pmat);
        return 0;
    case ft_encrypted:
    case ft_encrypted2:
    case ft_CID_encrypted:
    case ft_user_defined:
    case ft_PCL_user_defined:
    case ft_GL2_stick_user_defined:
    case ft_GL2_531:


        {
            const gs_font *base_font = font;

            while (base_font->base != base_font)
                base_font = base_font->base;
            if (font->FontType == ft_user_defined ||
                font->FontType == ft_PCL_user_defined ||
                font->FontType == ft_GL2_stick_user_defined ||
                font->FontType == ft_GL2_531)
                *pmat = base_font->FontMatrix;
            else if (base_font->orig_FontMatrix.xx != 0 || base_font->orig_FontMatrix.xy != 0 ||
                base_font->orig_FontMatrix.yx != 0 || base_font->orig_FontMatrix.yy != 0)
                *pmat = base_font->orig_FontMatrix;
            else {


                if (base_font->FontMatrix.xx == 1.0/2048 &&
                    base_font->FontMatrix.xy == 0 &&
                    base_font->FontMatrix.yx == 0 &&
                    any_abs(base_font->FontMatrix.yy) == 1.0/2048
                    )
                    *pmat = base_font->FontMatrix;
                else
                    gs_make_scaling(0.001, 0.001, pmat);
            }
        }
        if (font->FontType == ft_CID_encrypted && cid != -1) {
            int fidx;

            if (cid < GS_MIN_CID_GLYPH)
                cid = GS_MIN_CID_GLYPH;
            code = ((gs_font_cid0 *)font)->cidata.glyph_data((gs_font_base *)font,
                                cid, NULL, &fidx);
            if (code < 0) {
                code = ((gs_font_cid0 *)font)->cidata.glyph_data((gs_font_base *)font,
                                (gs_glyph)GS_MIN_CID_GLYPH, NULL, &fidx);
            }
            if (code >= 0) {
                gs_matrix_multiply(&(gs_cid0_indexed_font(font, fidx)->FontMatrix),
                                pmat, pmat);
            }
        }
        return 0;
    default:
        return_error(gs_error_rangecheck);
    }
}
