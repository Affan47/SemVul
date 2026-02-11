find_disc_centre_candidates(GArray *candidates,
                            PixelQueue *inqueue,
                            const guint *grain,
                            guint width, guint height,
                            gdouble dx, gdouble dy,
                            gdouble centrex, gdouble centrey)
{
    guint m;

    g_array_set_size(candidates, 0);
    for (m = 0; m < inqueue->len; m++) {
        GridPoint *mpt = inqueue->points + m;
        guint i = mpt->i, j = mpt->j, k = i*width + j, size = 8*grain[k], w;
        InscribedDisc cand;

        if (i && j && (w = grain[k - width-1]) != G_MAXUINT)
            size += w;
        if (i && (w = grain[k - width]) != G_MAXUINT)
            size += 2*w;
        if (i && j < width-1 && (w = grain[k - width+1]) != G_MAXUINT)
            size += w;
        if (j && (w = grain[k-1]) != G_MAXUINT)
            size += 2*w;
        if (j < width-1 && (w = grain[k+1]) != G_MAXUINT)
            size += 2*w;
        if (i < height-1 && j && (w = grain[k + width-1]) != G_MAXUINT)
            size += w;
        if (i < height-1 && (w = grain[k + width]) != G_MAXUINT)
            size += 2*w;
        if (i < height-1 && j < width-1 && (w = grain[k + width+1]) != G_MAXUINT)
            size += w;

        cand.x = (mpt->j + 0.5)*dx;
        cand.y = (mpt->i + 0.5)*dy;
        cand.size = size;


        cand.R2 = ((cand.x - centrex)*(cand.x - centrex)
                   + (cand.y - centrey)*(cand.y - centrey));
        g_array_append_val(candidates, cand);
    }
    g_array_sort(candidates, &compare_candidates);
}
