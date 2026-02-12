static void ok_png_decode_filter(uint8_t * RESTRICT curr, const uint8_t * RESTRICT prev,
                                 size_t length, int filter, uint8_t bpp) {
    switch (filter) {
        case OK_PNG_FILTER_NONE:

            break;
        case OK_PNG_FILTER_SUB: {


            for (size_t i = bpp; i < length; i++) {
                curr[i] = curr[i] + curr[i - bpp];
            }
            break;
        }
        case OK_PNG_FILTER_UP: {


            for (size_t i = 0; i < length; i++) {
                curr[i] = curr[i] + prev[i];
            }
            break;
        }
        case OK_PNG_FILTER_AVG: {


            for (size_t i = 0; i < bpp; i++) {
                curr[i] = curr[i] + (prev[i] >> 1);
            }
            for (size_t j = bpp; j < length; j++) {
                curr[j] = curr[j] + ((curr[j - bpp] + prev[j]) >> 1);
            }
            break;
        }
        case OK_PNG_FILTER_PAETH: {


            for (size_t i = 0; i < bpp; i++) {
                curr[i] += prev[i];
            }
            for (size_t j = bpp; j < length; j++) {
                curr[j] += ok_png_paeth_predictor(curr[j - bpp], prev[j], prev[j - bpp]);
            }
            break;
        }
    }
}
