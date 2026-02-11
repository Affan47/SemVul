vbrpsy_compute_fft_s(lame_internal_flags const *gfc, const sample_t * const buffer[2], int chn,
                     int sblock, FLOAT(*fftenergy_s)[HBLKSIZE_s], FLOAT(*wsamp_s)[3][BLKSIZE_s])
{
    int     j;

    if (sblock == 0 && chn < 2) {
        fft_short(gfc, *wsamp_s, chn, buffer);
    }
    if (chn == 2) {
        FLOAT const sqrt2_half = SQRT2 * 0.5f;

        for (j = BLKSIZE_s - 1; j >= 0; --j) {
            FLOAT const l = wsamp_s[0][sblock][j];
            FLOAT const r = wsamp_s[1][sblock][j];
            wsamp_s[0][sblock][j] = (l + r) * sqrt2_half;
            wsamp_s[1][sblock][j] = (l - r) * sqrt2_half;
        }
    }


    fftenergy_s[sblock][0] = (*wsamp_s)[sblock][0];
    fftenergy_s[sblock][0] *= fftenergy_s[sblock][0];
    for (j = BLKSIZE_s / 2 - 1; j >= 0; --j) {
        FLOAT const re = (*wsamp_s)[sblock][BLKSIZE_s / 2 - j];
        FLOAT const im = (*wsamp_s)[sblock][BLKSIZE_s / 2 + j];
        fftenergy_s[sblock][BLKSIZE_s / 2 - j] = (re * re + im * im) * 0.5f;
    }
}
