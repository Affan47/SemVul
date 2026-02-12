ImagingLibTiffEncode(Imaging im, ImagingCodecState state, UINT8 *buffer, int bytes) {


    TIFFSTATE *clientstate = (TIFFSTATE *)state->context;
    TIFF *tiff = clientstate->tiff;

    TRACE(("in encoder: bytes %d\n", bytes));
    TRACE(
        ("State: count %d, state %d, x %d, y %d, ystep %d\n",
         state->count,
         state->state,
         state->x,
         state->y,
         state->ystep));
    TRACE(
        ("State: xsize %d, ysize %d, xoff %d, yoff %d \n",
         state->xsize,
         state->ysize,
         state->xoff,
         state->yoff));
    TRACE(("State: bits %d, bytes %d \n", state->bits, state->bytes));
    TRACE(
        ("Buffer: %p: %c%c%c%c\n",
         buffer,
         (char)buffer[0],
         (char)buffer[1],
         (char)buffer[2],
         (char)buffer[3]));
    TRACE(
        ("State->Buffer: %c%c%c%c\n",
         (char)state->buffer[0],
         (char)state->buffer[1],
         (char)state->buffer[2],
         (char)state->buffer[3]));
    TRACE(
        ("Image: mode %s, type %d, bands: %d, xsize %d, ysize %d \n",
         im->mode,
         im->type,
         im->bands,
         im->xsize,
         im->ysize));
    TRACE(
        ("Image: image8 %p, image32 %p, image %p, block %p \n",
         im->image8,
         im->image32,
         im->image,
         im->block));
    TRACE(("Image: pixelsize: %d, linesize %d \n", im->pixelsize, im->linesize));

    dump_state(clientstate);

    if (state->state == 0) {
        TRACE(("Encoding line bt line"));
        while (state->y < state->ysize) {
            state->shuffle(
                state->buffer,
                (UINT8 *)im->image[state->y + state->yoff] +
                    state->xoff * im->pixelsize,
                state->xsize);

            if (TIFFWriteScanline(
                    tiff, (tdata_t)(state->buffer), (uint32)state->y, 0) == -1) {
                TRACE(("Encode Error, row %d\n", state->y));
                state->errcode = IMAGING_CODEC_BROKEN;
                TIFFClose(tiff);
                if (!clientstate->fp) {
                    free(clientstate->data);
                }
                return -1;
            }
            state->y++;
        }

        if (state->y == state->ysize) {
            state->state = 1;

            TRACE(("Flushing \n"));
            if (!TIFFFlush(tiff)) {
                TRACE(("Error flushing the tiff"));

                state->errcode = IMAGING_CODEC_MEMORY;
                TIFFClose(tiff);
                if (!clientstate->fp) {
                    free(clientstate->data);
                }
                return -1;
            }
            TRACE(("Closing \n"));
            TIFFClose(tiff);

            clientstate->loc = 0;
            clientstate->size = clientstate->eof;
        }
    }

    if (state->state == 1 && !clientstate->fp) {
        int read = (int)_tiffReadProc(clientstate, (tdata_t)buffer, (tsize_t)bytes);
        TRACE(
            ("Buffer: %p: %c%c%c%c\n",
             buffer,
             (char)buffer[0],
             (char)buffer[1],
             (char)buffer[2],
             (char)buffer[3]));
        if (clientstate->loc == clientstate->eof) {
            TRACE(("Hit EOF, calling an end, freeing data"));
            state->errcode = IMAGING_CODEC_END;
            free(clientstate->data);
        }
        return read;
    }

    state->errcode = IMAGING_CODEC_END;
    return 0;
}
