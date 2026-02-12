rgb2l(UINT8 *out, const UINT8 *in, int xsize) {
    int x;
    for (x = 0; x < xsize; x++, in += 4) {

        *out++ = L24(in) >> 16;
    }
}
