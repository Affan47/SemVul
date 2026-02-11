unpremultiply_data (png_structp png, png_row_infop row_info, png_bytep data)
{
        unsigned int i;

        for (i = 0; i < row_info->rowbytes; i += 4) {
                uint8_t *b = &data[i];
                uint32_t pixel;
                uint8_t  alpha;

                memcpy (&pixel, b, sizeof (uint32_t));
                alpha = (pixel & 0xff000000) >> 24;
                if (alpha == 0) {
                        b[0] = b[1] = b[2] = b[3] = 0;
                } else {
                        b[0] = (((pixel & 0xff0000) >> 16) * 255 + alpha / 2) / alpha;
                        b[1] = (((pixel & 0x00ff00) >>  8) * 255 + alpha / 2) / alpha;
                        b[2] = (((pixel & 0x0000ff) >>  0) * 255 + alpha / 2) / alpha;
                        b[3] = alpha;
                }
        }
}
