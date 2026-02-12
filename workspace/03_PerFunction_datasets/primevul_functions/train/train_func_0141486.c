rgb2bit(UINT8 *out, const UINT8 *in, int xsize) {
    int x;
    for (x = 0; x < xsize; x++, in += 4) {

        *out++ = (L(in) >= 128000) ? 255 : 0;
    }
}
