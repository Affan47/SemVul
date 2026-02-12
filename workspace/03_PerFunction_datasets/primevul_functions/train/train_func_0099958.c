float txt_calculate_text_size(gs_gstate *pgs, gs_font *ofont,
                              const gs_matrix *pfmat, gs_matrix *smat, gs_matrix *tmat,
                              gs_font *font, gx_device *pdev)
{
    gs_matrix orig_matrix;
    double
        sx = pdev->HWResolution[0] / 72.0,
        sy = pdev->HWResolution[1] / 72.0;
    float size;


    txtwrite_font_orig_matrix(ofont, -1, &orig_matrix);


    if (gs_matrix_invert(&orig_matrix, smat) < 0) {
        gs_make_identity(smat);
        return 1;
    }
    gs_matrix_multiply(smat, pfmat, smat);
    *tmat = ctm_only(pgs);
    tmat->tx = tmat->ty = 0;
    gs_matrix_multiply(smat, tmat, tmat);


    size = hypot(tmat->yx, tmat->yy) / sy;
    if (size < 0.01)
        size = hypot(tmat->xx, tmat->xy) / sx;
    if (size < 0.01)
        size = 1;

    return(size);
}
