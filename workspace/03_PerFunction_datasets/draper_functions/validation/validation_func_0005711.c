ufraw_despeckle(ufraw_data *uf, UFRawPhase phase)
{
    ufraw_image_data *img = &uf->Images[phase];
    const int depth = img->depth / 2, rowstride = img->rowstride / 2;
    int passes[4], pass, maxpass;
    int win[4], i, c, colors;
    guint16 *base;
    double decay[4];

    ufraw_image_format(&colors, NULL, img, "68", G_STRFUNC);
    maxpass = 0;
    for (c = 0; c < colors; ++c) {
        win[c] = uf->conf->despeckleWindow[c < 3 ? c : 1] + 0.01;
        decay[c] = uf->conf->despeckleDecay[c < 3 ? c : 1];
        passes[c] = uf->conf->despecklePasses[c < 3 ? c : 1] + 0.01;
        if (!win[c])
            passes[c] = 0;
        if (passes[c] > maxpass)
            maxpass = passes[c];
    }
    progress(PROGRESS_DESPECKLE, -maxpass * colors);
    for (pass = maxpass - 1; pass >= 0; --pass) {
        for (c = 0; c < colors; ++c) {
            progress(PROGRESS_DESPECKLE, 1);
            if (pass >= passes[c])
                continue;
#ifdef _OPENMP
            #pragma omp parallel for default(shared) private(i,base)
#endif
            for (i = 0; i < img->height; ++i) {
                base = (guint16 *)img->buffer + i * rowstride;
                ufraw_despeckle_line(base, depth, img->width, win[c],
                                     decay[c], colors, c);
            }
#ifdef _OPENMP
            #pragma omp parallel for default(shared) private(i,base)
#endif
            for (i = 0; i < img->width; ++i) {
                base = (guint16 *)img->buffer + i * depth;
                ufraw_despeckle_line(base, rowstride, img->height, win[c],
                                     decay[c], colors, c);
            }
        }
    }
}
