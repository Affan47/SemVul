bits_replicate_horizontally(byte * data, uint width, uint height,
                 uint raster, uint replicated_width, uint replicated_raster)
{

    const byte *orig_row = data + (height - 1) * raster;
    byte *tile_row = data + (height - 1) * replicated_raster;
    uint y;

    if (!(width & 7)) {
        uint src_bytes = width >> 3;
        uint dest_bytes = replicated_width >> 3;

        for (y = height; y-- > 0;
             orig_row -= raster, tile_row -= replicated_raster
             ) {
            uint move = src_bytes;
            const byte *from = orig_row;
            byte *to = tile_row + dest_bytes - src_bytes;

            memmove(to, from, move);
            while (to - tile_row >= move) {
                from = to;
                to -= move;
                memmove(to, from, move);
                move <<= 1;
            }
            if (to != tile_row)
                memmove(tile_row, to, to - tile_row);
        }
    } else {


        uint bit_count = width & (uint)(-(int)width);
        uint left_mask = (0xff00 >> bit_count) & 0xff;

        for (y = height; y-- > 0;
             orig_row -= raster, tile_row -= replicated_raster
             ) {
            uint sx;

            for (sx = width; sx > 0;) {
                uint bits, dx;

                sx -= bit_count;
                bits = (orig_row[sx >> 3] << (sx & 7)) & left_mask;
                for (dx = sx + replicated_width; dx >= width;) {
                    byte *dp;
                    int dbit;

                    dx -= width;
                    dbit = dx & 7;
                    dp = tile_row + (dx >> 3);
                    *dp = (*dp & ~(left_mask >> dbit)) | (bits >> dbit);
                }
            }
        }
    }
}
