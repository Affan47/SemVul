shrink_pixel(dcraw_image_type pixp, int row, int col,
                                    dcraw_data *hh, unsigned *fseq, int scale)
    {
        unsigned sum[4], count[4];
        int ri, ci, cl;
        dcraw_image_type *ibase;

        memset(sum, 0, 4 * sizeof(unsigned));
        memset(count, 0, 4 * sizeof(unsigned));
        for (ri = 0; ri < scale; ++ri) {
            ibase = hh->raw.image + ((row * scale + ri) / 2) * hh->raw.width;
            for (ci = 0; ci < scale; ++ci) {
                cl = fcol_color(fseq[ri], col * scale + ci);
                sum[cl] += ibase[(col * scale + ci) / 2][cl];
                ++count[cl];
            }
        }
        for (cl = 0; cl < hh->raw.colors; ++cl)
            pixp[cl] = sum[cl] / count[cl];
    }
