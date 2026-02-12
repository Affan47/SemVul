static inline void ok_jpg_dequantize(ok_jpg_decoder *decoder, ok_jpg_component *c,
                                     int16_t *in_block, int16_t *out_block) {

    const uint8_t *q_table = decoder->q_table[c->Tq];
    for (int k = 0; k < 64; k++) {
        out_block[ok_jpg_zig_zag[k]] = in_block[k] * q_table[k];
    }
}
