flake_encode_frame(FlakeContext *s, uint8_t *frame_buffer, int16_t *samples)
{
    int fs;
    FlacEncodeContext *ctx;

    ctx = (FlacEncodeContext *) s->private_ctx;
    fs = -1;
    if((ctx->params.variable_block_size > 0) &&
       !(s->params.block_size & 7) && s->params.block_size >= 128) {
        fs = encode_frame_vbs(s, frame_buffer, samples);
    } else {
        fs = encode_frame(s, frame_buffer, samples);
    }
    return fs;
}
