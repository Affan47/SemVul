decode_init(AVCodecContext * avctx) {
    NellyMoserDecodeContext *s = avctx->priv_data;

    s->avctx = avctx;
    av_random_init(&s->random_state, 0);
    ff_mdct_init(&s->imdct_ctx, 8, 1);

    dsputil_init(&s->dsp, avctx);

    if(s->dsp.float_to_int16 == ff_float_to_int16_c) {
        s->add_bias = 385;
        s->scale_bias = 1.0/(8*32768);
    } else {
        s->add_bias = 0;
        s->scale_bias = 1.0/(1*8);
    }


    if (!ff_sine_128[127])
        ff_sine_window_init(ff_sine_128, 128);

    avctx->sample_fmt = SAMPLE_FMT_S16;
    avctx->channel_layout = CH_LAYOUT_MONO;
    return 0;
}
