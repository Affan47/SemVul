_decodeStrip(Imaging im, ImagingCodecState state, TIFF *tiff) {
    INT32 strip_row;
    UINT8 *new_data;
    UINT32 rows_per_strip, row_byte_size;
    int ret;

    ret = TIFFGetField(tiff, TIFFTAG_ROWSPERSTRIP, &rows_per_strip);
    if (ret != 1) {
        rows_per_strip = state->ysize;
    }
    TRACE(("RowsPerStrip: %u \n", rows_per_strip));


    row_byte_size = (state->xsize * state->bits + 7) / 8;


    if (INT_MAX / row_byte_size < rows_per_strip) {
        state->errcode = IMAGING_CODEC_MEMORY;
        return -1;
    }

    state->bytes = rows_per_strip * row_byte_size;

    TRACE(("StripSize: %d \n", state->bytes));

    if (TIFFStripSize(tiff) > state->bytes) {


        state->errcode = IMAGING_CODEC_MEMORY;
        return -1;
    }


    new_data = realloc(state->buffer, state->bytes);
    if (!new_data) {
        state->errcode = IMAGING_CODEC_MEMORY;
        return -1;
    }

    state->buffer = new_data;

    for (; state->y < state->ysize; state->y += rows_per_strip) {
        if (TIFFReadEncodedStrip(
                tiff,
                TIFFComputeStrip(tiff, state->y, 0),
                (tdata_t)state->buffer,
                -1) == -1) {
            TRACE(("Decode Error, strip %d\n", TIFFComputeStrip(tiff, state->y, 0)));
            state->errcode = IMAGING_CODEC_BROKEN;
            return -1;
        }

        TRACE(("Decoded strip for row %d \n", state->y));


        for (strip_row = 0;
             strip_row < min((INT32)rows_per_strip, state->ysize - state->y);
             strip_row++) {
            TRACE(("Writing data into line %d ; \n", state->y + strip_row));


            state->shuffle(
                (UINT8 *)im->image[state->y + state->yoff + strip_row] +
                    state->xoff * im->pixelsize,
                state->buffer + strip_row * row_byte_size,
                state->xsize);
        }
    }
    return 0;
}
