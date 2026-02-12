ImagingFliDecode(Imaging im, ImagingCodecState state, UINT8 *buf, Py_ssize_t bytes) {
    UINT8 *ptr;
    int framesize;
    int c, chunks, advance;
    int l, lines;
    int i, j, x = 0, y, ymax;


    if (bytes < 4) {
        return 0;
    }


    ptr = buf;

    framesize = I32(ptr);
    if (framesize < I32(ptr)) {
        return 0;
    }


    if (bytes < 8) {
        state->errcode = IMAGING_CODEC_OVERRUN;
        return -1;
    }
    if (I16(ptr + 4) != 0xF1FA) {
        state->errcode = IMAGING_CODEC_UNKNOWN;
        return -1;
    }

    chunks = I16(ptr + 6);
    ptr += 16;
    bytes -= 16;


    for (c = 0; c < chunks; c++) {
        UINT8 *data;
        if (bytes < 10) {
            state->errcode = IMAGING_CODEC_OVERRUN;
            return -1;
        }
        data = ptr + 6;
        switch (I16(ptr + 4)) {
            case 4:
            case 11:

                break;
            case 7:


                lines = I16(data);
                data += 2;
                for (l = y = 0; l < lines && y < state->ysize; l++, y++) {
                    UINT8 *local_buf = (UINT8 *)im->image[y];
                    int p, packets;
                    ERR_IF_DATA_OOB(2)
                    packets = I16(data);
                    data += 2;
                    while (packets & 0x8000) {

                        if (packets & 0x4000) {
                            y += 65536 - packets;
                            if (y >= state->ysize) {
                                state->errcode = IMAGING_CODEC_OVERRUN;
                                return -1;
                            }
                            local_buf = (UINT8 *)im->image[y];
                        } else {

                            local_buf[state->xsize - 1] = (UINT8)packets;
                        }
                        ERR_IF_DATA_OOB(2)
                        packets = I16(data);
                        data += 2;
                    }
                    for (p = x = 0; p < packets; p++) {
                        ERR_IF_DATA_OOB(2)
                        x += data[0];
                        if (data[1] >= 128) {
                            ERR_IF_DATA_OOB(4)
                            i = 256 - data[1];
                            if (x + i + i > state->xsize) {
                                break;
                            }
                            for (j = 0; j < i; j++) {
                                local_buf[x++] = data[2];
                                local_buf[x++] = data[3];
                            }
                            data += 2 + 2;
                        } else {
                            i = 2 * (int)data[1];
                            if (x + i > state->xsize) {
                                break;
                            }
                            ERR_IF_DATA_OOB(2 + i)
                            memcpy(local_buf + x, data + 2, i);
                            data += 2 + i;
                            x += i;
                        }
                    }
                    if (p < packets) {
                        break;
                    }
                }
                if (l < lines) {

                    state->errcode = IMAGING_CODEC_OVERRUN;
                    return -1;
                }
                break;
            case 12:


                y = I16(data);
                ymax = y + I16(data + 2);
                data += 4;
                for (; y < ymax && y < state->ysize; y++) {
                    UINT8 *out = (UINT8 *)im->image[y];
                    ERR_IF_DATA_OOB(1)
                    int p, packets = *data++;
                    for (p = x = 0; p < packets; p++, x += i) {
                        ERR_IF_DATA_OOB(2)
                        x += data[0];
                        if (data[1] & 0x80) {
                            i = 256 - data[1];
                            if (x + i > state->xsize) {
                                break;
                            }
                            ERR_IF_DATA_OOB(3)
                            memset(out + x, data[2], i);
                            data += 3;
                        } else {
                            i = data[1];
                            if (x + i > state->xsize) {
                                break;
                            }
                            ERR_IF_DATA_OOB(2 + i)
                            memcpy(out + x, data + 2, i);
                            data += i + 2;
                        }
                    }
                    if (p < packets) {
                        break;
                    }
                }
                if (y < ymax) {

                    state->errcode = IMAGING_CODEC_OVERRUN;
                    return -1;
                }
                break;
            case 13:

                for (y = 0; y < state->ysize; y++) {
                    memset(im->image[y], 0, state->xsize);
                }
                break;
            case 15:


                for (y = 0; y < state->ysize; y++) {
                    UINT8 *out = (UINT8 *)im->image[y];
                    data += 1;
                    for (x = 0; x < state->xsize; x += i) {
                        ERR_IF_DATA_OOB(2)
                        if (data[0] & 0x80) {
                            i = 256 - data[0];
                            if (x + i > state->xsize) {
                                break;
                            }
                            ERR_IF_DATA_OOB(i + 1)
                            memcpy(out + x, data + 1, i);
                            data += i + 1;
                        } else {
                            i = data[0];
                            if (x + i > state->xsize) {
                                break;
                            }
                            memset(out + x, data[1], i);
                            data += 2;
                        }
                    }
                    if (x != state->xsize) {

                        state->errcode = IMAGING_CODEC_OVERRUN;
                        return -1;
                    }
                }
                break;
            case 16:

                if (state->xsize > bytes / state->ysize) {

                    return ptr - buf;
                }
                for (y = 0; y < state->ysize; y++) {
                    UINT8 *local_buf = (UINT8 *)im->image[y];
                    memcpy(local_buf, data, state->xsize);
                    data += state->xsize;
                }
                break;
            case 18:

                break;
            default:


                state->errcode = IMAGING_CODEC_UNKNOWN;
                return -1;
        }
        advance = I32(ptr);
        if (advance == 0 ) {

            state->errcode = IMAGING_CODEC_BROKEN;
            return -1;
        }
        if (advance < 0 || advance > bytes) {
            state->errcode = IMAGING_CODEC_OVERRUN;
            return -1;
        }
        ptr += advance;
        bytes -= advance;
    }

    return -1;
}
